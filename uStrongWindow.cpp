#include <vcl.h>
#pragma hdrstop

#include "uStrongWindow.h"
#include <System.IOUtils.hpp>
#include "MyBibleLibrary\MyBibleLibrary.h"
#include "MyBibleLibrary\GsReadBibleTextdata.h"
#include "uGlobalVar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
// Maksymalne numery dla słow greckich i hebrajskich
const int ciMaxNumHebr=8674, // https://pl.wikipedia.org/wiki/Konkordancja_Stronga
					ciMaxNumGrec=5624, // https://pl.wikipedia.org/wiki/Konkordancja_Stronga
// Inne stałe
					ciOffsetTextStrong=5; // Od którego miejsca zaczyna się słownik, po numerze słowa
enum {// Numery ikon
	enImage_Search, //0.Ikona wyszukiwania
	enSelect_Hebr=0,
	enSelect_Grec
 };
// Przedrostki do numeru Stronga
const UnicodeString custrSelectPre[] = {"H", "G"}, // [07-06-2024]
										// Wybór słownika
										custrSelectDict[] = {"Hebrajsko-Polski", "Grecko-Polski"},
										custrHeadHTML = UnicodeString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n") +
																		"<html>\n<head>\n" +
																		"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">" +// !!!
																		"<title></title>\n" +
																		"<style type=\"text/css\">\n" +
																		Format(".styleFound {background-color: %s;}\n", ARRAYOFCONST(( RGBToWebColorStr(clWebYellow) ))) +
																		"body {background-color:#FFFACD;font-size: x-large;}\n" +
																		"</style>\n</head>\n<body>\n",
										custrEndHTML = "\n</body>\n</html>";
const unsigned char cucDelimit = '#'; // Znak cięcia lini

TStrongWindow *StrongWindow;
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug("");
#endif
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
*/
//---------------------------------------------------------------------------
__fastcall TStrongWindow::TStrongWindow(TComponent* Owner)
	: TForm(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->CBoxSelectDict->Items->BeginUpdate();
	for(int i=0; i<ARRAYSIZE(custrSelectDict); ++i)
		{this->CBoxSelectDict->Items->Add(custrSelectDict[i]);}
	// Domyślnie aktywny pierwszy element, czyli słownik hebrajsko-polski
	this->CBoxSelectDict->ItemIndex = enSelect_Hebr;
	this->CBoxSelectDict->OnChange(this->CBoxSelectDict);
	this->CBoxSelectDict->Items->EndUpdate();
	this->LEditSearchNumberStr->MaxLength = 5;

	this->WebBrowserStrong->Navigate(WideString("about:blank").c_bstr()); // wypełnienie kontrolki pustą strony.
	this->WebBrowserVers->Navigate(WideString("about:blank").c_bstr()); // wypełnienie kontrolki pustą strony.
	// Wyszukanie konkretnego tłumaczenia //[09-06-2024]
	int iCountTrans = GsReadBibleTextData::CountTranslates();
	UnicodeString ustrNameTrans;
	//const UnicodeString custrFindNameTrans = "ELZEVIR TEXTUS RECEPTUS (1624)";
	const UnicodeString custrFindNameTrans = "TRO+";

	for(int i=0; i<iCountTrans; ++i)
	{
		GsReadBibleTextData::GetInfoNameTranslate(i, ustrNameTrans);
		if(ustrNameTrans == custrFindNameTrans)
		{
			this->_iNumberTranslate = i;
			break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TStrongWindow::FormClose(TObject *Sender, TCloseAction &Action)
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
void __fastcall TStrongWindow::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	// Lista z danymi Stronga// [05-06-2024]
	this->_pHSListStrong = new THashedStringList();
	if(!this->_pHSListStrong) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));
	// Lista z danymi wystapień w wersetach, poszczególnych słów // [08-06-2024]
	this->_pHListWordInVersesExist = new THashedStringList();
	if(!this->_pHListWordInVersesExist) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));
	// Lista wystąpień dla wybranego słowa
	this->_pHListVerses = new THashedStringList();
	if(!this->_pHListVerses) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));
	this->_pHListVerses->Delimiter = cucDelimit;
	this->_pHListVerses->StrictDelimiter = true;

	// Plik z danymi Stronga// [05-06-2024]
	if(!TFile::Exists(GlobalVar::Global_custrPathStrongDict))
		throw(Exception("Brak pliku ze słownikiem Stronga!"));
	this->_pHSListStrong->LoadFromFile(GlobalVar::Global_custrPathStrongDict, TEncoding::UTF8);
	// Plik z danymi wystapień w wersetach, poszczególnych słów // [08-06-2024]
	if(!TFile::Exists(GlobalVar::Global_custrPathFileWordVersesExist))
		throw(Exception("Brak pliku ze słownikiem Stronga!"));
	this->_pHListWordInVersesExist->LoadFromFile(GlobalVar::Global_custrPathFileWordVersesExist, TEncoding::UTF8);
}
//---------------------------------------------------------------------------
void __fastcall TStrongWindow::FormDestroy(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->_pHSListStrong) {delete this->_pHSListStrong; this->_pHSListStrong = nullptr;}
	if(this->_pHListWordInVersesExist) {delete this->_pHListWordInVersesExist; this->_pHListWordInVersesExist = nullptr;}
	if(this->_pHListVerses) {delete this->_pHListVerses; this->_pHListVerses = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall TStrongWindow::_AllClear()
/**
	OPIS METOD(FUNKCJI): Czysczenie wszystkiego
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!this->Visible) return;
	this->WebBrowserStrong->Navigate(WideString("about:blank").c_bstr()); // wypełnienie kontrolki pustą strony.
	this->WebBrowserVers->Navigate(WideString("about:blank").c_bstr()); // wypełnienie kontrolki pustą strony.
	this->ControlListVerses->ItemCount = 0;
	this->_pHListVerses->Clear();
	this->STextInfos->Caption = "";
}
//-------------------------- AKCJE I ZDARZENIA ------------------------------
void __fastcall TStrongWindow::CBoxSelectDictChange(TObject *Sender)
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
	this->ButtStartSearch->Enabled = ((pCBox->ItemIndex > -1) && !this->LEditSearchNumberStr->Text.IsEmpty());
	this->LEditSearchNumberStr->Text = custrSelectPre[pCBox->ItemIndex];
  // Czyszczenie wszystkiego
	this->_AllClear();
}
//---------------------------------------------------------------------------
void __fastcall TStrongWindow::LEditSearchNumberStrChange(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TLabeledEdit *pLEdit = dynamic_cast<TLabeledEdit *>(Sender);
	if(!pLEdit) return;
	//--- zabezpieczenie przed wprowadzeniem niewłaściwego numeru słoa
	this->_iSearchNumber = pLEdit->Text.SubString1(2, 4).ToIntDef(0); // [07-06-2024]
//  #if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("this->iSearchNumber: %d", ARRAYOFCONST(( this->iSearchNumber ))));
//	#endif
	if(this->CBoxSelectDict->ItemIndex == enSelect_Hebr)
	{
		if((this->_iSearchNumber > ciMaxNumHebr) || (this->_iSearchNumber < 1))
		{
			this->ButtStartSearch->Enabled = false;
      return;
		}
	}
	else if(this->CBoxSelectDict->ItemIndex == enSelect_Grec)
	{
		if((this->_iSearchNumber > ciMaxNumGrec) || (this->_iSearchNumber < 1))
		{
			this->ButtStartSearch->Enabled = false;
			return;
    }
	}
	//--- Zabezpieczenie przed brakiem wyboru typu słownika
	this->ButtStartSearch->Enabled = (this->CBoxSelectDict->ItemIndex > -1);
}
//---------------------------------------------------------------------------
void __fastcall TStrongWindow::ButtStartSearchClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): [07-06-2024]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TButton *pButt = dynamic_cast<TButton *>(Sender);
	if(!pButt) return;
	//---
	UnicodeString ustrSearch, ustrSignType,
								ustrSignCurrent = custrSelectPre[this->CBoxSelectDict->ItemIndex],
								ustrExistsVerses;
	int iSearchDig=-1;
  TStringStream *pStringStream = new TStringStream("", TEncoding::UTF8, true); //Allokacja strumienia dla tekstu html
	if(!pStringStream) throw(Exception("Błąd inicjalizacji objektu TStringStream"));
	this->ControlListVerses->ItemIndex = -1; // Nowe wyszukiwanie więc brak zaznaczonego elementu
	this->_pHListVerses->Clear();

	// Szukanie [07-06-2024] // [08-06-2024]
	for(int i=0; i<this->_pHSListStrong->Count; ++i)
	{
		ustrSignType = this->_pHSListStrong->Strings[i].SubString(1, 1);
		iSearchDig = this->_pHSListStrong->Strings[i].SubString(2, 4).ToIntDef(0);
		if((ustrSignType == ustrSignCurrent) && (iSearchDig == this->_iSearchNumber))
		{
			ustrSearch = this->_pHSListStrong->Strings[i].SubString(7, 2000); // [08-06-2024]
			break;
		}
	}
	// Wyodrębnianie miejsca wystapień wybranego słowa
	if(this->CBoxSelectDict->ItemIndex == enSelect_Grec)
	{
		ustrExistsVerses = this->_pHListWordInVersesExist->Strings[iSearchDig - 1].SubString1(6, 70000);
		this->_pHListVerses->DelimitedText = ustrExistsVerses;
		this->_pHListVerses->Delete(0);
		this->STextInfos->Caption = Format("Szukane słowo: \"%s\" Ilość wersetów , w których występuje słowo: %d",
			ARRAYOFCONST(( this->LEditSearchNumberStr->Text, this->_pHListVerses->Count)));
	}
	else
	{
		this->STextInfos->Caption = Format("Szukane słowo: \"%s\"", ARRAYOFCONST(( this->LEditSearchNumberStr->Text)));
	}
	this->ControlListVerses->ItemCount = this->_pHListVerses->Count;

	pStringStream->WriteString(custrHeadHTML); //Zapis nagłówka kodu html do strumienia
	pStringStream->WriteString(Format("%s", ARRAYOFCONST(( ustrSearch ))));

	pStringStream->WriteString(custrEndHTML);
	pStringStream->Position = 0;

	IPersistStreamInit *psi;
	_di_IStream sa(*(new TStreamAdapter(pStringStream, soReference)));
	if(SUCCEEDED(this->WebBrowserStrong->Document->QueryInterface(IID_IPersistStreamInit, (void **)&psi)))
		{psi->Load(sa);}
	// Oczyszczenie kontrolki podglądu wersetu
	this->WebBrowserVers->Navigate(WideString("about:blank").c_bstr()); // wypełnienie kontrolki pustą strony.

	if(pStringStream) {delete pStringStream; pStringStream = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall TStrongWindow::LEditSearchNumberStrKeyUp(TObject *Sender, WORD &Key,
					TShiftState Shift)
/**
	OPIS METOD(FUNKCJI): // [08-06-2024]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TLabeledEdit *pLEdit = dynamic_cast<TLabeledEdit *>(Sender);
	if(!pLEdit) return;
	//---
  if(Key == VK_RETURN)
	{
		if(!pLEdit->Text.IsEmpty() && (pLEdit->Text.Length() > 1))
		{
			if(this->ButtStartSearch->Enabled) // 10-06-2024
				{this->ButtStartSearchClick(this->ButtStartSearch);}
		}
  }
}
//---------------------------------------------------------------------------
void __fastcall TStrongWindow::ControlListVersesBeforeDrawItem(int AIndex, TCanvas *ACanvas,
					TRect &ARect, TOwnerDrawState AState)
/**
	OPIS METOD(FUNKCJI): // [08-06-2024]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	int iBook=0, iChapt=0, iVers=0;
	UnicodeString ustrAdress = this->_pHListVerses->Strings[AIndex];

	iBook = ustrAdress.SubString(1, 3).ToIntDef(0);
	iChapt = ustrAdress.SubString(4, 3).ToIntDef(0);
	iVers = ustrAdress.SubString(7, 3).ToIntDef(0);

	this->LabelItemAdresVers->Caption = Format("%s %d:%d",
		ARRAYOFCONST(( GsReadBibleTextData::GsInfoAllBooks[iBook - 1].ShortNameBook, iChapt, iVers )));
}
//---------------------------------------------------------------------------
void __fastcall TStrongWindow::ControlListVersesItemClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): // [09-06-2024]
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
	int iBook=0, iChapt=0, iVers=0, iPos=0;
	UnicodeString ustrSelectVers =  this->_pHListVerses->Strings[pCList->ItemIndex],
								ustrAdress;
	const UnicodeString custrStyleFStart = "<span class=\"styleFound\">",
											custrStyleFStop = "</span>";
  //---
  TStringStream *pStringStream = new TStringStream("", TEncoding::UTF8, true); //Allokacja strumienia dla tekstu html
	if(!pStringStream) throw(Exception("Błąd inicjalizacji objektu TStringStream"));

	iBook = ustrSelectVers.SubString(1, 3).ToIntDef(0);
	iChapt = ustrSelectVers.SubString(4, 3).ToIntDef(0);
	iVers = ustrSelectVers.SubString(7, 3).ToIntDef(0);
	ustrAdress = Format("%s %d:%d",
		ARRAYOFCONST(( GsReadBibleTextData::GsInfoAllBooks[iBook - 1].ShortNameBook, iChapt, iVers )));

	GsReadBibleTextData::GetTextVersOfAdress(iBook-1, iChapt, iVers, this->_iNumberTranslate, ustrSelectVers);
	// Zaznaczanie wybranego słowa //[09-06-2024]
	this->_SearchVersWord(ustrSelectVers);

	pStringStream->WriteString(custrHeadHTML); //Zapis nagłówka kodu html do strumienia
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
void __fastcall TStrongWindow::_SearchVersWord(UnicodeString &_custrIn)
/**
	OPIS METOD(FUNKCJI): // [11-06-2024]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	int iPos=0, iFind=0;
	const UnicodeString custrStyleFStart = "<span class=\"styleFound\">",
											custrStyleFStop = "</span>";
	UnicodeString ustrTemp=_custrIn, ustrFind,
								ustrModify;

	do //[12-06-2024]
	{
		iPos = ustrTemp.Pos("/m>"); // Pozycja końca tłumaczenia pojedyńczego słowa
		ustrFind = ustrTemp.SubString(1, iPos + 2); // Wyondrębnienie tłumaczenia słowa

		ustrTemp = ustrTemp.Delete(1, ustrFind.Length()); // Wykasowanie definicji słowa z całego wersetu
		iFind = ustrFind.Pos(this->LEditSearchNumberStr->Text.SubString(2, 4));
		if(iFind > 0)
		{
			// Jeśli znaleziono opis słowa o numerze szukanym
			ustrModify = Format("%s%s%s", ARRAYOFCONST(( custrStyleFStart, ustrFind.Delete(1, 1), custrStyleFStop )));
			_custrIn = StringReplace(_custrIn, ustrFind, ustrModify, TReplaceFlags() << rfIgnoreCase);
		}
	} while(iPos > 0); // Warunek pozostania w pętli
}
//---------------------------------------------------------------------------

