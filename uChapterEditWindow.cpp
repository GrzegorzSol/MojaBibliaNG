#include <vcl.h>
#pragma hdrstop

#include "uChapterEditWindow.h"
#include "uGlobalVar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TChapterEditWindow *ChapterEditWindow;
const UnicodeString GlobalSizeFontText = "\\fs20",
										GlobalHeaderRtf = UnicodeString("{\\rtf1\\ansi\\deff0{\\fonttbl{\\f0\\fnil\\fcharset238{\\*\\fname Arial;}Arial CE;}{\\f1\\fnil Arial;}}") +
																		 "{\\colortbl ;\\red0\\green0\\blue0;\\red255\\green0\\blue0;\\red0\\green255\\blue0;\\red0\\green0\\blue255;}" +
																		 "{\\*\\generator Msftedit 5.41.21.2510;}\\viewkind4\\uc1\\pard\\sa200\\sl276\\slmult1\\qc\\tx720\\tx1440\\tx2880\\tx5760\\cf1\\lang1045\\b\\f0\\fs24 Edycja wczytanego rozdziału (tylko polskie, pełne przekłady)\\b0\\f1\\line\\pard\\sa200\\sl276\\slmult1\\tx720\\tx1440\\tx2880\\tx5760\\cf2\\b" + GlobalSizeFontText,
										GlobalAdressVersRtf = "\\f1\\line\\cf2\\b",
										GlobalVersRtf = "\\cf1\\b0\\f0",
										GlobalNameTransRtf = "\\cf4\\f1",
										GlobalEndVersRtf = "\\cf1\\f1",
										GlobalSizeNameTransRtf = "\\fs16";
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
	GsDebugClass::WriteDebug("");
#endif
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
*/
//---------------------------------------------------------------------------
__fastcall TChapterEditWindow::TChapterEditWindow(TComponent* Owner, TTabSheet *pTabSheet)
	: TForm(Owner)
/**
	OPIS METOD(FUNKCJI): Metoda tworząca główne okno
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_pGsTabSheetClass = dynamic_cast<GsTabSheetClass *>(pTabSheet);
	if(this->_pGsTabSheetClass)
	{
		this->Caption = this->_pGsTabSheetClass->Caption;
	}
	this->_iGetTranslate = this->_pGsTabSheetClass->GetTabSet()->TabIndex; //Numer aktualnie wyświetlanego tłumaczenia w zakładce z tekstem
}
//---------------------------------------------------------------------------
void __fastcall TChapterEditWindow::FormClose(TObject *Sender, TCloseAction &Action)
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
void __fastcall TChapterEditWindow::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_pGsEditorClass = new GsEditorClass(this);
	if(!this->_pGsEditorClass) throw(Exception("Błąd inicjalizacji objektu GsEditorClass"));
	this->_pGsEditorClass->Parent = this;
	this->_pGsEditorClass->Align = alClient;
}
//---------------------------------------------------------------------------
void __fastcall TChapterEditWindow::FormDestroy(TObject *Sender)
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
void __fastcall TChapterEditWindow::FormActivate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TList *pListTr = GsReadBibleTextData::GetListAllTrChap(); //Lista wszystkich tekstów z wybranego rozdziału
	if(!pListTr) return;
	//---
  TStringStream *pStringStream = new TStringStream("", TEncoding::ANSI, true);
	if(!pStringStream) throw(Exception("Błąd inicjalizacji objektu TStringStream"));
	//---
	unsigned char uiTranslatesIndex, iIndexVers=0;
	//bool bExit=false;
	TRichEdit *pTRichEdit = this->_pGsEditorClass->GetRichEditObject();
	if(!pTRichEdit) return;
	pTRichEdit->Lines->BeginUpdate();
	//---
	try
	{
		pStringStream->WriteString(GlobalHeaderRtf);
		do
		{
			uiTranslatesIndex = static_cast<unsigned char>(pListTr->Count);
			for(int iTranslates=0; iTranslates<pListTr->Count; iTranslates++)
			{
				//Wyłuskanie wskaźnika na wybrane tłumaczenie
				GsReadBibleTextItem *pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(iTranslates);
				if(!pGsReadBibleTextItem) return;
				//Wyłuskanie wskaźnika na THashedStringList z tekstem konkretnego tłumaczenia, z wybranego rozdziału
				THashedStringList *pTempHSList = static_cast<THashedStringList *>(pListTr->Items[iTranslates]);
				if(!pTempHSList) return;
				//---
				//if(pTempHSList->Count == 0) {uiTranslatesIndex--; continue;}
				//if((this->_iGetTranslate > 0) && ((this->_iGetTranslate - 1) != iTranslates)) {uiTranslatesIndex--; continue;}
				if((pTempHSList->Count == 0) || ((this->_iGetTranslate > 0) && ((this->_iGetTranslate - 1) != iTranslates))) {uiTranslatesIndex--; continue;}
				if(iIndexVers < pTempHSList->Count)
				{
					if(pGsReadBibleTextItem->enTypeTranslate == enTypeTr_Full) //Tylko całe polskie tłumaczenia
					{
						if(!pTempHSList->Strings[iIndexVers].IsEmpty())
						{
							pStringStream->WriteString(Format("%s %s %u:%u %s %s%s%s%s [%s]%s" ,ARRAYOFCONST((GlobalAdressVersRtf, GsReadBibleTextData::GsInfoAllBooks[this->_pGsTabSheetClass->_ShucIndexBook].ShortNameBook,
								this->_pGsTabSheetClass->_ShucIndexChapt + 1, iIndexVers + 1, GlobalVersRtf, pTempHSList->Strings[iIndexVers],
								GlobalEndVersRtf, GlobalNameTransRtf, GlobalSizeNameTransRtf, pGsReadBibleTextItem->NameTranslate, GlobalSizeFontText))));
						}
					}
					else uiTranslatesIndex--;
				}
				else
				//Dotarłem do ostatniego wersetu danego tłumaczenia
				{
					uiTranslatesIndex--;
				}
			}

			iIndexVers++;
			if(this->_iGetTranslate == 0)
      //Jeśli wybrane konkretne tłumaczenie to nie wstawiać  przerw pustej lini
			{
				if(uiTranslatesIndex > 0) pStringStream->WriteString("\\line");
			}
			if(uiTranslatesIndex >= cucMaxCountTranslates) uiTranslatesIndex=0; //Zabezpieczenie przed przekęceniem licznika
		}while(uiTranslatesIndex > 0);
    pStringStream->WriteString("}");
		pStringStream->Position = 0;
		this->_pGsEditorClass->LoadEditorFromStream(pStringStream);
	}
	__finally
	{
		if(pStringStream) delete pStringStream;
  }
	pTRichEdit->Lines->EndUpdate();
	return;
}
//---------------------------------------------------------------------------

