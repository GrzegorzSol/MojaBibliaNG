#ifndef uSuperDitionariesWindowH
#define uSuperDitionariesWindowH

#include <System.Actions.hpp>
#include <System.Classes.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include "uGlobalVar.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ControlList.hpp>
#include <Vcl.StdCtrls.hpp>

#include "GsComponents\GsSuperDictionarysClass.h"
#include <SHDocVw.hpp>
#include <Vcl.OleCtrls.hpp>
//---------------------------------------------------------------------------
class TSuperDitionariesWindow : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageListMain;
	TActionManager *ActionManagerMain;
	TActionToolBar *ActionToolBarMain;
	TAction *ActionGrec;
	TAction *ActionHbr;
	TPanel *PanelListStrong;
	TPanel *PanelInfoDisplay;
	TControlList *ControlListStrong;
	TLabel *LabelStrongNumber;
	TLabel *LabelInfoDictionary;
	TPanel *PanelListvers;
	TControlList *ControlListApperances;
	TWebBrowser *WebBrowserImpotance;
	TLabel *LabelApperances;
	TImage *ImageVers;
	TImageList *ImageListSmall;
	TWebBrowser *WebBrowserVers;
	TImage *ImageStrongNumbers;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall ActionTypeStrongExecute(TObject *Sender);
	void __fastcall ControlListStrongBeforeDrawItem(int AIndex, TCanvas *ACanvas,
          TRect &ARect, TOwnerDrawState AState);
	void __fastcall ControlListStrongItemClick(TObject *Sender);
	void __fastcall ControlListApperancesBeforeDrawItem(int AIndex, TCanvas *ACanvas,
          TRect &ARect, TOwnerDrawState AState);
	void __fastcall ControlListApperancesItemClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
	ManagerSuperDictionaries *_pManagerSuperDictionaries=nullptr;
	THashedStringList *_pHListVerses=nullptr;
	UnicodeString __fastcall _SelectVersWordGrec(const UnicodeString &_custrIn);
	UnicodeString __fastcall _SelectVersWordHbr(const UnicodeString &_custrIn);
  int _iSearchNumber=-1, // [07-06-2024]
			_iNumberTranslateGrec=-1, // Numer tłumaczenia greckiego używany do wyświetlania wersetów // [31-07-2024]
			_iNumberTranslateHbr=-1;  // Numer tłumaczenia hebrajskiego używany do wyświetlania wersetów // [31-07-2024]
public:		// User declarations
	__fastcall TSuperDitionariesWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSuperDitionariesWindow *SuperDitionariesWindow;
//---------------------------------------------------------------------------
#endif
