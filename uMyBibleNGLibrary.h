#ifndef uMyBibleNGLibraryH
#define uMyBibleNGLibraryH
//---------------------------------------------------------------------------
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.IniFiles.hpp>
#include "GsDirect2DClass.h"
//---------------------------------------------------------------------------
//MOŻLIWE ŻE CAŁA BIBLIOTEKA ZOTANIE PRZENIESIONA DO BIBLIOTEKI GsReadBibleTextClass
/****************************************************************************
*                        Klasa GsListBoxMultiMClass                         *
*****************************************************************************/
class GsListViewMultiMClass : public TCustomListView
{
	friend class GsPanelMultiM;
	__fastcall GsListViewMultiMClass(TComponent* Owner);
	__fastcall virtual ~GsListViewMultiMClass();
	void __fastcall _CreateColumns();
	//static int __fastcall MySort(TStringList* List, int Index1, int Index2);
	void __fastcall ClearList(); //Czyszczenie listy
	static int __fastcall SortListFiles(void * Item1, void * Item2); //Sortowanie TList
	//---
	TImageList *_pImageList;
	//THashedStringList *_pHSListFiles;
	TList *_pListFile; //Lista plików
	//Indeksy początku i końca listy
	int _iLViewStartIndex;
	int _iLViewEndIndex;
	protected:
		virtual bool __fastcall OwnerDataFetch(Comctrls::TListItem* Item, Comctrls::TItemRequest Request);
		virtual bool __fastcall OwnerDataHint(int StartIndex, int EndIndex);
		virtual int __fastcall OwnerDataFind(TItemFind Find, const System::UnicodeString FindString, const System::Types::TPoint &FindPosition,
			void *FindData, int StartIndex, TSearchDirection Direction, bool Wrap);
		virtual void __fastcall DoSelectItem(TListItem* Item, bool Selected);
		virtual void __fastcall DrawItem(TListItem* Item, const System::Types::TRect &Rect, Winapi::Windows::TOwnerDrawState State);
		DYNAMIC void __fastcall ColClick(TListColumn* Column);
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
		//---
    void __fastcall _OnMouseLeave(TObject *Sender);
	private:
};
/****************************************************************************
*                             Klasa GsPanelMultiM                           *
*****************************************************************************/
class GsPanelMultiM  : public TCustomPanel
{
	friend class GsListViewMultiMClass;
	public:
		__fastcall GsPanelMultiM(TComponent* Owner, TPageControl *_pPControl);
		__fastcall virtual ~GsPanelMultiM();
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
	private:
		GsDirect2DClass *pGsDirect2DClass;
		GsListViewMultiMClass *_pGsListViewMultiMClass;
		TSplitter *_pSplitter;
		TPageControl *_pPControlMainWindow; //Objekt klasy TPageControl na głównym oknie aplikacji
		void __fastcall _ImageOnClick(System::TObject* Sender);
};
/****************************************************************************
*                          Klasa GsTabSheetGraphics                         *
*****************************************************************************/
class GsTabSheetGraphics : public TTabSheet
{
	friend class GsPanelMultiM;
	public:
		inline GsDirect2DClass *__fastcall GetD2DObject() {return this->pGsDirect2DClassFull;}
		__fastcall GsTabSheetGraphics(TComponent* Owner);
		__fastcall virtual ~GsTabSheetGraphics();
	private:
		GsDirect2DClass *pGsDirect2DClassFull;
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
};
/****************************************************************************
*                          Klasa GsPanelSelectVersImage                          *
*****************************************************************************/
class GsPanelSelectVersImage  : public TCustomPanel
{
	friend class GsTabSheetGraphics;

	__fastcall GsPanelSelectVersImage(TComponent* Owner);
	__fastcall virtual ~GsPanelSelectVersImage();
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
	private:
    UnicodeString ustrSelectVers;
};
#endif
