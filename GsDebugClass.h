#ifndef GsDebugClassH
#define GsDebugClassH

#include <winuser.h>
#include <strsafe.h>
//---------------------------------------------------------------------------
class GsDebugClass
{
	public:
		inline static void __fastcall InitDebug(int iX=100, int iY=100, int iWidth=800, int iHeight=400, bool bTopMost=false)
		/**
			OPIS METOD(FUNKCJI):
			OPIS ARGUMENTÓW:
			OPIS ZMIENNYCH:
			OPIS WYNIKU METODY(FUNKCJI):
		*/
		{
			// Utwórz lub przypnij konsolę
			BOOL bAttached = AttachConsole(ATTACH_PARENT_PROCESS);
      if(!bAttached)
			{
				AllocConsole();
			}
			else
			{
        // Sprawdź, czy STDOUT faktycznie istnieje
				HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

				if(hOut == nullptr || hOut == INVALID_HANDLE_VALUE)
				{
					// Konsola rodzica jest bezużyteczna → utwórz własną
					FreeConsole();
					AllocConsole();
				}
			}

			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //Uchwyt do konsoli
			HWND hConsole = GetConsoleWindow();
			if(hConsole && hOut)
			{
				// Usuń menu systemowe z paska okna
				LONG style = GetWindowLongPtr(hConsole, GWL_STYLE);
				style &= ~WS_SYSMENU; // Wyczyść flagę WS_SYSMENU
				style &= ~WS_SIZEBOX; // Usuń możliwość przeciągania krawędzi
				SetWindowLongPtr(hConsole, GWL_STYLE, style);

        SetWindowPos(hConsole, nullptr, 0, 0, 0, 0,
					SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

				SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY); //Tekst konsoli

				MoveWindow(hConsole, iX, iY, iWidth, iHeight, TRUE);
				if(bTopMost) SetWindowPos(hConsole, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW | SWP_FRAMECHANGED);
			}

			SetConsoleTitle(TEXT("Debug Console"));
		}
		//-----------------------------------------------------------------------
		inline static void __fastcall SetConsoleFontSize(short width, short height)
		/**
			OPIS METOD(FUNKCJI):
			OPIS ARGUMENTÓW:
			OPIS ZMIENNYCH:
			OPIS WYNIKU METODY(FUNKCJI):
		*/
		{
      HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			if(hOut == INVALID_HANDLE_VALUE) return;

      CONSOLE_FONT_INFOEX cfi;
			cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    	GetCurrentConsoleFontEx(hOut, FALSE, &cfi);

      cfi.nFont = 0;
      cfi.dwFontSize.X = width;   // szerokość (zwykle ignorowana)
			cfi.dwFontSize.Y = height;  // wysokość znaków
      cfi.FontFamily = FF_DONTCARE;
			cfi.FontWeight = FW_NORMAL;

      ZeroMemory(cfi.FaceName, sizeof(cfi.FaceName));
			//std::wcscpy_s(cfi.FaceName, LF_FACESIZE, L"Consolas"); // lub np. L"Lucida Console"
			StringCchCopy(cfi.FaceName, LF_FACESIZE, L"Consolas");

			SetCurrentConsoleFontEx(hOut, FALSE, &cfi);
    }
		//-----------------------------------------------------------------------
		inline static void __fastcall WriteDebug(UnicodeString _inStrWrite)
		/**
			OPIS METOD(FUNKCJI): Zapis na konsoli
			OPIS ARGUMENTÓW:
			OPIS ZMIENNYCH:
			OPIS WYNIKU METODY(FUNKCJI):
		*/
		{
			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //Uchwyt do konsoli
			DWORD written;
			if(hOut)
			{
				_inStrWrite += "\n";
				WriteConsole(hOut, _inStrWrite.c_str(), _inStrWrite.Length(), &written, 0);
      }
		}
		//-----------------------------------------------------------------------
		inline static void __fastcall ClearDebug()
    /**
			OPIS METOD(FUNKCJI):
			OPIS ARGUMENTÓW:
			OPIS ZMIENNYCH:
			OPIS WYNIKU METODY(FUNKCJI):
		*/
		{
      COORD topLeft = {0, 0};
			CONSOLE_SCREEN_BUFFER_INFO screen;
			DWORD written;

			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //Uchwyt do konsoli
			if(!GetConsoleScreenBufferInfo(hOut, &screen)) return;
			FillConsoleOutputCharacter(hOut, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
			FillConsoleOutputAttribute(hOut, screen.wAttributes, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
			SetConsoleCursorPosition(hOut, topLeft);
    }
		//-----------------------------------------------------------------------
    inline static void __fastcall CloseDebug()
		/**
			OPIS METOD(FUNKCJI):
			OPIS ARGUMENTÓW:
			OPIS ZMIENNYCH:
			OPIS WYNIKU METODY(FUNKCJI):
		*/
		{
			FreeConsole();
		}
};
//---------------------------------------------------------------------------
#endif
