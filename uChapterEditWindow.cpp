#include <vcl.h>
#pragma hdrstop

#include "uChapterEditWindow.h"
#include "uGlobalVar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TChapterEditWindow *ChapterEditWindow;
const UnicodeString GlobalHeaderRtf = UnicodeString("{\\rtf1\\ansi\\deff0{\\fonttbl{\\f0\\fnil\\fcharset238{\\*\\fname Arial;}Arial CE;}{\\f1\\fnil Arial;}}") +
																		 "{\\colortbl ;\\red0\\green0\\blue0;\\red255\\green0\\blue0;}" +
																		 "{\\*\\generator Msftedit 5.41.21.2510;}\\viewkind4\\uc1\\pard\\sa200\\sl276\\slmult1\\qc\\tx720\\tx1440\\tx2880\\tx5760\\cf1\\lang1045\\b\\f0\\fs24 Edycja wczytanego rozdziału (tylko polskie, pełne przekłady)\\b0\\f1\\line\\pard\\sa200\\sl276\\slmult1\\tx720\\tx1440\\tx2880\\tx5760\\cf2\\b\\fs18",
										custrAdressVersRtf = "\\f1\\line\\cf2\\b",
										custrVersRtf = "\\cf1\\b0\\f0",
										custrEndVersRtf = "\\cf2\\b\\f1";
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
	GsDebugClass::WriteDebug("");
#endif
#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
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
	this->pGsTabSheetClass = dynamic_cast<GsTabSheetClass *>(pTabSheet);
	if(this->pGsTabSheetClass)
	{
		this->Caption = this->pGsTabSheetClass->Caption;
  }
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
	this->pGsEditorClass = new GsEditorClass(this);
	if(!pGsEditorClass) throw(Exception("Błąd inicjalizacji objektu GsEditorClass"));
	this->pGsEditorClass->Parent = this;
	this->pGsEditorClass->Align = alClient;
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
	TList *pListTr = GsReadBibleTextData::GetListAllTrChap();
	if(!pListTr) return;
	//---
  TStringStream *pStringStream = new TStringStream("", TEncoding::ANSI, true);
	if(!pStringStream) throw(Exception("Błąd inicjalizacji objektu TStringStream"));
	//---
	unsigned char uiTranslatesIndex=0, iIndexVers=0;
	bool bExit=false;
	TRichEdit *pTRichEdit = this->pGsEditorClass->GetRichEditObject();
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
				GsReadBibleTextItem *pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(iTranslates);
				if(!pGsReadBibleTextItem) return;
				//---
				THashedStringList *pTempHSList = static_cast<THashedStringList *>(pListTr->Items[iTranslates]);
				if(!pTempHSList) return;
				//---
				if(pTempHSList->Count == 0) {uiTranslatesIndex--; continue;}
				if(iIndexVers < pTempHSList->Count)
				{
					if(pGsReadBibleTextItem->enTypeTranslate == enTypeTr_Full) //Tylko całe polskie tłumaczenia
					{
						if(!pTempHSList->Strings[iIndexVers].IsEmpty())
						{
							pStringStream->WriteString(Format("%s %s %u:%u %s \"%s\" %s" ,ARRAYOFCONST((custrAdressVersRtf, GsReadBibleTextData::GsInfoAllBooks[this->pGsTabSheetClass->_ShucIndexBook].ShortNameBook,
																																													this->pGsTabSheetClass->_ShucIndexChapt + 1, iIndexVers + 1,
																																													custrVersRtf, pTempHSList->Strings[iIndexVers], custrEndVersRtf))));
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
			if(uiTranslatesIndex > 0) pStringStream->WriteString("\\line");
			if(uiTranslatesIndex >= cucMaxCountTranslates) uiTranslatesIndex=0; //Zabezpieczenie przed przekęceniem licznika
		}while(uiTranslatesIndex > 0);
    pStringStream->WriteString("}");
		pStringStream->Position = 0;
		this->pGsEditorClass->LoadEditorFromStream(pStringStream);
	}
	__finally
	{
		if(pStringStream) delete pStringStream;
  }
	pTRichEdit->Lines->EndUpdate();
}
//---------------------------------------------------------------------------

