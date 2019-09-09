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
HWND Global_ButtonImage, Global_ButtonOK, Global_ListBoxHnd, Global_ProgressHnd;
HANDLE Global_hSemaphore;

TCHAR Global_lpszPathExistsOldApplic[MAX_PATH],  //Ścieżka dostępu do katalogu lokalnej, istniejącej aplikacji
			Global_lpszInfo[Global_cuiMaxlenInfo], 		 //Informacje
			Global_lpszDownloadedNewApplic[MAX_PATH],  //Ścieżka dostępu do pliku pobranego, aplikacji
			Global_lpszMutexName[Global_ciMaxSizeMutexName];//Pełna nazwa mutexa
			//Global_lpszFilenameExe[_MAX_PATH];
#if defined(_MBTESTING_)
	const	TCHAR Global_lpcszNameApplic[Global_cuMaxLenName] = TEXT("Moja Biblia NG Testing.exe"),          //Nazwa lokalna aplikacji
				Global_lpcszParentExeFile[MAX_PATH] = TEXT("Moja Biblia NG Testing.exe");
#else
	const	TCHAR Global_lpcszNameApplic[Global_cuMaxLenName] = TEXT("Moja Biblia NG.exe"),          //Nazwa lokalna aplikacji
				Global_lpcszParentExeFile[MAX_PATH] = TEXT("Moja Biblia NG.exe");
#endif
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

	//TCHAR lpszFilenameExe[_MAX_PATH];
	//GetModuleFileName(NULL, Global_lpszFilenameExe, MAX_PATH);
	//Tworzenie pełnej nazwy mutexa
	StringCchPrintf(Global_lpszMutexName, Global_ciMaxSizeMutexName, TEXT("MutexName_%s"), Global_lpcszNameApplic);
	//Ścieżka dostępu do katalogu aplikacji
	GetCurrentDirectory(MAX_PATH, Global_lpszPathExistsOldApplic); //Ścieżka dostępu do katalogu lokalnej aplikacji
	PathAppend(Global_lpszPathExistsOldApplic, Global_lpcszNameApplic);

	GetTempPath(MAX_PATH, Global_lpszDownloadedNewApplic); //Pobranie ściezki dostępu do katalogu tymczsowego
	PathAppend(Global_lpszDownloadedNewApplic, Global_lpcszNameApplic); //Ściezka dostępu do pobranej aplikacji

	Global_hLBoxBrush = CreateSolidBrush(RGB(160, 160, 220));			//Pędzel dla podkładu pod kontrolkę LISTBOX
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
  switch(uMsg)
	{
    case WM_INITDIALOG:
		{
			Global_ListBoxHnd = GetDlgItem(hDlg, IDC_LISTBOX);
			//Ustawienie ikonki, na pasku okna dialogu
			SetClassLongPtr(hDlg, GCLP_HICON, (LONG_PTR)LoadIcon(Global_hThisInstance, MAKEINTRESOURCE(ICON_UPDATE))); //Ikonka aplikacji
			HICON hIconButton = LoadIcon(Global_hThisInstance, MAKEINTRESOURCE(ICON_UPDATE));	//Pzyskanie ikony z zasobów
			SendMessage(Global_ButtonImage , BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIconButton);
			//Tworzenie pełnej nazwy mutexa
			SendMessage(Global_ListBoxHnd, LB_ADDSTRING, 0, (LPARAM)Global_lpszMutexName);

			StringCchPrintf(Global_lpszInfo, Global_cuiMaxlenInfo, TEXT(" %s"), Global_lpszPathExistsOldApplic);
			SendMessage(Global_ListBoxHnd, LB_ADDSTRING, 0, (LPARAM)Global_lpszInfo);
			StringCchPrintf(Global_lpszInfo, Global_cuiMaxlenInfo, TEXT(" %s"), Global_lpszDownloadedNewApplic);
			SendMessage(Global_ListBoxHnd, LB_ADDSTRING, 0, (LPARAM)Global_lpszInfo);

			//SendMessage(Global_ProgressHnd, PBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 100));
		}
		return true;
		//---
    case WM_CLOSE:
    {
				EndDialog(hDlg, 0);
    }
		return true;
		//---
    case WM_CTLCOLORLISTBOX:
		{
			HWND hCtl = (HWND)lParam;	//Uchwyt kontrolki, która wysłała komunikat
			HDC hDC = (HDC)wParam;   //Uchwyt kontekstu urządzenia
			//---
			if(hCtl == Global_ListBoxHnd) 	//Jeśli komunikat pochodzi od statycznej kontrolki informacyjnej
			{
				SetBkMode(hDC, TRANSPARENT );					//Tekst bedzie miał przezroczyste tło
        SetTextColor( hDC, RGB(55, 55, 55));	//Kolor tekstu
        return(LRESULT)Global_hLBoxBrush;
			}
		}
		return true;
		//---
		case WM_COMMAND:
		{
      switch(LOWORD(wParam))
			{
				case IDC_BUTTONOK:
					Global_hSemaphore = CreateSemaphore(NULL, 0, 1, Global_lpszMutexName);
					if((Global_hSemaphore != 0) && (GetLastError() == ERROR_ALREADY_EXISTS))
					{
						CloseHandle(Global_hSemaphore);
						SendMessage(Global_ListBoxHnd, LB_ADDSTRING, 0, (LPARAM)TEXT("Aplikacja nie została zamknieta, więc nie mogę przeprowadzić aktualizacji. Zamknij aplikacje i spróbuj ponownie."));
            return true;
          }

					BOOL b=FALSE;

					//bool result = CopyFileEx(Global_lpszDownloadedNewApplic, Global_lpszPathExistsOldApplic, NULL , NULL, &b, NULL);//COPY_FILE_FAIL_IF_EXISTS);
          bool result=true;
					if(!result)
					{
						SendMessage(Global_ListBoxHnd, LB_ADDSTRING, 0, (LPARAM)TEXT("Kopiowanie nie powiodło się!!! Zamknij okienko aktualizacji"));
            //ShellExecute(NULL, NULL , Global_lpcszParentExeFile, NULL, NULL, SW_SHOWNORMAL);
					}
					else
					{
						ShellExecute(NULL, NULL , Global_lpcszParentExeFile, NULL, NULL, SW_SHOWNORMAL);
						SendMessage(hDlg, WM_CLOSE, 0, 0);
					}
					break;
			}
		}
		//---
    case WM_DESTROY:
		{
			//DestroyWindow(hDlg);
		}
	}
	return false;
}
//---------------------------------------------------------------------------

