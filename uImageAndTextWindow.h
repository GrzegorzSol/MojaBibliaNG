#ifndef uImageAndTextWindowH
#define uImageAndTextWindowH
//---------------------------------------------------------------------------
#include <System.Actions.hpp>
#include <System.Classes.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.WinXCtrls.hpp>

#include "uMyBibleNGLibrary.h"
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TImageAndTextWindow : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PControlTools;
	TPageControl *PControlImageAndText;
	TTabSheet *TabSheetSelectImages;
	TActionToolBar *ActionToolBarImageAndText;
	TImageList *ImageListImageAndTextActive;
	TActionManager *ActionManagerImageAndText;
	TImageList *ImageListImageAndTextInActive;
	TAction *Act_CloseActiveSheet;
	TTabSheet *TabSheetTools;
	TBalloonHint *BalloonHintImageAndText;
	TAction *Act_SaveAs;
	TAction *Act_Save;
	TAction *Act_Text;
	TSplitView *SplitViewImageAndText;
	TMemo *MemoImageAndText;
	TAction *Act_ResizeWorkPanel;
	TImageList *ImageListSmallImageAndText;
	TButton *ButtDisplayNewText;
	TColorBox *CBoxSelectColorText;
	TGroupBox *GrBoxImageAndText1;
	TGroupBox *GrBoxImageAndText2;
	TLabel *LabelColorText;
	TLabel *LabelNameFont;
	TComboBox *CBoxSelectFont;
	TLabel *LabelSizeFont;
	TComboBox *CBoxSizeFont;
	TTrackBar *TrBarOpacityBrush;
	TLabel *LabelSetOpacityBrush;
	TLabel *LabelColorText2;
	TColorBox *CBoxSelectColorText2;
	TLabel *LabelRotationText;
	TTrackBar *TrBarRotationText;
	TCheckBox *ChBoxIsDoubleColor;
	TAction *Act_OnlyText;
	TRadioGroup *RGroupSelectEffects;
	TGroupBox *GrBoxEffects;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Act_CloseActiveSheetExecute(TObject *Sender);
	void __fastcall PControlImageAndTextEnter(TObject *Sender);
	void __fastcall PControlImageAndTextDrawTab(TCustomTabControl *Control, int TabIndex,
          const TRect &Rect, bool Active);
	void __fastcall Act_SaveAsExecute(TObject *Sender);
	void __fastcall Act_SaveExecute(TObject *Sender);
	void __fastcall Act_TextExecute(TObject *Sender);
	void __fastcall Act_ResizeWorkPanelExecute(TObject *Sender);
	void __fastcall PControlImageAndTextChange(TObject *Sender);
	void __fastcall MemoImageAndTextChange(TObject *Sender);
	void __fastcall ButtDisplayNewTextClick(TObject *Sender);
	void __fastcall CBoxSelectColorTextGetColors(TCustomColorBox *Sender, TStrings *Items);
	void __fastcall CBoxAllSelect(TObject *Sender);
	void __fastcall PControlToolsMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall TrBarAllChange(TObject *Sender);
	void __fastcall ChBoxAllClick(TObject *Sender);
	void __fastcall SplitViewImageAndTextOpened(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Act_OnlyTextExecute(TObject *Sender);
	void __fastcall RGroupSelectEffectsClick(TObject *Sender);

private:	// User declarations
	void __fastcall _InitTagAndHint();
	GsDirect2DClass *__fastcall _GetDirect2DFromActiveSheet();
  GsPanelMultiM *_pGsPanelMultiM;
	void __fastcall _SetupAllEnable(const bool _bEnable);
  UnicodeString _ustrInputText;
public:		// User declarations
	__fastcall TImageAndTextWindow(TComponent* Owner, const UnicodeString ustrInput = "");
};
//---------------------------------------------------------------------------
extern PACKAGE TImageAndTextWindow *ImageAndTextWindow;
//---------------------------------------------------------------------------
#endif
