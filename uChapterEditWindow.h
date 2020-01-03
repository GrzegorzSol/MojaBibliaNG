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
<<<<<<< HEAD
	GsEditorClass *_pGsEditorClass;
	GsTabSheetClass *_pGsTabSheetClass; //Aktualna aktywna zakładka z rozdziałem
	int _iGetTranslate; //Numer aktualnie wyświetlanego tłumaczenia w zakładce z tekstem
=======
	GsEditorClass *pGsEditorClass;
	GsTabSheetClass *pGsTabSheetClass; //Aktualna aktywna zakładka z rozdziałem
>>>>>>> fbbdb400f4cfa8322c74fdb8d1b4dd727fb5ecc4
public:		// User declarations
	__fastcall TChapterEditWindow(TComponent* Owner, TTabSheet *pTabSheet);
};
//---------------------------------------------------------------------------
extern PACKAGE TChapterEditWindow *ChapterEditWindow;
//---------------------------------------------------------------------------
#endif
