#pragma hdrstop

#include "GsHelp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

const int ciAddHeight = 6, // Dodanie wysokości do pozycji by tekst zaczynał sie od górnego marginesu = ciAddHeight / 2
					ciAddWidth = 12; // Dodanie szerokosci do pozycji by tekst zaczynał sie od lewego marginesu = ciAddWidth / 2

__fastcall GsHelp::GsHelp(TComponent* Owner) : TGraphicControl(Owner)
/**
	OPIS METOD(FUNKCJI): Konstruktor
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->Color = this->FGetHelpColor;
	this->Font->Size = this->FGetHelpFontSize;
  this->Font->Quality = TFontQuality::fqClearType;
	this->Canvas->Font = this->Font;
}
//---------------------------------------------------------------------------
__fastcall GsHelp::~GsHelp()
/**
	OPIS METOD(FUNKCJI): Destruktor
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
void __fastcall GsHelp::Paint()
/**
	OPIS METOD(FUNKCJI): Rysowanie połączeń między pozycjami
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TGraphicControl::Paint();
	//Własny kod
  this->Canvas->Brush->Color = this->Color;
	this->Canvas->RoundRect(this->ClientRect, 10, 10);

  // By nie rysować tekstu z podkładem, oraz by metoda Rectangle nie rysowała tła.
	this->Canvas->Brush->Style = bsClear;

	TRect MyRect(this->ClientRect); MyRect.Top = ciAddHeight / 2; MyRect.Left = ciAddWidth / 2;
	MyRect.Right -= ciAddWidth / 2;
	DrawText(this->Canvas->Handle, this->Text.c_str(), -1, &MyRect, DT_WORDBREAK);
}
//---------------------------------------------------------------------------
//----------------------- Metody prywatne właściwości------------------------
void __fastcall GsHelp::FSetHelpText(const UnicodeString &ustrToSet)
/**
	OPIS METOD(FUNKCJI): Zmiana tekstu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->FGetHelpText = ustrToSet;
	this->Text = ustrToSet;
	// Dostosowywanie wysokości to tekstu
	TRect ValMyRect = this->ClientRect;
	this->ClientHeight = DrawText(this->Canvas->Handle, this->Text.c_str(), -1, &ValMyRect, DT_WORDBREAK | DT_CALCRECT) + ciAddHeight;

	this->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall GsHelp::FSetHelpColor(const TColor cColor)
/**
	OPIS METOD(FUNKCJI): Zmiana koloru
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->FGetHelpColor = cColor;
	this->Color = cColor;

	this->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall GsHelp::FSetHelpFontSize(int iSize)
/**
	OPIS METOD(FUNKCJI): Zmiana wielkości czcionki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->FGetHelpFontSize = iSize;

	this->Invalidate();
}
//---------------------------------------------------------------------------

