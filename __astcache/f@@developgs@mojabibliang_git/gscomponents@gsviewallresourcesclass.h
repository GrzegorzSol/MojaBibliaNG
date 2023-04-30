#ifndef GsViewAllResourcesClassH
#define GsViewAllResourcesClassH

#include <Vcl.ComCtrls.hpp>
#include "GsReadBibleTextClass\GsReadBibleTextClass.h"
//---------------------------------------------------------------------------
//Dane dla grup
enum {enGroup_Translate, enGroup_Graphics, enGroup_CoomentFiles, enGroup_FavVers, enGroup_Count};

class GsViewAllResourcesClass : public TCustomListView
{
  public:
		__fastcall GsViewAllResourcesClass(TComponent* Owner);
		__fastcall virtual ~GsViewAllResourcesClass();
		//---
		__property TLVSelectItemEvent OnSelectItem = {read=FOnSelectItem, write=FOnSelectItem};
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
		virtual void __fastcall DoSelectItem(TListItem* Item, bool Selected);
		virtual void __fastcall DrawItem(TListItem* Item, const System::Types::TRect &Rect, Winapi::Windows::TOwnerDrawState State);
	private:
		void __fastcall _CreateAllColumns(); //Tworzenie kolumn
		void __fastcall _LoadAllResources(); //Tworzenie kompletnej listy wszystkich zasobów
		void __fastcall _InitAllImage();     //Tworzenie listy obrazów
		//---
		TImageList *_pImages;
		TLVSelectItemEvent FOnSelectItem;
};
//---------------------------------------------------------------------------
#endif
