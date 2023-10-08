#ifndef GsSchemeVersClassH
#define GsSchemeVersClassH

#include <Vcl.ExtCtrls.hpp>
#include "MyBibleLibrary\MyBibleLibrary.h"
//---------------------------------------------------------------------------
//Struktura tymczasowa do zapisu i odczytu pliku z projektem schematu
const int SIZE_ADDR_VERS = 16;
static UnicodeString sustrVersionGsMasterBibleScheme = "0.7.8235.8529";
typedef struct _ReadWriteDataObject
{
	int RW_ID,															//Numer identyfikacyjny
			RW_IDList,													//Pozycja w globalnej liście objektu _GsChildBibleSchemeList, klasy TList
			RW_Left,														//
			RW_Top,															//
			RW_IDListParent;										//Numer identyfikacyjny przodka w głównej liście, lub -1, gdy jest to korzeń
	wchar_t RW_AdressVers[SIZE_ADDR_VERS];	//Adres wersetu
	unsigned char RW_Book, RW_Chapt, RW_Vers, RW_Trans;
} ReadWriteDataObject, *PReadWriteDataObject;
/****************************************************************************
*					 Klasa całkowicie PRYWATNA GsCoreBibleScheme,											*
*										 pochodna TCustomPanel.																	*
*****************************************************************************/
class GsCoreBibleScheme : public TCustomPanel
{
	public:
		__fastcall GsCoreBibleScheme(TComponent* Owner);
		__fastcall virtual ~GsCoreBibleScheme();
	//---
	protected:
		TList *ListChildren=nullptr; //Lista potomków
		int IDChild=-1,
				GetStartX=-1, GetStartY=-1;	//Współrzędne kliknięcia na objekt klasy
		unsigned char Level=0; //Poziom
		bool StartMove=false;	//Rozpoczıcie przesuwania
};
/****************************************************************************
*					 Klasa całkowicie PRYWATNA GsChildBibleScheme,										*
*										 pochodna GsCoreBibleScheme.														*
*****************************************************************************/
class GsScrollBibleScheme;
class GsDrawPanelBibleScheme;
class GsMasterBibleScheme;
class GsChildBibleScheme : public GsCoreBibleScheme
{
	friend class GsDrawPanelBibleScheme;
	friend class GsMasterBibleScheme;
	//---
	__fastcall GsChildBibleScheme(TComponent* Owner, PReadWriteDataObject _PReadWriteDataObject=0);
	__fastcall virtual ~GsChildBibleScheme();
	//---
	unsigned char ucBook, ucChapt, ucVers, ucTrans;
	GsChildBibleScheme *ParentObjectScheme; //Wskaźnik na przodka
	//---
	GsDrawPanelBibleScheme *DrawPanelScheme; //Objekt klasy GsDrawPanelBibleScheme, na którym objekt jest rysowany
	GsScrollBibleScheme *pGsScrollBibleScheme; //Objekt, klasy GsScrollBibleScheme
	GsMasterBibleScheme *pGsMasterBibleScheme; //Główny objekt klasy GsMasterBibleScheme
	//---
	UnicodeString ustrVers; //Adres werset, objektu
	THashedStringList *SListVers; //Lista wersetów ze wszystkich tłumaczeń
	void __fastcall ViewSelectObject(); //Wyświetlenie wersetu wybranego objektu
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
		virtual void __fastcall Paint();
		DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
		DYNAMIC void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
		DYNAMIC void __fastcall MouseMove(System::Classes::TShiftState Shift, int X, int Y);
};
/****************************************************************************
*					 Klasa całkowicie PRYWATNA GsDrawPanelBibleScheme,								*
*										 pochodna TCustomPanel.																	*
*****************************************************************************/
class GsDrawPanelBibleScheme : public TCustomPanel
{
	friend class GsMasterBibleScheme;
	friend class GsScrollBibleScheme;
	friend class GsChildBibleScheme;
	//---
	__fastcall GsDrawPanelBibleScheme(TComponent* Owner);
	__fastcall virtual ~GsDrawPanelBibleScheme();
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
		virtual void __fastcall Paint();
	private:
		GsChildBibleScheme *_pSelectObject,	//Aktualnie aktywny objekt
											 *_pRootObject;		//Okno głównego korzenia
		UnicodeString _ustrSelectNameProject; //Nazwa aktualnego projektu
		TList *_GsChildBibleSchemeList;
		//---
		void __fastcall _AddNewObject();
		void __fastcall _DeleteObject();
		bool __fastcall _OpenProjectObject();
		void __fastcall _SaveProjectObjectToFile();
		void __fastcall _ViewProjectDocument();
};
/****************************************************************************
*								 Główna klasa GsScrollBibleScheme,													*
*												 pochodna TScrollBox.																*
*****************************************************************************/
class GsScrollBibleScheme : public TScrollBox
{
	friend class GsMasterBibleScheme;
	__fastcall GsScrollBibleScheme(TComponent* Owner);
	__fastcall virtual ~GsScrollBibleScheme();
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
	private:
		GsDrawPanelBibleScheme *_pGsDrawPanelBibleScheme;
};
/****************************************************************************
*								 Główna klasa GsMasterBibleScheme,													*
*												 pochodna TScrollBox.																*
*****************************************************************************/
class GsMasterBibleScheme : public TCustomPanel
{
	friend class GsChildBibleScheme;
	friend class GsDrawPanelBibleScheme;
	//---
	public:
		__fastcall GsMasterBibleScheme(TComponent* Owner);
		__fastcall virtual ~GsMasterBibleScheme();
		inline void __fastcall AddNewObjectScheme() {this->_pGsDrawPanelBibleScheme->_AddNewObject();}
		inline void __fastcall DeleteObjectScheme() {this->_pGsDrawPanelBibleScheme->_DeleteObject();}
		inline bool __fastcall OpenProjectObjectScheme() {return this->_pGsDrawPanelBibleScheme->_OpenProjectObject();}
		inline void __fastcall SaveProjectObjectSchemeToFile() {this->_pGsDrawPanelBibleScheme->_SaveProjectObjectToFile();}
		inline void __fastcall ViewProjectDocument() {this->_pGsDrawPanelBibleScheme->_ViewProjectDocument();}
		inline int __fastcall GetCountObjectScheme() {return this->_pGsDrawPanelBibleScheme->_GsChildBibleSchemeList->Count;}
		inline GsEditorClass *__fastcall GetEditorClass() {return pGsEditorClass;}
		inline static UnicodeString __fastcall GetVersionClass() {return Format("Klasa \"GsMasterBibleScheme\" v%s", ARRAYOFCONST((sustrVersionGsReadBibleTextClass)));};	//Metoda inline zwracająca wersje klasy
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
	private:
		GsScrollBibleScheme *_pGsScrollBibleScheme; //Wskaźnik na scrolling i panel do rysowania
		GsBarSelectVers *_pGsBarSelectVers;
		GsDrawPanelBibleScheme *_pGsDrawPanelBibleScheme;
		GsEditorClass *pGsEditorClass;
		TSplitter *pSplitter;
		TLabel *_pVersDisplayText; //Wyświetlenie wybranego wersetu
};

//---------------------------------------------------------------------------
#endif
