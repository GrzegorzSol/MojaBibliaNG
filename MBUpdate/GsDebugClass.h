#ifndef GsDebugClassH
#define GsDebugClassH

#include <winuser.h>
//---------------------------------------------------------------------------
class GsDebugClass
{
	public:
		static void __fastcall InitDebug(short int _Bottom = 26, short int _Right = 100)
		/**
			OPIS METOD(FUNKCJI):
			OPIS ARGUMENTÓW:
			OPIS ZMIENNYCH:
			OPIS WYNIKU METODY(FUNKCJI):
		*/
		{
			if(AllocConsole())
			{
        AttachConsole(GetCurrentProcessId()); //Identyfikator procesu, którego konsola ma być używana.
				SMALL_RECT srctWindow; //Wymiary okna konsoli
				HMENU hMenuWindow;     //Menu systemowe okna konsoli
				HWND hConsoleWindow;         //Uchwyt do okna konsoli
				HANDLE _hMyDebugConsole=NULL;

				_hMyDebugConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Uchwyt do konsoli
				if(_hMyDebugConsole)
				{
					hConsoleWindow = GetConsoleWindow();
					if(hConsoleWindow)
					{
            //Dezaktywacja przycisku systemowego zamykania okna konsoli
						hMenuWindow = GetSystemMenu(hConsoleWindow, false);
						if(hMenuWindow) DeleteMenu(hMenuWindow, SC_CLOSE, MF_BYCOMMAND);
						//Ustalenie wymiarów okna konsoli
						srctWindow.Top = 0; srctWindow.Left = 0;
						srctWindow.Bottom = _Bottom; srctWindow.Right = _Right;
						//---
						SetConsoleTitle(TEXT("Debug Console")); //Tytuł konsoli
						SetConsoleTextAttribute(_hMyDebugConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); //Tekst konsoli
						SetConsoleWindowInfo(_hMyDebugConsole, true, &srctWindow); //Ustawienie rozmiarów konsoli

						SetWindowPos(hConsoleWindow, HWND_TOP, 10, 40, 0, 0, SWP_NOSIZE); //Zmienia położenie okna konsoli debugowania
					}
				}
			}
		};
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
		};
		//-----------------------------------------------------------------------
		inline static void __fastcall WriteDebug(UnicodeString _inStrWrite)
		/**
			OPIS METOD(FUNKCJI): Zapis na konsoli
			OPIS ARGUMENTÓW:
			OPIS ZMIENNYCH:
			OPIS WYNIKU METODY(FUNKCJI):
		*/
		{
			HANDLE _hMyDebugConsole=NULL;
			_hMyDebugConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Uchwyt do konsoli
			if(_hMyDebugConsole == NULL) return;
			_inStrWrite += "\n";
			WriteConsole(_hMyDebugConsole, _inStrWrite.c_str(), _inStrWrite.Length(), 0, 0);
		};
};
//---------------------------------------------------------------------------
#endif
