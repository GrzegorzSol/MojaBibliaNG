#ifndef uDisplayPreviewWindowH
#define uDisplayPreviewWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.IniFiles.hpp>
#include <SHDocVw.hpp>
#include <Vcl.OleCtrls.hpp>
//---------------------------------------------------------------------------
class TDisplayPreviewWindow : public TForm
{
__published:	// IDE-managed Components
	TWebBrowser *WebBrowserPreview;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
	THashedStringList *_pHSListDisplayChapt=nullptr;
  UnicodeString _ustrPreviewText;
public:		// User declarations
	__fastcall TDisplayPreviewWindow(TComponent* Owner);
	void __fastcall SetDisplayPreviewText(const UnicodeString &ustrPreviewText);
};
//---------------------------------------------------------------------------
extern PACKAGE TDisplayPreviewWindow *DisplayPreviewWindow;
//---------------------------------------------------------------------------
#endif
