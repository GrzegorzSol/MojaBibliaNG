#ifndef uSearchTextWindowH
#define uSearchTextWindowH
//---------------------------------------------------------------------------
#include <SHDocVw.hpp>
#include <System.Classes.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ButtonGroup.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.OleCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
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
	TPageControl *PControlSetupsSearch;
	TTabSheet *TabSheetInputText;
	TTabSheet *TabSheetStatistick;
	TGroupBox *GroBoxSetupSearchText;
	TGroupBox *GroBoxViewSearchText;
	TPageControl *PControlViewsText;
	TTabSheet *TabSheetViewListSearch;
	TImageList *ImgListSmallSearch;
	TWebBrowser *WBrowserResultSearch;
	TTabSheet *TabSheetViewListView;
	TStatusBar *StBarInfos;
	TListView *LViewResultSearch;
	TWebBrowser *WBrowserSelectItemResult;
	TBalloonHint *BalloonHintSearch;
	TListView *LViewStatistic;
	TPanel *PanelButtons;
	TButton *ButtonSearchStart;
	TWebBrowser *WebBrowserSelectBookStatistic;
	TPanel *PanelDisplaySearchBook;
	TStaticText *STextInfoSelectBookSearch;
	TTabSheet *TabSheetSettings;
	TColorBox *ColorBoxBackGroundSearchList;
	TLabel *LabelBackGroundSearchList;
	TLabel *LabelBackGroundStatisticList;
	TColorBox *ColorBoxBackGroundStatisticList;
	TLabel *LabelBackGroundSelectVers;
	TColorBox *ColorBoxBackGroundSelectVers;
	TGroupBox *GrBoxSetupsStatistic;
	TGroupBox *GrBoxSetupsAllSearchResult;
	TGroupBox *GrBoxSetupsSelectVer;
	TButton *ButtonSaveSearch;
	TGroupBox *GrBoxFlags;
	TCheckBox *ChBoxSizeTextSearch;
	TCheckBox *ChBoxMemoSetupsSearch;
	TCheckBox *ChBoxOnlyWord;
	TGroupBox *GrBoxListGroupSearchedTexts;
	TListBox *LBoxSearchTexts;
	TGroupBox *GrBoxRegularExpressions;
	TCheckBox *ChBoxIsRegEx;
	TButton *ButtonHelpRegExp;
	TGroupBox *GrBoxSearchText;
	TComboBox *CBoxHistorySearchText;
	TButton *ButtAddListTextSearch;
	TGroupBox *GrBoxNormalSearch;
	TCheckBox *ChBoxAllSearchTexts;
	TImageList *ImgListLargeSearch;
	TPanel *PanelListButtons;
	TButton *ButtClearAllListSearch;
	TButton *DeleteSelectPos;
	TPanel *PanelListWords;
	TButtonGroup *ButtGrSelectActionList;
	TPanel *PanelInfosSelectActionSearch;
	TLabel *LabelInfosSelectActionSearch;
	TPanel *PanelLogo;
	TImage *ImageLogoSearch;
	TStaticText *STextLogoSearch;
	TLabel *LabelInfoTo;
	TLabel *LabelInfoSelectTranslates;
	TLabel *LabelInfoRange;
	TComboBox *CBoxStopSelectRange;
	TComboBox *CBoxStartSelectRange;
	TComboBox *CBoxSelectTranslates;
	TComboBox *CBoxSelectRangeSearch;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ButtonSearchStartClick(TObject *Sender);
	void __fastcall CBoxCloseUp(TObject *Sender);
	void __fastcall LEditSearchTextChange(TObject *Sender);
	void __fastcall ChBoxIsRegExClick(TObject *Sender);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall LViewResultSearchData(TObject *Sender, TListItem *Item);
	void __fastcall LViewResultSearchDataHint(TObject *Sender, int StartIndex,
					int EndIndex);
	void __fastcall LViewResultSearchGetImageIndex(TObject *Sender, TListItem *Item);
	void __fastcall LViewAllSelectItem(TObject *Sender, TListItem *Item,
					bool Selected);
	void __fastcall ButtonHelpRegExpClick(TObject *Sender);
	void __fastcall CBoxSearchDrawItem(TWinControl *Control, int Index,
					TRect &Rect, TOwnerDrawState State);
	void __fastcall PControlChanging(TObject *Sender, bool &AllowChange);
	void __fastcall LViewStatisticDrawItem(TCustomListView *Sender, TListItem *Item,
					TRect &Rect, TOwnerDrawState State);
	void __fastcall FormDeactivate(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall CBoxHistorySearchTextChange(TObject *Sender);
	void __fastcall PControlViewsTextDrawTab(TCustomTabControl *Control, int TabIndex,
					const TRect &Rect, bool Active);
	void __fastcall ColorBoxGetColors(TCustomColorBox *Sender,
					TStrings *Items);
	void __fastcall ColorBoxChange(TObject *Sender);
	void __fastcall ButtonSaveSearchClick(TObject *Sender);
	void __fastcall ChBoxAllSearchTextsClick(TObject *Sender);
	void __fastcall ButtAddListTextSearchClick(TObject *Sender);
	void __fastcall ButtAllListSearchClick(TObject *Sender);
	void __fastcall ButtGrSelectActionListClick(TObject *Sender);

private:	// User declarations
	THashedStringList *_pHSListSearchResult; //Lista zawierające wszystkie znalezione wersety
	UnicodeString _ustrResultSearchHTML; // [10-10-2023]
	//TIntegerDynArray _ArraySearch; // 26-07-2025
	int _iStart_index;	//Początkowy index dla TListView
	int _iEnd_index;		//Końcowy index dla TListView
	void __fastcall _DisplayListTextHTML(TWebBrowser *_pWebBrowser, THashedStringList *_pHListAnyVers,
		const EnTypeDisplayHTML _TypeDisplayHTML, const int iSelectDisplayVerset=-1);
	void __fastcall _IsMatchRegSearch(const UnicodeString &custrFullVers, const UnicodeString &custrTextSearch,
		THashedStringList *_pBookListText, const int ciIndexVers, PStatisticFindView MyDataStatistic); // 13-07-2025
	bool __fastcall _IsMatchNormalSearch(const UnicodeString &custrFullVers, const UnicodeString &custrTextSearch, // 13-07-2005
		THashedStringList *_pBookListText, const int ciIndexVers, PStatisticFindView _pMyDataStatistic);
	bool __fastcall _IsSameWord(const UnicodeString &custrFullVers, const UnicodeString &custrSearchString,
		const int ciPositionSearch);
	bool __fastcall _IsMatchSearchListTexts(const UnicodeString &custrFullVers, THashedStringList *_pBookListText,
		const int ciIndexVers, PStatisticFindView _pMyDataStatistic); // 14-07-2025
public:		// User declarations
	__fastcall TSearchTextWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSearchTextWindow *SearchTextWindow;
//---------------------------------------------------------------------------
#endif
