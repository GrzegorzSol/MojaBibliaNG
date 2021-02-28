#include <vcl.h>
#pragma hdrstop

#include <System.IOUtils.hpp>
#include "uFastTipsWindow.h"
#include "uGlobalVar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFastTipsWindow *FastTipsWindow;
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
	GsDebugClass::WriteDebug("");
#endif
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug("");
#endif
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
*/
//---------------------------------------------------------------------------
__fastcall TFastTipsWindow::TFastTipsWindow(TComponent* Owner)
	: TForm(Owner)
  /**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!TDirectory::Exists(GlobalVar::Global_ustrDirHelp)) throw(Exception("Brak katalogu z plikami pomocy"));
	//---
	this->_pWICImage = nullptr;
  this->_usiIndexFileTips = 0;
	//Odczyt z konfiguracji, czy pokazywać przy starcie tipsy, czy nie, Odpowiednie ustawienie
  //przełącznika, objektu klasy TToggleSwitch
	if(GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsTipsWindowStart, true))
		this->TgSwitchVisibleTips->State = tssOn;
	else
		this->TgSwitchVisibleTips->State = tssOff;
	//Obliczanie ilości kart nawigatora wskazówek i tworzenie objektów TCard
	this->_SDirListFilesTips = TDirectory::GetFiles(GlobalVar::Global_ustrDirHelp, Format("*.%s", ARRAYOFCONST(( GlobalVar::Global_ustrExPathFileTips ))));
}
//---------------------------------------------------------------------------
void __fastcall TFastTipsWindow::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_pWICImage = new TWICImage();
	if(!this->_pWICImage) throw(Exception("Błąd inicjalizacji objektu TWICImage"));
	//Wczytanie grafiki dla wprowadzenia do nawigatora wskazówek
	UnicodeString ustrStartTipsImage = TPath::Combine(GlobalVar::Global_ustrDirHelp,Format("0_%s", ARRAYOFCONST(( GlobalVar::Global_ustrCorePathNameImageTips ))));
	ustrStartTipsImage = TPath::ChangeExtension(ustrStartTipsImage, GlobalVar::Global_ustrExPathTipsImageHelp);
	//---
	if(TFile::Exists(ustrStartTipsImage))
	//Wczytanie początkowej grafiki dla nawigatora wskazówek
	{
		this->_pWICImage->LoadFromFile(ustrStartTipsImage);
		this->ImageTips->Picture->Assign(this->_pWICImage);
	}
	else  throw(Exception("Błąd inicjalizacji nawigatora wskazówek"));
	//Wczytanie tekstu dla wprowadzenia do nawigatora wskazówek
	UnicodeString ustrStartTipsFile = TPath::Combine(GlobalVar::Global_ustrDirHelp,Format("0_%s", ARRAYOFCONST(( GlobalVar::Global_ustrCoreNameFileTips ))));
	ustrStartTipsFile = TPath::ChangeExtension(ustrStartTipsFile, GlobalVar::Global_ustrExPathFileTips);
	//Wczytanie pierwszej karty
	this->WBrowserTips->Navigate(ustrStartTipsFile.c_str());
	//Wczytanie wszystkich kart
	for(int i=0; i<5; i++) //Tymczasowo
	{
		//pNewMemo->Lines->Add(Format("Karta numer: %u", ARRAYOFCONST(( i ))));
	}
}
//---------------------------------------------------------------------------
void __fastcall TFastTipsWindow::FormDestroy(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	delete this->_pWICImage; this->_pWICImage = nullptr;
  #if defined(_DEBUGINFO_)
		GsDebugClass::WriteDebug(Format("this->_SDirListFilesTips.Length: %u", ARRAYOFCONST(( this->_SDirListFilesTips.Length ))));
	#endif
}
//---------------------------------------------------------------------------
void __fastcall TFastTipsWindow::FormClose(TObject *Sender, TCloseAction &Action)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  GlobalVar::Global_ConfigFile->UpdateFile();	//Zrzut pliku ini z pamięci, do pliku ini
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TFastTipsWindow::TgSwitchVisibleTipsClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TToggleSwitch *pTSwitch = dynamic_cast<TToggleSwitch *>(Sender);
	if(!pTSwitch) return;
	//---
	switch(pTSwitch->State)
	{
		case tssOn:
			GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsTipsWindowStart, true);
		break;
		//---
		case tssOff:
			GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsTipsWindowStart, false);
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFastTipsWindow::ButtNextTipsClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TButton *pButton = dynamic_cast<TButton *>(Sender);
	if(!pButton) return;
	//---
}
//---------------------------------------------------------------------------
void __fastcall TFastTipsWindow::ButtPrevTipsClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  TButton *pButton = dynamic_cast<TButton *>(Sender);
	if(!pButton) return;
	//---
}
//---------------------------------------------------------------------------

