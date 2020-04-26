#include <windows.h>
#include <shlwapi.h>
#include <Strsafe.h>
#include <commctrl.h>
#include "winmbupdext.h"

//#define _MBTESTING_
#pragma hdrstop

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif
const size_t Global_cuMaxLenName=68,
						 Global_cuiMaxlenInfo=512;
const int Global_ciMaxSizeMutexName = 128;

HINSTANCE Global_hThisInstance;
HWND Global_ListBox, Global_ProgressBar, Global_Timer;
HANDLE Global_hSemaphore;

TCHAR Global_lpszPathExistsOldApplic[MAX_PATH],  //Ścieżka dostępu do katalogu lokalnej, istniejącej aplikacji
			Global_lpszPathExistsOldApplic_x64[MAX_PATH],  //Ścieżka dostępu do katalogu lokalnej, istniejącej aplikacji 64 bitowej
			//---
			Global_lpszDownloadedNewApplic[MAX_PATH],  //Ścieżka dostępu do pliku pobranego, aplikacji
			Global_lpszDownloadedNewApplic_x64[MAX_PATH],  //Ścieżka dostępu do pliku pobranego, aplikacji 64 bitowej
			//---
			Global_lpszMutexName[Global_ciMaxSizeMutexName],//Pełna nazwa mutexa
			Global_lpszDirNameUpd[MAX_PATH] = TEXT("MojaBibliaNG"); //Katalog

const	TCHAR Global_lpcszNameApplic[Global_cuMaxLenName] = TEXT("Moja Biblia NG.exe"),          //Nazwa lokalna aplikacji
						Global_lpcszNameApplic_x64[Global_cuMaxLenName] = TEXT("Moja Biblia NG x64.exe");      //Nazwa lokalna aplikacji 64bitowej
/*
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
*/
//--- Inne zmienne
HBRUSH Global_hLBoxBrush; //Pędzel dla podkładu pod kontrolkę LISTBOX

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);	//Obsługa dialogu

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  int iRet=0;
	Global_hThisInstance = hInstance;

	//Tworzenie pełnej nazwy mutexa
	StringCchPrintf(Global_lpszMutexName, Global_ciMaxSizeMutexName, TEXT("MutexName_%s"), Global_lpcszNameApplic);
	//Ścieżka dostępu do katalogu aplikacji
	GetCurrentDirectory(MAX_PATH, Global_lpszPathExistsOldApplic); //Ścieżka dostępu do katalogu lokalnej aplikacji, czyli katalogu aktualnego projektu!
  GetCurrentDirectory(MAX_PATH, Global_lpszPathExistsOldApplic_x64); //Ścieżka dostępu do katalogu lokalnej aplikacji, czyli katalogu aktualnego projektu!
	PathAppend(Global_lpszPathExistsOldApplic, Global_lpcszNameApplic);
	PathAppend(Global_lpszPathExistsOldApplic_x64, Global_lpcszNameApplic_x64);
	//Katalog tymczasowy, do którego sa pobirane aktualizacje
	GetTempPath(MAX_PATH, Global_lpszDownloadedNewApplic); //Pobranie ściezki dostępu do katalogu tymczsowego
  GetTempPath(MAX_PATH, Global_lpszDownloadedNewApplic_x64); //Pobranie ściezki dostępu do katalogu tymczsowego
	//Tworzenie ścieżki dostępu do pobranych aplikacji (ścieżka źródłowa)
	PathAppend(Global_lpszDownloadedNewApplic, Global_lpszDirNameUpd); //Ściezka dostępu do katalogu pobranej aplikacji
	PathAppend(Global_lpszDownloadedNewApplic, Global_lpcszNameApplic); //Ściezka dostępu do pobranej aplikacji
	//Tworzenie ścieżki dostępu do istniejących, starych aplikacji (ścieżka docelowa)
	PathAppend(Global_lpszDownloadedNewApplic_x64, Global_lpszDirNameUpd); //Ściezka dostępu do katalogu pobranej aplikacji 64 bitowej
	PathAppend(Global_lpszDownloadedNewApplic_x64, Global_lpcszNameApplic_x64); //Ściezka dostępu do pobranej aplikacji 64 bitowej
	#if defined(_MBTESTING_) //jeśli w stanie testów
		const int ciSizeTempEnv = 1024;
		TCHAR lpszInfo[ciSizeTempEnv];
		StringCchPrintf(lpszInfo, ciSizeTempEnv, TEXT("%s\n%s\n-----\n%s\n%s"), Global_lpszPathExistsOldApplic, Global_lpszPathExistsOldApplic_x64,
			Global_lpszDownloadedNewApplic, Global_lpszDownloadedNewApplic_x64);

		MessageBox(NULL, lpszInfo, TEXT("Nowa wersja"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
		//return 0;
	#endif

	Global_hLBoxBrush = CreateSolidBrush(RGB(160, 160, 220));			//Pędzel dla podkładu pod kontrolkę LISTBOX
  Sleep(1000);
	iRet = DialogBox(Global_hThisInstance, MAKEINTRESOURCE(DIALOG_UPDATE), NULL, DialogProc);

	DeleteObject(Global_hLBoxBrush);
	return iRet;
}
//---------------------------------------------------------------------------
INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	const int cITimerTime = 2400;
	switch(uMsg)
	{
		case WM_INITDIALOG:
		{
			Global_ListBox = GetDlgItem(hDlg, IDC_LISTBOX);
			Global_ProgressBar = GetDlgItem(hDlg, IDC_PROGRESSBAR);	

			long style = GetWindowLong(Global_ProgressBar, GWL_STYLE);
			style |= PBS_MARQUEE;
			SetWindowLong(Global_ProgressBar, GWL_STYLE, style);

			SendMessage(Global_ProgressBar, (UINT)PBM_SETMARQUEE, (WPARAM)true, (LPARAM)0);

			//Ustawienie ikonki, na pasku okna dialogu
			SetClassLongPtr(hDlg, GCLP_HICON, (LONG_PTR)LoadIcon(Global_hThisInstance, MAKEINTRESOURCE(ICON_UPDATE))); //Ikonka aplikacji
			//Właściwe działanie
			#if !defined(_MBTESTING_) //Jeśli aplikacje NIE JEST w trybie testowym
				Global_hSemaphore = CreateSemaphore(NULL, 0, 1, Global_lpszMutexName);
				if((Global_hSemaphore != 0) && (GetLastError() == ERROR_ALREADY_EXISTS))
				{
					CloseHandle(Global_hSemaphore);
					SendMessage(Global_ListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("Aplikacja nie została zamknięta, więc nie mogę przeprowadzić aktualizacji. Zamknij aplikacje i spróbuj ponownie."));
					return true;
				}
				CloseHandle(Global_hSemaphore);
    	#endif
      SendMessage(Global_ListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("Przeprowadzam aktualizacje..."));
			//Kopiowanie aktualizacji
			BOOL b=FALSE;

			bool result32 = CopyFileEx(Global_lpszDownloadedNewApplic, Global_lpszPathExistsOldApplic, NULL , NULL, &b, NULL);
			bool result64 = CopyFileEx(Global_lpszDownloadedNewApplic_x64, Global_lpszPathExistsOldApplic_x64, NULL , NULL, &b, NULL);

			if((!result32) || (!result64))
			{
				SendMessage(Global_ListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("Kopiowanie nie powiodło się!!! Zamknij okienko aktualizacji"));
				//ShellExecute(NULL, NULL , Global_lpcszNameApplic, NULL, NULL, SW_SHOWNORMAL);
				//SendMessage(hDlg, WM_CLOSE, 0, 0);
			}
			else
			{
				//DeleteFile(Global_lpszDownloadedNewApplic);
				SetTimer(hDlg, IDT_TIMER, cITimerTime, (TIMERPROC) NULL);
				SendMessage(Global_ListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("Aktualizacja zakończyła się pełnym sukcesem, teraz zostanie uruchomiona zaktualizowana aplikacja \"Moja Biblia NG\""));
				#if !defined(_MBTESTING_) //Jeśli aplikacje NIE JEST w trybie testowym
					ShellExecute(NULL, NULL , Global_lpcszNameApplic, NULL, NULL, SW_SHOWNORMAL);
				#endif
				//SendMessage(hDlg, WM_CLOSE, 0, 0);
			}
		}
		break;
		//----------------------------------------------------------------------------------
		case WM_CLOSE:
		{
				KillTimer(hDlg, IDT_TIMER);
				EndDialog(hDlg, 0);
		}
		break;
		//----------------------------------------------------------------------------------
		case WM_CTLCOLORLISTBOX:
		{
			HWND hCtl = (HWND)lParam;	//Uchwyt kontrolki, która wysłała komunikat
			HDC hDC = (HDC)wParam;   //Uchwyt kontekstu urządzenia
			//---
			if(hCtl == Global_ListBox) 	//Jeśli komunikat pochodzi od statycznej kontrolki informacyjnej
			{
				SetBkMode(hDC, TRANSPARENT );					//Tekst bedzie miał przezroczyste tło
        SetTextColor( hDC, RGB(55, 55, 55));	//Kolor tekstu
        return(LRESULT)Global_hLBoxBrush;
			}
		}
		break;
		//----------------------------------------------------------------------------------
		case WM_COMMAND:
		{
		}
		break;
		//----------------------------------------------------------------------------------
		case WM_TIMER:
		{
      switch (wParam)
			{
				case IDT_TIMER:
        	SendMessage(hDlg, WM_CLOSE, 0, 0);
					return true;
			}
		}
		break;
		//----------------------------------------------------------------------------------
		default: return false;
	}
	return true;
}
//---------------------------------------------------------------------------

