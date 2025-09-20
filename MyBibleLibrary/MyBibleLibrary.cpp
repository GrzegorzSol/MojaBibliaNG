/*
					OPIS KLAS BIBLIOTEKI
	Klasa GsReadBibleTextData - Klasa zawierająca dane statyczne, dostępne wszystkim innym klasom. Metody tej klasu służą do zarządzania innymi klasami tej biblioteki,
															i są interfejsem na zewnatrz do posługiwania się pozostałymi klasami, które sa w większości prywatne.
															Jej metody są równierz używane do komunikacji między innymi klasami.
	Klasa MyObjectVers - Klasa z niezbednymi informacjami o każdym wersecie. Objekt tej klasy jest tworzony dla KAŻDEGO wersetu
	Klasa GsAbsReadBibleText	- Klasa abstrakcyjna bedąca przodkiem większości klas modułu
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
	Klasa GsControlListVers - Klasa pochodna TCustomControlListVers, wyświetlająca aktualnie wybrany werset na głównej zakładce okna, w formie listy wybieralnej
	Klasa GsLViewDictionaryClass - Klasa pochodna TCustomListView, jest klasą słownika i konkordancji grecko-polskiej
	Klasa GsLViewCommentsAllClass - Klasa listy wszystkich komentarzy do wersetów biblijnych
	Klasa GsListBoxFavoritiesClass - Klasa listy ulubionych wersetów
*/

#pragma hdrstop

#include "MyBibleLibrary\MyBibleLibrary.h"
#include <System.IOUtils.hpp>
#include <System.StrUtils.hpp>
#include "MyBibleLibrary\GsReadBibleTextData.h"
#include "MyBibleLibrary\MyBibleCoreDataImages.h" //Dane dla grafiki (Pojedyńcch obrazów i list obrazów)
//---------------------------------------------------------------------------
#pragma package(smart_init)
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug("");
#endif
[30-07-2023]
*/
// Stałe uzywane do wyboru wyswietlania widoku interlinearnego dla Nowego Testament
const int ciMinSelectBookNewTestament = 38, // Minimum numeru ksiegi Nowego Testamenu
					ciMaxSelectBookNewTestament = 66; // Maksimum numeru ksiegi Nowego Testamentu
///////////////////////////////////////////////////////////////////////////////////
// 	 KLASY PRZEZNACZONE DO PRACY ZE SDANDARTOWYMI TŁUMACZENIAMI PISMA SWIETEGO 	 //
///////////////////////////////////////////////////////////////////////////////////
/****************************************************************************
 *										KLASA MyObjectVers																		*
 ****************************************************************************/
__fastcall MyObjectVers::MyObjectVers(const UnicodeString &HeadVers)
/**
	OPIS METOD(FUNKCJI): Konstruktor klasy MyObjectVers
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->AdressString = HeadVers.SubString(1, 9);		//Adres wersetu 001001001
	this->ucBook = HeadVers.SubString(1, 3).ToIntDef(1) - 1;//Księgi są numerowane w pliku z tłumaczeniem od 1, a teblice od 0.
	this->ucChapt = HeadVers.SubString(4, 3).ToIntDef(1);
	this->ucVers = HeadVers.SubString(7, 3).ToIntDef(1);

	if(this->ucVers == 0)
	{
		int iNextVerify=0;
		wcsncpy(this->ReplaceAdressIsNotValidNumber, HeadVers.SubString(7, 3).LastChar(), 1);
		this->ucVers = HeadVers.SubString(7, 2).ToIntDef(0);

		if(this->ucVers == 0)
		{
			wcsncpy(this->ReplaceAdressIsNotValidNumber, HeadVers.SubString(8, 2).c_str(), 2);
			this->ucVers = HeadVers.SubString(7, 1).ToIntDef(0);
		}
	}
	//----- Tworzenie adresu wersetu
	this->BookChaptVers = Format("%s %d:%d%s", ARRAYOFCONST((AppCTable_InfoAllBooks[this->ucBook].ShortNameBook, this->ucChapt, this->ucVers, this->ReplaceAdressIsNotValidNumber )));
}
//---------------------------------------------------------------------------
__fastcall MyObjectVers::~MyObjectVers()
/**
	OPIS METOD(FUNKCJI): Destruktor klasy MyObjectVers
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//
}
/****************************************************************************
 *													Klasa GsReadBibletextItem												*
 ****************************************************************************/
//Klasa GsHashedStringListItem //[07-08-2023]
//Klasa dziedziczy z THashedStringList i jest obsługiwana przez klasę GsReadBibleTextItem
__fastcall GsHashedStringListItem::GsHashedStringListItem()
/**
	OPIS METOD(FUNKCJI): Konstruktor klasy GsHashedStringListItem
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
__fastcall GsHashedStringListItem::~GsHashedStringListItem()
/**
	OPIS METOD(FUNKCJI): Destruktor klasy GsHashedStringListItem
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->Clear();
}
//---------------------------------------------------------------------------
void __fastcall GsHashedStringListItem::Clear()
/**
	OPIS METOD(FUNKCJI): Wirtualna klasa wywolywana podczas czyszczenia całej zawartosci
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	MyObjectVers *_pMyOjectVers=nullptr;

	for(int i=0; i<this->Count; ++i)
	{
		_pMyOjectVers = dynamic_cast<MyObjectVers *>(this->Objects[i]);
		if(_pMyOjectVers) {delete _pMyOjectVers; _pMyOjectVers = nullptr;}
	}

	THashedStringList::Clear();
}
	//=========================================================================
__fastcall GsReadBibleTextItem::GsReadBibleTextItem(const UnicodeString &_PathTransl, EnTypeTranslate IdenTypeTranslate, const unsigned char cucIndex)
	: IsActiveTranslate(true),	//Czy tłumaczenie jest aktywne, czyli czy jest wyświetlane
		enTypeTranslate(IdenTypeTranslate),
		FullPathTranslate(_PathTransl) //Kompletna ścieżka do tłumaczenia
/**
	OPIS METOD(FUNKCJI): Konstruktor klasy GsReadBibletextItem
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH: UnicodeString _PathTransl - Scieżka dostępu do tłumaczenia
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	THashedStringList *_tempHStringList=nullptr; //Hashed String lista z całym tłumaczeniem
	int iGetBook=0;
	//Ścieżka do pliku informacji o tłumaczeniu
	this->PathInfoTranslate = Format("%s", ARRAYOFCONST(( TPath::ChangeExtension(_PathTransl, GsReadBibleTextData::GsExtendNoAsteriskTextInfoTranslate) )));

	try
	{
		this->uiIndexTranslate = cucIndex; //Indeks tłumaczenia
		_tempHStringList = new THashedStringList();	//String lista z całym tłumaczeniem
		if(!_tempHStringList) throw(Exception("Błąd inicjalizacji listy na pojedyńczą księge tłumaczenia"));
		_tempHStringList->LoadFromFile(_PathTransl, TEncoding::UTF8); //Wczytanie całego tłumaczenia
		this->uiAllVersCount = _tempHStringList->Count - 1;	 //Ilość wszystkich wersetów(pierwszy werset to nazwa tłumaczenia)
		this->NameTranslate = _tempHStringList->Strings[0]; //Nazwa tłumaczenia
		//----- Zarezerwowanie tablicy objektów, klasy GsHashedStringListItem dla poszczególnych ksiąg.
		for(int iIndex=0; iIndex<GlobalVar::Global_NumberBooks; ++iIndex)
		{
			//Tworzenie tablicy wskaźników do klasy GsHashedStringListItem, dla każdej księgi, wczytanego tłumaczenia
			this->_pGsHListAllListBooks[iIndex] = new GsHashedStringListItem(); //Inicjowanie 73 wskaźników
			if(!this->_pGsHListAllListBooks[iIndex]) throw(Exception("Błąd inicjalizacji listy na pojedyńczą księge tłumaczenia"));
		}
		//----- Wczytanie poszczególnych ksiąg do poszczególnych string list
		for(int iIndex=1; iIndex<_tempHStringList->Count; ++iIndex)
		//Przegląd całego tekstu tłumaczenia, w celu wyodrębnienia poszczególnych ksiąg, i umieszczenia ich w odpowiednich string listach
		//Pętla rozpoczyna się od pozycji 1, gdyż pozycja 0, to nazwa tłumaczenia.
		{
			//KSIĘGI LICZONE SĄ OD ZERA!!! Odczytanie numeru księgi
			iGetBook = _tempHStringList->Strings[iIndex].SubString(1, 3).ToInt() - 1; //Odczyt numeru księgi. Księgi są numerowane w pliku z tłumaczeniem od 1, a teblice od 0.
			MyObjectVers *pMyObjectVers = new MyObjectVers(_tempHStringList->Strings[iIndex].SubString(1, 9)); //Objekt klasy MyObjectVers dodawany do każdego wersetu
			if(!pMyObjectVers) throw(Exception("Błąd inicjalizacji danych dodawanych, do każdego wersetu"));
			pMyObjectVers->NameTranslate = this->NameTranslate; //Nazwa tłumaczenia
			pMyObjectVers->ucIdTranslate = cucIndex; //Indeks tłumaczenia
			if(iIndex==1) this->ucStartBook = iGetBook; //Początkowy numer księgi (od jakiej księgi zaczyna się tłumaczenie)
			//Umieszczenie tekstu zależnie od numeru księgi, w odpowiedniej string liście, o indeksie równym numerowi księgi
			this->_pGsHListAllListBooks[iGetBook]->AddObject(_tempHStringList->Strings[iIndex], pMyObjectVers);
			//Indeks wersetu w liście wersetów dla bierzącej księgi
			pMyObjectVers->ucIndexVersOnList = this->_pGsHListAllListBooks[iGetBook]->Count - 1;
		}
		this->ucCountBooks = iGetBook - this->ucStartBook + 1; //Ilość ksiąg w tłumaczeniu
		//czy tłumaczenie zawiera księgi apokryficzne
		if(this->ucCountBooks == GlobalVar::Global_NumberBooks) this->IsApocryfic = true; else this->IsApocryfic = false;
//    #if defined(_DEBUGINFO_)
//			GsDebugClass::WriteDebug(Format("Apocryfik %d", ARRAYOFCONST(((int)this->IsApocryfic))));
//		#endif
	}
	__finally
	{
		if(_tempHStringList) {delete _tempHStringList; _tempHStringList = nullptr;}
	}
}
//---------------------------------------------------------------------------
__fastcall GsReadBibleTextItem::~GsReadBibleTextItem()
/**
	OPIS METOD(FUNKCJI): Destruktor klasy GsReadBibletextItem
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsHashedStringListItem *_pGsHSList=nullptr;
	MyObjectVers *_pMyOjectVers=nullptr;
	for(int iIndex=0; iIndex<GlobalVar::Global_NumberBooks; ++iIndex)
	//Kolejne wskaźniki na objekt GsHashedStringListItem, z tablicy wszystkich ksiąg tłumaczenia
	{
		_pGsHSList = this->_pGsHListAllListBooks[iIndex]; //Wskaźnik na objekt THashedStringList, z listą wszystkich wersetów danej księgi
		//Zwolnienie całej GsHashedStringListItem(y) z całą księgą (wszystkimi wersetami)
		if(_pGsHSList) {delete _pGsHSList; _pGsHSList = nullptr;}
	}
}
//---------------------------------------------------------------------------
GsHashedStringListItem *__fastcall GsReadBibleTextItem::GetSelectBooks(const unsigned char uiSelectBook)
/**
	OPIS METOD(FUNKCJI): Metoda zwraca wskaźnik na konkrętną księge
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//if(uiSelectBook<0 || (uiSelectBook>=GsReadBibleTextData::GsNumberBooks)) return 0; //Przekroczenie zakresu
	if(uiSelectBook < this->ucStartBook || (uiSelectBook >= (this->ucCountBooks + this->ucStartBook))) return 0;
	return this->_pGsHListAllListBooks[uiSelectBook];
}
/****************************************************************************
 *										 Główna klasa GsReadBibleTextClass											*
 ****************************************************************************/
	//Klasa GsListItemTranslates //[08-08-2023]
	//Klasa dziedziczy z TList i jest obsługiwana przez klasę GsReadBibleTextClass
__fastcall GsListItemTranslates::GsListItemTranslates()
/**
	OPIS METOD(FUNKCJI): Konstruktor klasy GsListItemTranslates
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
__fastcall GsListItemTranslates::~GsListItemTranslates()
/**
	OPIS METOD(FUNKCJI): Destruktor klasy GsListItemTranslates
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->Clear();
}
//---------------------------------------------------------------------------
void __fastcall GsListItemTranslates::Clear()
/**
	OPIS METOD(FUNKCJI): Wirtualna klasa wywolywana podczas czyszczenia całej zawartosci
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TList::Clear();
}
//---------------------------------------------------------------------------
void __fastcall GsListItemTranslates::Notify(void *Ptr, TListNotification Action)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsReadBibleTextItem *pGsReadBibleTextItem = static_cast<GsReadBibleTextItem *>(Ptr);
	if(!pGsReadBibleTextItem) return;
	//---
	if(Action == lnDeleted)
	{
		if(pGsReadBibleTextItem) {delete pGsReadBibleTextItem; pGsReadBibleTextItem = nullptr;}
	}
	else if(Action == lnAdded)
	{
	}
	else if(Action == lnExtracted)
	{
	}

	TList::Notify(Ptr, Action);

}
//===========================================================================
//NUMER TŁUMACZENIA LICZYMY OD ZERA. NUMER KSIĘGI LICZYMY OD ZERA!!!
int __fastcall MySortDir(TStringList* List, int Index1, int Index2)
/**
	OPIS METOD(FUNKCJI): Sortowanie listy wszystkich tłumaczeń. Oryginalne tłumaczenia ZAWSZE są na końcu!!!
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
	NUMER TŁUMACZENIA LICZYMY OD ZERA. NUMER KSIĘGI LICZYMY OD ZERA!!!
*/
{
	UnicodeString ustr1 = TPath::GetExtension(List->Strings[Index1]),
								ustr2 = TPath::GetExtension(List->Strings[Index2]);
	//---
	if((ustr1 != GsReadBibleTextData::GsExtendNoAsteriskFileTranslateFull) && (ustr2 == GsReadBibleTextData::GsExtendNoAsteriskFileTranslateFull))
	{
		return 1;
	}
	else if((ustr2 != GsReadBibleTextData::GsExtendNoAsteriskFileTranslateFull) && (ustr1 == GsReadBibleTextData::GsExtendNoAsteriskFileTranslateFull))
	{
		return -1;
	}
	else
	{
		return AnsiCompareText(List->Strings[Index1], List->Strings[Index2]);
	}
	return 0;
}
//---------------------------------------------------------------------------
GsReadBibleTextClass::GsReadBibleTextClass(const UnicodeString &_PathDir)
/**
	OPIS METOD(FUNKCJI): Konstruktor klasy ReadBibleTextClass
	OPIS ARGUMENTÓW: UnicodeString _PathDir - Scieżka dostępu do katalogu wszustich tłumaczeń
									 TMemo *pMemoDebug - Wskaźnik na klasę TMemo, na której będą wyświetlane informacje podczas debugowania.
																			 Domyślnie wskaźnik jest równy 0, czyli brak debugowania
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(GsReadBibleTextData::pGsReadBibleTextClass)
		throw(Exception("Dokonano już inicjalizacji objektu GsReadBibleTextClass"));
	//---
	GsReadBibleTextData::pGsReadBibleTextClass = this;	//Wskaźnik na główną klasę
	//GsReadBibleTextData::GsInitGlobalImageList();	 //Inicjalizacja listy ikon
	//--- Inicjalizacja listy wszystkich tłumaczeń
	this->_GsListItemsTranslates = new GsListItemTranslates();
	if(!this->_GsListItemsTranslates) throw(Exception("Błąd inicjalizacji objektu GsListItemTranslates"));
	//String lista opisów wszystkich tłumaczeń, niezależnie od aktywacji tłumaczenia
	this->_pSListAllNamesTranslates = new TStringList(); //[09-12-2023]
	if(!this->_pSListAllNamesTranslates) throw(Exception("Błąd inicjalizacji objektu TStringList")); //[09-12-2023]
	//--- Inicjalizacja listy THashedStringList, wybranego rozdziału, wszystkich tłumaczeń,
	//--- więc ilość elementów listy równa się ilości elementów listy this->_ListItemsTranslates
	this->_ListAllTrChap = new TList();
	if(!this->_ListAllTrChap) throw(Exception("Błąd allokacji TList"));
	//Objekt, klasy THashedStringList z danymi do wyświetlenia tekstu Nowego Testamentu, w formie interlinearne, grecko-polskiej
	this->_SListInterLinear = new THashedStringList();
	if(!this->_SListInterLinear) throw(Exception("Błąd allokacji THashedStringList."));
	this->_LoadAllTranslates(_PathDir);//Załadowanie całego tekstu biblii, z odpowiednim wykonaniem ich podziału
}
//--------------------------------------------------------------------------
GsReadBibleTextClass::~GsReadBibleTextClass()
/**
	OPIS METOD(FUNKCJI): Destruktor klasy ReadBibleTextClass
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//String lista opisów wszystkich tłumaczeń, niezależnie od aktywacji tłumaczenia //[09-12-2023]
	if(this->_pSListAllNamesTranslates) {delete this->_pSListAllNamesTranslates; this->_pSListAllNamesTranslates = nullptr;} //[09-12-2023]
	//Likwidacja listy wszystkich, dostępnych tłumaczeń
	if(this->_GsListItemsTranslates) {delete this->_GsListItemsTranslates; this->_GsListItemsTranslates = nullptr;} //[09-12-2023]
	//--- Usuwanie listy z objektami, klasy ThashedstringList, zawierającymi tekst wszystkich dostępnych
	//		tłumaczeń i wybranego rozdziału
	this->_ClearListAllTrChap(true); //Lista wybranego rozdziału i księgi, jest czyszczona i likwidowana!!!
	//Likwidacja objektu, klasy THashedStringList z danymi do wyświetlenia tekstu Nowego Testamentu, w formie interlinearne, grecko-polskiej
	if(this->_SListInterLinear) {delete this->_SListInterLinear; this->_SListInterLinear = nullptr;}
	GsReadBibleTextData::GsFreeGlobalImageList();	 //Likwidacja zmiennych klasy
}
//---------------------------------------------------------------------------
bool __fastcall GsReadBibleTextClass::_LoadAllTranslates(const UnicodeString &_PathDir)
/**
	OPIS METOD(FUNKCJI): Załadowanie wszystkich plików tłumaczeń, oprócz tłumaczeń, które zostały wykluczone w pilku konfiguracji
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!TDirectory::Exists(_PathDir)) throw(Exception("Niewłaściwy katalog z tłumaczeniami"));	//Jeśli nie istnieje katalog z księgami to upuść metodę
	EnTypeTranslate _enTypeTranslate; //Typ tłumaczenia, typu EnTypeTranslate
	GsReadBibleTextItem *pGsReadBibleTextItem=nullptr;
	this->uiCountPol=0; this->uiCountOryg=0;
	TStringList *pSListExcludeTrans = new TStringList();
	if(!pSListExcludeTrans) throw(Exception("Błąd inicjalizacji objektu TStringList"));
	//Odczyt z pliku ini, tłumaczeń wykluczonych
	pSListExcludeTrans->CommaText = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_TranslatesSection_Main, GlobalVar::GlobalIni_ExcludeTranslates, "");
	//Odczyt wszystkich dostępnych tłumaczeń
	GlobalVar::SDirTranslatesList = TDirectory::GetFiles(_PathDir, GsReadBibleTextData::GsExtendFileTranslateAll, 0);
	//Tworzenie string listy wszystkich możliwych tłumaczeń, a następnie posortowanie ich ze względu na typ.
	//Oryginalne tłumaczenia ZAWSZE są na końcu!!!
	TStringList *pSortedListFileTrans = new TStringList();
	if(!pSortedListFileTrans) throw(Exception("Błąd inicjalizacji objektu TStringList"));
	for(int i=0; i<GlobalVar::SDirTranslatesList.Length; ++i) {pSortedListFileTrans->Add(GlobalVar::SDirTranslatesList[i]);}
	pSortedListFileTrans->CustomSort(MySortDir); //Sortowanie tłumaczeń
	GlobalVar::SDirTranslatesList = pSortedListFileTrans->ToStringArray();
	UnicodeString ustrNameTranslate; //[09-12-2023]
	//---
	//for(int i=0; i<pSortedListFileTrans->Count; ++i)
	for(int i=0; i<pSortedListFileTrans->Count; ++i)
	{
		//Dodanie opisów tłumaczeń, niezależnie od ich aktyawacji
		ustrNameTranslate = TPath::GetFileName(pSortedListFileTrans->Strings[i]); //[09-12-2023]
		this->_pSListAllNamesTranslates->Add(ustrNameTranslate); //[09-12-2023]

		//Nie wczytywanie tłumaczeń, które są na liście wykluczeń
		if(pSListExcludeTrans->IndexOf(ustrNameTranslate) > -1) continue;
		//Inicjowanie wszystkich dostępnych tłumaczeń, przez tworzenie objektów, klasy TranslateItemClassNG
		if(TPath::GetExtension(pSortedListFileTrans->Strings[i]) == GsReadBibleTextData::GsExtendNoAsteriskFileTranslateFull)
			{_enTypeTranslate = enTypeTr_Full; ++this->uiCountPol;}
		else if(TPath::GetExtension(pSortedListFileTrans->Strings[i]) == GsReadBibleTextData::GsExtendNoAsteriskFileTranslateGrecOrg)
			{_enTypeTranslate = enTypeTr_Greek; ++this->uiCountOryg;}
		else if(TPath::GetExtension(pSortedListFileTrans->Strings[i]) == GsReadBibleTextData::GsExtendNoAsteriskFileTranslateHbrOrg)
			{_enTypeTranslate = enTypeTr_Hebrew; ++this->uiCountOryg;}
		//--- Dodawanie klasy(GsReadBibleTextItem) tłumaczenia, listy klas dostępnych tłumaczeń
		GsReadBibleTextItem *pGsReadBibleTextItem = new GsReadBibleTextItem(pSortedListFileTrans->Strings[i], _enTypeTranslate, i);
		if(!pGsReadBibleTextItem) throw(Exception("Błąd inicjalizacji objektu, klasy GsReadBibleTextItem"));
		this->_GsListItemsTranslates->Add(pGsReadBibleTextItem); //[13-05-2024]Dodawanie tłumaczenia
		//--- Dodawanie string listy tłumaczenia, do listy klas THashedStringList, z tekstami wszystkich dostępnych tłumaczeń, dla wybranego rozdziału i księgi.
		//		Klasy THashedStringList wszystkich tłumaczeń, będą wypełniane gdy zostanie wybrana księga, oraz rozdział
		THashedStringList *_pHListChapt = new THashedStringList();	//String lista NA PRZYSZŁY wybranego rozdziału i księgi, kolejnego tłumaczenia
		if(!_pHListChapt) throw(Exception("Błąd inicjalizacji danych THashedStringList"));
		this->_ListAllTrChap->Add(_pHListChapt); //Dodanie String listy, która na początku jest PUSTA, wybranej księgi i tłumaczenia do listy głównej, DLA PRZYSZŁEGO wybranego rozdziału i księgi
		//Potem gdy zostanie wybrana księga i rozdział, string lista będzie zawierała, wersety wybranej księgi i rozdziału, każdego tłumaczenia.
	}
//  #if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("this->_ListAllTrChap->Count: %d", ARRAYOFCONST((this->_ListAllTrChap->Count))));
//	#endif
	// this->_DeleteSelectTranslate(1); //Działa!!!
	// Wczytanie danych do objektu, klasy THashedStringList z danymi do wyświetlenia tekstu Nowego Testamentu, w formie interlinearne, grecko-polskiej
	// Czyli pliku "gnt.intrl"
//  #if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("gnt: \"%s\" - %s", ARRAYOFCONST((GlobalVar::Global_custrPathFileInterlinear,
//			GlobalVar::Global_custrPathFileWordVersesExistHbr))));
//	#endif
	if(TFile::Exists(GlobalVar::Global_custrPathFileInterlinear))
		{this->_SListInterLinear->LoadFromFile(GlobalVar::Global_custrPathFileInterlinear, TEncoding::UTF8);}
	else MessageBox(NULL, Format("Brak pliku: %s", ARRAYOFCONST((GlobalVar::Global_custrPathFileInterlinear))).c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
	//---
	if(pSListExcludeTrans) {delete pSListExcludeTrans; pSListExcludeTrans = nullptr;}
	if(pSortedListFileTrans) {delete pSortedListFileTrans; pSortedListFileTrans = nullptr;}
	//---
	return true;
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextClass::SaveCurrentSheetText(const UnicodeString &custrPath)
/**
	OPIS METOD(FUNKCJI): Zapisuje zawartość aktualnej zakładki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsTabSheetClass *pGsTabSheetClass = static_cast<GsTabSheetClass *>(GsReadBibleTextData::_GsPageControl->ActivePage);
	if(!pGsTabSheetClass) return;
	//---
	if(custrPath==0)
	{
		UnicodeString _custrPath = Format("%s_%u_%s.html", ARRAYOFCONST((AppCTable_InfoAllBooks[pGsTabSheetClass->_ShucIndexBook].FullNameBook, pGsTabSheetClass->_ShucIndexChapt+1,
			pGsTabSheetClass->pGsTabSetClass->Tabs->Strings[pGsTabSheetClass->pGsTabSetClass->TabIndex])));
		//Zapisanie pliku html, pod domyślna nazwą
		TFile::WriteAllText(_custrPath, pGsTabSheetClass->ustrHtmlText, TEncoding::UTF8);
	}
	else
	{TFile::WriteAllText(custrPath, pGsTabSheetClass->ustrHtmlText, TEncoding::UTF8);}
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextClass::_GetNameIndependentTranslate(const int i, UnicodeString &NameTranslate)
/**
	OPIS METOD(FUNKCJI): Zwraca nazwę tłumaczenia niezależnie od jego statusu (aktywny, lub nie) //[09-12-2023]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(i < this->_pSListAllNamesTranslates->Count)
	{
		NameTranslate = this->_pSListAllNamesTranslates->Strings[i];
	}
	else NameTranslate = "";
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextClass::_GetInfoNameTranslate(const int i, UnicodeString &NameTranslate)
/**
	OPIS METOD(FUNKCJI): Zwraca nazwę wybranego tłumaczenia
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
	NUMER TŁUMACZENIA LICZYMY OD ZERA. NUMER KSIĘGI LICZYMY OD ZERA!!!
*/
{
	if(i >= this->_GsListItemsTranslates->Count)
		{NameTranslate = "Zły numer tłumaczenia!"; return;}
	GsReadBibleTextItem *pGsReadBibleTextItem = static_cast<GsReadBibleTextItem *>(this->_GsListItemsTranslates->Items[i]);
	if(!pGsReadBibleTextItem) throw(Exception("Błąd metody pGsReadBibleTextItem::GetInfoNameTranslate"));
	NameTranslate = pGsReadBibleTextItem->NameTranslate;
}
//---------------------------------------------------------------------------
THashedStringList *__fastcall GsReadBibleTextClass::GetSelectBookTranslate(const int iGetTranslate, const int iGetBook)
/**
	OPIS METOD(FUNKCJI): Metoda zwraca THashedStringListe na konkretne tłumaczenia i księgi
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
	NUMER TŁUMACZENIA LICZYMY OD ZERA. NUMER KSIĘGI LICZYMY OD ZERA!!!
	Metoda używana w Metodzie GetAllTranslatesChapter()
*/
{
	if(iGetTranslate >= this->_GsListItemsTranslates->Count) return 0;
	GsReadBibleTextItem *pGsReadBibleTextItem = static_cast<GsReadBibleTextItem *>(this->_GsListItemsTranslates->Items[iGetTranslate]);
	if(pGsReadBibleTextItem)
	{
		//Zabezpieczenie przed niewłaściwym indeksem księgi, w wybranym tłumaczeniu
		if((iGetBook < static_cast<int>(pGsReadBibleTextItem->ucStartBook)) ||
			 (iGetBook >=static_cast<int>((pGsReadBibleTextItem->ucCountBooks + pGsReadBibleTextItem->ucStartBook))))
		{GsReadBibleTextData::EnErrorCode = enR_GSelectBoook; return 0;}
		return pGsReadBibleTextItem->_pGsHListAllListBooks[iGetBook];
	}
	return 0;
}
//---------------------------------------------------------------------------
THashedStringList *__fastcall GsReadBibleTextClass::GetSelectBookOrgTranslate(int _iBook)
/**
	OPIS METOD(FUNKCJI): Metoda zwraca string listę wersetów z pierwszego w kolejności tłumaczenia typu EnTypeTranslate, dla wybranego rozdziału
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
	NUMER TŁUMACZENIA LICZYMY OD ZERA. NUMER KSIĘGI LICZYMY OD ZERA!!!
	Metoda używana TYLKO w module(klasie) GsLViewDictionaryClass (lista Słów greckich z ich tłumaczeniami)
*/
{
	if(_iBook >= static_cast<int>(GlobalVar::Global_NumberBooks)) return 0;
	//---
	const EnTypeTranslate _EnTypeTranslate=enTypeTr_Greek;
  //--- Wybór tłumaczenia, które bedzie uzywane dla słownika i konkordancji grecko-polskiej [02-06-2024]
	UnicodeString ustrSelectTransDictCord = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_TranslatesSection_Main,
		GlobalVar::GlobalIni_SelectTranslateForDictConcord, GlobalVar::Global_DefaultNameTranslateToDictionary);

	for(int i=0; i<this->_GsListItemsTranslates->Count; ++i)
	{
		GsReadBibleTextItem *pGsReadBibleTextItem = static_cast<GsReadBibleTextItem *>(this->_GsListItemsTranslates->Items[i]);
		if(pGsReadBibleTextItem)
		{
			if(pGsReadBibleTextItem->enTypeTranslate == _EnTypeTranslate)
			{
				if(pGsReadBibleTextItem->NameTranslate == ustrSelectTransDictCord)
				{
//					#if defined(_DEBUGINFO_)
//						GsDebugClass::WriteDebug(Format("Name: \"%s\"", ARRAYOFCONST(( pGsReadBibleTextItem->NameTranslate ))));
//						GsDebugClass::WriteDebug(Format("File name: \"%s\"", ARRAYOFCONST(( TPath::GetFileName(pGsReadBibleTextItem->FullPathTranslate) ))));
//					#endif
					return pGsReadBibleTextItem->_pGsHListAllListBooks[_iBook];
				}
			}
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextClass::_ViewSListBibleToHTML(TWebBrowser *_cWebBrowser,
			THashedStringList *_HStringInput, const DataDisplayTextAnyBrowser &DataDisplay)
/**
	OPIS METOD(FUNKCJI): Przekształcenie DOWOLNEJ String listy wersetów, w wizualny tekst html (np. przy wyszukiwaniu)
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI): Tekst w formacie html

*/
{
	if((DataDisplay.strBackgroundColor.IsEmpty()) || (DataDisplay.strBackgroundColor.Length() != 7)) {return;}	//Opuść metodę jeśli zmienna _astrColor nie jest określeniem koloru w formacie html, czyli np. #CCAAFF
	THashedStringList *_HStringList;//=0;
	TStringStream *pStringStream = new TStringStream("", TEncoding::UTF8, true);
	if(!pStringStream) throw(Exception("Błąd inicjalizacji objektu TStringStream"));

	try
	{
		pStringStream->WriteString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">");
		//int iPozycja=0;
		//Jaka String lista ma być brana pod uwagę. Jeśli w argumencie metody jest podany wskaźnik
		//na String liste, to on zostanie wzięty pod uwagę, w przeciwnym wypadku, za liste wejściową
		//bedzie wżięta String lista wersetów apokryficznych wewnątrz rozdziałów, czyli this->_SListApocryficAddOn
		_HStringList = _HStringInput;
		UnicodeString ustrStyle = UnicodeString("<html><head>") +
																		"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">" +
																		"<title>Wybrany rozdział, dla dostępnych tłumaczeń</title>" +
																		"<style type=\"text/css\">" +
																		Format(".styleColorAdressTranslates {color: #FF0000; font-size:%dpt;font-family:%s;}",
																			ARRAYOFCONST((DataDisplay.iSizeFont-3, DataDisplay.strNameFont))) +
																		Format(".styleText {color: #000000; font-size:%dpt;font-family:%s;}", ARRAYOFCONST((DataDisplay.iSizeFont, DataDisplay.strNameFont))) +
																		Format("body {background-color:%s;}", ARRAYOFCONST((DataDisplay.strBackgroundColor))) +
																		"</style></head><body>";
		pStringStream->WriteString(Format("%s", ARRAYOFCONST((ustrStyle))));
		//-----
		for(int i=0; i<_HStringList->Count; ++i)
		{
			MyObjectVers *pMyObjectVers = dynamic_cast<MyObjectVers *>(_HStringList->Objects[i]);
			if(pMyObjectVers)
				pStringStream->WriteString(Format("<span class=\"styleColorAdressTranslates\">%s	</span><span class=\"styleText\">%s</span>", ARRAYOFCONST((pMyObjectVers->BookChaptVers, _HStringList->Strings[i]))));
			//-----
			pStringStream->WriteString("<br>");
			if(DataDisplay.bIsHorizontLine) pStringStream->WriteString("<hr>");//Pozioma kreska;
		}
		pStringStream->WriteString("</body></html>");
		pStringStream->Position = 0;
		if(DataDisplay.pMemoryStream)
		{
			//Zapis wyniku wyszukiwania jako danych html, do objektu, klasy TMemoryStream (_pMemoryStrResult)
			DataDisplay.pMemoryStream->Clear();
			DataDisplay.pMemoryStream->Position = 0;
			pStringStream->SaveToStream(DataDisplay.pMemoryStream);
			pStringStream->Position = 0;
		}
		//Wczytanie do objektu, klasy TWebBrowser (_cWebBrowser) zawartości objeltu, klasy TMemoryStream (stm)
		IPersistStreamInit *psi;

		_di_IStream sa(*(new TStreamAdapter(pStringStream, soReference)));
		if(SUCCEEDED(_cWebBrowser->Document->QueryInterface(IID_IPersistStreamInit, (void **)&psi)))
			{psi->Load(sa);}

	}
	__finally
	{
		if(pStringStream) {delete pStringStream; pStringStream = nullptr;}
	}
}
//---------------------------------------------------------------------------
bool __fastcall GsReadBibleTextClass::GetAllTranslatesChapter(const int iGetBook, const int iGetChap)
/**
	OPIS METOD(FUNKCJI): Konstruowanie listy z wybranym rozdziałem, wybranej księgi dla wszystkich tłumaczeń
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
	NUMER TŁUMACZENIA LICZYMY OD ZERA. NUMER KSIĘGI LICZYMY OD ZERA!!!
*/
{
	if(this->_GsListItemsTranslates->Count == 0) throw(Exception("Nie zostały wczytane dostępne tłumaczenia, metodą \"LoadAllTranslates()\""));
	int iFindChapter; //Szukany rozdział
	THashedStringList *_pHListChapt=nullptr;
	//---
	this->_ClearListAllTrChap();	//Wyczyszczenie TYLKO zawartości listy!!!

	for(int i=0; i<this->_GsListItemsTranslates->Count; ++i)
	{
		THashedStringList *_pTempHSList =	 this->GetSelectBookTranslate(i, iGetBook); //String lista wybranej księgi kolejnego tłumaczenia
		if(!_pTempHSList) continue;//Gdy wybierzesz księge ze st, metoda zwróci 0 podczas badania GNT, i odwrotnie w przypadku wyboru księgi NT, metoda zwróci 0 podczas badania HST
		_pHListChapt = static_cast<THashedStringList *>(this->_ListAllTrChap->Items[i]);	//String lista wybranego rozdziału, kolejnego tłumaczenia
		//W _pHListChapt, typu THashedStringList, KTÓRA JEST PÓSTA, zostanie umieszcony wybrany rozdział, kolejnego tłumaczenia
		if(!_pHListChapt) throw(Exception("Brak zainicjowanego objektu THashedStringList w liście wybranego rozdziału"));
		//Tworzenie string listy wybranej księgi i rozdziału
		for(int iVers=0; iVers<_pTempHSList->Count; ++iVers)
		{
			iFindChapter = _pTempHSList->Strings[iVers].SubString(4, 3).ToInt(); //Odczyt rozdziału kolejnego wersetu
			if(iFindChapter == (iGetChap + 1))
			{
				_pHListChapt->AddObject(_pTempHSList->Strings[iVers].SubString(10, GlobalVar::Global_MaxlengthVers), _pTempHSList->Objects[iVers]);
			}
		}
	}

	GsTabSheetClass *pGsTabSheetClass = static_cast<GsTabSheetClass *>(GsReadBibleTextData::_GsPageControl->ActivePage);
	if(!pGsTabSheetClass) throw(Exception("Nie powiodło się wyłuskanie wskaźnika na aktualną zakładkę"));
	pGsTabSheetClass->Caption = Format("%s: %u rozdział", ARRAYOFCONST((AppCTable_InfoAllBooks[iGetBook].FullNameBook, iGetChap+1)));
	//Metoda dodajaca informacje o otwartym rozdziale do listy historii
	GsReadBibleTextData::AddItemHistoryList(pGsTabSheetClass->Caption); //TUTAJ JEST BŁĄD!!!
	//Informacja w strukturze zakładki o numerze księgi i rozdziału
	pGsTabSheetClass->_ShucIndexBook = iGetBook;
	pGsTabSheetClass->_ShucIndexChapt = iGetChap;
	//Maksymalny wskaźnik, równy ilości rozdziałów w wybranej księdze.
	pGsTabSheetClass->pProgressBar->Max = AppCTable_InfoAllBooks[pGsTabSheetClass->_ShucIndexBook].ucCountChapt-1;
	pGsTabSheetClass->pProgressBar->Position = iGetChap; //Aktualna pozycja wskaźnika umiejscowienia w wybranej księdze
	//Ustawianie objektu, klasy TTaskBar
	if(GsReadBibleTextData::_GsTaskBar)
	{
		GsReadBibleTextData::_GsTaskBar->ProgressMaxValue = pGsTabSheetClass->pProgressBar->Max;
		GsReadBibleTextData::_GsTaskBar->ProgressValue = pGsTabSheetClass->pProgressBar->Position;
		//Application->Title = pGsTabSheetClass->Caption;
	}
	//---
	if(pGsTabSheetClass->pComboBox->ItemIndex!=iGetChap) pGsTabSheetClass->pComboBox->ItemIndex = iGetChap;	 //Uaktywnienie odpowiedniej pozycji w liście dostępnych rozdziałów
	//Kontrola aktywności przycisków przewijania do następnej, lub poprzedniej księgi
	TToolButton *pGetNextBook = pGsTabSheetClass->pToolBar->Buttons[enImageIndex_ToNextBook - enImageIndex_ToNextBook];
	TToolButton *pGetPrevBook = pGsTabSheetClass->pToolBar->Buttons[enImageIndex_ToPrevBook - enImageIndex_ToNextBook];
	pGetNextBook->Enabled = (pGsTabSheetClass->_ShucIndexBook < GlobalVar::Global_NumberBooks-1);
	pGetPrevBook->Enabled = (pGsTabSheetClass->_ShucIndexBook > 0);
	//Kontrola aktywności przycisków przewijania rozdziałów do produ i do tyłu
	TToolButton *pGetToolButtonPrev = pGsTabSheetClass->pToolBar->Buttons[enImageIndex_ToPrevBook - enImageIndex_NextChapter];
	TToolButton *pGetToolButtonNext = pGsTabSheetClass->pToolBar->Buttons[enImageIndex_ToPrevBook - enImageIndex_PrevChapter];
	pGetToolButtonNext->Enabled = pGsTabSheetClass->_ShucIndexChapt < AppCTable_InfoAllBooks[pGsTabSheetClass->_ShucIndexBook].ucCountChapt-1;
	pGetToolButtonPrev->Enabled = pGsTabSheetClass->_ShucIndexChapt > 0;

	return true;
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextClass::DisplayAllTextInHTML(TWebBrowser *_pWebBrowser, const int iSelectTranslate)
/**
	OPIS METOD(FUNKCJI): Metoda łączy w jedną całość jako kod Html tekst, ze wszystkich tłumaczeń, wybranej księgi i rozdziału.
											 Daną z tekstem jest lista this->_ListAllTrChap
	OPIS ARGUMENTÓW: UnicodeString &JoinText - Referencja do stringu, w którym zostanie umieszczony połączony tekst
									 TWebBrowser *_pWebBrowser - Wskaźnik na objekt typy TWebBrowse, na którym ma być wyświetlony tekst
									 int iSelectTranslate - Numer konkretnego tłumaczenia, domyślnie -1, czyli wszystkie tłumaczenie. Trzeba odjąć 1 gdyż w zakładce
																					objektu klasy GsTabSetClass, konkretne tłumaczenia nie zaczynają się od indeksu 0 (wszystkie tłumaczenia), tylko 1 (pierwsze tłumaczenie)!!!.
																					Gdyby tego nie zrobić to wybrano by tłumaczenie o indeksie +1, a tablica tłumaczeń GsReadBibleTextClass::_ListAllTrChap zaczyna się od 0!!!
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!this->_ListAllTrChap) {throw(Exception("Nie zainicjowano listy wszystkich tłumaczeń, wybranej księgi i rozdziału"));}
	if(this->_ListAllTrChap->Count == 0) return;	//Pusta lista
	//---
	TTreeNode *pTreeNodeSelect = GsReadBibleTextData::pGsTreeBibleClass->Selected; //[03-08-2023]
	//---
	MyObjectVers *pMyOjectVers=nullptr;
	THashedStringList *pTempHSList=nullptr;
	int iIndexVers=0, //Indeks wersetów w równoległym tłumaczeniu, lub pojedyńczym
			iIndexFav=-1;//Indeks na globalnej liście wersetów ulubionych
	unsigned char uiTranslatesIndex;//=0;
	bool bIsOneTranslate=false; // Wiele tłumaczeń = false, jedno = true // [04-09-2025]
	UnicodeString _Style_FavoriteStyle = "", //Styl zaznaczania ulubionego wersetu
								_Style_CommentStyle = "",	 //Styl zaznaczania wersetu skomentowanego
								_StyleFav_End = "",
								_StyleComm_End = "",
								//---
								DisplaySelectNameTranslate; //Nazwa tlumaczenia wyłuskana z GsReadBibleTextItem->NameTranslate. W wypadku wybrania pojedyńczego
																						// tłumaczenia bedzie pusta[30-08-2023]
	TStringStream *pStringStream = new TStringStream("", TEncoding::UTF8, true); //Allokacja strumienia dla tekstu html
	if(!pStringStream) throw(Exception("Błąd inicjalizacji objektu TStringStream"));
	//Pobranie aktualnej zakładki i wyzerowanie zmiennych z zawartością zakładki i zawartości objektu klasy TListBox
	GsTabSheetClass *pGsTabSheetClass = dynamic_cast<GsTabSheetClass *>(GsReadBibleTextData::_GsPageControl->ActivePage);
	if(!pGsTabSheetClass) throw(Exception("Nie mogę uzyskać wskaźnika do aktualnej zakładki!"));
	pGsTabSheetClass->ustrHtmlText = ""; //Wyczyszczenie zawartości zakładki, jako strony w kodzie html, do ewentualnego zapisania jako samodzielnej strony html.
	pGsTabSheetClass->pHSListActualText->Clear(); //Wyczyszczenie listy surowej aktualnie przeglądanego rozdziału
	pGsTabSheetClass->pLBoxSelectText->Items->BeginUpdate();
	pGsTabSheetClass->pLBoxSelectText->Clear(); //Wyczyszczenie listy ulubionych wersetów (objekt, klasy TListBox)
	//Podmiana elementu /title w kodzie html wczytanego rozdziału i księgi na nazwę księgi - [03-08-2023]
	UnicodeString ustrHeaderText = StringReplace(GsReadBibleTextData::GsHTMLHeaderText, GsReadBibleTextData::GsHTMLTitle,
		"<title>" + pTreeNodeSelect->Text + "</title>", TReplaceFlags() << rfReplaceAll); //[03-08-2023]
	pStringStream->WriteString(ustrHeaderText); //Zapis nagłówka kodu html do strumienia
	try
	{
		do
		//Pętla obracająca się przez kolejne wersety wybranej księgi i rodziału, wszystkich dostępnych tłumaczeń (for)
		{
			//Jeśli chcemy tylko jedno tłumaczenie, to licznik tłumaczeń = 1
			if(iSelectTranslate>-1) {uiTranslatesIndex = 1; bIsOneTranslate = true;}
			else // W przeciwnym przypadku ilość tłumaczeń równa ilością wszystkich załadowanych!
			{
				uiTranslatesIndex = static_cast<unsigned char>(this->_ListAllTrChap->Count);
				bIsOneTranslate = false;
			}
			//---
			for(int iIndexChapt=0; iIndexChapt<this->_ListAllTrChap->Count; ++iIndexChapt)
			//Dodawanie pokolei równoległych wersetów ze wszystkich tłumaczeń
			{
				if((iSelectTranslate>-1) && (iIndexChapt!=iSelectTranslate))
					//Jeśli ma być wyświetlone konkretne tłumaczenie
					//iSelectTranslate>-1, czyli nie wszyskie tłumaczenia (iSelectTranslate==-1)
					//i!=iSelectTranslate, pętla jest w niewybranym tłumaczeniu
					{continue;}
        // Wyłuskanie wskaźnika GsReadBibleTextItem konkretnego tłumaczenia, w celu sprawdzenia typu tłumaczenia
				GsReadBibleTextItem *pGsReadBibleTextItem = this->GetTranslateClass(iIndexChapt);
				//Wyłuskanie THashedStringListy konkretnego tłumaczenia, dla wybranego rozdziału
				pTempHSList = static_cast<THashedStringList *>(this->_ListAllTrChap->Items[iIndexChapt]);
				if(!pTempHSList || !pGsReadBibleTextItem) throw(Exception("Błąd metody łączenia wszystkich tłumaczeń"));
				//Nazwa tlumaczenia wyłuskana z GsReadBibleTextItem->NameTranslate.
				//W wypadku wybrania pojedyńczego tłumaczenia bedzie pusta //[30-08-2023]
				if(iSelectTranslate == -1) DisplaySelectNameTranslate = pGsReadBibleTextItem->NameTranslate; else DisplaySelectNameTranslate = "";
				//Gdy string lista pusta (hebrajski tekst w nowym testamencie, grecki tekst w starym testamencie), to nie wpływa na opuszczenie pętli do, while.
				if(pTempHSList->Count == 0)
				//Gdy lista konkretnego tłumaczenia i rozdziału jest pusta, bo brak księgi.
				{
					uiTranslatesIndex--;
					if(iSelectTranslate>-1)
						{pStringStream->WriteString("<span class=\"styleNoTranslate\">To tłumaczenie nie zawiera tekstu wybranej księgi!</span>\n");}
					continue;
				}

				if(iIndexVers < pTempHSList->Count)
				//Istnieją jeszcze wersety dla aktualnego tłumaczenia
				{
					pMyOjectVers = static_cast<MyObjectVers *>(pTempHSList->Objects[iIndexVers]);
					if(!pMyOjectVers) throw(Exception("Błąd odczytu objektu MyObjectVers"));
					//Dodawanie kolejnego wersetu
					if(!pTempHSList->Strings[iIndexVers].IsEmpty())
					{
						//Lista surowa aktualnie przegladanego rozdziału [25-08-2021]; [20-08-2023]
						//pGsTabSheetClass->pHSListActualText->AddObject(Format("%s %s", ARRAYOFCONST(( pMyOjectVers->BookChaptVers, pTempHSList->Strings[iIndex] ))), pMyOjectVers);
						pGsTabSheetClass->pHSListActualText->AddObject(Format("%s", ARRAYOFCONST((pTempHSList->Strings[iIndexVers] ))), pMyOjectVers);

						if(pGsTabSheetClass->pLBoxSelectText->Items->IndexOf(pMyOjectVers->AdressString) == -1)
						//Jeśli nie istnieje jeszcze adres wersetu
						{
							pGsTabSheetClass->pLBoxSelectText->AddItem(pMyOjectVers->AdressString, pMyOjectVers); //Dodanie wersetu do listy zaznaczalnej
							iIndexFav = GlobalVar::Global_HSListAllFavoritiesVers->IndexOf(pMyOjectVers->AdressString); //Indeks na globalnej liście wersetów ulubionych
							if(iIndexFav > -1)
							//Jeśli werset jest na globalnej liście wersetów ulubionych, zaznacz go na objekcie, klasy TListBox, z ulubionymi wersetami, z wybranego rozdziału
							{
								pGsTabSheetClass->pLBoxSelectText->Selected[pGsTabSheetClass->pLBoxSelectText->Count - 1] = true;
							}
						}
						if(pGsReadBibleTextItem->enTypeTranslate == enTypeTr_Full) //Pełne polskie tłumaczenie
						{
							if(iIndexFav > -1) ///Werset jest na liście ulubionych 13.01.2019
							{
								_Style_FavoriteStyle = "<div class=\"styleFavorite\">\n"; //"<span class=\"styleFavorite\">"; //Styl zaznaczania ulubionego wersetu
								_StyleFav_End = "</div>\n";
							}
							else //Wersetu nie ma na liście ulubionych 13.01.2019, style będą puste
							{
								_Style_FavoriteStyle = ""; //Styl zaznaczania ulubionego wersetu
								_StyleFav_End = "\n";
							}
							//Odznaczanie wersetu z komentarzem
							if(TFile::Exists(TPath::Combine(GlobalVar::Global_custrPathDirComments, pMyOjectVers->AdressString) + GlobalVar::Global_custrExtendCommentsFiles))
							//Jeśli istnieje plik komentarzy
							{
								_Style_CommentStyle = "<span class=\"styleComment\">C";	 //Styl zaznaczania wersetu skomentowanego
								_StyleComm_End = "</span>\n";
							}
							else
							{
								_Style_CommentStyle = "";	 //Styl zaznaczania wersetu skomentowanego
								_StyleComm_End = "";
							}
							//[14-04-2024] //[17-08-2024]
							pStringStream->WriteString(Format(UnicodeString("<p>\n") +	//[21-09-2023] //[14-04-2024] //[17-08-2024]
							//"<p>\n" +
							_Style_FavoriteStyle +
							"%s" +	// _Style_CommentStyle
							"%s" +	"<span class=\"styleColorAdressTranslates\">\n\t" + // _StyleComm_End,
							"%s\n</span>\n"+ // pMyOjectVers->BookChaptVers,
							"<span class=\"styleText\"; id=tekst%d_%d>\n\t" +  // iIndex, i
							"%s\n</span>\n", // pTempHSList->Strings[iIndex]
							ARRAYOFCONST((_Style_CommentStyle,
														_StyleComm_End,
														pMyOjectVers->BookChaptVers,
														iIndexChapt, iIndexVers, // tłumaczenie_werset [24-08-2025]
														pTempHSList->Strings[iIndexVers]
														))));
							// Nazwa tłumaczenia
							pStringStream->WriteString(Format(UnicodeString("<span class=\"styleTranslates\">\n\t%s\n</span>\n"),
								ARRAYOFCONST((DisplaySelectNameTranslate))));
							pStringStream->WriteString(_StyleFav_End); //[14-04-2024] //[17-08-2024]
							pStringStream->WriteString("</p>\n");
						}
						else // Częściowe oryginalne, lub polskie tłumaczenie tłumaczenie
						{ // Usunięte z powody tworzenia przeglądy tłumaczeń specjalistycznych //[11-05-2024]
							// Więc tłumaczenia nie będą wyswietlane w głównym oknie, tylko w oknie do przeglądy
							// tego typu tłumaczeń. Jedna warunek "else" zostanie zachowany //[12-05-2024]
						}
						pStringStream->WriteString("<!---- Kolejny werset ---->\n"); //[14-04-2024] //[18-04-2024]
					} //if(!pTempHSList->Strings[iIndex].IsEmpty())
				} //if(iIndex < pTempHSList->Count)
				else
				//Aktualne tłumaczenie nie ma już wersetów, licznik tłumaczeń zostaje zmniejszony o 1
				{
					uiTranslatesIndex--;
				}
			}
			++iIndexVers;
			if(uiTranslatesIndex >= GlobalVar::Global_cucMaxCountTranslates) uiTranslatesIndex=0; //Zabezpieczenie przed przekęceniem licznika
			if((iSelectTranslate == -1) && (uiTranslatesIndex > 0))
			{
				pStringStream->WriteString("<hr>\n");
			}

		}while(uiTranslatesIndex > 0);
		pGsTabSheetClass->pLBoxSelectText->Items->EndUpdate();
		//--- Uzupełnienie kodu Java script o indeksy wersetów // [30-08-2025]
		// Kod Java script. // [24-08-2025] // [30-08-2025]
//    #if defined(_DEBUGINFO_)
//			GsDebugClass::WriteDebug(Format("bIsOneTranslate: %d", ARRAYOFCONST(((int)bIsOneTranslate))));
//		#endif
		if(bIsOneTranslate) // [04-09-2025]
		{
  		GsReadBibleTextData::GsHTMLJavaScripts = UnicodeString // Rozpoczęcie kodu Java script // [30-08-2025]
  																						("<script type=\"text/javascript\">\n") +
  																						// Wczytanie kody java script, który umożliwia klikalność słów
  																						TFile::ReadAllText(GsReadBibleTextData::GsHTML_FileJavaSc_SelectWord, TEncoding::UTF8) +
  																						"\n\n// Wywołanie z poziomu window.onload() z podanymi identyfikatorami\n" +
  																						"window.onload = function()\n{\n";
  		// Tworzenie wywoływania funkcji Java script z indeksem wersetów
  		// dla wybranego tłumaczenia i wersetu z wybranego rozdziału // [30-08-2025]
  		for(int iIndexTrans=0; iIndexTrans<this->uiCountPol; ++iIndexTrans)
  		{
  			for(int iVers=0; iVers<iIndexVers; ++iVers)
  			{
  				GsReadBibleTextData::GsHTMLJavaScripts += Format("\tprzetworzTekst(\"tekst%d_%d\");\n",
  					ARRAYOFCONST((iIndexTrans, iVers)));
  			}
  		}
			GsReadBibleTextData::GsHTMLJavaScripts += "}\n</script>\n";
			pStringStream->WriteString(GsReadBibleTextData::GsHTMLJavaScripts); // [24-08-2025]
		}
		pStringStream->WriteString("</body>\n</html>\n");
		pStringStream->Position = 0;
		//--- Zmienna do zapisu zawartości zakładki w postaci kodu html, z wybranym rozdziałem, do ewentualnego zapisu jako samodzielnej strony.
		pGsTabSheetClass->ustrHtmlText += pStringStream->DataString;
		//-----
		IPersistStreamInit *psi;
		_di_IStream sa(*(new TStreamAdapter(pStringStream, soReference)));
		if(SUCCEEDED(_pWebBrowser->Document->QueryInterface(IID_IPersistStreamInit, (void **)&psi)))
			{psi->Load(sa);}
	}
	__finally
	{
		if(pStringStream) {delete pStringStream; pStringStream = nullptr;}
	}
}
//---------------------------------------------------------------------------
GsReadBibleTextItem *__fastcall GsReadBibleTextClass::GetTranslateClass(const int iNumberTrans)
/**
	OPIS METOD(FUNKCJI): Metoda zwraca wskaźnik na klasę wybranego tłumaczenia
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(iNumberTrans >= this->_GsListItemsTranslates->Count) return 0;
	GsReadBibleTextItem *pGsReadBibleTextItem = static_cast<GsReadBibleTextItem *>(this->_GsListItemsTranslates->Items[iNumberTrans]);
	return pGsReadBibleTextItem;
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextClass::_ClearListAllTrChap(const bool bIsRemoveList)
/**
	OPIS METOD(FUNKCJI): Zwolnienie zawartości listy _ListAllTrChap.
	OPIS ARGUMENTÓW: bool bIsRemoveList - Czy lista ma być usunięta, domyślnie(false) tylko wyczyszczona!!!
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Najpierw usunięcie wszystkich THashedStringList z wszystkimi tłumaczeniemi i wybranym rozdziele,	z listy
	if(this->_ListAllTrChap)
	{
		for(int i=0; i<this->_ListAllTrChap->Count; ++i)
		{
			//Czyszczenie string list z tekstem poszczególnych tłumaczeń i wybranego rozdziału
			THashedStringList *_pTempHSList = static_cast<THashedStringList *>(this->_ListAllTrChap->Items[i]);
			if(_pTempHSList)
			{
				_pTempHSList->Clear(); //Tylko czyszczenie ISTNIEJĄCYCH string list, na wybrany rozdział ze wszystkich tłumaczeń!!!
				if(bIsRemoveList) {delete _pTempHSList; _pTempHSList = nullptr;} //USUWANIE istniejących string list!!!
			}
		}
		if(bIsRemoveList) {delete this->_ListAllTrChap; this->_ListAllTrChap = nullptr;} //--- Usuwanie listy !!!
	}
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextClass::GlobalTextDragDrop(TObject *Sender, TObject *Source, int X, int Y)
/**
	OPIS METOD(FUNKCJI): Główna metoda wywoływana podczas upuszczenia objektu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsReadBibleTextData::pGsTreeBibleClass->DblClick(); //Załadowanie odpowiedniego rozdziału
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextClass::_GlobalTextDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept)
/**
	OPIS METOD(FUNKCJI): Główna metoda wywoływana podczas przeciągania elementu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Akceptacja jeśli jest to objekt odpowiedniej klasy
	Accept = Source->ClassNameIs("GsTreeBibleClass");
}
//---------------------------------------------------------------------------
void __fastcall GsReadBibleTextClass::_DeleteSelectTranslate(const int iNumberTrans)
/**
	OPIS METOD(FUNKCJI): Skasowanie wybranego tłumaczenia
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(iNumberTrans >= this->_GsListItemsTranslates->Count) return;
	//---
	GsReadBibleTextItem *pGsReadBibleTextItem = static_cast<GsReadBibleTextItem *>(this->_GsListItemsTranslates->Items[iNumberTrans]);
	if(pGsReadBibleTextItem)
	{
		//--- Skasowanie objektu, klasy wybranego tłumaczenia
		delete pGsReadBibleTextItem; pGsReadBibleTextItem = nullptr;
		this->_GsListItemsTranslates->Delete(iNumberTrans);
		//--- Czysczenie string listy na wybrany rozdział, wybranego tłumaczenia, które zostanie skasowane.
		//		KONIECZNE zwolnienie THashedStringListy dla wybranego tłumaczenie, i pozycji o numerze tłumaczenia z listy this->_ListAllTrChap
		THashedStringList *_pTempHSList = static_cast<THashedStringList *>(this->_ListAllTrChap->Items[iNumberTrans]);
		if(_pTempHSList)
			{_pTempHSList->Clear(); delete _pTempHSList; _pTempHSList = nullptr;}
		this->_ListAllTrChap->Delete(iNumberTrans);
	}
}
/****************************************************************************
 *													Klasa GsTreeNodeClass														*
 ****************************************************************************/
__fastcall GsTreeNodeClass::GsTreeNodeClass(TTreeNodes* Owner) : TTreeNode(Owner)
/**
	OPIS METOD(FUNKCJI): Główny konstruktor, klasy GsTreeNodeClass
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
__fastcall GsTreeNodeClass::~GsTreeNodeClass()
/**
	OPIS METOD(FUNKCJI): Główny Destruktor, klasy GsTreeNodeClass
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	///
}
/****************************************************************************
 *												Klasalasa GsTreeBibleClass												*
 ****************************************************************************/
__fastcall GsTreeBibleClass::GsTreeBibleClass(TComponent* Owner, TPageControl *pPageControl)
	: TCustomTreeView(Owner)
/**
	OPIS METOD(FUNKCJI): Główny konstruktor, klasy MBNGTreeVBibleClass
	OPIS ARGUMENTÓW: TComponent* Owner - Wskaźnik na właściciela klasy
									 TPageControl *pPageControl - Wskaźnik na klasę typy TPageControl, na której pojawiać sie będą zakładki
																								wybranych rozdziałów bibli.
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass) throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	//---
	this->OnCreateNodeClass = this->_CreateNodeClass; //Podmiana klasy TTreeNode na GsTreeNodeClass
	this->Images = GsReadBibleTextData::_GsImgListData; //Lista ikon przyporządkowana
	this->RightClickSelect = true;
	this->ReadOnly = true;
	this->DragMode = dmAutomatic;
	//this->DoubleBuffered = true;
	//this->StyleElements = TStyleElements() << seBorder; //Tylko Border
	this->Font->Quality = TFontQuality::fqClearType;
  this->ParentFont = true;
	//---
	this->FPMenuBook = new TPopupMenu(this);
	if(!this->FPMenuBook) throw(Exception("Błąd inicjalizacji klasy TPopupMenu"));
	this->FPMenuBook->Images = this->Images;
	this->FPMenuBook->AutoPopup = false;	//Musi być!!!
	this->FPMenuBook->AutoHotkeys = maManual; //Brak podkreśleń
	this->PopupMenu = this->FPMenuBook;
	//this->HotTrack = true;
	this->ParentShowHint = false;
	this->OnHint = this->_OnHint;
	//---
	GsReadBibleTextData::_GsPageControl = pPageControl;	 //Globalny wskażnik na klasę TPageControl, będący polem statycznym klasy GsReadBibleTextData
	GsReadBibleTextData::_GsPageControl->Images = GsReadBibleTextData::_GsImgListData;
	//---
	//TPanel *pPanelText = static_cast<TPanel *>(GsReadBibleTextData::_GsPageControl->Parent);
	//if(pPanelText)
	//{
		//pPanelText->OnDragDrop = GsReadBibleTextData::pGsReadBibleTextClass->_GlobalDragDrop;
		//pPanelText->OnDragOver = GsReadBibleTextData::pGsReadBibleTextClass->_GlobalDragOver;
		//GsReadBibleTextData::_GsPageControl->OnDragDrop = GsReadBibleTextData::pGsReadBibleTextClass->_GlobalDragDrop;
		//GsReadBibleTextData::_GsPageControl->OnDragOver = GsReadBibleTextData::pGsReadBibleTextClass->_GlobalDragOver;
	//}
	//---
	GsReadBibleTextData::pGsTreeBibleClass = this;
	this->OnMouseLeave = this->_OnMouseLeave;
}
//---------------------------------------------------------------------------
__fastcall GsTreeBibleClass::~GsTreeBibleClass()
/**
	OPIS METOD(FUNKCJI): Główny Destruktor, klasy GsTreeBibleClass
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleClass::CreateWnd()
/**
	OPIS METOD(FUNKCJI): Tworzenie kontrolki i kompletnego drzewa ksiąg
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCustomTreeView::CreateWnd();
	//Własny kod
	//this->DoubleBuffered = true;
	this->_pBalloonHint = new TBalloonHint(this);
	if(!this->_pBalloonHint) throw(Exception("Błąd funkcji TBalloonHint"));
	this->_pBalloonHint->Images = GsReadBibleTextData::_GsImgListData;
	this->_pBalloonHint->HideAfter = 1200;
	GsReadBibleTextData::_GsBalloonHint = this->_pBalloonHint;
	this->CustomHint = this->_pBalloonHint;
	this->ShowHint = true;
	this->Hint = Format("Drzewo ksiąg biblijnych|Drzewo ksiąg biblijnych, pokazujące podział Pisma Świętego według standartowego podziału|%u",
		ARRAYOFCONST((enImageIndex_Root)));
	//---
	unsigned char uiLicz=0;	//Licznik ksiąg
	this->Items->BeginUpdate();
	this->Items->Clear();
	GsTreeNodeClass *pNodeMainRoot = this->_AddRootNodeObject("Księgi Biblijne", enTypeRoot_Books);
	if(!pNodeMainRoot) throw(Exception("Błąd inicjalizacji korzenia, drzewa"));
	//---
	for(unsigned char ucIndex=0; ucIndex<GsReadBibleTextData::GsNumberGroups; ++ucIndex)
	//Dodawanie grup bibli do drzewa
	{
		GsTreeNodeClass *pNodeGroup = this->_AddChildNodeObject(pNodeMainRoot, GsReadBibleTextData::GsNamesTableNameGroupBook[ucIndex]);
		if(!pNodeGroup) throw(Exception("Błąd inicjalizacji klasy GsTreeNodeClass"));
		for(int i=0; i<GsReadBibleTextData::GsTableNameGroupBook[ucIndex]; ++i)
		//Dodawanie poszczególnych ksiąg do gróp
		{
			GsTreeNodeClass *pNodeBook = this->_AddChildNodeObject(pNodeGroup, AppCTable_InfoAllBooks[uiLicz].FullNameBook);
			if(!pNodeBook) throw(Exception("Błąd inicjalizacji klasy GsTreeNodeClass"));
			pNodeBook->ucIndexBook = uiLicz; //Numer księgi
			pNodeBook->ucCountChapt = AppCTable_InfoAllBooks[uiLicz].ucCountChapt; //Ilość rozdziałów
			++uiLicz; //Licznik indeksu księgi
		}
	}
	this->FullExpand();	//Drzewo całkowicie rozwinięte
	this->Items->GetFirstNode()->MakeVisible();
	this->Items->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleClass::DestroyWnd()
/**
	OPIS METOD(FUNKCJI): Niszczenie kontrolki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	TCustomTreeView::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleClass::DblClick()
/**
	OPIS METOD(FUNKCJI): Przeciążona metoda, podwójnego kliknięcia
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsTreeNodeClass *pSelectNode = dynamic_cast<GsTreeNodeClass *>(this->Selected);
	if((pSelectNode == 0) || (pSelectNode->Level < 2)) return;

	//---
	GsReadBibleTextData::OpenSelectBookAndChapter(pSelectNode->ucIndexBook+1, 1);
}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleClass::GetImageIndex(TTreeNode* Node)
/**
	OPIS METOD(FUNKCJI): Przyporządkowywanie ikon poszczarólnym gałęziom
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//--- Przyporządkowanie grafik, korzeniu i gałęziom drzewa ksiąg biblijnych
	Node->ImageIndex = Node->Level;
	Node->SelectedIndex = Node->Level;
}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleClass::DoContextPopup(const Types::TPoint &MousePos, bool &Handled)
/**
	OPIS METOD(FUNKCJI): Wirtualna metoda tworzenia podręcznego menu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsTreeNodeClass *pGsTreeNodeClass = dynamic_cast<GsTreeNodeClass *>(this->Selected);
	if((pGsTreeNodeClass == NULL) || (pGsTreeNodeClass->Level < 2))
	//Pozycja w drzewie ksiąg zaznaczona, i pozycja wskazuje na pojedyńczą księge
	{
		TCustomTreeView::DoContextPopup(MousePos, Handled);
		return;
	}
	this->FPMenuBook->Items->Clear();	//Skasowanie wszystkich pozycji z menu podręcznego
	//Tworzenie podręcznego menu rozdziałów
	for(int iIndex=0; iIndex<pGsTreeNodeClass->ucCountChapt; ++iIndex)
	{
		TMenuItem *NewItem = new TMenuItem(this->FPMenuBook);
		if(!NewItem) throw(Exception("Błąd inicjalizacji klasy TMenuItem"));
		this->FPMenuBook->Items->Add(NewItem);
		NewItem->Caption = Format("%u rozdział", ARRAYOFCONST((iIndex + 1)));
		NewItem->Tag = iIndex;
		NewItem->OnClick = this->_SelectPopupTreeBooksExecute;
		NewItem->ImageIndex = enImageIndex_SelectChapter;
		if(iIndex==33 || iIndex==66 || iIndex==99 || iIndex==132) NewItem->Break = mbBarBreak; //08-07-2021 -> 25-08-2021
	}
	TPoint ScrXY = this->ClientToScreen(MousePos);
	this->FPMenuBook->Popup(ScrXY.X, ScrXY.Y);	//Pojawienie się popupmenu

	pGsTreeNodeClass->Selected = true;
	Handled = true;
}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleClass::DragOver(System::TObject* Source, int X, int Y, System::Uitypes::TDragState State, bool &Accept)
/**
	OPIS METOD(FUNKCJI): Przeciąganie
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Accept = Source->ClassNameIs("GsTreeBibleClass");
	Accept = false; //30-03-2021
}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleClass::Resize(void)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleClass::Delete(TTreeNode* Node)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

	GsTreeNodeClass *pGsTreeNodeClass = dynamic_cast<GsTreeNodeClass *>(Node);
	if(pGsTreeNodeClass)
	{
		//delete pGsTreeNodeClass; pGsTreeNodeClass = nullptr; //[30-07-2023]
	}
}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleClass::_CreateNodeClass(TCustomTreeView *Sender, TTreeNodeClass &NodeClass)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	NodeClass = __classid(GsTreeNodeClass);	 //Klasa GsTreeNodeClass, odtąd zastępuje oryginalną TTreeNode
}
//---------------------------------------------------------------------------
GsTreeNodeClass *__fastcall GsTreeBibleClass::_AddRootNodeObject(const UnicodeString &_NameRoot, enTypeRoot _eTypeRoot, void *pObject)
/**
	OPIS METOD(FUNKCJI): Tworzenie "korzenia" dla objektu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TTreeNode *nodeMainRoot = this->Items->AddObject(NULL, _NameRoot, pObject);
	if(!nodeMainRoot) throw(Exception("Błąd inicjalizacji klasy AddObject"));
	GsTreeNodeClass *pGsTreeNodeClass = dynamic_cast<GsTreeNodeClass *>(nodeMainRoot);
	if(!pGsTreeNodeClass) throw(Exception("Błąd konwersji z TTreeNode*, na GsTreeNodeClass*"));
	pGsTreeNodeClass->eTypeRoot = _eTypeRoot; //Typ korzenia, księgi biblijne lub zasoby, lub inne
	return pGsTreeNodeClass;
}
//---------------------------------------------------------------------------
GsTreeNodeClass *__fastcall GsTreeBibleClass::_AddChildNodeObject(const GsTreeNodeClass* pParent, const UnicodeString &ustrNameChild, void *pObject)
/**
	OPIS METOD(FUNKCJI): Dodawanie pozycji do podpozycji
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TTreeNode *pParentObject = dynamic_cast<TTreeNode *>(const_cast<GsTreeNodeClass *>(pParent)); //clang
	//TTreeNode *pParentObject = dynamic_cast<TTreeNode *>(pParent);
	if(!pParentObject) throw(Exception("Błąd konwersji z GsTreeNodeClass*, na TTreeNode*"));
	TTreeNode *childNode = this->Items->AddChildObject(pParentObject, ustrNameChild, pObject);
	GsTreeNodeClass *pGsTreeNodeClass = dynamic_cast<GsTreeNodeClass *>(childNode);
	if(!pGsTreeNodeClass) throw(Exception("Błąd konwersji z TTreeNode*, na GsTreeNodeClass*"));
	pGsTreeNodeClass->eTypeRoot = enTypeRoot_NoRoot; //To nie korzeń
	return pGsTreeNodeClass;
}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleClass::_OnHint(System::TObject* Sender, TTreeNode* const Node, System::UnicodeString &Hint)
/**
	OPIS METOD(FUNKCJI): Wyświetlanie podpowiedzi dla poszczególnych pozycji drzewa
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsTreeNodeClass *pGsTreeNodeClass = dynamic_cast<GsTreeNodeClass *>(Node);
	if(!pGsTreeNodeClass) return;
	//---
	if((pGsTreeNodeClass->HasChildren) || (pGsTreeNodeClass->Level < enTypeNode_Book)) return; //Jeśli posiada dziecko, to wyjdź z metody
	//---
	TRect NodeRect = Node->DisplayRect(true);
	TPoint HintPoint = ClientToScreen(TPoint(NodeRect.Left, NodeRect.Top)); //Konwersja na współrzędne ekranowe
	//---
	if(pGsTreeNodeClass->ucIndexBook <= GsReadBibleTextData::GsPairsGroupBible[en_GrSearch_FullAll].ucStopRange) //Księgi Pisma Świętego
	{
		this->_pBalloonHint->Title = pGsTreeNodeClass->Text;
		if((pGsTreeNodeClass->ucIndexBook >= GsReadBibleTextData::GsPairsGroupBible[en_GrSearch_Old].ucStartRange) &&
			 (pGsTreeNodeClass->ucIndexBook <= GsReadBibleTextData::GsPairsGroupBible[en_GrSearch_Old].ucStopRange))	//Stary Testament
		{
			this->_pBalloonHint->Description = Format("%s.Stary Tetament. Księga numer: [%s]", ARRAYOFCONST((pGsTreeNodeClass->Text, UnicodeString(pGsTreeNodeClass->ucIndexBook+1))));
		}
		else if((pGsTreeNodeClass->ucIndexBook >= GsReadBibleTextData::GsPairsGroupBible[en_GrSearch_New].ucStartRange) &&
						(pGsTreeNodeClass->ucIndexBook <= GsReadBibleTextData::GsPairsGroupBible[en_GrSearch_New].ucStopRange))	//Nowy Testament
		{
			this->_pBalloonHint->Description = Format("%s.Nowy Tetament. Księga numer: [%s]", ARRAYOFCONST((pGsTreeNodeClass->Text, UnicodeString(pGsTreeNodeClass->ucIndexBook+1))));
		}
		else if(pGsTreeNodeClass->ucIndexBook >= GsReadBibleTextData::GsPairsGroupBible[en_GrSearch_Apocr].ucStartRange &&
					 (pGsTreeNodeClass->ucIndexBook <= GsReadBibleTextData::GsPairsGroupBible[en_GrSearch_Apocr].ucStopRange) )	//Księgi Apokryficzne
		{
			this->_pBalloonHint->Description = Format("%s.Księgi Apokryficzne. Księga numer: [%s]", ARRAYOFCONST((pGsTreeNodeClass->Text, UnicodeString(pGsTreeNodeClass->ucIndexBook+1))));
		}
		this->_pBalloonHint->ShowHint(HintPoint);
	}
}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleClass::_SelectPopupTreeBooksExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Metoda wywoływana podczas wybranie pozycji w menu podręcznym
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TMenuItem *pItem = dynamic_cast<TMenuItem *>(Sender);
	if(!pItem) return;
	//---
	GsTreeNodeClass *pGsTreeNodeClass = dynamic_cast<GsTreeNodeClass *>(this->Selected);
	if((pGsTreeNodeClass == 0) || (pGsTreeNodeClass->Level < 2)) return;
	GsReadBibleTextData::OpenSelectBookAndChapter(pGsTreeNodeClass->ucIndexBook+1, pItem->Tag+1);
}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleClass::_SectionHeaderResize(THeaderControl* HeaderControl, THeaderSection* Section)
/**
	OPIS METOD(FUNKCJI): Metoda wywoływana podczas zmiany sekcji nagłówka
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall GsTreeBibleClass::_OnMouseLeave(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Metoda wywoływana podczas wyjścia wskaźnika myszy poza objekt //[02-11-2019]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TTabSheet *pTabSheet = dynamic_cast<TTabSheet *>(this->Parent);
	if(!pTabSheet) return;
	//---
	if(pTabSheet->OnMouseLeave)
	{
		pTabSheet->OnMouseLeave(pTabSheet);
	}
}
/****************************************************************************
*											Klasa GsListBoxSelectedVersClass											*
*****************************************************************************/
__fastcall GsListBoxSelectedVersClass::GsListBoxSelectedVersClass(TComponent* Owner) : TCustomListBox(Owner)
/**
	OPIS METOD(FUNKCJI): Główny konstruktor, klasy GsListBoxSelectedVersClass
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//this->DoubleBuffered = true;
	this->Style = lbOwnerDrawVariable;
	//this->StyleElements = TStyleElements();
	this->MultiSelect = true; this->ExtendedSelect = false;
	this->Color = clCream;
	this->iRIndex = -1;	 //Aktywna pozycja, po kliknięciu prawym przyciskiem myszy, lub -1
	this->Font->Quality = TFontQuality::fqClearType;
	this->ParentFont = true;
}
//---------------------------------------------------------------------------
__fastcall GsListBoxSelectedVersClass::~GsListBoxSelectedVersClass()
/**
	OPIS METOD(FUNKCJI): Główny destruktor, klasy GsListBoxSelectedVersClass
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
void __fastcall GsListBoxSelectedVersClass::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCustomListBox::CreateWnd();
	//Własny kod.
}
//---------------------------------------------------------------------------
void __fastcall GsListBoxSelectedVersClass::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	TCustomListBox::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsListBoxSelectedVersClass::DrawItem(int Index, const TRect &Rect, TOwnerDrawState State)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	MyObjectVers *pMyObjectVers = static_cast<MyObjectVers *>(this->Items->Objects[Index]);
	if(!pMyObjectVers) return;
	//--- Kolory aktywnego stylu //[16-12-2023]
	//TColor cText = TStyleManager::ActiveStyle->GetStyleFontColor(sfListItemTextNormal);

	//this->Canvas->Brush->Color = cBackGround;
	TCanvas *pCanvas = this->Canvas;
	const int ciLeftOffset=8;
	TRect MyRect(Rect), CRect(0, Rect.Top, ciLeftOffset, Rect.Bottom);
	//Gdy pusta pozycja, kolor zaznaczenia systemowy
	//pCanvas->Font->Color = cText;
	UnicodeString ustrText;
	//Adres wersetu
	ustrText = this->Items->Strings[Index];
	//---
	if(State.Contains(odSelected) && !this->Items->Strings[Index].IsEmpty())
	{
		pCanvas->Brush->Color = clWebDarkTurquoise;
		pCanvas->Font->Color = clRed;
		pCanvas->Font->Style = TFontStyles() << fsBold;
	}
	pCanvas->FillRect(Rect);
	//---
	if(!this->Items->Strings[Index].IsEmpty())
	{
		MyRect.Inflate(-ciLeftOffset, 0, -4, 0);
		DrawText(pCanvas->Handle, pMyObjectVers->BookChaptVers.c_str(), -1, &MyRect, DT_SINGLELINE | DT_VCENTER);
		if(this->iRIndex==Index)
		{
			pCanvas->Brush->Color = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorBackgroundMarkerComment, clYellow);
			pCanvas->Font->Color = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorCommentVers, clLime);
			pCanvas->Font->Style = TFontStyles() << fsBold << fsUnderline;
			DrawText(pCanvas->Handle, L"C", -1, &CRect, DT_SINGLELINE | DT_VCENTER);
		}
	}
	/*
	else
	{
		pCanvas->Pen->Color = clRed;
		pCanvas->MoveTo(Rect.Left + 1, (Rect.Bottom - Rect.Top) / 2 + Rect.Top);
		pCanvas->LineTo(Rect.Right - 1, (Rect.Bottom - Rect.Top) / 2 + Rect.Top);
	}
	*/
	//---Zlikwidowanie obramówki w wybranej pozycji
	if(State.Contains(odFocused)) pCanvas->DrawFocusRect(Rect);
}
//---------------------------------------------------------------------------
void __fastcall GsListBoxSelectedVersClass::Click()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	UnicodeString ustrSelect = this->Items->Strings[this->ItemIndex];
	int iIndex = GlobalVar::Global_HSListAllFavoritiesVers->IndexOf(ustrSelect);

	if((iIndex == -1) && this->Selected[this->ItemIndex])
	{
		GlobalVar::Global_HSListAllFavoritiesVers->Add(ustrSelect);
	}
	else if((iIndex > -1) && !this->Selected[this->ItemIndex])
	{
		GlobalVar::Global_HSListAllFavoritiesVers->Delete(iIndex);
	}
	//Uaktualnienie wyświetlania aktualnego rozdziału, z zaznaczonymi, lub nie, ulubionymi wersetami
	GsTabSheetClass *pGsTabSheetClass = dynamic_cast<GsTabSheetClass *>(GsReadBibleTextData::_GsPageControl->ActivePage); //Aktualna zakładka 07-01-2019
	//Powtórne wczytanie tekstu rozdziału [07-01-2019][14-04-2024 - wyświetlanie na tym samym tłumaczeniu, a nie na wszystkich]
	if(pGsTabSheetClass) GsReadBibleTextData::pGsReadBibleTextClass->DisplayAllTextInHTML(pGsTabSheetClass->pWebBrowser, pGsTabSheetClass->pGsTabSetClass->TabIndex-1);
	//Uaktualnienie listy ulubionych wersetów, w głównym oknie, na zakładce
	if(GsReadBibleTextData::pGsListBoxFavoritiesClass)
	{
		GsReadBibleTextData::pGsListBoxFavoritiesClass->ReLoadFavList();
	}
}
//---------------------------------------------------------------------------
void __fastcall GsListBoxSelectedVersClass::MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(Button != mbRight) return;
	this->iRIndex = this->ItemAtPos(TPoint(X, Y), true);
	if(this->iRIndex == -1) return;
	UnicodeString ustrPathComm = TPath::Combine(GlobalVar::Global_custrPathDirComments, this->Items->Strings[this->iRIndex]) + GlobalVar::Global_custrExtendCommentsFiles;
	GsTabSheetClass *pGsTabSheetClass = dynamic_cast<GsTabSheetClass *>(GsReadBibleTextData::_GsPageControl->ActivePage);
	this->Refresh();
	if(pGsTabSheetClass)
	{
		//Uruchomienie edycji
		pGsTabSheetClass->pToolButtonEdit->Down = true; pGsTabSheetClass->_OnClickToolButton(pGsTabSheetClass->pToolButtonEdit);
		pGsTabSheetClass->pGsEditorClass->LoadEditorFromFile(ustrPathComm);
	}
	if(!TFile::Exists(ustrPathComm)) pGsTabSheetClass->pGsEditorClass->ClearEditor(); //Wyczyszczenie edytora
}
/****************************************************************************
 *														KLASA GsTabSheetClass													*
 ****************************************************************************/
__fastcall GsTabSheetClass::GsTabSheetClass(TComponent* Owner) : TTabSheet(Owner)
/**
	OPIS METOD(FUNKCJI): Główny konstruktor, klasy GsTabSheetClass
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass)
		throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	GsReadBibleTextData::_GsPageControl->Visible = true; //01-02-2020
	TToolButton *pToolButton = nullptr;
	// Odczyt domyślnego ustawienia // [01-09-2025]
	this->iGetDefaultTranslate = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ParametersSetupsSearch_Main,
		GlobalVar::GlobalIni_Translate, 0) + 1;
	//---
	//this->DoubleBuffered = true;
	//this->StyleElements = TStyleElements();
	this->Font->Quality = TFontQuality::fqClearType;
  this->ParentFont = true;
	//---
	//Lista surowa aktualnie przegladanego rozdziału 25-08-2021
	//Będzie służyła do wyświetlania w objekcie klasy TControlList, który zastąpi sposób wyświetlania w formie html
	this->pHSListActualText = new THashedStringList();
	if(!this->pHSListActualText) throw(Exception("Błąd inicjalizacji klasy THashedStringList"));
	this->pHSlistResultSearchSelectWord = new THashedStringList(); // Lista wyszkanych miejsc wystepowania zaznaczonego słowa
	if(!this->pHSlistResultSearchSelectWord) throw(Exception("Błąd inicjalizacji klasy THashedStringList"));
	//---
	this->PageControl = GsReadBibleTextData::_GsPageControl; //Umieszczanie objektu klasy na objekcie typu TPageControl
	this->PageControl->ActivePage = this; //Nowostworzona zakładka, staje się zakładką aktualną
	this->OnDragDrop = GsReadBibleTextData::pGsReadBibleTextClass->GlobalTextDragDrop;
	this->OnDragOver = GsReadBibleTextData::pGsReadBibleTextClass->_GlobalTextDragOver;
	this->ImageIndex = enImageIndex_SelectChapter;
	//Panel na TToolBar
	TPanel *pPanelBox = new TPanel(this);
	if(!pPanelBox) throw(Exception("Błąd inicjalizacji klasy TPanel"));
	pPanelBox->Parent = this;
	pPanelBox->Align = alTop;
	pPanelBox->Height = 24;//38;
	pPanelBox->BorderStyle = bsNone;
	pPanelBox->BevelOuter = bvNone;
	pPanelBox->ShowCaption = false;
	pPanelBox->Font->Quality = TFontQuality::fqClearType;

	this->_InitControlsSelectWord(pPanelBox); // Kontrolka(i) do wyświetlania i podejmowania akcji z wybranym słowem z rozdziału // [30-08-2025]
	this->_InitCBoxChaptersSelect(pPanelBox); //Inicjalizacja objektu klasy TComboBox do wybierania rozdziałów w bierzacej zakładce
	this->_InitToolBarAllButtons(pPanelBox); //Inicjalizacja głównego objektu klasy TToolBar ze wszystkimi przyciskami
	this->_InitToolBarViewText(pPanelBox); //Inicjalizacja objektu klasy TToolbar do zmieniania widoków wyświetlanych wersetów
	this->_InitTabSetDisplayTranslates(); //Stworzenie dolnego objektu, klasy GsTabSetClass, do wyboru wyświetlania
	this->_InitPanelInfoTranslation(); //Panel z objektami informacyjnymi o wybranym tłumaczeniu
	this->_DisplayInfosTranslates(); //Metoda wyświetla informacje o przekładach i wybranym rozdziale
	//Inicjalizacja panelu, dla wyświetlania kontrolek, związanych z tekstem.
	TPanel *pPanelText = new TPanel(this);
	if(!pPanelText) throw(Exception("Błąd inicjalizacji klasy TPanel"));
	pPanelText->Parent = this;
	pPanelText->Align = alClient;
	pPanelText->BevelOuter = bvNone;
	pPanelText->BorderStyle = bsNone;
	pPanelText->ShowCaption = false;
	pPanelText->OnDragDrop = this->OnDragDrop;
	pPanelText->OnDragOver = this->OnDragOver;
	pPanelText->Font->Quality = TFontQuality::fqClearType;
	this->_InitPanelTextBible(pPanelText); //Kontrolki dotyczące tekstu biblijnego: TProgressBar, TWebBrowser,
																				 //GsListBoxSelectedVersClass, GsEditorClass
	//Splitter
	this->pSplitterEd = new TSplitter(pPanelText);
	if(!this->pSplitterEd) throw(Exception("Błąd inicjalizacji klasy TSplitter"));
	this->pSplitterEd->Parent = pPanelText;
	this->pSplitterEd->Align = alBottom;
	this->pSplitterEd->Color = clMaroon;
	this->pSplitterEd->MinSize = this->pGsEditorClass->Height / 2;
	this->pSplitterEd->Visible = false;
	//Aktywacja wczytanego tekstu
	this->pWebBrowser->SetFocus();
	this->_InitPanelSearchSelectWordResult(); // Panel z wynikami wyszukiwania
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_InitPanelInfoTranslation()
/**
	OPIS METOD(FUNKCJI): Panel z objektami informacyjnymi o wybranym tłumaczeniu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->pPanelInfoTraslates = new TPanel(this);
	if(!this->pPanelInfoTraslates) throw(Exception("Błąd inicjalizacji klasy TPanel"));
	this->pPanelInfoTraslates->Parent = this;
	this->pPanelInfoTraslates->Align = alBottom;
	this->pPanelInfoTraslates->Height = 128;
	this->pPanelInfoTraslates->ShowCaption = false;
	this->pPanelInfoTraslates->BorderStyle = bsSingle;
	this->pPanelInfoTraslates->Font->Quality = TFontQuality::fqClearType;
	//---
	this->pWebBrowserInfoTranslations = new TWebBrowser(this->pPanelInfoTraslates);
	if(!this->pWebBrowserInfoTranslations) throw(Exception("Błąd inicjalizacji klasy TWebBrowser"));
	this->pWebBrowserInfoTranslations->TOleControl::Parent = this->pPanelInfoTraslates;
	this->pWebBrowserInfoTranslations->Align = alClient;
	this->pWebBrowserInfoTranslations->Offline = true;
	this->pWebBrowserInfoTranslations->Navigate(WideString("about:blank").c_bstr()); // wypełnienie kontrolki pustą stroną.
	this->pPanelInfoTraslates->Visible = false;
	this->pWebBrowserInfoTranslations->Visible = this->pPanelInfoTraslates->Visible;
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_InitPanelTextBible(TPanel *pPanelParent)
/**
	OPIS METOD(FUNKCJI): Kontrolki dotyczące tekstu biblijnego: TProgressBar, TWebBrowser,
											 GsListBoxSelectedVersClass, GsEditorClass
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//---Inicjalizacja pionowego wskaźnika, umiejscowienia pozycji w rozdziale
	this->pProgressBar = new TProgressBar(pPanelParent);
	this->pProgressBar->Parent = pPanelParent;
	this->pProgressBar->Align = alRight;
	this->pProgressBar->Orientation = pbVertical;
	this->pProgressBar->Width = 8;
	this->pProgressBar->BarColor = clRed;
	this->pProgressBar->CustomHint = GsReadBibleTextData::_GsBalloonHint;
	this->pProgressBar->ShowHint = true;
	//SendMessage(this->pProgressBar->Handle, PBM_SETBARCOLOR, 0, clBlue);
	this->pProgressBar->Hint = Format("Pozycja w księdze|Pionowy pasek pokazujący pozycje wybranego rozdziału, względem całej księgi|%u",
		ARRAYOFCONST((enImageIndex_InfoHelp)));
	//---Inicjalizacja objektu, klasy TWebBrowser
	this->pWebBrowser = new TWebBrowser(pPanelParent);
	if(!this->pWebBrowser) throw(Exception("Błąd inicjalizacji klasy TWebBrowser"));
	//pPanelParent->InsertControl(this->pWebBrowser); //Też działa
	this->pWebBrowser->TOleControl::Parent = pPanelParent;
	this->pWebBrowser->Align = alClient;
	this->pWebBrowser->Offline = true;
	this->pWebBrowser->Navigate(WideString("about:blank").c_bstr()); // wypełnienie kontrolki pustą strony.
	this->pWebBrowser->OnDragDrop = pPanelParent->OnDragDrop;
	this->pWebBrowser->OnDragOver = pPanelParent->OnDragOver;
	this->pWebBrowser->OnDocumentComplete = this->_OnDocumentComplete; //[31-07-2023]
	this->pWebBrowser->OnBeforeNavigate2 = this->_OnBeforeNavigate2; // [29-08-2025]
	//Wybieralny tekst rozdziału
	this->pLBoxSelectText = new GsListBoxSelectedVersClass(pPanelParent);
	if(!this->pLBoxSelectText) throw(Exception("Błąd inicjalizacji klasy GsListBoxSelectedVersClass"));
	this->pLBoxSelectText->Parent = pPanelParent;
	this->pLBoxSelectText->Align = alLeft;
	this->pLBoxSelectText->Width = 98;
	this->pLBoxSelectText->Visible = false;
	this->pLBoxSelectText->Font->Quality = TFontQuality::fqClearType;
	//Edycja komentarza do wybranego wersetu, lub rozdziału
	this->pGsEditorClass = new GsEditorClass(pPanelParent);
	if(!this->pGsEditorClass) throw(Exception("Błąd inicjalizacji klasy GsEditorClass"));
	this->pGsEditorClass->Parent = pPanelParent;
	this->pGsEditorClass->Align = alBottom;
	this->pGsEditorClass->Height = 160;
	this->pGsEditorClass->Visible = false;
	this->pGsEditorClass->OnSave = this->_OnSaveComments;
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_InitPanelSearchSelectWordResult()
/**
	OPIS METOD(FUNKCJI): Otwarcie panelu z wynikami wyszukiwania zaznaczonego słowa // [31-08-2025]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  TForm *pMainWindow = Application->MainForm;
	if(!pMainWindow) throw(Exception("Błąd wyłuskania wskaźnika do głównego okna"));
	//---
	this->pPanelSelectWordResult = new TPanel(this);
	if(!this->pPanelSelectWordResult) throw(Exception("Błąd inicjalizacji klasy TPanel"));
	this->pPanelSelectWordResult->Parent = this;
	this->pPanelSelectWordResult->Left = this->pButtSearchSelectWord->Left;
	this->pPanelSelectWordResult->Top = this->pButtSearchSelectWord->Parent->Top;// + this->pButtSearchSelectWord->Parent->Height + 1;
	this->pPanelSelectWordResult->Width = this->Width - this->pButtSearchSelectWord->Left - 38;
	this->pPanelSelectWordResult->Height = 700;
	this->pPanelSelectWordResult->Visible = false;
	this->pPanelSelectWordResult->OnMouseLeave = this->_OnMouseLeave;
	//---
	this->pCListResultSearchSelectWord = new TControlList(this->pPanelSelectWordResult);
	if(!this->pCListResultSearchSelectWord) throw(Exception("Błąd inicjalizacji klasy TControlList"));
	this->pCListResultSearchSelectWord->Parent = this->pPanelSelectWordResult;
	this->pCListResultSearchSelectWord->Align = alClient;
	this->pCListResultSearchSelectWord->AlignWithMargins = true;
	this->pCListResultSearchSelectWord->Font->Size = 10;
	this->pCListResultSearchSelectWord->ItemHeight = 7 * -this->pCListResultSearchSelectWord->Font->Height - 4;
	this->pCListResultSearchSelectWord->OnBeforeDrawItem = this->_OnBeforeDrawItemControlList;
	this->pCListResultSearchSelectWord->OnItemClick = this->_OnItemClickControlList;
	//---
	this->pLabelItemResultSearchSelectWord = new TLabel(this);
	if(!this->pLabelItemResultSearchSelectWord) throw(Exception("Błąd inicjalizacji klasy TLabel"));
	this->pLabelItemResultSearchSelectWord->Align = alClient;
	this->pLabelItemResultSearchSelectWord->AutoSize = false;
	this->pLabelItemResultSearchSelectWord->AlignWithMargins = true;
	this->pLabelItemResultSearchSelectWord->Layout = tlCenter;
  this->pLabelItemResultSearchSelectWord->WordWrap = true;
	//---
	this->pLabelItemAddressResult = new TLabel(this);
	if(!this->pLabelItemAddressResult) throw(Exception("Błąd inicjalizacji klasy TLabel"));
	this->pLabelItemAddressResult->Align = alLeft;
	this->pLabelItemAddressResult->Width = 68;
	this->pLabelItemAddressResult->AutoSize = false;
	this->pLabelItemAddressResult->AlignWithMargins = true;
	this->pLabelItemAddressResult->Layout = tlCenter;
	this->pLabelItemAddressResult->StyleElements = TStyleElements() << seClient << seBorder;
	this->pLabelItemAddressResult->Font->Size = 10;
	this->pLabelItemAddressResult->Font->Style = TFontStyles() << fsBold;
	this->pLabelItemAddressResult->Font->Color = clRed;

	this->pCListResultSearchSelectWord->AddControlToItem(this->pLabelItemAddressResult);
	this->pCListResultSearchSelectWord->AddControlToItem(this->pLabelItemResultSearchSelectWord);
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_OnBeforeDrawItemControlList(int AIndex, Vcl::Graphics::TCanvas* ACanvas,
		const System::Types::TRect &ARect, Winapi::Windows::TOwnerDrawState AState)
/**
	OPIS METOD(FUNKCJI): Zdarzenie listy resultatów wyszukiwania zaznaczonego słowa // [31-08-2025]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if((AIndex < 0) || (AIndex >= this->pHSlistResultSearchSelectWord->Count)) return;

	MyObjectVers *pMyObjectVers = static_cast<MyObjectVers *>(this->pHSlistResultSearchSelectWord->Objects[AIndex]);
	if(!pMyObjectVers) return;

	this->pLabelItemAddressResult->Caption = pMyObjectVers->BookChaptVers;
	this->pLabelItemResultSearchSelectWord->Caption = this->pHSlistResultSearchSelectWord->Strings[AIndex].SubString(11, GlobalVar::Global_MaxlengthVers);
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_OnItemClickControlList(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI): Klikniecie na pozycję listy resultatów wyszukiwania zaznaczonego słowa // [14-09-2025]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TControlList *pCList = dynamic_cast<TControlList *>(Sender);
	if(!pCList) return;
	//---
	MyObjectVers *pMyObjectVers = static_cast<MyObjectVers *>(this->pHSlistResultSearchSelectWord->Objects[pCList->ItemIndex]);
	if(!pMyObjectVers) return;
//  #if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("Trans: %d, Book: %d, Chapt: %d",
//			ARRAYOFCONST((this->pGsTabSetClass->TabIndex-1, pMyObjectVers->ucBook, pMyObjectVers->ucChapt))));
//	#endif

	this->pPanelSelectWordResult->Visible = false;

	//GsReadBibleTextData::pGsReadBibleTextClass->GetAllTranslatesChapter(pMyObjectVers->ucBook, pMyObjectVers->ucChapt-1);
	//Wyświetl tekst dla wszystkich tłumaczeń, lub wybranego.
	//GsReadBibleTextData::pGsReadBibleTextClass->DisplayAllTextInHTML(this->pWebBrowser, this->pGsTabSetClass->TabIndex-1);
	this->pComboBox->ItemIndex = pMyObjectVers->ucChapt-1;
	this->_OnSelectBoxChapter(this->pComboBox);
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_OnMouseLeave(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI): Mysz poza objekt, klasy TControlList, list wersetów ze słowem zaznaczonym // [31-08-2025]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
//	TControlList *pCList = dynamic_cast<TControlList *>(Sender);
//	if(!pCList) return;
	//---
	this->pPanelSelectWordResult->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_InitToolBarViewText(TPanel *pPanelParent)
/**
	OPIS METOD(FUNKCJI): Inicjalizacja objektu klasy TToolbar do zmieniania widoków wyświetlanych wersetów
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TToolButton *pToolButton = nullptr;
	const UnicodeString NameTextButtons[] = {"Widok do czytania", "Widok do wybierania wersetów"};

	this->pToolBarText = new TToolBar(pPanelParent);
	if(!this->pToolBarText) throw(Exception("Błąd inicjalizacji klasy TToolBar"));
	//this->pToolBarText->StyleElements = TStyleElements();
	this->pToolBarText->Parent = pPanelParent;
	this->pToolBarText->AutoSize = true;
	this->pToolBarText->Align = alLeft;
	this->pToolBarText->Flat = true;
	this->pToolBarText->Images = GsReadBibleTextData::_GsImgListData;
	this->pToolBarText->DisabledImages = GsReadBibleTextData::_GsImgListDataDisable;
	this->pToolBarText->DrawingStyle = (Vcl::Comctrls::TTBDrawingStyle)Vcl::Comctrls::gdoGradient;
	this->pToolBarText->HotTrackColor = clGreen;//clWebCornFlowerBlue;
	//--- Przyciski widoków na toolbarze
	for(int i=ARRAYSIZE(NameTextButtons)-1; i>=0; i--)
	{
		pToolButton = new TToolButton(this->pToolBarText);
		if(!pToolButton) throw(Exception("Błąd inicjalizacji klasy TToolButton"));
		pToolButton->Parent = this->pToolBarText;
		pToolButton->ImageIndex = enImageIndex_ReadOnlyText - i;
		pToolButton->Tag = pToolButton->ImageIndex;
		pToolButton->ShowHint = true;
		pToolButton->OnClick = this->_OnClickToolButton;
		pToolButton->Grouped = true;
		pToolButton->Style = tbsCheck;
		pToolButton->CustomHint = GsReadBibleTextData::_GsBalloonHint;
		if(pToolButton->ImageIndex == enImageIndex_ReadOnlyText)
		{
			pToolButton->Down = true;		//Obraz widoku tekstu biblijnego tylko do przeglądania
			pToolButton->Hint = Format("Widok do przeglądania|Widoku tekstu biblijnego tylko do przeglądania|%u", ARRAYOFCONST((pToolButton->ImageIndex)));
		}
		else if(pToolButton->ImageIndex == enImageIndex_ViewSelectText)
		{
			pToolButton->Hint = Format("Widok do przeglądania i wybierania wersetów|Widoku tekstu biblijnego do przeglądania, oraz wybierania wersetów z aktualnego rozdziału|%u", ARRAYOFCONST((pToolButton->ImageIndex)));
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_InitToolBarAllButtons(TPanel *pPanelParent)
/**
	OPIS METOD(FUNKCJI): Inicjalizacja głównego objektu klasy TToolBar ze wszystkimi przyciskami
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TToolButton *pToolButton = nullptr;

	this->pToolBar = new TToolBar(pPanelParent);
	if(!this->pToolBar) throw(Exception("Błąd inicjalizacji klasy TToolBar"));
	//this->pToolBar->StyleElements = TStyleElements();
	this->pToolBar->Parent = pPanelParent;
	this->pToolBar->AutoSize = true;
	this->pToolBar->Align = alLeft;
	this->pToolBar->Flat = true;
	this->pToolBar->Images = GsReadBibleTextData::_GsImgListData;
	this->pToolBar->DisabledImages = GsReadBibleTextData::_GsImgListDataDisable;
	this->pToolBar->DrawingStyle = (Vcl::Comctrls::TTBDrawingStyle)Vcl::Comctrls::gdoGradient;
	this->pToolBar->HotTrackColor = clWebDarkOrange;
		//--- Przyciski nawigacji i innych na toolbarze
	//Wyświetlanie informacji o wybranym tłumaczeniu, lub tłumaczeniach, oraz rozdziałach
	this->pToolButtonInfoTranslates = new TToolButton(this->pToolBar);
	if(!this->pToolButtonInfoTranslates) throw(Exception("Błąd inicjalizacji klasy TToolButton"));
	this->pToolButtonInfoTranslates->Parent = this->pToolBar;
	this->pToolButtonInfoTranslates->ImageIndex = enImageIndex_DisplayInfoTranslates;
	this->pToolButtonInfoTranslates->ShowHint = true;
	this->pToolButtonInfoTranslates->Tag = this->pToolButtonInfoTranslates->ImageIndex;
	this->pToolButtonInfoTranslates->OnClick = this->_OnClickToolButton;
	this->pToolButtonInfoTranslates->AllowAllUp = true;
	this->pToolButtonInfoTranslates->Style = tbsCheck;
	this->pToolButtonInfoTranslates->CustomHint = GsReadBibleTextData::_GsBalloonHint;
	this->pToolButtonInfoTranslates->Hint = Format("Informacje o przekładach|Wyświetlenie informacji o wszystkich, dostępnych przekładach, lub o bierzącym przekładzie i rozdziale|%u", ARRAYOFCONST((this->pToolButtonInfoTranslates->ImageIndex)));
	//Rozpoczęcie edycji komentarza do zaznaczonego wersetu
	this->pToolButtonEdit = new TToolButton(this->pToolBar);
	if(!this->pToolButtonEdit) throw(Exception("Błąd inicjalizacji klasy TToolButton"));
	this->pToolButtonEdit->Parent = this->pToolBar;
	this->pToolButtonEdit->ImageIndex = enImageIndex_EditText;
	this->pToolButtonEdit->ShowHint = true;
	this->pToolButtonEdit->Tag = this->pToolButtonEdit->ImageIndex;
	this->pToolButtonEdit->OnClick = this->_OnClickToolButton;
	this->pToolButtonEdit->AllowAllUp = true;
	this->pToolButtonEdit->Style = tbsCheck;
	this->pToolButtonEdit->CustomHint = GsReadBibleTextData::_GsBalloonHint;
	this->pToolButtonEdit->Hint = Format("Otwarcie edytora|Otwarcie edytora i rozpoczęcie redagowania komentarza do wybranego rozdziału|%u", ARRAYOFCONST((this->pToolButtonEdit->ImageIndex)));
		//Przewijanie rozdziałów
	for(int i=enImageIndex_ToPrevBook; i>=enImageIndex_ToNextBook; i--)
	{
		pToolButton = new TToolButton(this->pToolBar);
		if(!pToolButton) throw(Exception("Błąd inicjalizacji klasy TToolButton"));
		pToolButton->Parent = this->pToolBar;
		pToolButton->ImageIndex = i;
		pToolButton->ShowHint = true;
		pToolButton->Tag = pToolButton->ImageIndex;
		pToolButton->OnClick = this->_OnClickToolButton;
		pToolButton->CustomHint = GsReadBibleTextData::_GsBalloonHint;
		//---
		if(i == enImageIndex_ToNextBook)
			pToolButton->Hint = Format("Wybór następnej księgi|Przewinięcie do następnej księgi|%u", ARRAYOFCONST((i)));
		else if(i == enImageIndex_PrevChapter)
			pToolButton->Hint = Format("Poprzedni rozdział|Przewinięcie zawartości wybranej księgi do poprzedniego rozdziału|%u", ARRAYOFCONST((i)));
		else if(i == enImageIndex_NextChapter)
			pToolButton->Hint = Format("Następny rozdział|Przewinięcie zawartości wybranej księgi do następnego rozdziału|%u", ARRAYOFCONST((i)));
		else if(i == enImageIndex_ToPrevBook)
			pToolButton->Hint = Format("Wybór poprzedniej księgi|Przewinięcie do poprzedniej księgi|%u", ARRAYOFCONST((i)));
	}
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_InitCBoxChaptersSelect(TPanel *pPanelParent)
/**
	OPIS METOD(FUNKCJI): Inicjalizacja objektu klasy TComboBox do wybierania rozdziałów w bierzacej zakładce
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Wyłuskanie aktywnego objektu, klasy GsTreeNodeClass, z drzewa ksiąg
	GsTreeNodeClass *pGsTreeNodeClass = dynamic_cast<GsTreeNodeClass *>(GsReadBibleTextData::pGsTreeBibleClass->Selected);
	if(!pGsTreeNodeClass) throw(Exception("Błąd procedury wyłuskania, objektu klasy GsTreeNodeClass"));
	this->pComboBox = new TComboBox(pPanelParent);
	if(!this->pComboBox) throw(Exception("Błąd inicjalizacji klasy TComboBox"));
	this->pComboBox->Parent = pPanelParent;
	this->pComboBox->Font->Quality = TFontQuality::fqClearType;
	this->pComboBox->Align = alLeft;
	this->pComboBox->AlignWithMargins = true;
	this->pComboBox->Margins->Left = 4; this->pComboBox->Margins->Right = 4;
	int iITempMargin = (pPanelParent->Height - this->pComboBox->Height) / 2;
	this->pComboBox->Margins->Top = iITempMargin; this->pComboBox->Margins->Bottom = iITempMargin;
	this->pComboBox->OnSelect = this->_OnSelectBoxChapter;
	this->pComboBox->Width = 160;
	this->pComboBox->Style = csOwnerDrawFixed;
	this->pComboBox->OnDrawItem = this->_OnSelectChaptCBoxDrawItem;
	this->pComboBox->CustomHint = GsReadBibleTextData::_GsBalloonHint;;
	this->pComboBox->ShowHint = true;
	this->pComboBox->Hint = "Wybór rozdziału|Wybór numeru rozdziału z listy rozdziałów, dostępnych dla wybranej księgi";
			//Tworzenie listy rozdziałów wybranej księgi, dla objektu, klasy TComboBox
	for(int iChapt=0; iChapt<AppCTable_InfoAllBooks[pGsTreeNodeClass->ucIndexBook].ucCountChapt; ++iChapt)
		{this->pComboBox->AddItem(Format("Rozdział %u", ARRAYOFCONST((iChapt + 1))), 0);}
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_InitControlsSelectWord(TPanel *pPanelParent)
/**
	OPIS METOD(FUNKCJI): Kontrolka(i) do wyświetlania i podejmowania akcji
											 z wybranym słowem z rozdziału // [30-08-2025]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TForm *pMainWindow = Application->MainForm;
	if(!pMainWindow) throw(Exception("Błąd wyłuskania wskaźnika do głównego okna"));
	//---
	this->pButtSearchSelectWord = new TButton(pPanelParent);
	if(!this->pButtSearchSelectWord) throw(Exception("Błąd inicjalizacji klasy TButton"));
	this->pButtSearchSelectWord->Parent = pPanelParent;
	this->pButtSearchSelectWord->Align = alLeft;
	this->pButtSearchSelectWord->AlignWithMargins = true;
	this->pButtSearchSelectWord->Enabled = false;
	this->pButtSearchSelectWord->Caption = "Wyszukaj zaznaczone słowo";
	this->pButtSearchSelectWord->Width = pMainWindow->Canvas->TextWidth(this->pButtSearchSelectWord->Caption) + 34;
	this->pButtSearchSelectWord->Enabled = false;
	this->pButtSearchSelectWord->Images = GsReadBibleTextData::_GsImgListData;
	this->pButtSearchSelectWord->DisabledImages = GsReadBibleTextData::_GsImgListDataDisable;
	this->pButtSearchSelectWord->ImageIndex = enImageIndex_SearchSelectWord;
	this->pButtSearchSelectWord->DisabledImageIndex = enImageIndex_SearchSelectWord;
  this->pButtSearchSelectWord->OnClick = this->_OnButtonSearchSelectWord;
	//--- Pole tekstowe z wybranym słowem
	this->pLabeledEdit = new TLabeledEdit(pPanelParent);
	if(!this->pLabeledEdit) throw(Exception("Błąd inicjalizacji klasy TLabeledEdit"));
	this->pLabeledEdit->Parent = pPanelParent;
	this->pLabeledEdit->Align = alLeft;
	this->pLabeledEdit->AlignWithMargins = true;
	this->pLabeledEdit->Width = 200;
	this->pLabeledEdit->EditLabel->Caption = "Zaznaczony tekst: ";
	this->pLabeledEdit->ReadOnly = true;
	this->pLabeledEdit->Margins->Top = 1; this->pLabeledEdit->Margins->Bottom = 1;
	this->pLabeledEdit->Margins->Left =  pMainWindow->Canvas->TextWidth(this->pLabeledEdit->EditLabel->Caption) + 8;
	this->pLabeledEdit->LabelPosition = lpLeft;
	//this->pLabeledEdit->Font->Color = clBlue;
	this->pLabeledEdit->Font->Style = TFontStyles() << fsBold;
	//this->pLabeledEdit->StyleElements = TStyleElements() << seClient << seBorder;
	this->pLabeledEdit->OnChange = this->_OnChangeSelectWord;
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_InitTabSetDisplayTranslates()
/**
	OPIS METOD(FUNKCJI): Zakładki z wyborem sposobu wyświetlania tłumaczeń
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	static const UnicodeString custrAllTranslatesTab = "Wszystkie tłumaczenia";

	this->pGsTabSetClass = new GsTabSetClass(this);
	if(!this->pGsTabSetClass) throw(Exception("Błąd inicjalizacji klasy TTabSet"));
	this->pGsTabSetClass->Parent = this;

	this->pGsTabSetClass->Align = alBottom;
	this->pGsTabSetClass->SelectedColor = clRed;
	this->pGsTabSetClass->Tabs->Add(custrAllTranslatesTab);
	this->pGsTabSetClass->CustomHint = GsReadBibleTextData::_GsBalloonHint;
	//this->pGsTabSetClass->Style = tsOwnerDraw;
	this->pGsTabSetClass->Images = GsReadBibleTextData::_GsImgListData;
	this->pGsTabSetClass->ShowHint = true;
	this->pGsTabSetClass->Hint = Format("Wybór żródła do wyświetlenia|Wybór sposobu wyświetlania tekstu, po między widokiem równoległym dla wszystkich tłumaczeń, a widokiem dla jednego, wybranego tłumaczeniai|%u",
		ARRAYOFCONST((enImageIndex_InfoHelp)));
	const int ciGetTrPol = GsReadBibleTextData::pGsReadBibleTextClass->_GsListItemsTranslates->Count; //Ilość polskich tłumaczeń
	//Dodawanie tłumaczeń
	for(int i=0; i<ciGetTrPol; ++i)
	{
		GsReadBibleTextItem *pGsReadBibleTextItem = static_cast<GsReadBibleTextItem *>(GsReadBibleTextData::pGsReadBibleTextClass->_GsListItemsTranslates->Items[i]);
		//Sprawdzanie czy to jest pełne, polskie tłumaczenie
		if(pGsReadBibleTextItem) {if(pGsReadBibleTextItem->enTypeTranslate == enTypeTr_Full) this->pGsTabSetClass->Tabs->Add(pGsReadBibleTextItem->NameTranslate);}
	}
	this->pGsTabSetClass->TabIndex = 0; //Domyślna zakładka rodzaju tłumaczenia (wszyskie tłumaczenia)
}
//---------------------------------------------------------------------------
__fastcall GsTabSheetClass::~GsTabSheetClass()
/**
	OPIS METOD(FUNKCJI): Główny Destruktor, klasy GsTabSheetClass
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Lista surowa aktualnie przegladanego rozdziału 25-08-2021
	//Będzie służyła do wyświetlania w objekcie klasy TControlList, który zastąpi sposób wyświetlania w formie html
	if(this->pHSListActualText)
		{delete this->pHSListActualText; this->pHSListActualText = nullptr;}
  // Lista wyszkanych miejsc wystepowania zaznaczonego słowa
	if(this->pHSlistResultSearchSelectWord)
		{delete this->pHSlistResultSearchSelectWord; this->pHSlistResultSearchSelectWord = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_OnSelectChaptCBoxDrawItem(Vcl::Controls::TWinControl* Control,
	int Index, const System::Types::TRect &Rect, Winapi::Windows::TOwnerDrawState State)
/**
	OPIS METOD(FUNKCJI): Własnoręczne rysowanie objektu, klasy TComboBox, wyboru rozdziałów
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TComboBox *pCBox = dynamic_cast<TComboBox *>(Control);
	if(!pCBox) return;
	//---
	TRect MyRect = Rect;
	TCanvas *pCanvas = pCBox->Canvas;
	if(State.Contains(odSelected))
	{
		pCanvas->Brush->Color = clWebOrangeRed;
		pCanvas->Font->Color = pCBox->Font->Color;
	}

	pCanvas->FillRect(MyRect);
	GsReadBibleTextData::_GsImgListData->Draw(pCanvas, 1, MyRect.Height() / 2 - (GsReadBibleTextData::_GsImgListData->Height / 2) + MyRect.Top, enImageIndex_SelectChapter);
	MyRect.Left += 18;

	DrawText(pCanvas->Handle, pCBox->Items->Strings[Index].c_str(), -1, &MyRect, DT_SINGLELINE | DT_VCENTER);
}
//---------------------------------------------------------------------------
bool __fastcall GsTabSheetClass::_NextChapter()
/**
	OPIS METOD(FUNKCJI): Metody przewijania aktualnej księgi o rozdział w przód
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall GsTabSheetClass::_PrevChapter()
/**
	OPIS METOD(FUNKCJI): Metody przewijania aktualnej księgi o rozdział w tył
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	return true;
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_OnClickToolButton(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI): Kliknięto na przycisk TToolBaru
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TToolButton *pToolButton = dynamic_cast<TToolButton *>(Sender);
	if(!pToolButton) return;
	//---
	switch(pToolButton->Tag)	//Identyfikowanie, który przycisk został wybrany
	{
		case enImageIndex_ToPrevBook:		 //Poprzednia księga
		{
			if(this->_ShucIndexBook > 0)
			{
				this->_ShucIndexBook--;
				this->pComboBox->ItemIndex = 0;	 //Uaktywnienie odpowiedniej pozycji w liście dostępnych rozdziałów
				GsReadBibleTextData::pGsReadBibleTextClass->GetAllTranslatesChapter(this->_ShucIndexBook, 0);
				//Wyświetl tekst dla wszystkich tłumaczeń, lub wybranego.
				GsReadBibleTextData::pGsReadBibleTextClass->DisplayAllTextInHTML(this->pWebBrowser, this->pGsTabSetClass->TabIndex-1);
				//Tworzenie listy rozdziałów wybranej księgi, dla objektu, klasy TComboBox
				this->pComboBox->Clear();
				for(int iChapt=0; iChapt<AppCTable_InfoAllBooks[this->_ShucIndexBook].ucCountChapt; ++iChapt)
					{this->pComboBox->AddItem(Format("Rozdział %u", ARRAYOFCONST((iChapt + 1))), 0);}
				this->pComboBox->ItemIndex = 0;
				this->_DisplayInfosTranslates(this->pGsTabSetClass->TabIndex-1);
			}
		}
		break;
		//---
		case enImageIndex_ToNextBook:		 //Następna księga
		{
			if(this->_ShucIndexBook < GlobalVar::Global_NumberBooks-1)
			{
				++this->_ShucIndexBook;
				this->pComboBox->ItemIndex = 0;	 //Uaktywnienie odpowiedniej pozycji w liście dostępnych rozdziałów
				GsReadBibleTextData::pGsReadBibleTextClass->GetAllTranslatesChapter(this->_ShucIndexBook, 0);
				//Wyświetl tekst dla wszystkich tłumaczeń, lub wybranego.
				GsReadBibleTextData::pGsReadBibleTextClass->DisplayAllTextInHTML(this->pWebBrowser, this->pGsTabSetClass->TabIndex-1);
				//Tworzenie listy rozdziałów wybranej księgi, dla objektu, klasy TComboBox
				this->pComboBox->Clear();
				for(int iChapt=0; iChapt<AppCTable_InfoAllBooks[this->_ShucIndexBook].ucCountChapt; ++iChapt)
					{this->pComboBox->AddItem(Format("Rozdział %u", ARRAYOFCONST((iChapt + 1))), 0);}
				this->pComboBox->ItemIndex = 0;
				this->_DisplayInfosTranslates(this->pGsTabSetClass->TabIndex-1);
			}
		}
		break;
		//---
		case enImageIndex_NextChapter:		 //Następny rozdział
		{
			if(this->_ShucIndexChapt < AppCTable_InfoAllBooks[this->_ShucIndexBook].ucCountChapt-1)
			{
				++this->_ShucIndexChapt; //Następny rozdział
				++this->pComboBox->ItemIndex;	 //Uaktywnienie odpowiedniej pozycji w liście dostępnych rozdziałów
				GsReadBibleTextData::pGsReadBibleTextClass->GetAllTranslatesChapter(this->_ShucIndexBook, this->_ShucIndexChapt);
				//Wyświetl tekst dla wszystkich tłumaczeń, lub wybranego.
				GsReadBibleTextData::pGsReadBibleTextClass->DisplayAllTextInHTML(this->pWebBrowser, this->pGsTabSetClass->TabIndex-1);
				//pToolButton->Enabled = this->_ShucIndexChapt < GsReadBibleTextData::GsInfoAllBooks[this->_ShucIndexBook].ucCountChapt-1;
				this->_DisplayInfosTranslates(this->pGsTabSetClass->TabIndex-1);
			}
		}
		break;
		//---
		case enImageIndex_PrevChapter:		 //Poprzedni rozdział
		{
			if(this->_ShucIndexChapt > 0)
			{
				this->_ShucIndexChapt--; //Poprzedni rozdział
				this->pComboBox->ItemIndex--;	 //Uaktywnienie odpowiedniej pozycji w liście dostępnych rozdziałów
				GsReadBibleTextData::pGsReadBibleTextClass->GetAllTranslatesChapter(this->_ShucIndexBook, this->_ShucIndexChapt);
				//Wyświetl tekst dla wszystkich tłumaczeń, lub wybranego.
				GsReadBibleTextData::pGsReadBibleTextClass->DisplayAllTextInHTML(this->pWebBrowser, this->pGsTabSetClass->TabIndex-1);
				//pToolButton->Enabled = this->_ShucIndexChapt > 0;
				this->_DisplayInfosTranslates(this->pGsTabSetClass->TabIndex-1);
			}
		}
		break;
		//---
		case enImageIndex_ViewSelectText:	//18.Obraz widoku tekstu biblijnego do selekcji wersetów
		{
			this->pLBoxSelectText->Visible = true;
		}
		break;
		//---
		case enImageIndex_ReadOnlyText:		 //19.Obraz widoku tekstu biblijnego tylko do przeglądania
		{
			this->pLBoxSelectText->Visible = false;
		}
		break;
		//---
		case enImageIndex_EditText:	 //20.Edycja komentarza do wybranego wersetu, lub rozdziału
		{
			this->pGsEditorClass->Visible = pToolButton->Down;
			this->pSplitterEd->Visible = pToolButton->Down;
		}
		break;
		//---
		case enImageIndex_DisplayInfoTranslates: //Wyświetlanie informacji o przekładach
		{
			this->pPanelInfoTraslates->Visible = pToolButton->Down;
			this->pWebBrowserInfoTranslations->Visible = pToolButton->Down;
		}
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_OnSelectBoxChapter(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI): Zdarzenie generowane gdy została wybrana pozycja z kontrolki typu TComboBox, służącej do wyboru rozdziału
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TComboBox *pCBox = dynamic_cast<TComboBox *>(Sender);
	if(!pCBox) return;
	//---
	GsReadBibleTextData::pGsReadBibleTextClass->GetAllTranslatesChapter(this->_ShucIndexBook, this->pComboBox->ItemIndex);
	//Wyświetl tekst dla wszystkich tłumaczeń, lub wybranego.
	GsReadBibleTextData::pGsReadBibleTextClass->DisplayAllTextInHTML(this->pWebBrowser, this->pGsTabSetClass->TabIndex-1);
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_OnSaveComments(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI): Zdarzenie OnSave, objektu klasy GsEditorClass
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsEditorClass *pGsEditorClass = dynamic_cast<GsEditorClass *>(Sender);
	if(!pGsEditorClass) return;
	//--- Uaktualnienie objektu, klasy GsListBoxSelectedVersClass,
	//		a jednocześnie ponowne wczytanie wybranego rozdziału, z odpowiednimi znacznikami
	// Uaktualnienie wyświetlania aktualnego rozdziału, z zaznaczonymi, lub nie, wersetami z komentarzem
	GsTabSheetClass *pGsTabSheetClass = dynamic_cast<GsTabSheetClass *>(GsReadBibleTextData::_GsPageControl->ActivePage); //Aktualna zakładka 07-01-2019
	if(pGsTabSheetClass) GsReadBibleTextData::pGsReadBibleTextClass->DisplayAllTextInHTML(pGsTabSheetClass->pWebBrowser);//Powtórne wczytanie tekstu rozdziału 07-01-2019
	// Odswierzenie głównej listy komentarzy w głównym oknie
	GsReadBibleTextData::pGsLViewCommentsAllClass->ReloadAllVersComments(false);
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_OnChangeSelectWord(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI): Zmieniono zawartość pola z wybranym słowem
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TLabeledEdit *pLEdit = dynamic_cast<TLabeledEdit *>(Sender);
	if(!pLEdit) return;
	//---
	// Aby przycisk wyszukiwania słowa był aktywny, pole w wybranym słowm nie może być puste,
	// i niw może być to zakładka z równoległymi tłumaczeniami // 02-09-2025
	this->pButtSearchSelectWord->Enabled = !pLEdit->Text.IsEmpty() && (this->pGsTabSetClass->TabIndex > 0);
//  #if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("pGsTabSetClass->TabIndex: %d", ARRAYOFCONST((pGsTabSetClass->TabIndex))));
//	#endif
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_OnButtonSearchSelectWord(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI): Zdarzenie wybrania przycisku wyszukiwania zaznaczonego słowa [31-08-2025]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TButton *pButt = dynamic_cast<TButton *>(Sender);
	if(!pButt) return;
	//---
	int iPos=0;
	this->pPanelSelectWordResult->Visible = true;

	this->pHSlistResultSearchSelectWord->BeginUpdate();
	this->pHSlistResultSearchSelectWord->Clear();

	//GsReadBibleTextItem *pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(this->iGetDefaultTranslate);
//  #if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("pGsTabSetClass->TabIndex: %d", ARRAYOFCONST((this->pGsTabSetClass->TabIndex))));
//	#endif
  // Wyszukiwanie tylko dotyczą tłumaczenia w bierzącej zakładce // [02-09-2025]
	GsReadBibleTextItem *pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(this->pGsTabSetClass->TabIndex - 1);
	if(pGsReadBibleTextItem)
	{
		THashedStringList *pHSList = GsReadBibleTextData::GetSelectBoksInTranslate(pGsReadBibleTextItem, this->_ShucIndexBook);
		if(pHSList)
		{
			for(int i=0; i<pHSList->Count; ++i)
			{
				iPos = System::Sysutils::AnsiLowerCase(pHSList->Strings[i]).Pos(System::Sysutils::AnsiLowerCase(this->pLabeledEdit->Text));
				if(iPos > 0) this->pHSlistResultSearchSelectWord->AddObject(pHSList->Strings[i], pHSList->Objects[i]);
			}
		}
	}
	this->pCListResultSearchSelectWord->ItemCount = this->pHSlistResultSearchSelectWord->Count;
	this->pHSlistResultSearchSelectWord->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_OnDocumentComplete(System::TObject* ASender, const _di_IDispatch pDisp, const System::OleVariant &URL)
/**
	OPIS METOD(FUNKCJI): [31-07-2023]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TWebBrowser *pBrowser = dynamic_cast<TWebBrowser *>(ASender);
	if(!pBrowser) return;
	//---
	TTreeNode *pTreeNodeSelect = GsReadBibleTextData::pGsTreeBibleClass->Selected; //[03-08-2023]
	UnicodeString ustrInfoPanel = Format("Strona wczytana z tekstem [%s]", ARRAYOFCONST(( pTreeNodeSelect->Text ))); //[04-08-2023]

	TForm *pMainForm = Application->MainForm;

	for(int i=0; i<pMainForm->ComponentCount; ++i)
	{
		TComponent *pComponent = pMainForm->Components[i];
		if(pComponent->ClassNameIs("TStatusBar"))
		{
			TStatusBar *pStatusBar = dynamic_cast<TStatusBar *>(pComponent);
			if(pStatusBar)
			{
				if(pStatusBar->SimplePanel)
					{pStatusBar->SimpleText = ustrInfoPanel;}
				else
				{
					if(pStatusBar->Panels->Count > 0)
						{pStatusBar->Panels->Items[0]->Text = ustrInfoPanel;}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_OnBeforeNavigate2(System::TObject *ASender, const _di_IDispatch pDisp, const OleVariant &URL, const OleVariant &Flags,
		const OleVariant &TargetFrameName, const OleVariant &PostData, const OleVariant &Headers, WordBool &Cancel)
/**
	OPIS METOD(FUNKCJI): [29-08-2025]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TWebBrowser *pBrowser = dynamic_cast<TWebBrowser *>(ASender);
	if(!pBrowser) return;
	//---
	if(this->pGsTabSetClass->TabIndex == 0)
	{
		this->pLabeledEdit->Text = "";
    Cancel = VARIANT_TRUE; // zatrzymuje nawigację, nie pokazuje błędu
		return;
  }

  UnicodeString adres = URL;
	if (adres.Pos("app://") == 1)
	{
		UnicodeString ustrWordSelect = adres.SubString(7, adres.Length() - 7);
		this->pLabeledEdit->Text = ustrWordSelect;
		Cancel = VARIANT_TRUE; // zatrzymuje nawigację, nie pokazuje błędu
	}
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_GetHTMLText(UnicodeString &_ustrTextHTML)
/**
	OPIS METOD(FUNKCJI): Metoda wypełnią kodem html, zmienną UnicodeString, z aktualnej zakładki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	_ustrTextHTML = this->ustrHtmlText;
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_GetText(UnicodeString &_ustrText)
/**
	OPIS METOD(FUNKCJI): Metoda wypełnią tekstem, zmienną UnicodeString, z aktualnej zakładki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	_ustrText = this->pHSListActualText->Text;
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_GetListText(THashedStringList *_pHSListChapt)
/**
	OPIS METOD(FUNKCJI): Metoda wypełnia lstę listą z aktualnej zakładki [25-08-2023]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	_pHSListChapt->Assign(this->pHSListActualText);
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::_DisplayInfosTranslates(const int iTab)
/**
	OPIS METOD(FUNKCJI): Metoda wyświetla informacje o przekładach i wybranym rozdziale
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TStringStream *pStringStream = new TStringStream("", TEncoding::UTF8, true);
	if(!pStringStream) throw(Exception("Błąd inicjalizacji objektu TStringStream"));
	GsTabSheetClass *pGsTabSheetClass = dynamic_cast<GsTabSheetClass *>(GsReadBibleTextData::_GsPageControl->ActivePage);
	if(!pGsTabSheetClass) return;

	try
	{
		pStringStream->WriteString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">");
		pStringStream->WriteString(UnicodeString("<html><head>") +
																		"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">" +
																		"<title>Informacja o tłumaczeniach</title>" +
																		"<style type=\"text/css\">" +
																		".styleColorValue {color: #4B0082; font-size:12pt;font-family:Arial; font-weight:bold; background-position:center;}" +
																		".styleText {color: #000000; font-size:12pt;font-family:Times;}" +
																		".styleInfoTranslate {color: #FF0000; font-size:12pt;font-family:Arial; font-weight:bold; background-position:center;}" +
																		"body {background-color:#CCCCEE; font-size:12pt;font-family:Arial;}" +
																		"</style></head><body>");

		if(iTab==-1)
		//Informacje o wszystkich tłumaczeniach
		{
			pStringStream->WriteString("<span class=\"styleColorValue\">Nazwa tłumaczenia: </span><span class=\"styleText\">Wszystkie, dostępne tłumaczenia</span>");
		}
		else
		//Wybrane tłumaczenie
		{
			GsReadBibleTextItem *pGsReadBibleTextItem = GsReadBibleTextData::pGsReadBibleTextClass->GetTranslateClass(iTab); //Wyłuskanie wskaźnika GsReadBibleTextItem konkretnego tłumaczenia, w celu sprawdzenia typu tłumaczenia
			pStringStream->WriteString(Format("<span class=\"styleColorValue\">Nazwa tłumaczenia: </span><span class=\"styleText\">%s</span>", ARRAYOFCONST((pGsReadBibleTextItem->NameTranslate))));
			pStringStream->WriteString("<br>");
			pStringStream->WriteString(Format("<span class=\"styleColorValue\">Ilość wszystkich wersetów w tłumaczeniu: </span><span class=\"styleText\">%d wersetów</span>", ARRAYOFCONST((pGsReadBibleTextItem->uiAllVersCount))));
			pStringStream->WriteString("<br>");
			pStringStream->WriteString(Format("<span class=\"styleColorValue\">Wybrana księga: </span><span class=\"styleText\">%s</span>", ARRAYOFCONST((AppCTable_InfoAllBooks[this->_ShucIndexBook].FullNameBook))));
			pStringStream->WriteString("<br>");
			pStringStream->WriteString(Format("<span class=\"styleColorValue\">Wybrany rozdział: </span><span class=\"styleText\">%d</span>", ARRAYOFCONST((this->_ShucIndexChapt+1))));
			//Informacje o wybranym tłumaczeniu
			pStringStream->WriteString("<br><br>");
			pStringStream->WriteString("<span class=\"styleInfoTranslate\">Informacje o tłumaczeniu:</span>");
			pStringStream->WriteString("<hr>");

			if(TFile::Exists(pGsReadBibleTextItem->PathInfoTranslate))
			{
				pStringStream->WriteString("<span class=\"styleText\">");
				pStringStream->WriteString(TFile::ReadAllText(pGsReadBibleTextItem->PathInfoTranslate, TEncoding::UTF8));
				pStringStream->WriteString("</span>");
			}
		}

		pStringStream->WriteString("</body></html>");
		pStringStream->Position = 0;

		//Wczytanie do objektu, klasy TWebBrowser (this->pWebBrowserinfoTranslations) zawartości objeltu, klasy TStringStream (pStringStream)
		IPersistStreamInit *psi;

		_di_IStream sa(*(new TStreamAdapter(pStringStream, soReference)));
		if(SUCCEEDED(this->pWebBrowserInfoTranslations->Document->QueryInterface(IID_IPersistStreamInit, (void **)&psi)))
			{psi->Load(sa);}
	}
	__finally
	{
		if(pStringStream) {delete pStringStream; pStringStream = nullptr;}
	}
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::CreateWnd()
/**
	OPIS METOD(FUNKCJI): Tworzenie kontrolki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TTabSheet::CreateWnd();
	//Własny kod.
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::DestroyWnd()
/**
	OPIS METOD(FUNKCJI): Niszczenie kontrolki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	TTabSheet::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetClass::DoHide()
/**
	OPIS METOD(FUNKCJI): Ukrycie kontrolki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->pPanelSelectWordResult->Visible = false;
}
//---------------------------------------------------------------------------
TTabSet* __fastcall GsTabSheetClass::GetTabSet()
/**
	OPIS METOD(FUNKCJI): Wyłuskanie wskażnika na zakładki tłumaczeń
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	return this->pGsTabSetClass;
}
/****************************************************************************
 *														KLASA GsTabSetClass														*
 ****************************************************************************/
__fastcall GsTabSetClass::GsTabSetClass(TComponent* Owner) : TTabSet(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass)
		throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	//---
	//this->DoubleBuffered = true;
	this->OnChange = this->_OnChange;
	this->bIsCreate = true; //Objekt został stworzony
	this->Font->Quality = TFontQuality::fqClearType;
  this->ParentFont = true;
}
//---------------------------------------------------------------------------
__fastcall GsTabSetClass::~GsTabSetClass()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
void __fastcall GsTabSetClass::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TTabSet::CreateWnd();
	//Własny kod.
}
//---------------------------------------------------------------------------
void __fastcall GsTabSetClass::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	TTabSet::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsTabSetClass::_OnChange(System::TObject* Sender, int NewTab, bool &AllowChange)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("GsTabSetClass::_OnChange -> %d", ARRAYOFCONST((NewTab))));
//	#endif
	if(!this->bIsCreate)
	{
		GsTabSheetClass *pGsTabSheetClass = dynamic_cast<GsTabSheetClass *>(GsReadBibleTextData::_GsPageControl->ActivePage);
		if(!pGsTabSheetClass) return;
		//Ponowne wczytanie wszystkich tłumaczeń, dla wybranej księgi i rozdziału, by przy przełączaniu zakładek wyboru tłumacznia
		//nie wyświetlano tekstu z sąsiedniej zakładki ksiegi i rozdziału!
		GsReadBibleTextData::pGsReadBibleTextClass->GetAllTranslatesChapter(pGsTabSheetClass->_ShucIndexBook, pGsTabSheetClass->_ShucIndexChapt); //Niekoniecznie potrzebne
		//Od NewTab odejmowane jast 1, gdyż pierwsza pozycja zakładek to nie konkretne tłumaczenie, lecz wszystkie tłumaczenia
		GsReadBibleTextData::pGsReadBibleTextClass->DisplayAllTextInHTML(pGsTabSheetClass->pWebBrowser, NewTab-1);

		pGsTabSheetClass->_DisplayInfosTranslates(NewTab-1);

//    #if defined(_DEBUGINFO_)
//			GsDebugClass::WriteDebug(Format("NewTab: %d, TabIndex: %d", ARRAYOFCONST((NewTab, this->TabIndex))));
//		#endif
		// Wykasowanie zawartości pola edycji wybranego słowa, po wykasowaniu zezaktywuje sie równierz przycisk wyszukiwania.
		// // 02-09-2025
		//if(NewTab == 0)
		pGsTabSheetClass->pLabeledEdit->Clear();
	}
	else
	{
		this->bIsCreate = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall GsTabSetClass::DrawTab(Vcl::Graphics::TCanvas *TabCanvas, const Winapi::Windows::TRect &R,
	int Index, bool Selected)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
  Kod tymczasowo martwy // 10-10-2024
*/
{
	TRect MyRect = R;

	DrawText(TabCanvas->Handle, this->Tabs->Strings[Index].c_str(), -1, &MyRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("%s", ARRAYOFCONST((this->Tabs->Strings[Index]))));
//	#endif
}
//---------------------------------------------------------------------------
int __fastcall GsTabSetClass::GetImageIndex(int TabIndex)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  return enImageIndex_Book;
}
/****************************************************************************
 *													KLASA GsBarSelectVers														*
 ****************************************************************************/
//Tagi dla objektów, klasy TPopupMenu i TToolButton
enum {enPopupMenu_Books=10, enPopupMenu_Chapters, enPopupMenu_Vers, enPopupMenu_Translates,
			enButton_Books=100, enButton_Chapter, enButton_Vers, enButton_Translates, enButton_NextVers, enButton_PrevVers,
			enButton_CopyToSheet, enButton_Save, enButtonFav, //[24-10-2023]
			enButton_Delete
			};
const UnicodeString NAMEPANELSELECTVERS = "GsPanelSelectVers";
__fastcall GsBarSelectVers::GsBarSelectVers(TComponent* Owner, const unsigned char _cucBook, const unsigned char _cucChapt,
																						const unsigned char _cucVers, bool bSelectComment)
	: TToolBar(Owner), _FucSelectBook(_cucBook), _FucSelectChapt(_cucChapt), _FucSelectVers(_cucVers)
/**
	OPIS METOD(FUNKCJI): Konstruktor
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TList *pListTempAllTranslates=nullptr; //Tymczasowa lista
	GsReadBibleTextItem *pGsReadBibleTextItem=nullptr;
	this->Font->Quality = TFontQuality::fqClearType;
	this->ParentFont = true;

	if(!GsReadBibleTextData::pGsReadBibleTextClass) throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));

	this->_pBSListAllFullTranslates = new TList(); //Lista wszystkich tłumaczeń
	if(!this->_pBSListAllFullTranslates) throw(Exception("Nie dokonano inicjalizacji objektu TList"));

	//Lista wszystkich pełnych tłumaczeń
	pListTempAllTranslates = GsReadBibleTextData::GetGlobalListAllTraslates(); // Lista wszystkich tłumaczeń
	for(int i=0; i<pListTempAllTranslates->Count; ++i)
	{
		pGsReadBibleTextItem = static_cast<GsReadBibleTextItem *>(pListTempAllTranslates->Items[i]);
		if((pGsReadBibleTextItem)  && (pGsReadBibleTextItem->enTypeTranslate == enTypeTr_Full))
		{
			this->_pBSListAllFullTranslates->Add(pGsReadBibleTextItem);
		}
	}

	this->EdgeBorders = TEdgeBorders() << ebBottom << ebTop << ebLeft << ebRight;
	this->ShowCaptions = true;
	this->AutoSize = true;
	this->Wrapable = true;
	this->List = true;
}
//---------------------------------------------------------------------------
__fastcall GsBarSelectVers::~GsBarSelectVers()
/**
	OPIS METOD(FUNKCJI): Destruktor
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->_pBSListAllFullTranslates) {delete this->_pBSListAllFullTranslates; this->_pBSListAllFullTranslates = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall GsBarSelectVers::CreateWnd()
/**
	OPIS METOD(FUNKCJI): Tworzenie kontrolki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TToolBar::CreateWnd();
	//Własny kod.
  // Sprawdzanie typu przodka objektu, by wyswietlić, lub nie wybrane przyciski //[01-11-2024]
	GsPanelSelectVers *pGsPanelSelectVers = static_cast<GsPanelSelectVers *>(this->Parent);
	bool IsVisibleButton = ((pGsPanelSelectVers != nullptr) && (pGsPanelSelectVers->ClassNameIs("GsPanelSelectVers")));
//  #if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("IsVisibleButton: %d", ARRAYOFCONST(( (int)IsVisibleButton ))));
//	#endif

	this->DrawingStyle = Vcl::Comctrls::dsGradient;
	this->Images = GsReadBibleTextData::_GsImgListData;
	this->DisabledImages = GsReadBibleTextData::_GsImgListDataDisable;
	//---
	this->_pSelectFavCBox = new TToolButton(this);//Czy werset należy do ulubionych
	if(!this->_pSelectFavCBox) throw(Exception("Błąd funkcji TToolButton"));
	this->_pSelectFavCBox->Parent = this;
	this->_pSelectFavCBox->AutoSize = true;
	this->_pSelectFavCBox->Visible = true;
	this->_pSelectFavCBox->ImageIndex = enImageIndex_SelectFavVerset;
	this->_pSelectFavCBox->Caption = "Ulubiony werset";
	this->_pSelectFavCBox->OnClick = this->_OnClickFavVers; //[24-10-2023]
	this->_pSelectFavCBox->CustomHint = GsReadBibleTextData::_GsBalloonHint;
	this->_pSelectFavCBox->ShowHint = true;
	this->_pSelectFavCBox->Style = tbsCheck;
	this->_pSelectFavCBox->Hint = Format("Ustawia wyświetlony werset jako ulubiony|Zaznaczenie aktualnie wybranego wersetu, jako ulubionego|%u", ARRAYOFCONST((this->_pSelectFavCBox->ImageIndex)));
	this->_pSelectFavCBox->Visible = IsVisibleButton;
	//this->_pSelectFavCBox->ParentFont = true;
	//Przeniesienie tekstu na zakładkę
	this->_pButCopyToSheet = new TToolButton(this);
	if(!this->_pButCopyToSheet) throw(Exception("Błąd funkcji TToolButton"));
	this->_pButCopyToSheet->Parent = this;
	this->_pButCopyToSheet->AutoSize = true;
	this->_pButCopyToSheet->ImageIndex = enImageIndex_CopyToSheet;
	this->_pButCopyToSheet->Caption = "Skopiuj tekst";
	this->_pButCopyToSheet->OnClick = this->_OnClickCopyToSheet;
	this->_pButCopyToSheet->Visible = true;
	this->_pButCopyToSheet->CustomHint = GsReadBibleTextData::_GsBalloonHint;
	this->_pButCopyToSheet->ShowHint = true;
	this->_pButCopyToSheet->Hint = Format("Kopiuje werset na zakładkę|Kopiuje wybrany werset, na zakładkę, w głównym oknie|%u", ARRAYOFCONST((this->_pButCopyToSheet->ImageIndex)));
	this->_pButCopyToSheet->Visible = IsVisibleButton;
	//this->_pButCopyToSheet->ParentFont = true;
	//Kasowanie komentarza do aktualnego wersetu
	this->_pDeleteNoteVers	= new TToolButton(this);
	if(!this->_pDeleteNoteVers) throw(Exception("Błąd funkcji TToolButton"));
	this->_pDeleteNoteVers->Parent = this;
	this->_pDeleteNoteVers->AutoSize = true;
	this->_pDeleteNoteVers->ImageIndex = enImageIndex_Delete;
	this->_pDeleteNoteVers->Caption = "Skasuj komentarz";
	this->_pDeleteNoteVers->OnClick = this->_OnClickDeleteComment;
	this->_pDeleteNoteVers->Visible = true;
	this->_pDeleteNoteVers->CustomHint = GsReadBibleTextData::_GsBalloonHint;
	this->_pDeleteNoteVers->ShowHint = true;
	this->_pDeleteNoteVers->Hint = Format("Skasuj komentarz|Kasuje komentarz do aktualnie wyświetlanego wersetu.|%u", ARRAYOFCONST((this->_pDeleteNoteVers->ImageIndex)));
	this->_pDeleteNoteVers->Visible = IsVisibleButton;
	//this->_pDeleteNoteVers->ParentFont = true;
	//Zapis komentarza do aktualnego wersetu
	this->_pSaveNoteToVers = new TToolButton(this);
	if(!this->_pSaveNoteToVers) throw(Exception("Błąd funkcji TToolButton"));
	this->_pSaveNoteToVers->Parent = this;
	this->_pSaveNoteToVers->AutoSize = true;
	this->_pSaveNoteToVers->ImageIndex = enImageIndex_Save;
	this->_pSaveNoteToVers->Caption = "Zapisz komentarz";
	this->_pSaveNoteToVers->OnClick = this->_OnClickSaveComment;
	this->_pSaveNoteToVers->Visible = true;
	this->_pSaveNoteToVers->CustomHint = GsReadBibleTextData::_GsBalloonHint;
	this->_pSaveNoteToVers->ShowHint = true;
	this->_pSaveNoteToVers->Hint = Format("Zapisz komentarz|Zapisuje komentarz do aktualnie wyświetlanego wersetu.|%u", ARRAYOFCONST((this->_pSaveNoteToVers->ImageIndex)));
	this->_pSaveNoteToVers->Visible = IsVisibleButton;
	//this->_pSaveNoteToVers->ParentFont = true;
	//Poprzedni werset
	this->_pButPrevVers = new TToolButton(this);
	if(!this->_pButPrevVers) throw(Exception("Błąd funkcji TToolButton"));
	this->_pButPrevVers->Parent = this;
	this->_pButPrevVers->AutoSize = true;
	this->_pButPrevVers->ImageIndex = enImageIndex_PrevChapter;
	this->_pButPrevVers->Caption = "Poprzedni werset";
	this->_pButPrevVers->OnClick = this->_OnClickNavigateVers;
	this->_pButPrevVers->Enabled = false;
	this->_pButPrevVers->CustomHint = GsReadBibleTextData::_GsBalloonHint;
	this->_pButPrevVers->ShowHint = true;
	this->_pButPrevVers->Hint = Format("Przewija do poprzedniego wersetu|Przewija do poprzedniego wersetu|%u", ARRAYOFCONST((this->_pButPrevVers->ImageIndex)));
	this->_pButPrevVers->Visible = true;//!this->_FbBarSelectComment; //W przypadku gdy werset został wybrany w liście komentarzy w głównym oknie,																													 //nie jest możliwy wybór pojedyńczego tłumaczenia, lecz wyświetlane są wszystkie dostępne tłumaczenia.
	//this->_pButPrevVers->ParentFont = true;
	//Następny werset
	this->_pButNextVers = new TToolButton(this);
	if(!this->_pButNextVers) throw(Exception("Błąd funkcji TToolButton"));
	this->_pButNextVers->Parent = this;
	this->_pButNextVers->AutoSize = true;
	this->_pButNextVers->ImageIndex = enImageIndex_NextChapter;
	this->_pButNextVers->Caption = "Następny werset";
	this->_pButNextVers->OnClick = this->_OnClickNavigateVers;
	this->_pButNextVers->CustomHint = GsReadBibleTextData::_GsBalloonHint;
	this->_pButNextVers->ShowHint = true;
	this->_pButNextVers->Hint = Format("Przewija do następnego wersetu|Przewija do nstępnego wersetu|%u", ARRAYOFCONST((this->_pButNextVers->ImageIndex)));
	this->_pButNextVers->Visible = true;//W przypadku gdy werset został wybrany w liście komentarzy w głównym oknie,
																			//nie jest możliwy wybór pojedyńczego tłumaczenia, lecz wyświetlane są wszystkie dostępne tłumaczenia.
	//this->_pButNextVers->ParentFont = true;
	//Wybrany werset //[15-12-2024]
	this->_pLabelSelect = new TLabel(this);
	if(!this->_pLabelSelect) throw(Exception("Błąd funkcji TLabel"));
	this->_pLabelSelect->Parent = this;
	this->_pLabelSelect->ParentFont = true;
	this->_pLabelSelect->ShowHint = true;
	this->_pLabelSelect->CustomHint = GsReadBibleTextData::_GsBalloonHint;
	this->_pLabelSelect->StyleElements = TStyleElements() << seClient << seBorder;
	this->_pLabelSelect->Transparent = true;
	this->_pLabelSelect->Alignment = taCenter;
  this->_pLabelSelect->Font->Size = 14;
	this->_pLabelSelect->Font->Quality = TFontQuality::fqClearType;
	this->_pLabelSelect->Font->Style = TFontStyles() << fsBold;
	this->_pLabelSelect->Font->Color = clRed;
	this->_pLabelSelect->Layout = tlCenter;
	this->_pLabelSelect->Caption = Format("%s %u:%u", ARRAYOFCONST((AppCTable_InfoAllBooks[this->_FucSelectBook].ShortNameBook, this->_FucSelectChapt+1, this->_FucSelectVers)));
	this->_pLabelSelect->Hint = Format("Adres wersetu|Pokazuje adres wersetu, czyli księge, rozdział i werset|%u",
		ARRAYOFCONST((enImageIndex_InfoHelp)));
	//Wybór wersetu
	this->_pButVers = new TToolButton(this);
	if(!this->_pButVers) throw(Exception("Błąd funkcji TToolButton"));
	this->_pButVers->Parent = this;
	this->_pButVers->ImageIndex = enImageIndex_SelectVers;
	this->_pButVers->Style = tbsDropDown;
	this->_pButVers->AutoSize = true;
	this->_pButVers->OnClick = this->_OnClickButtonSelect;
	this->_pButVers->CustomHint = GsReadBibleTextData::_GsBalloonHint;
	this->_pButVers->ShowHint = true;
	this->_pButVers->Hint = Format("Wybór wersetu|Pozwala na wybór wersetu z wybranejgo rozdziału i księgi|%u", ARRAYOFCONST((this->_pButVers->ImageIndex)));
	this->_pButVers->Visible = true;//!this->_FbBarSelectComment; //W przypadku gdy werset został wybrany w liście komentarzy w głównym oknie,
																												 //nie jest możliwy wybór pojedyńczego tłumaczenia, lecz wyświetlane są wszystkie dostępne tłumaczenia.
	//this->_pButVers->ParentFont = true;
	//Wybór rozdziału
	this->_pButChapt = new TToolButton(this);
	if(!this->_pButChapt) throw(Exception("Błąd funkcji TToolButton"));
	this->_pButChapt->Parent = this;
	this->_pButChapt->ImageIndex = enImageIndex_SelectChapter;
	this->_pButChapt->Style = tbsDropDown;
	this->_pButChapt->AutoSize = true;
	this->_pButChapt->OnClick = this->_OnClickButtonSelect;
	this->_pButChapt->CustomHint = GsReadBibleTextData::_GsBalloonHint;
	this->_pButChapt->ShowHint = true;
	this->_pButChapt->Hint = Format("Wybór rozdziału|Pozwala na wybór rozdziału z wybranej księgi|%u", ARRAYOFCONST((this->_pButChapt->ImageIndex)));
	this->_pButChapt->Visible = true;//!this->_FbBarSelectComment; //W przypadku gdy werset został wybrany w liście komentarzy w głównym oknie,
																													//nie jest możliwy wybór pojedyńczego tłumaczenia, lecz wyświetlane są wszystkie dostępne tłumaczenia.
	//this->_pButChapt->ParentFont = true;
	//Wybór księgi
	this->_pButBooks = new TToolButton(this);
	if(!this->_pButBooks) throw(Exception("Błąd funkcji TToolButton"));
	this->_pButBooks->Parent = this;
	this->_pButBooks->ImageIndex = enImageIndex_Book;
	this->_pButBooks->Style = tbsDropDown;
	this->_pButBooks->AutoSize = true;
	this->_pButBooks->OnClick = this->_OnClickButtonSelect;
	this->_pButBooks->CustomHint = GsReadBibleTextData::_GsBalloonHint;
	this->_pButBooks->ShowHint = true;
	this->_pButBooks->Hint = Format("Wybór księgi|Pozwala na wybór księgi z wybranego tłumaczenia|%u", ARRAYOFCONST((this->_pButBooks->ImageIndex)));
	this->_pButBooks->Visible = true;//!this->_FbBarSelectComment; //W przypadku gdy werset został wybrany w liście komentarzy w głównym oknie,
																													//nie jest możliwy wybór pojedyńczego tłumaczenia, lecz wyświetlane są wszystkie dostępne tłumaczenia.
	//this->_pButBooks->ParentFont = true;
	//
	this->_pSelectFavCBox->Tag = enButtonFav; //[24-10-2023]
	//this->_pButTranslates->Tag = enButton_Translates;
	this->_pButVers->Tag = enButton_Vers;
	this->_pButChapt->Tag = enButton_Chapter;
	this->_pButBooks->Tag = enButton_Books;
	this->_pButNextVers->Tag = enButton_NextVers;
	this->_pButPrevVers->Tag = enButton_PrevVers;
	this->_pButCopyToSheet->Tag = enButton_CopyToSheet;
	this->_pSaveNoteToVers->Tag = enButton_Save;
	this->_pDeleteNoteVers->Tag = enButton_Delete;

	//Tworzenie stałych popup menu (wszystkich tłumaczeń, księgi biblijne, rozdziałów i wersetów)
	this->_CreatePMenuBooks();
	if(this->Parent->ClassNameIs(NAMEPANELSELECTVERS)) this->_DisplayVers(); //Zabezpieczenie
}
//---------------------------------------------------------------------------
void __fastcall GsBarSelectVers::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	TToolBar::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsBarSelectVers::_CreatePMenuBooks()
/**
	OPIS METOD(FUNKCJI): Tworzenie stałych popup menu (wszystkich tłumaczeń, księgi biblijne, rozdziałów i wersetów)
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsReadBibleTextItem *pGsReadBibleTextItem=nullptr;

	this->_pPMenuBooks = new TPopupMenu(this);					//Popup menu z listą ksiąg biblijnych
	if(!this->_pPMenuBooks) throw(Exception("Błąd funkcji TPopupMenu"));
	this->_pPMenuChapt = new TPopupMenu(this);		 //Popup menu z listą rozdziałów
	if(!this->_pPMenuChapt) throw(Exception("Błąd funkcji TPopupMenu"));
	this->_pPMenuVers = new TPopupMenu(this);			 //Popup menu z listą wersetów
	if(!this->_pPMenuVers) throw(Exception("Błąd funkcji TPopupMenu"));
	//---
	this->_pPMenuBooks->Tag = enPopupMenu_Books;
	this->_pPMenuChapt->Tag = enPopupMenu_Chapters;
	this->_pPMenuVers->Tag = enPopupMenu_Vers;
	//---Uwaga: Obrazki w menu powodują że nie są widoczne napisy w popupmenu, podczas włączonych stylów!!!
	this->_pPMenuBooks->Images = GsReadBibleTextData::_GsImgListData;
	this->_pPMenuChapt->Images = GsReadBibleTextData::_GsImgListData;
	this->_pPMenuVers->Images =	 GsReadBibleTextData::_GsImgListData;
	// Wyszukanie najbliższego tłumaczenia apokryficznego
	UnicodeString ustrNameTranslates;
	bool bIsSelectApocryfic=false;
	for(unsigned char i=0; i<this->_pBSListAllFullTranslates->Count; ++i)
	{

    pGsReadBibleTextItem = static_cast<GsReadBibleTextItem *>(this->_pBSListAllFullTranslates->Items[i]);
		if(pGsReadBibleTextItem && !bIsSelectApocryfic && pGsReadBibleTextItem->IsApocryfic)
		{
			bIsSelectApocryfic = true;
			this->_FucSelectTranslate = i;
		}
	}
	//--- Stworzenie popup menu listy ksiąg biblijnych
	for(unsigned char i=0; i<GlobalVar::Global_NumberBooks; ++i)
	{
		TMenuItem *NewItem = new TMenuItem(this->_pPMenuBooks);
		if(!NewItem) throw(Exception("Błąd funkcji TMenuItem"));

		this->_pPMenuBooks->Items->Add(NewItem);
		NewItem->Caption = AppCTable_InfoAllBooks[i].FullNameBook;
		if(i==(unsigned char)this->_FucSelectBook) this->_pButBooks->Caption = NewItem->Caption; //Wybrana księga domyślnie
		NewItem->OnClick = this->_OnClick_PMenu;
		NewItem->Tag = i;
		NewItem->ImageIndex = enImageIndex_Book;
		if(i==33 || i==66) NewItem->Break = mbBarBreak; //08-07-2021
	}
	//---- Stworzenie listy rozdziałów dla księgi.
	for(unsigned char i=0; i<AppCTable_InfoAllBooks[this->_FucSelectBook].ucCountChapt; ++i)
	{
		TMenuItem *NewItem = new TMenuItem(this->_pPMenuChapt);
		if(!NewItem) throw(Exception("Błąd funkcji TMenuItem"));
		this->_pPMenuChapt->Items->Add(NewItem);
		NewItem->Caption = Format("Rozdział: %u", ARRAYOFCONST((i + 1)));
		if(i==this->_FucSelectChapt) this->_pButChapt->Caption = NewItem->Caption;
		NewItem->OnClick = this->_OnClick_PMenu;
		NewItem->Tag = i;
		NewItem->ImageIndex = enImageIndex_SelectChapter;
		if(i==33 || i==66 || i==99 || i==132 || i==165) NewItem->Break = mbBarBreak;
	}
	//--- Stworzenie listy wersetów dla pierwszego tłumaczenia, księgi i rozdziału.
	unsigned int uiVers = GsReadBibleTextData::GetCountVer(0, this->_FucSelectBook, this->_FucSelectChapt);
	for(unsigned int i=0; i<uiVers; ++i)
	{
		TMenuItem *NewItem = new TMenuItem(this->_pPMenuVers);
		if(!NewItem) throw(Exception("Błąd funkcji TMenuItem"));
		this->_pPMenuVers->Items->Add(NewItem);
		NewItem->Caption = Format("Werset %u", ARRAYOFCONST((i + 1)));
		NewItem->Tag = i;
		NewItem->OnClick = this->_OnClick_PMenu;
		NewItem->ImageIndex = enImageIndex_SelectVers;
	}
	//---
	this->_pButBooks->DropdownMenu = this->_pPMenuBooks;
	this->_pButChapt->DropdownMenu = this->_pPMenuChapt;
	this->_pButVers->DropdownMenu = this->_pPMenuVers;
	//---
	this->_pButVers->Caption = Format("Werset %u", ARRAYOFCONST((this->_FucSelectVers)));
}
//---------------------------------------------------------------------------
void __fastcall GsBarSelectVers::_VerifyVarset()
/**
	OPIS METOD(FUNKCJI): Sprawdzenie wyświetlanego wersetu, czy jest na liście ulubionych i czy posiada komentarz. Jeśli jest
											 przycisk _pSelectFavCBox jest wciśniety //[24-10-2023]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
void __fastcall GsBarSelectVers::_OnClickFavVers(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI): Aktualny werset staje się ulubionym, lub nie [24-10-2023][29-10-2023]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  TToolButton *pToolButton = dynamic_cast<TToolButton *>(Sender);
	if(!pToolButton) return;
	//---
	UnicodeString ustrCreateName = Format("%.3u%.3u%.3u%", ARRAYOFCONST((this->_FucSelectBook + 1, this->_FucSelectChapt + 1, this->_FucSelectVers)));
//  #if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("ustrCreateName: \"%s\"", ARRAYOFCONST((ustrCreateName))));
//	#endif
	//Wyłuskanie wskaźnika na aktualną zakładke z tekstem
	GsTabSheetClass *pGsTabSheetClass = dynamic_cast<GsTabSheetClass *>(GsReadBibleTextData::_GsPageControl->ActivePage);
  if(pGsTabSheetClass) //Jeśli jest aktywna zakładka z wczytanym rozdziałem, trzeba uaktualnić liste ulubionych wersetów w birzącym, wczytanym rozdziele
	{
  	GsListBoxSelectedVersClass *pLBoxFav = pGsTabSheetClass->pLBoxSelectText;
  	if(pLBoxFav)
		{
  		pLBoxFav->ItemIndex = this->_FucSelectVers - 1;
  		pLBoxFav->Selected[this->_FucSelectVers - 1] = pToolButton->Down;
  		pLBoxFav->Click();
		}
	}
  else //Brak zakładki w głównym oknie z wczytanym rozdziałem //[29-10-2023]
	{
		int iIndex = GlobalVar::Global_HSListAllFavoritiesVers->IndexOf(ustrCreateName);
    //Jeśli aktualny werset jest na liście ulubionych to go skasuj
		if(iIndex > -1 && !pToolButton->Down) GlobalVar::Global_HSListAllFavoritiesVers->Delete(iIndex);
		//Jeśli nie jest, to go dodaj
		else if(iIndex == -1 && pToolButton->Down) GlobalVar::Global_HSListAllFavoritiesVers->Add(ustrCreateName);
  }
}
//---------------------------------------------------------------------------
void __fastcall GsBarSelectVers::_OnClickSaveComment(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI): Zapis komentarza do aktualnie wyświetlanego wersetu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  TToolButton *pToolButton = dynamic_cast<TToolButton *>(Sender);
	if(!pToolButton) return;
	//---
	UnicodeString ustrCreateName = Format("%.3u%.3u%.3u%", ARRAYOFCONST((this->_FucSelectBook + 1, this->_FucSelectChapt + 1, this->_FucSelectVers))),
								ustrCreateFullPathName;
	ustrCreateFullPathName = TPath::Combine(GlobalVar::Global_custrPathDirComments, ustrCreateName);
	ustrCreateFullPathName = TPath::ChangeExtension(ustrCreateFullPathName, GlobalVar::Global_custrExtendCommentsFiles);
	//--- Zapis komentarza
	GsPanelSelectVers *pGsPanelSelectVers = dynamic_cast<GsPanelSelectVers *>(this->Parent);
	if(pGsPanelSelectVers)
	{
		pGsPanelSelectVers->_pEditComment->SaveEditorToFile(ustrCreateFullPathName);
	}
}
//---------------------------------------------------------------------------
void __fastcall GsBarSelectVers::_OnClickDeleteComment(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI): Skasowania komentarza do aktualnie wyświetlanego wersetu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  TToolButton *pToolButton = dynamic_cast<TToolButton *>(Sender);
	if(!pToolButton) return;
	//---
	UnicodeString ustrCreateName = Format("%.3u%.3u%.3u%", ARRAYOFCONST((this->_FucSelectBook + 1, this->_FucSelectChapt + 1, this->_FucSelectVers)));
  //Sprawdzanie czy istnieje komentarz do wersetu //[27-10-2023]
	ustrCreateName = TPath::Combine(GlobalVar::Global_custrPathDirComments, ustrCreateName + GlobalVar::Global_custrExtendCommentsFiles);

	if(TFile::Exists(ustrCreateName))
	{
		UnicodeString ustrMessage = "Czy jesteś pewny, że chcesz skasować istniejący komentarz? Nie będzie można cofnąć operacji!";
		int iResult = MessageBox(NULL, ustrMessage.c_str(), TEXT("Pytanie aplikacji"), MB_YESNO | MB_ICONWARNING | MB_TASKMODAL | MB_DEFBUTTON2);
    if(iResult == IDYES)
		{
      TFile::Delete(ustrCreateName);
			//Wyczyszczenie edycji
				//Wyłuskanie wskaźnika na klasę GsEditorClass
			GsPanelSelectVers *pGsPanelSelectVers = dynamic_cast<GsPanelSelectVers *>(this->Parent);
			if(pGsPanelSelectVers)
			{
				GsEditorClass *pGsEditorClass = pGsPanelSelectVers->_pEditComment;
				pGsEditorClass->ClearEditor();
				pToolButton->Enabled = false;
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall GsBarSelectVers::_OnClickNavigateVers(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI): Przyciśnięto któryś z przycisków nawigacji po rozdziele
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TToolButton *pToolButton = dynamic_cast<TToolButton *>(Sender);
	if(!pToolButton) return;
	//---
	TMenuItem *pMenuItemSend=nullptr;
	TMenuItem *pMenuItem = this->_pPMenuVers->Items->Find(this->_pButVers->Caption); //Wyszukanie w menu aktualnego wersetu
	if(!pMenuItem) throw(Exception("Błąd wyboru wersetu z aktualnego rozdziału"));
	//---
	switch(pToolButton->Tag)
	{
		case enButton_NextVers:
		{
			this->_pButPrevVers->Enabled = true;
			if(pMenuItem->Tag >= this->_pPMenuVers->Items->Count - 1) return;
			pMenuItemSend = this->_pPMenuVers->Items->Items[pMenuItem->Tag+1];
			if(!pMenuItemSend) throw(Exception("Błąd wyboru wersetu z aktualnego rozdziału"));
			pToolButton->Enabled = (pMenuItemSend->Tag < this->_pPMenuVers->Items->Count-1);
		}
		break;
		//---
		case enButton_PrevVers:
		{
			this->_pButNextVers->Enabled = true;
			if(pMenuItem->Tag <= 0) return;
			pMenuItemSend = this->_pPMenuVers->Items->Items[pMenuItem->Tag-1];
			if(!pMenuItemSend) throw(Exception("Błąd wyboru wersetu z aktualnego rozdziału"));
			pToolButton->Enabled = (pMenuItem->Tag > 1);
		}
		break;
		//---
	}
	pMenuItemSend->Click(); //Uruchomienie metody GsBarSelectVers::_OnClick_PMenu()
}
//---------------------------------------------------------------------------
void __fastcall GsBarSelectVers::_OnClickDisplay(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI): Obsługa wyboru wyświetlenia wybranego wersetu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
void __fastcall GsBarSelectVers::GetSelectAdress(unsigned char &_usBook, unsigned char &_usChapt, unsigned char &_usVers, unsigned char &_ucTranslate)
/**
	OPIS METOD(FUNKCJI): Informacja o adresie wersetu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	_usBook = this->_FucSelectBook;
	_usChapt = this->_FucSelectChapt;
	_usVers = this->_FucSelectVers;
	_ucTranslate = this->_FucSelectTranslate;
}
//---------------------------------------------------------------------------
void __fastcall GsBarSelectVers::_DisplayVers()
/**
	OPIS METOD(FUNKCJI): Obsługa wyboru wyświetlenia wybranego wersetu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  GsPanelSelectVers *pGsPanelSelectVers = dynamic_cast<GsPanelSelectVers *>(this->Parent);
	if(!pGsPanelSelectVers) return;
	//---
	GsReadBibleTextItem *pGsReadBibleTextItem=nullptr;
	UnicodeString ustrText, ustrCreateName, ustrCreateFullPathName;

  TStringStream *pStringStream = new TStringStream("", TEncoding::UTF8, true);
	if(!pStringStream) throw(Exception("Błąd inicjalizacji objektu TStringStream"));

	pStringStream->WriteString(GsReadBibleTextData::GsHTMLHeaderDisplayVer);

	try
	{
		for(int iLicz=0; iLicz<this->_pBSListAllFullTranslates->Count; ++iLicz)
  	{
			pGsReadBibleTextItem = static_cast<GsReadBibleTextItem *>(this->_pBSListAllFullTranslates->Items[iLicz]);
  		if(pGsReadBibleTextItem)
			{
				GsReadBibleTextData::GetTextVersOfAdress(this->_FucSelectBook, this->_FucSelectChapt+1, this->_FucSelectVers, iLicz, ustrText);
				if(ustrText.Length() > 0)
  			{
					pStringStream->WriteString(Format("<span class=\"styleText\">%s</span>",
						ARRAYOFCONST((ustrText))));
          //Nazwa tłumaczenia
					pStringStream->WriteString(Format("<span class=\"styleTranslates\"> [%s]</span>",
						ARRAYOFCONST((pGsReadBibleTextItem->NameTranslate))));
          //Dwie puste linie
					if(iLicz<(this->_pBSListAllFullTranslates->Count-1)) pStringStream->WriteString("<br><br>");
  			}
  		}
		}

    pStringStream->WriteString("</body></html>");
		pStringStream->Position = 0;
		IPersistStreamInit *psi;
		_di_IStream sa(*(new TStreamAdapter(pStringStream, soReference)));
		if(SUCCEEDED(pGsPanelSelectVers->_pWebBrowser->Document->QueryInterface(IID_IPersistStreamInit, (void **)&psi)))
			{psi->Load(sa);}
		// Wyświetlenie w sposób interlinearny wersetu z Nowego Testamentu - Księgi liczone od "0"
		if(((this->_FucSelectBook) > ciMinSelectBookNewTestament) && ((this->_FucSelectBook) < ciMaxSelectBookNewTestament))
		{
			pGsPanelSelectVers->_pSGridInterlinearVers->Visible = true;
			pGsPanelSelectVers->_DisplayInterlinear(this->_FucSelectBook+1, this->_FucSelectChapt+1, this->_FucSelectVers);
		}
		else pGsPanelSelectVers->_pSGridInterlinearVers->Visible = false;
		//Odczyt komentarza
		ustrCreateName = Format("%.3u%.3u%.3u%s",
			ARRAYOFCONST((this->_FucSelectBook + 1, this->_FucSelectChapt + 1, this->_FucSelectVers, GlobalVar::Global_custrExtendCommentsFiles)));
		ustrCreateFullPathName = TPath::Combine(GlobalVar::Global_custrPathDirComments, ustrCreateName);

		if(pGsPanelSelectVers && pGsPanelSelectVers->_pEditComment->Visible)
		{
			pGsPanelSelectVers->_pEditComment->ClearEditor(); //[28-10-2023]
			pGsPanelSelectVers->_pEditComment->LoadEditorFromFile(ustrCreateFullPathName);
    }
	}
	__finally
	{
		if(pStringStream) {delete pStringStream; pStringStream = nullptr;}
  }
}
//---------------------------------------------------------------------------
void __fastcall GsBarSelectVers::_OnClickButtonSelect(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI): Kliknięto myszką na przyciski wyboru tekstu biblijnego
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	return;
	TToolButton *pToolButton = dynamic_cast<TToolButton *>(Sender);
	if(!pToolButton) return;
	//---
	POINT pMouse;
	GetCursorPos(&pMouse);
	pToolButton->DropdownMenu->Popup(pMouse.x, pMouse.y);
}
//---------------------------------------------------------------------------
void __fastcall GsBarSelectVers::_OnClickCopyToSheet(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI): Kliknięto myszką na przyciski przeniesienia(skopiowania) wybranego wersetu, na zakładkę w głównym oknie
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TToolButton *pToolButton = dynamic_cast<TToolButton *>(Sender);
	if(!pToolButton) return;
	//---
	GsReadBibleTextItem *pGsReadBibleTextItem=nullptr;
	UnicodeString ustrText;

  //Lista wszystkich pełnych tłumaczeń
	GsControlListVers *pGsControlListVers=nullptr;
	if(!GsReadBibleTextData::GsSheetListVers) //Zakładka z wybranymi wersetami nie istnieje
	{
		GsTabSheetSelectVersClass *pGsTabSheetSelectVersClass = new GsTabSheetSelectVersClass(GsReadBibleTextData::_GsPageControl);	 //Przyporządkowanie zakładki do klasy TPageControl
		if(!pGsTabSheetSelectVersClass) throw(Exception("Nie można zainicjować klasy GsTabSheetSelectVersClass"));
		//---
		pGsControlListVers = pGsTabSheetSelectVersClass->pGsControlListVers;
	}
	else //Zakładka z wybranymi wersetami już istnieje
	{
		pGsControlListVers = GsReadBibleTextData::GsSheetListVers->pGsControlListVers;
	}
	//---
	for(int i=0; i<this->_pBSListAllFullTranslates->Count; ++i)
	{
		pGsReadBibleTextItem = static_cast<GsReadBibleTextItem *>(this->_pBSListAllFullTranslates->Items[i]);
		if(pGsReadBibleTextItem)
		{
			GsReadBibleTextData::GetTextVersOfAdress(this->_FucSelectBook, this->_FucSelectChapt+1, this->_FucSelectVers, i, ustrText);

			if(ustrText.Length() > 0)
			{
				pGsControlListVers->pHSListVerses->AddObject(Format("%s %u:%u=%s",
					ARRAYOFCONST((AppCTable_InfoAllBooks[this->_FucSelectBook].ShortNameBook, this->_FucSelectChapt+1, this->_FucSelectVers, ustrText))), pGsReadBibleTextItem);
			}
		}
	}
	pGsControlListVers->pHSListVerses->AddObject("", 0);
	if(pGsControlListVers)
	{
		pGsControlListVers->ItemCount = pGsControlListVers->pHSListVerses->Count;
	}
}
//---------------------------------------------------------------------------
void __fastcall GsBarSelectVers::_OnClick_PMenu(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI): Obsługa wyboru pozycji z wszystkich popup menu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TMenuItem *pMItem = dynamic_cast<TMenuItem *>(Sender);
	if(!pMItem) return;
	//---
	TPopupMenu *pPMenu = dynamic_cast<TPopupMenu *>(pMItem->Owner);
	if(!pPMenu) return;
	//---
	switch(pPMenu->Tag)
	{
		case enPopupMenu_Books:					//Wybrano pozycje z listy ksiąg
		{
			GsReadBibleTextItem *pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(this->_FucSelectTranslate); //Metoda zwraca wskaźnik na klasę wybranego tłumaczenia
			if(!pGsReadBibleTextItem) throw(Exception("Błąd funkcji GsReadBibleTextData::GetTranslate()"));
			if( (pMItem->Tag > (signed char)(pGsReadBibleTextItem->ucStartBook + pGsReadBibleTextItem->ucCountBooks)) ||
					(pMItem->Tag < (signed char)pGsReadBibleTextItem->ucStartBook))
			//Zabezpieczenie przed wyborem księgi, której nie ma w wybranym tłumaczeniu
			{
				MessageBox(NULL, TEXT("Wybrane tłumaczenie, nie zawiera wybranej księgi, więc wybór będzie anulowany"), TEXT("Informacja aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
				return;
			}
			//---
			this->_pButBooks->Caption = pMItem->Caption;
			this->_FucSelectBook = pMItem->Tag;
			this->_FucSelectChapt = 0;
			this->_FucSelectVers = 1;
			//---
			this->_pPMenuChapt->Items->Clear(); //Wymazanie pozycji z listy rozdziałów
			for(unsigned char i=0; i<AppCTable_InfoAllBooks[pMItem->Tag].ucCountChapt; ++i)
			{
				TMenuItem *NewItem = new TMenuItem(this->_pPMenuChapt);
				if(!NewItem) throw(Exception("Błąd funkcji TMenuItem"));
				this->_pPMenuChapt->Items->Add(NewItem);
				NewItem->Caption = Format("Rozdział: %u", ARRAYOFCONST((i+1)));
				NewItem->Tag = i;
				NewItem->OnClick = this->_OnClick_PMenu;
				NewItem->ImageIndex = enImageIndex_SelectChapter; //13-06-2021
				if(i==33 || i==66 || i==99 || i==132 || i==165) NewItem->Break = mbBarBreak; //08-07-2021
			}
		}
		this->_OnClick_PMenu(this->_pPMenuChapt->Items->Items[0]);
		break;
		//---
		case enPopupMenu_Chapters:			//Wybrano pozycje z listy rozdziałów
		{
			this->_FucSelectChapt = pMItem->Tag;
			this->_FucSelectVers = 1;
			this->_pButChapt->Caption = this->_pPMenuChapt->Items->Items[this->_FucSelectChapt]->Caption;

			this->_pPMenuVers->Items->Clear(); //Wymazanie pozycji z listy rozdziałów
			unsigned int uiVers = GsReadBibleTextData::GetCountVer(this->_FucSelectTranslate, this->_FucSelectBook, this->_FucSelectChapt);
			if(uiVers == 0)
			{
        // Tekst apokryficzny
				this->_DisplayVers();
				break;
			}
			for(unsigned int i=0; i<uiVers; ++i)
			{
				TMenuItem *NewItem = new TMenuItem(this->_pPMenuVers);
				if(!NewItem) throw(Exception("Błąd funkcji TMenuItem"));
				this->_pPMenuVers->Items->Add(NewItem);
				NewItem->Caption = Format("Werset %u", ARRAYOFCONST((i + 1)));
				NewItem->Tag = i;
				NewItem->OnClick = this->_OnClick_PMenu;
				NewItem->ImageIndex = enImageIndex_SelectVers; //13-06-2021
				if(i==33 || i==66 || i==99 || i==132 || i==165) NewItem->Break = mbBarBreak; //08-07-2021
			}
		}
		this->_OnClick_PMenu(this->_pPMenuVers->Items->Items[0]);
		break;
		//---
		case enPopupMenu_Vers:
		{
			//Stan przewijania zależny od numeru wybranego wersetu
			this->_pButNextVers->Enabled = (pMItem->Tag < this->_pPMenuVers->Items->Count - 1);	 //Zabezpieczenie przed maksymalnym wersetem
			this->_pButPrevVers->Enabled = (pMItem->Tag > 0); //Zabezpieczenie przed minimalnym wersetem
			this->_FucSelectVers = pMItem->Tag + 1;
			this->_pButVers->Caption = pMItem->Caption;
			//08-07-2021. Umieszczenie w wyborze wersetu, wczesniej metoda była wywoływana 3 razy!!!
			if(this->Parent->ClassNameIs(NAMEPANELSELECTVERS)) this->_DisplayVers(); //Zabezpieczenie przed brakiem przodka
		}
		break;
	}
	//
	this->_pLabelSelect->Caption = Format("%s %u:%u", ARRAYOFCONST((AppCTable_InfoAllBooks[this->_FucSelectBook].ShortNameBook, this->_FucSelectChapt+1, this->_FucSelectVers)));
}
//---------------------------------------------------------------------------
void __fastcall GsBarSelectVers::Resize()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	
}
//---------------------------------------------------------------------------
/****************************************************************************
 *													KLASA GsPanelSelectVers													*
 ****************************************************************************/
enum{enRow_StrongNumber, enRow_GreckWord, enRow_PolWord, enRow_Count //Numery rzędów w objekcie TStringGrid w widoku interlinearnym
		};
__fastcall GsPanelSelectVers::GsPanelSelectVers(TComponent* Owner, const unsigned char _cucBook, const unsigned char _cucChapt,
																								const unsigned char _cucVers)
	: TCustomPanel(Owner), ucSetBook(_cucBook), ucSetChapt(_cucChapt), ucSetVers(_cucVers)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass)
		throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	this->Font->Quality = TFontQuality::fqClearType;
	this->ParentFont = true;
}
//---------------------------------------------------------------------------
__fastcall GsPanelSelectVers::~GsPanelSelectVers()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
void __fastcall GsPanelSelectVers::CreateWnd()
/**
	OPIS METOD(FUNKCJI): Tworzenie kontrolki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCustomPanel::CreateWnd();
	//Własny kod.
		//---Przyciski główne
	this->_pGsBarSelectVers = new GsBarSelectVers(this, this->ucSetBook, this->ucSetChapt, this->ucSetVers);
	if(!this->_pGsBarSelectVers)
		throw(Exception("Nie dokonano inicjalizacji objektu GsBarSelectVers"));
	this->_pGsBarSelectVers->Parent = this;
	this->_pGsBarSelectVers->Align = alTop;
	this->_pGsBarSelectVers->_pGsPanelSelectVers = this;
		//Objekt klasy TStringGrid z interlinearnym widokiem polsko-gerckim
	this->_pSGridInterlinearVers = new TStringGrid(this);
	if(!this->_pSGridInterlinearVers)
		throw(Exception("Nie dokonano inicjalizacji objektu TStringGrid"));
	this->_pSGridInterlinearVers->Parent = this;
	this->_pSGridInterlinearVers->Align = alBottom;
	this->_pSGridInterlinearVers->Ctl3D = false;
	this->_pSGridInterlinearVers->RowCount = enRow_Count;
	this->_pSGridInterlinearVers->FixedCols = 0;
	this->_pSGridInterlinearVers->FixedRows = 0;
	this->_pSGridInterlinearVers->Font->Quality = TFontQuality::fqClearType;
	this->_pSGridInterlinearVers->DefaultRowHeight = 2 * -this->_pSGridInterlinearVers->Font->Height;
	this->_pSGridInterlinearVers->DefaultColWidth = 148;
	this->_pSGridInterlinearVers->Height = this->_pSGridInterlinearVers->RowCount * (this->_pSGridInterlinearVers->DefaultRowHeight) + 28;
	this->_pSGridInterlinearVers->Options << goThumbTracking >> goRangeSelect >> goVertLine;// >> goHorzLine;
	//this->_pSGridInterlinearVers->Visible = !this->FIsVisibleSetTranslate;
	// [16-06-2024]
	this->_pSGridInterlinearVers->Visible = false;
	this->_pSGridInterlinearVers->Options = TGridOptions() >> goVertLine >> goHorzLine;
	this->_pSGridInterlinearVers->OnDrawCell = this->_DrawGridInterlinearVersCell;
	this->_pSGridInterlinearVers->DefaultDrawing = false;
	this->_pSGridInterlinearVers->Font->Size = 12;
	this->_pSGridInterlinearVers->StyleElements = TStyleElements(); //[17-06-2024]
	//---Wyświetlenie wersetów
	this->_pWebBrowser = new TWebBrowser(this);
	if(!this->_pWebBrowser) throw(Exception("Błąd inicjalizacji klasy TWebBrowser"));
	this->_pWebBrowser->TOleControl::Parent = this;
	this->_pWebBrowser->Align = alClient;
	this->_pWebBrowser->Offline = true;
	this->_pWebBrowser->Navigate(WideString("about:blank").c_bstr()); // wypełnienie kontrolki pustą stroną.
	this->_pWebBrowser->SetFocus();
	//---Edycja komentarza
	this->_pEditComment = new GsEditorClass(this);
	if(!this->_pEditComment) throw(Exception("Błąd inicjalizacji klasy GsEditorClass"));
	this->_pEditComment->Parent = this;
	this->_pEditComment->Align = alBottom;
	this->_pEditComment->Height = 240;
	//Wystarczy by jeden parametr miał wartość true
}
//---------------------------------------------------------------------------
void __fastcall GsPanelSelectVers::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	TCustomPanel::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsPanelSelectVers::_DisplayInterlinear(const unsigned char cucBook, const unsigned char cucChapt, const unsigned char cucVers)
/**
	OPIS METOD(FUNKCJI): Wyświetlenie interlinearnego układu dla greckiego oryginału
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if((cucBook < GsReadBibleTextData::GsPairsGroupBible[en_GrSearch_New].ucStartRange+1) || (cucBook > GsReadBibleTextData::GsPairsGroupBible[en_GrSearch_New].ucStopRange+1))
	{
		//Wyczyszczenie zawartości objektu, klasy TStringGrid
		for(int iRow=0; iRow<this->_pSGridInterlinearVers->RowCount; ++iRow)
		{
			for(int iCol=0; iCol<this->_pSGridInterlinearVers->ColCount; ++iCol)
			{
				this->_pSGridInterlinearVers->Cells[iCol][iRow] = "";
			}
		}
		return;
	}
	//---
	THashedStringList *pHSListSelectVers = new THashedStringList();
	if(!pHSListSelectVers)
		throw(Exception("Nie dokonano inicjalizacji objektu THashedStringList"));
	//---
	unsigned char ucBook, ucChapt, ucVers; //Numery odczytane

	for(int i=0; i<GsReadBibleTextData::pGsReadBibleTextClass->_SListInterLinear->Count; ++i)
	{
		ucBook = GsReadBibleTextData::pGsReadBibleTextClass->_SListInterLinear->Strings[i].SubString(1, 3).ToInt();
		ucChapt = GsReadBibleTextData::pGsReadBibleTextClass->_SListInterLinear->Strings[i].SubString(4, 3).ToInt();
		ucVers = GsReadBibleTextData::pGsReadBibleTextClass->_SListInterLinear->Strings[i].SubString(7, 3).ToInt();
		if((ucBook==cucBook) && (ucChapt==cucChapt) && (ucVers==cucVers))
			{pHSListSelectVers->Add(GsReadBibleTextData::pGsReadBibleTextClass->_SListInterLinear->Strings[i]);}
	}
	if(pHSListSelectVers->Count > 0) this->_pSGridInterlinearVers->ColCount = pHSListSelectVers->Count;	//Kolumn tyle, ile słów w wersecie
	for(int iIndex=0; iIndex<pHSListSelectVers->Count; ++iIndex)
	{
		this->_pSGridInterlinearVers->Cells[iIndex][enRow_StrongNumber] = pHSListSelectVers->Names[iIndex].Delete(1, 10).SubString(1, 5);
		this->_pSGridInterlinearVers->Cells[iIndex][enRow_GreckWord] = pHSListSelectVers->Names[iIndex].Delete(1, 10).SubString(7, 20);
		this->_pSGridInterlinearVers->Cells[iIndex][enRow_PolWord] = pHSListSelectVers->ValueFromIndex[iIndex];
		// Szerokość kolumny zależna od zawartości. Szerokość zależna od tekstu tłumaczenia, ze względu ze tekst ten jest najdłuższy //[16-06-2024]
		this->_pSGridInterlinearVers->ColWidths[iIndex] = this->_pSGridInterlinearVers->Canvas->TextWidth(pHSListSelectVers->ValueFromIndex[iIndex]) * 1.5;
		if(this->_pSGridInterlinearVers->ColWidths[iIndex] < 98) this->_pSGridInterlinearVers->ColWidths[iIndex] = 120;
	}
	if(pHSListSelectVers) {delete pHSListSelectVers; pHSListSelectVers = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall GsPanelSelectVers::_DrawGridInterlinearVersCell(System::TObject* Sender, int ACol, int ARow, const System::Types::TRect &Rect, TGridDrawState State)
/**
	OPIS METOD(FUNKCJI): Własne rysowanie komórek w objekcie, klasy TStringGrid // [16-06-2024]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TStringGrid *pSGrid = dynamic_cast<TStringGrid *>(Sender);
	if(!pSGrid) return;
	UnicodeString ustrCellText = pSGrid->Cells[ACol][ARow];
	TRect DrawRect = Rect;
	InflateRect(DrawRect, -2, 0);

	pSGrid->Canvas->Brush->Color = pSGrid->Color;
  pSGrid->Canvas->FillRect(Rect);

	if(ARow == enRow_GreckWord) pSGrid->Canvas->Font->Color = clRed;
	else if(ARow == enRow_StrongNumber) pSGrid->Canvas->Font->Color = clGreen;
	else if(ARow == enRow_PolWord)
	{
		pSGrid->Canvas->Font->Style = TFontStyles() << fsBold;
	}

	DrawText(pSGrid->Canvas->Handle, ustrCellText.c_str(), -1, &DrawRect, DT_SINGLELINE | DT_VCENTER);
}
/****************************************************************************
 *										 KLASA GsTabSheetSelectVersClass											*
 ****************************************************************************/
__fastcall GsTabSheetSelectVersClass::GsTabSheetSelectVersClass(TComponent* Owner) : TTabSheet(Owner)
/**
	OPIS METOD(FUNKCJI): Główny konstruktor, klasy GsTabSheetSelectVersClass
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!GsReadBibleTextData::pGsReadBibleTextClass)
		throw(Exception("Nie dokonano inicjalizacji objektu GsReadBibleTextClass"));
	//---
  this->Font->Size = 12;
	this->Font->Quality = TFontQuality::fqClearType;
	this->ParentFont = true;
	this->Caption = "Lista wybranych wersetów";
	this->ImageIndex = enImageIndex_CopyToSheet;
	GsReadBibleTextData::GsSheetListVers = this;
	this->PageControl = GsReadBibleTextData::_GsPageControl; //Umieszczanie objektu klasy na objekcie typu TPageControl
	this->PageControl->ActivePage = this; //Nowostworzona zakładka, staje się zakładką aktualną

  this->pGsControlListVers = new GsControlListVers(this);
	if(!this->pGsControlListVers) throw(Exception("Nie można zainicjować klasy GsControlListVers"));
	this->pGsControlListVers->Parent = this;
	this->pGsControlListVers->Align = alClient;
	this->pGsControlListVers->AlignWithMargins = true;
	this->pGsControlListVers->ItemHeight = 2.9 * this->Font->Size;
}
//---------------------------------------------------------------------------
__fastcall GsTabSheetSelectVersClass::~GsTabSheetSelectVersClass()
/**
	OPIS METOD(FUNKCJI): Główny Destruktor, klasy GsTabSheetSelectVersClass
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetSelectVersClass::CreateWnd()
/**
	OPIS METOD(FUNKCJI): Tworzenie kontrolki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TTabSheet::CreateWnd();
	//Własny kod.
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetSelectVersClass::DestroyWnd()
/**
	OPIS METOD(FUNKCJI): Niszczenie kontrolki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	TTabSheet::DestroyWnd();
}
/****************************************************************************
*												 Klasa GsControlListVers														*
*			Wyświetlanie wybranego wersetu w głównej zakładce, w głównym oknie		*
*****************************************************************************/
__fastcall GsControlListVers::GsControlListVers(TComponent* Owner) : TCustomControlList(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->pHSListVerses = new THashedStringList();
	if(!this->pHSListVerses) throw(Exception("Nie można zainicjować klasy THashedStringList"));
	this->OnEnableItem = this->ControlListEnableItem;
	this->Font->Quality = TFontQuality::fqClearType;
	this->ParentFont = true;
}
//---------------------------------------------------------------------------
__fastcall GsControlListVers::~GsControlListVers()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if(this->pHSListVerses) {delete this->pHSListVerses; this->pHSListVerses = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall GsControlListVers::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCustomControlList::CreateWnd();
	//Własny kod.
	this->pImageVers = new TImage(this);
	if(!this->pImageVers) throw(Exception("Nie można zainicjować klasy TImage"));
	//this->pImageVers->Parent = this;
	this->pImageVers->Align = alLeft;
	this->pImageVers->Width = GsReadBibleTextData::_GsImgListDataLarge->Width + 4;
	this->pImageVers->Center = true;
	//---
	this->pLabelAdress = new TLabel(this);
	if(!this->pLabelAdress) throw(Exception("Nie można zainicjować klasy TLabel"));
	//this->pLabelAdress->Parent = this;
	//this->pLabelAdress->Width = 100;
	this->pLabelAdress->StyleElements = TStyleElements();
	this->pLabelAdress->Align = alLeft;
	this->pLabelAdress->AlignWithMargins = true;
	this->pLabelAdress->Layout = tlCenter;
	this->pLabelAdress->AutoSize = false;
	this->pLabelAdress->Font->Style = TFontStyles()<< fsBold;
	this->pLabelAdress->Font->Color = clRed;
	//---
	this->pLabelText = new TLabel(this);
	if(!this->pLabelText) throw(Exception("Nie można zainicjować klasy TLabel"));
	//this->pLabelText->Parent = this;
	this->pLabelText->Align = alClient;
	this->pLabelText->AutoSize = false;
	this->pLabelText->AlignWithMargins = true;
	this->pLabelText->Layout = tlCenter;
	this->pLabelText->EllipsisPosition = epEndEllipsis;
	//---
	this->pLabelTranslate = new TLabel(this);
	if(!this->pLabelTranslate) throw(Exception("Nie można zainicjować klasy TLabel"));
	//this->pLabelTranslate->Parent = this;
	this->pLabelTranslate->Align = alRight;
	this->pLabelTranslate->Alignment = taLeftJustify;
	this->pLabelTranslate->AlignWithMargins = true;
	this->pLabelTranslate->StyleElements = TStyleElements();
	this->pLabelTranslate->AutoSize = false;
	this->pLabelTranslate->Width = 200;
	this->pLabelTranslate->Font->Size = 9;
	this->pLabelTranslate->Font->Color = clYellow;
	this->pLabelTranslate->Layout = tlBottom;
	//---
	this->AddControlToItem(this->pImageVers);
	this->AddControlToItem(this->pLabelAdress);
	this->AddControlToItem(this->pLabelText);
	this->AddControlToItem(this->pLabelTranslate);
}
//---------------------------------------------------------------------------
void __fastcall GsControlListVers::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //Własny kod.
	TCustomControlList::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsControlListVers::DoBeforeDrawItem(int AIndex, Vcl::Graphics::TCanvas* ACanvas,
			const System::Types::TRect &ARect, Winapi::Windows::TOwnerDrawState AState)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsReadBibleTextItem *pGsReadBibleTextItem=nullptr;
  TRect MyRect = ARect;

	if(this->pHSListVerses->Strings[AIndex].Length() > 0)
	{
		pGsReadBibleTextItem = static_cast<GsReadBibleTextItem *>(this->pHSListVerses->Objects[AIndex]);
		this->pLabelAdress->Caption = Format("%s", ARRAYOFCONST((this->pHSListVerses->Names[AIndex])));
		this->pLabelText->Caption = Format("%s", ARRAYOFCONST((this->pHSListVerses->ValueFromIndex[AIndex])));
		GsReadBibleTextData::_GsImgListDataLarge->GetIcon(0, this->pImageVers->Picture->Icon);
		if(pGsReadBibleTextItem)
			this->pLabelTranslate->Caption = pGsReadBibleTextItem->NameTranslate;
	}
	else
	{
		MyRect.Inflate(-8, -8, -8, -8);
		FillRectAlpha(ACanvas, MyRect, clBlue, 50);
		this->pLabelAdress->Caption = "";
		this->pLabelText->Caption = "";
		this->pLabelTranslate->Caption = "";
    this->pImageVers->Picture->Assign(nullptr);
  }
}
//---------------------------------------------------------------------------
void __fastcall GsControlListVers::DoItemClicked()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
//  #if defined(_DEBUGINFO_)
//		//GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
//		GsDebugClass::WriteDebug("DoItemClicked()");
//	#endif
}
//---------------------------------------------------------------------------
void __fastcall GsControlListVers::ControlListEnableItem(const int AIndex, bool &AEnabled)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->pHSListVerses->Strings[AIndex].Length() == 0)
		AEnabled = false;
}
/****************************************************************************
*												 Klasa GsLViewDictionaryClass												*
*****************************************************************************/
static const int ciMaxStrongCount=5625; //Maksymalny numer słowa w greckim nowym testamencie, według numeracji Stronga
//Tablica nazw kolumn w głównej liście
static UnicodeString ustrColumsNames[] = {"Grecki wyraz", "Numeracja wg. Stronga", "Tłumaczenie na polski"};
enum {enGreekWord, enNumberStrong, enTranslates, enSize};
enum {enIconPosition, enIconGreekWord, enIconStrongNum, enIconDictPol};
__fastcall GsLViewDictionaryClass::GsLViewDictionaryClass(TComponent* Owner) : TCustomListView(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_pListWordGrec = new TList();
	if(!this->_pListWordGrec) throw(Exception("Błąd funkcji TList"));
	//this->StyleElements = TStyleElements(); //Musi być
	this->OwnerData = true;
	this->OwnerDraw = true;
	//this->OnGetImageIndex = this->_OnGetImageIndex;
	//this->OnGetSubItemImage = this->_OnGetSubItemImage;
	//this->DoubleBuffered = true;
  this->Font->Quality = TFontQuality::fqClearType;
	this->ParentFont = true;
	this->Font->Size = 12;
	this->_iLViewStartIndex=0; this->_iLViewEndIndex=0; //Zakres dolny i górny elementów w liście wirtualnej
	this->ReadOnly = true;
	this->RowSelect = true;
	this->ViewStyle = vsReport;
	this->SmallImages = GsReadBibleTextData::_GsImgListData; //Ikony kolumn
}
//---------------------------------------------------------------------------
__fastcall GsLViewDictionaryClass::~GsLViewDictionaryClass()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//--- Deallokacja listy, struktarami dla każdego słowa
	for(int i=0; i<this->_pListWordGrec->Count; ++i)
	{
		DataGrecWordDictClass *pDataGrecWordDictClass = static_cast<DataGrecWordDictClass *>(this->_pListWordGrec->Items[i]);
		if(pDataGrecWordDictClass)
		{
			delete pDataGrecWordDictClass; pDataGrecWordDictClass = nullptr;
//      #if defined(_DEBUGINFO_)
//				GsDebugClass::WriteDebug(Format("i: %d -> GsLViewDictionaryClass", ARRAYOFCONST((i))));
//			#endif
		}
	}

	this->_pListWordGrec->Clear();
	if(this->_pListWordGrec) {delete this->_pListWordGrec; this->_pListWordGrec = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall GsLViewDictionaryClass::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCustomListView::CreateWnd();
	//Własny kod.
  this->_CreateAllColumns();
	this->Items->BeginUpdate();
	//--- Allokacja listy, struktarami dla każdego słowa według Stronga - czyli 5625 pozycji
	for(int i=0; i<ciMaxStrongCount; ++i)
	{
		DataGrecWordDictClass *pDataGrecWordDictClass = new DataGrecWordDictClass();
		if(!pDataGrecWordDictClass) throw(Exception("Błąd funkcji DataGrecWordDictClass"));
		pDataGrecWordDictClass->IsDataEmpty = true; //Domyślnie true, klasa jeszcze nie wypełniona. Przy pierwszym wypełnieniu, zmienia wartość na false
		if(pDataGrecWordDictClass)
			{this->_pListWordGrec->Add(pDataGrecWordDictClass);}
	}
	//this->_pListWordGrec->Count
	//--- Obróbka danych z pliku \Data\gnt.intrl.
	// Uzyskanie wskaźnika na listę z zawartościa pliku z danymi interlinearnymi, grecko-polskimi, czyli "gnt.intrl"
	THashedStringList *pHSListInterlinearGreek = GsReadBibleTextData::pGsReadBibleTextClass->GetListInterlinearGrec();

	for(int i=0; i<pHSListInterlinearGreek->Count; ++i)
	{
		if(!pHSListInterlinearGreek->Strings[i].IsEmpty()) //Wszystkie słowa greckiego przekładu
		{
			//Pozyskanie numeru Stronga
			int iStrongNumber = pHSListInterlinearGreek->Strings[i].SubString(12, 4).ToIntDef(0); //Numer Stronga
			if(iStrongNumber > 0)
			{
				// Wyłuskanie struktury z stringlisty this->_pListWordGrec, o numerze wybranej pozycji.
        // Z pozycji tej odczytany jest numer Stronga
				DataGrecWordDictClass *pDataGrecWordDictClass = static_cast<DataGrecWordDictClass *>(this->_pListWordGrec->Items[iStrongNumber]);
				if(pDataGrecWordDictClass->IsDataEmpty)
				{
					pDataGrecWordDictClass->ustrGrecName = pHSListInterlinearGreek->Names[i].SubString(17, 200); //Greckie słowo
					pDataGrecWordDictClass->ustrStrongNumber = pHSListInterlinearGreek->Names[i].SubString(11, 5); //String stronga GXXXX
					pDataGrecWordDictClass->ustrDictPol = pHSListInterlinearGreek->ValueFromIndex[i]; // Tłumaczenie
					pDataGrecWordDictClass->IsDataEmpty = false;
				}
				// Lista wersetów, w których dane słowo występuje. Lista jest w strukturze DataGrecWordDictClass, która
				// odpowiada konkretnemu numerowi Stronga. DataGrecWordDictClass są zgrupowane w liście
				//
				pDataGrecWordDictClass->pHSListVers->Add(pHSListInterlinearGreek->Names[i].SubString(1, 9)); //Lista wersetów, w których dane słowo występuje
			}
		}
	}
	//Zlikwidowanie pierwszej pozycji
	DataGrecWordDictClass *pDataGrecWordDictClass = static_cast<DataGrecWordDictClass *>(this->_pListWordGrec->Items[0]);
	if(pDataGrecWordDictClass) {delete pDataGrecWordDictClass; pDataGrecWordDictClass = nullptr;}
	this->_pListWordGrec->Delete(0);
	//---
	this->Items->Count = this->_pListWordGrec->Count;
	this->Items->EndUpdate();
	//---Inicjalizacja objektu, klasy TWebBrowser
	this->_pWBrowseResult = new TWebBrowser(this->Parent);
	if(!this->_pWBrowseResult) throw(Exception("Błąd inicjalizacji klasy TWebBrowser"));
	this->_pWBrowseResult->TOleControl::Parent = this->Parent;
	this->_pWBrowseResult->Align = alClient;
	this->_pWBrowseResult->Offline = true;
	this->_pWBrowseResult->Navigate(WideString("about:blank").c_bstr()); // wypełnienie kontrolki pustą stroną.
	this->_pWBrowseResult->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall GsLViewDictionaryClass::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	TCustomListView::DestroyWnd();
}
//---------------------------------------------------------------------------
bool __fastcall GsLViewDictionaryClass::OwnerDataFetch(Comctrls::TListItem* Item, Comctrls::TItemRequest Request)
/**
	OPIS METOD(FUNKCJI): OnData
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if ((Item->Index > this->_iLViewEndIndex) || (Item->Index < this->_iLViewStartIndex)) return false;

	if(Request.Contains(irText) || Item->Caption.IsEmpty())
	{
		//Item->Caption = this->_pHSList->Strings[Item->Index];
		DataGrecWordDictClass *pDataGrecWordDictClass = static_cast<DataGrecWordDictClass *>(this->_pListWordGrec->Items[Item->Index]);

		Item->Caption = pDataGrecWordDictClass->ustrGrecName;
		//Item->ImageIndex = enIconPosition;
		Item->SubItems->Add(pDataGrecWordDictClass->ustrStrongNumber);
		Item->SubItems->Add(pDataGrecWordDictClass->ustrDictPol);
	}
	if (Request.Contains(irImage))
	{
		//Item->ImageIndex = pItemInfoFile->iIconId;
	}

	return true;
}
//---------------------------------------------------------------------------
void __fastcall GsLViewDictionaryClass::_CreateAllColumns()
/**
	OPIS METOD(FUNKCJI): Tworzenie kolumn
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListColumn *NewColumn=nullptr;

	//Dodawanie kolumn
	for(unsigned int iColumns=0; iColumns<ARRAYSIZE(ustrColumsNames); ++iColumns)
	{
		NewColumn = this->Columns->Add();
		NewColumn->Caption = ustrColumsNames[iColumns];
		NewColumn->Width = 2 * this->Canvas->TextWidth(ustrColumsNames[iColumns]);
		NewColumn->ImageIndex = enImageIndex_GrecWordColumn + iColumns;//ID_GLOBALIMAGE_ID_GRECWORD_COLUMN + iColumns;
	}
}
//---------------------------------------------------------------------------
bool __fastcall GsLViewDictionaryClass::OwnerDataHint(int StartIndex, int EndIndex)
/**
	OPIS METOD(FUNKCJI): OnDataHint
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_iLViewStartIndex = StartIndex; //Dolny zakres, elementów listy
	this->_iLViewEndIndex = EndIndex;			//Górny zakres, elementów listy

	return true;
}
//---------------------------------------------------------------------------
int __fastcall GsLViewDictionaryClass::OwnerDataFind(TItemFind Find, const System::UnicodeString FindString, const System::Types::TPoint &FindPosition,
			void * FindData, int StartIndex, TSearchDirection Direction, bool Wrap)
/**
	OPIS METOD(FUNKCJI): OnDataHint
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	for(int i=0; i<this->_pListWordGrec->Count; ++i)
	{
		DataGrecWordDictClass *pDataGrecWordDictClass = static_cast<DataGrecWordDictClass *>(this->_pListWordGrec->Items[i]);
		if (UpperCase(pDataGrecWordDictClass->ustrGrecName) == UpperCase(FindString))
		{
			return i;
			//break;
		}
	}
	return -1;
}
//---------------------------------------------------------------------------
void __fastcall GsLViewDictionaryClass::DrawItem(TListItem* Item, const System::Types::TRect &Rect, Winapi::Windows::TOwnerDrawState State)
/**
	OPIS METOD(FUNKCJI):Rysowanie pozycji listy
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TRect RectBounds = Item->DisplayRect(drBounds);
	TRect RectLabel = Item->DisplayRect(drLabel);
	TRect RectIcon = Item->DisplayRect(drIcon);
	//--- Kolory aktywnego stylu //[16-12-2023]
	TColor cBackGround = TStyleManager::ActiveStyle->GetStyleColor(scListView);
	TColor cText = TStyleManager::ActiveStyle->GetStyleFontColor(sfListItemTextNormal);
	this->Canvas->Brush->Color = cBackGround;

	if(State.Contains(odSelected))
	{
		this->Canvas->Brush->Color = clWebRoyalBlue;//clYellow;
	}
	this->Canvas->FillRect(RectBounds);

	this->SmallImages->Draw(this->Canvas, RectIcon.Left, RectIcon.Top + 1, enImageIndex_GrecWordItem);

	this->Canvas->Font->Color = clRed;
	this->Canvas->Font->Style = TFontStyles() << fsBold;
	DrawText(this->Canvas->Handle, Item->Caption.c_str(), -1, &RectLabel, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	//---
	TRect RectSubItemText = RectBounds; RectSubItemText.Left += 20; //[16-12-2023]
	TRect RectSubItemIcon = RectBounds; RectSubItemIcon.Left += 4;	//[16-12-2023]

	for(int iColumn=1; iColumn<this->Columns->Count; ++iColumn)
	{
		//Wymiary następnej kolumny
		RectSubItemText.Left += this->Column[iColumn-1]->Width;
		RectSubItemText.Right = RectSubItemText.Left + this->Column[iColumn]->Width;

		RectSubItemIcon.Left += this->Column[iColumn-1]->Width; //[16-12-2023]
		//
		if(iColumn==1)
		{
			this->Canvas->Font->Color = clWebLimeGreen;
			this->Canvas->Font->Style = TFontStyles();
			this->SmallImages->Draw(this->Canvas, RectSubItemIcon.Left, RectSubItemIcon.Top + 1, enImageIndex_GrecStrongColumn); //[16-12-2023]
		}
		else if(iColumn==2)
		{
			this->Canvas->Font->Color = cText;//this->Font->Color; //Tłumaczenie
			this->Canvas->Font->Style = TFontStyles();
			this->SmallImages->Draw(this->Canvas, RectSubItemIcon.Left, RectSubItemIcon.Top + 1, enImageIndex_GrecDictionaryColumn); //[16-12-2023]
		}

		DrawText(this->Canvas->Handle, Item->SubItems->Strings[iColumn-1].c_str(), -1, &RectSubItemText, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	}
}
//--------------------------------------------------------------------------
void __fastcall GsLViewDictionaryClass::_OnGetImageIndex(System::TObject* Sender, TListItem* Item)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	Item->ImageIndex = enImageIndex_GrecWordItem;
}
//---------------------------------------------------------------------------
void __fastcall GsLViewDictionaryClass::_OnGetSubItemImage(System::TObject* Sender, TListItem* Item, int SubItem, int &ImageIndex)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	ImageIndex = enImageIndex_GrecWordItem;
}
//---------------------------------------------------------------------------
void __fastcall GsLViewDictionaryClass::DoSelectItem(TListItem* Item, bool Selected)
/**
	OPIS METOD(FUNKCJI): Wybranie pozycji z ListView listy
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->ItemIndex == -1) return;	//Kliknąłeś poza pozycje listy, która jest numerem stronga
	THashedStringList *pHSListTemp=nullptr;
	try
	{
		pHSListTemp = new THashedStringList();
		if(!pHSListTemp) throw(Exception("Błąd funkcji THashedStringList"));
		//--- Wyciągnięcie struktury DataGrecWordDictClass, wybranej pozycji
		DataGrecWordDictClass *pDataGrecWordDictClass = static_cast<DataGrecWordDictClass *>(this->_pListWordGrec->Items[this->ItemIndex]);
		if(pDataGrecWordDictClass)
		//Jeśli uzyskano wskażnik na listę wystąpień słowa greckiego
		{
			for(int iVers=0; iVers<pDataGrecWordDictClass->pHSListVers->Count; ++iVers)
			//Liczenie elementów listy wystąpień greckiego słowa
			{
				//Odczytanie księgi z pozycji, listy wystąpień greckiego słowa
				int iBook = pDataGrecWordDictClass->pHSListVers->Strings[iVers].SubString(1, 3).ToInt();
				//Uzyskanie wskażnika na liste wersetów wybranej księgi
				THashedStringList *pHSListGreek = GsReadBibleTextData::pGsReadBibleTextClass->GetSelectBookOrgTranslate(iBook-1);//iBook);
				for(int i=0; i<pHSListGreek->Count; ++i)
				//Liczenie wersetów wybranej księgi
				{
					if(pDataGrecWordDictClass->pHSListVers->Strings[iVers] == pHSListGreek->Strings[i].SubString(1, 9))
					{
						//Jeśli adres miejsca wystąpienia greckiego słowa, z kolejnej pozycji, listy wystąpień,
						//zgadza się z adresem odczytanego, kolejnego wersetu z listy wersetów, wybranego wcześniej rozdiału,
						//werset zostaje dodany do tymczasowej listy.
						pHSListTemp->AddObject(pHSListGreek->Strings[i].SubString(11, GlobalVar::Global_MaxlengthVers), pHSListGreek->Objects[i]);
						break;
					}
				}
			}
		}
		DataDisplayTextAnyBrowser SetDataDisplay;
		SecureZeroMemory(&SetDataDisplay, sizeof(DataDisplayTextAnyBrowser));
		SetDataDisplay.strBackgroundColor = RGBToWebColorStr(clWebAzure);
		SetDataDisplay.strNameFont = "Times New Roman";
		SetDataDisplay.iSizeFont = 16;
		SetDataDisplay.pMemoryStream = nullptr;
		SetDataDisplay.bIsHorizontLine = true;
		//---
		GsReadBibleTextData::pGsReadBibleTextClass->_ViewSListBibleToHTML(this->_pWBrowseResult, pHSListTemp, SetDataDisplay);
	}
	__finally
	{
		if(pHSListTemp) {delete pHSListTemp; pHSListTemp = nullptr;}
	}
}
/****************************************************************************
*												 Klasa GsLViewCommentsAllClass											*
*****************************************************************************/
static UnicodeString ustrColumsNamesComments[] = {"Werset", "Komentarz"};
enum {enComments_Vers, enComments_Comment, enComments_Count};
//---------------------------------------------------------------------------
ListComments::ListComments(const UnicodeString _ustrName) : LC_FileName(_ustrName)
/**
	OPIS METOD(FUNKCJI): Konstruktor klasy ListComments
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	UnicodeString ustrTemp = TPath::GetFileNameWithoutExtension(_ustrName);

	this->LC_ucBook = ustrTemp.SubString(1, 3).ToInt() - 1,//Księgi są numerowane w pliku z tłumaczeniem od 1, a teblice od 0.
	this->LC_ucChapt = ustrTemp.SubString(4, 3).ToInt(),
	this->LC_ucVers = ustrTemp.SubString(7, 3).ToIntDef(0);
	//----- Tworzenie adresu wersetu
	this->LC_BookChaptVers = Format("%s %d:%d", ARRAYOFCONST((AppCTable_InfoAllBooks[this->LC_ucBook].ShortNameBook, this->LC_ucChapt, this->LC_ucVers)));
}
//---------------------------------------------------------------------------
ListComments::~ListComments()
/**
	OPIS METOD(FUNKCJI): Destruktor klasy ListComments
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
}
//---------------------------------------------------------------------------
__fastcall GsLViewCommentsAllClass::GsLViewCommentsAllClass(TComponent* Owner) : TCustomListView(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListColumn *NewColumn=nullptr;
	ListComments *pListComments=nullptr;

	this->_ListComments = new TList();
	if(!this->_ListComments) throw(Exception("Błąd inicjalizacji objektu, klasy TList"));

	this->Font->Quality = TFontQuality::fqClearType;
	this->ParentFont = true;
	this->OwnerData = true;
	this->OwnerDraw = true;
	this->ReadOnly = true;
	this->RowSelect = true;
	//this->DoubleBuffered = true;
	this->ViewStyle = vsReport;
	this->_iLViewStartIndex=0; this->_iLViewEndIndex=0; //Zakres dolny i górny elementów w liście wirtualnej
	//Dodawanie kolumn
	for(unsigned int iColumns=0; iColumns<ARRAYSIZE(ustrColumsNamesComments); ++iColumns)
	{
		NewColumn = this->Columns->Add();
		NewColumn->Caption = ustrColumsNamesComments[iColumns];
		if(iColumns>0) NewColumn->AutoSize = true;
		else NewColumn->Width = 68;
		//NewColumn->ImageIndex = enImageIndex_GrecWordColumn + iColumns;//ID_GLOBALIMAGE_ID_GRECWORD_COLUMN + iColumns;
	}
	//---
	this->ReloadAllVersComments();
	GsReadBibleTextData::pGsLViewCommentsAllClass = this; //Zapamiętanie wskaźnika na objekt, klasy GsLViewCommentsAllClas, utworzony w głównym oknie
}
//--------------------------------------------------------------------------
void __fastcall GsLViewCommentsAllClass::ReloadAllVersComments(bool _bStartup)
/**
	OPIS METOD(FUNKCJI): Wyczyszcenie i pomowne załadowanie listy wersetów
	OPIS ARGUMENTÓW: bool _Startup - pierwsze załadowanie listy, domyślnie true
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	ListComments *pListComments=nullptr;
	UnicodeString ustrExtFileComment = Format("*%s", ARRAYOFCONST((GlobalVar::Global_custrExtendCommentsFiles))); //Wstawienie na początek znaku gwiazdki
	TStringDynArray SDirFileList; //Lista plików z komentarzem
	//Najpierw zwolnienie listy this->_ListComments
	if(this->_ListComments->Count > 0)
	{
		for(int i=0; i<this->_ListComments->Count; ++i)
		{
			pListComments = static_cast<ListComments *>(this->_ListComments->Items[i]);
			if(pListComments) {delete pListComments; pListComments = nullptr;}
		}
		this->_ListComments->Clear();
	}
	//---
	//Odczyt wszystkich dostępnych komentarzy
	SDirFileList = TDirectory::GetFiles(GlobalVar::Global_custrPathDirComments, ustrExtFileComment, 0);
	//Stworzenie listy objektów, klasy ListComments
	for(int i=0; i<SDirFileList.Length; ++i)
	{
		pListComments = new ListComments(SDirFileList[i]);
		if(!pListComments) throw(Exception("Błąd wyłuskania objektu, klasy ListComments"));
		this->_ListComments->Add(pListComments); //Dodanie klasy do listy komentarzy
	}
	//-----
	if(!_bStartup)
	{
		//Wyświetlenie oświerzonej listy, ale tylko przy odświerzeniu, nie przy pierwszym załadowaniu.
		//Metoda wywoływana przez objekt, klasy TMainBibleWindow. w metodzie Act_SelectVersExecute,
		//po zamknięciu okna wybory wersetów(ewentualna mozliwość napisania, lub modyfikacji komentarza),
		//w oknie, objektu, klasy TSelectVersWindow
		//Poniższe linijki, są wywoływane w metodzie CreateWnd(), bo inaczej nie zadziała klasa, jako OwnerData,
		//później gdy zawartość bedzie odświerzana dopiero wtedy bedzie wykonywany poniższy kod.
		this->Items->BeginUpdate();
		this->Items->Count = this->_ListComments->Count;
		this->Items->EndUpdate();
	}
}
//--------------------------------------------------------------------------
__fastcall GsLViewCommentsAllClass::~GsLViewCommentsAllClass()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	ListComments *pListComments=nullptr;
	//Zwolnienie listy komentarzy
	if(this->_ListComments)
	{
		for(int i=0; i<this->_ListComments->Count; ++i)
		//Zwalnianie poszczególnych klas komentarzy z listy
		{
			pListComments = static_cast<ListComments *>(this->_ListComments->Items[i]);
			if(pListComments) {delete pListComments; pListComments = nullptr;}
		}
		delete this->_ListComments; this->_ListComments = nullptr; //Konćowe zwolnienie objektu, klasy TList, z listą komentarzy
	}
}
//--------------------------------------------------------------------------
ListComments *__fastcall GsLViewCommentsAllClass::GetSelectComent(int iIndex)
/**
	OPIS METOD(FUNKCJI): Zwracana, wybrana pozycja komentarza
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(iIndex >= this->_ListComments->Count) return 0;
	ListComments *pListComments=nullptr;
	pListComments = static_cast<ListComments *>(this->_ListComments->Items[iIndex]);
	if(pListComments) return pListComments;
	return 0;
}
//--------------------------------------------------------------------------
void __fastcall GsLViewCommentsAllClass::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCustomListView::CreateWnd();
	//Własny kod.
	this->Items->BeginUpdate();
	this->Items->Count = this->_ListComments->Count;
	this->Items->EndUpdate();
}
//--------------------------------------------------------------------------
void __fastcall GsLViewCommentsAllClass::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	TCustomListView::DestroyWnd();
}
//--------------------------------------------------------------------------
bool __fastcall GsLViewCommentsAllClass::OwnerDataFetch(Comctrls::TListItem* Item, Comctrls::TItemRequest Request)
/**
	OPIS METOD(FUNKCJI): OnData
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if ((Item->Index > this->_iLViewEndIndex) || (Item->Index < this->_iLViewStartIndex)) return false;
	ListComments *pListComments;//=0;
	if(Request.Contains(irText) || Item->Caption.IsEmpty())
	{
		//Item->Caption = this->_pHSList->Strings[Item->Index];
		pListComments = static_cast<ListComments *>(this->_ListComments->Items[Item->Index]);

		Item->Caption = pListComments->LC_BookChaptVers;
		//Item->ImageIndex = enIconPosition;
		//Item->SubItems->Add(pListComments->LC_ustrComment);
	}
	if (Request.Contains(irImage))
	{
		//Item->ImageIndex = pItemInfoFile->iIconId;
	}

	return true;
}
//---------------------------------------------------------------------------
bool __fastcall GsLViewCommentsAllClass::OwnerDataHint(int StartIndex, int EndIndex)
/**
	OPIS METOD(FUNKCJI):Rysowanie pozycji listy
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_iLViewStartIndex = StartIndex; //Dolny zakres, elementów listy
	this->_iLViewEndIndex = EndIndex;			//Górny zakres, elementów listy

	return true;
}
//---------------------------------------------------------------------------
int __fastcall GsLViewCommentsAllClass::OwnerDataFind(TItemFind Find, const System::UnicodeString FindString, const System::Types::TPoint &FindPosition,
			void * FindData, int StartIndex, TSearchDirection Direction, bool Wrap)
/**
	OPIS METOD(FUNKCJI): OnDataHint
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	ListComments *pListComments=nullptr;
	for(int i=0; i<this->_ListComments->Count; ++i)
	{
		pListComments = static_cast<ListComments *>(this->_ListComments->Items[i]);
		if (UpperCase(pListComments->LC_FileName) == UpperCase(FindString))
		{
			return i;
			//break;
		}
	}
	return -1;
}
//---------------------------------------------------------------------------
void __fastcall GsLViewCommentsAllClass::DoSelectItem(TListItem* Item, bool Selected)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if((this->ItemIndex == -1) || (!Selected)) return;	//Kliknąłeś poza pozycje listy
	ListComments *pListComments=nullptr;
	pListComments = static_cast<ListComments *>(this->_ListComments->Items[Item->Index]);
	if(!pListComments) return;
}
//---------------------------------------------------------------------------
void __fastcall GsLViewCommentsAllClass::DrawItem(TListItem* Item, const System::Types::TRect &Rect, Winapi::Windows::TOwnerDrawState State)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TRect RectBounds = Item->DisplayRect(drBounds);
	TRect RectLabel = Item->DisplayRect(drLabel);
	TRect RectIcon = Item->DisplayRect(drIcon);
	//--- Kolory aktywnego stylu //[16-12-2023]
	TColor cBackGround = TStyleManager::ActiveStyle->GetStyleColor(scListView);
	TColor cText = TStyleManager::ActiveStyle->GetStyleFontColor(sfListItemTextNormal);

	this->Canvas->Brush->Color = cBackGround;//clGreen;
	if(State.Contains(odSelected))
	{
		this->Canvas->Brush->Color = clWebDarkTurquoise;//clGreen;
	}
	this->Canvas->FillRect(RectBounds);
	this->Canvas->Font->Color = clWebBlue;
	this->Canvas->Font->Style = TFontStyles() << fsBold;

	DrawText(this->Canvas->Handle, Item->Caption.c_str(), -1, &RectLabel, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	//return;
	TRect RectSubItem = RectBounds; RectSubItem.Left += 4;
	for(int iColumn=1; iColumn<this->Columns->Count; ++iColumn)
	{
		//Wymiary następnej kolumny
		RectSubItem.Left += this->Column[iColumn-1]->Width + 1;
		RectSubItem.Right = RectSubItem.Left + this->Column[iColumn]->Width;
		if(iColumn==1)
		{
			this->Canvas->Font->Color = cText;//this->Font->Color;
			this->Canvas->Font->Style = TFontStyles();
		}

		DrawText(this->Canvas->Handle, TEXT("Komentarz"), -1, &RectSubItem, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	}
}
//---------------------------------------------------------------------------
void __fastcall GsLViewCommentsAllClass::DblClick()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Sprawdzenie poprawności podwójnego kliknięcia
	if(this->ItemIndex == -1) return;
	ListComments *pListComments=nullptr;
	pListComments = static_cast<ListComments *>(this->_ListComments->Items[this->ItemIndex]);
	if(!pListComments) return;
	//Jeśli istnieje zewnętrzna metoda OnDblClick() to ją wywołaj
	if(this->FOnDblClick) this->FOnDblClick(this);
}
//---------------------------------------------------------------------------
/****************************************************************************
*												Klasa GsListBoxFavoritiesClass											*
*****************************************************************************/
__fastcall GsListBoxFavoritiesClass::GsListBoxFavoritiesClass(TComponent* Owner) : TCustomListBox(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//this->DoubleBuffered = true;
	this->Style = lbOwnerDrawVariable;
	this->Font->Quality = TFontQuality::fqClearType;
	this->ParentFont = true;
	//this->StyleElements = TStyleElements();
	GsReadBibleTextData::pGsListBoxFavoritiesClass = this;
}
//---------------------------------------------------------------------------
__fastcall	GsListBoxFavoritiesClass::~GsListBoxFavoritiesClass()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
void __fastcall GsListBoxFavoritiesClass::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCustomListBox::CreateWnd();
	//Własny kod.
	this->ReLoadFavList();
}
//---------------------------------------------------------------------------
void __fastcall GsListBoxFavoritiesClass::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	TCustomListBox::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsListBoxFavoritiesClass::DblClick()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->ItemIndex == -1) return;

	//Jeśli istnieje zewnętrzna metoda OnDblClick() to ją wywołaj
	if(this->FOnDblClick) this->FOnDblClick(this);
}
//---------------------------------------------------------------------------
void __fastcall GsListBoxFavoritiesClass::DrawItem(int Index, const TRect &Rect, TOwnerDrawState State)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCanvas *pCanvas = this->Canvas;
	TRect MyRect(Rect);
	int ucBook, ucChapt, ucVers;
	UnicodeString BookChaptVers;

	pCanvas->FillRect(Rect);

	if(!this->Items->Strings[Index].IsEmpty())
	{
		ucBook = this->Items->Strings[Index].SubString(1, 3).ToInt() - 1,//Księgi są numerowane w pliku z tłumaczeniem od 1, a teblice od 0.
		ucChapt = this->Items->Strings[Index].SubString(4, 3).ToInt(),
		ucVers = this->Items->Strings[Index].SubString(7, 3).ToIntDef(0);
		//----- Tworzenie adresu wersetu
		BookChaptVers = Format("%s %d:%d", ARRAYOFCONST((AppCTable_InfoAllBooks[ucBook].ShortNameBook, ucChapt, ucVers)));
		MyRect.Left += 4; MyRect.Right -= 4;

		DrawText(pCanvas->Handle, BookChaptVers.c_str(), -1, &MyRect, DT_SINGLELINE | DT_VCENTER);
	}
	//---Zlikwidowanie obramówki w wybranej pozycji
	if(State.Contains(odFocused)) pCanvas->DrawFocusRect(Rect);
}
//---------------------------------------------------------------------------
void __fastcall GsListBoxFavoritiesClass::ReLoadFavList()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(TFile::Exists(GlobalVar::Global_custrPathFileFavoriteVers))
	{
		this->Items->BeginUpdate(); //Przenieść do klasy
		this->Items->Assign(GlobalVar::Global_HSListAllFavoritiesVers);
		this->Items->EndUpdate();
	}
}
//---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
// KLASY PRZEZNACZONE DO PRACY ZE SPECJALISTYCZNYMI TŁUMACZENIAMI PISMA SWIETEGO //
///////////////////////////////////////////////////////////////////////////////////
/*
	Rozpoczęcie pracy nad modułem przeglądu tłumaczeń specjalistycznych
	oraz wszystkimi potrzebnymi klasami dla tego modułu, czyli tłumaczeń w
	oryginalnych językach oraz interlinearnych - Oświęcim 11-05-2024
*/
/****************************************************************************
*										 Główna klasa GsObjectItemsSpec						  						*
*****************************************************************************/
__fastcall GsObjectItemsSpec::GsObjectItemsSpec()
/**
	OPIS METOD(FUNKCJI): Konstruktor klasy GsObjectItemsSpec //[11-05-2024]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug("GsObjectItemsSpec::GsObjectItemsSpec()");
//		GsDebugClass::WriteDebug("-------------------------------------------");
//	#endif
	this->OwnsObjects = false;
}
//---------------------------------------------------------------------------
__fastcall GsObjectItemsSpec::~GsObjectItemsSpec()
/**
	OPIS METOD(FUNKCJI): Destruktor klasy GsObjectItemsSpec //[11-05-2024]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->Clear();
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug("-------------------------------------------");
//		GsDebugClass::WriteDebug("GsObjectItemsSpec::~GsObjectItemsSpec()");
//	#endif
}
//---------------------------------------------------------------------------
void __fastcall GsObjectItemsSpec::Clear()
/**
	OPIS METOD(FUNKCJI): Wirtualna klasa wywolywana podczas czyszczenia całej zawartosci //[11-05-2024]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TObjectList::Clear();
}
//---------------------------------------------------------------------------
/****************************************************************************
 *												Klasa GsReadBibleSpecTextClass										*
 ****************************************************************************/
__fastcall GsReadBibleSpecTextClass::GsReadBibleSpecTextClass()
/**
	OPIS METOD(FUNKCJI): //[11-05-2024]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug("GsReadBibleSpecTextClass::GsReadBibleSpecTextClass()");
//		GsDebugClass::WriteDebug("==========================================");
//	#endif
	// Inicjalizacja list wszystkich tłumaczeń specjalistycznych
	this->_pGsObjectItemsSpec = new GsObjectItemsSpec();
	if(!this->_pGsObjectItemsSpec) throw(Exception("Błąd inicjalizacji objektu GsObjectItemsSpec"));

	TList *pList = GsReadBibleTextData::pGsReadBibleTextClass->GetListAllTranslates();
	GsReadBibleTextItem *pGsReadBibleTextItem=nullptr;
	// Dodawanie z listy już wczytanych tłumaczeń pozycji do listy tłumaczeń specjalistycznych.
	// Jako pozycje jest wykorzystana istniejąca klasa GsReadBibleTextItem
	for(int i=0; i<pList->Count; ++i)
	{
		pGsReadBibleTextItem = static_cast<GsReadBibleTextItem *>(pList->Items[i]);

		if(pGsReadBibleTextItem->enTypeTranslate != enTypeTr_Full)
		{
//			#if defined(_DEBUGINFO_)
//				GsDebugClass::WriteDebug(Format("Name: %s", ARRAYOFCONST((pGsReadBibleTextItem->FullPathTranslate))));
//			#endif
			this->_pGsObjectItemsSpec->Add(pGsReadBibleTextItem);
		}
	}
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("this->_pGsObjectItemsSpec->Count: %d", ARRAYOFCONST((this->_pGsObjectItemsSpec->Count))));
//	#endif
}
//---------------------------------------------------------------------------
__fastcall GsReadBibleSpecTextClass::~GsReadBibleSpecTextClass()
/**
	OPIS METOD(FUNKCJI): //[11-05-2024]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->_pGsObjectItemsSpec) {delete this->_pGsObjectItemsSpec; this->_pGsObjectItemsSpec = nullptr;}
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug("==========================================");
//		GsDebugClass::WriteDebug("GsReadBibleSpecTextClass::~GsReadBibleSpecTextClass()");
//	#endif
}
//---------------------------------------------------------------------------
