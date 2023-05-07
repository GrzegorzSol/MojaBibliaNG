//---------------------------------------------------------------------------

#ifndef uHistoryChaptersOpenH
#define uHistoryChaptersOpenH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ToolWin.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class THistoryOpenChaptersWindow : public TForm
{
__published:	// IDE-managed Components
	TListView *LViewHistoryCh;
	TActionToolBar *ActionToolBarHistoryCh;
	TActionManager *ActionManagerHistoryCh;
	TImageList *ImageListHistoryCh;
	TAction *Act_DeleteSelectItemHistoryCh;
	TImageList *ImageListSmallHistoryCh;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall LViewHistoryChData(TObject *Sender, TListItem *Item);
	void __fastcall LViewHistoryChDataFind(TObject *Sender, TItemFind Find, const UnicodeString FindString,
          const TPoint &FindPosition, Pointer FindData,
          int StartIndex, TSearchDirection Direction, bool Wrap, int &Index);
	void __fastcall LViewHistoryChDataHint(TObject *Sender, int StartIndex, int EndIndex);
	void __fastcall LViewHistoryChDrawItem(TCustomListView *Sender, TListItem *Item,
          TRect &Rect, TOwnerDrawState State);
	void __fastcall Act_DeleteSelectItemHistoryChExecute(TObject *Sender);
	void __fastcall LViewHistoryChDblClick(TObject *Sender);



private:	// User declarations
public:		// User declarations
	__fastcall THistoryOpenChaptersWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THistoryOpenChaptersWindow *HistoryOpenChaptersWindow;
//---------------------------------------------------------------------------
#endif
