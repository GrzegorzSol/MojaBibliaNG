#include <vcl.h>
#pragma hdrstop

#include "uReadingPlanWindow.h"
#include <System.IOUtils.hpp>
#include "MyBibleLibrary\MyBibleLibrary.h"
#include "MyBibleLibrary\GsReadBibleTextdata.h"
#include "uGlobalVar.h"
#include <DateUtils.hpp>
#include <System.StrUtils.hpp>
#include <System.IOUtils.hpp>
#include <sapi.h>
#include <System.Threading.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
	GsDebugClass::WriteDebug("");
#endif
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
*/
TReadingPlanWindow *ReadingPlanWindow;
enum {enImage_NoSpeakReadingText, enImage_SpeakReadingText, enImage_NoViewJournalingPlan, enImage_ViewJournalingPlan};
enum enumErrors {enErrorEndPlan = 100};
const int Gl_ciMaxShets = 8, //Maksymalna ilość par i zakładek
					Gl_ciMaxLengthPair = 6, //Minimalna długość pary (9+1+9)
					Gl_MaxNotReadingText=100;
UnicodeString Gl_ustrTableText[Gl_ciMaxShets]; //Tablica tekstów z zakładek
DataDisplayTextAnyBrowser Gl_SetDataDisplay;
TColor Gl_TablePagesColors[Gl_ciMaxShets] = {clWebForestGreen, clWebLightSeaGreen, clWebCornFlowerBlue, clWebDeepskyBlue,
																						 clWebPlum, clWebDarkTurquoise, clWebPaleGoldenrod, clWebLavender};
ISpVoice* Gl_pVoice=nullptr;
SPVOICESTATUS Gl_VoiceStatus;
//---------------------------------------------------------------------------
__fastcall TReadingPlanWindow::TReadingPlanWindow(TComponent* Owner)
	: TForm(Owner)
/**
	OPIS METOD(FUNKCJI): Konstruktor klasy TReadingPlanWindow
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->Width = 1240; this->Height = 960;
	this->Constraints->MinWidth = this->Width; this->Constraints->MinHeight = this->Height;
}
//---------------------------------------------------------------------------
void __fastcall TReadingPlanWindow::FormClose(TObject *Sender, TCloseAction &Action)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TReadingPlanWindow::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_pListWebBrowsers = new TList();
	if(!this->_pListWebBrowsers) throw(Exception("Błąd tworzenia objektu, klasy TList"));

	this->_pListWebBrowsers->Add(this->WebBrowserReadingPlan1); this->WebBrowserReadingPlan1->Navigate(WideString("about:blank").c_bstr());
	this->_pListWebBrowsers->Add(this->WebBrowserReadingPlan2); this->WebBrowserReadingPlan2->Navigate(WideString("about:blank").c_bstr());
	this->_pListWebBrowsers->Add(this->WebBrowserReadingPlan3); this->WebBrowserReadingPlan3->Navigate(WideString("about:blank").c_bstr());
	this->_pListWebBrowsers->Add(this->WebBrowserReadingPlan4); this->WebBrowserReadingPlan4->Navigate(WideString("about:blank").c_bstr());
	this->_pListWebBrowsers->Add(this->WebBrowserReadingPlan5); this->WebBrowserReadingPlan5->Navigate(WideString("about:blank").c_bstr());
	this->_pListWebBrowsers->Add(this->WebBrowserReadingPlan6); this->WebBrowserReadingPlan6->Navigate(WideString("about:blank").c_bstr());
	this->_pListWebBrowsers->Add(this->WebBrowserReadingPlan7); this->WebBrowserReadingPlan7->Navigate(WideString("about:blank").c_bstr());
	this->_pListWebBrowsers->Add(this->WebBrowserReadingPlan8); this->WebBrowserReadingPlan8->Navigate(WideString("about:blank").c_bstr());
	//Właściwe wyświetlenie tłumaczenia, księgi i rozdziału
	SecureZeroMemory(&Gl_SetDataDisplay, sizeof(DataDisplayTextAnyBrowser));
	Gl_SetDataDisplay.strBackgroundColor = ColorToWebColorStr(Gl_TablePagesColors[0]);
	Gl_SetDataDisplay.strNameFont = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_FontPlan, "Times New Roman");
	Gl_SetDataDisplay.iSizeFont = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_SizeFontPlan, "16").ToIntDef(16);
	Gl_SetDataDisplay.pMemoryStream = nullptr;
	//Obliczanie kolejnego tekstu do czytania według daty
	TDateTime dt = GlobalVar::Global_ConfigFile->ReadDate(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_StartDate, TDateTime::CurrentDate());
	this->_iDayPlan = DaysBetween(TDateTime::CurrentDate(), dt); //Jako argument dla this->_ReadSelectPlan

	this->_pHSListJournaling = new THashedStringList();
	if(!this->_pHSListJournaling) throw(Exception("Błąd funkcji THashedStringList"));
	this->_ReadSetupsJournal(); //Odczyt i ustawienia dziennika
	this->_ReadSelectPlan();
}
//---------------------------------------------------------------------------
void __fastcall TReadingPlanWindow::FormShow(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	///
}
//---------------------------------------------------------------------------
void __fastcall TReadingPlanWindow::FormActivate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Odczytanie nieprzeczytanych tekstów z planu
	for(int i=1; i<this->ChListBoxJournaling->Count; i++)
	{
		if((i<=(this->_iDayPlan + 1)) && (!this->ChListBoxJournaling->Checked[i]))
		{
			MessageBox(NULL, UnicodeString(Format(UnicodeString("Opuściłeś tekst przeznaczony na dzień: %d. Jeśli przeczytałeś go, zaznacz odpowiednią pozycje w dzienniku.") +
				 "Jeśli nie przeczytałeś odpowiedniego tekstu na zaległy dzień, wybierz go z listy. Pozycje nieprzeczytane nie mają zaznaczenia w kwadraciku, po lewej stronie pozycji. "+
				 "Po nadrobieniu zaległości zaznacz odpowiednie pozycje z listy",
				ARRAYOFCONST((i)))).c_str(), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
			this->_bIsSelectDay = true;
			break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TReadingPlanWindow::_ReadSetupsJournal()
/**
	OPIS METOD(FUNKCJI): Odczyt i ustawienia dziennika
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(TFile::Exists(GlobalVar::GlobalPath_CurrentActivePlan))
	{
		this->_pHSListJournaling->LoadFromFile(GlobalVar::GlobalPath_CurrentActivePlan, TEncoding::UTF8);
		this->ChListBoxJournaling->Items->BeginUpdate();
		for(int i=0; i<this->_pHSListJournaling->Count; i++)
		{
			if(i==0) //Pierwsza pozycja to nazwa planu
			{
				this->ChListBoxJournaling->Items->Add(TPath::GetFileNameWithoutExtension(this->_pHSListJournaling->Strings[i]));
				this->ChListBoxJournaling->ItemEnabled[0] = false;
			}
			else
			{
				this->ChListBoxJournaling->Items->Add(this->_pHSListJournaling->Names[i]);
				this->ChListBoxJournaling->Checked[i] = (this->_pHSListJournaling->ValueFromIndex[i].ToIntDef(0) != 0);
				if(i>(this->_iDayPlan + 1))
					{this->ChListBoxJournaling->ItemEnabled[i] = false;}
			}
		}

		this->ChListBoxJournaling->Items->EndUpdate();
		this->ChListBoxJournaling->Header[0] = true;
		this->ChListBoxJournaling->ItemIndex = this->_iDayPlan + 1;
	}
}
//---------------------------------------------------------------------------
void __fastcall TReadingPlanWindow::_ReadSelectPlan(const int iSetDayPlan)
/**
	OPIS METOD(FUNKCJI): Odczyt i wyświetlenie pozycji aktualnego planu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	const UnicodeString custrSeparator = "|";
	THashedStringList *pHSLFilePlan=nullptr, *pHSList=nullptr;
	UnicodeString ustrNameTraPlan = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_TranslateRPlan, "bwa.pltmb - Biblia Warszawska");
	//Odczyt indeksu tłumaczenia używanego w planie czytania
	int iPosDescription = ustrNameTraPlan.Pos("- "), //Opis tłumaczenia po nazwie pliku t€maczenia (nazwa pliku - Opis tłumaczenia)
			iReadIDTr = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_IDTranslateRPlan, -1),
			iPosName = ustrNameTraPlan.Pos(" "),
			iLengthPair, iCurrentDayPlan=-1;
	TDateTime dt = GlobalVar::Global_ConfigFile->ReadDate(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_StartDate, TDateTime::CurrentDate());

	if(iSetDayPlan == -1) iCurrentDayPlan = this->_iDayPlan; else iCurrentDayPlan = iSetDayPlan;

	if(iReadIDTr > -1) //Wydobycie indeksu dla używanego tłumaczenia w planie, jeśli nie zostało to zapisane w konfiguracji
	{
		UnicodeString ustrIDTPlan = ustrNameTraPlan.SubString(1, iPosName-1); //Sama nazwa tłumaczenia

		for(int i=0; i<GlobalVar::SDirTranslatesList.Length; i++)
		{
			if(ustrIDTPlan == TPath::GetFileName(GlobalVar::SDirTranslatesList[i])) //Lista ścieżek dostępu do, wszystkich dostępnych tłumaczeń
			{
				this->_iIDTranslateReadingPlan = i;
				break;
			}
		}
	}
	//---
	this->PageControlReadingPlanes->ActivePageIndex = 0;
	//---
	if(TDirectory::Exists(GlobalVar::Global_custrPathAllReadingPlan))
	//Czy istnieje katalog z plikami planów
	{
		try
		{
			try
			{
				const UnicodeString ustrPathFileReadingPlan = TPath::Combine(GlobalVar::Global_custrPathAllReadingPlan,
					GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_SelectPlan, ""));

				pHSLFilePlan = new THashedStringList(); //Lista odczytanych lini zakresów z pliku planu (max. 8)
				if(!pHSLFilePlan) throw(Exception("Błąd funkcji THashedStringList"));
				pHSList = new THashedStringList(); //Lista par granic tekstu, odczytanych z pliku planu
				if(!pHSList) throw(Exception("Błąd funkcji THashedStringList"));

				pHSLFilePlan->LoadFromFile(ustrPathFileReadingPlan, TEncoding::UTF8);
				UnicodeString ustrInfosCurrentPlan = "Aktualny plan czytania: \"%s\". Tłumczenie: \"%s\". Aktualna data: %s. Data rozpoczęcia aktualnego planu: %s. Dzień %d czytania z %d dni.";
				this->LabelInfosReadingPlan->Caption = Format(ustrInfosCurrentPlan,
					ARRAYOFCONST((pHSLFilePlan->Strings[0], ustrNameTraPlan.SubString(iPosDescription+2, 100), TDateTime::CurrentDate().FormatString("dd-mm-yyyy"),
					dt.FormatString("dd-mm-yyyy"), iCurrentDayPlan+1, pHSLFilePlan->Count-1)));

				if(iCurrentDayPlan >= pHSLFilePlan->Count-1)
				{
					throw(enErrorEndPlan);
				}
				//											1						2						3
				//sda tablica par (para1 para1|para2 para2|para3 para3)
				TStringDynArray sda = SplitString(pHSLFilePlan->Strings[iCurrentDayPlan+1], custrSeparator); //Ilość par rozdzialona znakiem custrSeparator
				for(int i=0; i<sda.Length; i++)
				{
					iLengthPair = UnicodeString(sda[i]).Length(); //Długość pary
					if(iLengthPair >= Gl_ciMaxLengthPair) {pHSList->AddObject(sda[i], 0);} //StringLista "pHSList" zawiera pary
				}
				for(int i=0; i<Gl_ciMaxShets; i++)
				//Przegląd wszystkich możliwych zakładek
				{
					//Wyodrębnienie objektu klasy TWebBrowser
					TWebBrowser *pWebBrowser = static_cast<TWebBrowser *>(this->_pListWebBrowsers->Items[i]);
					if(pWebBrowser)
					{
						//Kolor podkładu, kolejnej zakładki
						Gl_SetDataDisplay.strBackgroundColor = ColorToWebColorStr(Gl_TablePagesColors[i]);
						if(i<pHSList->Count)
						///Odczyt par adresów tekstu (pHSList) i otwarcie zakładek
						{
							Gl_ustrTableText[i] = GsReadBibleTextData::DisplayExceptTextInHTML(pWebBrowser, this->_iIDTranslateReadingPlan, pHSList->Strings[i], Gl_SetDataDisplay);
							TTabSheet *pTabSheet = this->PageControlReadingPlanes->Pages[i];
							if(pTabSheet) pTabSheet->TabVisible = true;
						}
						else
						//Zakładka nie posiada pary, więc bedzie niewidoczna
						{
							TTabSheet *pTabSheet = this->PageControlReadingPlanes->Pages[i];
							if(pTabSheet) pTabSheet->TabVisible = false;
						}
					}
				}
			} //try catch
			catch(enumErrors enEr)
			{
				switch(enEr)
				{
					case enErrorEndPlan:
						MessageBox(NULL, TEXT("Wybrany Plan czytania Pisma Świętego został zakończony"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
						this->LabelInfosReadingPlan->Alignment = taCenter;
						this->LabelInfosReadingPlan->Caption = "Wybrany Plan czytania Pisma Świętego został zakończony, rozpocznij inny plan, lub powtórz aktualny";
						break;
				}
			}
			catch(Exception &e)
			{
				MessageBox(NULL, e.Message.c_str(), TEXT("Informacje aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
			}
		} //try
		__finally
		{
			if(pHSList) {delete pHSList; pHSList = nullptr;}
			if(pHSLFilePlan) {delete pHSLFilePlan; pHSLFilePlan = nullptr;}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TReadingPlanWindow::FormDestroy(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_pHSListJournaling->SaveToFile(GlobalVar::GlobalPath_CurrentActivePlan, TEncoding::UTF8);
	if(this->_pListWebBrowsers) {delete this->_pListWebBrowsers; this->_pListWebBrowsers = nullptr;}
	if(this->_pHSListJournaling) {delete this->_pHSListJournaling; this->_pHSListJournaling = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall TReadingPlanWindow::PageControlReadingPlanesDrawTab(TCustomTabControl *Control,
					int TabIndex, const TRect &Rect, bool Active)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TPageControl *pPControl = dynamic_cast<TPageControl *>(Control);
	if(!pPControl) return;
	//-----
	TTabSheet *pActSheet = dynamic_cast<TTabSheet *>(pPControl->Pages[TabIndex]);	//Aktualna zakładka
	if(!pActSheet) return;
	//---
	TRect MyRect(Rect);
	if(Active)
	{
		pPControl->Canvas->Font->Color = clYellow;
		pPControl->Canvas->Brush->Color = clBlue;
	}
	else
	{
		pPControl->Canvas->Brush->Color = clCream;
	}
	pPControl->Canvas->FillRect(Rect);
	pPControl->Images->Draw(pPControl->Canvas, Rect.Left + 4, (Rect.Top + ((Rect.Bottom - Rect.Top) / 2)) - (pPControl->Images->Height / 2), pActSheet->ImageIndex);
	MyRect.Left += (pPControl->Images->Width + 4);
	DrawText(pPControl->Canvas->Handle, pActSheet->Caption.c_str(), -1, &MyRect, DT_VCENTER | DT_SINGLELINE);
}
//---------------------------------------------------------------------------
void __fastcall TReadingPlanWindow::_SpeakText(const UnicodeString ustrTextSpeak)
/**
	OPIS METOD(FUNKCJI): Tekst do przeczytania na głos przez syntezator mowy
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	HRESULT hr, hResult;
	_di_ITask MyTask[1];
	int value=0;

	if(ustrTextSpeak.IsEmpty()) return;

	int iRate = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_SetRate, -2),
			iVolume = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_SetVolume, 100);

	MyTask[0] = TTask::Create([&, ustrTextSpeak, iRate, iVolume] () //Funkcja Lambda
	{
		try
		{
			try
			{
				hResult = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
				if(FAILED(hResult)) throw(Exception("Błąd funkcji syntezy mowy"));

				hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&Gl_pVoice);
				if(SUCCEEDED(hr))
				{
					Gl_pVoice->SetRate(iRate);
					Gl_pVoice->SetVolume(iVolume);

					hr = Gl_pVoice->Speak(ustrTextSpeak.c_str(), 0, NULL);
					this->SButtonStartSpeak->Down = false;
					this->SButtonStartSpeak->Update();
					if(Gl_pVoice)
					{
						Gl_pVoice->Release();
						Gl_pVoice = nullptr;
					}
					//TInterlocked::Add(value, 500);
				}
			}
			catch(Exception &e)
			{
				MessageBox(NULL, e.Message.c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
			}
		}
		__finally
		{
			CoUninitialize();
		}
	});
	MyTask[0]->Start();
	//MyTask[0]->Release();
}
//---------------------------------------------------------------------------
void __fastcall TReadingPlanWindow::SButtonStartSpeakClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TSpeedButton *pSButton = dynamic_cast<TSpeedButton *>(Sender);
	if(!pSButton) return;
	//---
	if(pSButton->Down)
	{
		if(!Gl_pVoice)
		{
			this->_SpeakText(Gl_ustrTableText[this->PageControlReadingPlanes->ActivePageIndex]);
		}
		else
		{
			Gl_pVoice->GetStatus(&Gl_VoiceStatus, NULL);
			if(Gl_VoiceStatus.dwRunningState == 0) Gl_pVoice->Resume();
		}
	} //if(pSButton->Down)
	else
	{
		if(!Gl_pVoice) return;

		Gl_pVoice->GetStatus(&Gl_VoiceStatus, NULL);
		if(Gl_VoiceStatus.dwRunningState == SPRS_IS_SPEAKING) Gl_pVoice->Pause();
	} //else(pSButton->Down)
}
//---------------------------------------------------------------------------
void __fastcall TReadingPlanWindow::SButtonJournalingClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Ukrywanie lub pokazywanie dziennika
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TSpeedButton *pSButton = dynamic_cast<TSpeedButton *>(Sender);
	if(!pSButton) return;
	//---
	this->PanelJournaling->Visible = pSButton->Down;
	this->SplitterSizeJournaling->Left = this->PageControlReadingPlanes->Left + this->PageControlReadingPlanes->Width;
}
//---------------------------------------------------------------------------
void __fastcall TReadingPlanWindow::SButtonStopSpeakClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Całkowite stopowanie czytania tekstu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TSpeedButton *pSButton = dynamic_cast<TSpeedButton *>(Sender);
	if(!pSButton) return;
	//---
	if(Gl_pVoice)
	{
		Gl_pVoice->Release();
		Gl_pVoice = nullptr;
	}
}
//---------------------------------------------------------------------------
void __fastcall TReadingPlanWindow::ChListBoxJournalingClickCheck(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCheckListBox *pChLBox = dynamic_cast<TCheckListBox *>(Sender);
	if(!pChLBox) return;
	//---
	if(pChLBox->Checked[pChLBox->ItemIndex])
	{
		this->_pHSListJournaling->ValueFromIndex[pChLBox->ItemIndex] = "1";
	}
	else
	{
		this->_pHSListJournaling->ValueFromIndex[pChLBox->ItemIndex] = "0";
	}
}
//---------------------------------------------------------------------------
void __fastcall TReadingPlanWindow::ChListBoxJournalingDrawItem(TWinControl *Control,
					int Index, TRect &Rect, TOwnerDrawState State)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCheckListBox *pChLBox = dynamic_cast<TCheckListBox *>(Control);
	if(!pChLBox) return;
	//---
	TCanvas *pCanvas = pChLBox->Canvas;
	pCanvas->Font = pChLBox->Font;
	TRect myRect(Rect);
	int iFlags=0;
	//---
	if(pChLBox->Header[Index])
	{
		pCanvas->Brush->Color = clWebIndigo;
		pCanvas->Font->Style = TFontStyles() << fsBold;
		pCanvas->Font->Color = clYellow;
	}
	else
	{
		if(Index > this->_iDayPlan + 1)
		{
			pCanvas->Brush->Color = clWebPeachPuff;
		}
		else
		{
			pCanvas->Brush->Color = clWebPaleTurquoise;
		}
		//---
		if(State.Contains(odSelected))
		{
			pCanvas->Brush->Color = clRed;
		}
	}
	//---
	pCanvas->FillRect(Rect);
	myRect.Inflate(-2, 0, 0, 0);

	if(Index == 0) //Tytuł
		{iFlags = DT_SINGLELINE | DT_VCENTER | DT_CENTER;}
	else
		{iFlags = DT_SINGLELINE | DT_VCENTER;}

	DrawText(pCanvas->Handle, pChLBox->Items->Strings[Index].c_str(), -1, &myRect,	iFlags);
}
//---------------------------------------------------------------------------
void __fastcall TReadingPlanWindow::ChListBoxJournalingClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCheckListBox *pChLBox = dynamic_cast<TCheckListBox *>(Sender);
	if(!pChLBox || pChLBox->ItemIndex == -1) return;
	//---
	if(this->_bIsSelectDay) this->_ReadSelectPlan(pChLBox->ItemIndex - 1); //Czy istnieje możliwość wybory dnia do przeczytania?
}
//---------------------------------------------------------------------------
void __fastcall TReadingPlanWindow::SplitterSizeJournalingCanResize(TObject *Sender,
					int &NewSize, bool &Accept)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TSplitter *pSplitter = dynamic_cast<TSplitter *>(Sender);
	if(!pSplitter) return;
	//---
	if(NewSize > 480) NewSize = 480;
	else if(NewSize < 244) NewSize = 244;
}
//---------------------------------------------------------------------------

