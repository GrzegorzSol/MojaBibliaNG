//---------------------------------------------------------------------------

#ifndef uSearchTextWindowH
#define uSearchTextWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <SHDocVw.hpp>
#include <Vcl.OleCtrls.hpp> //Główna klasa do pracy z tekstem biblijnym
#include <System.IniFiles.hpp>
//---------------------------------------------------------------------------
typedef struct _StatisticFindView
{
	unsigned int uiCountFind;   //Ilość znalezień w księdze
							 //uiWidthBar;    //Obliczona szerokość wskaźnika
} StatisticFindView, *PStatisticFindView;
//---------------------------------------------------------------------------
class TSearchTextWindow : public TForm
{
__published:	// IDE-managed Components
	TPageControl *STW_PControlSet;
	TTabSheet *STW_TabSheetInputText;
	TLabeledEdit *STW_LEditSearchText;
	TGridPanel *STW_GrPanelButtons;
	TButton *STW_ButtonSearchStart;
	TCheckBox *STW_ChBoxIsRegEx;
	TTabSheet *STW_TabSheetStatistick;
	TGroupBox *STW_GroBoxSetupSearchText;
	TGroupBox *STW_GroBoxViewSearchText;
	TPageControl *STW_PControlViewsText;
	TTabSheet *STW_TabSheetViewListSearch;
	TImageList *ImgListSmallSearch;
	TWebBrowser *STW_WBrowserResultSearch;
	TTabSheet *STW_TabSheetViewListView;
	TComboBox *STW_CBoxSelectRangeSearch;
	TLabel *STW_LabelInfoRange;
	TComboBox *STW_CBoxStartSelectRange;
	TComboBox *STW_CBoxStopSelectRange;
	TLabel *STW_LabelInfoTo;
	TLabel *STW_LabelInfoSelectTranslates;
	TComboBox *STW_CBoxSelectTranslates;
	TStatusBar *STW_StBarInfos;
	TListView *STW_LViewResultSearch;
	TWebBrowser *STW_WBrowserSelectItemResult;
	TButton *STW_ButtonHelpRegExp;
	TBalloonHint *BalloonHintSearch;
	TListView *STW_LViewStatistic;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall STW_ButtonSearchStartClick(TObject *Sender);
	void __fastcall CBoxCloseUp(TObject *Sender);
	void __fastcall STW_LEditSearchTextChange(TObject *Sender);
	void __fastcall STW_ChBoxIsRegExClick(TObject *Sender);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall STW_LViewResultSearchData(TObject *Sender, TListItem *Item);
	void __fastcall STW_LViewResultSearchDataHint(TObject *Sender, int StartIndex,
          int EndIndex);
	void __fastcall STW_LViewResultSearchGetImageIndex(TObject *Sender, TListItem *Item);
	void __fastcall STW_LViewResultSearchSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
	void __fastcall STW_ButtonHelpRegExpClick(TObject *Sender);
	void __fastcall STW_CBoxSearchDrawItem(TWinControl *Control, int Index,
          TRect &Rect, TOwnerDrawState State);
	void __fastcall STW_PControlChanging(TObject *Sender, bool &AllowChange);
	void __fastcall STW_LViewStatisticDrawItem(TCustomListView *Sender, TListItem *Item,
          TRect &Rect, TOwnerDrawState State);
	void __fastcall FormDeactivate(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);

private:	// User declarations
	THashedStringList *_pHSListSearchResult; //Lista zawierające wszystkie znalezione wersety
	int _iStart_index;	//Początkowy index dla TListView
	int _iEnd_index;    //Końcowy index dla TListView
public:		// User declarations
	__fastcall TSearchTextWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSearchTextWindow *SearchTextWindow;
//---------------------------------------------------------------------------
#endif
