#include <vcl.h>
#pragma hdrstop

#include "uImageAndTextWindow.h"
#include "uGlobalvar.h"
#include <System.IOUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TImageAndTextWindow *ImageAndTextWindow;
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug("");
#endif
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
*/
enum {
				//Numery ikon
				enIcon_CloseSheet, enIcon_SaveAs, enIcon_Save, enIcon_Text, enIcon_ResizeWorkPanel,
				//Numery zakładek po lewej stronie
				enSheet_SelectImage=0, enSheet_ToolsImage,
				//Tagi objektów, klasy TPageControl
				enPControl_ImageTools=100, enPControl_ImageDisplay,
				//Tagi dla ikon
				enIconTag_CloseSheet=200, enIconTag_SaveAs, enIconTag_Save, enIconTag_Text, enIconTag_ResizeWorkPanel,
				//Tagi dla objektu, klasy TComboBox
				enTagCBox_ColorFont=300, enTagCBox_SelectFont, enTagCBox_SizeFont,
				//Tagi dla objektów, klasy TTrackBar
				enTagTrBar_Opacity=400,
				//Tagi dla przycisków TButton
				enTagAcceptText=500, enTagAcceptOptionsText
		 };
UnicodeString ustrFontname[] = {"Arial", "Times New Roman", "Gabriola", "Impact", "Seagull", "Segoe Script", "Segoe UI", "Tahoma", "Verdana",
																"Comic Sans MS", "Calibri"},
							ustrFontSize[] = {"10", "12", "16", "18", "24", "28", "36", "48", "72", "98", "102", "122", "148"};
//---------------------------------------------------------------------------
__fastcall TImageAndTextWindow::TImageAndTextWindow(TComponent* Owner)
	: TForm(Owner)
/**
	OPIS METOD(FUNKCJI): Konstruktor klasy TImageAndTextWindow
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  this->_IsStart = true; //Uruchomienie okna
	//Stworzenie zawartości zakładki z multimediami
	GsPanelMultiM *pGsPanelMultiM = new GsPanelMultiM(this->TabSheetSelectImages, this->PControlImageAndText);
	if(!pGsPanelMultiM) throw(Exception("Błąd inicjalizacji objektu GsPanelMultiM"));
	pGsPanelMultiM->Parent = this->TabSheetSelectImages;
	pGsPanelMultiM->Align = alClient;

	this->PControlTools->ActivePageIndex = enSheet_SelectImage;

	this->_InitTagAndHint();
	//Inicjalizacja objektów, klasy TCombobox
	for(unsigned int i=0; i<ARRAYSIZE(ustrFontname); i++)
	{
		this->CBoxSelectFont->AddItem(ustrFontname[i], 0);
	}
	int iIndexFontName = this->CBoxSelectFont->Items->IndexOf(CFNameFont);
	this->CBoxSelectFont->ItemIndex = iIndexFontName;
	for(unsigned int i=0; i<ARRAYSIZE(ustrFontSize); i++)
	{
		this->CBoxSizeFont->AddItem(ustrFontSize[i], 0);
	}
	int iIndexFontSize = this->CBoxSizeFont->Items->IndexOf(UnicodeString((int)CFSizeFont));
	this->CBoxSizeFont->ItemIndex = iIndexFontSize;
	//---
	this->TrBarOpacityBrush->Max = CFOpacityBrush * 10;
	this->TrBarOpacityBrush->Position = this->TrBarOpacityBrush->Max;
	//---
	this->_bChangeOptionsText = false;  //true jesli zmieniono parametr tekstu
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::FormClose(TObject *Sender, TCloseAction &Action)
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
void __fastcall TImageAndTextWindow::_InitTagAndHint()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  this->PControlTools->Tag = enPControl_ImageTools;
	this->PControlImageAndText->Tag = enPControl_ImageDisplay;
	//---
	this->TrBarOpacityBrush->Tag = enTagTrBar_Opacity;
	//---
	this->Act_CloseActiveSheet->Tag = enIconTag_CloseSheet;
	this->Act_CloseActiveSheet->Hint = Format("Zamknięcie zakładki|Zamknięcie aktualnie aktywnej zakładki z grafiką|%u", ARRAYOFCONST((this->Act_CloseActiveSheet->ImageIndex)));
	this->Act_SaveAs->Tag = enIconTag_SaveAs;
	this->Act_SaveAs->Hint = Format("Zapisanie grafiki pod nową nazwą...|Zapisanie grafiki pod nową nazwą. Typ pliku jest rozpoznawalny po rozszerzeniu|%u", ARRAYOFCONST((this->Act_SaveAs->ImageIndex)));
	this->Act_Save->Tag = enIconTag_Save;
	this->Act_Save->Hint = Format("Zapisanie grafiki pod starą nazwą|Zapisanie grafiki pod starą nazwą, gdy została zmieniona|%u", ARRAYOFCONST((this->Act_Save->ImageIndex)));
	this->Act_Text->Tag = enIconTag_Text;
	this->Act_Text->Hint = Format("Przełącznik widocznosci tekstu|Przełącznik umożliwijący nakładanie tekst na wczytany obrazek.|%u", ARRAYOFCONST((this->Act_Text->ImageIndex)));
	this->Act_ResizeWorkPanel->Tag = enIconTag_ResizeWorkPanel;
	this->Act_ResizeWorkPanel->Hint = Format("Przełącznik widocznosci lewego panelu z narzedziami|Przełącznik umożliwijący schowanie, lub odkrycie lewego panelu z narzedziami.|%u", ARRAYOFCONST((this->Act_ResizeWorkPanel->ImageIndex)));
  //Tagi dla objektu, klasy TComboBox
	this->CBoxSelectColorText->Tag = enTagCBox_ColorFont;
	this->CBoxSelectFont->Tag = enTagCBox_SelectFont;
	this->CBoxSizeFont->Tag = enTagCBox_SizeFont;
	//tagi dla objektu, klasy TButton
	this->ButtDisplayNewText->Tag = enTagAcceptText;
	this->ButtAcceptAllOptionsText->Tag = enTagAcceptOptionsText;
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::_ReadAllParameters(const GsDirect2DClass *pGsDirect2DClass)
/**
	OPIS METOD(FUNKCJI): Odczytuje wszystkie parametry dla obrazka (objektu, klasy GsDirect2DClass)
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  this->MemoImageAndText->Text = pGsDirect2DClass->TextWrite;
	this->CBoxSelectColorText->Selected = pGsDirect2DClass->StandartColorText;
	//Odczyt używanego kroju czcionki
	int iIndexFont = this->CBoxSelectFont->Items->IndexOf(pGsDirect2DClass->NameFont);
	this->CBoxSelectFont->ItemIndex = iIndexFont;
	//Odczyt wielkośći czcionki
	int iIndexFontSize = this->CBoxSizeFont->Items->IndexOf(UnicodeString((int)pGsDirect2DClass->SizeFont));
	this->CBoxSizeFont->ItemIndex = iIndexFontSize;
	//Odczyt przezroczystości
	this->TrBarOpacityBrush->Position = (int)(pGsDirect2DClass->OpacityBrush * 10.0);
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::Act_CloseActiveSheetExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if((this->PControlImageAndText->PageCount <= 0)  || (this->PControlImageAndText->ActivePageIndex == -1)) return;
	//---
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	GsTabSheetGraphics *pGsTabSheetGraphics = dynamic_cast<GsTabSheetGraphics *>(this->PControlImageAndText->ActivePage);
	if(pGsTabSheetGraphics)
	{
		delete pGsTabSheetGraphics;
		this->Act_CloseActiveSheet->Enabled = (this->PControlImageAndText->PageCount > 0);
		this->Act_SaveAs->Enabled = this->Act_CloseActiveSheet->Enabled;
		this->Act_Save->Enabled = this->Act_CloseActiveSheet->Enabled;
		this->Act_Text->Enabled = this->Act_CloseActiveSheet->Enabled;
		this->SplitViewImageAndText->Opened = !this->Act_CloseActiveSheet->Enabled;

		this->MemoImageAndText->Enabled = this->Act_CloseActiveSheet->Enabled;
		this->ButtDisplayNewText->Enabled = this->Act_CloseActiveSheet->Enabled;
		this->ButtAcceptAllOptionsText->Enabled = this->Act_CloseActiveSheet->Enabled;
		this->CBoxSelectColorText->Enabled = this->Act_CloseActiveSheet->Enabled;
		this->CBoxSelectFont->Enabled = this->Act_CloseActiveSheet->Enabled;
		this->CBoxSizeFont->Enabled = this->Act_CloseActiveSheet->Enabled;
	}
}
//---------------------------------------------------------------------------
GsDirect2DClass *__fastcall TImageAndTextWindow::_GetDirect2DFromActiveSheet()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->PControlImageAndText->PageCount == 0) return 0;
	//---
	GsTabSheetGraphics *pGsTabSheetGraphics = dynamic_cast<GsTabSheetGraphics *>(this->PControlImageAndText->ActivePage);
  if(pGsTabSheetGraphics)
	{
		GsDirect2DClass *pGsDirect2DClass = pGsTabSheetGraphics->GetD2DObject();
		return  pGsDirect2DClass;
	}
  return 0;
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::PControlImageAndTextEnter(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  #if defined(_DEBUGINFO_)
		GsDebugClass::WriteDebug("TImageAndTextWindow::PControlImageAndTextEnter");
	#endif
	TPageControl *pPageControl = dynamic_cast<TPageControl *>(Sender);
	if(!pPageControl) return;
	//---
	if(pPageControl->PageCount > 0)
	{
		this->Act_CloseActiveSheet->Enabled = true;
    this->Act_SaveAs->Enabled = this->Act_CloseActiveSheet->Enabled;
		this->Act_Save->Enabled = this->Act_CloseActiveSheet->Enabled;
		this->Act_Text->Enabled = this->Act_CloseActiveSheet->Enabled;
		this->SplitViewImageAndText->Opened = !this->Act_CloseActiveSheet->Enabled;
		this->Act_ResizeWorkPanel->Checked = this->SplitViewImageAndText->Opened;

		GsDirect2DClass *pGsDirect2DClass = this->_GetDirect2DFromActiveSheet();
		if(pGsDirect2DClass)
		{
			//Na wybranej zakładce, jest uaktywnione wyświetlanie tekstu na grafice, lub nie
			this->Act_Text->Checked = pGsDirect2DClass->IsDisplayText;
			this->_ReadAllParameters(pGsDirect2DClass);
		}
		this->_bChangeOptionsText = false;  //true jesli zmieniono parametr tekstu
		this->ButtAcceptAllOptionsText->Enabled = this->_bChangeOptionsText;
	}
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::PControlImageAndTextDrawTab(TCustomTabControl *Control,
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
	switch(pPControl->Tag)
	{
		case enPControl_ImageTools:
    	if(Active)
			{
				pPControl->Canvas->Font->Color = clYellow;
				pPControl->Canvas->Brush->Color = clRed;
        if(this->SplitViewImageAndText->CompactWidth == 0) this->SplitViewImageAndText->CompactWidth = Rect.GetWidth();
			}
			pPControl->Canvas->Font->Orientation = 900;
			pPControl->Canvas->FillRect(Rect);
			MyRect.Inflate(-4, 0, 0, 9);
			DrawText(pPControl->Canvas->Handle, pActSheet->Caption.c_str(), -1, &MyRect, DT_BOTTOM | DT_SINGLELINE);
			break;
			//---
		case enPControl_ImageDisplay:
			if(Active)
			{
				pPControl->Canvas->Font->Color = clYellow;
				pPControl->Canvas->Brush->Color = clBlue;
			}
			pPControl->Canvas->FillRect(Rect);
			//MyRect.Inflate(-4, 0, 0, 0);
			DrawText(pPControl->Canvas->Handle, pActSheet->Caption.c_str(), -1, &MyRect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
			break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::Act_SaveAsExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	this->SplitViewImageAndText->Opened = false;
  this->Act_ResizeWorkPanel->Checked = this->SplitViewImageAndText->Opened;
	//---
  TSaveDialog *pSaveDialog = new TSaveDialog(this);
	if(!pSaveDialog) throw(Exception("Błąd inicjalizacji objektu TSaveDialog"));
	pSaveDialog->Title = "Podaj nazwę projektu do zapisu";
	pSaveDialog->Filter = UnicodeString("Pliki typu jpg(*.jpg)|*.JPG|") +
												"Plik typu png(*.png)|*.PNG|" +
												"Plik typu gif(*.gif)|*.GIF|" +
												"Plik typu tiff(*.tiff)|*.TIFF|" +
												"Plik typu bmp(*.bmp)|*.BMP|"
												"Domyślny typ pliku(*.*)|*.*";
	pSaveDialog->Options << ofOverwritePrompt << ofHideReadOnly;
	pSaveDialog->InitialDir = GlobalVar::Global_custrGetExeDir; //Katalog aplikacji
	pSaveDialog->DefaultExt = "jpg";

	UnicodeString ustrPathSaveFile;
	try
	{
		try
		{
			if(pSaveDialog->Execute())
			{
				ustrPathSaveFile = pSaveDialog->FileName.LowerCase();
        #if defined(_DEBUGINFO_)
					GsDebugClass::WriteDebug(Format("ustrPathSaveFile: %s", ARRAYOFCONST((ustrPathSaveFile))));
				#endif
				if(this->PControlImageAndText->PageCount > 0)
				{
					GsDirect2DClass *pGsDirect2DClass = this->_GetDirect2DFromActiveSheet();
					if(pGsDirect2DClass)
					{
						pGsDirect2DClass->GsD2D_SavePicture(ustrPathSaveFile);
					}
        }
			}
		}
		catch(...)
		{
			MessageBox(NULL, Format("Błąd operacji zapisu pliku o nazwie: %s do zapisu", ARRAYOFCONST((ustrPathSaveFile))).c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
    }
	}
	__finally
	{
		if(pSaveDialog) {delete pSaveDialog; pSaveDialog = 0;}
	}
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::Act_SaveExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::Act_TextExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):Uaktywnione wyświetlanie tekstu na grafice, lub nie
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	GsDirect2DClass *pGsDirect2DClass = this->_GetDirect2DFromActiveSheet();
	if(pGsDirect2DClass)
	{
		pGsDirect2DClass->IsDisplayText = pAction->Checked;
		if(pAction->Checked) this->MemoImageAndText->Text = pGsDirect2DClass->TextWrite;
		//Objekty aktywne, zależnie od tego czy jest załączony przełącznik w głównym menu, do wyświetlania tekstu
		this->MemoImageAndText->Enabled = pAction->Checked;
		this->ButtDisplayNewText->Enabled = pAction->Checked;
		this->ButtAcceptAllOptionsText->Enabled = pAction->Checked && this->_bChangeOptionsText;
		this->CBoxSelectColorText->Enabled = pAction->Checked;
		this->CBoxSelectFont->Enabled = pAction->Checked;
		this->CBoxSizeFont->Enabled = pAction->Checked;
		this->TrBarOpacityBrush->Enabled = pAction->Checked;
		//---
		this->_ReadAllParameters(pGsDirect2DClass);
	}
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::Act_ResizeWorkPanelExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):Chowanie lub pokazywanie panelu zakładek z narzedziami
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	this->SplitViewImageAndText->Opened = pAction->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::PControlImageAndTextChange(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):Zmiana aktywnej zakładki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TPageControl *pPControl = dynamic_cast<TPageControl *>(Sender);
	if(!pPControl) return;
	//---
	switch(pPControl->Tag)
	{
		case enPControl_ImageDisplay:
		{
			GsDirect2DClass *pGsDirect2DClass = this->_GetDirect2DFromActiveSheet();
			if(pGsDirect2DClass)
			{
				//Na wybranej zakładce, jest uaktywnione wyświetlanie tekstu na grafice, lub nie
				this->Act_Text->Checked = pGsDirect2DClass->IsDisplayText;
				this->MemoImageAndText->Text = pGsDirect2DClass->TextWrite;
        //Objekty aktywne, zależnie od tego czy na zakładce jest object z załączoną flaga wyswietlania tekstu
				this->MemoImageAndText->Enabled = this->Act_Text->Checked;
				this->ButtDisplayNewText->Enabled = this->Act_Text->Checked;
				//this->ButtAcceptAllOptionsText->Enabled = this->Act_Text->Checked;
				this->CBoxSelectColorText->Enabled = this->Act_Text->Checked;
				this->CBoxSelectFont->Enabled = this->Act_Text->Checked;
				this->CBoxSizeFont->Enabled = this->Act_Text->Checked;
				this->TrBarOpacityBrush->Enabled = this->Act_Text->Checked;

				this->_ReadAllParameters(pGsDirect2DClass);

        this->_bChangeOptionsText = false;  //true jesli zmieniono parametr tekstu
		this->ButtAcceptAllOptionsText->Enabled = this->_bChangeOptionsText;
			}
		}
		break;
		//---
		case enPControl_ImageTools:

		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::PControlToolsMouseDown(TObject *Sender,
					TMouseButton Button, TShiftState Shift, int X, int Y)
/**
	OPIS METOD(FUNKCJI):Kliknięto na zakładki narżedzi
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  TPageControl *pPControl = dynamic_cast<TPageControl *>(Sender);
	if(!pPControl) return;
	//---
	this->SplitViewImageAndText->Opened = true;
	this->Act_ResizeWorkPanel->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::ButtAllClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):Zmiana tekstu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TButton *pButton = dynamic_cast<TButton *>(Sender);
	if(!pButton) return;
	//---
	GsDirect2DClass *pGsDirect2DClass = this->_GetDirect2DFromActiveSheet();
	if(pGsDirect2DClass)
	{
		switch(pButton->Tag)
		{
			case enTagAcceptText:
				pGsDirect2DClass->TextWrite = this->MemoImageAndText->Text;
				break;
			//---
			case enTagAcceptOptionsText:
				pGsDirect2DClass->StandartColorText = this->CBoxSelectColorText->Selected;
				pGsDirect2DClass->NameFont = this->CBoxSelectFont->Items->Strings[this->CBoxSelectFont->ItemIndex];
				pGsDirect2DClass->SizeFont = (float)this->CBoxSizeFont->Items->Strings[this->CBoxSizeFont->ItemIndex].ToDouble();
				pGsDirect2DClass->OpacityBrush = (float)((float)this->TrBarOpacityBrush->Position / 10.0f);

				this->_bChangeOptionsText = false;  //true jesli zmieniono parametr tekstu
				this->ButtAcceptAllOptionsText->Enabled = this->_bChangeOptionsText;
				break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::CBoxSelectColorTextGetColors(TCustomColorBox *Sender,
					TStrings *Items)
/**
	OPIS METOD(FUNKCJI):Dodanie kolorów do listy
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  Items->AddObject("clWebDarkOrange", (TObject *)clWebDarkOrange);
	Items->AddObject("clWebLinen", (TObject *)clWebLinen);
	Items->AddObject("clWebBurlywood", (TObject *)clWebBurlywood);
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::SelectChangeOptionsText(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):Zmiana parametrów tekstu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  #if defined(_DEBUGINFO_)
		GsDebugClass::WriteDebug(Format("this->_IsStart: %d", ARRAYOFCONST(((int)this->_IsStart))));
	#endif
	if(!this->_IsStart)
	{
		#if defined(_DEBUGINFO_)
			GsDebugClass::WriteDebug(Format("Sender: %s", ARRAYOFCONST((Sender->ClassName()))));
		#endif
		this->_bChangeOptionsText = true;  //true jesli zmieniono parametr tekstu
		this->ButtAcceptAllOptionsText->Enabled = this->_bChangeOptionsText;
	}
	else
  {
    this->_IsStart = false;
	}
}
//---------------------------------------------------------------------------

