﻿#pragma hdrstop

#include "GsEditorClass.h"
#include <Vcl.Dialogs.hpp>
#include <System.IOUtils.hpp>
#include "GsEditorDataImages.h" //Dane dla grafiki (Pojedyńcch obrazów i list obrazów)
#include <Vcl.Printers.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif

#if defined(_WIN64)
#else
#endif
*/
enum {
				EnImage_Save,			//0-0.Zapis pod tą samą nazwą
				EnImage_SaveAs,		//1-1.Zapis pod zmienioną nazwą
				EnImage_Open,			//2-2.Otwórz
				EnImage_Print,		//3-3.Drukuj
				EnImage_Clear,		//4-4.Wyczyść
				EnImage_Sep,			//5.Separator
				EnImage_Copy,			//6-5.Kopiuj
				EnImage_Cut,			//7-6.Wytnij
				EnImage_Insert,		//8-7.Wstaw
				EnImage_Sep1,			//9.Separator
				EnImage_Find,			//10-8.Szukaj
				EnImage_FindReplace,//11-9.Szukaj i podmień
				EnImage_Sep2,			//12.Separator
				EnImage_Undo,			//13-10.Cofnij
				EnImage_Redo,			//14-11.Wróć
				EnImage_Sep3,			//15.Separator
				EnTag_FontName,		//16.Nazwa czcionki
				EnTag_FontSize,		//17.Wielkość czcionki
				EnImage_Bold,			//18-12.Pogrubienie
				EnImage_Italic,		//19-13.Pochylona
				EnImage_Underline,//20-14.Podkreślona
				EnImage_StrikeOut,//21-15
				EnImage_Sep4,			//22.Separator
				EnImage_FontColour,//23
				EnImage_FontBackgroundColour,//24
				EnImage_Sep5,			//25.Separator
				EnImage_LeftAl,		//26-16.Dosunięcie tekstu do lewego marginesu
				EnImage_CentreAl, //27-17.Dosunięcie tekstu d centrum
				EnImage_RightAl,	//28-18.Dosunięcie tekstu do prawego marginesu
				EnImage_Sep6,			//29.Separator
				EnImage_Paragraph,//30-19.Punktowanie
				//---
				EnImage_Count
		 };
enum {EnPanel_FileInfo, EnPanel_Info, EnPanel_Count};
const UnicodeString custrSep = "SEP", //Nazwa domyślna separatora
										//Nazwy przycislów
										ustrHintButtons[] = {"Zapisz", "Zapisz jako...", "Otwórz...", "Drukuj zawartość...", "Wyczyść", custrSep, "Kopiuj", "Wytnij", "Wstaw",
																				 custrSep, "Szukaj...", "Szukaj i podmień...", custrSep, "Cofnij", "Powróć", custrSep,
																				 "Nazwa czcionki", "Wielkość czcionki", "Pogrubiona", "Pochylona", "Podkreślona", "Przekreślona",
																				 custrSep, "Kolor czcionki", "Kolor podkładu czcionki", custrSep, "Dosunięcie do lewej",
																				 "Wycentrowanie", "Dosunięcie do prawej", custrSep, "Punktowanie"},
										//Nazwy czcionek
										ustrNameFont[] = {"Arial", "Tahoma", "Verdana", "Times New Roman", "Courier New", "DejaVu Sans"},
										//Wielkości czcionek
										ustrSizeFont[] = {"8", "9", "10", "11", "12", "14", "16", "18", "20", "24", "28"};
enum {EnSizeFont_8, EnSizeFont_9, EnSizeFont_10, EnSizeFont_11, EnSizeFont_12, EnSizeFont_14,
			EnSizeFont_16, EnSizeFont_18, EnSizeFont_20, EnSizeFont_24, EnSizeFont_28, EnSizeFont_Count};

__fastcall GsEditorClass::GsEditorClass(TComponent* Owner) : TCustomPanel(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->pTImageListActive = new TImageList(this);
	if(!this->pTImageListActive) throw(Exception("Nie dokonano inicjalizacji objektu TImageList"));
	this->Font->Quality = TFontQuality::fqClearType;
	this->ParentFont = true;
	this->pTImageListActive->ColorDepth = cd32Bit;		 //Głębia kolorów przyszłych obrazków
	this->pTImageListActive->DrawingStyle = dsTransparent;
		//
	this->pTImageListInActive = new TImageList(this);
	if(!this->pTImageListInActive) throw(Exception("Nie dokonano inicjalizacji objektu TImageList"));
	this->pTImageListInActive->ColorDepth = cd32Bit;		 //Głębia kolorów przyszłych obrazków
	this->pTImageListInActive->DrawingStyle = dsTransparent;
	this->_InitImageList();
	//---
	this->pBalloonHint = new TBalloonHint(this);
	if(!this->pBalloonHint) throw(Exception("Nie dokonano inicjalizacji objektu TBalloonHint"));
	this->pBalloonHint->Images = this->pTImageListActive;
	//---
	this->pSBar = new TStatusBar(this);
	if(!this->pSBar) throw(Exception("Nie dokonano inicjalizacji objektu TStatusBar"));
	this->pSBar->Parent = this;
	this->pSBar->ParentFont = true;
	this->pSBar->ShowHint = true;
	this->pSBar->Hint = "Informacje";
	this->pSBar->Font->Quality = TFontQuality::fqClearType;
	//---
	this->pTRichEdit = new TRichEdit(this);
	if(!this->pTRichEdit) throw(Exception("Nie dokonano inicjalizacji objektu TRichEdit"));
	this->pTRichEdit->Parent = this;
	this->pTRichEdit->ParentFont = true;
	this->pTRichEdit->Align = alClient;
	this->pTRichEdit->Font->Quality = TFontQuality::fqClearType;
	this->pTRichEdit->StyleElements = TStyleElements();
	//Zależność suwaka przewijania, od atrybutu WordWrap
	if (this->pTRichEdit->WordWrap) this->pTRichEdit->ScrollBars = ssVertical; //Suwak tylko pionowy
	else this->pTRichEdit->ScrollBars = ssBoth; //Suwak pionowy i poziomy
	//---
	//this->pTRichEdit->ScrollBars = ssBoth;
	this->pTRichEdit->OnSelectionChange = this->_OnSelectionChangeEdit;
	this->pTRichEdit->OnChange = this->_OnChangeEdit;
	//Wartości domyślne prywatnych danych
	this->FEditorFileName = "";
	//this->FIsVisibleAllIOButtons = true;
	//Dostosowanie flg przycisków, do flagi widoczności przyciskó IO
	this->FDisplaySelectIOButtons = DisplaySelectIOButtons();
	if(this->FIsVisibleAllIOButtons) this->FDisplaySelectIOButtons = DisplaySelectIOButtons() << enSetButton_Save << enSetButton_SaveAs << enSetButton_Open;
}
//---------------------------------------------------------------------------
__fastcall GsEditorClass::~GsEditorClass()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
void __fastcall GsEditorClass::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCustomPanel::CreateWnd();
	//Własny kod.
	this->_InitInterface();
	//Ustawienie marginesów po lewej i prawej stronie
	TRect RichRect = this->pTRichEdit->ClientRect;	//Obszar klienta
	RichRect.Inflate(-15, -15);
	this->pTRichEdit->Perform(EM_SETRECT, 0, RichRect);
	this->pTRichEdit->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall GsEditorClass::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	TCustomPanel::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsEditorClass::ClearEditor()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->pTRichEdit->Clear();
	//Ustawienia innych przycisków w stan nieaktywny
	this->pTRichEdit->Modified = false;
	this->pTButtUndo->Enabled = this->pTRichEdit->Modified;
	this->pSBar->Panels->Items[EnPanel_Info]->Text = "Plik niezmodyfikowany";
	this->pTButtSave->Enabled = false;
	this->pTButtInsert->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall GsEditorClass::_InitInterface()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TLabel *pLabel;//=0;
	//---
	this->pToolBar = new TToolBar(this);
	if(!this->pToolBar) throw(Exception("Błąd inicjalizacji klasy TToolBar"));

	this->pToolBar->Parent = this;
	this->pToolBar->AutoSize = true;
	//this->pToolBar->Height = 12;
	this->pToolBar->Flat = true;
	//this->pToolBar->StyleElements = TStyleElements();
	this->pToolBar->DrawingStyle = (Vcl::Comctrls::TTBDrawingStyle)Vcl::Comctrls::gdoGradient;
	this->pToolBar->Images = this->pTImageListActive;
	this->pToolBar->DisabledImages = this->pTImageListInActive;
	this->pToolBar->ShowHint = true;
	this->pToolBar->CustomHint = this->pBalloonHint;
	//Dodawanie przycisków na toolbar
	int cor=11; //Ilość separatorów i objektów, klasy innej niż TToolButton
	for(int i=EnImage_Count-1; i>=0; i--)
	{
		if(i == EnTag_FontName) //Nazwa czcionki
		{
			this->pCBoxSelectFontName = new TComboBox(this->pToolBar);
			if(!this->pCBoxSelectFontName) throw(Exception("Błąd inicjalizacji klasy TComboBox"));
			this->pCBoxSelectFontName->Parent = this->pToolBar;
			this->pCBoxSelectFontName->Hint = ustrHintButtons[i];
			this->pCBoxSelectFontName->Tag = i;
			this->pCBoxSelectFontName->Style = csDropDownList;
			this->pCBoxSelectFontName->OnChange = this->_OnChangeCBox;
			for(unsigned int iLicz=0; iLicz<ARRAYSIZE(ustrNameFont); ++iLicz)
			{
				this->pCBoxSelectFontName->Items->Add(ustrNameFont[iLicz]);
			}
			this->pCBoxSelectFontName->ItemIndex = 0;
			//---
			pLabel = new TLabel(this->pToolBar);
			if(!pLabel) throw(Exception("Błąd inicjalizacji klasy TLabel"));
			pLabel->Parent = this->pToolBar;
			pLabel->Caption = ustrHintButtons[EnTag_FontName];
			//pLabel->StyleElements = TStyleElements();
			pLabel->Layout = tlCenter;
			pLabel->Alignment = taCenter;
			pLabel->Width = this->pToolBar->Canvas->TextWidth(ustrHintButtons[EnTag_FontName]) + 12;
			pLabel->Hint = ustrHintButtons[EnTag_FontName];
			//pLabel->Transparent = false;
			cor--;
			continue;
		}
		if(i == EnTag_FontSize) //Wielkość czcionki
		{
			this->pCBoxSelectFontSize = new TComboBox(this->pToolBar);
			if(!this->pCBoxSelectFontSize) throw(Exception("Błąd inicjalizacji klasy TComboBox"));
			this->pCBoxSelectFontSize->Parent = this->pToolBar;
			this->pCBoxSelectFontSize->Width = 42;
			this->pCBoxSelectFontSize->Hint = ustrHintButtons[i];
			this->pCBoxSelectFontSize->Tag = i;
			this->pCBoxSelectFontSize->Style = csDropDownList;
			this->pCBoxSelectFontSize->OnChange = this->_OnChangeCBox;
			for(unsigned int iLicz=0; iLicz<ARRAYSIZE(ustrSizeFont); ++iLicz)
			{
				this->pCBoxSelectFontSize->Items->Add(ustrSizeFont[iLicz]);
			}
			this->pCBoxSelectFontSize->ItemIndex = EnSizeFont_12;
			//---
			pLabel = new TLabel(this->pToolBar);
			if(!pLabel) throw(Exception("Błąd inicjalizacji klasy TLabel"));
			pLabel->Parent = this->pToolBar;
			pLabel->Caption = ustrHintButtons[EnTag_FontSize];
			pLabel->Layout = tlCenter;
			pLabel->Alignment = taCenter;
			pLabel->Width = this->pToolBar->Canvas->TextWidth(ustrHintButtons[EnTag_FontSize]) + 12;
			pLabel->Hint = ustrHintButtons[EnTag_FontSize];
			//pLabel->Transparent = false;
			cor--;
			continue;
		}
		if(i == EnImage_FontColour)
		{
			this->pColBoxFont = new TColorBox(this->pToolBar);
			if(!this->pColBoxFont) throw(Exception("Błąd inicjalizacji klasy TColorBox"));
			this->pColBoxFont->Parent = this->pToolBar;
			this->pColBoxFont->Style = TColorBoxStyle() << cbStandardColors << cbExtendedColors << cbPrettyNames;
			this->pColBoxFont->Hint = ustrHintButtons[EnImage_FontColour];
			this->pColBoxFont->Tag = i;
			this->pColBoxFont->OnChange = this->_OnChangeColor;
			//---
			pLabel = new TLabel(this->pToolBar);
			if(!pLabel) throw(Exception("Błąd inicjalizacji klasy TLabel"));
			pLabel->Parent = this->pToolBar;
			pLabel->Caption = ustrHintButtons[EnImage_FontColour];
			pLabel->Layout = tlCenter;
			pLabel->Alignment = taCenter;
			pLabel->Width = this->pToolBar->Canvas->TextWidth(ustrHintButtons[EnImage_FontColour]) + 12;
			pLabel->Hint = ustrHintButtons[EnImage_FontColour];
			//pLabel->Transparent = false;
			cor--;
			continue;
		}
		if(i == EnImage_FontBackgroundColour)
		{
			this->pColBoxBackground = new TColorBox(this->pToolBar);
			if(!this->pColBoxBackground) throw(Exception("Błąd inicjalizacji klasy TColorBox"));
			this->pColBoxBackground->Parent = this->pToolBar;
			this->pColBoxBackground->Style = TColorBoxStyle() << cbStandardColors << cbExtendedColors << cbPrettyNames;
			//this->pColBoxBackground->CustomHint = this->pBalloonHint;
			this->pColBoxBackground->Hint = ustrHintButtons[EnImage_FontBackgroundColour];
			this->pColBoxBackground->Tag = i;
			this->pColBoxBackground->OnChange = this->_OnChangeColor;
			//---
			pLabel = new TLabel(this->pToolBar);
			if(!pLabel) throw(Exception("Błąd inicjalizacji klasy TLabel"));
			pLabel->Parent = this->pToolBar;
			pLabel->Caption = ustrHintButtons[EnImage_FontBackgroundColour];
			pLabel->Layout = tlCenter;
			pLabel->Alignment = taCenter;
			pLabel->Width = this->pToolBar->Canvas->TextWidth(ustrHintButtons[EnImage_FontBackgroundColour]) + 12;
			pLabel->Hint = ustrHintButtons[EnImage_FontBackgroundColour];
			//pLabel->Transparent = false;
			cor--;
			continue;
		}
		TToolButton *pToolButton = new TToolButton(this->pToolBar);
		if(!pToolButton) throw(Exception("Błąd inicjalizacji klasy TToolButton"));
		pToolButton->Parent = this->pToolBar;
		if(ustrHintButtons[i] == custrSep) //Separator
		{
			pToolButton->Style = tbsSeparator;
			pToolButton->Width = 8;
			cor--;
			continue;
		}
		pToolButton->ImageIndex = i-cor;
		pToolButton->Hint = ustrHintButtons[i];
		pToolButton->OnClick = this->_OnClickTButt;
		pToolButton->Tag = 10 * (i+1);
		if(((i >= EnImage_Bold) && (i <= EnImage_StrikeOut)) ||
			 ((i >= EnImage_LeftAl) && (i <= EnImage_RightAl)))
		//Przyciski nie powracające ze stanu wciśnięcia
		{
			pToolButton->Style = tbsCheck;
			if((i >= EnImage_LeftAl) && (i <= EnImage_RightAl))
			//Przyciski, należące do grupu, gdzie może być wciśnięty tylko jeden przycisk
			{
				pToolButton->AllowAllUp = true;
				pToolButton->Grouped = true;
			}
		}
		//--- Przyciski IO
		if(i == EnImage_Save)
		//Niema jeszcze nazwy
		{
			this->pTButtSave = pToolButton; //Zapis pod tą samą nazwą
			this->pTButtSave->Enabled = false;
			this->pTButtSave->Visible = this->IsVisibleAllIOButton && this->FDisplaySelectIOButtons.Contains(enSetButton_Save);
			this->pTButtSave->Hint = Format("Zapis pod tą samą nazwą|Zapis zawartości edytora pod nazwą, pod którą została wczytana.|%u", ARRAYOFCONST((this->pTButtSave->ImageIndex)));
		}
		if(i == EnImage_SaveAs)
		{
			this->pTButtSaveAs = pToolButton;	 //Zapis pod zmienioną nazwą
			this->pTButtSaveAs->Visible = this->IsVisibleAllIOButton && this->FDisplaySelectIOButtons.Contains(enSetButton_SaveAs);
			this->pTButtSaveAs->Hint = Format("Zapis pod tą wybraną nazwą|Zapis zawartości edytora pod nową nazwą, którą można wybrać.|%u", ARRAYOFCONST((this->pTButtSaveAs->ImageIndex)));
		}
		if(i == EnImage_Open)
		{
			this->pTButtLoad = pToolButton;		 //Otwórz
			this->pTButtLoad->Visible = this->IsVisibleAllIOButton && this->FDisplaySelectIOButtons.Contains(enSetButton_Open);
			this->pTButtLoad->Hint = Format("Wczytanie danych z pliku|Wczytanie zawartości wybranego pliku.|%u", ARRAYOFCONST((this->pTButtLoad->ImageIndex)));
		}
		if(i == EnImage_Print) pToolButton->Hint = Format("Wydrukuj|Wydrukowanie całego tekstu w edytorze.|%u", ARRAYOFCONST((pToolButton->ImageIndex)));
		//---
		if(i == EnImage_Copy)	pToolButton->Hint = Format("Skopiuj|Skopiowanie zaznaczonego tekstu.|%u", ARRAYOFCONST((pToolButton->ImageIndex)));
		if(i == EnImage_Cut) pToolButton->Hint = Format("Wytnij|Wycięcie zaznaczonego tekstu.|%u", ARRAYOFCONST((pToolButton->ImageIndex)));
		if(i == EnImage_Insert)
		{
			this->pTButtInsert = pToolButton; //Tryb wstawiania na początku wyłączony
			this->pTButtInsert->Enabled = false;
			this->pTButtInsert->Hint = Format("Wstaw tekst|Wstawienie poprzednio skopiowanego tekstu w miejsce kursora.|%u", ARRAYOFCONST((this->pTButtInsert->ImageIndex)));
		}
		if(i == EnImage_Find) pToolButton->Hint = Format("Wyszukaj|Wyszukiwanie wybranej frazy, we wczytanym tekscie.|%u", ARRAYOFCONST((pToolButton->ImageIndex)));
		if(i == EnImage_FindReplace) pToolButton->Hint = Format("Wyszukaj i podmień|Wyszukiwanie i zamiana wybranej frazy, na nową fraze, we wczytanym tekscie.|%u", ARRAYOFCONST((pToolButton->ImageIndex)));
		//Przyciski Undo, Redo
		if(i == EnImage_Undo)
		{
			this->pTButtUndo = pToolButton; //Cofnij
			this->pTButtUndo->Enabled = false;
			this->pTButtUndo->Hint = Format("Cofnij|Cofanie do ostatniej zawartości edytora.|%u", ARRAYOFCONST((this->pTButtUndo->ImageIndex)));
		}
		if(i == EnImage_Redo) //Wróć
		{
			this->pTButtRedo = pToolButton;
			this->pTButtRedo->Enabled = false;
			this->pTButtRedo->Hint = Format("Wróć|Rezygnacja z operacji wycofania.|%u", ARRAYOFCONST((this->pTButtRedo->ImageIndex)));
		}
		//Przyciski atrybutów tekstu
		if(i == EnImage_Bold)
		{
			this->pTButtBold = pToolButton; //Pogrubienie
			this->pTButtBold->Hint = Format("Pogrubienie|Pogrubienie zaznaczonego tekstu.|%u", ARRAYOFCONST((this->pTButtBold->ImageIndex)));
		}
		if(i == EnImage_Italic)
		{
			this->pTButtItalic = pToolButton;		//Pochylona
			this->pTButtItalic->Hint = Format("Pochylenie|Pochylenie zaznaczonego tekstu.|%u", ARRAYOFCONST((this->pTButtItalic->ImageIndex)));
		}
		if(i == EnImage_Underline)
		{
			this->pTButtUnderline = pToolButton;//Podkreślona
			this->pTButtUnderline->Hint = Format("Podkreślenie|Podkreślenie zaznaczonego tekstu.|%u", ARRAYOFCONST((this->pTButtUnderline->ImageIndex)));
		}
		if(i == EnImage_StrikeOut)
		{
			this->pTButtStrikeOut = pToolButton;//Przekreślona
			this->pTButtStrikeOut->Hint = Format("Przekreślenie|Przekreślenie zaznaczonego tekstu.|%u", ARRAYOFCONST((this->pTButtStrikeOut->ImageIndex)));
		}
		//Przyciski formatowania tekstu
		if(i == EnImage_LeftAl)
		{
			this->pTButtLeft = pToolButton; //Dosunięcie tekstu do lewego marginesu
			this->pTButtLeft->Hint = Format("Do lewego marginesu|Dosunięcie tekstu do lewego marginesu.|%u", ARRAYOFCONST((this->pTButtLeft->ImageIndex)));
		}
		if(i == EnImage_CentreAl)
		{
			this->pTButtCenter = pToolButton; //Dosunięcie tekstu do centrum
			this->pTButtCenter->Hint = Format("Do środka|Dosunięcie tekstu do środka.|%u", ARRAYOFCONST((this->pTButtCenter->ImageIndex)));
		}
		if(i == EnImage_RightAl)
		{
			this->pTButtRight = pToolButton;	 //Dosunięcie tekstu do prawego marginesu
			this->pTButtRight->Hint = Format("Do prawego marginesu|Dosunięcie tekstu do prawego marginesu.|%u", ARRAYOFCONST((this->pTButtRight->ImageIndex)));
		}
		//Paragraf
		if(i == EnImage_Paragraph)
		{
			this->pTButtParagraf = pToolButton; //Paragraf
			pToolButton->Style = tbsCheck;
			this->pTButtParagraf->Hint = Format("Wypunktowanie|Wstawienie wypunktowania tekstu.|%u", ARRAYOFCONST((this->pTButtParagraf->ImageIndex)));
		}
		//Skasowanie zawartości //[27-10-2023]
		if(i == EnImage_Clear)
		{
			this->pTButtClear = pToolButton;
			this->pTButtClear->Hint = Format("Skasuj|Skasowanie zawartości edytora.|%u", ARRAYOFCONST((this->pTButtClear->ImageIndex)));
		}
	}
	//Panele
	for(int i=0; i<EnPanel_Count; ++i)
	{
		TStatusPanel *Panel = this->pSBar->Panels->Add();
		if(i==EnPanel_FileInfo) Panel->Width = (float)this->Parent->Width * 0.66;
		else Panel->Width = (float)this->Parent->Width * 0.33;
	}
	this->pSBar->Panels->Items[EnPanel_Info]->Text = "Plik niezmodyfikowany";
	//this->pTRichEdit->SelAttributes->Name = this->pCBoxSelectFontName->Text;
	//this->pTRichEdit->SelAttributes->Size = StrToIntDef(this->pCBoxSelectFontSize->Items->Strings[this->pCBoxSelectFontSize->ItemIndex], 8);
	this->pTRichEdit->Font->Size = this->pCBoxSelectFontSize->Text.ToIntDef(12);
	this->pTRichEdit->Font->Name = "Arial";
	this->pTRichEdit->Font->Color = clBlack;
	this->pTRichEdit->Color = clWhite;
	this->pColBoxFont->Selected = this->pTRichEdit->SelAttributes->Color;
	this->pColBoxBackground->Selected = (TColor)-1;//this->pTRichEdit->Color;
}
//---------------------------------------------------------------------------
void __fastcall GsEditorClass::FSetupVisibleAllIOButtons(bool _IsVisibleIOButtons)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->pTButtSaveAs) //Bardzo ważne!!!
	{
		//Przyciski zapisu, zapisu jako, ładowania będą widoczne, lub nie, czyli trzech pierwszych przycisków po lewej stronie
		this->pTButtSave->Visible = _IsVisibleIOButtons;
		this->pTButtSaveAs->Visible = _IsVisibleIOButtons;
		this->pTButtLoad->Visible = _IsVisibleIOButtons;
		//Ustawienie przycisków IO
		this->FDisplaySelectIOButtons.Clear();
		if(_IsVisibleIOButtons) this->FDisplaySelectIOButtons = DisplaySelectIOButtons() << enSetButton_Save << enSetButton_SaveAs << enSetButton_Open;
	}
	//Ustawienie prywatnej danej
	this->FIsVisibleAllIOButtons = _IsVisibleIOButtons;
}
//---------------------------------------------------------------------------
void __fastcall GsEditorClass::LoadEditorFromFile(const UnicodeString _ustrInFilePath)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(TFile::Exists(_ustrInFilePath))
	{
		this->pTRichEdit->Lines->LoadFromFile(_ustrInFilePath);
	}
	this->FEditorFileName = _ustrInFilePath; //Zapamiętanie pliku wczytanego, lub nowego
	this->pTButtSave->Enabled = false; //Plik dopiero co wczytany, więc niema możliwości zapisu
	this->pSBar->Panels->Items[EnPanel_FileInfo]->Text = Format("Aktualny plik: \"%s\"", ARRAYOFCONST((_ustrInFilePath)));
	this->pTRichEdit->Modified = false;
	this->pTButtUndo->Enabled = this->pTRichEdit->Modified;
	this->pSBar->Panels->Items[EnPanel_Info]->Text = "Plik niezmodyfikowany";
	this->pTRichEdit->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall GsEditorClass::FSetupDisplaySelectIOButtons(const DisplaySelectIOButtons _SetDisplayButtons)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->pTButtSave->Visible = this->FIsVisibleAllIOButtons && _SetDisplayButtons.Contains(enSetButton_Save);
	this->pTButtSaveAs->Visible = this->FIsVisibleAllIOButtons && _SetDisplayButtons.Contains(enSetButton_SaveAs);
	this->pTButtLoad->Visible = this->FIsVisibleAllIOButtons && _SetDisplayButtons.Contains(enSetButton_Open);
	this->FDisplaySelectIOButtons = _SetDisplayButtons;
}
//---------------------------------------------------------------------------
void __fastcall GsEditorClass::LoadEditorFromStream(TStream* Stream)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

	this->pTRichEdit->Lines->LoadFromStream(Stream);
	this->pTRichEdit->Modified = false;
	this->pSBar->Panels->Items[EnPanel_Info]->Text = "Plik niezmodyfikowany";
	this->pTButtSave->Enabled = false;
	this->pTRichEdit->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall GsEditorClass::SaveEditorToFile(const UnicodeString _ustrInFilePath)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->pTRichEdit->Text.IsEmpty()) return;
	this->pTRichEdit->Lines->SaveToFile(_ustrInFilePath);
	this->pTButtSave->Enabled = false; //Plik dopiero co wczytany, więc niema możliwości zapisu
	this->pTRichEdit->Modified = false;
	this->pTButtUndo->Enabled = this->pTRichEdit->Modified;
	this->pSBar->Panels->Items[EnPanel_Info]->Text = "Plik niezmodyfikowany";
	this->pTRichEdit->SetFocus();
	//Jeśli istnieje zewnętrzna metoda OnSave() to ją wywołaj
	if(this->FOnSave) this->FOnSave(this);
}
//---------------------------------------------------------------------------
void __fastcall GsEditorClass::_OnClickTButt(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI): Przyciski
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TToolButton *pTButt = dynamic_cast<TToolButton *>(Sender);
	if(!pTButt) return;
	const UnicodeString ustrFileTypes[] = {"Pliki typy rtf", "*.rtf",
																				 "Każdy plik", "*.*"};
	//---
	int iTag = pTButt->Tag / 10 - 1;
	const UnicodeString ustrFileFilter = "Pliki typu rtf(*.rtf)|*.RTF|Każdy plik (*.*)|*.*";
	//---
	switch(iTag)
	{
		case EnImage_Save:		 //Zapis pod tą samą nazwą
		{
			//if(this->FEditorFileName.IsEmpty()) return;
			this->pTRichEdit->Lines->SaveToFile(this->FEditorFileName);
			this->pTRichEdit->Modified = false;
			this->pTButtUndo->Enabled = this->pTRichEdit->Modified;
			this->pSBar->Panels->Items[EnPanel_Info]->Text = "Plik niezmodyfikowany";
			this->pTButtSave->Enabled = false; //Plik dopiero co wczytany, więc niema możliwości zapisu
			//Jeśli istnieje zewnętrzna metoda OnSave() to ją wywołaj
			if(this->FOnSave) this->FOnSave(this);
		}
		break;
		//---
		case EnImage_SaveAs:	 //Zapis pod zmienioną nazwą
		{
			TFileSaveDialog	 *pFileSaveDialog = new TFileSaveDialog (this);
			if(!pFileSaveDialog) throw(Exception("Błąd inicjalizacji objektu TFileSaveDialog "));
			pFileSaveDialog->Title = "Podaj nazwę pliku do zapisu";
			for(int i=0; i<ARRAYSIZE(ustrFileTypes); i+=2)
			{
				TFileTypeItem *pTFileTypeItem = pFileSaveDialog->FileTypes->Add();
				pTFileTypeItem->DisplayName = ustrFileTypes[i];
				pTFileTypeItem->FileMask = ustrFileTypes[i+1];
			}

			pFileSaveDialog->Options = TFileDialogOptions() << fdoOverWritePrompt << fdoFileMustExist;
			pFileSaveDialog->DefaultExtension	 = "rtf";
			pFileSaveDialog->FileName = "Bez nazwy";

			try
			{
				try
				{
					if(pFileSaveDialog->Execute())
					{
						this->pTRichEdit->Lines->SaveToFile(pFileSaveDialog->FileName);
						this->pTButtSave->Enabled = false;
						this->pTRichEdit->Modified = false;
						this->pTButtUndo->Enabled = this->pTRichEdit->Modified;
						this->pSBar->Panels->Items[EnPanel_Info]->Text = "Plik niezmodyfikowany";
						//Jeśli istnieje zewnętrzna metoda OnSave() to ją wywołaj
						if(this->FOnSave) this->FOnSave(this); //Nie jestem pewny
					}
				}
				catch(const Exception& e)
				{
					MessageBox(NULL, Format("Błąd otwarcia pliku, do zapisu, o nazwie: %s", ARRAYOFCONST((pFileSaveDialog->FileName))).c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
				}
			}
			__finally
			{
				if(pFileSaveDialog) {delete pFileSaveDialog; pFileSaveDialog = nullptr;}
			}
		}
		break;
		//---
		case EnImage_Open:		 //Otwórz
		{
			TFileOpenDialog *pFileOpenDialog = new TFileOpenDialog(this);
			if(!pFileOpenDialog) throw(Exception("Błąd inicjalizacji objektu TFileOpenDialog"));

			pFileOpenDialog->Title = "Podaj nazwę pliku do odczytu";
			for(int i=0; i<ARRAYSIZE(ustrFileTypes); i+=2)
			{
				TFileTypeItem *pTFileTypeItem = pFileOpenDialog->FileTypes->Add();
				pTFileTypeItem->DisplayName = ustrFileTypes[i];
				pTFileTypeItem->FileMask = ustrFileTypes[i+1];
			}

			pFileOpenDialog->Options = TFileDialogOptions() << fdoPathMustExist << fdoFileMustExist;

			try
			{
				try
				{
					if(pFileOpenDialog->Execute()) //Element został wybrany
					{
						this->pTRichEdit->Lines->LoadFromFile(pFileOpenDialog->FileName);
						this->FEditorFileName = pFileOpenDialog->FileName;
						this->pSBar->Panels->Items[EnPanel_FileInfo]->Text = Format("Aktualny plik: \"%s\"", ARRAYOFCONST((this->FEditorFileName)));
						this->pTRichEdit->Modified = false;
						this->pTButtUndo->Enabled = this->pTRichEdit->Modified;
						this->pSBar->Panels->Items[EnPanel_Info]->Text = "Plik niezmodyfikowany";
						this->pTButtSave->Enabled = false; //Plik dopiero co wczytany, więc niema możliwości zapisu
					}
				}
				catch(const Exception& e)
				{
					MessageBox(NULL, Format("Błąd otwarcia pliku, do odczytu, o nazwie: %s", ARRAYOFCONST((pFileOpenDialog->FileName))).c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
				}
			}
			__finally
			{
				if(pFileOpenDialog) {delete pFileOpenDialog; pFileOpenDialog = nullptr;}
			}

		}
		break;
		//---
		case EnImage_Print:
		{
			this->_PrintEditor();
		}
		break;
		//---
		case EnImage_Clear:		 //Wyczyść
		{
			this->ClearEditor();
		}
		break;
		//---
		case EnImage_Copy:		 //Kopiuj
		{
			this->pTRichEdit->CopyToClipboard();
			this->pTButtInsert->Enabled = true;
		}
		break;
		//---
		case EnImage_Cut:			 //Wytnij
		{
			this->pTRichEdit->CutToClipboard();
			this->pTButtInsert->Enabled = true;
		}
		break;
		//---
		case EnImage_Insert:	 //Wstaw
		{
			this->pTRichEdit->PasteFromClipboard();
		}
		break;
		//---
		case EnImage_Find:		 //Szukaj
		{

		}
		break;
		//---
		case EnImage_FindReplace://Szukaj i podmień
		{

		}
		break;
		//---
		case EnImage_Undo:		 //Cofnij
		{
			if(this->pTRichEdit->CanUndo)
			{
				this->pTRichEdit->Undo();
				if(!this->pTRichEdit->CanUndo)
				//Nie ma więcej cofnięć, więc tekst został niezmodyfikowany
				{
					this->pTRichEdit->Modified = false;
					this->pTButtUndo->Enabled = this->pTRichEdit->Modified;
					this->pSBar->Panels->Items[EnPanel_Info]->Text = "Plik niezmodyfikowany";
					this->pTButtSave->Enabled = false;
					this->pTButtUndo->Enabled = false;
					this->pTButtRedo->Enabled = true;
				}
				else this->pTButtRedo->Enabled = false;
			}

		}
		break;
		//---
		case EnImage_Redo:		 //Wróć
		{
			#if defined(__clang__)
				this->pTRichEdit->Perform(EM_REDO, 0, (LPARAM)0);
			#else
				this->pTRichEdit->Perform(EM_REDO, 0, 0);
			#endif
			this->pTRichEdit->Modified = true;
			if(this->pTRichEdit->CanUndo) this->pSBar->Panels->Items[EnPanel_Info]->Text = "Plik zmodyfikowany";
			//this->pTButtSave->Enabled = true;
			//this->pTButtUndo->Enabled = true;
		}
		break;
		//---
		case EnImage_Bold:		 //Pogrubienie
		{
			if(pTButt->Down)
				this->pTRichEdit->SelAttributes->Style = this->pTRichEdit->SelAttributes->Style << fsBold;
			else
				this->pTRichEdit->SelAttributes->Style = this->pTRichEdit->SelAttributes->Style >> fsBold;
		}
		break;
		//---
		case EnImage_Italic:	 //Pochylona
		{
			if(pTButt->Down)
				this->pTRichEdit->SelAttributes->Style = this->pTRichEdit->SelAttributes->Style << fsItalic;
			else
				this->pTRichEdit->SelAttributes->Style = this->pTRichEdit->SelAttributes->Style >> fsItalic;
		}
		break;
		//---
		case EnImage_Underline: //Podkreślona
		{
			if(pTButt->Down)
				this->pTRichEdit->SelAttributes->Style = this->pTRichEdit->SelAttributes->Style << fsUnderline;
			else
				this->pTRichEdit->SelAttributes->Style = this->pTRichEdit->SelAttributes->Style >> fsUnderline;
		}
		break;
		//---
		case EnImage_StrikeOut: //Przekreślona
		{
			if(pTButt->Down)
				this->pTRichEdit->SelAttributes->Style = this->pTRichEdit->SelAttributes->Style << fsStrikeOut;
			else
				this->pTRichEdit->SelAttributes->Style = this->pTRichEdit->SelAttributes->Style >> fsStrikeOut;
		}
		break;
		//---
		case EnImage_LeftAl:	 //Dosunięcie tekstu do lewego marginesu
		{
			if(pTButt->Down) this->pTRichEdit->Paragraph->Alignment = taLeftJustify;
		}
		break;
		//---
		case EnImage_CentreAl: //Dosunięcie tekstu d centrum
		{
			if(pTButt->Down) this->pTRichEdit->Paragraph->Alignment = taCenter;
		}
		break;
		//---
		case EnImage_RightAl: //Dosunięcie tekstu do prawego marginesu
		{
			if(pTButt->Down) this->pTRichEdit->Paragraph->Alignment = taRightJustify;
		}
		break;
		//---
		case EnImage_Paragraph: //Punktowanie
		{
			if(pTButt->Down) this->pTRichEdit->Paragraph->Numbering = nsBullet;
			else this->pTRichEdit->Paragraph->Numbering = nsNone;
		}
		break;
	}
	this->pTRichEdit->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall GsEditorClass::_OnSelectionChangeEdit(System::TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Zmiana zawartości
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TRichEdit *pREdit = dynamic_cast<TRichEdit *>(Sender);
	if(!pREdit) return;
	//---
	if(this->pTRichEdit->Modified)
	{
		this->pSBar->Panels->Items[EnPanel_Info]->Text = "Plik zmodyfikowany";
		this->pTButtSave->Enabled = true;
	}
	this->pTButtUndo->Enabled = this->pTRichEdit->Modified;
	this->pColBoxFont->Selected = pREdit->SelAttributes->Color; //Kolor czcionki
	int iIndexFont = this->pCBoxSelectFontName->Items->IndexOf(pREdit->SelAttributes->Name);
	if(iIndexFont > -1)
	//Nazwa czcionki
		{this->pCBoxSelectFontName->ItemIndex = iIndexFont;}
	//Wielkość czcionki
	int iIndexSizeFont = this->pCBoxSelectFontSize->Items->IndexOf(pREdit->SelAttributes->Size);
	if(iIndexSizeFont > -1)
	//Style czcionki
		{this->pCBoxSelectFontSize->ItemIndex = iIndexSizeFont;}
	this->pTButtBold->Down = this->pTRichEdit->SelAttributes->Style.Contains(fsBold);
	this->pTButtItalic->Down = this->pTRichEdit->SelAttributes->Style.Contains(fsItalic);
	this->pTButtUnderline->Down = this->pTRichEdit->SelAttributes->Style.Contains(fsUnderline);
	this->pTButtStrikeOut->Down = this->pTRichEdit->SelAttributes->Style.Contains(fsStrikeOut);
	//Formatowanie tekstu
	this->pTButtLeft->Down = this->pTRichEdit->Paragraph->Alignment == taLeftJustify;
	this->pTButtCenter->Down = this->pTRichEdit->Paragraph->Alignment == taCenter;
	this->pTButtRight->Down = this->pTRichEdit->Paragraph->Alignment == taRightJustify;
	//Punktowanie
	this->pTButtParagraf->Down = this->pTRichEdit->Paragraph->Numbering == nsBullet;
	//Kolor podkładu
	TCharFormat2 charFormat;
	ZeroMemory(&charFormat, sizeof(TCharFormat2));
	charFormat.cbSize = sizeof(TCharFormat2);
	this->pTRichEdit->Perform(EM_GETCHARFORMAT,	 (WPARAM)SCF_SELECTION, (LPARAM)&charFormat);

	//if( ((charFormat.dwMask & CFM_BACKCOLOR) == CFM_BACKCOLOR) /*&& ((charFormat.dwEffects & CFE_AUTOCOLOR) != CFE_AUTOCOLOR) && (charFormat.crBackColor == clBlack)*/)
	if(charFormat.crBackColor != 0)
	{
		this->pColBoxBackground->Selected = (TColor)charFormat.crBackColor;
	}
	else this->pColBoxBackground->Selected = (TColor)-1;
}
//---------------------------------------------------------------------------
void __fastcall GsEditorClass::_OnChangeEdit(System::TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Zmiana zawartości
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TRichEdit *pREdit = dynamic_cast<TRichEdit *>(Sender);
	if(!pREdit) return;
	//---
	if(this->pTRichEdit->Modified)
	{
		this->pSBar->Panels->Items[EnPanel_Info]->Text = "Plik zmodyfikowany";
		this->pTButtSave->Enabled = true;
	}
	this->pTButtUndo->Enabled = this->pTRichEdit->Modified;
}
//---------------------------------------------------------------------------
void __fastcall GsEditorClass::_OnChangeCBox(System::TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Zmiana czcionki i jej wielkości
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TComboBox *pCBox = dynamic_cast<TComboBox *>(Sender);
	if(!pCBox) return;
	//---
	switch(pCBox->Tag)
	{
		case EnTag_FontName:	 //Nazwa czcionki
		{
			this->pTRichEdit->SelAttributes->Name = pCBox->Text;
		}
		break;
		//---
		case EnTag_FontSize:	 //Wielkość czcionki
		{
			this->pTRichEdit->SelAttributes->Size = StrToIntDef(pCBox->Items->Strings[pCBox->ItemIndex], 8);
		}
		break;
		//---
	}
	this->pTRichEdit->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall GsEditorClass::_OnChangeColor(System::TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Zmiana kolorów tekstu i podkładu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TColorBox *pColBox = dynamic_cast<TColorBox *>(Sender);
	if(!pColBox) return;
	//---
	switch(pColBox->Tag)
	{
		case EnImage_FontColour: //Kolor czcionki
		{
			this->pTRichEdit->SelAttributes->Color = pColBox->Selected;
		}
		break;
		//---
		case EnImage_FontBackgroundColour: //Kolor podkładu czcionki
		{
			TCharFormat2 cf;
			ZeroMemory(&cf, sizeof(TCharFormat2));
			cf.cbSize = sizeof(TCharFormat2);
			cf.dwMask = CFM_BACKCOLOR;
			cf.crBackColor = ColorToRGB(pColBox->Selected);
			this->pTRichEdit->Perform(EM_SETCHARFORMAT,	 (WPARAM)SCF_SELECTION, (LPARAM)&cf);
		}
		break;
	}
	this->pTRichEdit->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall GsEditorClass::_InitImageList()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TIcon *pIcon=0;
	TMemoryStream *pMemoryStr=0;
	/*
	const unsigned char ID_CLEAR_DIS[] =
	{

	};
	*/
	try
	{
		pIcon = new TIcon();
		if(!pIcon) throw(Exception("Błąd metody TIcon"));
		pMemoryStr = new TMemoryStream();
		if(!pMemoryStr) throw(Exception("Błąd metody TMemoryStream"));
		//****************************************** WERSJA IKON AKTYWNYCH ****************************************
		//--- 0.Ikona - zapis pod tą samą nazwą
		pMemoryStr->WriteBuffer(ID_SAVE, ARRAYSIZE(ID_SAVE)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 1.Ikona - zapis pod zmienioną nazwą
		pMemoryStr->WriteBuffer(ID_SAVE_AS, ARRAYSIZE(ID_SAVE_AS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 2.Ikona - otwórz
		pMemoryStr->WriteBuffer(ID_OPEN, ARRAYSIZE(ID_OPEN)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 3.Ikona - drukuj
		pMemoryStr->WriteBuffer(ID_PRINT, ARRAYSIZE(ID_PRINT)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 4.Ikona - wyczyść
		pMemoryStr->WriteBuffer(ID_CLEAR, ARRAYSIZE(ID_CLEAR)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 5.Ikona - kopiuj
		pMemoryStr->WriteBuffer(ID_COPY, ARRAYSIZE(ID_COPY)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 6.Ikona - wytnij
		pMemoryStr->WriteBuffer(ID_CUT, ARRAYSIZE(ID_CUT)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 7.Ikona - wstaw
		pMemoryStr->WriteBuffer(ID_INSERT, ARRAYSIZE(ID_INSERT)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 8.Ikona - szukaj
		pMemoryStr->WriteBuffer(ID_FIND, ARRAYSIZE(ID_FIND)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 9.Ikona - szukaj i podmień
		pMemoryStr->WriteBuffer(ID_FINDREPLACE, ARRAYSIZE(ID_FINDREPLACE)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 10.Ikona - cofnij
		pMemoryStr->WriteBuffer(ID_UNDO, ARRAYSIZE(ID_UNDO)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 11.Ikona - wróć
		pMemoryStr->WriteBuffer(ID_REDO, ARRAYSIZE(ID_REDO)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 12.Ikona - pogrubiona
		pMemoryStr->WriteBuffer(ID_BOLD, ARRAYSIZE(ID_BOLD)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 13.Ikona - pochylona
		pMemoryStr->WriteBuffer(ID_ITALIC, ARRAYSIZE(ID_ITALIC)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 14.Ikona - podkreślona
		pMemoryStr->WriteBuffer(ID_UNDERLINE, ARRAYSIZE(ID_UNDERLINE)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 15.Ikona - przekreślona
		pMemoryStr->WriteBuffer(ID_STRIKEOUT, ARRAYSIZE(ID_STRIKEOUT)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 16.Ikona - do lewej
		pMemoryStr->WriteBuffer(ID_LEFTAL, ARRAYSIZE(ID_LEFTAL)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 17.Ikona - centrum
		pMemoryStr->WriteBuffer(ID_CENTER, ARRAYSIZE(ID_CENTER)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 18.Ikona - do prawej
		pMemoryStr->WriteBuffer(ID_RIGHTAL, ARRAYSIZE(ID_RIGHTAL)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 19.Ikona - paragraf
		pMemoryStr->WriteBuffer(ID_PARAGRAPH, ARRAYSIZE(ID_PARAGRAPH)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//**************************************** WERSJA IKON NIEAKTYWNYCH ***************************************
		//--- 0.Ikona - zapis pod tą samą nazwą
		pMemoryStr->WriteBuffer(ID_SAVE_DIS, ARRAYSIZE(ID_SAVE_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 1.Ikona - zapis pod zmienioną nazwą
		pMemoryStr->WriteBuffer(ID_SAVE_AS_DIS, ARRAYSIZE(ID_SAVE_AS_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 2.Ikona - otwórz
		pMemoryStr->WriteBuffer(ID_OPEN_DIS, ARRAYSIZE(ID_OPEN_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 3.Ikona - drukuj
		pMemoryStr->WriteBuffer(ID_PRINT_DIS, ARRAYSIZE(ID_PRINT_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 4.Ikona - wyczyść
		pMemoryStr->WriteBuffer(ID_CLEAR_DIS, ARRAYSIZE(ID_CLEAR_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 5.Ikona - kopiuj
		pMemoryStr->WriteBuffer(ID_COPY_DIS, ARRAYSIZE(ID_COPY_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 6.Ikona - wytnij
		pMemoryStr->WriteBuffer(ID_CUT_DIS, ARRAYSIZE(ID_CUT_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 7.Ikona - wstaw
		pMemoryStr->WriteBuffer(ID_INSERT_DIS, ARRAYSIZE(ID_INSERT_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 8.Ikona - szukaj
		pMemoryStr->WriteBuffer(ID_FIND_DIS, ARRAYSIZE(ID_FIND_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 9.Ikona - szukaj i podmień
		pMemoryStr->WriteBuffer(ID_FINDREPLACE_DIS, ARRAYSIZE(ID_FINDREPLACE_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 10.Ikona - cofnij
		pMemoryStr->WriteBuffer(ID_UNDO_DIS, ARRAYSIZE(ID_UNDO_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 11.Ikona - wróć
		pMemoryStr->WriteBuffer(ID_REDO_DIS, ARRAYSIZE(ID_REDO_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 12.Ikona - pogrubiona
		pMemoryStr->WriteBuffer(ID_BOLD_DIS, ARRAYSIZE(ID_BOLD_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 13.Ikona - pochylona
		pMemoryStr->WriteBuffer(ID_ITALIC_DIS, ARRAYSIZE(ID_ITALIC_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 14.Ikona - podkreślona
		pMemoryStr->WriteBuffer(ID_UNDERLINE_DIS, ARRAYSIZE(ID_UNDERLINE_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 15.Ikona - przekreślona
		pMemoryStr->WriteBuffer(ID_STRIKEOUT_DIS, ARRAYSIZE(ID_STRIKEOUT_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 16.Ikona - do lewej
		pMemoryStr->WriteBuffer(ID_LEFTAL_DIS, ARRAYSIZE(ID_LEFTAL_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 17.Ikona - centrum
		pMemoryStr->WriteBuffer(ID_CENTER_DIS, ARRAYSIZE(ID_CENTER_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 18.Ikona - do prawej
		pMemoryStr->WriteBuffer(ID_RIGHTAL_DIS, ARRAYSIZE(ID_RIGHTAL_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListInActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
		//--- 19.Ikona - paragraf
		pMemoryStr->WriteBuffer(ID_PARAGRAPH_DIS, ARRAYSIZE(ID_PARAGRAPH_DIS)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->pTImageListActive->AddIcon(pIcon);										//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();
	}
	__finally
	{
		//--- Zwolnienie objektu, klasy TIcon i TMemoryStream
		if(pIcon) {delete pIcon; pIcon = nullptr;}
		if(pMemoryStr) {delete pMemoryStr; pMemoryStr = nullptr;}
	}
}
//---------------------------------------------------------------------------
void __fastcall GsEditorClass::_PrintEditor()
/**
	OPIS METOD(FUNKCJI): Drukowanie zawartości edytora
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TPrintDialog *PrintDialogMainMan = new TPrintDialog(this);
	if(!PrintDialogMainMan) throw(Exception("Nie dokonano inicjalizacji objektu TPrintDialog"));
	//---
	if(PrintDialogMainMan->Execute())
	{
		this->pTRichEdit->Print("");
	}
}
//---------------------------------------------------------------------------
