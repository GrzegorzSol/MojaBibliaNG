//---------------------------------------------------------------------------

#ifndef uSchemeVersWindowH
#define uSchemeVersWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "MyBibleLibrary\GsSchemeVersClass.h"
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ToolWin.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSchemeVersWindow : public TForm
{
__published:	// IDE-managed Components
	TActionToolBar *ActToolBarScheme;
	TImageList *ImgListScheme;
	TImageList *ImgListDisableScheme;
	TActionManager *ActionManagerScheme;
	TAction *ActNewLink;
	TAction *ActDeleteLink;
	TAction *ActSave;
	TAction *ActOpenProject;
	TBalloonHint *BalloonHintScheme;
	TAction *ActCreateFileFromScheme;
	TAction *ActViewEditor;
	TAction *ActRenameObject;
	TAction *ActSetupScheme;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall ActNewLinkExecute(TObject *Sender);
	void __fastcall ActDeleteLinkExecute(TObject *Sender);
	void __fastcall ActSaveExecute(TObject *Sender);
	void __fastcall ActOpenProjectExecute(TObject *Sender);
	void __fastcall ActCreateFileFromSchemeExecute(TObject *Sender);
	void __fastcall ActViewEditorExecute(TObject *Sender);
	void __fastcall ActRenameObjectExecute(TObject *Sender);
	void __fastcall ActSetupSchemeExecute(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
	GsMasterBibleScheme *pGsMasterBibleScheme;
public:		// User declarations
	__fastcall TSchemeVersWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSchemeVersWindow *SchemeVersWindow;
//---------------------------------------------------------------------------
#endif
