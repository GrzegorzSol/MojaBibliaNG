﻿#include <vcl.h>
#pragma hdrstop

#include "uHistoryChaptersOpen.h"
#include "MyBibleLibrary\MyBibleLibrary.h" //Główna klasa do pracy z tekstem biblijnym
#include "MyBibleLibrary\GsReadBibleTextdata.h"
#include "uGlobalVar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
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
THistoryOpenChaptersWindow *HistoryOpenChaptersWindow;

static int iLViewStartIndex=0; static int iLViewEndIndex=0; //Zakres dolny i górny elementów w liście wirtualnej
const UnicodeString custrNameColumns[] = {"Rozdział", "Data otwarcia"}; //Nazwy kolumn na liście historii
enum {//Kolumny
			enColumn_Chapter, enColumn_DateTime, enColumn_Count,
			//Głowne obrazy 32 pikseli
			enImage_DeleteSelectItem=0,
			//Małe obrazy 16 pikseli dla listy i jej kolumn
			enSmallImage_ChaptItem=0, enSmallImage_DateItem, enSmallImage__ColumnChapt, enSmallImage_ColumnDate};

//---------------------------------------------------------------------------
__fastcall THistoryOpenChaptersWindow::THistoryOpenChaptersWindow(TComponent* Owner, TAction *pAction)
	: TForm(Owner), _pStartAction(pAction)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW: TAction *pAction - Akcja, króra wywołała okno
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListColumn *NewColumn;

	//Dodawanie kolumn
	for(unsigned int iColumns=0; iColumns<enColumn_Count; ++iColumns)
	{
		NewColumn = this->LViewHistoryCh->Columns->Add();
		NewColumn->Caption = custrNameColumns[iColumns];
		NewColumn->AutoSize = true;
		NewColumn->ImageIndex = iColumns + enSmallImage__ColumnChapt;
	}

	this->LViewHistoryCh->Items->BeginUpdate();
	this->LViewHistoryCh->Items->Count = GlobalVar::Global_HListHistoryChapterOpen->Count;
	this->LViewHistoryCh->Items->EndUpdate();

	this->_pStartAction->Enabled = false;
	//---
	this->Act_DeleteSelectItemHistoryCh->Hint = Format("%s|Skasowanie z listy historii zaznaczonej pozycji, operacja jest nieodwracalna.|%u", ARRAYOFCONST((this->Act_DeleteSelectItemHistoryCh->Caption, this->Act_DeleteSelectItemHistoryCh->ImageIndex)));
}
//---------------------------------------------------------------------------
void __fastcall THistoryOpenChaptersWindow::FormClose(TObject *Sender, TCloseAction &Action)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	Action = caFree;
	this->_pStartAction->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall THistoryOpenChaptersWindow::Act_DeleteSelectItemHistoryChExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	TListItem *pListItem = this->LViewHistoryCh->Selected;
	int iIndexOf=-1;

	UnicodeString ustrMessage = "Czy jesteś pewny, że chcesz skasować wybraną(ne) pozycje z listy historii? Nie będzie można cofnąć operacji i odzyskać pozycje!";//[23-08-2023]

	THashedStringList *pHSListSelected = new THashedStringList(); //Tymczasowa (buforowa) lista zaznaczonych elementów //[22-08-2023]
	if(!pHSListSelected) throw(Exception("Błąd inicjalizacji objektu, klasy THashedStringList!"));
	TItemStates selected = TItemStates() << isSelected;

	while(pListItem)
	{
		pHSListSelected->Add(GlobalVar::Global_HListHistoryChapterOpen->Strings[pListItem->Index]);
		pListItem = this->LViewHistoryCh->GetNextItem(pListItem, sdAll, selected);
	}

	int iResult = MessageBox(NULL, ustrMessage.c_str(), //[23-08-2023]
													 TEXT("Pytanie aplikacji"), MB_YESNO | MB_ICONWARNING | MB_TASKMODAL | MB_DEFBUTTON2);
	if(iResult == IDNO)
	{
		if(pHSListSelected) {delete pHSListSelected; pHSListSelected = nullptr;}
		this->LViewHistoryCh->ClearSelection();
		return;
	}

	for(int i=0; i<pHSListSelected->Count; ++i)
	{
		iIndexOf = GlobalVar::Global_HListHistoryChapterOpen->IndexOf(pHSListSelected->Strings[i]);
		if(iIndexOf == -1) continue;
		GlobalVar::Global_HListHistoryChapterOpen->Delete(iIndexOf);
	}

	if(pHSListSelected) {delete pHSListSelected; pHSListSelected = nullptr;}

	this->LViewHistoryCh->Items->BeginUpdate();
	this->LViewHistoryCh->Items->Count = GlobalVar::Global_HListHistoryChapterOpen->Count;
	this->LViewHistoryCh->Items->EndUpdate();

	this->LViewHistoryCh->ClearSelection();
}
//---------------------------------------------------------------------------
void __fastcall THistoryOpenChaptersWindow::LViewHistoryChData(TObject *Sender,
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
	//--- Wyjście, gdy element, nie mieści się w zakresie listy
	if((Item->Index<iLViewStartIndex) || (Item->Index>iLViewEndIndex)) return;

	Item->Caption = GlobalVar::Global_HListHistoryChapterOpen->Names[Item->Index];
	Item->SubItems->Add(GlobalVar::Global_HListHistoryChapterOpen->ValueFromIndex[Item->Index]);
}
//---------------------------------------------------------------------------
void __fastcall THistoryOpenChaptersWindow::LViewHistoryChDataFind(TObject *Sender,
					TItemFind Find, const UnicodeString FindString, const TPoint &FindPosition,
					Pointer FindData, int StartIndex, TSearchDirection Direction,
					bool Wrap, int &Index)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListView *pLView = dynamic_cast<TListView *>(Sender);
	if(!pLView) return;
	//---
	Index = -1;
}
//---------------------------------------------------------------------------
void __fastcall THistoryOpenChaptersWindow::LViewHistoryChDataHint(TObject *Sender,
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
	//---
	iLViewStartIndex = StartIndex; //Dolny zakres, elementów listy
	iLViewEndIndex = EndIndex;		 //Górny zakres, elementów listy
}
//---------------------------------------------------------------------------
void __fastcall THistoryOpenChaptersWindow::LViewHistoryChDblClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListView *pLView = dynamic_cast<TListView *>(Sender);
	if(!pLView) return;
	//---
	PInfoAllBooks pInfobook=nullptr;
	TListItem *Item = pLView->Items->Item[pLView->ItemIndex];
	int iBook=-1, iChapt=-1, iPosSpace=0;
	if(!Item) return;
	UnicodeString ustrName = Item->Caption.SubString(1, Item->Caption.Pos(":") - 1),
								ustrChapt;
	UnicodeString ustrTest = Item->Caption.SubString(Item->Caption.Pos(": ") + 2, 25);
	iPosSpace = ustrTest.Pos(" ");
	ustrChapt = ustrTest.Delete(iPosSpace, 28);
	iChapt = ustrChapt.ToIntDef(1);

	for(int i=0; i<GlobalVar::Global_NumberBooks; ++i)
	{
		pInfobook = const_cast<PInfoAllBooks>(&AppCTable_InfoAllBooks[i]);
		if(!pInfobook) return;

		if(pInfobook->FullNameBook == ustrName)
		{
			iBook = i + 1;
			break;
		}
	}
	GsReadBibleTextData::OpenSelectBookAndChapter(iBook, iChapt);
	//GlobalVar::Global_HListHistoryChapterOpen->Delete(GlobalVar::Global_HListHistoryChapterOpen->Count - 1);
	GlobalVar::Global_HListHistoryChapterOpen->Delete(0);
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall THistoryOpenChaptersWindow::LViewHistoryChChange(TObject *Sender,
					TListItem *Item, TItemChange Change) //[22-08-2023]
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListView *pLView = dynamic_cast<TListView *>(Sender);
	if(!pLView) return;
	//---
	if(Change == ctState)
	{
		//Aktywacja przycisku do kasowania pozycji gdy istnieje choćby jeden element zaznaczony
		this->Act_DeleteSelectItemHistoryCh->Enabled = (this->LViewHistoryCh->SelCount > 0);
	}
}
//---------------------------------------------------------------------------
void __fastcall THistoryOpenChaptersWindow::LViewHistoryChGetImageIndex(TObject *Sender,
					TListItem *Item)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	Item->ImageIndex = enSmallImage_ChaptItem;
}
//---------------------------------------------------------------------------
void __fastcall THistoryOpenChaptersWindow::LViewHistoryChGetSubItemImage(TObject *Sender,
					TListItem *Item, int SubItem, int &ImageIndex)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	ImageIndex = enSmallImage_DateItem;
}
//---------------------------------------------------------------------------

