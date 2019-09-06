//---------------------------------------------------------------------------

#ifndef uMainH
#define uMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TWindowMainTest : public TForm
{
__published:	// IDE-managed Components
	TButton *ButtUpd;
	void __fastcall ButtUpdClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TWindowMainTest(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWindowMainTest *WindowMainTest;
//---------------------------------------------------------------------------
#endif
