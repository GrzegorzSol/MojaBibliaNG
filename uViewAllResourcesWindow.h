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
	void __fastcall ImageDisplayResourceDblClick(TObject *Sender);
private:	// User declarations
	float fFactorProp;
	TForm *_pDisplayWindow=nullptr;
	TImage *_pImageScr=nullptr;

	void __fastcall _OnKeyPress(TObject *Sender, System::WideChar &Key);
	GsViewAllResourcesClass *_pGsViewAllResourcesClass;
	void __fastcall _OnSelectItem(System::TObject* Sender, TListItem* Item, bool Selected);
	void __fastcall _DisplaySelectVersAllTrans(const DataItemResources *pDataItemResources);
	void __fastcall _DisplayImage(const UnicodeString _pathImages);
public:		// User declarations
	__fastcall TViewAllResourcesWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TViewAllResourcesWindow *ViewAllResourcesWindow;
//---------------------------------------------------------------------------
#endif
