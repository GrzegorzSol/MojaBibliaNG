//---------------------------------------------------------------------------

#ifndef uReadUpdateWindowH
#define uReadUpdateWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TReadUpdateWindow : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *LabeledEdCurrentVersion;
	TLabeledEdit *LabeledEdDownLoadversion;
	TStaticText *STextInfos;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	void __fastcall _GetIsUpdateVerify();
  bool __fastcall _DownLoadFileFTP(const UnicodeString _destPathDownload, const UnicodeString _ustrPathFTPFile);
public:		// User declarations
	__fastcall TReadUpdateWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TReadUpdateWindow *ReadUpdateWindow;
//---------------------------------------------------------------------------
#endif
