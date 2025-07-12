#ifndef GsDebugClassH
#define GsDebugClassH

#include <winuser.h>
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
			if(!AttachConsole(ATTACH_PARENT_PROCESS)) {AllocConsole();}

			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //Uchwyt do konsoli
			HWND hConsole = GetConsoleWindow();
			if(hConsole && hOut)
			{
				// Usuń menu systemowe z paska okna
				LONG style = GetWindowLong(hConsole, GWL_STYLE);
				style &= ~WS_SYSMENU; // Wyczyść flagę WS_SYSMENU
				style &= ~WS_SIZEBOX; // Usuń możliwość przeciągania krawędzi
				SetWindowLong(hConsole, GWL_STYLE, style);

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

			std::wcscpy_s(cfi.FaceName, LF_FACESIZE, L"Consolas"); // lub np. L"Lucida Console"

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
			if(hOut)
			{
				_inStrWrite += "\n";
				WriteConsole(hOut, _inStrWrite.c_str(), _inStrWrite.Length(), 0, 0);
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
			GetConsoleScreenBufferInfo(hOut, &screen);
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
