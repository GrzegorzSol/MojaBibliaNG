#include <vcl.h>
#pragma hdrstop

#include "uDisplayPreviewWindow.h"
#include "GsReadBibleTextData.h"
#include "uGlobalVar.h"
#include <windowsx.h>

#if defined(_DEBUGINFO_)
	#include "GsDebugClass.h"
#endif
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDisplayPreviewWindow *DisplayPreviewWindow;

int __fastcall GetTaskbarHeight();
LRESULT __stdcall _NewIEServerProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);
// Zmienne globalne
WNDPROC _OldIEServerProc=nullptr;
HWND hGlFoundIEServer=nullptr;
constexpr wchar_t GlFindWebBrowseClassName[] = L"Internet Explorer_Server";

int iGlGetStartX=0, iGlGetStartY=0, iLastX=-1, iLastY=-1;
bool bGlStartMove=false;
TForm *pDisplayWindow=nullptr;
//---------------------------------------------------------------------------
__fastcall TDisplayPreviewWindow::TDisplayPreviewWindow(TComponent* Owner)
	: TForm(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//--- Okno podglądu tekstu przy zwiniętej aplikacji
	this->Width = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_PreviewWindowText, GlobalVar::GlobalIni_WidthPreviewWindow, 640);
	this->Height = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_PreviewWindowText, GlobalVar::GlobalIni_HeightPreviewWindow, 700);
	this->AlphaBlendValue = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_PreviewWindowText, GlobalVar::GlobalIni_TransparentPreviewWindow, 255);
  if(this->AlphaBlendValue == 255) this->AlphaBlend = false; else this->AlphaBlend = true;

	this->Left = Screen->Width - this->Width - 4;
	this->Top = Screen->Height - this->Height - GetTaskbarHeight() - 4;
	this->WebBrowserPreview->Navigate(WideString("about:blank").c_bstr(), 8); // wypełnienie kontrolki pustą strony.
}
//---------------------------------------------------------------------------
void __fastcall TDisplayPreviewWindow::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	SetWindowPos(this->Handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}
//---------------------------------------------------------------------------
void __fastcall TDisplayPreviewWindow::FormDestroy(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  HWND hIE = this->_GetIEServerWindow();
	if(hIE && _OldIEServerProc)
	{
		SetWindowLongPtr(hIE, GWLP_WNDPROC, (LONG_PTR)_OldIEServerProc);
		_OldIEServerProc = nullptr;
	}
}
//---------------------------------------------------------------------------
void __fastcall TDisplayPreviewWindow::FormShow(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	pDisplayWindow = this;
	if(this->_ustrPreviewText.Length() > 0)
	{
		TStringStream *pStringStream=nullptr;
		try
		{
			pStringStream = new TStringStream("", TEncoding::UTF8, true);
			IPersistStreamInit *psi=nullptr;

			pStringStream->WriteString(this->_ustrPreviewText);
			pStringStream->Position = 0;

      _di_IStream sa(*(new TStreamAdapter(pStringStream, soReference)));
			if(SUCCEEDED(this->WebBrowserPreview->Document->QueryInterface(IID_IPersistStreamInit, (void **)&psi)))
				{psi->Load(sa);}
		}
		__finally
		{
			if(pStringStream) {delete pStringStream; pStringStream = nullptr;}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TDisplayPreviewWindow::FormClose(TObject *Sender, TCloseAction &Action)
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
void __fastcall TDisplayPreviewWindow::SetDisplayPreviewText(const UnicodeString &ustrPreviewText)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_ustrPreviewText = ustrPreviewText;
}
//---------------------------------------------------------------------------
void __fastcall TDisplayPreviewWindow::WebBrowserPreviewDocumentComplete(TObject *ASender,
					IDispatch * const pDisp, const OleVariant &URL)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if (_OldIEServerProc != nullptr) return; // już zrobione
	HWND hIE = this->_GetIEServerWindow();
	if(!hIE) throw(Exception("Nie uzyskano wewnetrznego okna objektu klasy TWebBrowser!"));
	// Podmiana procedury obsługujacej kontrolke na własną (subclassing)
	_OldIEServerProc = (WNDPROC)SetWindowLongPtr(hIE, GWLP_WNDPROC, (LONG_PTR)_NewIEServerProc);
}
//---------------------------------------------------------------------------
HWND TDisplayPreviewWindow::_GetIEServerWindow()
/**
	OPIS METOD(FUNKCJI): Odnalezienie okna wewnetrznego TWebBrowser
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	HWND hParent = this->WebBrowserPreview->Handle;
	hGlFoundIEServer = nullptr;
	EnumChildWindows(hParent, EnumChildProc, 0);

	return hGlFoundIEServer;
}
//--------------------------- FUNKCJE POMOCNICZE-----------------------------
LRESULT __stdcall _NewIEServerProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
/**
	OPIS METOD(FUNKCJI): Podmieniainie WndProc dla okna wewnetrznego TWebBrowser
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	switch(msg)
	{
		case WM_LBUTTONDOWN:
		{
			iGlGetStartX = GET_X_LPARAM(lParam);
			iGlGetStartY = GET_Y_LPARAM(lParam);
			bGlStartMove = true;
		}
		break;
		//---
		case WM_LBUTTONUP:
		{
			bGlStartMove = false; //Koniec przesuwania
		}
		break;
		//---
		case WM_MOUSEMOVE:
		{
			int iX=0, iY=0;
			if(bGlStartMove)
			{
				iX = GET_X_LPARAM(lParam);
				iY = GET_Y_LPARAM(lParam);

				int idX = iX - iLastX; // Przesunięcie w poziomie
				int idY = iY - iLastY; // Przesunięcie w pionie

				pDisplayWindow->Left += (idX - iGlGetStartX);
				pDisplayWindow->Top  += (idY - iGlGetStartY);
				iLastX = iX; iLastY = iY;
        SetCursor(LoadCursor(NULL, IDC_SIZEALL));  // krzyżyk do przesuwania
			}
			iLastX = 0; iLastY = 0; // !!!
		}
		break;
		//---
//		case WM_SETCURSOR:
//		{
//			SetCursor(LoadCursor(NULL, IDC_SIZEALL));  // krzyżyk do przesuwania
//			return TRUE; // blokuje domyślne ustawianie kursora przez IE
//		}
	}

	return CallWindowProc(_OldIEServerProc, hwnd, msg, wParam, lParam);
}
//---------------------------------------------------------------------------
int __fastcall GetTaskbarHeight()
/**
	OPIS METOD(FUNKCJI): Metoda zwraca wwysokość paska zadań Windowsa
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	APPBARDATA t_abd;

	SecureZeroMemory(&t_abd, sizeof(APPBARDATA));
	t_abd.cbSize = sizeof(APPBARDATA);

	if(SHAppBarMessage(ABM_GETTASKBARPOS, &t_abd))
	{
		const RECT t_rc = t_abd.rc;
		switch (t_abd.uEdge)
		{
				case ABE_BOTTOM:
				case ABE_TOP:
						return t_rc.bottom - t_rc.top;

				case ABE_LEFT:
				case ABE_RIGHT:
						return t_rc.right - t_rc.left;
		}
	}

  return 0;
}
//---------------------------------------------------------------------------
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	wchar_t className[MAX_PATH];
	if(GetClassName(hwnd, className, MAX_PATH))
	{
		if(lstrcmp(className, GlFindWebBrowseClassName) == 0)
		{
			hGlFoundIEServer = hwnd;
			return FALSE; // Zatrzymanie przeszukiwania
		}
	}
	return TRUE; // Kontynuacja
}
//---------------------------------------------------------------------------


