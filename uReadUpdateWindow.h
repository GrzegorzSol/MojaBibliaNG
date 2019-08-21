//---------------------------------------------------------------------------

#ifndef uReadUpdateWindowH
#define uReadUpdateWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TReadUpdateWindow : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TReadUpdateWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TReadUpdateWindow *ReadUpdateWindow;
//---------------------------------------------------------------------------
#endif
