#ifndef uSendingMailWindowH
#define uSendingMailWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.IniFiles.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class TSendingMailWindow : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *LEditAdressMail;
	TPanel *PanelMailSending;
	TButton *ButtSendingMail;
	TLabel *LabelLastUseAddress;
	TComboBox *CBoxLastUseAddress;
	TImageList *ImageListMailSending;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ButtSendingMailClick(TObject *Sender);
	void __fastcall CBoxLastUseAddressChange(TObject *Sender);
private:	// User declarations
	const UnicodeString _ustrTextHTML;
public:		// User declarations
	__fastcall TSendingMailWindow(TComponent* Owner, const UnicodeString &ustrTextHTML);
};
//---------------------------------------------------------------------------
extern PACKAGE TSendingMailWindow *SendingMailWindow;
//---------------------------------------------------------------------------
#endif
