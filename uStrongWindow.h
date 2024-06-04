#ifndef uStrongWindowH
#define uStrongWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TStrongWindow : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TStrongWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TStrongWindow *StrongWindow;
//---------------------------------------------------------------------------
#endif
