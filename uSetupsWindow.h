/*
	Klasa do obsługi okna wszystkich ustawień aplikacji
*/
//---------------------------------------------------------------------------

#ifndef uSetupsWindowH
#define uSetupsWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ButtonGroup.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "uGlobalVar.h"
#include <Vcl.CheckLst.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TSetupsWindow : public TForm
{
__published:	// IDE-managed Components
	TButtonGroup *SW_ButGroupSections;
	TImageList *SW_ImgListMain;
	TPageControl *SW_PControlSelected;
	TGridPanel *SW_GrPanelButtons;
	TTabSheet *SW_SheetLajout;
	TTabSheet *SW_SheetFlags;
	TTabSheet *SW_SheetPaths;
	TLabeledEdit *SW_LEditPath1;
	TLabeledEdit *SW_LEditPath2;
	TLabeledEdit *SW_LEditPath3;
	TGroupBox *SW_GrBoxSelectPathDirMulti;
	TImageList *SW_ImgListSmallMain;
	TButton *SW_ButtSelectDirMulti_1;
	TButton *SW_ButtSelectDirMulti_2;
	TButton *SW_ButtSelectDirMulti_3;
	TButton *SW_ButtSetupSave;
	TButton *SW_ButtSetupCancel;
	TBalloonHint *SW_BalloonHint;
	TCheckBox *SW_CBoxIsDisplaySplashScreen;
	TCheckBox *SW_CBoxIsRequestEnd;
	TButton *SW_ButtSetupReturn;
	TTabSheet *SW_SheetTranslates;
	TImageList *SW_ImgListMainSmall;
	TListView *SW_ListViewAllTranslates;
	TStaticText *SW_STextInfo;
	TStaticText *SW_STextInfoHeadSelectTranslates;
	TGroupBox *GrBoxSetColors;
	TPaintBox *SW_PBoxViewSetupColors;
	TScrollBox *SW_ScrBoxViewSetupColors;
	TTabSheet *SW_OthersSetups;
	TLabel *LabelSizeMainFont;
	TLabel *LabelSizeFontAdress;
	TLabel *LabelFontNameTranslates;
	TSpinEdit *SpEditSizeMainFont;
	TSpinEdit *SpEditSizeAdressFont;
	TSpinEdit *SpEditSizeTranslatesFont;
	TColorBox *SW_ColorBoxColorOrygTr;
	TLabel *LabelColorOrygTr;
	TButton *ButtFontNameMainText;
	TButton *ButtFontNameAdress;
	TButton *ButtFontNameTranslates;
	TCheckBox *SW_CBoxOnlyOne;
	TCheckBox *SW_CBoxAutoFindUpdate;
	TCheckBox *SW_CBoxReLoadBooks;
	TCheckBox *SW_CBoxTips;
	TPanel *SW_PanelSelectListButtons;
	TPanel *SW_PanelImageLogo;
	TImage *SW_SetupsImageLogo;
	TGroupBox *GrBoxSetupsFullTr;
	TLabel *LabelColorBacground;
	TColorBox *SW_ColorBoxBackground;
	TLabel *LabelColorNameTranslate;
	TColorBox *SW_ColorBoxNameTranslate;
	TLabel *LabelColorAdresFullTranslates;
	TColorBox *SW_ColorBoxColorAdressFulltranslates;
	TGroupBox *GrBoxSelectAndCommentsSetups;
	TColorBox *SW_ColorBoxFavorities;
	TLabel *LabelColorFavorities;
	TLabel *LabelColorComment;
	TColorBox *SW_ColorBoxComment;
	TColorBox *SW_ColorBackgroundMarkerComment;
	TLabel *LabelColorBackgroundMarkComments;
	TGroupBox *GrBoxOryginalPartTranslates;
	TLabel *LabelColorAdressOryg;
	TColorBox *SW_ColorBoxAdressOryg;
	TLabel *LabelColorNameOrygTrans;
	TColorBox *SW_ColorBoxColorNameOrygTran;
	TTabSheet *SW_SheetReadingPlan;
	TPanel *PanelReadingPlanSetupLeft;
	TComboBox *CBoxSelectTranslate;
	TComboBox *CBoxSelectPlan;
	TComboBox *CBoxSelectFontReadingPlan;
	TComboBox *CBoxSelectSizeFontPlan;
	TDateTimePicker *DateTimePickerSelectStartDatePlan;
	TSpeedButton *SpButtonStartPlan;
	TPanel *PanelViewSelectPlan;
	TListView *LViewDisplayselectPlan;
	TLabel *LabelInfoSelectAndactivatePlan;
	TLabel *LabelTitleDisplayListPlan;
	TGroupBox *GrBoxSelectTranslate;
	TGroupBox *GrBoxSelectReadingPlan;
	TGroupBox *GrBoxSelectFont;
	TGroupBox *GrBoxSizeFont;
	TGroupBox *GrBoxSelectDate;
	TGroupBox *GrBoxSetupsSpeak;
	TTrackBar *TrackBarSetRate;
	TTrackBar *TrackBarSetVolume;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall SW_ButGroupSectionsButtonClicked(TObject *Sender, int Index);
	void __fastcall SW_PControlSelectedChange(TObject *Sender);
	void __fastcall SW_ButtSetups_Click(TObject *Sender);
	void __fastcall SW_CBox_Click(TObject *Sender);
	void __fastcall SW_ColorBoxGetColors(TCustomColorBox *Sender, TStrings *Items);
	void __fastcall SW_PBoxViewSetupColorsPaint(TObject *Sender);
	void __fastcall SW_ColorAllChange(TObject *Sender);
	void __fastcall ButtFontSelectClick(TObject *Sender);
	void __fastcall SpEditSizeFontChange(TObject *Sender);
	void __fastcall SW_ButGroupSectionsKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall SpButtonStartStopReadingPlanClick(TObject *Sender);
	void __fastcall DateTimePickerSelectStartDatePlanChange(TObject *Sender);
	void __fastcall LViewDisplayselectPlanDrawItem(TCustomListView *Sender, TListItem *Item,
          TRect &Rect, TOwnerDrawState State);
	void __fastcall CBoxSelectPlanChange(TObject *Sender);
	void __fastcall LViewDisplayselectPlanChanging(TObject *Sender, TListItem *Item,
          TItemChange Change, bool &AllowChange);

private:	// User declarations
	UnicodeString __fastcall _SelectMultimediaDir(UnicodeString _ustrPath=GlobalVar::Global_custrPathMultimediaFilesData);
	TStringList *_SListOldConfig=nullptr;	//Przechowywanie ustawień, podczas uruchomienia okna konfiguracji
	THashedStringList	*_HSListViewAllTr=nullptr; //Tekst wszystkich dostępnych tłumaczeń, modelowego wersetu
	void __fastcall _ReadAllConfig(); //Odczyt wszystkich ustawień aplikacji i ustawienie komponentów
	void __fastcall _WriteAllConfig();//Zapis wszystkich ustawień aplikacji
	void __fastcall _VaidatePathMedia(TLabeledEdit *pLEditPath, UnicodeString ustrSection, UnicodeString ustrkey); //Niewłaściwa ścierzka dostępu do katalogu z mediami //30-03-2021
	void __fastcall _InitLViewDisplaySelectPlan(); //Inicjalizacja parametrów dla listy przeglądu wybranego planu
	void __fastcall _DisplaySelectPlan(); //Wyswietlenie wybranego planu
	int _iNumberDayPlan=-1; //Numer kolejnej lekcji z aktywnego planu
public:		// User declarations
	__fastcall TSetupsWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSetupsWindow *SetupsWindow;
//---------------------------------------------------------------------------
#endif
