#ifndef uMainWindowH
#define uMainWindowH
//---------------------------------------------------------------------------
#include "GsReadBibleTextClass\GsReadBibleTextClass.h" //Główna klasa do pracy z tekstem biblijnym
#include <System.Actions.hpp>
#include <System.Classes.hpp>
#include <System.ImageList.hpp>
#include <System.Win.TaskbarCore.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <Vcl.Taskbar.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ActnColorMaps.hpp>
#include <Vcl.WinXCtrls.hpp> //!!!
//#include <Vcl.AppEvnts.hpp>
//---------------------------------------------------------------------------
class TMainBibleWindow : public TForm
{
__published:	// IDE-managed Components
	TActionToolBar *ActionToolBarMain;
	TActionManager *ActionManagerMain;
	TPageControl *PageControlBibleText;
	TAction *Act_CloseSheetActive;
	TImageList *ImageListMainActive;
	TImageList *ImageListMainInactive;
	TAction *Act_SaveChaptToHTML;
	TAction *Act_SearchBibleText;
	TStatusBar *StatusBarMain;
	TAction *Act_SetupsApplic;
	TAction *Act_SelectVers;
	TBalloonHint *BalloonHintMain;
	TTrayIcon *TrayIconMain;
	TPopupMenu *PMenuTray;
	TTaskbar *TaskbarMain;
	TCoolBar *CoolBarMain;
	TActionToolBar *ActionToolBarTools;
	TAction *Act_CorcordanceDictionaryGrec;
	TImageList *ImageListSmall;
	TAction *Act_ProjectSchemeVers;
	TAction *Act_Infomations;
	TStandardColorMap *StandardColorMapMain;
	TAction *Act_ViewAllResources;
	TStandardColorMap *StandardColorMapTools;
	TAction *Act_ResizeWork;
	TActionManager *ActionManagerOther;
	TAction *Act_OtherInfoTaskbarButton;
	TAction *Act_OtherInfoApplicTaskBarButton;
	TAction *Act_FacePage;
	TAction *Act_Update;
	TAction *Act_EditChapter;
	TImage *ImageBackgroundWindow;
	TAction *Act_MailChapt;
	TAction *Act_ImageAndText;
	TAction *Act_Help;
	TAction *Act_Tips;
	TPanel *PanelTools;
	TPageControl *PageControlTools;
	TTabSheet *TabSheetBooks;
	TTabSheet *TabSheetAllCommentsVers;
	TStaticText *STextHeaderListCommentVers;
	TStaticText *STextHeaderFavorteListVers;
	TAction *Act_ReadingPlan;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Act_CloseSheetActiveExecute(TObject *Sender);
	void __fastcall Act_SaveChaptToHTMLExecute(TObject *Sender);
	void __fastcall Act_SearchBibleTextExecute(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall StatusBarMainDrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel,
          const TRect &Rect);
	void __fastcall Act_SetupsApplicExecute(TObject *Sender);
	void __fastcall Act_SelectVersExecute(TObject *Sender);
	void __fastcall TrayIconMainBalloonClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall MBW_PageControlAllChange(TObject *Sender);
	void __fastcall Act_CorcordanceDictionaryGrecExecute(TObject *Sender);
	void __fastcall MBW_PageControlsAllDrawTab(TCustomTabControl *Control, int TabIndex,
          const TRect &Rect, bool Active);
	void __fastcall Act_ProjectSchemeVersExecute(TObject *Sender);
	void __fastcall Act_InfomationsExecute(TObject *Sender);
	void __fastcall Act_ViewAllResourcesExecute(TObject *Sender);
	void __fastcall Act_ResizeWorkExecute(TObject *Sender);
	void __fastcall Act_OtherInfoTaskbarButtonExecute(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Act_FacePageExecute(TObject *Sender);
	void __fastcall Act_UpdateExecute(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall PageControlBibleTextEnter(TObject *Sender);
	void __fastcall Act_EditChapterExecute(TObject *Sender);
	void __fastcall Act_MailChaptExecute(TObject *Sender);
	void __fastcall Act_ImageAndTextExecute(TObject *Sender);
	void __fastcall Act_HelpExecute(TObject *Sender);
	void __fastcall Act_TipsExecute(TObject *Sender);
	void __fastcall ImageBackgroundWindowDragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
	void __fastcall Act_ReadingPlanExecute(TObject *Sender);
private:	// User declarations
	GsLViewCommentsAllClass *pGsLViewCommentsAllClass;
	GsListBoxFavoritiesClass *pGsListBoxFavoritiesClass;
	void __fastcall _AppException(TObject *Sender, Exception *pException);	//Obsługa błędów całej aplikacji
	bool __fastcall _AppHelp(System::Word Command, NativeInt Data, bool &CallHelp);
	void __fastcall _AppOnHint(TObject *Sender);
	void __fastcall _AppMessage(tagMSG &Msg, bool &Handled);
	void __fastcall _CreatePopupTrayIcon();
	void __fastcall _OnClick_PMenuTray(System::TObject* Sender);
	void __fastcall _InitAllTagAndHint();
	void __fastcall _OnDblClick_ListComment(System::TObject* Sender);
	void __fastcall _OnDblClick_ListFavorities(System::TObject* Sender);
	void __fastcall _DisplayHelp(TAction *_pAction);
	//---
public:		// User declarations
	__fastcall TMainBibleWindow(TComponent* Owner);
	virtual __fastcall ~TMainBibleWindow();
};
//---------------------------------------------------------------------------
extern PACKAGE TMainBibleWindow *MainBibleWindow;
//---------------------------------------------------------------------------
#endif
