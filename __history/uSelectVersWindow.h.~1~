//---------------------------------------------------------------------------

#ifndef uSelectVersWindowH
#define uSelectVersWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "MyBibleLibrary\MyBibleLibrary.h"
#include <Vcl.ExtCtrls.hpp> //Główna klasa do pracy z tekstem biblijnym
//---------------------------------------------------------------------------
class TSelectVersWindow : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
	GsPanelSelectVers *_pGsPanelSelectVers=nullptr;
	const unsigned char _InputCucStartBook,
											_InputCucStartChapt,
											_InputCucStarVers;
	bool _InputBSelectComment;
public:		// User declarations
	__fastcall TSelectVersWindow(TComponent* Owner, const unsigned char _cucStartBook=0, const unsigned char _cucStartChapt=0, const unsigned char _cucStarVers=1, bool bSelectComment=false);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectVersWindow *SelectVersWindow;
//---------------------------------------------------------------------------
#endif
