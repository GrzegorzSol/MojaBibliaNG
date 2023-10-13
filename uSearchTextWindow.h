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
typedef struct _StatisticFindView //struktura informacyjna o statystyce wyszukiwania
{
	unsigned int uiCountFind;		//Ilość znalezień w księdze
							 //uiWidthBar;		//Obliczona szerokość wskaźnika
} StatisticFindView, *PStatisticFindView;
//---Typy wyświetlania informacji w trybie html,
enum EnTypeDisplayHTML {
												enTypeDisplay_ResultsearchAll=1000,		 //Wyświetlanie wszystkich znalezionych wersetów
												enTypeDisplay_ResultSearchSelectBook,	 //Wyświetlanie znelozionych wersetów dla konkretnej księgi
												enTypeDisplay_ResultSelectVers				 //Wyświetlanie wybranego wersetu z listy wszystkich znalezionych wesetów
											 };
//---------------------------------------------------------------------------
class TSearchTextWindow : public TForm
{
__published:	// IDE-managed Components
	TPageControl *STW_PControlSetupsSearch;
	TTabSheet *STW_TabSheetInputText;
	TCheckBox *STW_ChBoxIsRegEx;
	TTabSheet *STW_TabSheetStatistick;
	TGroupBox *STW_GroBoxSetupSearchText;
	TGroupBox *STW_GroBoxViewSearchText;
	TPageControl *STW_PControlViewsText;
	TTabSheet *STW_TabSheetViewListSearch;
	TImageList *ImgListSmallSearch;
	TWebBrowser *STW_WBrowserResultSearch;
	TTabSheet *STW_TabSheetViewListView;
	TStatusBar *STW_StBarInfos;
	TListView *STW_LViewResultSearch;
	TWebBrowser *STW_WBrowserSelectItemResult;
	TButton *STW_ButtonHelpRegExp;
	TBalloonHint *BalloonHintSearch;
	TListView *STW_LViewStatistic;
	TComboBox *STW_CBoxHistorySearchText;
	TLabel *STW_InfoSearchTextLabel;
	TPanel *STW_PanelButtons;
	TButton *STW_ButtonSearchStart;
	TPanel *STW_PanelImage;
	TPanel *STW_PanelSelectSearchParam;
	TComboBox *STW_CBoxStopSelectRange;
	TLabel *STW_LabelInfoTo;
	TComboBox *STW_CBoxStartSelectRange;
	TComboBox *STW_CBoxSelectTranslates;
	TLabel *STW_LabelInfoSelectTranslates;
	TComboBox *STW_CBoxSelectRangeSearch;
	TLabel *STW_LabelInfoRange;
	TImage *STW_ImageLogoSearch;
	TStaticText *STW_STextLogoSearch;
	TWebBrowser *STW_WebBrowserSelectBookStatistic;
	TPanel *STW_PanelDisplaySearchBook;
	TStaticText *STW_STextInfoSelectBookSearch;
	TTabSheet *STW_TabSheetSettings;
	TColorBox *STW_ColorBoxBackGroundSearchList;
	TLabel *STW_LabelBackGroundSearchList;
	TLabel *STW_LabelBackGroundStatisticList;
	TColorBox *STW_ColorBoxBackGroundStatisticList;
	TLabel *STW_LabelBackGroundSelectVers;
	TColorBox *STW_ColorBoxBackGroundSelectVers;
	TGroupBox *STW_GrBoxSetupsStatistic;
	TGroupBox *STW_GrBoxSetupsAllSearchResult;
	TGroupBox *STW_GrBoxSetupsSelectVer;
	TCheckBox *STW_ChBoxSizeTextSearch;
	TCheckBox *STW_ChBoxMemoSetupsSearch;
	TButton *STW_ButtonSaveSearch;
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
	void __fastcall STW_LViewAllSelectItem(TObject *Sender, TListItem *Item,
					bool Selected);
	void __fastcall STW_ButtonHelpRegExpClick(TObject *Sender);
	void __fastcall STW_CBoxSearchDrawItem(TWinControl *Control, int Index,
					TRect &Rect, TOwnerDrawState State);
	void __fastcall STW_PControlChanging(TObject *Sender, bool &AllowChange);
	void __fastcall STW_LViewStatisticDrawItem(TCustomListView *Sender, TListItem *Item,
					TRect &Rect, TOwnerDrawState State);
	void __fastcall FormDeactivate(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall STW_CBoxHistorySearchTextChange(TObject *Sender);
	void __fastcall STW_PControlViewsTextDrawTab(TCustomTabControl *Control, int TabIndex,
					const TRect &Rect, bool Active);
	void __fastcall STW_ColorBoxGetColors(TCustomColorBox *Sender,
					TStrings *Items);
	void __fastcall STW_ColorBoxChange(TObject *Sender);
	void __fastcall STW_ButtonSaveSearchClick(TObject *Sender);

private:	// User declarations
	THashedStringList *_pHSListSearchResult; //Lista zawierające wszystkie znalezione wersety
	UnicodeString _ustrResultSearchHTML; //[10-10-2023]
	int _iStart_index;	//Początkowy index dla TListView
	int _iEnd_index;		//Końcowy index dla TListView
	void __fastcall _DisplayListTextHTML(TWebBrowser *_pWebBrowser, THashedStringList *_pHListAnyVers,
		const EnTypeDisplayHTML _TypeDisplayHTML, const int iSelectDisplayVerset=-1);
public:		// User declarations
	__fastcall TSearchTextWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSearchTextWindow *SearchTextWindow;
//---------------------------------------------------------------------------
#endif
