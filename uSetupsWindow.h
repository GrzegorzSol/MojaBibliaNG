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
	TColorBox *SW_ColorBoxFavorities;
	TColorBox *SW_ColorBoxComment;
	TLabel *LabelColorFavorities;
	TLabel *LabelColorComment;
	TColorBox *SW_ColorBoxNameTranslate;
	TColorBox *SW_ColorBoxBackground;
	TLabel *LabelColorBacground;
	TLabel *LabelColorNameTranslate;
	TColorBox *SW_ColorBoxColorAdressFulltranslates;
	TLabel *LabelColorAdresFullTranslates;
	TPaintBox *SW_PBoxViewSetupColors;
	TScrollBox *SW_ScrBoxViewSetupColors;
	TColorBox *SW_ColorBackgroundMarkerComment;
	TLabel *LabelColorBackgroundMarkComments;
	TTabSheet *SW_OthersSetups;
	TLabel *LabelSizeMainFont;
	TLabel *LabelSizeFontAdress;
	TLabel *LabelFontNameTranslates;
	TSpinEdit *SpEditSizeMainFont;
	TSpinEdit *SpEditSizeAdressFont;
	TSpinEdit *SpEditSizeTranslatesFont;
	TColorBox *SW_ColorBoxColorOrygTr;
	TLabel *LabelColorOrygTr;
	TColorBox *SW_ColorBoxColorNameOrygTran;
	TLabel *LabelColorNameOrygTrans;
	TColorBox *SW_ColorBoxAdressOryg;
	TLabel *LabelColorAdressOryg;
	TButton *ButtFontNameMainText;
	TButton *ButtFontNameAdress;
	TButton *ButtFontNameTranslates;
	TCheckBox *SW_CBoxOnlyOne;
	TCheckBox *SW_CBoxAutoFindUpdate;
	TCheckBox *SW_CBoxReLoadBooks;
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
private:	// User declarations
	UnicodeString __fastcall _SelectMultimediaDir(UnicodeString _ustrPath=GlobalVar::Global_custrPathMultimediaFilesData);
	TStringList *_SListOldConfig;	//Przechowywanie ustawień, podczas uruchomienia okna konfiguracji
	THashedStringList	*_HSListViewAllTr; //Tekst wszystkich dostępnych tłumaczeń, modelowego wersetu
	void __fastcall _ReadAllConfig(); //Odczyt wszystkich ustawień aplikacji i ustawienie komponentów
	void __fastcall _WriteAllConfig();//Zapis wszystkich ustawień aplikacji
public:		// User declarations
	__fastcall TSetupsWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSetupsWindow *SetupsWindow;
//---------------------------------------------------------------------------
#endif
