//---------------------------------------------------------------------------

#ifndef uViewAllResourcesWindowH
#define uViewAllResourcesWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "GsComponents\GsViewAllResourcesClass.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TViewAllResourcesWindow : public TForm
{
__published:	// IDE-managed Components
	TRichEdit *REditInfoSelectItem;
	TPanel *PanelViews;
	TPanel *PanelDisplay;
	TSplitter *SplitterDisplay;
	TSplitter *SplitterViews;
	TImage *ImageDisplayResource;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall PanelDisplayResize(TObject *Sender);
private:	// User declarations
  GsViewAllResourcesClass *pGsViewAllResourcesClass;
	void __fastcall _OnSelectItem(System::TObject* Sender, TListItem* Item, bool Selected);
	void __fastcall _DisplayImage(const UnicodeString _pathImages);
public:		// User declarations
	__fastcall TViewAllResourcesWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TViewAllResourcesWindow *ViewAllResourcesWindow;
//---------------------------------------------------------------------------
#endif
