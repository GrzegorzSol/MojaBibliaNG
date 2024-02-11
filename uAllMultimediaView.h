#ifndef uAllMultimediaViewH
#define uAllMultimediaViewH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ControlList.hpp>
#include <System.IniFiles.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class TAllMultimediaView : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PControlAllMultimedia;
	TTabSheet *TabSheetTranslates;
	TTabSheet *TabSheetGraphics;
	TTabSheet *TabSheetComments;
	TTabSheet *TabSheetFavVerses;
	TControlList *CListTranlates;
	TLabel *LabelNameTranlate;
	TControlList *CListComments;
	TControlList *CListGraphics;
	TControlList *CListFavVerses;
	TImage *ImageTranslates;
	TImageList *ImgListAllView;
	TLabel *LabelTypeTranslate;
	TLabel *LabelNameGraphics;
	TImage *ImageGraphics;
	TRichEdit *RichEditInfo;
	TPanel *PanelDisplay;
	TImage *ImageSelectDisplay;
	THeaderControl *HeaderControlTranslates;
	THeaderControl *HeaderControlGraphics;
	THeaderControl *HeaderControlComments;
	THeaderControl *HeaderControlFavVerses;
	TImage *ImageComments;
	TImage *ImageFavVerses;
	TLabel *LabelComments;
	TLabel *LabelFavVerses;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall CListTranlatesBeforeDrawItem(int AIndex, TCanvas *ACanvas,
					TRect &ARect, TOwnerDrawState AState);
	void __fastcall CListGraphicsBeforeDrawItem(int AIndex, TCanvas *ACanvas, TRect &ARect,
          TOwnerDrawState AState);
	void __fastcall CListCommentsBeforeDrawItem(int AIndex, TCanvas *ACanvas, TRect &ARect,
          TOwnerDrawState AState);
	void __fastcall CListFavVersesBeforeDrawItem(int AIndex, TCanvas *ACanvas,
					TRect &ARect, TOwnerDrawState AState);
	void __fastcall CListAllItemClick(TObject *Sender);
	void __fastcall PanelDisplayResize(TObject *Sender);
	void __fastcall ImageSelectDisplayDblClick(TObject *Sender);
	void __fastcall HeaderControlAllSectionResize(THeaderControl *HeaderControl,
          THeaderSection *Section);

private:	// User declarations
	void __fastcall _SetTagsAndHints();
	void __fastcall _DisplayImage(const UnicodeString _pathImages);
	void __fastcall _OnKeyPress(TObject *Sender, System::WideChar &Key);

	void __fastcall _LoadAllTraslates();
	void __fastcall _LoadAllGraphics();
	void __fastcall _LoadAllComments();
	void __fastcall _LoadAllFavVerses();
	void __fastcall _DisplaySelectVersAllTrans(const UnicodeString ustrCodeVers);

	THashedStringList *_pHSListTranslates=nullptr,
										*_pHListGraphics=nullptr,
										*_pHListComments=nullptr,
										*_pHListFavVerses=nullptr;
	float _fFactorProp=0;
	TForm *_pDisplayWindow=nullptr;
	TImage *_pImageScr=nullptr;
public:		// User declarations
	__fastcall TAllMultimediaView(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAllMultimediaView *AllMultimediaView;
//---------------------------------------------------------------------------
#endif
