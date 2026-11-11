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
		UnicodeString ustrAllVersion;
		//Istnieje główne okno
		this->LabelHeaderInfos->Caption = Format(L"%s.", ARRAYOFCONST((Application->MainForm->Caption)));
		for(int iLicz=0; iLicz<GlobalVar::Global_SListAllVersionLibrary->Count; ++iLicz)
		{
			ustrAllVersion += GlobalVar::Global_SListAllVersionLibrary->Strings[iLicz]; ustrAllVersion += "\n";
		}
		this->STextInfoVersions->Caption = Format(L"Wersje zasobów:\n%s", ARRAYOFCONST((ustrAllVersion)));
		this->TimerInfoSystem->Enabled = false;
	}
	else
	{
		//Nie istnieje główne okno
		this->FormStyle = fsStayOnTop;
		//this->AlphaBlendValue = 190;
		this->LabelHeaderInfos->Caption = L"Uruchamianie aplikacji...";
		this->TimerInfoSystem->Enabled = true;
	}
	//---
	UnicodeString ustrTextInfo = UnicodeString(L"Aplikacja do studiowania Pisma Świętego.") +
		L"W jej skład wchodzą polskie przekłady biblii, w wersji protestanckiej jak i katolickiej (zawierającej apokryfy)." +
		L"Aplikacja również posiada dostęp do tekstów oryginalnych, w języku greckim (Nowy Testament, Septuaginta), jak i hebrajskim (Stary Testament).\n" +
		L"OSTRZEŻENIE: Aktualna wersja jest wersją rozwojową (tzw. beta), dlatego może działać niestabilnie!\n\n" +
		L"\tOpis licencji dla aplikacji Moja Biblia NG:\n" +
		L"Produkt ten posiada licencje FreeWare, więc jest przeznaczony do darmowego rozpowszechniania, ale bez czerpania jakichkolwiek korzyści finansowych.\n" +
		L"Kod źródłowy projektu jest upubliczniony na stronie: „https://github.com/GrzegorzSol/MojaBibliaNG_Git”, można go dowolnie modyfikować," +
		L"jednak o wszystkich takich zabiegach autor pragnie być poinformowany, razem z przedstawieniem zmodyfikowanego kodu.\n" +
		L"Aplikacja jest rozwijana pod patronatem zboru Kościoła Zielonoświątkowego w Oświęcimiu, a jej wyłącznym autorem jest Grzegorz Sołtysik.\n\n" +
		L"Jej rozwój rozpoczął się od 2007 roku (kolejne wersje były przeprojektowywane, zmieniane itd.). Więcej informacji znajduje się pod adresem \"https://www.facebook.com/MojaBiblia/\"\n\n",
								ustrInfoVerCompilation = UnicodeString(L"Cały projekt aplikacji, ze wszystkimi jego składnikami został stworzony za pomocą pakietu programistycznego firmy Embarcadero® C++Builder Community 12.1 Version 29.0.52631.8427.\n") +
																				 L"Skompilowany został za pomocą kompilatora C++ z powyższego pakietu, w wersji CLang\n",
								ustrInfox64 = L"\nAktualna wersja jest w wersji 64 bitowej!\n\n";
	//---
	#if defined(_WIN64)
		this->STextInfoLicence->Caption = Format(L"%s%s%s", ARRAYOFCONST((ustrTextInfo, ustrInfoVerCompilation, ustrInfox64)));
	#else
		this->STextInfoLicence->Caption = Format(L"%s%s", ARRAYOFCONST((ustrTextInfo, ustrInfoVerCompilation)));
	#endif
	this->STextInfoSystem->Caption =	Format(L"Wersja systemu operacyjnego:\n%s", ARRAYOFCONST((TOSVersion::ToString())));
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

