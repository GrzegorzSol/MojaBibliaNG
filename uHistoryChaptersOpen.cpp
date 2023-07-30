#include <vcl.h>
#pragma hdrstop

#include "uHistoryChaptersOpen.h"
#include "GsReadBibleTextClass\GsReadBibleTextClass.h" //Główna klasa do pracy z tekstem biblijnym
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
	for(unsigned int iColumns=0; iColumns<enColumn_Count; iColumns++)
	{
		NewColumn = this->LViewHistoryCh->Columns->Add();
		NewColumn->Caption = custrNameColumns[iColumns];
    NewColumn->AutoSize = true;
		NewColumn->ImageIndex = iColumns + enSmallImage__ColumnChapt;
	}

	this->LViewHistoryCh->Items->BeginUpdate();
	this->LViewHistoryCh->Items->Count = GlobalVar::Global_HListHistoryChapterOpen->Count;
	this->LViewHistoryCh->Items->EndUpdate();

	this->Act_DeleteSelectItemHistoryCh->Enabled = this->LViewHistoryCh->Items->Count > 0;
	this->_pStartAction->Enabled = false;
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
  #if defined(_DEBUGINFO_)
		GsDebugClass::WriteDebug(Format("%d - pListItem: %s", ARRAYOFCONST((pListItem->Index, pListItem->Caption))));
	#endif

	int iResult = MessageBox(NULL, TEXT("Czy jesteś pewny, że chcesz skasować wybraną pozycje historii? Nie będzie go można później odzyskać!"),
													 TEXT("Pytanie aplikacji"), MB_YESNO | MB_ICONWARNING | MB_TASKMODAL | MB_DEFBUTTON2);
	if(iResult == IDNO) return;


	GlobalVar::Global_HListHistoryChapterOpen->Delete(pListItem->Index);
  this->LViewHistoryCh->Items->BeginUpdate();
	this->LViewHistoryCh->Items->Count = GlobalVar::Global_HListHistoryChapterOpen->Count;
	this->LViewHistoryCh->Items->EndUpdate();
	pAction->Enabled = this->LViewHistoryCh->Items->Count > 0;
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
	iLViewEndIndex = EndIndex;     //Górny zakres, elementów listy
}
//---------------------------------------------------------------------------
void __fastcall THistoryOpenChaptersWindow::LViewHistoryChDrawItem(TCustomListView *Sender,
          TListItem *Item, TRect &Rect, TOwnerDrawState State)
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
	//---
	TRect RectBounds = Item->DisplayRect(drBounds);
	TRect RectLabel = Item->DisplayRect(drLabel);
	TRect RectIcon = Item->DisplayRect(drIcon);

  if(!(Item->Index % 2)) pLView->Canvas->Brush->Color = (TColor)0x00EEEEEE;

	if(State.Contains(odSelected))
	{
		pLView->Canvas->Brush->Color = clWebDarkOrange;
	}

	pLView->Canvas->FillRect(RectBounds);
	pLView->Canvas->Font = pLView->Font;
	pLView->Canvas->Font->Style = TFontStyles() << fsBold;

	DrawText(pLView->Canvas->Handle, Item->Caption.c_str(), -1, &RectLabel, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	pLView->SmallImages->Draw(pLView->Canvas, RectIcon.Left,
		RectIcon.Top + ((Rect.Height() - pLView->SmallImages->Height) / 2), enSmallImage_ChaptItem);

	TRect RectSubItem  = RectLabel;
	for(int iColumn=0; iColumn<pLView->Columns->Count - 1; iColumn++)
	{
		//Wymiary następnej kolumny
		RectSubItem.Left += pLView->Column[iColumn]->Width;
		RectSubItem.Right += pLView->Column[iColumn + 1]->Width;

		pLView->Canvas->Font->Color = clWindowText;
		pLView->Canvas->Font->Style = TFontStyles();

		TRect RectSubItem1 = RectSubItem;
		DrawText(pLView->Canvas->Handle, Item->SubItems->Strings[iColumn].c_str(), -1, &RectSubItem1,
			DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
		pLView->SmallImages->Draw(pLView->Canvas, RectSubItem.Left - pLView->SmallImages->Width - 2,
			RectSubItem.Top + ((RectSubItem.Height() - pLView->SmallImages->Height) / 2), enSmallImage_DateItem);
	}
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

//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("Item->Caption: %s", ARRAYOFCONST((Item->Caption))));
//		GsDebugClass::WriteDebug(Format("ustrName: %s", ARRAYOFCONST((ustrName))));
//		GsDebugClass::WriteDebug(Format("ustrTest: %s", ARRAYOFCONST((ustrTest))));
//		GsDebugClass::WriteDebug(Format("iPosSpace: %d", ARRAYOFCONST((iPosSpace))));
//		GsDebugClass::WriteDebug(Format("ustrChapt: %s - %d", ARRAYOFCONST((ustrChapt, iChapt))));
//	#endif
	for(int i=0; i<GsReadBibleTextData::GsNumberBooks; i++)
	{
		pInfobook = const_cast<PInfoAllBooks>(&GsReadBibleTextData::GsInfoAllBooks[i]);
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

