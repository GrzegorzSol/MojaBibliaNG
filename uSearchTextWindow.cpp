//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uSearchTextWindow.h"
#include "GsReadBibleTextClass\GsReadBibleTextClass.h"
#include <System.RegularExpressions.hpp>
#include "uGlobalVar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSearchTextWindow *SearchTextWindow;
static StatisticFindView TableStatisticFindView[GsReadBibleTextData::GsNumberBooks]; //Tablica wyników wyszukiwań, dla statystyki
//---
enum {  //Numery zakładek w ustawieniach wyszukiwania
				enIndexSetInputSearch, enIndexStatisticSearch,
				enIndexResultListHtml=0, enIndexResultListSelect,
				//Numery idyntyfikacyjne kontrolek
				enIdent_CBoxSelectRangeSearch = 0x100,
				enIdent_CBoxStartSelectRange,
				enIdent_CBoxStopSelectRange,
				enIdent_CBoxSelectTranslate,
				//Numery indeksów ikon
				enImageSearch_ButtonSearchStart=0,   //0.Rozpoczęcie wyszukiwania
				enImageSearch_ViewResultSearch,    //1.Przegląd wyników wyszukiwania
				enImageSearch_HelpReg,             //2.Pomoc w wyszukiwaniu za pomocą wyrażeń regularnych
				enImageSearch_StartSelect,         //3.Początkowa księga zakresu wyszukiwania
				enImageSearch_StopSelect,          //4.Końcowa księga zakresu wyszukiwania
				enImageSearch_Translates,          //5.Wybór tłumaczenia
				enImageSearch_SelectRange,         //6.Wybór zakresu wyszukiwania
				enImageSearch_Count,
				//Stałe numerów kolumn dla listy statystyki
				enColumn_NameBook=0, enColumn_CountFind, enColumn_Progres, enColumn_Count,
				//Tagi dla kontrolek
				enTag_PControlSet=100, //Zakładki wprowadzanie danych do przeszukiwań i statystyki wyszukiwania
				enTag_PCcontrolViewText //Zakładki wyników wyszukiwania
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
		"{n} - poprzedzający element pasuje dokładnie n razy";
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
	const unsigned char cucLimitGroupBooks[] = {39, 66, 73};
	enum {enLimit_OldTestament, enLimit_NewTestament, enLimit_Apocryfics=73};
  //---
	if(Screen->DesktopHeight > 800) this->Height = 795; else this->Height = 600; //Wysokość okna, zależna od wysokości ekranu
	this->STW_WBrowserResultSearch->Navigate(WideString("about:blank").c_bstr());	//Wypełnienie kontrolki pustą stroną, obowiązkowo!!!
  this->STW_WBrowserSelectItemResult->Navigate(WideString("about:blank").c_bstr());	//Wypełnienie kontrolki pustą stroną, obowiązkowo!!!
	this->STW_PControlSet->ActivePageIndex = enIndexSetInputSearch; //Domyślnie aktywna zakładka, po stworzeniu okna
	this->STW_PControlViewsText->ActivePageIndex = enIndexResultListHtml; //Domyślnie aktywna zakładka, wyników przeglądania
	//Nadawanie numerów identyfikacyjnych kontrolkom
	this->STW_CBoxSelectRangeSearch->Tag = enIdent_CBoxSelectRangeSearch;
	this->STW_CBoxStartSelectRange->Tag = enIdent_CBoxStartSelectRange;
	this->STW_CBoxStopSelectRange->Tag = enIdent_CBoxStopSelectRange;
	this->STW_CBoxSelectTranslates->Tag = enIdent_CBoxSelectTranslate;
	this->STW_PControlViewsText->Tag = enTag_PCcontrolViewText; //Zakładki wyników wyszukiwania
	this->STW_PControlSet->Tag = enTag_PControlSet; //Zakładki wprowadzanie danych do przeszukiwań i statystyki wyszukiwania
	//Wstępne ustawienia zawartości komponentów
		//Definiowanie komponentów wyboru ksiąg biblijnych
	for(int i=0; i<GsReadBibleTextData::GsNumberBooks; i++)
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
	this->STW_LEditSearchText->Hint = "Pole tekstowe do wprowadzania szukanego tekstu.";
	this->STW_ChBoxIsRegEx->Hint = "Czy wyszukiwanie będzie używało wyrażeń regularnych";
	this->STW_ButtonHelpRegExp->Hint = "Pomoc w wyszukiwaniu za pomocą wyrażeń regularnych.";
	this->STW_CBoxSelectRangeSearch->Hint = Format("Zakres wyszukiwania|Wybór zakresu ksiąg, które będą brane pod uwagę podczas wyszukiwania|%u", ARRAYOFCONST((enImageSearch_SelectRange)));
	this->STW_CBoxStartSelectRange->Hint = Format("Początkowa księga w wyszukiwaniu|Początkowa księga w zakresie wyszukiwania, zdefiniowanym przez użytkownika|%u", ARRAYOFCONST((enImageSearch_StartSelect)));
	this->STW_CBoxStopSelectRange->Hint = Format("Końcowa księga w wyszukiwaniu|Początkowa księga w zakresie wyszukiwania, zdefiniowanym przez użytkownika|%u", ARRAYOFCONST((enImageSearch_StopSelect)));
	this->STW_CBoxSelectTranslates->Hint = Format("Wybór tłumaczenia|Wybór tłumaczenia do przeszukania|%u", ARRAYOFCONST((enImageSearch_Translates)));
	this->STW_ButtonSearchStart->Hint = Format("Rozpoczęcie wyszukiwania|Rozpoczęcie wyszukiwania według ustawionych parametrów|%u", ARRAYOFCONST((this->STW_ButtonSearchStart->ImageIndex)));
	//----- Ustawienia objektu, klasy TListView dla statystyki
	TListColumn *NewColumn;//=0;
	TImageList *pImgList = GsReadBibleTextData::GetImageListData();
	if(!pImgList) throw(Exception("Błąd wyłuskania objektu TImageList"));
	this->STW_LViewStatistic->SmallImages = pImgList;
	//this->STW_LViewStatistic->GroupHeaderImages = pImgList;
	for(int i=0; i<GsReadBibleTextData::GsNumberGroups; i++)
	{
		TListGroup *NewGroup = this->STW_LViewStatistic->Groups->Add();
		NewGroup->State << lgsNormal << lgsCollapsible;
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
	for(unsigned char i=0; i<GsReadBibleTextData::GsNumberBooks; i++)
	{
		TListItem *NewItem = this->STW_LViewStatistic->Items->Add();
		NewItem->Caption = GsReadBibleTextData::GsInfoAllBooks[i].FullNameBook;
		if(i<cucLimitGroupBooks[enLimit_OldTestament]) NewItem->GroupID = 0;
		else if(i>=cucLimitGroupBooks[enLimit_OldTestament] && i<cucLimitGroupBooks[enLimit_NewTestament]) NewItem->GroupID = 1;
		else if(i>=cucLimitGroupBooks[enLimit_NewTestament]) NewItem->GroupID = 2;
	}
	this->STW_LViewStatistic->Items->EndUpdate();
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
	this->_pHSListSearchResult = new THashedStringList();
	if(!this->_pHSListSearchResult) throw(Exception("Błąd tworzenia tymczasowego objektu THashedStringList"));
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
	if(this->_pHSListSearchResult) {delete this->_pHSListSearchResult; this->_pHSListSearchResult = 0;}
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
	TRegExOptions regOptions = TRegExOptions() << roSingleLine << roIgnoreCase;
	signed char scTempStart, scTempStop;
	//---
	if(this->STW_LEditSearchText->Text.IsEmpty()) return; //Jeśli pole tekstu do wyszukanie jest puste, opuść metodę
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
	ZeroMemory(TableStatisticFindView, sizeof(TableStatisticFindView)); //Wyzerowanie tablicy statystyki wyszukiwania
	for(signed char scIndex=scTempStart; scIndex<=scTempStop; scIndex++)
	{
		pBookListText = GsReadBibleTextData::GetSelectBoksInTranslate(pGsReadBibleTextItem, scIndex);
		if(pBookListText)
		{
			for(int i=0; i<pBookListText->Count; i++)
			{
				iIndexTable = System::Sysutils::StrToInt(pBookListText->Strings[i].SubString(1, 3)) - 1; //Numer księgi liczony od 0.
				if(this->STW_ChBoxIsRegEx->Checked) //Wyszukiwanie za pomocą wyrażeń regularnych
				{
					if(System::Regularexpressions::TRegEx::IsMatch(pBookListText->Strings[i], this->STW_LEditSearchText->Text, regOptions))
					{
						this->_pHSListSearchResult->AddObject(pBookListText->Strings[i].SubString(10, ciSizeCutString), pBookListText->Objects[i]);
						//Wypełnienie odpowiedniej pozycji tablicy statystyki wyszukiwania. iIndexTable to numer księgi liczony od 0.
						TableStatisticFindView[iIndexTable].uiCountFind++;
					}
				}
				else //Wyszukiwanie tradycyjne
				{
					iPositionSearch = System::Sysutils::AnsiLowerCase(pBookListText->Strings[i]).Pos(System::Sysutils::AnsiLowerCase(this->STW_LEditSearchText->Text));
					if(iPositionSearch > 0)
					{
						//Wstawianie znacznika koloru, podkładu. MUSI być modyfikowana kopia
						ustrTemp = pBookListText->Strings[i].Insert(custrStyleF, iPositionSearch); //Wstawienie początku stylu, przed słowem szukanym
						//Wstawienie zakończenia stylu po szukanym słowie, plus wcześniej wstawionym stylu.
						ustrTemp = ustrTemp.Insert("</span>", iPositionSearch + this->STW_LEditSearchText->Text.Length() + custrStyleF.Length());
						this->_pHSListSearchResult->AddObject(ustrTemp.SubString(10, ciSizeCutString), pBookListText->Objects[i]);
						//Wypełnienie odpowiedniej pozycji tablicy statystyki wyszukiwania. iIndexTable to numer księgi liczony od 0.
						TableStatisticFindView[iIndexTable].uiCountFind++;
					} //if(iPositionSearch > 0)
				} //if(this->STW_ChBoxIsRegEx->Checked)
			} //for(int i=0; i<pBookListText->Count; i++)
		} //if(pBookListText)
	} //for(...)

	GsReadBibleTextData::DisplayListText(this->STW_WBrowserResultSearch, this->_pHSListSearchResult);
	this->STW_LViewResultSearch->Items->BeginUpdate();
	this->STW_LViewResultSearch->Items->Count = this->_pHSListSearchResult->Count;
	if(this->_pHSListSearchResult->Count > 0) this->STW_LViewResultSearch->ItemIndex = 0; //Po modyfikacji listy, jeśli ma elementy, wybieralnej wyników, pierwsza pozycja aktywna
	this->STW_LViewResultSearch->Items->EndUpdate();
	this->STW_WBrowserResultSearch->SetFocus();
	this->STW_StBarInfos->SimpleText = Format("Znaleziono %u pozycji", ARRAYOFCONST((this->_pHSListSearchResult->Count)));
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
				GsReadBibleTextItem *pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(pCBox->ItemIndex);
				if(!pGsReadBibleTextItem) return;
				this->STW_ButtonSearchStart->Enabled = (pGsReadBibleTextItem->enTypeTranslate == enTypeTr_Full && !this->STW_LEditSearchText->Text.IsEmpty());
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
	this->STW_LEditSearchText->Clear();
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
void __fastcall TSearchTextWindow::STW_LViewResultSearchSelectItem(TObject *Sender,
					TListItem *Item, bool Selected)
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
	if(!Item || !Selected) return;
  //Wyświetl aktualnie zaznaczoną pozycji z całej listy wyników wyszukiwania (Item->Index)
	GsReadBibleTextData::DisplayListText(this->STW_WBrowserSelectItemResult, this->_pHSListSearchResult, Item->Index);
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
	Rect.Left += 18;

	DrawTextW(pCanvas->Handle, pCBox->Items->Strings[Index].c_str(), -1, &Rect, DT_SINGLELINE | DT_VCENTER);
}
//---------------------------------------------------------------------------
void __fastcall TSearchTextWindow::STW_PControlChanging(TObject *Sender,
					bool &AllowChange)
/**
	OPIS METOD(FUNKCJI): Własne rysowanie objektóe, klasy TComboBox
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TPageControl *pPControl = dynamic_cast<TPageControl *>(Sender);
	if(!pPControl) return;
	switch(pPControl->Tag)
	{
		case enTag_PCcontrolViewText: //Zakładki wprowadzanie danych do przeszukiwań i statystyki wyszukiwania
		break;
		//---
		case enTag_PControlSet: //Zakładki wyników wyszukiwania
		break;
	}
	//Przełączenie na zakładke z listą wyników wyszukiwania i statystyki, jest niemożliwe, jeśli lista jest pusta
	AllowChange = this->STW_LViewResultSearch->Items->Count > 0;
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
	if(State.Contains(odSelected))
	{
		pLView->Canvas->Brush->Color = clYellow;
	}
  pLView->Canvas->FillRect(RectBounds);
	pLView->SmallImages->Draw(pLView->Canvas, RectIcon.Left, RectIcon.Top + 1, enImageIndex_Book);

  RectLabel.Left += 2;
	DrawText(pLView->Canvas->Handle,  Item->Caption.c_str(), -1, &RectLabel, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	TRect RectSubItem = RectBounds;
	for(int iColumn=0; iColumn<pLView->Columns->Count - 1; iColumn++)
	{
    //Wymiary następnej kolumny
		RectSubItem.Left += pLView->Column[iColumn]->Width + 1;
		if(iColumn==pLView->Columns->Count - 2) RectSubItem.Right = pLView->ClientRect.Right;
		else RectSubItem.Right += pLView->Column[iColumn + 1]->Width;
		if((TableStatisticFindView[Item->Index].uiCountFind > 0) && (iColumn == enColumn_CountFind-1))
		{
			pLView->Canvas->Font->Style = TFontStyles() << fsBold;
			pLView->Canvas->Font->Color = clRed;
			DrawText(pLView->Canvas->Handle, UnicodeString(TableStatisticFindView[Item->Index].uiCountFind).c_str() , -1, &RectSubItem, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
		}
		else if((TableStatisticFindView[Item->Index].uiCountFind > 0) && (iColumn == enColumn_Progres-1))
		//Rysowanie wykresu
		{
			fBarFind = (float)RectSubItem.Width() / (float)this->_pHSListSearchResult->Count;
			pLView->Canvas->Brush->Color = clGreen;

			RectSubItem.Right = RectSubItem.Left + (fBarFind * (float)TableStatisticFindView[Item->Index].uiCountFind);
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

