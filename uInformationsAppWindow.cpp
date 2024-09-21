#include <vcl.h>
#pragma hdrstop

#include "uInformationsAppWindow.h"
#include "uGlobalVar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInformationsAppWindow *InformationsAppWindow;
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif
*/
//---------------------------------------------------------------------------
__fastcall TInformationsAppWindow::TInformationsAppWindow(TComponent* Owner)
	: TForm(Owner)
/**
	OPIS METOD(FUNKCJI): Konstruktor klasy TInformationsAppWindow
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(Application->MainForm)
	{
		//Istnieje główne okno
		this->LabelHeaderInfos->Caption = Format("%s.", ARRAYOFCONST((Application->MainForm->Caption)));
		this->STextInfoVersions->Caption = Format("Wersje zasobów:\n%s.", ARRAYOFCONST((GlobalVar::Global_ustrVerGsReadBibleTextClass)));
		this->TimerInfoSystem->Enabled = false;
	}
	else
	{
		//Nie istnieje główne okno
		this->FormStyle = fsStayOnTop;
		//this->AlphaBlendValue = 190;
		this->LabelHeaderInfos->Caption = "Uruchamianie aplikacji...";
		this->TimerInfoSystem->Enabled = true;
	}
	//---
	UnicodeString ustrTextInfo = UnicodeString("Aplikacja do studiowania Pisma Świętego.") +
		"W jej skład wchodzą polskie przekłady biblii, w wersji protestanckiej jak i katolickiej (zawierającej apokryfy)." +
		"Aplikacja również posiada dostęp do tekstów oryginalnych, w języku greckim (Nowy Testament, Septuaginta), jak i hebrajskim (Stary Testament).\n" +
		"OSTRZEŻENIE: Aktualna wersja jest wersją rozwojową (tzw. beta), dlatego może działać niestabilnie!\n\n" +
		"\tOpis licencji dla aplikacji Moja Biblia NG:\n" +
		"Produkt ten posiada licencje FreeWare, więc jest przeznaczony do darmowego rozpowszechniania, ale bez czerpania jakichkolwiek korzyści finansowych.\n" +
		"Kod źródłowy projektu jest upubliczniony na stronie: „https://github.com/GrzegorzSol/MojaBibliaNG_Git”, można go dowolnie modyfikować," +
		"jednak o wszystkich takich zabiegach autor pragnie być poinformowany, razem z przedstawieniem zmodyfikowanego kodu.\n" +
		"Aplikacja jest rozwijana pod patronatem zboru Kościoła Zielonoświątkowego w Oświęcimiu, a jej wyłącznym autorem jest Grzegorz Sołtysik.\n\n" +
		"Jej rozwój rozpoczął się od 2007 roku (kolejne wersje były przeprojektowywane, zmieniane itd.). Więcej informacji znajduje się pod adresem \"https://www.facebook.com/MojaBiblia/\"\n\n",
								ustrInfoVerCompilation = UnicodeString("Cały projekt aplikacji, ze wszystkimi jego składnikami został stworzony za pomocą pakietu programistycznego firmy Embarcadero® C++Builder Community 12.1 Version 29.0.52631.8427.\n") +
																				 "Skompilowany został za pomocą kompilatora C++ z powyższego pakietu, w wersji CLang\n",
								ustrInfox64 = "\nAktualna wersja jest w wersji 64 bitowej!\n\n";
	//---
	#if defined(_WIN64)
		this->STextInfoLicence->Caption = Format("%s%s%s", ARRAYOFCONST((ustrTextInfo, ustrInfoVerCompilation, ustrInfox64)));
	#else
		this->STextInfoLicence->Caption = Format("%s%s", ARRAYOFCONST((ustrTextInfo, ustrInfoVerCompilation)));
	#endif
	this->STextInfoSystem->Caption =	Format("Wersja systemu operacyjnego:\n%s", ARRAYOFCONST((TOSVersion::ToString())));
}
//---------------------------------------------------------------------------
void __fastcall TInformationsAppWindow::FormClose(TObject *Sender, TCloseAction &Action)
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
void __fastcall TInformationsAppWindow::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//
}
//---------------------------------------------------------------------------
void __fastcall TInformationsAppWindow::TimerInfoSystemTimer(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	static unsigned char sucTick;
	if(sucTick==8) this->Close();
	++sucTick;
}
//---------------------------------------------------------------------------

