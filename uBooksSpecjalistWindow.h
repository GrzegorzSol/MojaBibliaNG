#ifndef uBooksSpecjalistWindowH
#define uBooksSpecjalistWindowH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.ImageList.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdCtrls.hpp>

#include "MyBibleLibrary\MyBibleLibrary.h"
#include <Vcl.ExtCtrls.hpp>
#include <SHDocVw.hpp>
#include <Vcl.OleCtrls.hpp>
//---------------------------------------------------------------------------
class TBooksSpecjalistWindow : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageListSpec;
	TToolBar *ToolBarSpec;
	TPopupMenu *PMenuSelectTrSpec;
	TComboBox *CBoxTranslatesList;
	TComboBox *CBoxBoksList;
	TComboBox *CBoxChaptersList;
	TWebBrowser *WebBrowserSpecText;
	TStaticText *STextInfoLoaded;
	TImageList *ImageListSpecDisable;
	TToolButton *ToolButtonNextChapt;
	TToolButton *ToolButtonPrevChapt;
	TToolButton *ToolButtonSep;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall CBoxSelectAllChange(TObject *Sender);
	void __fastcall ToolButtonChaptClick(TObject *Sender);
private:	// User declarations
	void __fastcall _SelectTranslateSpecExecute(TObject *Sender);
	GsReadBibleTextItem *_pGsReadBibleTextItem=nullptr; //Aktualnie wybrane tłumaczenie
	int _iSelectBoks=-1;
	TImageList *pImageList16=nullptr;
	THashedStringList *_pListSelectChapt=nullptr; // Wybrany rozdział
	inline static int _siIndexSpecWindow;
public:		// User declarations
	__fastcall TBooksSpecjalistWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBooksSpecjalistWindow *BooksSpecjalistWindow;
//---------------------------------------------------------------------------
#endif
