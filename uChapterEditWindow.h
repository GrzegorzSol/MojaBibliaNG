#ifndef uChapterEditWindowH
#define uChapterEditWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "GsReadBibleTextClass.h"
//---------------------------------------------------------------------------
class TChapterEditWindow : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
	GsEditorClass *pGsEditorClass;
	GsTabSheetClass *pGsTabSheetClass; //Aktualna aktywna zakładka z rozdziałem
public:		// User declarations
	__fastcall TChapterEditWindow(TComponent* Owner, TTabSheet *pTabSheet);
};
//---------------------------------------------------------------------------
extern PACKAGE TChapterEditWindow *ChapterEditWindow;
//---------------------------------------------------------------------------
#endif
