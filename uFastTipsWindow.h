#ifndef uFastTipsWindowH
#define uFastTipsWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.WinXCtrls.hpp>
#include <SHDocVw.hpp>
#include <Vcl.OleCtrls.hpp>
//---------------------------------------------------------------------------
class TFastTipsWindow : public TForm
{
__published:	// IDE-managed Components
	TPanel *PanelButtons;
	TPanel *PanelImagehelp;
	TToggleSwitch *TgSwitchVisibleTips;
	TButton *ButtNextTips;
	TButton *ButtPrevTips;
	TImage *ImageTips;
	TWebBrowser *WBrowserTips;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall TgSwitchVisibleTipsClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall ButtNextTipsClick(TObject *Sender);
	void __fastcall ButtPrevTipsClick(TObject *Sender);
private:	// User declarations
	TWICImage *_pWICImage;
	TStringDynArray _SDirListFilesTips;
  unsigned short int _usiIndexFileTips; //Indeks liczenia kolejnego pliku wskazówek
public:		// User declarations
	__fastcall TFastTipsWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFastTipsWindow *FastTipsWindow;
//---------------------------------------------------------------------------
#endif
