#ifndef uMainWindowH
#define uMainWindowH
//---------------------------------------------------------------------------
#include "GsReadBibleTextClass\GsReadBibleTextClass.h"
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
#include <Vcl.WinXCtrls.hpp> //Główna klasa do pracy z tekstem biblijnym
//---------------------------------------------------------------------------
class TMainBibleWindow : public TForm
{
__published:	// IDE-managed Components
	TActionToolBar *MBW_ActionToolBarMain;
	TActionManager *XMBW_ActionManagerMain;
	TPageControl *MBW_PageControlBibleText;
	TAction *Act_CloseSheetActive;
	TImageList *MBW_ImageListMainActive;
	TImageList *MBW_ImageListMainInactive;
	TAction *Act_SaveChaptToHTML;
	TAction *Act_SearchBibleText;
	TStatusBar *MBW_StatusBarMain;
	TAction *Act_SetupsApplic;
	TAction *Act_SelectVers;
	TBalloonHint *XMBW_BalloonHintMain;
	TTrayIcon *MBW_TrayIconMain;
	TPopupMenu *MBW_PMenuTray;
	TTaskbar *MBW_TaskbarMain;
	TPageControl *MBW_PageControlTools;
	TTabSheet *MBW_TabSheetBooks;
	TTabSheet *MBW_TabSheetMultimedials;
	TCoolBar *MBW_CoolBarMain;
	TActionToolBar *MBW_ActionToolBarTools;
	TAction *Act_CorcordanceDictionaryGrec;
	TTabSheet *MBW_TabSheetAllCommentsVers;
	TImageList *MBW_ImageListSmall;
	TAction *Act_ProjectSchemeVers;
	TStaticText *STextHeaderListCommentVers;
	TStaticText *STextHeaderFavorteListVers;
	TAction *Act_Infomations;
	TStandardColorMap *XMBW_StandardColorMapMain;
	TAction *Act_ViewAllResources;
	TStandardColorMap *XMBW_StandardColorMapTools;
	TAction *Act_ResizeWork;
	TActionManager *XMBW_ActionManagerOther;
	TAction *Act_OtherInfoTaskbarButton;
	TAction *Act_OtherInfoApplicTaskBarButton;
	TSplitView *MBW_SplitViewMain;
	TAction *Act_FacePage;
	TAction *Act_Update;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Act_CloseSheetActiveExecute(TObject *Sender);
	void __fastcall Act_SaveChaptToHTMLExecute(TObject *Sender);
	void __fastcall Act_SearchBibleTextExecute(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall MBW_StatusBarMainDrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel,
          const TRect &Rect);
	void __fastcall Act_SetupsApplicExecute(TObject *Sender);
	void __fastcall Act_SelectVersExecute(TObject *Sender);
	void __fastcall MBW_TrayIconMainBalloonClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall MBW_PageControlAllChange(TObject *Sender);
	void __fastcall MBW_SplitTreeTextCanResize(TObject *Sender, int &NewSize, bool &Accept);
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
private:	// User declarations
	GsLViewCommentsAllClass *pGsLViewCommentsAllClass;
	GsListBoxFavoritiesClass *pGsListBoxFavoritiesClass;
	void __fastcall _AppException(TObject *Sender, Exception *pException);	//Obsługa błędów całej aplikacji
	void __fastcall _AppOnHint(TObject *Sender);
	void __fastcall _CreatePopupTrayIcon();
	void __fastcall _OnClick_PMenuTray(System::TObject* Sender);
	void __fastcall _InitAllTagAndHint();
	void __fastcall _OnDblClick_ListComment(System::TObject* Sender);
	void __fastcall _OnDblClick_ListFavorities(System::TObject* Sender);
	//---
public:		// User declarations
	__fastcall TMainBibleWindow(TComponent* Owner);
	virtual __fastcall ~TMainBibleWindow();
};
//---------------------------------------------------------------------------
extern PACKAGE TMainBibleWindow *MainBibleWindow;
//---------------------------------------------------------------------------
#endif
