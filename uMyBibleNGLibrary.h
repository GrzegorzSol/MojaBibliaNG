#ifndef uMyBibleNGLibraryH
#define uMyBibleNGLibraryH
//---------------------------------------------------------------------------
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.IniFiles.hpp>
#include "GsDirect2DClass.h"
//---------------------------------------------------------------------------
/****************************************************************************
*                        Klasa GsListBoxMultiMClass                         *
*****************************************************************************/
class GsListViewMultiMClass : public TCustomListView
{
	friend class GsPanelMultiM;

	__fastcall GsListViewMultiMClass(TComponent* Owner);
	__fastcall virtual ~GsListViewMultiMClass();
	void __fastcall _CreateColumns();
	void __fastcall ClearList(); //Czyszczenie listy
	static int __fastcall SortListFiles(void * Item1, void * Item2); //Sortowanie TList
	//---
	TImageList *_pImageList;
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
	private:
	public:
};
/**************************************************************************************************************************************
*                             Klasa GsPanelMultiM                                																											*
* Klasa tworzy panel z objektami klas: GsListViewMultiMClass - czyli listą grafik																											*
*              												 GsDirect2DClass - klasą do wyświetlania i zarzadzania grafikami i obrazami, za pomocą Direct2D *
* Klasa równierz tworzy zakładke z objektem, klasy GsTabSheetGraphics, na objekcie klasy TPageControl, w głównym oknie aplikacji      *
***************************************************************************************************************************************/
class GsTabSheetGraphics;
class GsPanelMultiM  : public TCustomPanel
{
	friend class GsListViewMultiMClass;
	public:
		__fastcall GsPanelMultiM(TComponent* Owner, TPageControl *_pPControl);
		__fastcall virtual ~GsPanelMultiM();
		inline void __fastcall RefreshListView(){this->_pGsListViewMultiMClass->Invalidate();};
		inline GsListViewMultiMClass *__fastcall GetGsListViewMultiMClass() {return this->_pGsListViewMultiMClass;};
		GsTabSheetGraphics *__fastcall NewSheetOnlyText();
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
		inline GsDirect2DClass *__fastcall GetD2DObject() {return this->pGsDirect2DClass;}
		__fastcall GsTabSheetGraphics(TComponent* Owner);
		__fastcall virtual ~GsTabSheetGraphics();
	private:
		GsDirect2DClass *pGsDirect2DClass;
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
