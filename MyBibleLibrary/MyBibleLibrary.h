/*
					OPIS KLAS BIBLIOTEKI
	Klasa GsReadBibleTextData - Klasa zawierająca dane statyczne, dostępne wszystkim innym klasom. Metody tej klasu służą do zarządzania innymi klasami tej biblioteki,
															i są interfejsem na zewnatrz do posługiwania się pozostałymi klasami, które sa w większości prywatne.
															Jej metody są równierz używane do komunikacji między innymi klasami.
	Klasa MyObjectVers - Klasa z niezbednymi informacjami o każdym wersecie. Objekt tej klasy jest tworzony dla KAŻDEGO wersetu
	Klasa GsReadBibleTextItem - Klasa pojedyńczego tłumaczenia. Objekty tej klasy będą tworzyć listę, wszystkich dostępnych tłumaczeń.
	Klasa GsReadBibleTextClass - Klasa do zarządzania wszystkimi tłumaczeniami dostępnymi w aplikacji.
	KLASA GsTreeNodeClass - Klasa składników, klasy GsTreeBibleClass
	Klasa GsTreeBibleClass - Klasa wyświetlająca w formie drzewa wszystkie księgi biblijne, wraz z apokryfami
	Klasa GsListBoxSelectedVersClass - Klasa z pochodna klasy TCustomListBox, z listą wybieralną wersetów ulubionych, dla	 z aktualnego rozdziału
	Klasa GsTabSheetClass - Klasa pochodna TTabSheet
	Klasa GsTabSetClass - Klasa do wyboru wyswietlanego tłumaczenia, na głównej zakładce, z wybranym rozdziałem
	Klasa GsBarSelectVers - Klasa przycisków na zakładce, z wybranym rozdziałem
	Klasa GsPanelSelectVers - Klasa główna w oknie wyboru pojedyńczego wersetu
	Klasa GsTabSheetSelectVersClass - Klasa pochodna TTabSheet
	Klasa GsListBoxVersClass - Klasa pochodna TCustomListBox, wyświetlająca aktualnie wybrany werset na głównej zakładce okna, w formie listy wybieralnej
	Klasa GsLViewDictionaryClass - Klasa pochodna TCustomListView, jest klasą słownika i konkordancji grecko-polskiej
	Klasa GsLViewCommentsAllClass - Klasa listy wszystkich komentarzy do wersetów biblijnych
	Klasa GsListBoxFavoritiesClass - Klasa listy ulubionych wersetów
*/
#ifndef MyBibleLibraryH
#define MyBibleLibraryH
//---------------------------------------------------------------------------
//#define _TEST_CONTROLLIST_

#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Tabs.hpp>	//TTabSet
#include <System.IniFiles.hpp>
#include <SHDocVw.hpp>			//TWebBrowser
#include <Vcl.OleCtrls.hpp> //TWebBrowser
#include <Vcl.Grids.hpp> //TStringGrid
#include <Vcl.Taskbar.hpp>//TTaskBar
#include "uGlobalVar.h"
#include "GsComponents\GsEditorClass.h"

static UnicodeString sustrVersionGsReadBibleTextClass = "1.0.82632.96566";
enum enReturnError {enR_NoError,					 //Brak błędu
										enR_GSelectBoook=1000	 //Błąd zwracany gdy szukany rozdział nie mieści sie w tłumaczeniu oryginalnym
									 };
const unsigned char cucMaxCountTranslates=12; //Maksymalna ilość tłumaczeń
//Numery ikon dla lsisty typu TImageList GsReadBibleTextData::GsImgListData
enum {//--- Grafika dla drzewa ksiąg biblijnych
			enImageIndex_Root,						//0.Główny korzeń drzew
			enImageIndex_PartBooks,				//1.Grupa ksiąg
			enImageIndex_Book,						//2.Pojedyńcza księga
			enImageIndex_SelectChapter,		//3.Wybór rozdziału
			//--- Przyciski
			enImageIndex_ToNextBook,		//4.Następna księga
			enImageIndex_NextChapter,			//5.Następny rozdział
			enImageIndex_PrevChapter,			//6.Poprzedni rozdział
			enImageIndex_ToPrevBook,		//7.Poprzednia księga
			enImageIndex_DisplayVers,			//8.Wyświetl wybrany werset
			enImageIndex_Translates,			//9.Wybór tłumaczenia
			enImageIndex_SelectVers,			//10.Wybór wiersza
			enImageIndex_InfoHelp,				//11.Informacja i pomoc
			enImageIndex_CopyToSheet,			//12.Przeniesienie wybranego tekstu na zakładkę
			//---Ikony do słownika i korkondancji grecko-polskiej
			enImageIndex_GrecWordColumn,	//13.Obraz kolumny greckiego słowa
			enImageIndex_GrecStrongColumn,//14.Obraz kolumny numeracji Stronga
			enImageIndex_GrecDictionaryColumn, //15.Obraz kolumny tłumaczenia
			enImageIndex_GrecWordItem,		//16.Obraz pozycji w słowniku grecko-polskim
			enImageIndex_SelectFavVerset, //17.Obraz zaznaczania ulubionego wersetu
			enImageIndex_Save,						//18.Obraz zapisywania
			enImageIndex_Delete,					//19.Obraz kasowania
			enImageIndex_ViewSelectText,	//20.Obraz widoku tekstu biblijnego do selekcji wersetów
			enImageIndex_ReadOnlyText,		//21.Obraz widoku tekstu biblijnego tylko do przeglądania
			enImageIndex_EditText,				//22.Obraz rozpoczęcia edycji
			enImageIndex_DisplayInfoTranslates, //23.Obraz wyświetlania informacji o przekładach, lub wybranym przekładzie, rozdziale
			enImageIndex_Count						//Ilość grafik w objekcie GsReadBibleTextData::GsImgListData, typu TImageList
		 };
//Deklaracja niektórych klas
class GsReadBibleTextClass;
class GsTreeBibleClass;
class GsTabSheetSelectVersClass;
class GsReadBibleTextItem;
class GsTabSetClass;
class GsPanelSelectVers;
const int ciSelectViewAll = -1; //Ma wyświetlana cała lista wyników, stała dla metody DisplayListTextHTML()
class GsListBoxFavoritiesClass;
class GsLViewCommentsAllClass;
/*============================================================================
 =													STRUKTURA InfoAllBooks													 =
 ============================================================================*/
typedef struct _InfoAllBooks
				{
					const unsigned char ucIndex;					//Numer księgi
					const UnicodeString FullNameBook;			//Pełna nazwa księgi
					const UnicodeString ShortNameBook;	 //Skrót księgi
					const unsigned char ucCountChapt;			//Ilość rozdziałów
					_InfoAllBooks(unsigned char _ucIndex, UnicodeString _FullNameBook, UnicodeString _ShortNameBook, unsigned char _ucCountChapt) : ucIndex(_ucIndex),
						FullNameBook(_FullNameBook), ShortNameBook(_ShortNameBook), ucCountChapt(_ucCountChapt)
					/**
						OPIS METOD(FUNKCJI): Konstruktor klasy _InfoAllBooks
						OPIS ARGUMENTÓW:
						OPIS ZMIENNYCH:
						OPIS WYNIKU METODY(FUNKCJI):
					*/
					{

					};
				} InfoAllBooks, *PInfoAllBooks;
/*============================================================================
 =													STRUKTURA PairsGroupBooks												 =
 ============================================================================*/
 //Stałe dla tablicy GsReadBibleTextData::GsPairsGroupBible, grup ksiąg dla wyszukiwania
enum enPartBooksSearch
		 {en_GrSearch_FullAll,	//Wszystkie księgi wraz z apokryfami
			en_GrSearch_All,			//Wszystkie księgi, bez apokryfów
			en_GrSearch_Old,			//Księgi Starego Testamentu
			en_GrSearch_New,			//Księgi Nowego Testamentu
			en_GrSearch_Apocr,		//Księgi apokryficzne
			en_UserRange,					//Własny zakres
			en_OneBook,						//Pojedyńcza księga
			en_GrSearch_Count
		 };
typedef struct _PairsGroupBooks
				{
					const signed char ucStartRange, ucStopRange;
					_PairsGroupBooks(signed char _ucStartRange, signed char _ucStopRange) : ucStartRange(_ucStartRange), ucStopRange(_ucStopRange)
					/**
						OPIS METOD(FUNKCJI): Konstruktor klasy _PairsGroupBooks
						OPIS ARGUMENTÓW:
						OPIS ZMIENNYCH:
						OPIS WYNIKU METODY(FUNKCJI):
					*/
					{
					};
				} PairsGroupBooks, *PPairsGroupBooks;
/*============================================================================
 =													STRUKTURA DataToSearch													 =
 ============================================================================*/
typedef struct //Struktura danych jako argument dla metody wyszukiwania
		{
			bool IsRegular;										 //Czy pole należy traktować jako wyrażenie regularne
			UnicodeString ustrRegExSearchText; //Szukana fraza w formie wyrażeń regularnych
			enPartBooksSearch GroupBooksSearch;//Jaka część pisma do przeszukania
			char chSearchTranslate;						 //Numer tłumaczenia do przeszukania. Gdy wszyskie tłumaczenia to -1
			PairsGroupBooks pairToUserSearch;	 //Wskaźnik na parę numerów ksiąg do wyszukania
		} DataSearch, *PDataSearch;
//---------------------------------------------------------------------------
//enum enTypeRangeText {enTypeRange_Vers=100,				//Zakres ograniczony pełnymi adresami wersetów (po 9 znaków)
//											enTypeRange_Chapter,				//Zakres ograniczony tylko adresamo rozdziałów (po 6 znaków)
//											enTypeRange_OnlyOneChapter};//Zakres dotyczy pojedyńczego rozdziału (6 znaków)
typedef struct //Struktura danych jako argument dla wyświetlania tekstu biblijnego w dowolnym objekcie, klasy TWebBrowser
	{
		UnicodeString strBackgroundColor,		//Kolor podkładu
									strNameFont;					//nazwa czcionki
		int iSizeFont;											//Wielkość czcionki strNameFont
		TMemoryStream *pMemoryStream=nullptr;				//Zapis wyniku wyszukiwania jako danych html, do objektu, klasy TMemoryStream
		bool bIsHorizontLine;								//Czy istnieje pozioma linia między wersetami

	} DataDisplayTextAnyBrowser, *PDataDisplayTextAnyBrowser;
/****************************************************************************
 *										KLASA MyObjectVers																		*
 ****************************************************************************/
const int CISIZE_REPLACEADRESS_ISNOTVALIDNUMBER = 3;
class MyObjectVers : public TObject
{
	friend class GsReadBibleTextClass; //Klasa GsReadBibleTextClass ma pełny dostęp
	friend class GsReadBibleTextItem;	 //Klasa GsReadBibleTextItem ma pełny dostęp
	friend class GsHashedStringListItem; //Przyjaźń - klasa GsHashedStringListItem wywołuje destruktor

	__fastcall MyObjectVers(const UnicodeString &HeadVers);
	virtual __fastcall ~MyObjectVers();
	//---
	public:
		UnicodeString BookChaptVers,	//Identfikacja(adres)wersetu w wersji klasycznej (1Moj 1:1)
									AdressString,		//Adres wersetu w wersji zakodowanej (001001001)
									NameTranslate;	//Nazwa tłumaczenia
		wchar_t ReplaceAdressIsNotValidNumber[CISIZE_REPLACEADRESS_ISNOTVALIDNUMBER]; //Dodatek do adresu wersetu(numeru wersetu), gdy w tłumaczeniu znajduje się
																					 //dodatek w formie litery
		unsigned char ucIdTranslate,	//Numer tłumaczenia
									ucBook,		//Numer księgi
									ucChapt,	//Numer rozdziału
									ucVers,		//Numer wersetu
									ucIndexVersOnList;//Indeks wersetu w liście wersetów dla bierzącej księgi
};
/****************************************************************************
 *										 Główna klasa GsReadBibleTextItem											*
 ****************************************************************************/
	//Klasa GsHashedStringListItem
	//Klasa dziedziczy z THashedStringList i jest obsługiwana przez klasę GsReadBibleTextItem
class GsHashedStringListItem : public THashedStringList //[07-08-2023]
{
	friend class GsReadBibleTextItem; //Przyjeźń - klasa GsReadBibleTextItem wywołuje konstruktor
	//---
	__fastcall GsHashedStringListItem();
	__fastcall virtual ~GsHashedStringListItem();
	//---
	virtual void __fastcall Clear();
};
//Typy tłumaczeń (w języku polskim, lub oryginalnym)
enum EnTypeTranslate {enTypeTr_Full=0x10,	//Cały przekład Pisma Świętego
											enTypeTr_Greek,	//Tekst oryginalny Nowego Testamentu w języku greckim
											enTypeTr_Hebrew	//Tekst oryginalny Starego Testamentu w języku hebrajskim
										 };
class GsReadBibleTextItem : public TObject
{
	friend class GsReadBibleTextClass;
	friend class GsReadBibleTextData;
	friend class GsTabSheetClass;
	friend class GsBarSelectVers;
	friend class GsListItemTranslates; //Przyjaźń - GsListItemTranslates wywołuje destruktor
	//---
	GsReadBibleTextItem(const UnicodeString _PathTransl, EnTypeTranslate IdenTypeTranslate, const unsigned char cucIndex);
	virtual ~GsReadBibleTextItem();
	//---
	//Tablica wskaźników do klasy THashedStringList wszystkich ksiąg tłumaczenia, o wielkości równej ilości ksiąg bibli
	GsHashedStringListItem *_pGsHListAllListBooks[GlobalVar::Global_NumberBooks];	 //73 wskaźniki (tablica) na GsHashedStringListItem
	GsHashedStringListItem *__fastcall GetSelectBooks(const unsigned char uiSelectBook=0); //Metoda zwraca wskaźnik na konkrętną księge
	bool IsActiveTranslate;	//Czy tłumaczenie jest aktywne, czyli czy jest wyświetlane
	unsigned char ucCountBooks, //Ilość ksiąg w tłumaczeniu (oryginalne tłumaczenia, katolickie)
								ucStartBook,	 //Od numeru jakiej księgi zaczyna się tłumaczenie
								ucIndexTranslate;//Numer tłumaczenia
	public:
		EnTypeTranslate enTypeTranslate; //Typ tłumaczenia, typu EnTypeTranslate (całe pismo, grecki nt. itd.)
		UnicodeString NameTranslate,	//Nazwa tłumaczenia
									PathInfoTranslate; //Ścieżka do pliku informacji o tłumaczeniu
		int uiAllVersCount;	 //Ilość wszystkich wersetów
};
/****************************************************************************
 *												Klasa GsReadBibleTextClass												*
 ****************************************************************************/
	//Klasa GsListItemTranslates
	//Klasa dziedziczy z TList i jest obsługiwana przez klasę GsReadBibleTextClass
class GsListItemTranslates : public TList //[08-08-2023]
{
	friend class GsReadBibleTextClass; //Przyjaźń - GsReadBibleTextClasswywołuje konstruktora i dectruktora
	//---
	__fastcall GsListItemTranslates();
	__fastcall virtual ~GsListItemTranslates();
	//---
	virtual void __fastcall Clear(); //Tylko wywołanie TList::Clear();
	protected:
		virtual void __fastcall Notify(void * Ptr, TListNotification Action);
};
//Stałe dla metody GetCountTranslates, informującą czy zwracana ilość przekładów będzie dotyczyła wszystkich tłumaczeń,
//tylko polskich, czy oryginalnych
//enum EnTypeGetTranslates {enTypeGTr_All = 0x20, enTypeGTr_Pol, enTypeGTr_Org};
class GsReadBibleTextClass : public TObject
{
	friend class GsTabSheetClass;
	friend class GsTreeBibleClass;
	friend class GsTabSetClass;
	friend class GsReadBibleTextData;
	friend class GsPanelSelectVers;
	friend class GsLViewDictionaryClass;
	friend class GsListBoxSelectedVersClass;
	//---
	GsReadBibleTextClass(const UnicodeString _PathDir);
	virtual ~GsReadBibleTextClass();
		//---
	inline static UnicodeString __fastcall GetVersionClass() {return Format("Biblioteka: \"GsReadBibleTextClass\" v%s", ARRAYOFCONST((sustrVersionGsReadBibleTextClass)));};	//Metoda inline zwracająca wersje klasy
	bool __fastcall GetAllTranslatesChapter(const int iGetBook, const int iGetChap); //Wczytanie wybranego rozdziału dla wszystkich przekładów
	void __fastcall DisplayAllTextInHTML(TWebBrowser *_pWebBrowser, const int iSelectTranslate=-1); //Metoda łączy w jedną całość jako kod Html tekst, ze wszystkich tłumaczeń, wybranej księgi i rozdziału.
	void __fastcall SaveCurrentSheetText(const UnicodeString custrPath=0); //Zapisuje zawartość aktualnej zakładki
	inline TList *__fastcall GetListAllTranslates() {return this->_GsListItemsTranslates;}; //Metoda zwraca wskaźnik na listę wszystkich tłumaczeń
	inline unsigned int __fastcall GetCountTranslates() {return (unsigned int)this->_GsListItemsTranslates->Count;};
	GsReadBibleTextItem *__fastcall GetTranslateClass(const int iNumberTrans); //Metoda zwraca wskaźnik na klasę wybranego tłumaczenia
	void __fastcall _GetInfoNameTranslate(const int i, UnicodeString &NameTranslate); //Zwraca nazwę tłumaczenia o numerze i
	THashedStringList *__fastcall GetSelectBookTranslate(const int iGetTranslate, const int iGetBook); //Metoda zwraca wskażnik THashedStringList na pozycje określonej księgi i tłumaczenia
	THashedStringList *__fastcall GetSelectBookOrgTranslate(int _iBook, const EnTypeTranslate _EnTypeTranslate=enTypeTr_Greek); //Metoda zwraca string listę greckiego tłumaczenia i wybranej, CAŁEJ księgi oryginalnej.
	inline THashedStringList *GetListInterlinearGrec() {return this->_SListInterLinear;};	//Uzyskanie wskaźnika na listę z zawartościa pliku z danymi interlinearnymi, grecko-polskimi
	void __fastcall _ViewSListBibleToHTML(TWebBrowser *_cWebBrowser, THashedStringList *_HStringInput, const DataDisplayTextAnyBrowser &DataDisplay);	//Przekształcenie dowolnej String listy wersetów, w wizualny tekst html
	bool __fastcall _LoadAllTranslates(const UnicodeString _PathDir);	//Załadowanie całego tekstu biblii, z odpowiednim wykonaniem ich podziału.
	void __fastcall _ClearListAllTrChap(const bool bIsRemoveList=false);	//Zwolnienie zawartości listy _ListAllTrChap.

	void __fastcall _GlobalTextDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept);
	void __fastcall _DeleteSelectTranslate(const int iNumberTrans); //Skasowanie wybranego tłumaczenia
	//---
	GsListItemTranslates *_GsListItemsTranslates;	//Lista tłumaczeń. Klas GsReadBibleTextItem
	TList *_ListAllTrChap; //Lista klasy THashedStringList, zawierających tekst wszystkich dostępnych tłumaczeń, z wybranego rodziału.
	THashedStringList *_SListInterLinear; //Objekt, klasy THashedStringList z danymi do wyświetlenia tekstu Nowego Testamentu, w formie interlinearne, grecko-polskiej
	unsigned int uiCountPol, uiCountOryg; //Ilość polskich i oryginalnych tłumaczeń

	public:
		void __fastcall GlobalTextDragDrop(TObject *Sender, TObject *Source, int X, int Y); //Publiczny ze względu na umożliwienie dostępu z głównego okna
};
/****************************************************************************
 *												Klasalasa GsTreeNodeClass													*
 ****************************************************************************/
enum {enTypeNode_Root = 0, //Odpowiada polu Level
			enTypeNode_Group,
			enTypeNode_Book
			};
//Typy głównych korzeni
enum enTypeRoot {enTypeRoot_NoRoot = -1,
								 enTypeRoot_Books = 1000, //Korzeń ksiąg biblijnych
								 enTypeRoot_Resources			//Korzeń zasobów
		 };
class GsTreeNodeClass : public TTreeNode //Klasa całkowicie PRYWATNA!
{
	friend class GsTreeBibleClass;
	friend class GsTabSheetClass;
	//---
	__fastcall GsTreeNodeClass(TTreeNodes* Owner);
	__fastcall virtual ~GsTreeNodeClass();
	//---
	enTypeRoot eTypeRoot;
	unsigned char ucIndexBook,			 //Numer księgi
								ucCountChapt;			 //Ilość rozdziałów
};
/****************************************************************************
 *												Klasalasa GsTreeBibleClass												*
 *							Drzewo wszystkich, dostępnych ksąg biblijnych								*
 ****************************************************************************/
 //Stałe kolejnych sekcji w objekcie this->_pHeaderControl
enum {enHeaderSection_FullName,/* enHeaderSection_ShortName, enHeaderSection_CountChapt,*/ enHeaderSection_Count};
const UnicodeString Global_headersSectionName[] = {"Pełna nazwa księgi", "Skrót księgi", "Ilośc rozdziałów"};
class GsTreeBibleClass : public TCustomTreeView //Klasa cała jest prywatna
{
	friend class GsReadBibleTextClass;
	friend class GsReadBibleTextData;
	//---
	__fastcall GsTreeBibleClass(TComponent* Owner, TPageControl *pPageControl);
	__fastcall virtual ~GsTreeBibleClass();
	//---
	void __fastcall _CreateNodeClass(TCustomTreeView *Sender, TTreeNodeClass &NodeClass);
	GsTreeNodeClass *__fastcall _AddRootNodeObject(const UnicodeString _NameRoot, enTypeRoot _eTypeRoot, void *pObject=0);	//Dodawanie korzenia
	GsTreeNodeClass *__fastcall _AddChildNodeObject(const GsTreeNodeClass* pParent, const UnicodeString ustrNameChild, void *pObject=0); //Dodawanie pozycji do podpozycji
	void __fastcall _OnHint(System::TObject* Sender, TTreeNode* const Node, System::UnicodeString &Hint); //Wyświetlanie podpowiedzi dla poszczególnych pozycji drzewa
	void __fastcall _SelectPopupTreeBooksExecute(TObject *Sender);	//Metoda wywoływana podczas wybranie pozycji w menu podręcznym
	void __fastcall _SectionHeaderResize(THeaderControl* HeaderControl, THeaderSection* Section);
	//---
	TPopupMenu *FPMenuBook;
	TBalloonHint *_pBalloonHint;
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
		DYNAMIC void __fastcall DblClick();
		DYNAMIC void __fastcall DoContextPopup(const Types::TPoint &MousePos, bool &Handled); //Wirtualna metoda tworzenia podręcznego menu
		DYNAMIC void __fastcall DragOver(System::TObject* Source, int X, int Y, System::Uitypes::TDragState State, bool &Accept);
		DYNAMIC void __fastcall Resize(void);
		DYNAMIC void __fastcall Delete(TTreeNode* Node);
		virtual bool __fastcall CustomDrawItem(TTreeNode* Node, TCustomDrawState State, TCustomDrawStage Stage, bool &PaintImages); //Własny wygląd objektu
		virtual bool __fastcall CustomDraw(const System::Types::TRect &ARect, TCustomDrawStage Stage);
		virtual bool __fastcall IsCustomDrawn(TCustomDrawTarget Target, TCustomDrawStage Stage);	//Bez tej metody własnwe rysowanie objektu jest niemożliwe
		virtual void __fastcall GetImageIndex(TTreeNode* Node); //Przyporządkowywanie ikon poszczarólnym gałęziom
		//---
		void __fastcall _OnMouseLeave(TObject *Sender);
};
/****************************************************************************
*											Klasa GsListBoxSelectedVersClass											*
*****************************************************************************/
class GsListBoxSelectedVersClass : public TCustomListBox
{
	friend class GsTabSheetClass;
	public:
		__fastcall GsListBoxSelectedVersClass(TComponent* Owner);
		__fastcall virtual ~GsListBoxSelectedVersClass();
	protected:
		void __fastcall DrawItem(int Index, const TRect &Rect, TOwnerDrawState State);
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
		DYNAMIC void __fastcall Click();
		DYNAMIC void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	private:
		int iRIndex;	//Aktywna pozycja, po kliknięciu prawym przyciskiem myszy, lub -1
};
/****************************************************************************
 *													KLASA GsTabSheetClass														*
 ****************************************************************************/
class GsTabSheetClass : public TTabSheet
{
	friend class GsTreeBibleClass;
	friend class GsTabSetClass;
	friend class GsReadBibleTextClass;
	friend class GsReadBibleTextData;
	friend class GsListBoxSelectedVersClass;
	//---
	__fastcall GsTabSheetClass(TComponent* Owner);
	__fastcall virtual ~GsTabSheetClass();
	//---
	bool __fastcall _NextChapter();
	bool __fastcall _PrevChapter();
	void __fastcall _OnClickButton(System::TObject* Sender);
	void __fastcall _OnSelectBoxChapter(System::TObject* Sender);
	void __fastcall _OnSelectChaptCBoxDrawItem(Vcl::Controls::TWinControl* Control, int Index, const System::Types::TRect &Rect, Winapi::Windows::TOwnerDrawState State);
	void __fastcall _OnSaveComments(System::TObject* Sender);
	void __fastcall _GetHTMLText(UnicodeString &_ustrTextHTML); //Metoda wypełnią kodem html, zmienną UnicodeString, z aktualnej zakładki
	void __fastcall _GetText(UnicodeString &_ustrText); //Metoda wypełnią tekstem, zmienną UnicodeString, z aktualnej zakładki
	void __fastcall _GetListText(THashedStringList *_pHSListChapt);//Metoda wypełnia lstę listą z aktualnej zakładki [25-08-2023]
	void __fastcall _DisplayInfosTranslates(const int iTab=-1); //Metoda wyświetla informacje o przekładach i wybranym rozdziale

	void __fastcall _InitToolBarAllButtons(TPanel *pPanelParent); //Inicjalizacja głównego objektu klasy TToolBar ze wszystkimi przyciskami
	void __fastcall _InitToolBarViewText(TPanel *pPanelParent); //Inicjalizacja objektu klasy TToolbar do zmieniania widoków wyświetlanych wersetów
	void __fastcall _InitCBoxChaptersSelect(TPanel *pPanelParent); //Inicjalizacja objektu klasy TComboBox do wybierania rozdziałów w bierzacej zakładce
	void __fastcall _InitPanelInfoTranslation(); //Panel z objektami informacyjnymi o wybranym tłumaczeniu
	void __fastcall _InitPanelTextBible(TPanel *pPanelParent); //Kontrolki dotyczące tekstu biblijnego: TProgressBar,
																															//TWebBrowser, GsListBoxSelectedVersClass, GsEditorClass
	void __fastcall _OnDocumentComplete(System::TObject* ASender, const _di_IDispatch pDisp, const System::OleVariant &URL); //[31-07-2023]

	void __fastcall _InitTabSetDisplayTranslates(); //Zakładki z wyborem sposobu wyświetlania tłumaczeń
	//---Objekty na zakładce
	TToolBar *pToolBar, *pToolBarText;
	GsTabSetClass	*pGsTabSetClass; //Klasa zakładek, tłumaczeń
	TWebBrowser *pWebBrowser,
							*pWebBrowserInfoTranslations;
	TComboBox *pComboBox; //Lista do wyboru konkretnego rodziału, już bybranej księgi
	TProgressBar *pProgressBar; //Pionowy wskaźnik, umiejscowienia pozycji w rozdziale

	UnicodeString ustrHtmlText; //Tekst html aktualnie wczytanego rozdziału z wybranej księgi

	THashedStringList *pHSListActualText; //Lista surowa aktualnie przegladanego rozdziału 25-08-2021
																				//Będzie służyła do wyświetlania w objekcie klasy TControlList, który zastąpi sposób wyświetlania w formie html ???
	GsListBoxSelectedVersClass *pLBoxSelectText;	//Lista ulubionych wersetów
	GsEditorClass *pGsEditorClass;							 //Edycja komentarza do wybranego wersetu
	TSplitter *pSplitterEd;
	TPanel *pPanelInfoTraslates;
	//--- Niektóre przyciski na TToolbarach
	TToolButton *pToolButtonEdit,	//Przycisk do edycji
							*pToolButtonInfoTranslates;//Przycisk do informacji o przekładach
	public:
		unsigned char _ShucIndexBook,				//Numer księgi
									_ShucIndexChapt;			//Numer rozdziału
		TTabSet* __fastcall GetTabSet();		//Wyłuskanie wskażnika na zakładki tłumaczeń
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
};
/****************************************************************************
 *													KLASA GsTabSetClass															*
 ****************************************************************************/
class GsTabSetClass : public TTabSet //Klasa cała jest prywatna
{
	 friend class GsTabSheetClass;
	 //---
	 __fastcall GsTabSetClass(TComponent* Owner);
	 __fastcall virtual ~GsTabSetClass();
	 //---
	 void __fastcall _OnChange(System::TObject* Sender, int NewTab, bool &AllowChange);
	 //---
	 bool bIsCreate; //Objekt został stworzony
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
};
/**********************************************************************************
 *														KLASA GsBarSelectVers																*
 *	Klasa wizualna wyboru dowolnej księgi,																				*
 *	rozdziału i wersetu, oraz tłumaczenia																					*
 **********************************************************************************/
class GsBarSelectVers : public TToolBar //Klasa całkowicie prywatna
{
	friend class GsPanelSelectVers;
	public:
		__fastcall GsBarSelectVers(TComponent* Owner, const unsigned char _cucBook=0, const unsigned char _cucChapt=0,
															 const unsigned char _cucVers=1, bool bSelectComment=false);
		__fastcall virtual ~GsBarSelectVers();
		//---
		inline UnicodeString __fastcall GetSelectVers() {return this->_pSTextSelect->Caption;};
		THashedStringList *__fastcall GetSListVers(); //Wypełnienie string listy this->_pHSListSelectVers, wszystkich tłumaczeń, wybranym wersetem
		void __fastcall SetSListVers(THashedStringList *pToFillSList); //Wypełnienie string listy zewnętrznej wybanym wersetem ze wszystkich tłumaczeń
		inline int __fastcall GetSelectTranslate() {return this->_FucSelectTranslate;} //Metoda zwraca numer wybranego tłumaczenia
		void __fastcall GetSelectAdress(unsigned char &_usBook, unsigned char &_usChapt, unsigned char &_usVers, unsigned char &_ucTranslate); //Informacja o adresie wersetu
	private:
	bool _bFirstResize,	//Startowe skalowanie (true)
			 _FbBarSelectComment; //Wybrałeś komentarz w liście komentarzy w głównym oknie
			 //_bIsNextStart; //Pierwsze uruchomienie (true, póżniej false)
	TToolButton *_pButBooks,			//Wybór księgi
							*_pButChapt,			//Wybór rozdziału
							*_pButVers,				//Wybór wersetu
							*_pButTranslates, //Wybór tłumaczenia
							*_pButDisplay,		//Pokaż wybrany werset
							*_pButNextVers,		//Następny werset
							*_pButPrevVers,		//Poprzedni werset
							*_pButCopyToSheet,//Przeniesienie tekstu na zakładkę
							*_pSelectFavCBox,//Czy werset należy do ulubionych
							*_pSaveNoteToVers,//Zapis komentarza do aktualnego wersetu
							*_pDeleteNoteVers;//Kasowanie komentarza do aktualnego wersetu
	//---
	TPopupMenu *_pPMenuBooks;			//Popup menu z listą ksiąg biblijnych
	TPopupMenu *_pPMenuChapt;			//Popup menu z listą rozdziałów
	TPopupMenu *_pPMenuVers;			//Popup menu z listą wersetów
	TPopupMenu *_pPMenuTranslates;//Popup menu z listą tłumaczeń
	TStaticText *_pSTextSelect;	//Wybrany werset
	//TBalloonHint *_pBalloonHint;
	//--- Wybrane pozycje z TPopupMenu
	unsigned char _FucSelectBook,							//Wybrana księga
								_FucSelectChapt,						//Wybrany rozdział
								_FucSelectVers,							//Wybrany werset
								_FucSelectTranslate;				//Wybrane tłumaczenie

	THashedStringList *_pHSListSelectVers; //THashedStringLista wszystkich tłumaczeń wybranego wersetu
	GsPanelSelectVers *_pGsPanelSelectVers; //Wskaźnik na rodzica
	//---
	void __fastcall _CreatePMenuBooks(); //Tworzenie stałych popup menu (wszystkich tłumaczeń, księgi biblijne, rozdziałów i wersetów)
	void __fastcall _OnClick_PMenu(System::TObject* Sender);
	void __fastcall _OnClickDisplay(System::TObject* Sender);
	void __fastcall _OnClickButtonSelect(System::TObject* Sender);
	void __fastcall _OnClickNavigateVers(System::TObject* Sender);
	void __fastcall _OnClickCopyToSheet(System::TObject* Sender);
	void __fastcall _OnClickSaveComment(System::TObject* Sender);
	void __fastcall _OnClickDeleteComment(System::TObject* Sender);
	void __fastcall _DisplayVers(); //Wyświetlenie wybranego tekstu
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
		DYNAMIC void __fastcall Resize();
};
/****************************************************************************
 *													KLASA GsPanelSelectVers													*
 *	Klasa wizualna do wyświetlania wybranego wersetu,												*
 *	wybranego za pomocą objektu, klasy GsBarSelectVers											*
 ****************************************************************************/
class GsPanelSelectVers	 : public TCustomPanel
{
	friend class GsBarSelectVers;
	public:
		__fastcall GsPanelSelectVers(TComponent* Owner, const unsigned char _cucBook=0, const unsigned char _cucChapt=0, const unsigned char _cucVers=1, bool bSelectComment=false);
		__fastcall virtual ~GsPanelSelectVers();
		//---
		//Widoczność (true), lub nie (false), możliwości wyboru tłumaczenie
		__property bool IsVisibleSetTranslate = {read=FIsVisibleSetTranslate, write=_SetDisplayTranslate, default=true}; //Czy ma być wyświetlany przycisk, z rozwijalną listą, do wyboru przekładu, domyślnie true, czyli tak.
		__property bool IsEditComments = {read=FIsEditComments, write=_SetEditComments, default=true}; //Czy ma być wyświetlany objekt do pisania komentarzy, domyślnie nie (false)
		__property bool IsVisibleAccessories = {read=FIsVisibleAccessories, write=_SetIsVisibleAccessories, default=false}; //Czy mają być wyświetlane dodatkowe prayciski: kopiowania zawartości na nowa zakładkę, wyświetlanie odznaczania ulubionego wersetu
		__property bool IsVisibleIONoteEditors = {read=FVisibleIONoteEditors, write=_SetVisibleIONoteEditors, default=false};//Czy mają być wyświetlane w edytorze notatek przyciski (IO) zapisu i odczytu.
		//Czy objekt klasy GsBarSelectVers, ma być wyświetlanu sam bez panelu z zawartością wybranego wersetu, domyślnie tak (true)
		__property bool IsPanelText = {read=FIsPanelText, write=_SetDisplayText, default=true};
		inline void __fastcall DisplayStart() {this->_pGsBarSelectVers->_DisplayVers();}; //Wyświetla wybrany werset
		//---
		unsigned char ucSetBook,
									ucSetChapt,
									ucSetVers;
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
	private:
		GsBarSelectVers *_pGsBarSelectVers;
		GsEditorClass *_pEditComment; //Zlikwidować, lub zamienić nas wskaźnik, na klasę GsEditorClass
		bool FIsVisibleSetTranslate=true, //Czy ma być wyświetlany przycisk, z rozwijalną listą, do wyboru przekładu, domyślnie true, czyli tak.
				 FIsPanelText=true,			 //Czy objekt klasy GsBarSelectVers, ma być wyświetlanu sam bez panelu z zawartością wybranego wersetu, domyślnie tak (true)
				 FIsEditComments=true,	 //Czy ma być wyświetlany objekt do pisania komentarzy, domyślnie nie (true)
				 FIsVisibleAccessories,//Czy mają być wyświetlane dodatkowe prayciski: kopiowania zawartości na nowa zakładkę, wyświetlanie odznaczania ulubionego wersetu
				 FVisibleIONoteEditors,//Czy mają być wyświetlane w edytorze notatek przyciski zapisu i odczytu.
				 FbSelectComment; //Wybrałeś komentarz w liście komentarzy w głównym oknie
		TWebBrowser *_pWebBrowser;
		TStringGrid *_pSGridInterlinearVers; //Objekt klasy TStringGrid z interlinearnym widokiem polsko-gerckim
		TPanel *_pPanelCBoxes; //Panel przełączników
		TCheckBox *_pCBoxIsEditComment,	 // TUTAJ
							*_pCBoxIsDisplayTranslates,
							*_pCBoxIsAccess;
		//---
		void __fastcall _OnClickCBoxes(System::TObject* Sender);
		void __fastcall _SetDisplayTranslate(bool bIsDisplay);
		void __fastcall _SetEditComments(bool bIsComments);
		void __fastcall _SetDisplayText(bool bIsDisplay);
		void __fastcall _SetVisibleIONoteEditors(bool bIsDisplayIO);
		void __fastcall _SetIsVisibleAccessories(bool bIsAccess);
		void __fastcall _DisplayInterlinear(const unsigned char cucBook, const unsigned char cucChapt, const unsigned char cucVers); //Wyświetlenie interlinearnego układu dla greckiego oryginału
};
/****************************************************************************
 *										 KLASA GsTabSheetSelectVersClass											*
 *	Klasa wizualna zakładki do wyświetlania zawartości ulubionych wersetów	*
 ****************************************************************************/
class GsListBoxVersClass; //Lista wybranych wersetów dodanych z objektu, klasy GsPanelSelectVers (INNY WYBÓR!!!)
class GsTabSheetSelectVersClass : public TTabSheet //Klasa całkowicie PRYWATNA!
{
	friend class GsBarSelectVers;
	__fastcall GsTabSheetSelectVersClass(TComponent* Owner);
	__fastcall virtual ~GsTabSheetSelectVersClass();
	//---
	//void __fastcall _AddSelectvers()
	GsListBoxVersClass *pGsListBoxVersClass;
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
};
/****************************************************************************
*												 Klasa GsListBoxVersClass														*
*			Wyświetlanie wybranego wersetu w głównej zakładce, w głównym oknie		*
*****************************************************************************/
class GsListBoxVersClass : public TCustomListBox
{
	public:
		__fastcall GsListBoxVersClass(TComponent* Owner);
		__fastcall virtual ~GsListBoxVersClass();
	protected:
		void __fastcall DrawItem(int Index, const TRect &Rect, TOwnerDrawState State);
		void __fastcall MeasureItem(int Index, int &Height);
		DYNAMIC void __fastcall Resize(void);
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
	private:
};
/****************************************************************************
*		 Klasa całkowicie PRYWATNA DataGrecWordDictClass, pomocnicz klasa				*
*									dla klasy GsLViewDictionaryClass.													*
*****************************************************************************/
//--- Całkowicie prywatna klasa, służaca jako dane do każdego słowa w słowniku grecko-polskim
class DataGrecWordDictClass : public TObject
{
	friend class GsLViewDictionaryClass;

	DataGrecWordDictClass()
	{
		this->pHSListVers = new THashedStringList();
		if(!this->pHSListVers) throw(Exception("Błąd funkcji THashedStringList"));
	};
	virtual ~DataGrecWordDictClass()
	{
		delete this->pHSListVers; this->pHSListVers = nullptr;
	};
	//---
	bool IsDataEmpty;	//Domyślnie true.Klasa jeszcze nie wypełniona, przy pierwszym wypełnieniu, zmienia wartość na false
	UnicodeString ustrGrecName,			//Nazwa greckiego słowa
								ustrDictPol,			//Tłumaczenie
								ustrStrongNumber; //Numer stronga
	THashedStringList *pHSListVers; //Lista wersetów, w których dane słowo występuje
};
/****************************************************************************
*												 Klasa GsLViewDictionaryClass												*
*							 Klasa słownika i konkordancji grecko-polskiej								*
*****************************************************************************/
class GsLViewDictionaryClass : public TCustomListView
{
	public:
		__fastcall GsLViewDictionaryClass(TComponent* Owner);
		__fastcall virtual ~GsLViewDictionaryClass();
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
		virtual bool __fastcall OwnerDataFetch(Comctrls::TListItem* Item, Comctrls::TItemRequest Request);
		virtual bool __fastcall OwnerDataHint(int StartIndex, int EndIndex);
		virtual int __fastcall OwnerDataFind(TItemFind Find, const System::UnicodeString FindString, const System::Types::TPoint &FindPosition,
			void * FindData, int StartIndex, TSearchDirection Direction, bool Wrap);
		virtual void __fastcall DoSelectItem(TListItem* Item, bool Selected);
		virtual void __fastcall DrawItem(TListItem* Item, const System::Types::TRect &Rect, Winapi::Windows::TOwnerDrawState State);
	private:
	//Indeksy początku i końca listy
		int _iLViewStartIndex;
		int _iLViewEndIndex;
		TWebBrowser *_pWBrowseResult;	//Wyświetlanie wyników, dla wybranego słowa
		TList *_pListWordGrec; //Lista objektów, klasy DataGrecWordDictClass
		void __fastcall _CreateAllColumns(); //Tworzenie kolumn
};
/***************************************************************************************
 *												Klasa ListComments																					 *
 *	Klasa niewizualna pojedyńczej pozycji komentarza dla wersetu											 *
 *	Lista objektów tej klasy stanowi zawartość objektu, klasy GsLViewCommentsAllClass	 *
 *												Klasa GsLViewCommentsAllClass																 *
 *	Klasa wizualna listy, która znajduje sie na zkładce																 *
 *	okna gównego MBW_TabSheetAllCommentsVers;																					 *
 ***************************************************************************************/
class ListComments : public TObject//Struktura pojedyńczego komentarz
{
	friend class GsLViewCommentsAllClass;
	ListComments(const UnicodeString _ustrName);
	virtual ~ListComments();
	public:
		UnicodeString LC_FileName, //Nazwa pliku z komentarzem
									LC_BookChaptVers,	//Identfikacja(adres)wersetu
									LC_ustrComment;		//Właściwy komentarz
		unsigned char LC_ucBook,	 //Numer księgi
									LC_ucChapt,	 //Numer rozdziału
									LC_ucVers;	 //Numer wersetu
	private:

};
//---
class GsLViewCommentsAllClass : public TCustomListView
{
	public:
		__fastcall GsLViewCommentsAllClass(TComponent* Owner);
		__fastcall virtual ~GsLViewCommentsAllClass();
		//---
		ListComments *__fastcall GetSelectComent(int iIndex); //Wybrana pozycja komentarza
		void __fastcall ReloadAllVersComments(bool _bStartup=true); //Wyczyszcenie i pomowne załadowanie listy wersetów
		__property TNotifyEvent OnDblClick = {read=FOnDblClick, write=FOnDblClick};
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
		virtual bool __fastcall OwnerDataFetch(Comctrls::TListItem* Item, Comctrls::TItemRequest Request);
		virtual bool __fastcall OwnerDataHint(int StartIndex, int EndIndex);
		virtual int __fastcall OwnerDataFind(TItemFind Find, const System::UnicodeString FindString, const System::Types::TPoint &FindPosition,
			void * FindData, int StartIndex, TSearchDirection Direction, bool Wrap);
		virtual void __fastcall DoSelectItem(TListItem* Item, bool Selected);
		DYNAMIC void __fastcall DblClick();
		virtual void __fastcall DrawItem(TListItem* Item, const System::Types::TRect &Rect, Winapi::Windows::TOwnerDrawState State);
	private:
		//Indeksy początku i końca listy
		int _iLViewStartIndex;
		int _iLViewEndIndex;
		TList *_ListComments; //Lista komentarzy w formie struktur PListComments
		TNotifyEvent FOnDblClick;
};
/****************************************************************************
*												Klasa GsListBoxFavoritiesClass											*
*****************************************************************************/
class GsListBoxFavoritiesClass : public TCustomListBox
{
	public:
		__fastcall GsListBoxFavoritiesClass(TComponent* Owner);
		__fastcall virtual ~GsListBoxFavoritiesClass();
		void __fastcall ReLoadFavList();
		__property TNotifyEvent OnDblClick = {read=FOnDblClick, write=FOnDblClick};
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
		DYNAMIC void __fastcall DblClick();
		void __fastcall DrawItem(int Index, const TRect &Rect, TOwnerDrawState State);
	private:
		TNotifyEvent FOnDblClick;
};
#endif
