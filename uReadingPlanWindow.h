﻿#ifndef uReadingPlanWindowH
#define uReadingPlanWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <SHDocVw.hpp>
#include <Vcl.OleCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class TReadingPlanWindow : public TForm
{
__published:	// IDE-managed Components
	TWebBrowser *WebBrowserReadingPlan1;
	TWebBrowser *WebBrowserReadingPlan2;
	TWebBrowser *WebBrowserReadingPlan3;
	TWebBrowser *WebBrowserReadingPlan4;
	TWebBrowser *WebBrowserReadingPlan5;
	TWebBrowser *WebBrowserReadingPlan6;
	TPageControl *PageControlReadingPlanes;
	TTabSheet *TabSheetPlan1;
	TTabSheet *TabSheetPlan2;
	TTabSheet *TabSheetPlan3;
	TTabSheet *TabSheetPlan4;
	TTabSheet *TabSheetPlan5;
	TTabSheet *TabSheetPlan6;
	TTabSheet *TabSheetPlan7;
	TWebBrowser *WebBrowserReadingPlan7;
	TTabSheet *TabSheetPlan8;
	TWebBrowser *WebBrowserReadingPlan8;
	TLabel *LabelInfosReadingPlan;
	TPanel *PanelTextInfosReadingPlan;
	TImageList *ImageListSmallReadingPlan;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall PageControlReadingPlanesDrawTab(TCustomTabControl *Control,
          int TabIndex, const TRect &Rect, bool Active);
private:	// User declarations
	int _iIDTranslateReadingPlan=-1;
  TList *_pListWebBrowsers=nullptr;
public:		// User declarations
	__fastcall TReadingPlanWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TReadingPlanWindow *ReadingPlanWindow;
//---------------------------------------------------------------------------
#endif