#ifndef uNewSchemeVersWindowH
#define uNewSchemeVersWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "MyBibleLibrary\GsLogicalRelationshipTable.h"
#include "MyBibleLibrary\MyBibleLibrary.h"
#include <Vcl.ExtCtrls.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TNewSchemeVersWindow : public TForm
{
__published:	// IDE-managed Components
	TActionManager *ActionManagerMain;
	TImageList *ImageListMain;
	TImageList *ImageListMainDis;
	TActionToolBar *ActionToolBarMain;
	TAction *Act_AddItem;
	TAction *Act_DelItem;
	TBalloonHint *BalloonHintMain;
	TAction *Act_SetupsColors;
	TAction *Act_SelectTranslate;
	TAction *Act_Open;
	TAction *Act_Save;
	TAction *Act_RenameItem;
	TAction *Act_NewProject;
	TTreeView *TrViewMain;
	TAction *Act_SaveAtGfx;
	TImageList *ImageListSmall;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Act_AddItemExecute(TObject *Sender);
	void __fastcall Act_DelItemExecute(TObject *Sender);
	void __fastcall Act_SetupsColorsExecute(TObject *Sender);
	void __fastcall Act_SelectTranslateExecute(TObject *Sender);
	void __fastcall Act_OpenExecute(TObject *Sender);
	void __fastcall Act_SaveExecute(TObject *Sender);
	void __fastcall Act_RenameItemExecute(TObject *Sender);
	void __fastcall Act_NewProjectExecute(TObject *Sender);
	void __fastcall Act_SaveAtGfxExecute(TObject *Sender);
	void __fastcall TrViewMainGetImageIndex(TObject *Sender, TTreeNode *Node);
	void __fastcall TrViewMainClick(TObject *Sender);
private:	// User declarations
  void __fastcall _InitHintsAndTags();
	GsMaster *_pGsMasterRel=nullptr;
	GsBarSelectVers *_pGsBarSelectVers=nullptr; //Panel sterowania i wyboru wersetów dla drzewa
	TPanel *_pPanelSetups=nullptr, // Panel ustawień wykresu
				 *_pPanelSelectTranslate=nullptr; // Panel wyboru tłumaczenia
	TColorBox *_pCBSelect=nullptr, *_pCBRoot=nullptr, *_pCBLine=nullptr;
	TSpinEdit *_pSpinEdit=nullptr;
  TCheckBox *pCBoxIsTransparent=nullptr;
	TListBox *pLBox=nullptr;
	TStringList *_SListOldConfig=nullptr;
	//unsigned char _ucTranslate=0;
	void __fastcall _OpenSetupsVisualScheme();
	void __fastcall _OpenSelectTranslate();
  void __fastcall _CloseSetupsPanels(); // Zamykanie paneli konfiguracyjnych
  //void __fastcall _OpenSelectTranslate();
	void __fastcall _OnGetColors(TCustomColorBox *Sender, TStrings *Items);
	void __fastcall _OnAllButtonSetups(System::TObject* Sender);
	void __fastcall _OnMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall _ReadConfig();
	void __fastcall _WriteConfig();
public:		// User declarations
	__fastcall TNewSchemeVersWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNewSchemeVersWindow *NewSchemeVersWindow;
//---------------------------------------------------------------------------
#endif
