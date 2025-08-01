﻿#include <vcl.h>
#pragma hdrstop

#include "uSearchTextWindow.h"
#include "MyBibleLibrary\MyBibleLibrary.h"
#include "MyBibleLibrary\GsReadBibleTextdata.h"
#include <System.RegularExpressions.hpp>
#include <System.IOUtils.hpp>
#include "uGlobalVar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSearchTextWindow *SearchTextWindow;
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
	GsDebugClass::WriteDebug("");
#endif
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug("");
#endif
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
catch(Exception &e)
{
	MessageBox(NULL, e.Message.c_str() , TEXT("Błąd"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
}
*/
//---
enum {	// Numery zakładek w ustawieniach wyszukiwania
				enIndexSetInputSearch, enIndexStatisticSearch, enIndexSetupsSearch,
				enIndexResultListHtml=0, enIndexResultListSelect,
				// Numery idyntyfikacyjne kontrolek
				enIdent_CBoxSelectRangeSearch = 0x100,
				enIdent_CBoxStartSelectRange,
				enIdent_CBoxStopSelectRange,
				enIdent_CBoxSelectTranslate,
				// Numery identyfikacyjne kontrolek do ustawiania kolorów
				enIdent_ColorBBackGroundStatisticList = 0x200,
				enIdent_ColorBBockGroundSearchList,
				// Numery indeksów małych ikon
				enImageSearch_ButtonSearchStart=0,	 //0.Rozpoczęcie wyszukiwania
				enImageSearch_ViewResultSearch,		 //1.Przegląd wyników wyszukiwania
				enImageSearch_HelpReg,						 //2.Pomoc w wyszukiwaniu za pomocą wyrażeń regularnych
				enImageSearch_StartSelect,				 //3.Początkowa księga zakresu wyszukiwania
				enImageSearch_StopSelect,					 //4.Końcowa księga zakresu wyszukiwania
				enImageSearch_Translates,					 //5.Wybór tłumaczenia
				enImageSearch_SelectRange,				 //6.Wybór zakresu wyszukiwania
				enImageSearch_Statistic,					 //7.Zakładka statystyki wyszukiwania
				enImageSearch_InputText,					 //8.Zakładka wprowadzania tekstu szukanego
				enImageSearch_ResultListHTML,			 //9.Zakładka wyników wyszukiwania w formie html
				enImageSearch_ResultListSelect,		 //10.Zakładka wyników wyszukiwania z możliwością wyboru
				enImageSearch_Setups,							 //11.Ustawienia dodakowe dla wyszukiwania
				enImageSearch_SaveResult,					 //12.Zapisywanie rezultatów wyszukiwania
				enImageSearch_Count,
				// Numery indeksów wielkich ikon
				enImageLarge_SelectRegHelp=0,      //0.Wybranie pomocy dla wyszukiwania za pomocą wyrażeń regularnych
				enImageLarge_ClearListSearch,      //1.Czyszczenie całej zawartości list wyrażeń do wyszukania
				enImageLarge_DeleteSelectItem,     //2.Usunięcie z list wyrażeń do wyszukania wybranej pozycji
				enImageLarge_ANDSearchList,
				enImageLarge_ORSearchList,
				enImageLarge_Count,
				// Indeksy akcji wyszukiwania z listy
				enIndexSearchActionList_AND=0,     //0.Wszystkie wyrażenia z listy musza wystepować
				enIndexSearchActionList_OOR,       //1.Tylko jedno wyrażenie z list musi istnieć
				// Stałe numerów kolumn dla listy statystyki
				enColumn_NameBook=0, enColumn_CountFind, enColumn_Progres, enColumn_Count,
				// Tagi dla kontrolek
				enTag_PControlSetupsSearch=100, //Zakładki wprowadzanie danych do przeszukiwań i statystyki wyszukiwania
				enTag_PControlSearchViewText, //Zakładki wyników wyszukiwania
				// Tagi dla objektów, klasy TListView
				enTag_LViewResultSearch, //Objekt klasy TListView z listą znalezionych wersetów
				enTag_LViewStatistic,		 //Objekt klasy TListView z listą statystyki występowania szukanego tekstu dla poszczególnych ksiąg
				// Tagi dla objektów, klasy TCheckBox
				enTag_CBoxIsReg,				 //Czy używać w wyszukiwaniu wyrażeń regularnych?
				enTag_CBoxIsSizeText,		 //Czy podczas wyszukiwań rozróżniać wielkość liter?
				enTag_CBoxIsMemorySetupsSearch,	//Czy zapamiętać parametry wuszukiwania?
				// Tagi dla przycisków do sterowania lista wyrażeń do wyszukania
				enTagListSearch_ClearAll=200, // Czyszcenie całej zawartości
				enTagListSearch_DeleteSelect, // Usunięcie zaznaczonej pozycji
				// Numery akcji zastosowania listy wyrażeń
				enTypeAction_ANDWordSearch=0,
				enTypeAction_ORWordSearch
		 };
// Stałe do zaznaczania kolorem szukanego tekstu w wersecie
const UnicodeString Gl_custrStyleF = "<span class=\"styleFound\">",
										Gl_custrStyleEnd = "</span>";
// Stałe potrzebne do wyszukiwania
const int Gl_ciSizeCutString=512, // Ilość znaków skopiowanych z całej zawartosci wersetu(razem z adresem)
					Gl_ciStartVers = 11,		// Początek wersetu
					Gl_ciOffsetTextVers = 10; // Od tej pozycji wersetu zaczyna sie tekst
//Tekst opisu dla skłdni wyrażeń regularnych
const static UnicodeString Gl_ustrInoRegSearch = UnicodeString(". - (kropka)=dowolny znak\n") +
		"^ - dopasuj występujące po operatorze wyrażenie do początku wiersza (początek linii)\n" +
		"$ - dopasuj poprzedzające wyrażenie do końca wiersza (koniec linii)\n" +
		"\\x - znaki specjalne, gdzie	 x to znak specjalny np. \\$ zastąpi znak dolara\n" +
		"[lista] - wyszukuje dowolny znak spośród tych wymienionych na liście, mogą to być, przedziały np. [0-9] lub [a-d]\n" +
		"[^lista] - pasuje do znaku nie podanego na liście\n" +
		"\\< - początek słowa\n" +
		"\\> - koniec słowa\n" +
		"\\w - jest równoważne [0-9a-zA-Z] lub [[:alnum:]] – zastępuje dowolną liczbę lub cyfrę\n" +
		"\\W - oznacza to samo co $[^[[:alnum:]]]\n" +
		"()	 - grupowanie wyrażeń regularnych\n" +
		"|	 - operator LUB\n" +
		"?	 - dokładnie zero lub jeden element wcześniejszy\n" +
		"a|b - dopasuje wyrażenie	 a lub wyrażenie	b\n" +
		"*	 - dopasuj zero lub więcej wyrażeń znaku poprzedzający operator\n" +
		"+	 - jeden lub więcej elementów poprzedzających operator\n" +
		"{n} - poprzedzający element pasuje dokładnie n razy\n\n" +
		"\tGRUPOWANIE - kilka zastosowań grupowań:\n" + //[11-12-2024]
		"\" [0-7]\" – znajdź dowolną liczbę pomiędzy 0 a 7 poprzedzoną spacją.\n" +
		"\"a.[0-9]\" – poszukaj ciąg zaczynający się od \"a\", po którym następuje dowolny znak, a następnie cyfra.\n" +
		"\"[A-Z, ]\" – znajdź wszystkie duże litery, przecinki i spacje\n" +
		"\"(a|b|r)* \" – ciąg, który składa się z samych liter \"a\" lub \"b\" lub \"r\" i kończy się spacją\n",
													ustrTextLogoSearch = "DzAp 17:11\n\"...przyjęli oni Słowo z całą gotowością i codziennie BADALI Pisma, czy tak się rzeczy mają\"";
//Nazwy kolumn dla listy statystyki
const static UnicodeString Gl_ustrNameColumn[] = {"Nazwa księgi", "Ilość wystąpień", "Wskaźnik"},
													 Gl_ustrTypeActionSearchList[] = {"Wszystkie wyrażenia", "Dowolne wyażenie"},
													 Gl_ustrInfosTypesActionSearch[] = {"Podczas wyszukiwanie w poszczególnuch wersetach, muszą być znalezine wszystkie wyrażenia z listy",
																															"Podczas wyszukiwania w poszczególnych wersetach, musi wytąpić dowolne wyrażenie z listy"};
//---------------------------------------------------------------------------
__fastcall TSearchTextWindow::TSearchTextWindow(TComponent* Owner) : TForm(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW: GsReadBibleTextClass *pInToSearchGsReadBibleTextClass - wskaźnik przekazywany z głównej klasy, na główną klasę do pracy tekstem
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//if(Screen->DesktopHeight > 800) this->Height = 860; else this->Height = 600; //Wysokość okna, zależna od wysokości ekranu
	this->WBrowserResultSearch->Navigate(WideString("about:blank").c_bstr());	//Wypełnienie kontrolki pustą stroną, obowiązkowo!!!
	this->WBrowserSelectItemResult->Navigate(WideString("about:blank").c_bstr());	//Wypełnienie kontrolki pustą stroną, obowiązkowo!!!
	this->WebBrowserSelectBookStatistic->Navigate(WideString("about:blank").c_bstr());	//Wypełnienie kontrolki pustą stroną, obowiązkowo!!!
	this->PControlSetupsSearch->ActivePageIndex = enIndexSetInputSearch; //Domyślnie aktywna zakładka, po stworzeniu okna
	this->PControlViewsText->ActivePageIndex = enIndexResultListHtml; //Domyślnie aktywna zakładka, wyników przeglądania
	//Nadawanie numerów identyfikacyjnych kontrolkom
	this->CBoxSelectRangeSearch->Tag = enIdent_CBoxSelectRangeSearch;
	this->CBoxStartSelectRange->Tag = enIdent_CBoxStartSelectRange;
	this->CBoxStopSelectRange->Tag = enIdent_CBoxStopSelectRange;
	this->CBoxSelectTranslates->Tag = enIdent_CBoxSelectTranslate;
	this->PControlViewsText->Tag = enTag_PControlSearchViewText; //Zakładki wyników wyszukiwania
	this->PControlSetupsSearch->Tag = enTag_PControlSetupsSearch; //Zakładki wprowadzanie danych do przeszukiwań i statystyki wyszukiwania
	//Ustawienia kolorów
	this->ColorBoxBackGroundStatisticList->Tag = enIdent_ColorBBackGroundStatisticList;
	this->ColorBoxBackGroundSearchList->Tag = enIdent_ColorBBockGroundSearchList;
		//Objekty klasy TListView
	this->LViewResultSearch->Tag = enTag_LViewResultSearch; //Objekt klasy TListView z listą znalezionych wersetów
	this->LViewStatistic->Tag = enTag_LViewStatistic;			//Objekt klasy TListView z listą statystyki występowania szukanego tekstu dla poszczególnych ksiag
	//Tagi dla objektów, klasy TCheckBox
	this->ChBoxIsRegEx->Tag = enTag_CBoxIsReg;				 //Czy używać w wyszukiwaniu wyrażeń regularnych?
	this->ChBoxSizeTextSearch->Tag = enTag_CBoxIsSizeText;		//Czy podczas wyszukiwań rozróżniać wielkość liter?
	this->ChBoxMemoSetupsSearch->Tag = enTag_CBoxIsMemorySetupsSearch;	//Czy zapamiętać parametry wuszukiwania?
	//Wstępne ustawienia zawartości komponentów
		//Definiowanie komponentów wyboru ksiąg biblijnych
	for(int i=0; i<GlobalVar::Global_NumberBooks; ++i)
		{this->CBoxStartSelectRange->Items->Add(AppCTable_InfoAllBooks[i].FullNameBook);}
	this->CBoxStopSelectRange->Items->Assign(this->CBoxStartSelectRange->Items);
		//Definiowanie komponentu zakresu wyszukiwania
	for(unsigned int i=0; i<ARRAYSIZE(GsReadBibleTextData::GsNameAllRanges); ++i)
		{this->CBoxSelectRangeSearch->Items->Add(GsReadBibleTextData::GsNameAllRanges[i]);}
	this->CBoxSelectRangeSearch->ItemIndex = en_GrSearch_FullAll;
		//Definiowanie listy tłumaczeń do wybrania
	UnicodeString ustrNameTranslate;
	if(GsReadBibleTextData::CountTranslates() > 0)
	{
		for(unsigned char i=0; i<GsReadBibleTextData::CountTranslates(); ++i)
		{
			GsReadBibleTextData::GetInfoNameTranslate(i, ustrNameTranslate);
			this->CBoxSelectTranslates->Items->Add(ustrNameTranslate);
		}
		this->CBoxSelectTranslates->ItemIndex = 0;	//Domyślne pierwsze, dostępne tłumaczenie
	}
	this->CBoxHistorySearchText->Hint = "Pole tekstowe do wprowadzania szukanego tekstu.";
	this->ChBoxIsRegEx->Hint = "Czy wyszukiwanie będzie używało wyrażeń regularnych";
	this->ButtonHelpRegExp->Hint = "Pomoc w wyszukiwaniu za pomocą wyrażeń regularnych.";
	this->CBoxSelectRangeSearch->Hint = Format("Zakres wyszukiwania|Wybór zakresu ksiąg, które będą brane pod uwagę podczas wyszukiwania|%u", ARRAYOFCONST((enImageSearch_SelectRange)));
	this->CBoxStartSelectRange->Hint = Format("Początkowa księga w wyszukiwaniu|Początkowa księga w zakresie wyszukiwania, zdefiniowanym przez użytkownika|%u", ARRAYOFCONST((enImageSearch_StartSelect)));
	this->CBoxStopSelectRange->Hint = Format("Końcowa księga w wyszukiwaniu|Początkowa księga w zakresie wyszukiwania, zdefiniowanym przez użytkownika|%u", ARRAYOFCONST((enImageSearch_StopSelect)));
	this->CBoxSelectTranslates->Hint = Format("Wybór tłumaczenia|Wybór tłumaczenia do przeszukania|%u", ARRAYOFCONST((enImageSearch_Translates)));
	this->ButtonSearchStart->Hint = Format("Rozpoczęcie wyszukiwania|Rozpoczęcie wyszukiwania według ustawionych parametrów|%u", ARRAYOFCONST((this->ButtonSearchStart->ImageIndex)));
	this->ButtonSaveSearch->Hint = Format("Zapis wyników wyszukiwania|Zapisanie ulubionych wyników wyszukiwania|%u", ARRAYOFCONST((this->ButtonSaveSearch->ImageIndex)));
	//Logo wyszukiwania
	if(TFile::Exists(GlobalVar::Global_custrPathSearchLogo))
	{
		TWICImage *pWICImage = new TWICImage();
		if(!pWICImage) throw(Exception("Błąd inicjalizacji objektu TWICImage"));
		pWICImage->LoadFromFile(GlobalVar::Global_custrPathSearchLogo);
		this->ImageLogoSearch->Picture->Assign(pWICImage);
		delete pWICImage; pWICImage = nullptr;
		this->STextLogoSearch->Caption = ustrTextLogoSearch;
	}
	// Zastosowanie stylu do panelów
	this->PanelListButtons->Color = TStyleManager::ActiveStyle->GetSystemColor(clBtnFace);
	this->PanelListWords->Color = TStyleManager::ActiveStyle->GetSystemColor(clBtnFace);
	this->PanelInfosSelectActionSearch->Color = TStyleManager::ActiveStyle->GetSystemColor(clBtnFace);
  // Tagi dla przycisków, dla listy wyrażeń szukanych
	this->ButtClearAllListSearch->Tag = enTagListSearch_ClearAll;
	this->DeleteSelectPos->Tag = enTagListSearch_DeleteSelect;
	// Akcje zastosowania dla listy szukanych wyrażeń
		// Wysokość objektu klasy TButtonGroup, this->STW_ButtGrSelectActionList
	this->ButtGrSelectActionList->Margins->Bottom =
		LBoxSearchTexts->Height - (2 * this->ButtGrSelectActionList->ButtonHeight) + this->ButtGrSelectActionList->Margins->Top;
	TGrpButtonItem *pGrpButtonItem=nullptr;
	for(int i=0; i<ARRAYSIZE(Gl_ustrTypeActionSearchList); ++i)
	{
		pGrpButtonItem = this->ButtGrSelectActionList->Items->Add();
		pGrpButtonItem->Caption = Gl_ustrTypeActionSearchList[i];
    pGrpButtonItem->ImageIndex = enImageLarge_ANDSearchList + i;
	}
	// Domyślna akcja zastosowania do listy szukanych wyrażen
	this->ButtGrSelectActionList->ItemIndex = enIndexSearchActionList_AND;
	this->LabelInfosSelectActionSearch->Caption = Gl_ustrInfosTypesActionSearch[this->ButtGrSelectActionList->ItemIndex];
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	const unsigned char cucLimitGroupBooks[] = {39, 66, 73};
	enum {enLimit_OldTestament, enLimit_NewTestament, enLimit_Apocryfics=73};
	//----- Ustawienia objektu, klasy TListView dla statystyki
	TListColumn *NewColumn=nullptr;
	TImageList *pImgList = GsReadBibleTextData::GetImageList();
	if(!pImgList) throw(Exception("Błąd wyłuskania objektu TImageList"));
	this->LViewStatistic->SmallImages = pImgList;
	//this->STW_LViewStatistic->GroupHeaderImages = pImgList;
	for(int i=0; i<GsReadBibleTextData::GsNumberGroups; ++i)
	{
		TListGroup *NewGroup = this->LViewStatistic->Groups->Add();
		NewGroup->State = TListGroupStateSet() << lgsNormal << lgsCollapsible;
		NewGroup->Header = GsReadBibleTextData::GsNamesTableNameGroupBook[i];
		NewGroup->HeaderAlign = taCenter;
	}
	// Dodawanie kolumn do objektu, klasy TListView, statystyki
	for(unsigned int iColumns=0; iColumns<enColumn_Count; ++iColumns)
	{
		NewColumn = this->LViewStatistic->Columns->Add();
		NewColumn->Caption = Gl_ustrNameColumn[iColumns];
		NewColumn->AutoSize = true;
		switch(iColumns)
		{
			case enColumn_NameBook:
			{
				NewColumn->AutoSize = false;
				NewColumn->Width = 200;
			}
			break;
			//---
			case enColumn_CountFind:
			{
				NewColumn->AutoSize = false;
				NewColumn->Width = 98;
			}
			break;
		}
		NewColumn->ImageIndex = enImageIndex_Root;
	}
	this->LViewStatistic->Items->BeginUpdate();
	for(unsigned char i=0; i<GlobalVar::Global_NumberBooks; ++i)
	{
		TListItem *NewItem = this->LViewStatistic->Items->Add();
		NewItem->Caption = AppCTable_InfoAllBooks[i].FullNameBook;
		if(i<cucLimitGroupBooks[enLimit_OldTestament]) NewItem->GroupID = 0;
		else if(i>=cucLimitGroupBooks[enLimit_OldTestament] && i<cucLimitGroupBooks[enLimit_NewTestament]) NewItem->GroupID = 1;
		else if(i>=cucLimitGroupBooks[enLimit_NewTestament]) NewItem->GroupID = 2;
		//Zaalokowanie prywatnych danych w każdej pozycji, która reprezentuje kolejną księgę biblijną.
		//W tych danych będą przechowywane ilości wystąpień szukanego słowa w danej księdze
		PStatisticFindView MyDataStatistic = new StatisticFindView();
		if(!MyDataStatistic) throw(Exception("Błąd inicjalizacji objektu PStatisticFindView"));
		MyDataStatistic->uiCountFind = 0;
		NewItem->Data = MyDataStatistic;
	}
	this->LViewStatistic->Items->EndUpdate();
	// Lista zawierające wszystkie znalezione wersety
	this->_pHSListSearchResult = new THashedStringList();
	if(!this->_pHSListSearchResult) throw(Exception("Błąd tworzenia tymczasowego objektu THashedStringList"));
	// Lista dotyczczasowych tekstów wyszukiwanych
		//Odczyt pliku histori wyszukiwania
	if(TFile::Exists(GlobalVar::Global_custrPathHistorySearch))
		{this->CBoxHistorySearchText->Items->LoadFromFile(GlobalVar::Global_custrPathHistorySearch, TEncoding::UTF8);}
	// Odczyt i ustawienie objektów klasy TColorBox według zawartości pliku konfiguracyjnego
		// Wygląd
	this->ColorBoxBackGroundSearchList->Selected = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSetupsSection_Main, GlobalVar::GlobalIni_ColorsSetupsBackGroundAllListSearch, clMoneyGreen);
	this->ColorBoxBackGroundStatisticList->Selected = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSetupsSection_Main, GlobalVar::GlobalIni_ColorsSetupBackGroundSelectBookSearch, clMoneyGreen);
	this->ColorBoxBackGroundSelectVers->Selected = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSetupsSection_Main, GlobalVar::GlobalIni_ColorsSetupBackGroundSelectVers, clMoneyGreen);
		// Parametry wyszukiwania
	this->ChBoxMemoSetupsSearch->Checked = GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_IsMemorySetupsSearch, false);
	if(this->ChBoxMemoSetupsSearch->Checked)
	// Jeśli zapamiętywanie parametrów jest włączone
	{
		this->CBoxSelectTranslates->ItemIndex = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_Translate, 0);
		this->CBoxHistorySearchText->Text = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_TextSearch, "");
		this->ButtonSearchStart->Enabled = !this->CBoxHistorySearchText->Text.IsEmpty(); //Aktywacja przycisku wyszukiwania zależna od istnienia tekstu szukanego
		//this->STW_ButtonSaveSearch->Enabled = this->STW_ButtonSearchStart->Enabled;
		this->CBoxSelectRangeSearch->ItemIndex = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_SetupRangeBooks, en_GrSearch_FullAll);
		if(this->CBoxSelectRangeSearch->ItemIndex > en_GrSearch_Apocr)
		// Jeśli zakres jest ustawiony na własny, lub pojedyńczą księge
		{
			this->CBoxStartSelectRange->ItemIndex = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_StartUserRange, 0);
			this->CBoxStopSelectRange->ItemIndex = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_StopUserRange, this->CBoxStopSelectRange->Items->Count-1);
		}
		this->ChBoxSizeTextSearch->Checked = GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_IsSizeTextSearch, false);
		this->ChBoxIsRegEx->Checked = GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_IsRegSearch, false);

		this->ChBoxOnlyWord->Checked = GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_IsSearchSameWord, false);
		this->ChBoxAllSearchTexts->Checked = GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_IsSearchListWord, false);
	}
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::FormDestroy(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->_pHSListSearchResult) {delete this->_pHSListSearchResult; this->_pHSListSearchResult = nullptr;}

	this->CBoxHistorySearchText->Items->SaveToFile(GlobalVar::Global_custrPathHistorySearch, TEncoding::UTF8);
	//Zwalnianie prywatnych danych związanych z objektem TListitem, dla poszczególnych ksiąg
	for(int i=0; i<GlobalVar::Global_NumberBooks; ++i)
	{
		TListItem *MyItem = this->LViewStatistic->Items->Item[i];
		if(MyItem)
		{
			if(MyItem->Data)
			{
				//Wyłuskanie wskaźnika na prywatny objekt PStatisticFindView, z każdej pozycji klasy this->STW_LViewStatistic
				PStatisticFindView MyDataStatistic = static_cast<PStatisticFindView>(MyItem->Data);
				if(MyDataStatistic)
				{
					delete MyDataStatistic; MyDataStatistic = nullptr;
				}
			}
		}
	}

	//Zapis ustawień kolorów do zawartości pliku konfiguracyjnego
		//Wygląd
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ColorsSetupsSection_Main, GlobalVar::GlobalIni_ColorsSetupsBackGroundAllListSearch, this->ColorBoxBackGroundSearchList->Selected);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ColorsSetupsSection_Main, GlobalVar::GlobalIni_ColorsSetupBackGroundSelectBookSearch, this->ColorBoxBackGroundStatisticList->Selected);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ColorsSetupsSection_Main, GlobalVar::GlobalIni_ColorsSetupBackGroundSelectVers, this->ColorBoxBackGroundSelectVers->Selected);
		//Parametry wyszukiwania
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_IsMemorySetupsSearch, this->ChBoxMemoSetupsSearch->Checked);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_Translate, this->CBoxSelectTranslates->ItemIndex);
	GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_TextSearch, this->CBoxHistorySearchText->Text);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_SetupRangeBooks, this->CBoxSelectRangeSearch->ItemIndex);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_StartUserRange, this->CBoxStartSelectRange->ItemIndex);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_StopUserRange, this->CBoxStopSelectRange->ItemIndex);
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_IsSizeTextSearch, this->ChBoxSizeTextSearch->Checked);
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_IsRegSearch, this->ChBoxIsRegEx->Checked);


	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_IsSearchSameWord, this->ChBoxOnlyWord->Checked);
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_IsSearchListWord, this->ChBoxAllSearchTexts->Checked);
	//Zrzucenie zawartości objektu, klasy TMemIni, do pliku
	GlobalVar::Global_ConfigFile->UpdateFile();
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::FormClose(TObject *Sender, TCloseAction &Action)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::ButtonSearchStartClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Uaktywnianie właśnego zakresu wyszukiwania
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TButton *pButtSearch = dynamic_cast<TButton *>(Sender);
	if(!pButtSearch) return;
	//Przełączenie na pierwszą zakładkę
	this->PControlViewsText->TabIndex = enIndexResultListHtml;
	//---
	THashedStringList *pBookListText=nullptr;
	int iIndexTable;//=0;	 //Numer księgi liczony od 0.
	UnicodeString ustrFullVers, ustrTextSearch;//ustrReplaced, ;
	//---
	signed char scTempStart=0, scTempStop=0;
	PStatisticFindView pMyDataStatistic=nullptr;
	//---
	//if(this->STW_CBoxHistorySearchText->Text.IsEmpty()) return; //Jeśli pole tekstu do wyszukanie jest puste, opuść metodę
	//---- Wyłuskanie tłumaczenia
	GsReadBibleTextItem *pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(this->CBoxSelectTranslates->ItemIndex);
	if(!pGsReadBibleTextItem || (pGsReadBibleTextItem->enTypeTranslate != enTypeTr_Full)) return; //Wyjście, gdy nie udało sie wyłuskać tłumaczenia
	//---
	if(this->CBoxSelectRangeSearch->ItemIndex < en_UserRange && this->CBoxSelectRangeSearch->ItemIndex > -1)
	//Jeśli wybranym zakresem, jest zakres zdefiniowany, nie własny
	{
		scTempStart = GsReadBibleTextData::GsPairsGroupBible[CBoxSelectRangeSearch->ItemIndex].ucStartRange;
		scTempStop = GsReadBibleTextData::GsPairsGroupBible[CBoxSelectRangeSearch->ItemIndex].ucStopRange;
	}
	else if(this->CBoxSelectRangeSearch->ItemIndex >= en_UserRange)
	//Jeśli wybranym zakresem, jest zakres własny
	{
		if(this->CBoxStartSelectRange->ItemIndex > -1 &&	this->CBoxStopSelectRange->ItemIndex > -1)
		{
			scTempStart = this->CBoxStartSelectRange->ItemIndex;
			scTempStop = this->CBoxStopSelectRange->ItemIndex;
		}
	}
	else return;
	//---
	this->_pHSListSearchResult->Clear();
	for(signed char scIndex=scTempStart; scIndex<=scTempStop; ++scIndex)
	{
		// Wyłuskanie księgi z wersetami z konkretnego tłumaczenia
		pBookListText = GsReadBibleTextData::GetSelectBoksInTranslate(pGsReadBibleTextItem, scIndex);
		TListItem *MyItem = this->LViewStatistic->Items->Item[scIndex];

		//Wyłuskanie danych dla pozycji, która reprezentuje księgę. W tej danej będzie przechowywana ilość wystąpień szukanego słowa dla każdej księgi
		if(MyItem)
		{
			if(MyItem->Data)
			{
				pMyDataStatistic = static_cast<PStatisticFindView>(MyItem->Data);
				pMyDataStatistic->uiCountFind=0; //Wyczyszczenie pozycji
			}
		}
		//---
		if(pBookListText) // Lista wersetów z konkretnej księgi i tłumaczenia
		{
			for(int i=0; i<pBookListText->Count; ++i) // Iteracja po kolejnych wersetach
			{
				ustrFullVers = pBookListText->Strings[i];
				ustrTextSearch = this->CBoxHistorySearchText->Text;
				iIndexTable = ustrFullVers.SubString(1, 3).ToInt() - 1; //Numer księgi liczony od 0.
				//--- Wyszukiwanie za pomocą wyrażeń regularnych
				if(this->ChBoxIsRegEx->Checked && !ustrTextSearch.IsEmpty()) //Wyszukiwanie za pomocą wyrażeń regularnych
				{
					this->_IsMatchRegSearch(ustrFullVers, ustrTextSearch, pBookListText, i, pMyDataStatistic);
				}
				//--- Wyszukiwanie tradycyjne, jeśli wyłączone wyszukiwanie za pomocą wyrażeń regularnych
        //    oraz wyłączona lista wszystkich szukanych wyrażeń
				else if(!this->ChBoxIsRegEx->Checked && !this->ChBoxAllSearchTexts->Checked && !ustrTextSearch.IsEmpty()) // Wyszukiwanie tradycyjne
				{
					bool bExit = this->_IsMatchNormalSearch(ustrFullVers, ustrTextSearch, pBookListText, i, pMyDataStatistic);
          if(!bExit) continue;
				}
				//--- Wyszukiwanie wszystkich, jednocześnie występujących wyrażeń z listy
				else if(!this->ChBoxIsRegEx->Checked && this->ChBoxAllSearchTexts->Checked)
				{
					this->_IsMatchSearchListTexts(ustrFullVers, pBookListText, i, pMyDataStatistic);
				}//else(this->STW_ChBoxIsRegEx->Checked)
			} //for(int i=0; i<pBookListText->Count; ++i)
		} //if(pBookListText)
	} //for(...)

	this->LViewStatistic->Repaint(); //Odświerzenie listy statystyki 04-05-2021
  // Wyswietlenie listy wyszukanych wersetów, z możliwoscia zaznaczenie w wersecie szukanego wyrażenia
	this->_DisplayListTextHTML(this->WBrowserResultSearch, this->_pHSListSearchResult, enTypeDisplay_ResultsearchAll); //Wszystkie znalezione teksty
	this->LViewResultSearch->Items->BeginUpdate();
	this->LViewResultSearch->Items->Count = this->_pHSListSearchResult->Count;
	if(this->_pHSListSearchResult->Count > 0)
	{
		this->LViewResultSearch->ItemIndex = 0; //Po modyfikacji listy, jeśli ma elementy, wybieralnej wyników, pierwsza pozycja aktywna
	}
	this->LViewResultSearch->Items->EndUpdate();
	this->WBrowserResultSearch->SetFocus();
	this->StBarInfos->SimpleText = Format("Znaleziono %u pozycji", ARRAYOFCONST((this->_pHSListSearchResult->Count)));
	this->ButtonSaveSearch->Enabled = (this->_pHSListSearchResult->Count > 0);	//[10-10-2023]
	//Dodawanie do objekstu, klasy TComboBox sów wyszukiwanych 15-04-2021
	bool bIsDuplicate=false; //Zmienna oznaczająca że jest(true), lub nie (false) duplicat w słowie szukanym
	const int ciMaxHistorySearchText=24; //Maksymalna liczba zapamiętanej histori szukanego tekstu.
																			 //Gdy zostanie ona przekroczona, zostanie usunięte najstarsze słowo, by dodać najnowsze

	for(int i=0; i<this->CBoxHistorySearchText->Items->Count; ++i)
	{
		if(CBoxHistorySearchText->Text.LowerCase() == this->CBoxHistorySearchText->Items->Strings[i].LowerCase())
		{
			bIsDuplicate = true; break;
		}
	}

	if(!bIsDuplicate)
	{
		if(ciMaxHistorySearchText <= this->CBoxHistorySearchText->Items->Count) this->CBoxHistorySearchText->Items->Delete(0);
		this->CBoxHistorySearchText->Items->Add(CBoxHistorySearchText->Text);	 //Lista dotyczczasowych tekstów wyszukiwanych
	}
	//Wyczyszczenie objektu klasy TWebBrowser, po wyszukaniu nowego słowa
	this->WebBrowserSelectBookStatistic->Navigate(WideString("about:blank").c_bstr());
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::_IsMatchRegSearch(const UnicodeString &custrFullVers, const UnicodeString &custrTextSearch,
	THashedStringList *_pBookListText, const int ciIndexVers, PStatisticFindView _MyDataStatistic)
/**
	OPIS METOD(FUNKCJI): Metoda wyszukiwania za pomocą wyrażeń regularnych // 13-07-2025
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//--- Parametry wyszukiwania za pomocą wyrażeń regularnych
	TRegExOptions regOptions;
	UnicodeString ustrFullVersReplaced=custrFullVers, ustrReplaced;

	if(this->ChBoxSizeTextSearch->Checked) //Uwzględniana wielkość liter przy używaniu wyrażeń regularnych
		{regOptions = TRegExOptions() << roSingleLine;}
	else {regOptions = TRegExOptions() << roSingleLine << roIgnoreCase;}

	try
	{
		try
		{
			TMatch MyMatch = System::Regularexpressions::TRegEx::Match(custrFullVers, custrTextSearch, regOptions);
			if(MyMatch.Success)
			//if(System::Regularexpressions::TRegEx::IsMatch(custrFullVers, custrTextSearch, regOptions))
			{
				do
				{
					ustrReplaced = Format("%s%s%s", ARRAYOFCONST((Gl_custrStyleF, MyMatch.Value, Gl_custrStyleEnd )));
					ustrFullVersReplaced = StringReplace(ustrFullVersReplaced, MyMatch.Value,
						ustrReplaced, TReplaceFlags() << rfReplaceAll << rfIgnoreCase);
					// Usunięcie podwójnych znaczników zaznaczenia
					ustrFullVersReplaced = StringReplace(ustrFullVersReplaced, Gl_custrStyleF+Gl_custrStyleF,
						Gl_custrStyleF, TReplaceFlags() << rfReplaceAll << rfIgnoreCase);
					ustrFullVersReplaced = StringReplace(ustrFullVersReplaced, Gl_custrStyleEnd+Gl_custrStyleEnd,
						Gl_custrStyleEnd, TReplaceFlags() << rfReplaceAll << rfIgnoreCase);

					MyMatch = MyMatch.NextMatch();
				}while(MyMatch.Success);

				// Dodanie wersetu do listy znalezionych
				this->_pHSListSearchResult->AddObject(ustrFullVersReplaced.SubString(Gl_ciOffsetTextVers, Gl_ciSizeCutString), _pBookListText->Objects[ciIndexVers]);
				//Wypełnienie odpowiedniej pozycji tablicy statystyki wyszukiwania. iIndexTable to numer księgi liczony od 0.
				++_MyDataStatistic->uiCountFind;
			}
		}
		catch(Exception &e) //[11-12-2024]
		{
			MessageBox(NULL, e.Message.c_str() , TEXT("Błąd wyszukiwania za pomocą wyrażeń regularnych.\nPrawdopodobnie zastosowano niewłaściwy wzorzec"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
			return; // 13-07-2025
		}
	}
	__finally
	{

	}
}
//---------------------------------------------------------------------------
bool __fastcall TSearchTextWindow::_IsMatchNormalSearch(const UnicodeString &custrFullVers, const UnicodeString &custrTextSearch,
	THashedStringList *_pBookListText, const int ciIndexVers, PStatisticFindView _pMyDataStatistic)
/**
	OPIS METOD(FUNKCJI): Metoda wyszukiwania tradycyjnego // 13-07-2025
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	UnicodeString ustrSearchString, ustrReplaced, ustrAddingFullVers;
	int _iPositionSearch=0;
	bool bIsSameWord=false;

	if(this->ChBoxSizeTextSearch->Checked) //Uwzględniana wielkość liter
	{
		_iPositionSearch = custrFullVers.Pos(custrTextSearch);
		//_iPositionSearch = System::Pos(custrTextSearch, custrFullVers);
//		#if defined(_DEBUGINFO_)
//			if(_iPositionSearch > 0)
//				GsDebugClass::WriteDebug(Format("_iPositionSearch: %d", ARRAYOFCONST((_iPositionSearch))));
//		#endif
	}
	else
	{
		ustrSearchString = System::Sysutils::AnsiLowerCase(custrTextSearch);
		_iPositionSearch = System::Sysutils::AnsiLowerCase(custrFullVers).Pos(ustrSearchString);
	}

	if(_iPositionSearch > 0)
	{
		// Metoda sprawdza czy to jest same słowo
		bIsSameWord = this->_IsSameWord(custrFullVers, custrTextSearch, _iPositionSearch);
//    #if defined(_DEBUGINFO_)
//			GsDebugClass::WriteDebug(Format("bIsSameWord: %s", ARRAYOFCONST((BoolToStr(bIsSameWord, true) ))));
//		#endif

		if(this->ChBoxOnlyWord->Checked)
		// Wyszukiwanie tylko całych słów // 11-07-2025
		{
			if(!bIsSameWord) return false;
		}

		//Wstawianie znacznika koloru, podkładu. MUSI być modyfikowana kopia //[19-06-2024]
		ustrReplaced = Format("%s%s%s", ARRAYOFCONST((Gl_custrStyleF, custrTextSearch, Gl_custrStyleEnd )));
		ustrAddingFullVers = StringReplace(custrFullVers, custrTextSearch, ustrReplaced, TReplaceFlags() << rfReplaceAll << rfIgnoreCase);

		// Dodanie wersetu do listy znalezionych
		this->_pHSListSearchResult->AddObject(ustrAddingFullVers.SubString(Gl_ciOffsetTextVers, Gl_ciSizeCutString), _pBookListText->Objects[ciIndexVers]);
		//Wypełnienie odpowiedniej pozycji tablicy statystyki wyszukiwania. iIndexTable to numer księgi liczony od 0.
		++_pMyDataStatistic->uiCountFind;
	} //if(iPositionSearch > 0)
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSearchTextWindow::_IsSameWord(const UnicodeString &custrFullVers, const UnicodeString &custrSearchString,
	const int ciPositionSearch)
/**
	OPIS METOD(FUNKCJI): Metoda sprawdza czy to jest same słowo
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(ciPositionSearch > (custrFullVers.Length() - custrSearchString.Length())) return true; // [27-07-2025]
	bool bIsSameWord = // Wyszukiwanie tylko całych słów
		(
			// Początek słowa
			(
				(ciPositionSearch == Gl_ciStartVers) || // Początek tekstu
				(custrFullVers[ciPositionSearch - 1] == 32) // Spacja przed słowem
			) &&
			// Koniec słowa
			(
				(custrFullVers[ciPositionSearch + custrSearchString.Length()] == 32) || // Spacja po słowie
				(ciPositionSearch == (custrFullVers.Length() - custrSearchString.Length()))  || // Koniec tekstu
        // Znaki akceptowalna po słowie
				(custrFullVers[ciPositionSearch + custrSearchString.Length()] == ',') ||
				(custrFullVers[ciPositionSearch + custrSearchString.Length()] == '.') ||
				(custrFullVers[ciPositionSearch + custrSearchString.Length()] == ';') ||
        (custrFullVers[ciPositionSearch + custrSearchString.Length()] == ':') ||
				(custrFullVers[ciPositionSearch + custrSearchString.Length()] == '?') ||
				(custrFullVers[ciPositionSearch + custrSearchString.Length()] == '!')
			)
    );

	return bIsSameWord;
}
//---------------------------------------------------------------------------
bool __fastcall TSearchTextWindow::_IsMatchSearchListTexts(const UnicodeString &custrFullVers, THashedStringList *_pBookListText,
	const int ciIndexVers, PStatisticFindView _pMyDataStatistic)
/**
	OPIS METOD(FUNKCJI): Metoda wyszukiwania wszystkich wyrażeń z listy
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	int _iPositionSearch=0;
	UnicodeString ustrFullVersReplaced=custrFullVers, ustrReplaced;
	bool bIsSameWord=false;

	if(this->LBoxSearchTexts->Count == 0) return false;
  //---
	if(this->ButtGrSelectActionList->ItemIndex == enTypeAction_ANDWordSearch)
	// Wszystkie wyrażenia z listy muszą być znalezione
	{
		for(int i=0; i<this->LBoxSearchTexts->Count; ++i)
		{
			_iPositionSearch = custrFullVers.Pos(this->LBoxSearchTexts->Items->Strings[i]);
			if(_iPositionSearch == 0) return false;

			if(this->ChBoxOnlyWord->Checked)
			// Wyszukiwanie tylko całych słów
			{
				bIsSameWord = this->_IsSameWord(custrFullVers, this->LBoxSearchTexts->Items->Strings[i],_iPositionSearch);
				if(!bIsSameWord) return false;
			} // Nie dokończone // 20-07-2025

			ustrReplaced = Format("%s%s%s", ARRAYOFCONST((Gl_custrStyleF, this->LBoxSearchTexts->Items->Strings[i], Gl_custrStyleEnd )));
			ustrFullVersReplaced = StringReplace(ustrFullVersReplaced, this->LBoxSearchTexts->Items->Strings[i],
				ustrReplaced, TReplaceFlags() << rfReplaceAll << rfIgnoreCase);
		}

	}
	else if(this->ButtGrSelectActionList->ItemIndex == enTypeAction_ORWordSearch)
	// Które kolwiek wyrażenie z listy ma byc znalezione
	{
		bool bIsSearch=false;
    for(int i=0; i<this->LBoxSearchTexts->Count; ++i)
		{
			_iPositionSearch = custrFullVers.Pos(this->LBoxSearchTexts->Items->Strings[i]);
			if(_iPositionSearch > 0) bIsSearch = true;

      ustrReplaced = Format("%s%s%s", ARRAYOFCONST((Gl_custrStyleF, this->LBoxSearchTexts->Items->Strings[i], Gl_custrStyleEnd )));
			ustrFullVersReplaced = StringReplace(ustrFullVersReplaced, this->LBoxSearchTexts->Items->Strings[i],
				ustrReplaced, TReplaceFlags() << rfReplaceAll << rfIgnoreCase);
		}
		if(!bIsSearch) return false;
	}
	// Dodanie wersetu do listy znalezionych
	this->_pHSListSearchResult->AddObject(ustrFullVersReplaced.SubString(Gl_ciOffsetTextVers, Gl_ciSizeCutString), _pBookListText->Objects[ciIndexVers]);
  //Wypełnienie odpowiedniej pozycji tablicy statystyki wyszukiwania. iIndexTable to numer księgi liczony od 0.
	++_pMyDataStatistic->uiCountFind;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::CBoxCloseUp(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TComboBox *pCBox = dynamic_cast<TComboBox *>(Sender);
	if(!pCBox) return;
	//Wyczyszczenie objekty klasy TWebBrowser, do przeglądania znalezionych wersetów w wybranek księdze
	this->WebBrowserSelectBookStatistic->Navigate(WideString("about:blank").c_bstr());
	for(unsigned char i=0; i<GlobalVar::Global_NumberBooks; ++i)
	{
		TListItem *MyItem = this->LViewStatistic->Items->Item[i];
		if(MyItem)
		{
			if(MyItem->Data)
			{
				//Wyłuskanie wskaźnika na prywatny objekt PStatisticFindView, z każdej pozycji klasy this->STW_LViewStatistic
				PStatisticFindView MyDataStatistic = static_cast<PStatisticFindView>(MyItem->Data);
				if(MyDataStatistic)
				{
					MyDataStatistic->uiCountFind = 0;
				}
			}
		}
	}
	this->LViewStatistic->Repaint();
	//---
	switch(pCBox->Tag)
	{
		case enIdent_CBoxSelectRangeSearch:
			//--- Uaktywnienie wyborów początku i końca zakresu wyszukiwania, zależnie od wyboru właściwej pozycji z listy rozwijalnej
			{
				this->CBoxStartSelectRange->Enabled = (pCBox->ItemIndex == en_UserRange) || (pCBox->ItemIndex == en_OneBook);
				this->CBoxStopSelectRange->Enabled = (pCBox->ItemIndex == en_UserRange);
			}
		break;
		//
		case enIdent_CBoxSelectTranslate:
			//--- Wyłuskanie tłumaczenia
			{
				//Wyłuskanie typu tłumaczenia
				GsReadBibleTextItem *pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(pCBox->ItemIndex);
				if(!pGsReadBibleTextItem) return;
				//this->STW_CBoxHistorySearchText->Enabled = (pGsReadBibleTextItem->enTypeTranslate == enTypeTr_Full && !this->STW_CBoxHistorySearchText->Text.IsEmpty());
			}
		break;
		//
		case enIdent_CBoxStartSelectRange:
		//--- Początkowy zakres wyszukiwanie
			if(pCBox->ItemIndex > this->CBoxStopSelectRange->ItemIndex) this->CBoxStopSelectRange->ItemIndex = pCBox->ItemIndex;
		break;
		//
		case enIdent_CBoxStopSelectRange:
			if(pCBox->ItemIndex < this->CBoxStartSelectRange->ItemIndex) this->CBoxStartSelectRange->ItemIndex = pCBox->ItemIndex;
		//--- Końcowy zakres wyszukiwania
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::LEditSearchTextChange(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Metoda wywoływana przy zmianie zawartości pola tekstowego
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TLabeledEdit *pLEdit = dynamic_cast<TLabeledEdit *>(Sender);
	if(!pLEdit) return;
	//--- Kontrola wyszukiwanie tylko w wypadku nie pustego pola tekstowego
	GsReadBibleTextItem *pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(this->CBoxSelectTranslates->ItemIndex);
	if(!pGsReadBibleTextItem) return;
	this->ButtonSearchStart->Enabled = (pGsReadBibleTextItem->enTypeTranslate == enTypeTr_Full && !pLEdit->Text.IsEmpty());
	//this->STW_ButtonSaveSearch->Enabled = this->STW_ButtonSearchStart->Enabled;
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::ChBoxIsRegExClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Aktywacja wyszukiwania za pomocą wyrażeń regularnych
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCheckBox *pChBox = dynamic_cast<TCheckBox *>(Sender);
	if(!pChBox) return;
	//---
	this->CBoxHistorySearchText->Text = "";
	this->ButtonHelpRegExp->Enabled = pChBox->Checked;
	// Zmiana stanu wyszukiwań, które zastępuje wyszukiwanie za pomocą wyrażeń regularnych // 13-07-2025
	this->ChBoxSizeTextSearch->Enabled = !pChBox->Checked;
	this->ChBoxOnlyWord->Enabled = !pChBox->Checked;
	this->GrBoxListGroupSearchedTexts->Enabled = !pChBox->Checked;

	this->ChBoxAllSearchTexts->Checked = false;
	this->ChBoxAllSearchTexts->Enabled = !pChBox->Checked;

	this->ButtClearAllListSearch->Enabled = !pChBox->Checked && (this->LBoxSearchTexts->Count > 0);
	this->DeleteSelectPos->Enabled = !pChBox->Checked && (this->LBoxSearchTexts->Count > 0);
	this->LBoxSearchTexts->Enabled = !pChBox->Checked;

  //Wyczyszczenie objektu klasy TWebBrowser, po wyszukaniu nowego słowa
	this->WBrowserResultSearch->Navigate(WideString("about:blank").c_bstr());
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::ChBoxAllSearchTextsClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Szukanie zwszystkich wyrażeń z listy
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCheckBox *pChBox = dynamic_cast<TCheckBox *>(Sender);
	if(!pChBox) return;
	//---
	this->ButtAddListTextSearch->Enabled = pChBox->Checked;
	this->LBoxSearchTexts->Enabled = pChBox->Checked;
	this->ChBoxIsRegEx->Enabled = !pChBox->Checked;
	this->ButtGrSelectActionList->Enabled = pChBox->Checked;

  //Wyczyszczenie objektu klasy TWebBrowser, po wyszukaniu nowego słowa
	this->WBrowserResultSearch->Navigate(WideString("about:blank").c_bstr());
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//MessageBox(NULL, L"FormKeyUp()", L"Informacja aplikacji", MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
	if(Key != VK_RETURN) return;
	this->ButtonSearchStartClick(this->ButtonSearchStart);
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::LViewResultSearchData(TObject *Sender,
					TListItem *Item)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListView *pLView = dynamic_cast<TListView *>(Sender);
	if(!pLView) return;
	//-----
	if((Item->Index<this->_iStart_index) || (Item->Index>this->_iEnd_index)) return;
	MyObjectVers *pMyObjectVers = static_cast<MyObjectVers *>(this->_pHSListSearchResult->Objects[Item->Index]);
	if(pMyObjectVers)
	{
		Item->Caption = pMyObjectVers->BookChaptVers;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::LViewResultSearchDataHint(TObject *Sender,
					int StartIndex, int EndIndex)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListView *pLView = dynamic_cast<TListView *>(Sender);
	if(!pLView) return;
	//-----
	this->_iStart_index = StartIndex;
	this->_iEnd_index = EndIndex;
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::LViewResultSearchGetImageIndex(TObject *Sender,
					TListItem *Item)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListView *pLView = dynamic_cast<TListView *>(Sender);
	if(!pLView) return;
	//-----
	Item->ImageIndex = enImageSearch_ViewResultSearch;
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::LViewAllSelectItem(TObject *Sender,
					TListItem *Item, bool Selected)
/**
	OPIS METOD(FUNKCJI): W liście wyszukanych wersetów kliknięto na pozycje, lub liście statystyki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListView *pLView = dynamic_cast<TListView *>(Sender);
	if(!pLView) return;
	//---
	if(!Item || !Selected) return;
	//---
	switch(pLView->Tag)
	{
		case enTag_LViewResultSearch: //Objekt klasy TListView z listą znalezionych wersetów
		{
			// Wyswietlenie listy wyszukanych wersetów, z możliwoscia zaznaczenie w wersecie szukanego wyrażenia
			this->_DisplayListTextHTML(this->WBrowserSelectItemResult, this->_pHSListSearchResult, enTypeDisplay_ResultSelectVers, Item->Index);
		}
		break;
		//---
		case enTag_LViewStatistic:	 //Objekt klasy TListView z listą statystyki występowania szukanego tekstu dla poszczególnych ksiąg
		{
			THashedStringList *_tempHSLst=nullptr;
			try
			{
				try
				{
					_tempHSLst = new THashedStringList();
					if(!_tempHSLst) throw(Exception("Błąd tworzenia tymczasowego objektu THashedStringList"));
					//Skopiowanie wersetów dla wybranej księgi, z lsty wszystkich znalezionych werstów
					for(int i=0; i<this->_pHSListSearchResult->Count; ++i)
					{
						//Wyłuskanie wskaźnika na objekt, przyporządkowany pozycji w objekcie klasy THashedStringList
						MyObjectVers *pMyObjectVers = static_cast<MyObjectVers *>(this->_pHSListSearchResult->Objects[i]);
						if(pMyObjectVers)
						{
							if(pMyObjectVers->ucBook == pLView->ItemIndex)
							//Porównanie numeru wybranej księgi z numerem księgi w kolejnej pozycji na liście wszystkich znalezionych wersetów
							{
								//Jeśli oba numery sa jednakowe, to dodaj do listy tymczasowej by ja wyświetlic w formie html
								_tempHSLst->AddObject(this->_pHSListSearchResult->Strings[i], this->_pHSListSearchResult->Objects[i]);
							}
						}
					}
					if(_tempHSLst->Count > 0)
					//Wyświetlenie znalezionych wersetów w wybranej księdze
					{
            // Wyswietlenie listy wyszukanych wersetów, z możliwoscia zaznaczenie w wersecie szukanego wyrażenia
						this->_DisplayListTextHTML(this->WebBrowserSelectBookStatistic, _tempHSLst, enTypeDisplay_ResultSearchSelectBook);
						this->STextInfoSelectBookSearch->Caption = Format("W księdze o nazwie: \"%s\" znaleziono: %u wersetów", ARRAYOFCONST(( Item->Caption, _tempHSLst->Count )));
					}
					else
					//Wyczyszczenie objektu klasy TWebBrowser, gdy lista dla danej księgi jest pusta
					{
						this->WebBrowserSelectBookStatistic->Navigate(WideString("about:blank").c_bstr());
						this->STextInfoSelectBookSearch->Caption = "Brak wyników wyszukiwania";
					}
				}
				catch(Exception &e)
				{
					MessageBox(NULL, e.Message.c_str() , TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
				}
			}
			__finally
			{
				delete _tempHSLst; _tempHSLst = nullptr;
			}
		}
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::ButtonHelpRegExpClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TButton *pButtSearch = dynamic_cast<TButton *>(Sender);
	if(!pButtSearch) return;
	//---
	MessageBox(this->Handle, Gl_ustrInoRegSearch.c_str(), L"Informacja aplikacji", MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::CBoxSearchDrawItem(TWinControl *Control,
					int Index, TRect &Rect, TOwnerDrawState State)
/**
	OPIS METOD(FUNKCJI): Własne rysowanie objektóe, klasy TComboBox
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TComboBox *pCBox = dynamic_cast<TComboBox *>(Control);
	if(!pCBox) return;
	//---
	TCanvas *pCanvas = pCBox->Canvas;
	if(State.Contains(odSelected))
	{
		pCanvas->Brush->Color = clWebOrangeRed;
		pCanvas->Font->Color = pCBox->Font->Color;
	}

	pCanvas->FillRect(Rect);

	switch(pCBox->Tag)
	{
		case enIdent_CBoxSelectRangeSearch:
			this->ImgListSmallSearch->Draw(pCanvas, 1, Rect.Height() / 2 - (this->ImgListSmallSearch->Height / 2) + Rect.Top, enImageSearch_SelectRange);
		break;
		//---
		case enIdent_CBoxStartSelectRange:
			this->ImgListSmallSearch->Draw(pCanvas, 1, Rect.Height() / 2 - (this->ImgListSmallSearch->Height / 2) + Rect.Top, enImageSearch_StartSelect);
		break;
		//---
		case enIdent_CBoxStopSelectRange:
			this->ImgListSmallSearch->Draw(pCanvas, 1, Rect.Height() / 2 - (this->ImgListSmallSearch->Height / 2) + Rect.Top, enImageSearch_StopSelect);
		break;
		//---
		case enIdent_CBoxSelectTranslate:
			this->ImgListSmallSearch->Draw(pCanvas, 1, Rect.Height() / 2 - (this->ImgListSmallSearch->Height / 2) + Rect.Top, enImageSearch_Translates);
		break;
	}
	//Rect.Left += 18;
	Rect.Left += (this->ImgListSmallSearch->Width + 2);

	DrawText(pCanvas->Handle, pCBox->Items->Strings[Index].c_str(), -1, &Rect, DT_SINGLELINE | DT_VCENTER);
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::PControlChanging(TObject *Sender,
					bool &AllowChange)
/**
	OPIS METOD(FUNKCJI): Zezwolenie na zmiane zakładki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TPageControl *pPControl = dynamic_cast<TPageControl *>(Sender);
	if(!pPControl) return;
	//---
	switch(pPControl->Tag)
	{
		case enTag_PControlSearchViewText: //Zakładki wyników wyszykiwania
			//Przełączenie na zakładke z listą wyników wyszukiwania, jest niemożliwe, jeśli lista jest pusta
			AllowChange = (this->LViewResultSearch->Items->Count > 0);

		break;
		//---
		case enTag_PControlSetupsSearch: //Zakładki ustawiania i statystyki
			AllowChange = (this->LViewResultSearch->Items->Count > 0);// || (pPControl->TabIndex != enIndexStatisticSearch);
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::LViewStatisticDrawItem(TCustomListView *Sender,
					TListItem *Item, TRect &Rect, TOwnerDrawState State)
/**
	OPIS METOD(FUNKCJI): Własne rysowanie objektu klasy TListView
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListView *pLView = dynamic_cast<TListView *>(Sender);
	if(!pLView) return;
	//---
	TRect RectBounds = Item->DisplayRect(drBounds);
	TRect RectLabel = Item->DisplayRect(drLabel);
	TRect RectIcon = Item->DisplayRect(drIcon);
	float fBarFind;//=0;
	unsigned int uiCountSearch=0;
	//---
	if(Item->Data)
	//Odzcyt z danych prywatnych pozycji ilości znalezionych słów dla danej księgi, którą reprezentuje pozycja
	{
		PStatisticFindView MyDataStatisti = static_cast<PStatisticFindView>(Item->Data);
		uiCountSearch = MyDataStatisti->uiCountFind;
	}
	//---
	if(State.Contains(odSelected))
	//Selekcja pozycji
	{
		if(uiCountSearch > 0)
		//Są wyniki wyszukiwania dla ksiegi
		{
			pLView->Canvas->Brush->Color = clYellow;
		}
		else
		//Brak wyników wyszukiwania dla ksiegi
		{

		}
	}
	//---
	if(uiCountSearch > 0)
	//Są wyniki wyszukiwania dla ksiegi 16-04-2021
	{
		pLView->Canvas->FillRect(RectBounds);
		pLView->SmallImages->Draw(pLView->Canvas, RectIcon.Left, RectIcon.Top + 1, enImageIndex_Book);
	}
	else
	//Brak wyników wyszukiwania dla ksiegi
	{
		pLView->Canvas->Font->Color = clGray;
	}
	//---
	RectLabel.Left += 2;
	DrawText(pLView->Canvas->Handle,	Item->Caption.c_str(), -1, &RectLabel, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	//---
	TRect RectSubItem = RectBounds;
	for(int iColumn=0; iColumn<pLView->Columns->Count - 1; ++iColumn)
	{
		//Wymiary następnej kolumny
		RectSubItem.Left += pLView->Column[iColumn]->Width + 1;
		if(iColumn==pLView->Columns->Count - 2) RectSubItem.Right = pLView->ClientRect.Right;
		else RectSubItem.Right += pLView->Column[iColumn + 1]->Width;
		if((uiCountSearch > 0) && (iColumn == enColumn_CountFind-1))
		{
			pLView->Canvas->Font->Style = TFontStyles() << fsBold;
			pLView->Canvas->Font->Color = clRed;
			DrawText(pLView->Canvas->Handle, UnicodeString(uiCountSearch).c_str() , -1, &RectSubItem, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
		}
		else if((uiCountSearch > 0) && (iColumn == enColumn_Progres-1))
		//Rysowanie wykresu
		{
			fBarFind = (float)RectSubItem.Width() / (float)this->_pHSListSearchResult->Count;
			pLView->Canvas->Brush->Color = clGreen;

			RectSubItem.Right = RectSubItem.Left + (fBarFind * (float)uiCountSearch);
			RectSubItem.Inflate(0, -4, 0, -4);
			pLView->Canvas->FillRect(RectSubItem);
			pLView->Canvas->Brush->Color = clBlue;

			pLView->Canvas->FrameRect(RectSubItem);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::FormDeactivate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	///
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::FormActivate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	///
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::CBoxHistorySearchTextChange(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Zmieniłeś tekst wyszukiwany w polu objektu, klasy TComboBox
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TComboBox *pCBox = dynamic_cast<TComboBox *>(Sender);
	if(!pCBox) return;
	//--- Kontrola wyszukiwanie tylko w wypadku nie pustego pola tekstowego
	//GsReadBibleTextItem *pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(this->STW_CBoxSelectTranslates->ItemIndex);
	//if(!pGsReadBibleTextItem) return;
	//this->STW_ButtonSearchStart->Enabled = (pGsReadBibleTextItem->enTypeTranslate == enTypeTr_Full && !pCBox->Text.IsEmpty());
	this->ButtonSearchStart->Enabled = (!pCBox->Text.IsEmpty());
	//this->STW_ButtonSaveSearch->Enabled = this->STW_ButtonSearchStart->Enabled;
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::PControlViewsTextDrawTab(TCustomTabControl *Control,
					int TabIndex, const TRect &Rect, bool Active)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TPageControl *pPControl = dynamic_cast<TPageControl *>(Control);
	if(!pPControl) return;
	//-----
	TTabSheet *pActSheet = dynamic_cast<TTabSheet *>(pPControl->Pages[TabIndex]);	//Aktualna zakładka
	if(!pActSheet) return;
	//---
	TRect MyRect(Rect);
	pPControl->Canvas->Brush->Color = TStyleManager::ActiveStyle->GetSystemColor(clBtnFace);
	pPControl->Canvas->Font->Color = clWhite;
	switch(pPControl->Tag)
	{
		case enTag_PControlSetupsSearch: //Zakładki ustawiania i statystyki
		{
			if(Active)
			{
				//pPControl->Canvas->Font->Color = clWhite;
				pPControl->Canvas->Brush->Color = clWebMaroon;
			}
		}
		break;
		//---
	 case enTag_PControlSearchViewText: //Zakładki wyników wyszukiwania
		{
			if(Active)
			{
				pPControl->Canvas->Font->Color = clYellow;
				pPControl->Canvas->Brush->Color = clWebDarkSlategray;//clWebDarkMagenta;
			}
		}
		break;
	}

	pPControl->Canvas->FillRect(Rect);
	pPControl->Images->Draw(pPControl->Canvas, Rect.Left + 4, (Rect.Top + ((Rect.Bottom - Rect.Top) / 2)) - (pPControl->Images->Height / 2) + 2, pActSheet->ImageIndex);
	//MyRect.Inflate(-pPControl->Images->Width - 4, 0);
	MyRect.Left += (pPControl->Images->Width + 4);
	DrawText(pPControl->Canvas->Handle, pActSheet->Caption.c_str(), -1, &MyRect, DT_VCENTER | DT_SINGLELINE);
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::_DisplayListTextHTML(TWebBrowser *_pWebBrowser, THashedStringList *_pHListAnyVers,
	const EnTypeDisplayHTML _TypeDisplayHTML, const int iSelectDisplayVerset)
/**
	OPIS METOD(FUNKCJI): Wyswietlenie listy wyszukanych wersetów, z możliwoscia zaznaczenie w wersecie szukanego wyrażenia
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	MyObjectVers *pMyOjectVers=nullptr;
	TStringStream *pStringStream = new TStringStream("", TEncoding::UTF8, true);
	if(!pStringStream) throw(Exception("Błąd inicjalizacji objektu TStringStream"));

	UnicodeString ustrTemp;
	//---
	const UnicodeString ustrDisplayHeaderHTMLSearchAll = UnicodeString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n") +
		"<html>\n<head>\n" +
		"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n" +
		"<title>Wyniki wyszukiwania</title>\n" +
		"<style type=\"text/css\">\n" +
		".styleColorAdressTranslates {color: #FF0000; font-size:12pt;font-family:Times New Roman;}\n" +
		//".styleTranslates {color: #AAAAAA;font-size:12pt;font-family:Times New Roman;}" +
		".styleText {color: #000000;font-size:14pt;font-family:Times New Roman;}\n" +
		".styleFound {background-color: #FFFF00;}\n" +
		"body {background-color:" + RGBToWebColorStr(this->ColorBoxBackGroundSearchList->Selected) +
			";font-size:12pt;font-family:Times New Roman;}\n" +
		"</style>\n</head>\n<body>\n",
	ustrDisplayHeaderHTMLSearchBook = UnicodeString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n") +
		"<html>\n<head>\n" +
		"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n" +
		"<title>Wyniki wyszukiwania</title>\n" +
		"<style type=\"text/css\">\n" +
		".styleColorAdressTranslates {color: #FF0000; font-size:12pt;font-family:Times New Roman;}\n" +
		//".styleTranslates {color: #AAAAAA;font-size:12pt;font-family:Times New Roman;}" +
		".styleText {color: #000000;font-size:14pt;font-family:Times New Roman;}\n" +
		".styleFound {background-color: #FFFF00;}\n" +
		"body {background-color:" + RGBToWebColorStr(this->ColorBoxBackGroundStatisticList->Selected) +
			";font-size:12pt;font-family:Times New Roman;}\n" +
		"</style>\n</head>\n<body>\n",
	ustrDisplayHeaderHTMLSelectSearchVers = UnicodeString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n") +
		"<html>\n<head>\n" +
		"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n" +
		"<title>Wyniki wyszukiwania</title>\n" +
		"<style type=\"text/css\">\n" +
		".styleColorAdressTranslates {color: #FF0000; font-size:24pt;font-family:Times New Roman;}\n" +
		//".styleTranslates {color: #AAAAAA;font-size:12pt;font-family:Times New Roman;}" +
		".styleText {color: #000000;font-size:24pt;font-family:Times New Roman;}\n" +
		".styleFound {background-color: #FFFF00;}\n" +
		"body {background-color:" + RGBToWebColorStr(this->ColorBoxBackGroundSelectVers->Selected) +
			";font-size:16pt;font-family:Times New Roman;}\n" +
		"</style>\n</head>\n<body>\n";
	UnicodeString ustrDefineDisplayHTML;
	//---
	switch(_TypeDisplayHTML)
	{
		case enTypeDisplay_ResultsearchAll:				 //Wyświetlanie wszystkich znalezionych wersetów
			ustrDefineDisplayHTML = ustrDisplayHeaderHTMLSearchAll;

		break;
		//---
		case enTypeDisplay_ResultSearchSelectBook: //Wyświetlanie znelozionych wersetów dla konkretnej księgi
			ustrDefineDisplayHTML = ustrDisplayHeaderHTMLSearchBook;

		break;
		//---
		case enTypeDisplay_ResultSelectVers:			 //Wyświetlanie wybranego wersetu z listy wszystkich znalezionych wesetów
			ustrDefineDisplayHTML = ustrDisplayHeaderHTMLSelectSearchVers;

		break;
	}
	pStringStream->WriteString(ustrDefineDisplayHTML);

	try
	{
		try
		{
			for(int i=0; i<_pHListAnyVers->Count; ++i)
			{
				if((iSelectDisplayVerset > -1) && (i != iSelectDisplayVerset)) continue;
				pMyOjectVers = static_cast<MyObjectVers *>(_pHListAnyVers->Objects[i]);
				if(!pMyOjectVers) throw(Exception("Błąd odczytu objektu MyObjectVers"));
				//Dodawanie kolejnego wersetu
				ustrTemp = Format(UnicodeString("<p>\n") +
					"<span class=\"styleColorAdressTranslates\">\n%s\n</span>\n<span class=\"styleText\">\n%s\n</span>\n",
					ARRAYOFCONST((pMyOjectVers->BookChaptVers, _pHListAnyVers->Strings[i])));
				pStringStream->WriteString(ustrTemp);
				//pStringStream->WriteString("<br>");
				pStringStream->WriteString("</p>\n\n");
			}
			pStringStream->WriteString("</body>\n</html>\n");
			//----- Posłużenie sie pomocniczym TStringList, dla zapisania do strumienia, jako UTF-8
			pStringStream->Position = 0;
			//--- Zmienna do zapisu zawartości zakładki w postaci kodu html, z wybranym rozdziałem, do ewentualnego zapisu jako samodzielnej strony.
			if(_TypeDisplayHTML == enTypeDisplay_ResultsearchAll)
			{
				this->_ustrResultSearchHTML = ""; //[10-10-2023]
				this->_ustrResultSearchHTML += pStringStream->DataString; //[10-10-2023]
			}
			//---
			IPersistStreamInit *psi;
			_di_IStream sa(*(new TStreamAdapter(pStringStream, soReference)));
			if(SUCCEEDED(_pWebBrowser->Document->QueryInterface(IID_IPersistStreamInit, (void **)&psi)))
				{psi->Load(sa);}
		}
		catch(Exception &e)
		{
			MessageBox(NULL, e.Message.c_str() , TEXT("Błąd"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	}
	__finally
	{
		if(pStringStream) {delete pStringStream; pStringStream = nullptr;}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::ColorBoxGetColors(TCustomColorBox *Sender,
					TStrings *Items)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TColorBox *pColorBox = dynamic_cast<TColorBox *>(Sender);
	if(!pColorBox) return;
	//---
	Items->AddObject("clWebWheat", reinterpret_cast<TObject*>(clWebWheat));
	Items->AddObject("clWebBurlywood", reinterpret_cast<TObject*>(clWebBurlywood));
	Items->AddObject("clWebLinen", reinterpret_cast<TObject*>(clWebLinen));
	Items->AddObject("clWebLemonChiffon", reinterpret_cast<TObject*>(clWebLemonChiffon));
	Items->AddObject("clWebDarkOrange", reinterpret_cast<TObject*>(clWebDarkOrange));
	Items->AddObject("clWebDarkRed", reinterpret_cast<TObject*>(clWebDarkRed));
	Items->AddObject("clWebCoral", reinterpret_cast<TObject*>(clWebCoral));
	Items->AddObject("clWebGold", reinterpret_cast<TObject*>(clWebGold));
	Items->AddObject("clWebRosyBrown", reinterpret_cast<TObject*>(clWebRosyBrown));
	Items->AddObject("clWebForestGreen", reinterpret_cast<TObject*>(clWebForestGreen));
	Items->AddObject("clWebChartreuse", reinterpret_cast<TObject*>(clWebChartreuse));
	Items->AddObject("clWebSeaGreen", reinterpret_cast<TObject*>(clWebSeaGreen));
	Items->AddObject("clWebMediumAquamarine", reinterpret_cast<TObject*>(clWebMediumAquamarine));
	Items->AddObject("clWebLightCyan", reinterpret_cast<TObject*>(clWebLightCyan));
	Items->AddObject("clWebCornFlowerBlue", reinterpret_cast<TObject*>(clWebCornFlowerBlue));
	Items->AddObject("clWebIndigo", reinterpret_cast<TObject*>(clWebIndigo));
	Items->AddObject("clWebAqua", reinterpret_cast<TObject*>(clWebAqua));
	Items->AddObject("clWebRoyalBlue", reinterpret_cast<TObject*>(clWebRoyalBlue));
	Items->AddObject("clWebMidnightBlue", reinterpret_cast<TObject*>(clWebMidnightBlue));
	Items->AddObject("clWebDarkViolet", reinterpret_cast<TObject*>(clWebDarkViolet));
	Items->AddObject("clWebDarkMagenta", reinterpret_cast<TObject*>(clWebDarkMagenta));
	Items->AddObject("clWebDeepPink", reinterpret_cast<TObject*>(clWebDeepPink));
	Items->AddObject("clWebMediumSlateBlue", reinterpret_cast<TObject*>(clWebMediumSlateBlue));
	Items->AddObject("clWebSteelBlue", reinterpret_cast<TObject*>(clWebSteelBlue));
	Items->AddObject("clWebSlateBlue", reinterpret_cast<TObject*>(clWebSlateBlue));
	Items->AddObject("clWebDarkSlategray", reinterpret_cast<TObject*>(clWebDarkSlategray));
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::ColorBoxChange(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TColorBox *pColorBox = dynamic_cast<TColorBox *>(Sender);
	if(!pColorBox) return;
	//---
	//UnicodeString ustrSelectColor = RGBToWebColorStr(pColorBox->Selected);

	switch(pColorBox->Tag)
	{
		case enIdent_ColorBBackGroundStatisticList:
		break;
		//---
		case enIdent_ColorBBockGroundSearchList:
		break;
		//---
	}

	this->ButtonSearchStartClick(this->ButtonSearchStart);

	if(this->LViewResultSearch->ItemIndex > -1)
	{
		//Odświerzenie listy wszystkich znalezionych wersetów
		TListItem *Item = this->LViewResultSearch->Items->Item[this->LViewResultSearch->ItemIndex];
		if(Item)
		{
			this->LViewAllSelectItem(this->LViewResultSearch, Item ,true);
		}
	}
	//Odświerzać listy znalezionych wersetów nie trzeba gdyż wywołana metoda this->STW_ButtonSearchStartClick(this->STW_ButtonSearchStart),
	//powoduje wyczyszczenie wszystkich statystyk
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::ButtonSaveSearchClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):	//[10-10-2023]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TButton *pButton = dynamic_cast<TButton *>(Sender);
	if(!pButton) return;
	//---
	if(this->_ustrResultSearchHTML.IsEmpty()) return;
	//---
	UnicodeString ustrPathToSave = TPath::ChangeExtension(TPath::Combine(GlobalVar::Global_custrPathSearchFavorities, CBoxHistorySearchText->Text), GlobalVar::Global_custrFileSearchFavExtend),
								ustrPathInfos = TPath::ChangeExtension(ustrPathToSave, GlobalVar::Global_custrFileSearchInfoExtand);
	TFile::WriteAllText(ustrPathToSave, this->_ustrResultSearchHTML, TEncoding::UTF8);
	TMemIniFile *pIni = new TMemIniFile(ustrPathInfos, TEncoding::UTF8);
	if(!pIni) throw(Exception("Błąd inicjalizacji objektu TMemIniFile"));

	pIni->WriteString(GlobalVar::GlobalInfoSearch_Header, GlobalVar::GlobalInfoSearch_Name, this->CBoxHistorySearchText->Text);
	pIni->WriteString(GlobalVar::GlobalInfoSearch_Header, GlobalVar::GlobalInfoSearch_Translate, this->CBoxSelectTranslates->Text);
	pIni->WriteString(GlobalVar::GlobalInfoSearch_Header, GlobalVar::GlobalInfoSearch_RangeName, this->CBoxSelectRangeSearch->Text);
	pIni->WriteString(GlobalVar::GlobalInfoSearch_Header, GlobalVar::GlobalInfoSearch_Range, this->CBoxStartSelectRange->Text + "-" + this->CBoxStopSelectRange->Text);
	pIni->WriteInteger(GlobalVar::GlobalInfoSearch_Header, GlobalVar::GlobalInfoSearch_Count, this->_pHSListSearchResult->Count);

	//Zrzucenie zawartości objektu, klasy TMemIni, do pliku
	pIni->UpdateFile();
	if(pIni) {delete pIni; pIni = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::ButtAddListTextSearchClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TButton *pButtSearch = dynamic_cast<TButton *>(Sender);
	if(!pButtSearch) return;
	//---
	this->LBoxSearchTexts->Items->BeginUpdate();
	if(!this->CBoxHistorySearchText->Text.IsEmpty() && this->LBoxSearchTexts->Enabled)
	{
		if(this->LBoxSearchTexts->Items->IndexOf(this->CBoxHistorySearchText->Text) == -1)
		// Jeśli wyrażenie nie jest już na liście
		{
			this->LBoxSearchTexts->AddItem(this->CBoxHistorySearchText->Text, nullptr);
			this->DeleteSelectPos->Enabled = true;
			this->ButtClearAllListSearch->Enabled = true;
		}
	}
	this->LBoxSearchTexts->Items->EndUpdate();

  this->ButtonSearchStart->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::ButtAllListSearchClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TButton *pButt = dynamic_cast<TButton *>(Sender);
	if(!pButt) return;
	//---
	switch(pButt->Tag)
	{
		case enTagListSearch_ClearAll: // Czyszcenie całej zawartości
			this->LBoxSearchTexts->Items->BeginUpdate();
			this->LBoxSearchTexts->Clear();
			this->LBoxSearchTexts->Items->EndUpdate();
			pButt->Enabled = false;
			this->DeleteSelectPos->Enabled = this->LBoxSearchTexts->Count > 0;
		break;
		//---
		case enTagListSearch_DeleteSelect:  // Usunięcie zaznaczonej pozycji
			this->LBoxSearchTexts->DeleteSelected();
			pButt->Enabled = this->LBoxSearchTexts->Count > 0;
			this->ButtClearAllListSearch->Enabled = this->LBoxSearchTexts->Count > 0;
		break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::ButtGrSelectActionListClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TButtonGroup *pButtGroup = dynamic_cast<TButtonGroup *>(Sender);
	if(!pButtGroup) return;
	//---
	this->LabelInfosSelectActionSearch->Caption = Gl_ustrInfosTypesActionSearch[pButtGroup->ItemIndex];
}
//---------------------------------------------------------------------------

