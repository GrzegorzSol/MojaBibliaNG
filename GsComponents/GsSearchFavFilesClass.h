#ifndef GsSearchFavFilesClassH
#define GsSearchFavFilesClassH

#include <Vcl.ComCtrls.hpp>
#include <System.IniFiles.hpp>
//---------------------------------------------------------------------------
enum 	{
				enIndexImage16_Delete = 0,
				enImageImage16_Count
			};
// Klasa przeglądania ulubionych plików wyszukiwania
class GsSearchFavFilesClass : public TCustomListView
{
	public:
		__fastcall GsSearchFavFilesClass(TComponent* Owner);
		__fastcall virtual ~GsSearchFavFilesClass();
		//---
		void __fastcall ReadDirectoryFavSearch();
		void __fastcall DeleteSelectFile();
		inline TImageList *__fastcall GetImageList() {return this->_pImages16;};
		//---
		__property TLVSelectItemEvent OnSelectItem = {read = _FOnSelectItem, write = _FOnSelectItem};
    __property TNotifyEvent OnDblClick = {read=_FOnDblClick, write=_FOnDblClick};
		__property UnicodeString SelectFile = {read = _FustrSelectFile};
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
		void __fastcall DoSelectItem(TListItem* Item, bool Selected);
		DYNAMIC void __fastcall DblClick();
		DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	private:
		TStringDynArray _SDirSearchFilesFav;
		TImageList *_pImages=nullptr,
							 *_pImages16=nullptr;
		THashedStringList *_pHSListSelect=nullptr;
    TPopupMenu *_pPopupM=nullptr;
		UnicodeString _FustrSelectFile;

		void __fastcall _InitAllImage();
		void __fastcall _CreateListSelect();
		void __fastcall _OnClick_PMenu(System::TObject* Sender);

		TLVSelectItemEvent _FOnSelectItem;
		TNotifyEvent _FOnDblClick;
//		TTimer *_FTimerNotify=nullptr;
//		DWORD _FdwWaitStatusNotification;
//		HANDLE _FhChangeHandlesNotification=nullptr;
//		void __fastcall _FTimerNotifyTimer(TObject *Sender);
};
//---------------------------------------------------------------------------
#endif
