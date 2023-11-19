#ifndef uReadingPlanWindowH
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
#include <Vcl.Buttons.hpp>
#include <Vcl.CheckLst.hpp>
#include <System.IniFiles.hpp>
//#include "GsReadBibleTextClass\GsReadBibleTextClass.h"
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
	TImageList *ImageListBigReadingPlan;
	TSpeedButton *SButtonStartSpeak;
	TSpeedButton *SButtonJournaling;
	TPanel *PanelDayTextRead;
	TPanel *PanelJournaling;
	TCheckListBox *ChListBoxJournaling;
	TSplitter *SplitterSizeJournaling;
	TSpeedButton *SButtonStopSpeak;
	TPanel *PanelButtons;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall PageControlReadingPlanesDrawTab(TCustomTabControl *Control,
					int TabIndex, const TRect &Rect, bool Active);
	void __fastcall SButtonStartSpeakClick(TObject *Sender);
	void __fastcall SButtonJournalingClick(TObject *Sender);
	void __fastcall ChListBoxJournalingClickCheck(TObject *Sender);
	void __fastcall ChListBoxJournalingDrawItem(TWinControl *Control, int Index,
					TRect &Rect, TOwnerDrawState State);
	void __fastcall ChListBoxJournalingClick(TObject *Sender);
	void __fastcall SplitterSizeJournalingCanResize(TObject *Sender, int &NewSize,
					bool &Accept);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall SButtonStopSpeakClick(TObject *Sender);
private:	// User declarations
	int _iIDTranslateReadingPlan=-1, //Numer tłumaczenia dla planu
			_iDayPlan=0; //Numer dnia od rozpoczęcia czytania według planu
	bool _bIsSelectDay=false; //Czy istnieje możliwość wybory dnia do przeczytania?
	TList *_pListWebBrowsers=nullptr;
	THashedStringList *_pHSListJournaling=nullptr;
	void __fastcall _ReadSetupsJournal(); //Odczyt i ustawienia dziennika
	void __fastcall _ReadSelectPlan(const int iSetDayPlan=-1);		//Odczyt i wyświetlenie pozycji aktualnego planu
	void __fastcall _SpeakText(const UnicodeString ustrTextSpeak); //Tekst do przeczytania na głos przez syntezator mowy
public:		// User declarations
	__fastcall TReadingPlanWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TReadingPlanWindow *ReadingPlanWindow;
//---------------------------------------------------------------------------
#endif
