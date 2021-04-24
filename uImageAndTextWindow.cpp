#include <vcl.h>
#pragma hdrstop

#include "uImageAndTextWindow.h"
#include "uGlobalVar.h"
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
				enIcon_CloseSheet, enIcon_SaveAs, enIcon_Save, enIcon_Text, enIcon_ResizeWorkPanel, enIcon_OnlyText,
				//Numery zakładek po lewej stronie
				enSheet_SelectImage=0, enSheet_ToolsImage,
				//Tagi objektów, klasy TPageControl
				enPControl_ImageTools=100, enPControl_ImageDisplay,
				//Tagi dla ikon
				enIconTag_CloseSheet=200, enIconTag_SaveAs, enIconTag_Save, enIconTag_Text, enIconTag_ResizeWorkPanel,
				//Tagi dla objektu, klasy TComboBox
				enTagCBox_ColorFont=300, enTagCBox_ColorFont2, enTagCBox_SelectFont, enTagCBox_SizeFont,
				//Tagi dla objektów, klasy TTrackBar
				enTagTrBar_Opacity=400, enTagTrBar_Rotation,
				//Tagi dla objektów, klasy TCheckBox
				enTagChBox_IsGradientColor=500,
				//Numery małych ikon
				enSmallIcon_ApplyText = 0, enSmallIcon_Effects
		 };
UnicodeString ustrCaptionShettNoText = "Tylko tekst";
//---------------------------------------------------------------------------
__fastcall TImageAndTextWindow::TImageAndTextWindow(TComponent* Owner, const UnicodeString ustrInput)
	: TForm(Owner), _ustrInputText(ustrInput)
/**
	OPIS METOD(FUNKCJI): Konstruktor klasy TImageAndTextWindow
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Stworzenie zawartości zakładki z multimediami
	this->_pGsPanelMultiM = new GsPanelMultiM(this->TabSheetSelectImages, this->PControlImageAndText);
	if(!this->_pGsPanelMultiM) throw(Exception("Błąd inicjalizacji objektu GsPanelMultiM"));
	this->_pGsPanelMultiM->Parent = this->TabSheetSelectImages;
	this->_pGsPanelMultiM->Align = alClient;

	this->PControlTools->ActivePageIndex = enSheet_SelectImage;

	this->_InitTagAndHint();
	//Interface ustawiania efektów
	this->LBoxSelectEffects->Items->BeginUpdate();
  for(UnicodeString ustr : ustrListNameEffects)
		{this->LBoxSelectEffects->Items->Add(ustr);}
	this->LBoxSelectEffects->ItemIndex = 0;
	this->LBoxSelectEffects->Items->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::FormShow(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsListViewMultiMClass *pGsListViewMultiMClass = this->_pGsPanelMultiM->GetGsListViewMultiMClass();
	if(!pGsListViewMultiMClass || pGsListViewMultiMClass->Items->Count==0) return;
  this->_pGsPanelMultiM->SetFocus(); //Bardzo ważne!!! 25-07-2020
	//---
	pGsListViewMultiMClass->ItemIndex = 0;

  //Inicjalizacja objektów, klasy TCombobox
	THashedStringList *pTHashedStringList = new THashedStringList();//this->_pGsPanelMultiM->GetFonstList();
	if(pTHashedStringList)
	{
		D2D_CreateFontsList(pTHashedStringList);
		this->CBoxSelectFont->Items->Assign(pTHashedStringList);
		this->CBoxSelectFont->Sorted = true;

		int iIndexFontName = this->CBoxSelectFont->Items->IndexOf(CFNameFont);
		this->CBoxSelectFont->ItemIndex = iIndexFontName;

    delete pTHashedStringList;
	}
  //---
	for(unsigned int i=0; i<ARRAYSIZE(ustrFontSize); i++)
	{
		this->CBoxSizeFont->AddItem(ustrFontSize[i], 0);
	}
	int iIndexFontSize = this->CBoxSizeFont->Items->IndexOf(UnicodeString((int)CFSizeFont));
	this->CBoxSizeFont->ItemIndex = iIndexFontSize;
	//---
	this->TrBarOpacityBrush->Max = CFOpacityBrush * 10;
	this->TrBarOpacityBrush->Position = this->TrBarOpacityBrush->Max;
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
	this->TrBarRotationText->Tag = enTagTrBar_Rotation;
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
	this->Act_OnlyText->Tag = enIcon_OnlyText;
	this->Act_OnlyText->Hint = Format("Wyswietlanie samego tekstu|Wyświetlany jest sam tekst, brak obrazka w formie podkładu.|%u", ARRAYOFCONST((this->Act_OnlyText->ImageIndex)));
	//Tagi dla objektu, klasy TComboBox
	this->CBoxSelectColorText->Tag = enTagCBox_ColorFont;
	this->CBoxSelectColorText2->Tag = enTagCBox_ColorFont2;
	this->CBoxSelectFont->Tag = enTagCBox_SelectFont;
	this->CBoxSizeFont->Tag = enTagCBox_SizeFont;
	//Tagi dla objektów, klasy TCheckBox
	this->ChBoxIsDoubleColor->Tag = enTagChBox_IsGradientColor;
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
		this->_SetupAllEnable(this->Act_CloseActiveSheet->Enabled);
	}
	//---
	if(this->PControlImageAndText->PageCount == 0)
	{
		this->CBoxSelectColorText->Selected = CFStandardColorText;
		this->ChBoxIsDoubleColor->Checked = false;
		this->CBoxSelectColorText2->Selected = this->CBoxSelectColorText->Selected;
    //Odczyt używanego kroju czcionki
		int iIndexFont = this->CBoxSelectFont->Items->IndexOf(CFNameFont);
		this->CBoxSelectFont->ItemIndex = iIndexFont;
		//Odczyt wielkośći czcionki
		int iIndexFontSize = this->CBoxSizeFont->Items->IndexOf(UnicodeString((int)CFSizeFont));
		this->CBoxSizeFont->ItemIndex = iIndexFontSize;
		this->TrBarOpacityBrush->Position = 0;
		this->TrBarRotationText->Position = 0;

		this->PControlTools->ActivePageIndex = enSheet_SelectImage;
		this->PControlTools->SetFocus(); //Bardzo wazne!!!
	}
	else
	{
		this->PControlImageAndTextChange(this->PControlImageAndText);
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
		GsDebugClass::WriteDebug("TImageAndTextWindow::PControlImageAndTextEnter()");
	#endif
	TPageControl *pPageControl = dynamic_cast<TPageControl *>(Sender);
	if(!pPageControl) return;
	//---
	//this->Act_CloseActiveSheet->Enabled = true;
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
			if(!this->_ustrInputText.IsEmpty())
			//Przy KAŻDEJ nowej zakładce wpisywany jest tekst, który był podany przy konstruktorze
			{
				pGsDirect2DClass->TextWrite = this->_ustrInputText;
			}
      #if defined(_DEBUGINFO_)
				GsDebugClass::WriteDebug(Format("IsLoadedImage: %d", ARRAYOFCONST(((int)pGsDirect2DClass->IsLoadedImage))));
			#endif
      //Uaktywnij panel efektów, tylko wtedy, gdy obrazek jest wczytany
			this->LBoxSelectEffects->Enabled = pGsDirect2DClass->IsLoadedImage;
			this->LBoxSelectEffects->ItemIndex = pGsDirect2DClass->SetApplyEffect - EfGfx_NoEffect; //Odczyt efektu na nowej zakładce
			//Wyświetlanie tekstu
			this->MemoImageAndText->Text = pGsDirect2DClass->TextWrite;
			this->ChBoxIsDoubleColor->Checked = pGsDirect2DClass->IsGradientColorFont;
			//Odczyt używanego kroju czcionki
			int iIndexFont = this->CBoxSelectFont->Items->IndexOf(pGsDirect2DClass->NameFont);
			this->CBoxSelectFont->ItemIndex = iIndexFont;
			//Odczyt używanego koloru
			this->CBoxSelectColorText->Selected = pGsDirect2DClass->StandartColorText;
			this->CBoxSelectColorText2->Selected = this->CBoxSelectColorText->Selected;
			//Odczyt wielkośći czcionki
			int iIndexFontSize = this->CBoxSizeFont->Items->IndexOf(UnicodeString((int)pGsDirect2DClass->SizeFont));
			this->CBoxSizeFont->ItemIndex = iIndexFontSize;
			//Odczyt przezroczystości
			this->TrBarOpacityBrush->Position = (int)(pGsDirect2DClass->OpacityBrush * 10.0);
			this->TrBarRotationText->Position = (int)pGsDirect2DClass->RotationText;
			this->_SetupAllEnable(this->Act_Text->Checked);
		}
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
				if(this->SplitViewImageAndText->CompactWidth == 0)
				{
					this->SplitViewImageAndText->CompactWidth = Rect.GetWidth();
				}
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
				this->Act_Text->Checked = pGsDirect2DClass->IsDisplayText;
				this->_SetupAllEnable(this->Act_Text->Checked);
				//Odczyt tekstu
				this->MemoImageAndText->Text = pGsDirect2DClass->TextWrite;
				//czy uzywane dwa kolory do cieniowania
				this->ChBoxIsDoubleColor->Checked = pGsDirect2DClass->IsGradientColorFont;
				//Odczyt używanego kroju czcionki
				int iIndexFont = this->CBoxSelectFont->Items->IndexOf(pGsDirect2DClass->NameFont);
				this->CBoxSelectFont->ItemIndex = iIndexFont;
				//Odczyt używanego koloru
				this->CBoxSelectColorText->Selected = pGsDirect2DClass->StandartColorText;
        this->CBoxSelectColorText2->Selected = pGsDirect2DClass->StandartColorText2;
				//Odczyt wielkośći czcionki
				int iIndexFontSize = this->CBoxSizeFont->Items->IndexOf(UnicodeString((int)pGsDirect2DClass->SizeFont));
				this->CBoxSizeFont->ItemIndex = iIndexFontSize;
				//Odczyt przezroczystości
				this->TrBarOpacityBrush->Position = (int)(pGsDirect2DClass->OpacityBrush * 10.0);
				//Odczyt obrotu
				this->TrBarRotationText->Position = (int)pGsDirect2DClass->RotationText;
        //Odczyt czy został wczytany obrazek, czy sam tekst
				this->LBoxSelectEffects->Enabled = pGsDirect2DClass->IsLoadedImage;
				this->LBoxSelectEffects->ItemIndex = pGsDirect2DClass->SetApplyEffect - EfGfx_NoEffect;
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
												//"Plik typu gif(*.gif)|*.GIF|" +
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
				if(this->PControlImageAndText->PageCount > 0)
				{
					GsDirect2DClass *pGsDirect2DClass = this->_GetDirect2DFromActiveSheet();
					if(pGsDirect2DClass)
					{
						pGsDirect2DClass->GsD2D_SavePicture(ustrPathSaveFile);
						//pGsDirect2DClass->GsD2D_SavePictureOriginal(ustrPathSaveFile);
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
		if(pSaveDialog) {delete pSaveDialog; pSaveDialog = nullptr;}
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
		//if(pAction->Checked)
		this->MemoImageAndText->Text = pGsDirect2DClass->TextWrite;
    this->ChBoxIsDoubleColor->Checked = pGsDirect2DClass->IsGradientColorFont;

		this->_SetupAllEnable(pAction->Checked);

		if(pAction->Checked)
		{
			this->SplitViewImageAndText->Opened = true;
			this->PControlTools->ActivePageIndex = enSheet_ToolsImage;
			this->PControlTools->SetFocus(); //Bardzo wazne!!!
		}
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
void __fastcall TImageAndTextWindow::Act_OnlyTextExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):Wyswietlanie i operacje na samym tekście, zaden obrazek nie jest wyswietlany
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
  this->PControlTools->SetFocus(); //Bardzo wazne!!!
	//---
	GsTabSheetGraphics *pGsTabSheetGraphics = this->_pGsPanelMultiM->NewSheetOnlyText();
	if(pGsTabSheetGraphics)
	{
		pGsTabSheetGraphics->Caption = ustrCaptionShettNoText;
		this->Act_Text->Checked = true;
		this->Act_TextExecute(this->Act_Text);
  }
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::MemoImageAndTextChange(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):Zmiana tekstu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TMemo *pMemo = dynamic_cast<TMemo *>(Sender);
	if(!pMemo) return;
	//---
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::ButtDisplayNewTextClick(TObject *Sender)
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
		pGsDirect2DClass->TextWrite = this->MemoImageAndText->Text;
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
void __fastcall TImageAndTextWindow::CBoxAllSelect(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):Dodanie kolorów do listy
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsDirect2DClass *pGsDirect2DClass =  this->_GetDirect2DFromActiveSheet();
	if(!pGsDirect2DClass) return;
	//---
	if(Sender->ClassNameIs("TColorBox"))
	{
		TColorBox *pColorBox = dynamic_cast<TColorBox *>(Sender);
		if(!pColorBox) return;
		//---
		switch(pColorBox->Tag)
		{
			case enTagCBox_ColorFont:
				pGsDirect2DClass->StandartColorText = pColorBox->Selected;
				this->CBoxSelectColorText2->Selected = pColorBox->Selected;
			break;
			//---
			case enTagCBox_ColorFont2:
				pGsDirect2DClass->StandartColorText2 = pColorBox->Selected;
			break;
		}
	}
	else if(Sender->ClassNameIs("TComboBox"))
	{
		TComboBox *pCBox = dynamic_cast<TComboBox *>(Sender);
		if(!pCBox) return;
		//---
		switch(pCBox->Tag)
		{
			case enTagCBox_SelectFont:
				pGsDirect2DClass->NameFont = pCBox->Items->Strings[pCBox->ItemIndex];
			break;
			//---
			case enTagCBox_SizeFont:
				pGsDirect2DClass->SizeFont = (float)pCBox->Items->Strings[pCBox->ItemIndex].ToDouble();
      break;
    }
	}
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::TrBarAllChange(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TTrackBar *pTrBar = dynamic_cast<TTrackBar *>(Sender);
	if(!pTrBar) return;
	//---
	GsDirect2DClass *pGsDirect2DClass =  this->_GetDirect2DFromActiveSheet();
	if(!pGsDirect2DClass) return;
	//---
	switch(pTrBar->Tag)
	{
		case enTagTrBar_Opacity:
			pGsDirect2DClass->OpacityBrush = (float)((float)pTrBar->Position / 10.0f);
		break;
		//---
		case enTagTrBar_Rotation:
      pGsDirect2DClass->RotationText = (float)pTrBar->Position;
    break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::_SetupAllEnable(const bool _bEnable)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  GsDirect2DClass *pGsDirect2DClass =  this->_GetDirect2DFromActiveSheet();
	if(!pGsDirect2DClass) return;
	//---
	//Na wybranej zakładce, jest uaktywnione wyświetlanie tekstu na grafice, lub nie
	//Objekty aktywne, zależnie od tego czy na zakładce jest object z załączoną flaga wyswietlania tekstu
	this->MemoImageAndText->Enabled = _bEnable;
	this->ChBoxIsDoubleColor->Enabled = _bEnable;
	this->ButtDisplayNewText->Enabled = _bEnable;
	this->CBoxSelectColorText->Enabled = _bEnable;
	this->CBoxSelectFont->Enabled = _bEnable;
	this->CBoxSizeFont->Enabled = _bEnable;
	this->TrBarOpacityBrush->Enabled = _bEnable;

	this->LabelColorText->Enabled = _bEnable;
	this->LabelNameFont->Enabled = _bEnable;
	this->LabelSizeFont->Enabled = _bEnable;
	this->LabelSetOpacityBrush->Enabled = _bEnable;
	this->LabelRotationText->Enabled = _bEnable;
	this->TrBarOpacityBrush->Enabled = _bEnable;
	this->TrBarRotationText->Enabled = _bEnable;

	this->LabelColorText2->Enabled = _bEnable && this->ChBoxIsDoubleColor->Checked;
	this->CBoxSelectColorText2->Enabled = _bEnable && this->ChBoxIsDoubleColor->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::ChBoxAllClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsDirect2DClass *pGsDirect2DClass =  this->_GetDirect2DFromActiveSheet();
	if(!pGsDirect2DClass) return;
	//---
	TCheckBox *pChBox = dynamic_cast<TCheckBox *>(Sender);
	if(!pChBox) return;
	//---
	switch(pChBox->Tag)
	{
		case enTagChBox_IsGradientColor:
			pGsDirect2DClass->IsGradientColorFont = pChBox->Checked;

			this->LabelColorText2->Enabled = pChBox->Checked;;
			this->CBoxSelectColorText2->Enabled = pChBox->Checked;
			pGsDirect2DClass->StandartColorText2 = this->CBoxSelectColorText2->Selected;
		break;
		//---
  }
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::SplitViewImageAndTextOpened(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TSplitView *pSView = dynamic_cast<TSplitView *>(Sender);
	if(!pSView) return;
	//---
	this->_pGsPanelMultiM->RefreshListView();
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::LBoxSelectEffectsClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListBox *pLBox = dynamic_cast<TListBox *>(Sender);
	if(!pLBox) return;
	//---
	if(pLBox->ItemIndex == -1) return;
  //---
	GsDirect2DClass *pGsDirect2DClass = this->_GetDirect2DFromActiveSheet();
	if(pGsDirect2DClass)
	{
		EnEffectsGfx _EnEffectsGfx = static_cast<EnEffectsGfx>(EfGfx_NoEffect + pLBox->ItemIndex);

		if((!GlobalVar::IsWindows10) && (_EnEffectsGfx > EfGfx_Brightness)) //23-08-2020
		{
			MessageBox(NULL, TEXT("Aktualnie wybrany efekt wymaga minimum Windows 10!"), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
			return;
		}

		pGsDirect2DClass->SetApplyEffect = _EnEffectsGfx;
	}
}
//---------------------------------------------------------------------------
void __fastcall TImageAndTextWindow::LBoxSelectEffectsDrawItem(TWinControl *Control,
					int Index, TRect &Rect, TOwnerDrawState State)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListBox *pLBox = dynamic_cast<TListBox *>(Control);
	if(!pLBox) return;
	//---
	TRect MyRect = Rect;
	int iHeight = MyRect.Bottom - MyRect.Top;
	TCanvas *pCanvas = pLBox->Canvas;
	//---
	if(Index > (EfGfx_Brightness - EfGfx_NoEffect))
		{pCanvas->Font->Color = clRed;}
  else
		{pCanvas->Font->Color = pLBox->Font->Color;}

	if(State.Contains(odSelected))
	{
		pCanvas->Brush->Color = clYellow;
	}

	pCanvas->FillRect(MyRect);
	this->ImageListSmallImageAndText->Draw(pCanvas, 2, MyRect.Top + ((iHeight / 2) - (this->ImageListSmallImageAndText->Height / 2)), enSmallIcon_Effects);
	MyRect.Left += (4 + this->ImageListSmallImageAndText->Width);

	DrawText(pCanvas->Handle, pLBox->Items->Strings[Index].c_str(), -1, &MyRect, DT_SINGLELINE | DT_VCENTER);
}
//---------------------------------------------------------------------------

