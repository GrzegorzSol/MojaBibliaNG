#ifndef uMyBibleNGLibraryH
#define uMyBibleNGLibraryH
//---------------------------------------------------------------------------
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.IniFiles.hpp>
//#define _TWICIMAGE_ //Czy ma być używane obsługa jpg przez moduł buildera,
											//czy przez mechanizm wbudowany w Windows (Microsoft Windows Imaging Component)
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
	private:
	#if defined(_TWICIMAGE_) //Czy ma być używane obsługa jpg przez moduł buildera,
													 //czy przez mechanizm wbudowany w Windows (Microsoft Windows Imaging Component)
		//void __fastcall _OnProgress(System::TObject* Sender, TProgressStage Stage, System::Byte PercentDone, bool RedrawNow, const System::Types::TRect &R, const System::UnicodeString Msg);
	#endif
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
		TImage *_ImageView;	//Objekt, klasy TImage do wyświetlania grafiki
		//GsUtilityClass *pGsUtilityClass;
		GsListViewMultiMClass *_pGsListViewMultiMClass;
		TSplitter *_pSplitter;
		TPageControl *_pPControlMainWindow; //Objekt klasy TPageControl na głównym oknie aplikacji
		void __fastcall _ImageOnClick(System::TObject* Sender);
};
/****************************************************************************
*                          Klasa GsTabSheetGraphics                         *
*****************************************************************************/
class GsTabSheetGraphics : public TTabSheet //Klasa całkowicie PRYWATNA!
{
	friend class GsPanelMultiM;

	__fastcall GsTabSheetGraphics(TComponent* Owner);
	__fastcall virtual ~GsTabSheetGraphics();
	//---
	void __fastcall _OnMouseWhellUp(System::TObject* Sender, System::Classes::TShiftState Shift, const System::Types::TPoint &MousePos, bool &Handled);
	void __fastcall _OnMouseWhellDown(System::TObject* Sender, System::Classes::TShiftState Shift, const System::Types::TPoint &MousePos, bool &Handled);
	//---
	TScrollBox *_pScrollBox;
	TImage *_pImageFullDisplay;
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
};
//---------------------------------------------------------------------------
#endif
