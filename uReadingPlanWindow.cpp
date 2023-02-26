#include <vcl.h>
#pragma hdrstop

#include "uReadingPlanWindow.h"
#include <System.IOUtils.hpp>
#include "GsReadBibleTextClass\GsReadBibleTextClass.h"
#include "uGlobalVar.h"
#include <DateUtils.hpp>
#include <System.StrUtils.hpp>
#include <System.IOUtils.hpp>
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
enum {enImage_ReadingText};
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
  UnicodeString ustrNameTranslate,
								ustrNameTraPlan = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_TranslateRPlan, "bwa.pltmb - Biblia Warszawska");
	int iPosDescription = ustrNameTraPlan.Pos("- "),
			iPosName = ustrNameTraPlan.Pos(" "),
			iBook=0, iChapt=20, //Tymczasowo
			iDayPlan,
			//Odczyt indeksu tłumaczenia używanego w planie czytania
			iReadIDTr = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_IDTranslateRPlan, -1);
	const int ciMaxShets = 8;
	enum enumErrors {enErrorEndPlan = 100};
	THashedStringList *pHSLFilePlan=nullptr, *pHSList=nullptr;

  //Obliczanie kolejnego tekstu do czytania według daty
	TDateTime dt = GlobalVar::Global_ConfigFile->ReadDate(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_StartDate, TDateTime::CurrentDate());
	iDayPlan = DaysBetween(TDateTime::CurrentDate(), dt);

	TColor TablePagesColors[ciMaxShets] = {clWebForestGreen, clWebLightSeaGreen, clWebCornFlowerBlue, clWebDeepskyBlue,
																				 clWebPlum, clWebDarkTurquoise, clWebPaleGoldenrod, clWebLavender};
	this->_pListWebBrowsers = new TList();
	if(!this->_pListWebBrowsers) throw(Exception("Błąd tworzenia objektu, klasy TList"));

	this->_pListWebBrowsers->Add(this->WebBrowserReadingPlan1);
	this->_pListWebBrowsers->Add(this->WebBrowserReadingPlan2);
	this->_pListWebBrowsers->Add(this->WebBrowserReadingPlan3);
	this->_pListWebBrowsers->Add(this->WebBrowserReadingPlan4);
	this->_pListWebBrowsers->Add(this->WebBrowserReadingPlan5);
	this->_pListWebBrowsers->Add(this->WebBrowserReadingPlan6);
	this->_pListWebBrowsers->Add(this->WebBrowserReadingPlan7);
	this->_pListWebBrowsers->Add(this->WebBrowserReadingPlan8);

	if(iReadIDTr > -1) //Wydobycie indeksu dla używanego tłumaczenia w planie, jeśli nie zostało to zapisane w konfiguracji
	{
		UnicodeString ustrIDTPlan = ustrNameTraPlan.SubString(1, iPosName-1); //Sama nazwa tłumaczenia

		for(int i=0; i<GlobalVar::SDirTranslatesList.Length; i++)
		{
			if(ustrIDTPlan == TPath::GetFileName(GlobalVar::SDirTranslatesList[i]))
			{
				this->_iIDTranslateReadingPlan = i;
			}
		}
	}

	this->PageControlReadingPlanes->ActivePageIndex = 0;
  //Wypełnienie kontrolki pustą stroną.
	for(int i=0; i<this->_pListWebBrowsers->Count; i++)
	{
		TWebBrowser *pWebBrowser = static_cast<TWebBrowser *>(this->_pListWebBrowsers->Items[i]);
		if(pWebBrowser) {pWebBrowser->Navigate(WideString("about:blank").c_bstr());}
	}

	//Właściwe wyświetlenie tłumaczenia, księgi i rozdziału
	DataDisplayTextAnyBrowser SetDataDisplay;
	SecureZeroMemory(&SetDataDisplay, sizeof(DataDisplayTextAnyBrowser));
	SetDataDisplay.strBackgroundColor = ColorToWebColorStr(TablePagesColors[0]);
	SetDataDisplay.strNameFont = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_FontPlan, "Times New Roman");
	SetDataDisplay.iSizeFont = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_SizeFontPlan, "16").ToIntDef(16);
	SetDataDisplay.pMemoryStream = nullptr;
	SetDataDisplay.bIsHorizontLine = false;
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
					dt.FormatString("dd-mm-yyyy"), iDayPlan+1, pHSLFilePlan->Count-1)));

				if(iDayPlan >= pHSLFilePlan->Count-1)
				{
					throw(enErrorEndPlan);
				}

				TStringDynArray sda = SplitString(pHSLFilePlan->Strings[iDayPlan+1], "|");
  			for(int i=0; i<sda.Length; i++)
  			{
  				if(sda[i].Length() > 8) {pHSList->AddObject(sda[i], 0);}
  			}

    		for(int i=0; i<pHSList->Count; i++)
  			//Odczyt par adresów tekstu i otwarcie zakładek
    		{
  				if(i > ciMaxShets-1) break;
    			TWebBrowser *pWebBrowser = static_cast<TWebBrowser *>(this->_pListWebBrowsers->Items[i]);
  				if(pWebBrowser)
    			{
    				SetDataDisplay.strBackgroundColor = ColorToWebColorStr(TablePagesColors[i]);
  					GsReadBibleTextData::DisplayExceptTextInHTML(pWebBrowser, this->_iIDTranslateReadingPlan, pHSList->Strings[i], SetDataDisplay);
    				TTabSheet *pTabSheet = this->PageControlReadingPlanes->Pages[i];
  					if(pTabSheet) pTabSheet->TabVisible = true;
  					//Wyświetlenie zakresu na zakładkach
  					pTabSheet->Caption = Format("%s %d:%d - %s %d:%d", ARRAYOFCONST((GsReadBibleTextData::GsInfoAllBooks[pHSList->Strings[i].SubString(1, 3).ToInt() - 1].ShortNameBook,
  						pHSList->Strings[i].SubString(4, 3).ToInt(), pHSList->Strings[i].SubString(7, 3).ToInt(),
							GsReadBibleTextData::GsInfoAllBooks[pHSList->Strings[i].SubString(11, 3).ToInt() - 1].ShortNameBook,
  						pHSList->Strings[i].SubString(14, 3).ToInt(), pHSList->Strings[i].SubString(17, 3).ToInt())));
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
  if(this->_pListWebBrowsers) {delete this->_pListWebBrowsers; this->_pListWebBrowsers = nullptr;}
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

