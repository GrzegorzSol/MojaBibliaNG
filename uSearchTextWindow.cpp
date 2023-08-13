#include <vcl.h>
#pragma hdrstop

#include "uSearchTextWindow.h"
#include "MyBibleLibrary\MyBibleLibrary.h"
#include "MyBibleLibrary\GsReadBibleTextdata.h"
#include <System.RegularExpressions.hpp>
#include "uGlobalVar.h"
#include <System.IOUtils.hpp>
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
*/
//---
enum {  //Numery zakładek w ustawieniach wyszukiwania
				enIndexSetInputSearch, enIndexStatisticSearch, enIndexSetupsSearch,
				enIndexResultListHtml=0, enIndexResultListSelect,
				//Numery idyntyfikacyjne kontrolek
				enIdent_CBoxSelectRangeSearch = 0x100,
				enIdent_CBoxStartSelectRange,
				enIdent_CBoxStopSelectRange,
				enIdent_CBoxSelectTranslate,
				//Numery identyfikacyjne kontrolek do ustawiania kolorów
				enIdent_ColorBBackGroundStatisticList = 0x200,
				enIdent_ColorBBockGroundSearchList,
				//Numery indeksów ikon
				enImageSearch_ButtonSearchStart=0,   //0.Rozpoczęcie wyszukiwania
				enImageSearch_ViewResultSearch,    //1.Przegląd wyników wyszukiwania
				enImageSearch_HelpReg,             //2.Pomoc w wyszukiwaniu za pomocą wyrażeń regularnych
				enImageSearch_StartSelect,         //3.Początkowa księga zakresu wyszukiwania
				enImageSearch_StopSelect,          //4.Końcowa księga zakresu wyszukiwania
				enImageSearch_Translates,          //5.Wybór tłumaczenia
				enImageSearch_SelectRange,         //6.Wybór zakresu wyszukiwania
				enImageSearch_Statistic,           //7.Zakładka statystyki wyszukiwania
				enImageSearch_InputText,           //8.Zakładka wprowadzania tekstu szukanego
				enImageSearch_ResultListHTML,      //9.Zakładka wyników wyszukiwania w formie html
				enImageSearch_ResultListSelect,    //10.Zakładka wyników wyszukiwania z możliwością wyboru
        enImageSearch_Setups,              //11.Ustawienia dodakowe dla wyszukiwania
				enImageSearch_Count,
				//Stałe numerów kolumn dla listy statystyki
				enColumn_NameBook=0, enColumn_CountFind, enColumn_Progres, enColumn_Count,
				//Tagi dla kontrolek
				enTag_PControlSetupsSearch=100, //Zakładki wprowadzanie danych do przeszukiwań i statystyki wyszukiwania
				enTag_PControlSearchViewText, //Zakładki wyników wyszukiwania
        //Tagi dla objektów, klasy TListView
				enTag_LViewResultSearch, //Objekt klasy TListView z listą znalezionych wersetów
				enTag_LViewStatistic,    //Objekt klasy TListView z listą statystyki występowania szukanego tekstu dla poszczególnych ksiąg
				//Tagi dla objektów, klasy TCheckBox
				enTag_CBoxIsReg,         //Czy używać w wyszukiwaniu wyrażeń regularnych?
				enTag_CBoxIsSizeText,    //Czy podczas wyszukiwań rozróżniać wielkość liter?
				enTag_CBoxIsMemorySetupsSearch  //Czy zapamiętać parametry wuszukiwania?
		 };
//Tekst opisu dla skłdni wyrażeń regularnych
const static UnicodeString ustrInoRegSearch = UnicodeString(". - (kropka)=dowolny znak\n") +
		"^ - dopasuj występujące po operatorze wyrażenie do początku wiersza (początek linii)\n" +
		"$ - dopasuj poprzedzające wyrażenie do końca wiersza (koniec linii)\n" +
		"\\x - znaki specjalne, gdzie  x to znak specjalny np. \\$ zastąpi znak dolara\n" +
		"[lista] - zastępuje dowolny znak spośród tych wymienionych na liście, mogą to być, przedziały np. [0-9] lub [a-d]\n" +
		"[^lista] - pasuje do znaku nie podanego na liście\n" +
		"\\< - początek słowa\n" +
		"\\> - koniec słowa\n" +
		"\\w - jest równoważne [0-9a-zA-Z] lub [[:alnum:]] – zastępuje dowolną liczbę lub cyfrę\n" +
		"\\W - oznacza to samo co $[^[[:alnum:]]]\n" +
		"()  - grupowanie wyrażeń regularnych\n" +
		"| 	 - operator LUB\n" +
		"? 	 - dokładnie zero lub jeden element wcześniejszy\n" +
		"a|b - dopasuje wyrażenie  a lub wyrażenie  b\n" +
		"* 	 - dopasuj zero lub więcej wyrażeń znaku poprzedzający operator\n" +
		"+ 	 - jeden lub więcej elementów poprzedzających operator\n" +
		"{n} - poprzedzający element pasuje dokładnie n razy",
													ustrTextLogoSearch = "DzAp 17:11\n\"...przyjęli oni Słowo z całą gotowością i codziennie BADALI Pisma, czy tak się rzeczy mają\"";
//Nazwy kolumn dla listy statystyki
const static UnicodeString ustrNameColumn[] = {"Nazwa księgi", "Ilość wystąpień", "Wskaźnik"};
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
	this->STW_WBrowserResultSearch->Navigate(WideString("about:blank").c_bstr());	//Wypełnienie kontrolki pustą stroną, obowiązkowo!!!
	this->STW_WBrowserSelectItemResult->Navigate(WideString("about:blank").c_bstr());	//Wypełnienie kontrolki pustą stroną, obowiązkowo!!!
	this->STW_WebBrowserSelectBookStatistic->Navigate(WideString("about:blank").c_bstr());	//Wypełnienie kontrolki pustą stroną, obowiązkowo!!!
	this->STW_PControlSetupsSearch->ActivePageIndex = enIndexSetInputSearch; //Domyślnie aktywna zakładka, po stworzeniu okna
	this->STW_PControlViewsText->ActivePageIndex = enIndexResultListHtml; //Domyślnie aktywna zakładka, wyników przeglądania
	//Nadawanie numerów identyfikacyjnych kontrolkom
	this->STW_CBoxSelectRangeSearch->Tag = enIdent_CBoxSelectRangeSearch;
	this->STW_CBoxStartSelectRange->Tag = enIdent_CBoxStartSelectRange;
	this->STW_CBoxStopSelectRange->Tag = enIdent_CBoxStopSelectRange;
	this->STW_CBoxSelectTranslates->Tag = enIdent_CBoxSelectTranslate;
	this->STW_PControlViewsText->Tag = enTag_PControlSearchViewText; //Zakładki wyników wyszukiwania
	this->STW_PControlSetupsSearch->Tag = enTag_PControlSetupsSearch; //Zakładki wprowadzanie danych do przeszukiwań i statystyki wyszukiwania
	//Ustawienia kolorów
	this->STW_ColorBoxBackGroundStatisticList->Tag = enIdent_ColorBBackGroundStatisticList;
	this->STW_ColorBoxBackGroundSearchList->Tag = enIdent_ColorBBockGroundSearchList;
		//Objekty klasy TListView
	this->STW_LViewResultSearch->Tag = enTag_LViewResultSearch; //Objekt klasy TListView z listą znalezionych wersetów
	this->STW_LViewStatistic->Tag = enTag_LViewStatistic;     //Objekt klasy TListView z listą statystyki występowania szukanego tekstu dla poszczególnych ksiag
	//Tagi dla objektów, klasy TCheckBox
	this->STW_ChBoxIsRegEx->Tag = enTag_CBoxIsReg;         //Czy używać w wyszukiwaniu wyrażeń regularnych?
	this->STW_ChBoxSizeTextSearch->Tag = enTag_CBoxIsSizeText;    //Czy podczas wyszukiwań rozróżniać wielkość liter?
	this->STW_ChBoxMemoSetupsSearch->Tag = enTag_CBoxIsMemorySetupsSearch;  //Czy zapamiętać parametry wuszukiwania?
	//Wstępne ustawienia zawartości komponentów
		//Definiowanie komponentów wyboru ksiąg biblijnych
	for(int i=0; i<GlobalVar::Global_NumberBooks; i++)
		{this->STW_CBoxStartSelectRange->Items->Add(GsReadBibleTextData::GsInfoAllBooks[i].FullNameBook);}
	this->STW_CBoxStopSelectRange->Items->Assign(this->STW_CBoxStartSelectRange->Items);
		//Definiowanie komponentu zakresu wyszukiwania
	for(unsigned int i=0; i<ARRAYSIZE(GsReadBibleTextData::GsNameAllRanges); i++)
		{this->STW_CBoxSelectRangeSearch->Items->Add(GsReadBibleTextData::GsNameAllRanges[i]);}
	this->STW_CBoxSelectRangeSearch->ItemIndex = en_GrSearch_FullAll;
		//Definiowanie listy tłumaczeń do wybrania
	UnicodeString ustrNameTranslate;
	if(GsReadBibleTextData::CountTranslates() > 0)
	{
		for(unsigned char i=0; i<GsReadBibleTextData::CountTranslates(); i++)
		{
			GsReadBibleTextData::GetInfoNameTranslate(i, ustrNameTranslate);
			this->STW_CBoxSelectTranslates->Items->Add(ustrNameTranslate);
		}
    this->STW_CBoxSelectTranslates->ItemIndex = 0;  //Domyślne pierwsze, dostępne tłumaczenie
	}
	this->STW_CBoxHistorySearchText->Hint = "Pole tekstowe do wprowadzania szukanego tekstu.";
	this->STW_ChBoxIsRegEx->Hint = "Czy wyszukiwanie będzie używało wyrażeń regularnych";
	this->STW_ButtonHelpRegExp->Hint = "Pomoc w wyszukiwaniu za pomocą wyrażeń regularnych.";
	this->STW_CBoxSelectRangeSearch->Hint = Format("Zakres wyszukiwania|Wybór zakresu ksiąg, które będą brane pod uwagę podczas wyszukiwania|%u", ARRAYOFCONST((enImageSearch_SelectRange)));
	this->STW_CBoxStartSelectRange->Hint = Format("Początkowa księga w wyszukiwaniu|Początkowa księga w zakresie wyszukiwania, zdefiniowanym przez użytkownika|%u", ARRAYOFCONST((enImageSearch_StartSelect)));
	this->STW_CBoxStopSelectRange->Hint = Format("Końcowa księga w wyszukiwaniu|Początkowa księga w zakresie wyszukiwania, zdefiniowanym przez użytkownika|%u", ARRAYOFCONST((enImageSearch_StopSelect)));
	this->STW_CBoxSelectTranslates->Hint = Format("Wybór tłumaczenia|Wybór tłumaczenia do przeszukania|%u", ARRAYOFCONST((enImageSearch_Translates)));
	this->STW_ButtonSearchStart->Hint = Format("Rozpoczęcie wyszukiwania|Rozpoczęcie wyszukiwania według ustawionych parametrów|%u", ARRAYOFCONST((this->STW_ButtonSearchStart->ImageIndex)));

	//Logo wyszukiwania
	if(TFile::Exists(GlobalVar::Global_custrPathSearchLogo))
	{
		TWICImage *pWICImage = new TWICImage();
		if(!pWICImage) throw(Exception("Błąd inicjalizacji objektu TWICImage"));
		pWICImage->LoadFromFile(GlobalVar::Global_custrPathSearchLogo);
		this->STW_ImageLogoSearch->Picture->Assign(pWICImage);
		delete pWICImage; pWICImage = nullptr;
		this->STW_STextLogoSearch->Caption = ustrTextLogoSearch;
	}
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
	TImageList *pImgList = GsReadBibleTextData::GetImageListData();
	if(!pImgList) throw(Exception("Błąd wyłuskania objektu TImageList"));
	this->STW_LViewStatistic->SmallImages = pImgList;
	//this->STW_LViewStatistic->GroupHeaderImages = pImgList;
	for(int i=0; i<GsReadBibleTextData::GsNumberGroups; i++)
	{
		TListGroup *NewGroup = this->STW_LViewStatistic->Groups->Add();
		NewGroup->State = TListGroupStateSet() << lgsNormal << lgsCollapsible;
		NewGroup->Header = GsReadBibleTextData::GsNamesTableNameGroupBook[i];
		NewGroup->HeaderAlign = taCenter;
	}
	//Dodawanie kolumn do objektu, klasy TListView, statystyki
	for(unsigned int iColumns=0; iColumns<enColumn_Count; iColumns++)
	{
		NewColumn = this->STW_LViewStatistic->Columns->Add();
		NewColumn->Caption = ustrNameColumn[iColumns];
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
	this->STW_LViewStatistic->Items->BeginUpdate();
	for(unsigned char i=0; i<GlobalVar::Global_NumberBooks; i++)
	{
		TListItem *NewItem = this->STW_LViewStatistic->Items->Add();
		NewItem->Caption = GsReadBibleTextData::GsInfoAllBooks[i].FullNameBook;
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
	this->STW_LViewStatistic->Items->EndUpdate();
	//Lista zawierające wszystkie znalezione wersety
	this->_pHSListSearchResult = new THashedStringList();
	if(!this->_pHSListSearchResult) throw(Exception("Błąd tworzenia tymczasowego objektu THashedStringList"));
	//Lista dotyczczasowych tekstów wyszukiwanych
		//Odczyt pliku histori wyszukiwania
	if(TFile::Exists(GlobalVar::Global_custrPathHistorySearch))
		{this->STW_CBoxHistorySearchText->Items->LoadFromFile(GlobalVar::Global_custrPathHistorySearch, TEncoding::UTF8);}
	//Odczyt i ustawienie objektów klasy TColorBox według zawartości pliku konfiguracyjnego
		//Wygląd
	this->STW_ColorBoxBackGroundSearchList->Selected = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSetupsSection_Main, GlobalVar::GlobalIni_ColorsSetupsBackGroundAllListSearch, clMoneyGreen);
	this->STW_ColorBoxBackGroundStatisticList->Selected = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSetupsSection_Main, GlobalVar::GlobalIni_ColorsSetupBackGroundSelectBookSearch, clMoneyGreen);
	this->STW_ColorBoxBackGroundSelectVers->Selected = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSetupsSection_Main, GlobalVar::GlobalIni_ColorsSetupBackGroundSelectVers, clMoneyGreen);
		//Parametry wyszukiwania
	this->STW_ChBoxMemoSetupsSearch->Checked = GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_IsMemorySetupsSearch, false);
	if(this->STW_ChBoxMemoSetupsSearch->Checked)
  //Jeśli zapamiętywanie parametrów jest włączone
	{
		this->STW_CBoxSelectTranslates->ItemIndex = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_Translate, 0);
		this->STW_CBoxHistorySearchText->Text = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_TextSearch, "");
		this->STW_ButtonSearchStart->Enabled = !this->STW_CBoxHistorySearchText->Text.IsEmpty(); //Aktywacja przycisku wyszukiwania zależna od istnienia tekstu szukanego
		this->STW_CBoxSelectRangeSearch->ItemIndex = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_SetupRangeBooks, en_GrSearch_FullAll);
		if(this->STW_CBoxSelectRangeSearch->ItemIndex > en_GrSearch_Apocr)
		//Jeśli zakres jest ustawiony na własny, lub pojedyńczą księge
		{
			this->STW_CBoxStartSelectRange->ItemIndex = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_StartUserRange, 0);
			this->STW_CBoxStopSelectRange->ItemIndex = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_StopUserRange, this->STW_CBoxStopSelectRange->Items->Count-1);
		}
		this->STW_ChBoxSizeTextSearch->Checked = GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_IsSizeTextSearch, false);
		this->STW_ChBoxIsRegEx->Checked = GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_IsRegSearch, false);
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

	this->STW_CBoxHistorySearchText->Items->SaveToFile(GlobalVar::Global_custrPathHistorySearch, TEncoding::UTF8);
	//Zwalnianie prywatnych danych związanych z objektem TListitem, dla poszczególnych ksiąg
	for(int i=0; i<GlobalVar::Global_NumberBooks; i++)
	{
		TListItem *MyItem = this->STW_LViewStatistic->Items->Item[i];
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
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ColorsSetupsSection_Main, GlobalVar::GlobalIni_ColorsSetupsBackGroundAllListSearch, this->STW_ColorBoxBackGroundSearchList->Selected);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ColorsSetupsSection_Main, GlobalVar::GlobalIni_ColorsSetupBackGroundSelectBookSearch, this->STW_ColorBoxBackGroundStatisticList->Selected);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ColorsSetupsSection_Main, GlobalVar::GlobalIni_ColorsSetupBackGroundSelectVers, this->STW_ColorBoxBackGroundSelectVers->Selected);
  	//Parametry wyszukiwania
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_IsMemorySetupsSearch, this->STW_ChBoxMemoSetupsSearch->Checked);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_Translate, this->STW_CBoxSelectTranslates->ItemIndex);
	GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_TextSearch, this->STW_CBoxHistorySearchText->Text);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_SetupRangeBooks, this->STW_CBoxSelectRangeSearch->ItemIndex);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_StartUserRange, this->STW_CBoxStartSelectRange->ItemIndex);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_StopUserRange, this->STW_CBoxStopSelectRange->ItemIndex);
  GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_IsSizeTextSearch, this->STW_ChBoxSizeTextSearch->Checked);
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_ParametersSetupsSearch_Main, GlobalVar::GlobalIni_IsRegSearch, this->STW_ChBoxIsRegEx->Checked);
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
void __fastcall TSearchTextWindow::STW_ButtonSearchStartClick(TObject *Sender)
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
	this->STW_PControlViewsText->TabIndex = enIndexResultListHtml;
	//---
	THashedStringList *pBookListText;//=0;
	int iPositionSearch,//=0,
			iIndexTable;//=0;  //Numer księgi liczony od 0.
	const int ciSizeCutString=512; //Ilość znaków skopiowanych z całej zawartosci wersetu(razem z adresem)
	UnicodeString ustrTemp;
	const UnicodeString custrStyleF = "<span class=styleFound>";
	//---
	TRegExOptions regOptions;
	if(this->STW_ChBoxSizeTextSearch->Checked) //Uwzględniana wielkość liter przy używaniu wyrażeń regularnych
		{regOptions = TRegExOptions() << roSingleLine;}
	else {regOptions = TRegExOptions() << roSingleLine << roIgnoreCase;}
	//---
	signed char scTempStart, scTempStop;
	PStatisticFindView MyDataStatistic=nullptr;
	//---
	if(this->STW_CBoxHistorySearchText->Text.IsEmpty()) return; //Jeśli pole tekstu do wyszukanie jest puste, opuść metodę
	//---- Wyłuskanie tłumaczenia
	GsReadBibleTextItem *pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(this->STW_CBoxSelectTranslates->ItemIndex);
	if(!pGsReadBibleTextItem || (pGsReadBibleTextItem->enTypeTranslate != enTypeTr_Full)) return; //Wyjście, gdy nie udało sie wyłuskać tłumaczenia
	//---
	if(this->STW_CBoxSelectRangeSearch->ItemIndex < en_UserRange && this->STW_CBoxSelectRangeSearch->ItemIndex > -1)
	//Jeśli wybranym zakresem, jest zakres zdefiniowany, nie własny
	{
		scTempStart = GsReadBibleTextData::GsPairsGroupBible[STW_CBoxSelectRangeSearch->ItemIndex].ucStartRange;
		scTempStop = GsReadBibleTextData::GsPairsGroupBible[STW_CBoxSelectRangeSearch->ItemIndex].ucStopRange;
	}
	else if(this->STW_CBoxSelectRangeSearch->ItemIndex >= en_UserRange)
	//Jeśli wybranym zakresem, jest zakres własny
	{
		if(this->STW_CBoxStartSelectRange->ItemIndex > -1 &&  this->STW_CBoxStopSelectRange->ItemIndex > -1)
		{
			scTempStart = this->STW_CBoxStartSelectRange->ItemIndex;
			scTempStop = this->STW_CBoxStopSelectRange->ItemIndex;
		}
	}
	else return;
	//---
	this->_pHSListSearchResult->Clear();
	for(signed char scIndex=scTempStart; scIndex<=scTempStop; scIndex++)
	{
		pBookListText = GsReadBibleTextData::GetSelectBoksInTranslate(pGsReadBibleTextItem, scIndex);
		TListItem *MyItem = this->STW_LViewStatistic->Items->Item[scIndex];
		//Wyłuskanie danych dla pozycji, która reprezentuje księgę. W tej danej będzie przechowywana ilość wystąpień szukanego słowa dla każdej księgi
		if(MyItem)
		{
			if(MyItem->Data)
			{
				MyDataStatistic = static_cast<PStatisticFindView>(MyItem->Data);
				MyDataStatistic->uiCountFind=0; //Wyczyszczenie pozycji
			}
		}
		//---
		if(pBookListText)
		{
			for(int i=0; i<pBookListText->Count; i++)
			{
				iIndexTable = pBookListText->Strings[i].SubString(1, 3).ToInt() - 1; //Numer księgi liczony od 0.
				//---
				if(this->STW_ChBoxIsRegEx->Checked) //Wyszukiwanie za pomocą wyrażeń regularnych
				{
					if(System::Regularexpressions::TRegEx::IsMatch(pBookListText->Strings[i], this->STW_CBoxHistorySearchText->Text, regOptions))
					{
						this->_pHSListSearchResult->AddObject(pBookListText->Strings[i].SubString(10, ciSizeCutString), pBookListText->Objects[i]);
						//Wypełnienie odpowiedniej pozycji tablicy statystyki wyszukiwania. iIndexTable to numer księgi liczony od 0.
						MyDataStatistic->uiCountFind++;
					}
				}
				else //Wyszukiwanie tradycyjne
				{
					UnicodeString ustrSearchString;
					if(this->STW_ChBoxSizeTextSearch->Checked) //Uwzględniana wielkość liter
					{
						ustrSearchString = this->STW_CBoxHistorySearchText->Text;
						iPositionSearch = pBookListText->Strings[i].Pos(ustrSearchString);
					}
					else
					{
						ustrSearchString = System::Sysutils::AnsiLowerCase(this->STW_CBoxHistorySearchText->Text);
						iPositionSearch = System::Sysutils::AnsiLowerCase(pBookListText->Strings[i]).Pos(ustrSearchString);
					}
//					if(iPositionSearch > 0)
//					{
//						UnicodeString ustrReplace = custrStyleF + ustrSearchString + "</span>";
//  						ustrTemp = StringReplace(pBookListText->Strings[i], ustrSearchString,
//  							ustrReplace, TReplaceFlags() << rfReplaceAll << rfIgnoreCase);
//
//						this->_pHSListSearchResult->AddObject(ustrTemp.SubString(10, ciSizeCutString), pBookListText->Objects[i]);
//						//Wypełnienie odpowiedniej pozycji tablicy statystyki wyszukiwania. iIndexTable to numer księgi liczony od 0.
//						MyDataStatistic->uiCountFind++;
//					}
					if(iPositionSearch > 0)
					{
						//Wstawianie znacznika koloru, podkładu. MUSI być modyfikowana kopia
						ustrTemp = pBookListText->Strings[i].Insert(custrStyleF, iPositionSearch); //Wstawienie początku stylu, przed słowem szukanym
						//Wstawienie zakończenia stylu po szukanym słowie, plus wcześniej wstawionym stylu.
						ustrTemp = ustrTemp.Insert("</span>", iPositionSearch + this->STW_CBoxHistorySearchText->Text.Length() + custrStyleF.Length());

						this->_pHSListSearchResult->AddObject(ustrTemp.SubString(10, ciSizeCutString), pBookListText->Objects[i]);
						//Wypełnienie odpowiedniej pozycji tablicy statystyki wyszukiwania. iIndexTable to numer księgi liczony od 0.
						MyDataStatistic->uiCountFind++;
					} //if(iPositionSearch > 0)
				} //if(this->STW_ChBoxIsRegEx->Checked)
			} //for(int i=0; i<pBookListText->Count; i++)
		} //if(pBookListText)
	} //for(...)

  this->STW_LViewStatistic->Repaint(); //Odświerzenie listy statystyki 04-05-2021

	this->_DisplayListTextHTML(this->STW_WBrowserResultSearch, this->_pHSListSearchResult, enTypeDisplay_ResultsearchAll); //Wszystkie znalezione teksty
	this->STW_LViewResultSearch->Items->BeginUpdate();
	this->STW_LViewResultSearch->Items->Count = this->_pHSListSearchResult->Count;
	if(this->_pHSListSearchResult->Count > 0)
	{
		this->STW_LViewResultSearch->ItemIndex = 0; //Po modyfikacji listy, jeśli ma elementy, wybieralnej wyników, pierwsza pozycja aktywna
	}
	this->STW_LViewResultSearch->Items->EndUpdate();
	this->STW_WBrowserResultSearch->SetFocus();
	this->STW_StBarInfos->SimpleText = Format("Znaleziono %u pozycji", ARRAYOFCONST((this->_pHSListSearchResult->Count)));
	//Dodawanie do objekstu, klasy TComboBox sów wyszukiwanych 15-04-2021
	bool bIsDuplicate=false; //Zmienna oznaczająca że jest(true), lub nie (false) duplicat w słowie szukanym
	const int ciMaxHistorySearchText=24; //Maksymalna liczba zapamiętanej histori szukanego tekstu.
                                       //Gdy zostanie ona przekroczona, zostanie usunięte najstarsze słowo, by dodać najnowsze

	for(int i=0; i<this->STW_CBoxHistorySearchText->Items->Count; i++)
	{
		if(STW_CBoxHistorySearchText->Text.LowerCase() == this->STW_CBoxHistorySearchText->Items->Strings[i].LowerCase())
		{
			bIsDuplicate = true; break;
    }
	}

	if(!bIsDuplicate)
	{
		if(ciMaxHistorySearchText <= this->STW_CBoxHistorySearchText->Items->Count) this->STW_CBoxHistorySearchText->Items->Delete(0);
		this->STW_CBoxHistorySearchText->Items->Add(STW_CBoxHistorySearchText->Text);  //Lista dotyczczasowych tekstów wyszukiwanych
	}
  //Wyczyszczenie objektu klasy TWebBrowser, po wyszukaniu nowego słowa
	this->STW_WebBrowserSelectBookStatistic->Navigate(WideString("about:blank").c_bstr());
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
	this->STW_WebBrowserSelectBookStatistic->Navigate(WideString("about:blank").c_bstr());
	for(unsigned char i=0; i<GlobalVar::Global_NumberBooks; i++)
	{
		TListItem *MyItem = this->STW_LViewStatistic->Items->Item[i];
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
  this->STW_LViewStatistic->Repaint();
	//---
	switch(pCBox->Tag)
	{
		case enIdent_CBoxSelectRangeSearch:
			//--- Uaktywnienie wyborów początku i końca zakresu wyszukiwania, zależnie od wyboru właściwej pozycji z listy rozwijalnej
			{
				this->STW_CBoxStartSelectRange->Enabled = (pCBox->ItemIndex == en_UserRange) || (pCBox->ItemIndex == en_OneBook);
				this->STW_CBoxStopSelectRange->Enabled = (pCBox->ItemIndex == en_UserRange);
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
			if(pCBox->ItemIndex > this->STW_CBoxStopSelectRange->ItemIndex) this->STW_CBoxStopSelectRange->ItemIndex = pCBox->ItemIndex;
		break;
		//
		case enIdent_CBoxStopSelectRange:
			if(pCBox->ItemIndex < this->STW_CBoxStartSelectRange->ItemIndex) this->STW_CBoxStartSelectRange->ItemIndex = pCBox->ItemIndex;
    //--- Końcowy zakres wyszukiwania
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::STW_LEditSearchTextChange(TObject *Sender)
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
	GsReadBibleTextItem *pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(this->STW_CBoxSelectTranslates->ItemIndex);
	if(!pGsReadBibleTextItem) return;
	this->STW_ButtonSearchStart->Enabled = (pGsReadBibleTextItem->enTypeTranslate == enTypeTr_Full && !pLEdit->Text.IsEmpty());
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::STW_ChBoxIsRegExClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Wyczyszczenie pola do wpisywania poszukiwanego tekstu, przy każdej zmianie przełącznika
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCheckBox *pChBox = dynamic_cast<TCheckBox *>(Sender);
	if(!pChBox) return;
	//---
	this->STW_CBoxHistorySearchText->Text = "";
  this->STW_ButtonHelpRegExp->Enabled = pChBox->Checked;
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
	this->STW_ButtonSearchStartClick(this->STW_ButtonSearchStart);
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::STW_LViewResultSearchData(TObject *Sender,
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
void __fastcall TSearchTextWindow::STW_LViewResultSearchDataHint(TObject *Sender,
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
void __fastcall TSearchTextWindow::STW_LViewResultSearchGetImageIndex(TObject *Sender,
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
void __fastcall TSearchTextWindow::STW_LViewAllSelectItem(TObject *Sender,
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
			//Wyświetl aktualnie zaznaczoną pozycji z całej listy wyników wyszukiwania (Item->Index)
			this->_DisplayListTextHTML(this->STW_WBrowserSelectItemResult, this->_pHSListSearchResult, enTypeDisplay_ResultSelectVers, Item->Index);
		}
		break;
		//---
		case enTag_LViewStatistic:   //Objekt klasy TListView z listą statystyki występowania szukanego tekstu dla poszczególnych ksiąg
		{
			THashedStringList *_tempHSLst=nullptr;
			try
			{
				try
				{
					_tempHSLst = new THashedStringList();
					if(!_tempHSLst) throw(Exception("Błąd tworzenia tymczasowego objektu THashedStringList"));
					//Skopiowanie wersetów dla wybranej księgi, z lsty wszystkich znalezionych werstów
					for(int i=0; i<this->_pHSListSearchResult->Count; i++)
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
						this->_DisplayListTextHTML(this->STW_WebBrowserSelectBookStatistic, _tempHSLst, enTypeDisplay_ResultSearchSelectBook);
						this->STW_STextInfoSelectBookSearch->Caption = Format("W księdze o nazwie: \"%s\" znaleziono: %u wersetów", ARRAYOFCONST(( Item->Caption, _tempHSLst->Count )));
					}
					else
					//Wyczyszczenie objektu klasy TWebBrowser, gdy lista dla danej księgi jest pusta
					{
						this->STW_WebBrowserSelectBookStatistic->Navigate(WideString("about:blank").c_bstr());
						this->STW_STextInfoSelectBookSearch->Caption = "Brak wyników wyszukiwania";
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
void __fastcall TSearchTextWindow::STW_ButtonHelpRegExpClick(TObject *Sender)
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
	MessageBox(this->Handle, ustrInoRegSearch.c_str(), L"Informacja aplikacji", MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::STW_CBoxSearchDrawItem(TWinControl *Control,
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
void __fastcall TSearchTextWindow::STW_PControlChanging(TObject *Sender,
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
			AllowChange = (this->STW_LViewResultSearch->Items->Count > 0);

		break;
		//---
		case enTag_PControlSetupsSearch: //Zakładki ustawiania i statystyki
			AllowChange = (this->STW_LViewResultSearch->Items->Count > 0);// || (pPControl->TabIndex != enIndexStatisticSearch);
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::STW_LViewStatisticDrawItem(TCustomListView *Sender,
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
	DrawText(pLView->Canvas->Handle,  Item->Caption.c_str(), -1, &RectLabel, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	//---
	TRect RectSubItem = RectBounds;
	for(int iColumn=0; iColumn<pLView->Columns->Count - 1; iColumn++)
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
	this->AlphaBlendValue = GlobalVar::cuchABlendValue; //16-02-2020
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
	this->AlphaBlendValue = 255; //16-02-2020
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::STW_CBoxHistorySearchTextChange(TObject *Sender)
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
	this->STW_ButtonSearchStart->Enabled = (!pCBox->Text.IsEmpty());
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::STW_PControlViewsTextDrawTab(TCustomTabControl *Control,
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
	switch(pPControl->Tag)
	{
		case enTag_PControlSetupsSearch: //Zakładki ustawiania i statystyki
		{
			if(Active)
			{
				pPControl->Canvas->Font->Color = clWhite;
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
	OPIS METOD(FUNKCJI): W liście wyszukanych wersetów kliknięto na pozycje, lub liście statystyki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  MyObjectVers *pMyOjectVers=nullptr;
	TStringStream *pStringStream = new TStringStream("", TEncoding::UTF8, true);
	if(!pStringStream) throw(Exception("Błąd inicjalizacji objektu TStringStream"));
	//---
	const UnicodeString ustrDisplayHeaderHTMLSearchAll = UnicodeString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">") +
		"<html><head>" +
		"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">" +
		"<title>Wyniki wyszukiwania</title>" +
		"<style type=\"text/css\">" +
		".styleColorAdressTranslates {color: #FF0000; font-size:10pt;font-family:Times New Roman;}" +
		//".styleTranslates {color: #AAAAAA;font-size:12pt;font-family:Times New Roman;}" +
		".styleText {color: #000000;font-size:14pt;font-family:Times New Roman;}\n" +
		".styleFound {background-color: #FFFF00;}" +
		"body {background-color:" + RGBToWebColorStr(this->STW_ColorBoxBackGroundSearchList->Selected) +
			";font-size:12pt;font-family:Times New Roman;}" +
		"</style></head><body>",
	ustrDisplayHeaderHTMLSearchBook = UnicodeString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">") +
		"<html><head>" +
		"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">" +
		"<title>Wyniki wyszukiwania</title>" +
		"<style type=\"text/css\">" +
		".styleColorAdressTranslates {color: #FF0000; font-size:10pt;font-family:Times New Roman;}" +
		//".styleTranslates {color: #AAAAAA;font-size:12pt;font-family:Times New Roman;}" +
		".styleText {color: #000000;font-size:14pt;font-family:Times New Roman;}\n" +
		".styleFound {background-color: #FFFF00;}" +
		"body {background-color:" + RGBToWebColorStr(this->STW_ColorBoxBackGroundStatisticList->Selected) +
			";font-size:12pt;font-family:Times New Roman;}" +
		"</style></head><body>",
	ustrDisplayHeaderHTMLSelectSearchVers = UnicodeString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">") +
		"<html><head>" +
		"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">" +
		"<title>Wyniki wyszukiwania</title>" +
		"<style type=\"text/css\">" +
		".styleColorAdressTranslates {color: #FF0000; font-size:24pt;font-family:Times New Roman;}" +
		//".styleTranslates {color: #AAAAAA;font-size:12pt;font-family:Times New Roman;}" +
		".styleText {color: #000000;font-size:24pt;font-family:Times New Roman;}\n" +
		".styleFound {background-color: #FFFF00;}" +
		"body {background-color:" + RGBToWebColorStr(this->STW_ColorBoxBackGroundSelectVers->Selected) +
			";font-size:16pt;font-family:Times New Roman;}" +
		"</style></head><body>";
	UnicodeString ustrDefineDisplayHTML;
	//---
	switch(_TypeDisplayHTML)
	{
		case enTypeDisplay_ResultsearchAll:        //Wyświetlanie wszystkich znalezionych wersetów
			ustrDefineDisplayHTML = ustrDisplayHeaderHTMLSearchAll;
		break;
		//---
		case enTypeDisplay_ResultSearchSelectBook: //Wyświetlanie znelozionych wersetów dla konkretnej księgi
			ustrDefineDisplayHTML = ustrDisplayHeaderHTMLSearchBook;
		break;
		//---
		case enTypeDisplay_ResultSelectVers:       //Wyświetlanie wybranego wersetu z listy wszystkich znalezionych wesetów
			ustrDefineDisplayHTML = ustrDisplayHeaderHTMLSelectSearchVers;
		break;
  }
	pStringStream->WriteString(ustrDefineDisplayHTML);

	try
	{
		for(int i=0; i<_pHListAnyVers->Count; i++)
		{
			if((iSelectDisplayVerset > -1) && (i != iSelectDisplayVerset)) continue;
			pMyOjectVers = static_cast<MyObjectVers *>(_pHListAnyVers->Objects[i]);
			if(!pMyOjectVers) throw(Exception("Błąd odczytu objektu MyObjectVers"));
			//Dodawanie kolejnego wersetu
			pStringStream->WriteString(Format("<span class=\"styleColorAdressTranslates\">%s</span> <span class=\"styleText\">%s</span>", ARRAYOFCONST((pMyOjectVers->BookChaptVers, _pHListAnyVers->Strings[i]))));
			pStringStream->WriteString("<br>");
		}
		pStringStream->WriteString("</body></html>");
		//----- Posłużenie sie pomocniczym TStringList, dla zapisania do strumienia, jako UTF-8
		pStringStream->Position = 0;
		//---
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
void __fastcall TSearchTextWindow::STW_ColorBoxGetColors(TCustomColorBox *Sender,
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
void __fastcall TSearchTextWindow::STW_ColorBoxChange(TObject *Sender)
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

	this->STW_ButtonSearchStartClick(this->STW_ButtonSearchStart);

	if(this->STW_LViewResultSearch->ItemIndex > -1)
	{
		//Odświerzenie listy wszystkich znalezionych wersetów
		TListItem *Item = this->STW_LViewResultSearch->Items->Item[this->STW_LViewResultSearch->ItemIndex];
		if(Item)
		{
			this->STW_LViewAllSelectItem(this->STW_LViewResultSearch, Item ,true);
		}
	}
	//Odświerzać listy znalezionych wersetów nie trzeba gdyż wywołana metoda this->STW_ButtonSearchStartClick(this->STW_ButtonSearchStart),
  //powoduje wyczyszczenie wszystkich statystyk
}
//---------------------------------------------------------------------------

