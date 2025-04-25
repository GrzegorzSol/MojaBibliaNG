#ifndef GsLogicalRelationshipTableH
#define GsLogicalRelationshipTableH
//---------------------------------------------------------------------------
#include <Vcl.ExtCtrls.hpp>

enum {
//--- Numery identyfikacyjne kolorów
			enColorSchemeNum_Line=0,
			enColorSchemeNum_Active,
			enColorSchemeNum_InActive,
			enColorSchemeNum_Rot,
			enColorSchemeNum_Count,
			enTypeChild_Normal=100,
			enTypeChild_Comment
};
/****************************************************************************
*      Stara struktura _ReadWriteDataObject do zapisu i odczytu objektu     *
*****************************************************************************/
//Struktura tymczasowa do zapisu i odczytu pliku z projektem schematu
const int SIZE_ADDR_VERS = 16, //Długość miejsca na adres wersetu
					SIZE_CHILD_COMMENT = 255, //Długość komentarza do pojedyńczego elementu
					NSIZE_TEXT = 255; // Długość tekstu pozycji, w nowej wersji danych do zapisu
const UnicodeString custrOldExtFilesScheme = ".nsvp", // Stare rozszerzenie plików projektu
										custrNewExtFileScheme = ".lsvc", // "logical scheme of verse connection"
										custrProjectNameDefault = "Bez nazwy" + custrNewExtFileScheme;

typedef struct _ReadWriteDataObject
{
	int RW_ID,															// Numer identyfikacyjny
			RW_IDList,													// Pozycja w globalnej liście objektu _GsChildBibleSchemeList, klasy TList
			RW_Left,														//
			RW_Top,															//
			RW_IDListParent;										// Numer identyfikacyjny przodka w głównej liście, lub -1, gdy jest to korzeń
	wchar_t RW_AdressVers[SIZE_ADDR_VERS];	// Adres wersetu
	unsigned char RW_Book, RW_Chapt, RW_Vers, RW_Trans;
	//Nowe pola dodawać na końcu
	wchar_t wchComment[SIZE_CHILD_COMMENT]; //Komentarz do pozycji
} ReadWriteDataObject, *PReadWriteDataObject;
/****************************************************************************
*      Nowa struktura _NewReadWriteDataObject do zapisu i odczytu objektu   *
*****************************************************************************/
typedef struct _NewReadWriteDataObject
{
	int NRW_Type;                           // Typ objektu
	int NRW_ID,															// Numer identyfikacyjny
			NRW_IDList,													// Pozycja w globalnej liście objektu _GsChildBibleSchemeList, klasy TList
			NRW_Left,														//
			NRW_Top,															//
			NRW_IDListParent;										// Numer identyfikacyjny przodka w głównej liście, lub -1, gdy jest to korzeń
	wchar_t NRW_NameVers[SIZE_ADDR_VERS], // Adres wersetu w pozycji
					NRW_Text[NSIZE_TEXT];	// Zawartość tekstowa pozycji
	unsigned char NRW_Trans;
	//Nowe pola dodawać na końcu
	wchar_t NwchComment[SIZE_CHILD_COMMENT]; //Komentarz do pozycji
} NewReadWriteDataObject, *PNewReadWriteDataObject;

/****************************************************************************
*				         Klasa całkowicie PRYWATNA GsChild,								          *
*										  pochodna TGraphicControl.												      *
*****************************************************************************/
class GsChild : public TGraphicControl
{
	friend class GsDrawChildren;
	friend class GsMaster;
	// Kontruktory i destruktor
	__fastcall GsChild(TComponent* Owner, const UnicodeString &custrAdr, const UnicodeString &custrVers);
	__fastcall GsChild(TComponent* Owner, PReadWriteDataObject _PReadWriteDataObject);
	__fastcall GsChild(TComponent* Owner, PNewReadWriteDataObject _PNewReadWriteDataObject);
	__fastcall virtual ~GsChild();
	//---
  TTreeNode *_TreeNodeChild=nullptr;
	GsChild *_pPrevChild=nullptr, // Wskaźnik na przodka
					*_pNextChild=nullptr; // Wskaźnik na następny objekt
  UnicodeString _ustrNameVers, _ustrTextVers;
	protected:
		virtual void __fastcall Paint();
		DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
		DYNAMIC void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
		DYNAMIC void __fastcall MouseMove(System::Classes::TShiftState Shift, int X, int Y);

		void __fastcall _RefreshText(bool bPosition=false); // Pozycjonowanie tekstu w objekcie
    int _TypeObj=enTypeChild_Normal; // Typ objektu
		TList *_pListChildren=nullptr; // Lista potomków
		int _IDChild=-1, // Numer identyfikacyjny pozycji
				_GetStartX=-1, _GetStartY=-1;	// Współrzędne kliknięcia na objekt klasy
		unsigned char _Level=0; // Poziom
		bool _StartMove=false,	// Rozpoczıcie przesuwania
				 _IsActive=false; // Czy aktywny element
    TRect _RectText; // Obszar tekstu
};
/****************************************************************************
*				        Klasa całkowicie PRYWATNA GsDrawChildren,	      						*
*										      pochodna TCustomPanel.														*
*****************************************************************************/
class GsDrawChildren : public TCustomPanel
{
	friend class GsMaster;
	friend class GsChild;
	// Kontruktory i destruktor
	__fastcall GsDrawChildren(TComponent* Owner);
	__fastcall virtual ~GsDrawChildren();
	protected:
		BEGIN_MESSAGE_MAP
			VCL_MESSAGE_HANDLER(WM_ERASEBKGND, TWMEraseBkgnd, _WMErasebackground);
		END_MESSAGE_MAP(TCustomPanel);
		void __fastcall _WMErasebackground(TWMEraseBkgnd &Message);
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
		virtual void __fastcall Paint();
		DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	private:
    Graphics::TBitmap *_pBrushBitmap=nullptr;
		GsChild *_pSelectObject=nullptr,	// Aktualnie aktywny objekt, potrzebny do jego odryswania
																			// (rozpoczecie przesuwania) w metodzie MouseDown() klasy GsChild
						*_pRootObject=nullptr,		// Objekt głównego korzenia
						*_pCutCopyObject=nullptr;    // Objekt aktualnie skopiowany
		TList *_pMainChildrenList=nullptr;   // Płaska lista wszystkich pozycji
		void __fastcall _DeactivationAllItems(); // Kasowanie wszystkich aktywności
		bool __fastcall _OpenOldProject(TFileStream *pFileStream);
		bool __fastcall _OpenNewProject(TFileStream *pFileStream);
		void __fastcall _CalculateNewDimension(GsChild *pGsChild); // Obliczanie nowego rozmiaru
};
/****************************************************************************
*							           Główna klasa GsMaster,											        *
*											pochodna TScrollingWinControl.												*
*****************************************************************************/
class GsMaster : public TScrollingWinControl
{
	friend class GsDrawChildren;
	friend class GsChild;

	public:
		// Kontruktory i destruktor
		__fastcall GsMaster(TComponent* Owner, TTreeView *pTrView=nullptr);
		__fastcall virtual ~GsMaster();
    inline static UnicodeString sustrVersionLogicalRelationshipTable = "0.9.9235.8529";
		// Pola typu __property
		__property TMouseEvent OnMouseDown = {read = FGetSetOnMouseDown, write = FGetSetOnMouseDown};
		// Inne właściwości
		__property GsChild *SelectChildItem {read = FSelectItem, write = FSetChildSelect, default = 0}; // Wskaźnik na aktywną pozycję.
		__property UnicodeString GetSelectText {read = FSelectText, nodefault}; // Tekst w aktywnej pozycji.
		__property TList *GetSelectList {read = FGsChildrensSelectList, nodefault}; // Lista zaznaczonych elementów
		// Metody inline
		void __fastcall AddNewObjectScheme(const UnicodeString &custrAdr, const UnicodeString &custrVers);
		void __fastcall NewProject();
		bool __fastcall OpenProject(UnicodeString &ustrGetFileName);
		bool __fastcall SaveProject(UnicodeString &ustrGetFileName);
		void __fastcall RenameTextItem(const UnicodeString &custrNewAdr, const UnicodeString &custrNewVers); // Zmiana tekstu w wybranej pozycji
		void __fastcall DeleteObject();
		void __fastcall SaveToGfx(const UnicodeString &ustrPathSave);
		void __fastcall SaveToAllText(const UnicodeString &ustrPathSave); // Stworzenie pliku typu txt z zawartością wszystkich pozycji
		void __fastcall CutCopyToPaste();
		bool __fastcall PasteFromCopy();
		// Zmienne dotyczące wyglądu modułu newSchemeVers
		TColor Global_ColorsSchemeTable[enColorSchemeNum_Count];
		int Global_iWidthLineScheme=2; //Szerokość lini
		bool Global_IsTransparent=false; // Przezroczystość objektów
		TList *_pMultiSelectTreeNodes=nullptr; // Lista zaznaczonych pozycji dla multiselect, w drzewie TTreeView
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
		DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
		DYNAMIC bool __fastcall DoMouseWheel(System::Classes::TShiftState Shift, int WheelDelta, const System::Types::TPoint &MousePos);
	private:
		GsDrawChildren *_pGsDrawChildren=nullptr;
		UnicodeString _ustrProjectName;
		void __fastcall _CreateHierarchyText(const GsChild *pChild, TStrings *pStrings);
		bool __fastcall _FindObjectInTree(const GsChild *pChildForComparison, GsChild *pChild);
		// ----- Pola prywatne dla właściwości __property -----
		GsChild *FSelectItem=nullptr; // Wskaźnik na aktywną pozycję.
		UnicodeString FSelectText; // Tekst w aktywnej pozycji.
		TMouseEvent FGetSetOnMouseDown;
		TList *FGsChildrensSelectList=nullptr; // Lista dla wielokrotnego wyboru
		TTreeView *_pTreeView=nullptr;
		void __fastcall FSetChildSelect(GsChild *pGsChild);
};

#endif
