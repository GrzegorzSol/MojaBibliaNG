#ifndef uHelpMyBibleWindowH
#define uHelpMyBibleWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <SHDocVw.hpp>
#include <Vcl.OleCtrls.hpp>

struct HelpWindowData
{
	TAction *pAction=nullptr;
};
//---------------------------------------------------------------------------
class THelpMyBibleWindow : public TForm
{
__published:	// IDE-managed Components
	TPanel *PanelImageHelp;
	TImage *ImageHelp;
	TLabel *LabelTitle;
	TPanel *PanelPicture;
	TWebBrowser *WBrowserHelp;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	HelpWindowData _pHelpWindowData;
public:		// User declarations
	__fastcall THelpMyBibleWindow(TComponent* Owner, HelpWindowData &pHelpWindowData);
  virtual __fastcall ~THelpMyBibleWindow();
};
//---------------------------------------------------------------------------
extern PACKAGE THelpMyBibleWindow *HelpMyBibleWindow;
//---------------------------------------------------------------------------
#endif
