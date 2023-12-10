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
		static inline TImageList *_GsImgListData=nullptr; //Globalna lista grafik
		static inline TImageList *_GsImgListDataDisable=nullptr; //Globalna lista grafik nieaktywnych
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
		static const inline UnicodeString GsExtendFileTranslateFull="*.pltmb", //Rozszerzenie właściwego pliku z tłumaczeniem biblijnym JAKO WZORZEC!!!
													 GsExtendFileTranslateGrecOrg="*.grtmb",//Stałą z rozszerzeniem pliku z tłumaczeniem oryginalnym, greckim JAKO WZORZEC!!!
													 GsExtendFileTranslateHbrOrg="*.hbtmb",//Stałą z rozszerzeniem pliku z tłumaczeniem oryginalnym, hebrajskim JAKO WZORZEC!!!
													 GsExtendFileTranslateAll="*tmb",//Stałą z końcówką (bez dwuch pierwszych liter) rozszerzenia pliku z KAŻDYM tłumaczeniem JAKO WZORZEC!!!
													 GsExtendNoAsteriskFileTranslateFull=".pltmb", //Rozszerzenie właściwego pliku z tłumaczeniem biblijnym BEZ WZORCA!!!
													 GsExtendNoAsteriskFileTranslateGrecOrg=".grtmb",//Stałą z rozszerzeniem pliku z tłumaczeniem oryginalnym, greckim BEZ WZORCA!!!
													 GsExtendNoAsteriskFileTranslateHbrOrg =".hbtmb",//Stałą z rozszerzeniem pliku z tłumaczeniem oryginalnym, hebrajskim BEZ WZORCA!!!
													 GsExtendNoAsteriskTextInfoTranslate=".mbin"; //Rozszerzenie pliku typu txt z informacją o danym tłumaczeniu BEZ WZORCA!!!
		static UnicodeString inline //--- Nagłówki dla plików html
															 GsHTMLHeaderText="",	//Tekst nagłówka dla tekstu zwykłego
															 GsHTMLTitle="<title>Wybrany rozdział, dla dostępnych tłumaczeń</title>", //[03-08-2023]
															 GsHTMLHeaderSearch="",//Tekst nagłówka dla tekstu, wyniku wyszukiwania
															 GsHTMLHeaderDisplayVer="";//Tekst nagłówka dla tekstu wybranego wersetu
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
		static const inline InfoAllBooks GsInfoAllBooks[GlobalVar::Global_NumberBooks] =
		{													//--- Stary Testament
															InfoAllBooks(1,	"1 Mojżeszowa",									"1Moj",		50), //0
															InfoAllBooks(2, "2 Mojżeszowa",									"2Moj",		40), //1
															InfoAllBooks(3,	"3 Mojżeszowa",									"3Moj",		27), //2
															InfoAllBooks(4,	"4 Księga Mojżeszowa",					"4Moj",		 36), //3
															InfoAllBooks(5,	"5 Księga Mojżeszowa",					"5Moj",		34), //4
															InfoAllBooks(6,	"Księga Jozuego",								"Joz",		24), //5
															InfoAllBooks(7,	"Księga Sędziów",								"Sędź",		21), //6
															InfoAllBooks(8,	"Księga Rut",										"Rut",		4),	 //7
															InfoAllBooks(9,	"1 Księga Samuela",							"1Sam",		31), //8
															InfoAllBooks(10,	"2 Księga Samuela",							"2Sam",		24), //9
															InfoAllBooks(11,	"1 Księga Królewska",						"1Król",	22), //10
															InfoAllBooks(12,	"2 Księga Królewska",						"2Król",	25), //11
															InfoAllBooks(13,	"1 Księga Kronik",							"1Kron",		29), //12
															InfoAllBooks(14,	"2 Księga Kronik",							"2Kron",		36), //13
															InfoAllBooks(15,	"Księga Ezdrasza",							"Ezdr",		10), //14
															InfoAllBooks(16,	"Księga Nechemiasza",						"Nech",		13), //15
															InfoAllBooks(17,	"Księga Estery",								"Est",		10), //16
															InfoAllBooks(18,	"Księga Joba",									"Job",		42), //17
															InfoAllBooks(19,	"Księga Psalmów",								"Ps",			150),//18
															InfoAllBooks(20,	"Przypowieści Salomona",				"Przyp",	31), //19
															InfoAllBooks(21,	"Księga Kaznodziei Salomona",		"Kazn",		12), //20
															InfoAllBooks(22,	"Pieśni nad Pieśniami",					"PnP",		8),	 //21
															InfoAllBooks(23,	"Księga Izajasza",							"Iz",			66), //22
															InfoAllBooks(24,	"Księga Jeremiasza",						"Jer",		52), //23
															InfoAllBooks(25,	"Treny",												"Tren",		5),	 //24
															InfoAllBooks(26,	"Księga Ezechiela",							"Ez",			48), //25
															InfoAllBooks(27,	"Księga Daniela",								"Dan",		14), //26
															InfoAllBooks(28,	"Księga Ozeasza",								"Oz",			14), //27
															InfoAllBooks(29,	"Księga Joela",									"Jo",			3),	 //28
															InfoAllBooks(30,	"Księga Amosa",									"Am",			9),	 //29
															InfoAllBooks(31,	"Księga Abdiasza",							"Abd",		1),	 //30
															InfoAllBooks(32,	"Księga Jonasza",								"Jon",		4),	 //31
															InfoAllBooks(33,	"Księga Micheasza",							"Mich",		7),	 //32
															InfoAllBooks(34,	"Księga Nahuma",								"Nah",		3),	 //33
															InfoAllBooks(35,	"Księga Habakuka",							"Hab",		3),	 //34
															InfoAllBooks(36,	"Księga Sofoniasza",						"Sof",		3),	 //35
															InfoAllBooks(37,	"Księga Aggeusza",							"Agg",		2),	 //36
															InfoAllBooks(38,	"Księga Zachariasza",						"Zach",		14), //37
															InfoAllBooks(39,	"Księga Malachiasza",						"Mal",		3),	 //38
															//--- Nowy Testament
															InfoAllBooks(40,	"Ewangelia Mateusza",						"Mt",			28), //39
															InfoAllBooks(41,	"Ewangelia Marka",							"Mk",			16), //40
															InfoAllBooks(42,	"Ewangelia Łukasza",						"Łk",			24), //41
															InfoAllBooks(43,	"Ewangelia Jana",								"Jan",		21), //42
															InfoAllBooks(44,	"Dzieje Apostolskie",						"DzAp",		28), //43
															InfoAllBooks(45,	"List Pawła do Rzymian",				"Rzym",		16), //44
															InfoAllBooks(46,	"1 List Pawła do Koryntian",		"1Kor",		16), //45
															InfoAllBooks(47,	"2 List Pawła do Koryntian",		"2Kor",		13), //46
															InfoAllBooks(48,	"List Pawła do Galacjan",				"Gal",		6),	 //47
															InfoAllBooks(49,	"List Pawła do Efezjan",				"Efez",		6),	 //48
															InfoAllBooks(50,	"List Pawła do Filipian",				"Filip",	4),	 //49
															InfoAllBooks(51,	"List Pawła do Kolosan",				"Kol",		4),	 //50
															InfoAllBooks(52,	"1 List Pawła do Tesaloniczan",	"1Tes",		5),	 //51
															InfoAllBooks(53,	"2 List Pawła do Tesaloniczan",	"2Tes",		3),	 //52
															InfoAllBooks(54,	"1 List Pawła do Tymoteusza",		"1Tym",		6),	 //53
															InfoAllBooks(55,	"2 List Pawła do Tymoteusza",		"2Tym",		4),	 //54
															InfoAllBooks(56,	"List Pawła do Tytusa",					"Tyt",		3),	 //55
															InfoAllBooks(57,	"List Pawła do Filemona",				"Filem",	1),	 //56
															InfoAllBooks(58,	"List do Hebrajczyków",					"Hbr",		13), //57
															InfoAllBooks(59,	"List Jakuba",									"Jak",		5),	 //58
															InfoAllBooks(60,	"1 List Piotra",								"1Pt",		5),	 //59
															InfoAllBooks(61,	"2 List Piotra",								"2Pt",		3),	 //60
															InfoAllBooks(62,	"1 List Jana",									"1Jan",		5),	 //61
															InfoAllBooks(63,	"2 List Jana",									"2Jan",		1),	 //62
															InfoAllBooks(64,	"3 List Jana",									"3Jan",		1),	 //63
															InfoAllBooks(65,	"List Judy",										"Jud",		1),	 //64
															InfoAllBooks(66,	"Objawienie Jana",							"Obj",		22), //65
															//--- Apokryfy
															InfoAllBooks(67,	"Księga Tobiasza",							"Tob",		14), //66
															InfoAllBooks(68,	"Księga Judyty",								"Judyt",	16), //67
															InfoAllBooks(69,	"Księga I Machabejska",					"1Mach",	16), //68
															InfoAllBooks(70,	"Księga II Machabejska",				"2Mach",	15), //69
															InfoAllBooks(71,	"Księga Mądrości",							"Mądr",		19), //70
															InfoAllBooks(72,	"Księga Syracha",								"Syr",		51), //71
															InfoAllBooks(73,	"Księga Barucha",								"Bar",		6)	 //72
		};	//Tablica struktur InfoAllBooks, opisująca parametry ksiąg biblijnych
		static bool inline IsInitLibrary=false; //Czy została zainicjowana bibliteka (moduł)
		//---
		//Metoda zwraca wskaźnik na globalną listę grafik
		//inline static TImageList *__fastcall GetImageListData() {if(GsReadBibleTextData::IsInitLibrary)	 return GsReadBibleTextData::_GsImgListData; else return 0;}
		static UnicodeString __fastcall GetVersionMainClass(); //Wersja biblioteki GsReadBibleTextClass
		static void __fastcall InitMyBible(TForm *MainWindow); //Inicjalizacja pracy z biblioteką do analizy Pisma Świętego
		static void __fastcall CloseMyBible();	//Zamknięcie bilioteki do analizy Pisma Świętego
		static void __fastcall InitListColors();//Inicjalizacja listy kolorów
		static void __fastcall CreateTreeBooks(TWinControl* _OwnerParent, TPageControl *_PageControl, int _iWidth=260); //Stworzenie drzewa ksiąg i innych objektów biblioteki
		static void __fastcall SetupVariables(); //Ustawienie zmiennych dla klasy
		static unsigned char __fastcall CountTranslates();	//Metoda zwraca ilość tłumaczeń
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
		//Metoda wyświetla zakres wersetów z wybranego tłumaczenia w dowolnym objekcie, klasy TWebBrowser
		static UnicodeString __fastcall DisplayExceptTextInHTML(TWebBrowser *_pWebBrowser, const int iSelectTranslate,
			const UnicodeString ustrInputStartStop, const DataDisplayTextAnyBrowser &DataDisplay);
		//Metoda inicjuje zmienne dotyczące historii [30-07-2023]
		static void InitHistoryList();
		//Metoda dodajaca informacje o otwartym rozdziale do listy historii
		static void AddItemHistoryList(const UnicodeString _ustrTextItem);
		//Metoda wyświetla tekst aktualnej zakładki [20-08-2023]
		static void GetCurentText(UnicodeString &_ustrText);
		//Metoda zwraca surową listę aktualnej zakładki [25-08-2023]
		static void GetCurentListText(THashedStringList *_pHSList);
};
//---------------------------------------------------------------------------
#endif
