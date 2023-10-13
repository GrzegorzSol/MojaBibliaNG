#ifndef GsSearchFavFilesClassH
#define GsSearchFavFilesClassH

#include <Vcl.ComCtrls.hpp>
#include <System.IniFiles.hpp>
//---------------------------------------------------------------------------
// Klasa przeglądania ulubionych plików wyszukiwania
class GsSearchFavFilesClass : public TCustomListView
{
	public:
		__fastcall GsSearchFavFilesClass(TComponent* Owner);
		__fastcall virtual ~GsSearchFavFilesClass();
		//---
		void __fastcall ReadDirectoryFavSearch();
		__property TLVSelectItemEvent OnSelectItem = {read = _FOnSelectItem, write = _FOnSelectItem};
    __property TNotifyEvent OnDblClick = {read=_FOnDblClick, write=_FOnDblClick};
		__property UnicodeString SelectFile = {read = _FustrSelectFile};
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
		void __fastcall DoSelectItem(TListItem* Item, bool Selected);
		DYNAMIC void __fastcall DblClick();

	private:
		TStringDynArray _SDirSearchFilesFav;
		TImageList *_pImages=nullptr;
		THashedStringList *_pHSListSelect=nullptr;
		UnicodeString _FustrSelectFile;

		void __fastcall _InitAllImage();
		void __fastcall _CreateListSelect();

		TLVSelectItemEvent _FOnSelectItem;
		TNotifyEvent _FOnDblClick;
//		TTimer *_FTimerNotify=nullptr;
//		DWORD _FdwWaitStatusNotification;
//		HANDLE _FhChangeHandlesNotification=nullptr;
//		void __fastcall _FTimerNotifyTimer(TObject *Sender);
};
//---------------------------------------------------------------------------
#endif
