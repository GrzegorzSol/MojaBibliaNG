﻿#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include "uGlobalVar.h"
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("uInformationsAppWindow.cpp", InformationsAppWindow);
USEFORM("uMainWindow.cpp", MainBibleWindow);
USEFORM("uDictGrecPolWindow.cpp", DictGrecPolWindow);
USEFORM("uHistoryChaptersOpen.cpp", HistoryOpenChaptersWindow);
USEFORM("uNewSchemeVersWindow.cpp", NewSchemeVersWindow);
USEFORM("uSendingMailWindow.cpp", SendingMailWindow);
USEFORM("uSetupsWindow.cpp", SetupsWindow);
USEFORM("uStrongWindow.cpp", StrongWindow);
USEFORM("uReadingPlanWindow.cpp", ReadingPlanWindow);
USEFORM("uSearchTextWindow.cpp", SearchTextWindow);
USEFORM("uSelectVersWindow.cpp", SelectVersWindow);
USEFORM("uChapterEditWindow.cpp", ChapterEditWindow);
USEFORM("uAllMultimediaView.cpp", AllMultimediaView);
USEFORM("uBooksSpecjalistWindow.cpp", BooksSpecjalistWindow);
//---------------------------------------------------------------------------
#include "uInformationsAppWindow.h"
//---------------------------------------------------------------------------
void GsGetVersionIExplorer(int *iMajor, int *iMinor);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	HANDLE hSemaphore=nullptr;
	TMemIniFile *pTempMemIni=nullptr;
	int iReturn=0;
	
	try
	{
		try
		{
			//----- Sprawdzenie wersji systemu, jeśli mniejsz niż Windows 7, to wyjdź,
			//if(!TOSVersion::Check(6, 1)) //Zmienić na minimum Windows 10
			if(!TOSVersion::Check(10, 0))
			{
				//throw(Exception("Aplikacja do uruchomienia wymaga systemu operacyjnego w wersji minimalnej 6.1 (Windows 7 sp.1)"));
				throw(Exception("Aplikacja do uruchomienia wymaga systemu operacyjnego w wersji minimalnej 10.0 (Windows 10)"));
			}
			//----- Sprawdzanie czy została uruchomiona druga kopia aplikacji, jesli tak
			//			to zostanie automatycznie zamknięta
			pTempMemIni = new TMemIniFile(GlobalVar::Global_custrGetConfigFile, TEncoding::UTF8);
			if(!pTempMemIni) throw(Exception("Błąd inicjalizacji objektu TMemIniFile"));
			//----- Tworzenie globalnego wskaźnika, do pliku konfiguracyjnego
			bool bOnlyOne = pTempMemIni->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsOnlyOne, true);
			//---
			if(bOnlyOne) //Jeśli jest dopuszczalna tylko jedna kopia aplikacji, to sprawdzam czy nie uruchomiono drugiej.
			{
				hSemaphore = CreateSemaphore(NULL, 0, 1, GlobalVar::Global_ustrMutexName.c_str());
				if((hSemaphore != 0) && (GetLastError() == ERROR_ALREADY_EXISTS))
				{
					if(hSemaphore) {CloseHandle(hSemaphore); hSemaphore = nullptr;}
					throw(Exception("Została uruchomiona druga kopia aplikcji \"Moja Biblia NG\", więc zostanie ona natychmiast zamknięta!"));
				}
				else if(!hSemaphore)
				{
					throw(Exception("Nie mogę utworzyć semafora systemowego, więc zostanie ona natychmiast zamknięta!"));
				}
				if(hSemaphore) {CloseHandle(hSemaphore); hSemaphore = nullptr;}
			}
			//----- Sprawdzenie wersji Internet Explorera
			int iIEMajor=0, iIEMinor=0;
			const int iMinIEVersion=7;
			GsGetVersionIExplorer(&iIEMajor, &iIEMinor);
			if(iIEMajor < iMinIEVersion)
			{
				throw(Exception("Do poprawnej pracy aplikacji \"Moja Biblia NG\", potrzebny jest Internet Explorer w wersji, minimalnej 7. Niestety twoja wersja nie spełnia powyższych wymogów, więc aplikacja się nie uruchomi."));
			}
			//--- Otwarcie ewentualnie winiety informacyjnej
			if(pTempMemIni->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsDisplaySplashStart, true))
			{
				TInformationsAppWindow *pTInformationsAppWindow = new TInformationsAppWindow(Application);
				if(!pTInformationsAppWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TInformationsAppWindow"));
				pTInformationsAppWindow->Show();
				Application->ProcessMessages();
			}
			if(pTempMemIni) {delete pTempMemIni; pTempMemIni = nullptr;}
			//--- Klasyczny kod rozruchowy aplikacji
			Application->Initialize();
			Application->MainFormOnTaskBar = true;
			Application->CreateForm(__classid(TMainBibleWindow), &MainBibleWindow);
		Application->Run();
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
		catch (...)
		{
			try
			{
				throw Exception("");
			}
			catch (Exception &exception)
			{
				Application->ShowException(&exception);
			}
		} //catch
	} //__finally
	__finally
	{
		#if defined(_DEBUGINFO_)
			GsDebugClass::WriteDebug("__finally");
		#endif
		if(pTempMemIni) {delete pTempMemIni; pTempMemIni = nullptr;}
		if(hSemaphore) {CloseHandle(hSemaphore); hSemaphore = nullptr;}
	}

	return iReturn;
}
//---------------------------------------------------------------------------
void GsGetVersionIExplorer(int *iMajor, int *iMinor)
/**
	OPIS METOD(FUNKCJI): Funkcja służy do odczytywania wersji Internet Eksplorera z pliku rejestru
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	LONG lResult;
	int iPos,iPos2;
	const int ciSizeTemp = 5;
	HKEY hKey;
	DWORD dwSize=100, dwType;
	TCHAR szValue[100], szTemp[ciSizeTemp],
				*pDec,*pDec2;
	const TCHAR wSubkey[] = TEXT("SOFTWARE\\Microsoft\\Internet Explorer"),
							wVersion[] = TEXT("Version");
	bool bRetStr;
	try
	{
		lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, wSubkey, 0, KEY_QUERY_VALUE, &hKey);
		if(lResult != ERROR_SUCCESS) throw(Exception("Błąd otwarcia rejestru systemowego"));

		lResult = RegQueryValueEx(hKey, wVersion, NULL, &dwType, LPBYTE(szValue), &dwSize);
		if(lResult != ERROR_SUCCESS) throw(Exception("Błąd odczytu wartości z	 klucza rejestru"));

		//pDec = StrStr(szValue, TEXT("."));
		pDec = StrPos(szValue, TEXT("."));
		if(pDec == NULL) throw(Exception("Błąd odczytu wersji Internet Explorera"));
		//Pobieranie ze stringa informacji og³ównej wersji
		iPos = pDec - szValue + 1;
		ZeroMemory(szTemp, ciSizeTemp);
		//StringCchCopyN(szTemp, ciSizeTemp, szValue, iPos - 1);
		StrLCopy(szTemp, szValue, iPos - 1);
		bRetStr = TryStrToInt(szTemp, *iMajor);
		if(!bRetStr) throw(Exception("Błąd odczytu wersji Internet Explorera"));
		//Pobieranie ze stringa "mniejszej" wersji
		pDec++;
		//pDec2 = StrStr(pDec, TEXT("."));
		pDec2 = StrPos(pDec, TEXT("."));//Błąd odczytu wersji Internet Explorera"));
		iPos2 = pDec2 - szValue + 1;
		ZeroMemory(szTemp, ciSizeTemp);
		//StringCchCopyN(szTemp, ciSizeTemp, pDec, iPos2 - iPos - 1);
		StrLCopy(szTemp, pDec, iPos2 - iPos - 1);
		bRetStr = TryStrToInt(szTemp, *iMinor);
		if(!bRetStr) throw(Exception("Błąd odczytu wersji Internet Explorera"));
	}
	__finally
	{
		RegCloseKey(hKey);
	}
}
//---------------------------------------------------------------------------
