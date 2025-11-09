#include <vcl.h>
#pragma hdrstop

#include "uDisplayPreviewWindow.h"
#include "GsReadBibleTextData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDisplayPreviewWindow *DisplayPreviewWindow;

int __fastcall GetTaskbarHeight();

constexpr int ciWidthWindow = 640,
							ciHeightWindow = 700;
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
	this->Width = ciWidthWindow;
	this->Height = ciHeightWindow;
	this->Left = Screen->Width - ciWidthWindow - 4;
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
void __fastcall TDisplayPreviewWindow::FormShow(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
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


