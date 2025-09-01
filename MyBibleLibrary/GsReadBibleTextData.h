#ifndef GsReadBibleTextDataH
#define GsReadBibleTextDataH
//---------------------------------------------------------------------------
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
#include "MyBibleLibrary\MyBibleLibrary.h"
/****************************************************************************
 *						Całkowicie statyczna klasalasa GsReadBibleTextData						*
 ****************************************************************************/
/*
	TWORZENIE NAZW SKŁADOWYCH KLASY GsReadBibleTextData
	Gs + Typ + Data
*/
class GsReadBibleTextData : public TObject
{
	//Klasa GsReadBibleTextData, musi mieć deklaracje przyjaźni, prawie z każdą klasą modułu
	friend class GsReadBibleTextItem;
	friend class GsReadBibleTextClass;	//Przyjaźń z klasą główną
	friend class GsTreeBibleClass;
	friend class GsTabSheetClass;
	friend class GsTabSetClass;
	friend class MyObjectVers;
	friend class GsBarSelectVers;
	friend class GsPanelSelectVers;
  friend class GsControlListVers;
	friend class GsTabSheetSelectVersClass;
	friend class GsLViewDictionaryClass;
	friend class GsListBoxSelectedVersClass;
	friend class GsListBoxFavoritiesClass;
	friend class GsLViewCommentsAllClass;
	friend int __fastcall MySortDir(TStringList* List, int Index1, int Index2);	//dla funkcji wyszukiwania
	//---
	private:
		static void __fastcall GsInitGlobalImageList(TForm *pMainForm);	 //Inicjalizacja zmiennych klasy
		static void __fastcall GsFreeGlobalImageList();	 //Likwidacja zmiennych klasy
		//---
		static inline TImageList *_GsImgListData=nullptr, //Globalna lista grafik 16x16
														 *_GsImgListDataDisable=nullptr, //Globalna lista grafik nieaktywnych 16x16
														 *_GsImgListDataLarge=nullptr; //Globalna lista grafik 32x32
		static inline TPageControl *_GsPageControl=nullptr; //Wskaźnik na objekt klasy TPageControl z zakładkami do wyświetlania tekstów biblinych
		static inline TTaskbar *_GsTaskBar=nullptr;	//Wskaźnik na objekt, klasy TTaskBar
		static inline TBalloonHint *_GsBalloonHint=nullptr; //Globalna klasa podpowiedzi, zdefiniowana w konstruktorze klasy GsTreeBibleClass
		//---	 Wskaźniki na niektóre klasy
		static inline GsTreeBibleClass* pGsTreeBibleClass=nullptr; //Wskaźnik na klasę drzewa ksiąg bibliinych
		static inline GsListBoxFavoritiesClass *pGsListBoxFavoritiesClass=nullptr; //Wskaźnik na klasę listy ulubionych wersetów, w głównym oknie
		static inline GsLViewCommentsAllClass *pGsLViewCommentsAllClass=nullptr; //Wskażnik na klasę listy komentarzy do wersetów, w głównym oknie
		//---
		static inline enReturnError EnErrorCode=enR_NoError;
	public:
		static inline GsReadBibleTextClass* pGsReadBibleTextClass=nullptr;	//Wskaźnik na główną klasę
    static inline GsReadBibleSpecTextClass* pGsReadBibleSpecTextClass=nullptr; //w Wskaxnik na klase tłumaczeń specjalistycznych
		static const inline UnicodeString GsExtendFileTranslateFull="*.pltmb", //Rozszerzenie właściwego pliku z tłumaczeniem biblijnym JAKO WZORZEC!!!
													 GsExtendFileTranslateGrecOrg="*.grtmb",//Stałą z rozszerzeniem pliku z tłumaczeniem oryginalnym, greckim JAKO WZORZEC!!!
													 GsExtendFileTranslateHbrOrg="*.hbtmb",//Stałą z rozszerzeniem pliku z tłumaczeniem oryginalnym, hebrajskim JAKO WZORZEC!!!
													 GsExtendFileTranslateAll="*tmb",//Stałą z końcówką (bez dwuch pierwszych liter) rozszerzenia pliku z KAŻDYM tłumaczeniem JAKO WZORZEC!!!
													 GsExtendNoAsteriskFileTranslateFull=".pltmb", //Rozszerzenie właściwego pliku z tłumaczeniem biblijnym BEZ WZORCA!!!
													 GsExtendNoAsteriskFileTranslateGrecOrg=".grtmb",//Stałą z rozszerzeniem pliku z tłumaczeniem oryginalnym, greckim BEZ WZORCA!!!
													 GsExtendNoAsteriskFileTranslateHbrOrg =".hbtmb",//Stałą z rozszerzeniem pliku z tłumaczeniem oryginalnym, hebrajskim BEZ WZORCA!!!
													 GsExtendNoAsteriskTextInfoTranslate=".mbin"; //Rozszerzenie pliku typu txt z informacją o danym tłumaczeniu BEZ WZORCA!!!
		static UnicodeString inline //--- Nagłówki dla plików html
															 GsHTMLHeaderText="",	// Tekst nagłówka dla tekstu zwykłego
															 GsHTMLTitle="<title>Wybrany rozdział, dla dostępnych tłumaczeń</title>", // [03-08-2023]
															 GsHTMLHeaderSearch="",// Tekst nagłówka dla tekstu, wyniku wyszukiwania
															 GsHTMLHeaderDisplayVer="",// Tekst nagłówka dla tekstu wybranego wersetu
															 GsHTMLJavaScripts="", // Kody Java Script
															 // --- Skrypty Java Script
															 GsHTML_FileJavaSc_SelectWord=""; // Funkcja java script umożliwiająca klikalność słów [25-08-2025]
															 // ---
		static const unsigned char inline GsNumberAllGroups = en_GrSearch_Count,//Ilość grup biblii, do wyszukiwania
															 GsNumberGroups = 3,	//Ilość grup w drzewie struktury bibli
															 //Ilość ksiąg w poszczególnych grupach
															 GsTableNameGroupBook[GsReadBibleTextData::GsNumberGroups] = {39, 27, 7}; //Ilość ksiąg w poszczególnych grupach bibli
		static const inline UnicodeString GsNamesTableNameGroupBook[GsReadBibleTextData::GsNumberGroups] =
			{"Stary Testament", "Nowy Testament", "Księgi Apokryficzne"}; //Nazwy ksiąg w poszczególnych grupack bibli
		static inline GsTabSheetSelectVersClass *GsSheetListVers=nullptr;//Globalny wskażnik na zakładkę z listąwybranych wersetów za pomocą klasy GsBarSelectVers
		//---
		static const inline UnicodeString GsNameAllRanges[en_GrSearch_Count] =
			{"Całe Pismo Święte", "Protestancki kanon Pisma Świętego", "Stary Testament", "Nowy Testament", "Apokryfy", "Własny zakres", "Pojedyńcza księga"}; //Tablica nazw zakresów wyszukiwania
		static const inline PairsGroupBooks GsPairsGroupBible[en_GrSearch_Count] =
		{
			_PairsGroupBooks(0, 72),		//Wszystkie księgi wraz z apokryfami ->_PairsGroupBooks(const char ucStartRange, ucStopRange);
			_PairsGroupBooks(0, 65),		//Wszystkie księgi, bez apokryfów
			_PairsGroupBooks(0, 38),		//Księgi Starego Testamentu
			_PairsGroupBooks(39, 65),		//Księgi Nowego Testamentu
			_PairsGroupBooks(66, 72),		//Księgi apokryficzne
			_PairsGroupBooks(-1, -1),		//Własny zakres
			_PairsGroupBooks(-1, -1)		//Pojedyńcza księga
		}; //Tablica struktur PairsGroupBooks, danych dla grup ksiąg biblijnych,
		static bool inline IsInitLibrary=false; //Czy została zainicjowana bibliteka (moduł)
		//---
		//Metoda zwraca wskaźnik na globalną listę grafik
		//inline static TImageList *__fastcall GetImageListData() {if(GsReadBibleTextData::IsInitLibrary)	 return GsReadBibleTextData::_GsImgListData; else return 0;}
		static UnicodeString __fastcall GetVersionMainClass(); //Wersja biblioteki GsReadBibleTextClass
		static void __fastcall InitGlobalVariables(); //Ustawienie globalnych zmiennych dla całej aplikacji
		static void __fastcall InitMyBible(TForm *MainWindow); //Inicjalizacja pracy z biblioteką do analizy Pisma Świętego
		static void __fastcall CloseMyBible();	//Zamknięcie bilioteki do analizy Pisma Świętego
		static void __fastcall InitListColors();//Inicjalizacja listy kolorów
		static void __fastcall CreateTreeBooks(TWinControl* _OwnerParent, TPageControl *_PageControl, int _iWidth=260); //Stworzenie drzewa ksiąg i innych objektów biblioteki
		static void __fastcall SetupVariables(); //Ustawienie zmiennych dla klasy

		static unsigned char __fastcall CountTranslates();	//Metoda zwraca ilość tłumaczeń
		static unsigned char __fastcall CountPolTranslates(); //Metoda zwraca ilość tłumaczeń polskich // [30-08-2025]
		static void __fastcall GetInfoNameTranslate(const unsigned char i, UnicodeString &NameTranslate); //Zwraca nazwę tłumaczenia o numerze i
		static void __fastcall GetNameIndependentTranslate(const int i, UnicodeString &NameTranslate); //Zwraca nazwę tłumaczenia niezależnie od jego statusu (aktywny, lub nie) //[09-12-2023]
		static void __fastcall WriteCurrentSheetText(const UnicodeString custrPath=0); //Zapisuje zawartość aktualnej zakładki
		static void __fastcall GetTextHTMLCurrentSheet(UnicodeString &_ustrTextHTML); //Metoda wypełnią kodem html, zmienną UnicodeString, z aktualnej zakładki
		static GsReadBibleTextItem *__fastcall GetTranslate(const unsigned char cucNumberTrans); //Metoda zwraca wskaźnik na klasę wybranego tłumaczenia
		//static void __fastcall DisplayListText(TWebBrowser *_pWebBrowser, THashedStringList *_pHListAnyVers, const int iSelectViewInWebBrowser=ciSelectViewAll); //Metoda wyświetla w formie html, dowolną listę wersetów
		static THashedStringList *__fastcall GetSelectBoksInTranslate(GsReadBibleTextItem *pGsReadBibleTextItem, const signed char scIndexBook); //Wyodrębnienie konkretnej księgi(sciIndex), z wybranej struktury tłumaczenia (GetTranslate)
		static unsigned int __fastcall GetCountVer(const int iNumberTrans, const signed char scIndexBook, const unsigned char cucChapt);	//Metoda zwraca ilość wersetów, dla danego tłumaczenie, księgi i rozdziału
		//Metoda zwraca listę wybranego wersetu, dla wszystkich, dostępnych tłumaczeń
		static void __fastcall GetSelectVerAllTranslates(const unsigned char cucBook, const unsigned char cucChapt, const unsigned char cucVers, THashedStringList *_HSListVers);
		//Metoda zwraca dokładny tekst wersetu o konkretnym adresie i tłumaczeniu
		static void __fastcall GetTextVersOfAdress(const unsigned char cucBook, const unsigned char cucChapt, const unsigned char cucVers, const unsigned char cucTrans, UnicodeString &ustrText);
		//Otwarcie zakładki i wczytanie konkretnej księgi i rozdziału
		static void __fastcall OpenSelectBookAndChapter(int _iBook, int _iChapt=0);
		static inline TImageList *__fastcall GetImageList() {return GsReadBibleTextData::_GsImgListData;};
		static void __fastcall LoadFirstChapt(const unsigned char cucBook); //Otwiera pierwszy rozdział wybranej księgi
		static unsigned char __fastcall GetConvertIdToTreeView(const unsigned char cucID); //Tłumaczenie "płaskich" identyfikatorów, na pozycje w objekcie, klasy GsTreeBibleClass
		static TProgressBar *__fastcall GetCurrentNamberChaptOnSheet();	//Metoda zwraca wskaźnik na progresbar miejsca aktualnego rozdziału, w odniesieniu do aktualnej księgi
		static void __fastcall GetAdressFromId(UnicodeString &_ustrResult, int _iBook, int _iChapt, int _iVers=0); //Konwersja z podanych informacji typu int, numeru księgi, rozdziału i wersetu, na ciąg identyfikacyjny (001001001)
		//Metoda udostępnia aktualna listę tekstów wszystkich tłumaczeń z wybranego rozdziału
		static TList *__fastcall GetListAllTrChap();
		//Metoda udostępnia listę wszystkich dostępnych tłumaczeń
		static TList *__fastcall GetGlobalListAllTraslates();
		//Metoda wyświetla zakres wersetów z wybranego tłumaczenia w dowolnym objekcie, klasy TWebBrowser
		static UnicodeString __fastcall DisplayExceptTextInHTML(TWebBrowser *_pWebBrowser, const int iSelectTranslate,
			const UnicodeString ustrInputStartStop, const DataDisplayTextAnyBrowser &DataDisplay);
		//Metoda inicjuje zmienne dotyczące historii [30-07-2023]
		static void InitHistoryList();
		//Metoda dodajaca informacje o otwartym rozdziale do listy historii
		static void AddItemHistoryList(const UnicodeString &_ustrTextItem);
		//Metoda wyświetla tekst aktualnej zakładki [20-08-2023]
		static void GetCurentText(UnicodeString &_ustrText);
		//Metoda zwraca surową listę aktualnej zakładki [25-08-2023]
		static void GetCurentListText(THashedStringList *_pHSList);
};
//---------------------------------------------------------------------------
#endif
