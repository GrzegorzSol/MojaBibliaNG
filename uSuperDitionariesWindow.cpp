#include <vcl.h>
#pragma hdrstop

#include "uSuperDitionariesWindow.h"
#include "MyBibleLibrary\GsReadBibleTextdata.h"
#include <System.StrUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSuperDitionariesWindow *SuperDitionariesWindow;
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug("");
#endif
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
*/
enum {
	enStrongType_Grec=1000, enStrongType_Hbr,
	enCList_Strong=1100, enCList_Apperances,
	enIcon16_Apper=0, enIcon16_StrongNumbers,
	enIcon32_StrongGrek=0, enIcon32_StrongHbr
};

const UnicodeString custrHeadTransHTMLpre1 = UnicodeString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n") +
																		"<html>\n<head>\n" +
																		"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">" +// !!!
																		"<title>Tłumaczenie wybranego słowa</title>\n" +
																		"<style type=\"text/css\">\n" +
																		Format(".styleFound {background-color: %s;}\n", ARRAYOFCONST(( RGBToWebColorStr(clWebYellow) ))) +
																		".styleStrongWord {color: #FF0000;vertical-align: super;font-size: 42px;font-weight: bold;display: block;" +
																				"width: auto;margin-left: auto;margin-right: auto;text-align: center;}\n" +
																		".styleDescription {color: #0000FF;font-size: 24px;font-weight: bold;}\n",
                    custrHeadText = UnicodeString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n") +
																		"<html>\n<head>\n" +
																		"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">" +// !!!
																		"<title>Tekst interlinearny grecko-polski</title>\n" +
																		"<style type=\"text/css\">\n" +
																		Format(".styleFound {background-color: %s;}\n", ARRAYOFCONST(( RGBToWebColorStr(clWebYellow) ))) +
																		".styleNumber {color: #FF0000;vertical-align: super;font-size: small;font-weight: bold;}\n" +
																		Format("body {background-color: %s;font-size: x-large;}\n", ARRAYOFCONST(( RGBToWebColorStr(clWebLavender) )))  +
																		"</style>\n</head>\n<body>\n",
										custrEndHTML = "\n</body>\n</html>";
UnicodeString custrHeadTransHTML;
const unsigned char cucDelimit = ' '; // Znak cięcia lini
//---------------------------------------------------------------------------
__fastcall TSuperDitionariesWindow::TSuperDitionariesWindow(TComponent* Owner)
	: TForm(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	UnicodeString ustrConvertPathImage = StringReplace(GlobalVar::Global_custrPathBackgroundSDict, "\\", "\\\\", TReplaceFlags() << rfReplaceAll),
								ustrBackGround = Format(UnicodeString("body {background-image: url(\"%s\");\n") +
								"\tfont-size: x-large;}",
									ARRAYOFCONST((ustrConvertPathImage)));

	custrHeadTransHTML = Format("%s\n%s\n</style>\n</head>\n<body>\n",
		ARRAYOFCONST((custrHeadTransHTMLpre1, ustrBackGround)));

	this->ControlListStrong->Tag = enCList_Strong;
	this->ControlListApperances->Tag = enCList_Apperances;

	this->ActionGrec->Tag = enStrongType_Grec;
	this->ActionHbr->Tag = enStrongType_Hbr;
}
//---------------------------------------------------------------------------
void __fastcall TSuperDitionariesWindow::FormShow(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->ControlListStrong->ItemCount = ciMaxStrongGrecCount - 1;
	this->ControlListStrong->ItemIndex = 0;
	this->LabelInfoDictionary->Caption = "Grecko-Polski";
	this->ControlListStrong->ItemHeight = 2 * -this->ControlListStrong->Font->Height;
	this->ControlListApperances->ItemHeight = this->ControlListStrong->ItemHeight;
	this->WebBrowserImpotance->Navigate(WideString("about:blank").c_bstr()); // wypełnienie kontrolki pustą strony
	this->WebBrowserVers->Navigate(WideString("about:blank").c_bstr()); // wypełnienie kontrolki pustą strony.
	this->ControlListStrongItemClick(this->ControlListStrong);

  // Wyszukanie konkretnego tłumaczenia //[09-06-2024]
	int iCountTrans = GsReadBibleTextData::CountTranslates();
	UnicodeString ustrNameTrans;
	const UnicodeString custrFindNameTransGrec = "TRO+",
											custrFindNameTransHebr = "IBHP+"; // [31-07-2024]
  for(int i=0; i<iCountTrans; ++i)
	{
		GsReadBibleTextData::GetInfoNameTranslate(i, ustrNameTrans);
		if(ustrNameTrans == custrFindNameTransGrec)
		{
			this->_iNumberTranslateGrec = i;
		}
		if(ustrNameTrans == custrFindNameTransHebr) // [31-07-2024]
		{
			this->_iNumberTranslateHbr = i;
		}
  }
}
//---------------------------------------------------------------------------
void __fastcall TSuperDitionariesWindow::FormClose(TObject *Sender, TCloseAction &Action)
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
void __fastcall TSuperDitionariesWindow::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_pManagerSuperDictionaries = new ManagerSuperDictionaries(GlobalVar::Global_custrPathGrecSuperDictionary,
		GlobalVar::Global_custrPathHbrSuperDictionary);
	if(!this->_pManagerSuperDictionaries) throw(Exception("Błąd inicjalizacji objektu ManagerSuperDictionarys"));

  // Lista wystąpień dla wybranego słowa
	this->_pHListVerses = new THashedStringList();
	if(!this->_pHListVerses) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));
	this->_pHListVerses->Delimiter = cucDelimit;
	this->_pHListVerses->StrictDelimiter = true;

	this->_pManagerSuperDictionaries->ReadGrecDictionary();
	this->_pManagerSuperDictionaries->ReadHbrDictionary();
}
//---------------------------------------------------------------------------
void __fastcall TSuperDitionariesWindow::FormDestroy(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if(this->_pHListVerses) {delete this->_pHListVerses; this->_pHListVerses = nullptr;}
	if(this->_pManagerSuperDictionaries) {delete this->_pManagerSuperDictionaries; this->_pManagerSuperDictionaries = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall TSuperDitionariesWindow::ActionTypeStrongExecute(TObject *Sender)
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
	//this->ControlListStrong->ItemIndex = -1; // Nowe wyszukiwanie więc brak zaznaczonego elementu
	//this->_pHListVerses->Clear();

	switch(pAction->Tag)
	{
		case enStrongType_Grec:
			this->ControlListStrong->ItemCount = ciMaxStrongGrecCount - 1;
			this->LabelInfoDictionary->Caption = "Grecko-Polski";
		break;
		//---
		case enStrongType_Hbr:
			this->ControlListStrong->ItemCount = ciMaxStrongHbrCount - 1;
			this->LabelInfoDictionary->Caption = "Hebrajsko-Polski";
		break;
	}
	this->ControlListStrongItemClick(this->ControlListStrong);
}
//---------------------------------------------------------------------------
void __fastcall TSuperDitionariesWindow::ControlListStrongBeforeDrawItem(int AIndex,
					TCanvas *ACanvas, TRect &ARect, TOwnerDrawState AState)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if((AIndex < 0) || (AIndex >= this->ControlListStrong->ItemCount)) return;
	//---
	if(this->ActionGrec->Checked)
	{
		this->LabelStrongNumber->Caption = Format("G%d", ARRAYOFCONST((AIndex + 1)));
	}
	else
	{
		this->LabelStrongNumber->Caption = Format("H%d", ARRAYOFCONST((AIndex + 1)));
	}
	this->ImageListSmall->GetIcon(enIcon16_StrongNumbers, this->ImageStrongNumbers->Picture->Icon);
}
//---------------------------------------------------------------------------
void __fastcall TSuperDitionariesWindow::ControlListStrongItemClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TControlList *pCList = dynamic_cast<TControlList *>(Sender);
	if(!pCList) return;
	//---
	if(pCList->ItemIndex == -1) return;
	//---
	SuperDictionaryItemGrec *pSuperDictionaryItemGrec=nullptr;
	SuperDictionaryItemHbr *pSuperDictionaryItemHbr=nullptr;

  this->WebBrowserVers->Navigate(WideString("about:blank").c_bstr()); // wypełnienie kontrolki pustą strony.
	this->ControlListApperances->ItemIndex = -1; // Nowe wyszukiwanie więc brak zaznaczonego elementu
	this->_pHListVerses->BeginUpdate();
	this->_pHListVerses->Clear();

	TStringStream *pStringStream = new TStringStream("", TEncoding::UTF8, true); //Allokacja strumienia dla tekstu html
  if(!pStringStream) throw(Exception("Błąd inicjalizacji objektu TStringStream"));

	// Wyświetlenie tłumaczenia wyszukanego słowa
	pStringStream->WriteString(custrHeadTransHTML); //Zapis nagłówka kodu html do strumienia
  if(this->ActionGrec->Checked)
	{
		pSuperDictionaryItemGrec = this->_pManagerSuperDictionaries->GetStrongGrec(pCList->ItemIndex + 1);
		pStringStream->WriteString(Format("<span class=\"styleStrongWord\">%s</span>", ARRAYOFCONST((pSuperDictionaryItemGrec->ustrGrecWord))));
		pStringStream->WriteString(Format("<p><span class=\"styleDescription\">Wymowa: </span>%s</p>", ARRAYOFCONST((pSuperDictionaryItemGrec->ustrPhonetically))));
		pStringStream->WriteString(Format("<p><span class=\"styleDescription\">Gramatyka: </span>%s</p>", ARRAYOFCONST((pSuperDictionaryItemGrec->ustrGrammForm))));
		pStringStream->WriteString(Format("<p><span class=\"styleDescription\">Ilość wystąpień: </span>%s</p>", ARRAYOFCONST((pSuperDictionaryItemGrec->ustrNumberApp))));
		pStringStream->WriteString(Format("<p><span class=\"styleDescription\">Pochodzenie: </span>%s</p>", ARRAYOFCONST((pSuperDictionaryItemGrec->ustrOrigin))));
		pStringStream->WriteString(Format("<p><span class=\"styleDescription\">Tłumaczenie: </span>%s</p>", ARRAYOFCONST((pSuperDictionaryItemGrec->ustrTranslate))));
		// Wyodrębnianie miejsca wystapień wybranego słowa greckiego
		this->_pHListVerses->DelimitedText = pSuperDictionaryItemGrec->ustrApperDecode;
	}
	else
	{
		pSuperDictionaryItemHbr = this->_pManagerSuperDictionaries->GetStrongHbr(pCList->ItemIndex + 1);
		pStringStream->WriteString(Format("<span class=\"styleStrongWord\">%s</span>", ARRAYOFCONST((pSuperDictionaryItemHbr->ustrHbrWord))));
		pStringStream->WriteString(Format("<p><span class=\"styleDescription\">Wymowa: </span>%s</p>", ARRAYOFCONST((pSuperDictionaryItemHbr->ustrPhonetically))));
		pStringStream->WriteString(Format("<p><span class=\"styleDescription\">Gramatyka: </span>%s</p>", ARRAYOFCONST((pSuperDictionaryItemHbr->ustrGrammForm))));
		pStringStream->WriteString(Format("<p><span class=\"styleDescription\">Ilość wytąpień: </span>%s</p>", ARRAYOFCONST((pSuperDictionaryItemHbr->ustrNumberApp))));
		pStringStream->WriteString(Format("<p><span class=\"styleDescription\">Tłumaczenie 1: </span>%s</p>", ARRAYOFCONST((pSuperDictionaryItemHbr->ustrTranslate1))));
		pStringStream->WriteString(Format("<p><span class=\"styleDescription\">Tłumaczenie 2: </span>%s</p>", ARRAYOFCONST((pSuperDictionaryItemHbr->ustrTranslate2))));
    // Wyodrębnianie miejsca wystapień wybranego słowa greckiego
		this->_pHListVerses->DelimitedText = pSuperDictionaryItemHbr->ustrApperDecode;
	}
  this->_pHListVerses->EndUpdate();
	this->ControlListApperances->ItemCount = this->_pHListVerses->Count;
//  #if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("this->_pHListVerses->Count: \"%d\"", ARRAYOFCONST((this->_pHListVerses->Count))));
//    GsDebugClass::WriteDebug(Format("\"%s\"", ARRAYOFCONST((this->_pHListVerses->Strings[0]))));
//	#endif

	pStringStream->WriteString(custrEndHTML);
	pStringStream->Position = 0;

  IPersistStreamInit *psi;
	_di_IStream sa(*(new TStreamAdapter(pStringStream, soReference)));
	if(SUCCEEDED(this->WebBrowserImpotance->Document->QueryInterface(IID_IPersistStreamInit, (void **)&psi)))
		{psi->Load(sa);}

  if(pStringStream) {delete pStringStream; pStringStream = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall TSuperDitionariesWindow::ControlListApperancesBeforeDrawItem(int AIndex,
					TCanvas *ACanvas, TRect &ARect, TOwnerDrawState AState)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if((AIndex < 0) || (AIndex >= this->ControlListStrong->ItemCount)) return;
	//---
	if(this->_pHListVerses->Strings[AIndex] != "None")
	{
  	int iBook=0, iChapt=0, iVers=0;
  	UnicodeString ustrAdress = this->_pHListVerses->Strings[AIndex];

  	iBook = ustrAdress.SubString(1, 3).ToIntDef(0);
  	iChapt = ustrAdress.SubString(4, 3).ToIntDef(0);
  	iVers = ustrAdress.SubString(7, 3).ToIntDef(0);

  	this->LabelApperances->Caption = Format("%s %d:%d",
			ARRAYOFCONST((AppCTable_InfoAllBooks[iBook - 1].ShortNameBook, iChapt, iVers )));
	}
	else
		{this->LabelApperances->Caption = this->_pHListVerses->Strings[AIndex];}

	this->ImageListSmall->GetIcon(enIcon16_Apper, this->ImageVers->Picture->Icon);
}
//---------------------------------------------------------------------------
void __fastcall TSuperDitionariesWindow::ControlListApperancesItemClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  TControlList *pCList = dynamic_cast<TControlList *>(Sender);
	if(!pCList) return;
	//---
	if(pCList->ItemIndex == -1) return;
	//---
  int iBook=0, iChapt=0, iVers=0;
	UnicodeString ustrSelectVers = this->_pHListVerses->Strings[pCList->ItemIndex],
								ustrAdress;

//  #if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("ItemIndex: \"%s\"", ARRAYOFCONST((ustrSelectVers))));
//	#endif

	TStringStream *pStringStream = new TStringStream("", TEncoding::UTF8, true); //Allokacja strumienia dla tekstu html
	if(!pStringStream) throw(Exception("Błąd inicjalizacji objektu TStringStream"));
  // Wypisanie adresu wersetu w formie czytelnej
	iBook = ustrSelectVers.SubString(1, 3).ToIntDef(1);
	iChapt = ustrSelectVers.SubString(4, 3).ToIntDef(1);
	iVers = ustrSelectVers.SubString(7, 3).ToIntDef(1);
  ustrAdress = Format("%s %d:%d",
		ARRAYOFCONST((AppCTable_InfoAllBooks[iBook - 1].ShortNameBook, iChapt, iVers )));

  if(this->ActionGrec->Checked)
	{
		GsReadBibleTextData::GetTextVersOfAdress(iBook-1, iChapt, iVers, this->_iNumberTranslateGrec, ustrSelectVers);
    ustrSelectVers = this->_SelectVersWordGrec(ustrSelectVers);
	}
	else
	{
		GsReadBibleTextData::GetTextVersOfAdress(iBook-1, iChapt, iVers, this->_iNumberTranslateHbr, ustrSelectVers);
    ustrSelectVers = this->_SelectVersWordHbr(ustrSelectVers);
	}

  pStringStream->WriteString(custrHeadText); //Zapis nagłówka kodu html do strumienia
	pStringStream->WriteString(Format("%s %s", ARRAYOFCONST(( ustrAdress, ustrSelectVers ))));

	pStringStream->WriteString(custrEndHTML);
	pStringStream->Position = 0;

	IPersistStreamInit *psi;
	_di_IStream sa(*(new TStreamAdapter(pStringStream, soReference)));
	if(SUCCEEDED(this->WebBrowserVers->Document->QueryInterface(IID_IPersistStreamInit, (void **)&psi)))
		{psi->Load(sa);}

  if(pStringStream) {delete pStringStream; pStringStream = nullptr;}
}
//---------------------------------------------------------------------------
UnicodeString __fastcall TSuperDitionariesWindow::_SelectVersWordGrec(const UnicodeString &_custrIn)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  const UnicodeString custrStyleFStart="<span class=\"styleFound\">",
											custrStyleFStop="</span>";
	UnicodeString ustrOp=_custrIn,
								ustrOut,
								ustrModify;
	int iFind=0;

	// Podmiana na "</m>#"
	ustrOp = StringReplace(ustrOp, "</m> ", "</m>#", TReplaceFlags() << rfReplaceAll);
	// Podział wersetu na części kończace sie na "#". I stworzenie tablicy dynamicznej
	DynamicArray daWord = Strutils::SplitString(ustrOp, "#");

	for(int i=0; i<daWord.Length; ++i)
	{
		if(!daWord[i].IsEmpty())
		{
      // Wstawienie numeru słowa //[22-06-2024]
			daWord[i] = Format("<span class=\"styleNumber\">%d</span>%s", ARRAYOFCONST(( i+1, daWord[i] )));
			// w celu "pocięcia" wersetu na tłumaczenia pojedyńczych słów
			// Próba znalezienia kodu Stronga z przyległymi kodami html
			iFind = daWord[i].Pos(Format(" <font color=\"green\"><sup>%s</sup></font> ",
				ARRAYOFCONST(( UnicodeString(this->ControlListStrong->ItemIndex + 1) ))));

			if(iFind > 0)
			{
				// Jeśli znaleziono opis słowa o numerze szukanym
				// Dodanie do słowa znalezionego kodu html zmieniający podkład pod napisem
				ustrModify = Format("%s%s%s", ARRAYOFCONST(( custrStyleFStart, daWord[i], custrStyleFStop )));
				// Podmiana oryginalnego definicji słowa, podkoloryzowaną wersją //[22-06-2024]
				daWord[i] = StringReplace(daWord[i], daWord[i], ustrModify, TReplaceFlags());
			}
			// Ponowne dodanie wszystkich, wczesniej pociętych podciągów //[22-06-2024]
			ustrOut += daWord[i] + " ";
		}
	}

	return ustrOut;
}
//---------------------------------------------------------------------------
UnicodeString __fastcall TSuperDitionariesWindow::_SelectVersWordHbr(const UnicodeString &_custrIn)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  const UnicodeString custrStyleFStart="<span class=\"styleFound\">",
											custrStyleFStop="</span>";
	UnicodeString ustrOp=_custrIn,
								ustrOut,
								ustrModify,
								ustrTo;
	int iFind=0;
  // [02-08-2024]
	iFind = ustrOp.Pos(UnicodeString(this->ControlListStrong->ItemIndex + 1));

	if(iFind > 0)
	{
		ustrModify = Format("<sup>%s%s%s",
			ARRAYOFCONST(( custrStyleFStart, UnicodeString(this->ControlListStrong->ItemIndex + 1), custrStyleFStop )));
		ustrTo = Format("<sup>%s", ARRAYOFCONST(( UnicodeString(this->ControlListStrong->ItemIndex + 1) )) );
		ustrOut = StringReplace(ustrOp, ustrTo, ustrModify, TReplaceFlags());
	}

	return ustrOut;
}
//---------------------------------------------------------------------------
