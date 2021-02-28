#include <vcl.h>
#pragma hdrstop

#include <System.IOUtils.hpp>
#include "uHelpMyBibleWindow.h"
#include "uGlobalVar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THelpMyBibleWindow *HelpMyBibleWindow;
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
	GsDebugClass::WriteDebug("");
#endif
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug("");
#endif
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
*/
//---------------------------------------------------------------------------
__fastcall THelpMyBibleWindow::THelpMyBibleWindow(TComponent* Owner, HelpWindowData &pHelpWindowData)
	: TForm(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!TDirectory::Exists(GlobalVar::Global_ustrDirHelp)) throw(Exception("Brak katalogu z plikami pomocy"));
  //---
	this->PanelImageHelp->Color = clWebBurlywood;
	if(pHelpWindowData.pAction->ImageIndex > -1)
	{
		UnicodeString ustrFullPathHelpFile = TPath::Combine(GlobalVar::Global_ustrDirHelp,
			Format("%u_%s", ARRAYOFCONST(( pHelpWindowData.pAction->ImageIndex, GlobalVar::Global_ustrCoreNameHelp))));
		ustrFullPathHelpFile = TPath::ChangeExtension(ustrFullPathHelpFile, GlobalVar::Global_ustrExtPathHelp);
		#if defined(_DEBUGINFO_)
			GsDebugClass::WriteDebug(ustrFullPathHelpFile);
		#endif

		TBitmap *bmp = new TBitmap();
		if(!bmp) throw(Exception("Błąd inicjalizacji objektu grafiki bmp"));
		//---
		bmp->Width = pHelpWindowData.pAction->Images->Width;
		bmp->Height = pHelpWindowData.pAction->Images->Height;
		bmp->PixelFormat = pf32bit;
		pHelpWindowData.pAction->Images->Draw(bmp->Canvas, 0, 0, pHelpWindowData.pAction->ImageIndex, true);
		this->ImageHelp->Picture->Bitmap->Assign(bmp);
		delete bmp; bmp = nullptr;

		if(TFile::Exists(ustrFullPathHelpFile))
		{
			this->LabelTitle->Caption = pHelpWindowData.pAction->Caption;
			this->WBrowserHelp->Offline = true;
			this->WBrowserHelp->Navigate(ustrFullPathHelpFile.c_str());
		}
		else
		{
      this->LabelTitle->Caption = "Brak pliku pomocy!";
    }
		#if defined(_DEBUGINFO_)
			GsDebugClass::WriteDebug("THelpMyBibleWindow::THelpMyBibleWindow");
		#endif
	}
}
//---------------------------------------------------------------------------
__fastcall THelpMyBibleWindow::~THelpMyBibleWindow()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  #if defined(_DEBUGINFO_)
		GsDebugClass::WriteDebug("THelpMyBibleWindow::~THelpMyBibleWindow");
	#endif
}
//---------------------------------------------------------------------------
void __fastcall THelpMyBibleWindow::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	///
}
//---------------------------------------------------------------------------
void __fastcall THelpMyBibleWindow::FormDestroy(TObject *Sender)
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
void __fastcall THelpMyBibleWindow::FormClose(TObject *Sender, TCloseAction &Action)
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

