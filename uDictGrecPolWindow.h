//---------------------------------------------------------------------------

#ifndef uDictGrecPolWindowH
#define uDictGrecPolWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "GsReadBibleTextClass\GsReadBibleTextClass.h"
//---------------------------------------------------------------------------
class TDictGrecPolWindow : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
	GsLViewDictionaryClass *_pGsLViewDictionaryClass;
public:		// User declarations
	__fastcall TDictGrecPolWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDictGrecPolWindow *DictGrecPolWindow;
//---------------------------------------------------------------------------
#endif
