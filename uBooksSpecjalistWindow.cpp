#include <vcl.h>
#pragma hdrstop

#include "uBooksSpecjalistWindow.h"
#include "MyBibleLibrary\GsReadBibleTextdata.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBooksSpecjalistWindow *BooksSpecjalistWindow;
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug("");
#endif
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
*/
enum { //Tag i dla TComboBox (wyborów: Tłumaczenia, księgi, rozdziału)
 enCBoxSelect_Translate = 10,
 enCBoxSelect_Book,
 enCBoxSelect_Chapter,
 // Tagi dla przycisków
 enToolButton_Next = 20,
 enToolButton_Prev,
 // Grafika dla ikon
 enImage_Next=0,
 enImage_Prev
};
//---------------------------------------------------------------------------
__fastcall TBooksSpecjalistWindow::TBooksSpecjalistWindow(TComponent* Owner)
	: TForm(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->CBoxTranslatesList->Tag = enCBoxSelect_Translate;
	this->CBoxBoksList->Tag = enCBoxSelect_Book;
	this->CBoxChaptersList->Tag = enCBoxSelect_Chapter;

	this->ToolButtonNextChapt->Tag = enToolButton_Next;
	this->ToolButtonPrevChapt->Tag = enToolButton_Prev;

	this->pImageList16 = GsReadBibleTextData::GetImageList();
	this->WebBrowserSpecText->Navigate(WideString("about:blank").c_bstr()); // wypełnienie kontrolki pustą strony.
  // Licznik okien tlumaczeń specjalistycznych
	if(TBooksSpecjalistWindow::_siIndexSpecWindow < (GlobalVar::Global_cucMaxTranslatesSpecjalist - 1))
	{
		TBooksSpecjalistWindow::_siIndexSpecWindow++;
	}
	else TBooksSpecjalistWindow::_siIndexSpecWindow = 0;
}
//---------------------------------------------------------------------------
void __fastcall TBooksSpecjalistWindow::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsObjectItemsSpec *pGsObjectItemsSpec = GsReadBibleTextData::pGsReadBibleSpecTextClass->GetObjectItemsSpec();
	GsReadBibleTextItem *pGsReadBibleTextItem=nullptr;

	this->_pListSelectChapt = new THashedStringList();
	if(!this->_pListSelectChapt) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));
	// Tworzenie PopupMenu
	if(pGsObjectItemsSpec)
	{
		this->PMenuSelectTrSpec->Items->Clear();
		this->CBoxTranslatesList->Items->BeginUpdate();
		for(int i=0; i<pGsObjectItemsSpec->Count; ++i)
		{
			pGsReadBibleTextItem = static_cast<GsReadBibleTextItem *>(pGsObjectItemsSpec->Items[i]);
			if(pGsReadBibleTextItem)
			{
				TMenuItem *NewItem = new TMenuItem(this->PMenuSelectTrSpec);
				if(!NewItem) throw(Exception("Błąd inicjalizacji klasy TMenuItem"));
				this->PMenuSelectTrSpec->Items->Add(NewItem);
				NewItem->Caption = pGsReadBibleTextItem->NameTranslate;
				this->CBoxTranslatesList->AddItem(pGsReadBibleTextItem->NameTranslate, pGsReadBibleTextItem);
				NewItem->ImageIndex = 0;
				NewItem->Tag = 100 + i;
				NewItem->OnClick = this->_SelectTranslateSpecExecute;
			}
		}
		this->CBoxTranslatesList->Items->EndUpdate();
	}
	// Po wyborze tłumaczenia
	this->CBoxTranslatesList->ItemIndex = 0;
	this->CBoxSelectAllChange(this->CBoxTranslatesList);
	this->CBoxBoksList->ItemIndex = 0;
	this->CBoxSelectAllChange(this->CBoxBoksList);
}
//---------------------------------------------------------------------------
void __fastcall TBooksSpecjalistWindow::FormDestroy(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->_pListSelectChapt) {delete this->_pListSelectChapt; this->_pListSelectChapt = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall TBooksSpecjalistWindow::FormClose(TObject *Sender, TCloseAction &Action)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	Action = caFree;
  // Licznik okien tlumaczeń specjalistycznych
	TBooksSpecjalistWindow::_siIndexSpecWindow--;
}
//---------------------------------------------------------------------------
// AKCJE DLA MODUŁU
//---------------------------------------------------------------------------
void __fastcall TBooksSpecjalistWindow::_SelectTranslateSpecExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TMenuItem *pMenuItem = dynamic_cast<TMenuItem *>(Sender);
	if(!pMenuItem) return;
	//---
  #if defined(_DEBUGINFO_)
		GsDebugClass::WriteDebug(Format("pMenuItem: %s", ARRAYOFCONST(( pMenuItem->Caption ))));
	#endif
}
//---------------------------------------------------------------------------
void __fastcall TBooksSpecjalistWindow::CBoxSelectAllChange(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TComboBox *pCBox = dynamic_cast<TComboBox *>(Sender);
	if(!pCBox) return;
	//---
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("pCBox->Tag: %d", ARRAYOFCONST(( pCBox->Tag ))));
//	#endif
	//UnicodeString ustrVers;
	int iSelectChapt=-1;
	switch(pCBox->Tag)
	{
		case enCBoxSelect_Translate:
			{
				TStrings *pStrings = pCBox->Items;
				this->_pGsReadBibleTextItem = static_cast<GsReadBibleTextItem *>(pStrings->Objects[this->CBoxTranslatesList->ItemIndex]);
				if(this->_pGsReadBibleTextItem)
				{
					this->CBoxBoksList->Items->BeginUpdate();
					this->CBoxBoksList->Clear();
//					#if defined(_DEBUGINFO_)
//						GsDebugClass::WriteDebug(Format("this->_pGsReadBibleTextItem: %d", ARRAYOFCONST(( this->_pGsReadBibleTextItem->uiIndexTranslate ))));
//						GsDebugClass::WriteDebug(Format("this->_pGsReadBibleTextItem->ucStartBook: %d", ARRAYOFCONST(( this->_pGsReadBibleTextItem->ucStartBook ))));
//						GsDebugClass::WriteDebug(Format("this->_pGsReadBibleTextItem->ucCountBooks: %d", ARRAYOFCONST(( this->_pGsReadBibleTextItem->ucCountBooks ))));
//					#endif
					int iMaxBook = this->_pGsReadBibleTextItem->ucStartBook + this->_pGsReadBibleTextItem->ucCountBooks;
					for(int i=this->_pGsReadBibleTextItem->ucStartBook; i<iMaxBook; ++i)
					{
						this->CBoxBoksList->AddItem(GsReadBibleTextData::GsInfoAllBooks[i].FullNameBook, nullptr);
					}
					this->CBoxBoksList->Items->EndUpdate();
					this->CBoxBoksList->ItemIndex = 0;
          this->CBoxSelectAllChange(this->CBoxBoksList);
				}
			}
			break;
		//---
		case enCBoxSelect_Book:
		{
			this->CBoxChaptersList->Clear();
			if(this->_pGsReadBibleTextItem)
			{
				this->_iSelectBoks = this->_pGsReadBibleTextItem->ucStartBook + pCBox->ItemIndex;
//				#if defined(_DEBUGINFO_)
//					GsDebugClass::WriteDebug(Format("ucCountChapt: %d", ARRAYOFCONST(( GsReadBibleTextData::GsInfoAllBooks[iSelectBoks].ucCountChapt ))));
//					GsDebugClass::WriteDebug(Format("pCBox->ItemIndex: %d", ARRAYOFCONST(( iSelectBoks ))));
//				#endif
				this->CBoxChaptersList->Items->BeginUpdate();
				for(int i=0; i<GsReadBibleTextData::GsInfoAllBooks[this->_iSelectBoks].ucCountChapt; ++i)
				{
					this->CBoxChaptersList->AddItem(Format("Rozdział: %d", ARRAYOFCONST(( i + 1))), nullptr);
				}
				this->CBoxChaptersList->Items->EndUpdate();
				this->CBoxChaptersList->ItemIndex = 0;
				this->CBoxSelectAllChange(this->CBoxChaptersList);
			}
    }
		break;
		//---
		case enCBoxSelect_Chapter:
			if((this->CBoxTranslatesList->ItemIndex > -1) && (this->CBoxBoksList->ItemIndex > -1) && (this->_iSelectBoks > -1))
			{
				this->_pListSelectChapt->BeginUpdate();
				this->_pListSelectChapt->Clear();
				THashedStringList *HSList = GsReadBibleTextData::pGsReadBibleTextClass->GetSelectBookTranslate(
					this->_pGsReadBibleTextItem->uiIndexTranslate, this->_iSelectBoks);
				for(int i=0; i<HSList->Count; ++i) // Usunięcie zakodowanych adresów, wersetów
				{
					iSelectChapt = HSList->Strings[i].SubString(4, 3).ToInt();
//          #if defined(_DEBUGINFO_)
//						GsDebugClass::WriteDebug(Format("%d: %s", ARRAYOFCONST(( i, ustrVers))));
//					#endif
					if(iSelectChapt == pCBox->ItemIndex + 1)
						{this->_pListSelectChapt->AddObject(HSList->Strings[i].Delete0(0, 10), HSList->Objects[i]);}
				}
        this->_pListSelectChapt->EndUpdate();

				this->STextInfoLoaded->Caption = Format("%s - %s, rozdział: %d", ARRAYOFCONST(( this->_pGsReadBibleTextItem->NameTranslate,
						 GsReadBibleTextData::GsInfoAllBooks[this->_iSelectBoks].FullNameBook, pCBox->ItemIndex + 1)));

				DataDisplayTextAnyBrowser SetDataDisplay;
				SecureZeroMemory(&SetDataDisplay, sizeof(DataDisplayTextAnyBrowser));
				SetDataDisplay.strBackgroundColor = GlobalVar::Global_ColorsAllTranslates[TBooksSpecjalistWindow::_siIndexSpecWindow - 1];//[19-05-2024]
				SetDataDisplay.strNameFont = "Times New Roman";
				SetDataDisplay.iSizeFont = 14;
				SetDataDisplay.pMemoryStream = nullptr;
				SetDataDisplay.bIsHorizontLine = false;

				GsReadBibleTextData::pGsReadBibleTextClass->_ViewSListBibleToHTML(this->WebBrowserSpecText,
					this->_pListSelectChapt, SetDataDisplay);
        // Stany przycisków przewijania, zależnie od wyswietlanego rozdziału //[17-05-2024]
				this->ToolButtonPrevChapt->Enabled = (this->CBoxChaptersList->ItemIndex > 0);
				this->ToolButtonNextChapt->Enabled = (this->CBoxChaptersList->ItemIndex < this->CBoxChaptersList->Items->Count - 1);
			}
			break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TBooksSpecjalistWindow::ToolButtonChaptClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TToolButton *pTButton = dynamic_cast<TToolButton *>(Sender);
	if(!pTButton) return;
	//---
	const int ciMaxChapt = this->CBoxChaptersList->Items->Count,
						ciMaxBook = this->CBoxBoksList->Items->Count,
						ciMaxTranslates = this->CBoxTranslatesList->Items->Count;

	switch(pTButton->Tag)
	{
		case enToolButton_Next:
		{
			if(this->CBoxChaptersList->ItemIndex < ciMaxChapt - 1)
			{
        this->CBoxChaptersList->ItemIndex++;
      }
    }
		break;
		//---
		case enToolButton_Prev:
		{
			if(this->CBoxChaptersList->ItemIndex > 0)
			{
				this->CBoxChaptersList->ItemIndex--;
			}
		}
		break;
	}
	this->CBoxSelectAllChange(this->CBoxChaptersList);
}
//---------------------------------------------------------------------------

