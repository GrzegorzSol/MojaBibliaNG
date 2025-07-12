#include <vcl.h>
#pragma hdrstop

#include "uStrongWindow.h"
#include <System.IOUtils.hpp>
#include "MyBibleLibrary\MyBibleLibrary.h"
#include "MyBibleLibrary\GsReadBibleTextdata.h"
#include "uGlobalVar.h"
#include <System.StrUtils.hpp>
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
	enSelect_Grec,
  enImage16_Vers=0 //0.Ikona wersetu wystepowania
 };
// Przedrostki do numeru Stronga
const UnicodeString custrSelectPre[] = {"H", "G"}, // [07-06-2024]
										// Wybór słownika
										custrSelectDict[] = {"Hebrajsko-Polski", "Grecko-Polski"},
										custrHeadTransHTML = UnicodeString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n") +
																		"<html>\n<head>\n" +
																		"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">" +// !!!
																		"<title>Tłumaczenie wybranego słowa</title>\n" +
																		"<style type=\"text/css\">\n" +
																		Format(".styleFound {background-color: %s;}\n", ARRAYOFCONST(( RGBToWebColorStr(clWebYellow) ))) +
																		".styleNumber {color: #FF0000;vertical-align: super;font-size: small;font-weight: bold;}\n" +
																		"body {background-color:#FFFACD;font-size: x-large;}\n" +
																		"</style>\n</head>\n<body>\n",
										custrHeadText = UnicodeString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n") +
																		"<html>\n<head>\n" +
																		"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">" +// !!!
																		"<title>Tekst interlinearny grecko-polski</title>\n" +
																		"<style type=\"text/css\">\n" +
																		Format(".styleFound {background-color: %s;}\n", ARRAYOFCONST(( RGBToWebColorStr(clWebYellow) ))) +
																		".styleNumber {color: #FF0000;vertical-align: super;font-size: small;font-weight: bold;}\n" +
																		Format("body {background-color: %s;font-size: x-large;}\n", ARRAYOFCONST(( RGBToWebColorStr(clWebLavender) )))  +
																		"</style>\n</head>\n<body>\n",
										custrEndHTML = "\n</body>\n</html>",
										custrPathImportane = TPath::Combine(GlobalVar::Global_custrGetDataDir, "ImpStrong.html");
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
	// Lista wystąpień i tekstu widoczna tylko przy słowniku grecko-polskim //08-07-2024
	//this->ControlListVerses->Visible = (this->CBoxSelectDict->ItemIndex == enSelect_Grec);
	//this->PanelVers->Visible = this->ControlListVerses->Visible;

	this->CBoxSelectDict->OnChange(this->CBoxSelectDict);
	this->CBoxSelectDict->Items->EndUpdate();
	this->LEditSearchNumberStr->MaxLength = 5;

	this->WebBrowserStrong->Navigate(WideString("about:blank").c_bstr()); // wypełnienie kontrolki pustą strony.
	this->WebBrowserVers->Navigate(WideString("about:blank").c_bstr()); // wypełnienie kontrolki pustą strony.
	this->WebBrowserImpotance->Navigate(custrPathImportane.c_str()); // wypełnienie kontrolki instrukcją.
	// Wyszukanie konkretnego tłumaczenia //[09-06-2024]
	int iCountTrans = GsReadBibleTextData::CountTranslates();
	UnicodeString ustrNameTrans;
	const UnicodeString custrFindNameTransGrec = "TRO+",
											custrFindNameTransHebr = "IBHP+"; // [31-07-2024]

	for(int i=0; i<iCountTrans; ++i)
	{
		GsReadBibleTextData::GetInfoNameTranslate(i, ustrNameTrans);
		// Wyszukiwanie numerów tłumaczeń greckiego i hebrajskiego, używanych do modułu Stronga
//    #if defined(_DEBUGINFO_)
//			GsDebugClass::WriteDebug(Format("%d. - %s", ARRAYOFCONST(( i, ustrNameTrans ))));
//		#endif
		if(ustrNameTrans == custrFindNameTransGrec)
		{
			this->_iNumberTranslateGrec = i;
		}
		if(ustrNameTrans == custrFindNameTransHebr) // [31-07-2024]
		{
			this->_iNumberTranslateHbr = i;
		}
	}
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("_iNumberTranslateGrec: \"%d\" - _iNumberTranslateHbr: \"%d\"",
//			ARRAYOFCONST(( this->_iNumberTranslateGrec, this->_iNumberTranslateHbr ))));
//	#endif
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
	// Lista z danymi wystapień w wersetach, poszczególnych słów greckich // [08-06-2024]
	this->_pHListWordInVersesExistGrec = new THashedStringList();
	if(!this->_pHListWordInVersesExistGrec) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));
	// Lista z danymi wystapień w wersetach, poszczególnych słów hebrajskich // [31-07-2024]
	this->_pHListWordInVersesExistHbr = new THashedStringList();
	if(!this->_pHListWordInVersesExistHbr) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));
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
//  #if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("Global_custrPathStrongDict: \"%s\"", ARRAYOFCONST(( GlobalVar::Global_custrPathFileWordVersesExistGrec ))));
//	#endif
	// Załadowanie pliku z wystąpieniami słów greckich
	if(!TFile::Exists(GlobalVar::Global_custrPathFileWordVersesExistGrec))
		throw(Exception("Brak pliku ze słownikiem greckim Stronga!"));
	this->_pHListWordInVersesExistGrec->LoadFromFile(GlobalVar::Global_custrPathFileWordVersesExistGrec, TEncoding::UTF8);
	// Załadowanie pliku z wystąpieniami słów hebrajskich
	if(!TFile::Exists(GlobalVar::Global_custrPathFileWordVersesExistHbr))
		throw(Exception("Brak pliku ze słownikiem hebrajskim Stronga!"));
	this->_pHListWordInVersesExistHbr->LoadFromFile(GlobalVar::Global_custrPathFileWordVersesExistHbr, TEncoding::UTF8);
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
	if(this->_pHListWordInVersesExistGrec) {delete this->_pHListWordInVersesExistGrec; this->_pHListWordInVersesExistGrec = nullptr;}
	if(this->_pHListWordInVersesExistHbr) {delete this->_pHListWordInVersesExistHbr; this->_pHListWordInVersesExistHbr = nullptr;} // [31-07-2024]
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
	if(this->Visible) //17-06-2024]
	{
		this->LEditSearchNumberStr->SetFocus();
		this->LEditSearchNumberStr->SelStart = 1; // Kursor za literą "H" lib "G"
		// Lista wystąpień i tekstu widoczna tylko przy słowniku grecko-polskim //08-07-2024
		//this->ControlListVerses->Visible = (this->CBoxSelectDict->ItemIndex == enSelect_Grec);
    //this->PanelVers->Visible = this->ControlListVerses->Visible;
	}
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
	//---
	if(pLEdit->Text.IsEmpty()) return; //[23-06-2024]
	//---
	// Brak litery na początku, która informuje do jakiego słownika odnosi się numer Stronga //[23-06-2024]
	if((pLEdit->Text.Pos("H") != 1) && (pLEdit->Text.Pos("G") != 1)) {this->ButtStartSearch->Enabled = false; return;}
	//--- zabezpieczenie przed wprowadzeniem niewłaściwego numeru słowa
	this->_iSearchNumber = pLEdit->Text.SubString1(2, 4).ToIntDef(0); // [07-06-2024]

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
	OPIS METOD(FUNKCJI): Tworzenie listy wersetów z wybranym słowem[07-06-2024]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TButton *pButt = dynamic_cast<TButton *>(Sender);
	if(!pButt) return;
	//---
	UnicodeString ustrSearch, ustrSignType,
								ustrSignCurrent = custrSelectPre[this->CBoxSelectDict->ItemIndex], // Litera przed numerem Stronga: "H" lub "G"
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
		iSearchDig = this->_pHSListStrong->Strings[i].SubString(2, 4).ToIntDef(0); // Numer Stronga
		if((ustrSignType == ustrSignCurrent) && (iSearchDig == this->_iSearchNumber))
		{
      // Linia ze słownika "StrongDict.strdi", bez numeru Stronga
			ustrSearch = this->_pHSListStrong->Strings[i].SubString(7, 2000); // [08-06-2024] //"StrongDict.strdi"
			break;
		}
	}

	if(this->CBoxSelectDict->ItemIndex == enSelect_Grec) // [31-07-2024]
	{
		ustrExistsVerses = this->_pHListWordInVersesExistGrec->Strings[iSearchDig - 1].SubString1(6, 70000);
	}
  // Wyodrębnianie miejsca wystapień wybranego słowa hebrajskiego
	else if(this->CBoxSelectDict->ItemIndex == enSelect_Hebr) // [31-07-2024]
	{
		ustrExistsVerses = this->_pHListWordInVersesExistHbr->Strings[iSearchDig - 1].SubString1(6, 70000);
	}
	// Wyodrębnianie miejsca wystapień wybranego słowa greckiego
  this->_pHListVerses->DelimitedText = ustrExistsVerses;
	this->_pHListVerses->Delete(0);
	this->STextInfos->Caption = Format("Szukane słowo: \"%s\" Ilość wersetów , w których występuje słowo: %d",
		ARRAYOFCONST(( this->LEditSearchNumberStr->Text, this->_pHListVerses->Count)));
  //---
	this->ControlListVerses->ItemCount = this->_pHListVerses->Count;
	// Wyświetlenie tłumaczenia wyszukanego słowa
	pStringStream->WriteString(custrHeadTransHTML); //Zapis nagłówka kodu html do strumienia
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
	else if((Key == VK_DELETE) || (Key == VK_BACK))
	{
//    #if defined(_DEBUGINFO_)
//			GsDebugClass::WriteDebug(Format("Key: %d", ARRAYOFCONST(( Key ))));
//		#endif
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
		ARRAYOFCONST((AppCTable_InfoAllBooks[iBook - 1].ShortNameBook, iChapt, iVers )));

	this->ImageListSmall->GetIcon(0, this->ImageVers->Picture->Icon);
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
	int iBook=0, iChapt=0, iVers=0;
	UnicodeString ustrSelectVers = this->_pHListVerses->Strings[pCList->ItemIndex],
								ustrAdress;
	//---
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("%s", ARRAYOFCONST(( ustrSelectVers ))));
//	#endif
  TStringStream *pStringStream = new TStringStream("", TEncoding::UTF8, true); //Allokacja strumienia dla tekstu html
	if(!pStringStream) throw(Exception("Błąd inicjalizacji objektu TStringStream"));
	// Wypisanie adresu wersetu w formie czytelnej
	iBook = ustrSelectVers.SubString(1, 3).ToIntDef(0);
	iChapt = ustrSelectVers.SubString(4, 3).ToIntDef(0);
	iVers = ustrSelectVers.SubString(7, 3).ToIntDef(0);
	ustrAdress = Format("%s %d:%d",
		ARRAYOFCONST((AppCTable_InfoAllBooks[iBook - 1].ShortNameBook, iChapt, iVers )));

		// Wypisanie tekstu, zależnie od tłumaczenia // [31-07-2024]
	if(this->CBoxSelectDict->ItemIndex == enSelect_Grec) // [31-07-2024]
	{
		GsReadBibleTextData::GetTextVersOfAdress(iBook-1, iChapt, iVers, this->_iNumberTranslateGrec, ustrSelectVers);
	}
  else if(this->CBoxSelectDict->ItemIndex == enSelect_Hebr) // [31-07-2024]
	{
    GsReadBibleTextData::GetTextVersOfAdress(iBook-1, iChapt, iVers, this->_iNumberTranslateHbr, ustrSelectVers);
  }
	// Zaznaczanie wybranego słowa //[09-06-2024]
  if(this->CBoxSelectDict->ItemIndex == enSelect_Grec)
	{
		ustrSelectVers = this->_SearchVersWordGrec(ustrSelectVers);
	}
  else if(this->CBoxSelectDict->ItemIndex == enSelect_Hebr)
	{
    ustrSelectVers = this->_SearchVersWordHbr(ustrSelectVers);
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
UnicodeString __fastcall TStrongWindow::_SearchVersWordGrec(const UnicodeString &_custrIn)
/**
	OPIS METOD(FUNKCJI): //[18-06-2024]
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
				ARRAYOFCONST(( this->LEditSearchNumberStr->Text.SubString(2, 4) ))));

			if(iFind > 0)
			{
				// Jeśli znaleziono opis słowa o numerze szukanym
				// Dodanie do słowa znalezionego kodu html zmieniający podkład pod napisem
				ustrModify = Format("%s%s%s", ARRAYOFCONST(( custrStyleFStart, daWord[i], custrStyleFStop )));
				// Podmiana oryginalnego definicji słowa, podkoloryzowaną wersją //[22-06-2024]
				daWord[i] = StringReplace(daWord[i], daWord[i], ustrModify, TReplaceFlags());
//				#if defined(_DEBUGINFO_)
//					GsDebugClass::WriteDebug(Format("%d: %s", ARRAYOFCONST(( i, daWord[i]))));
//				#endif
			}
			// Ponowne dodanie wszystkich, wczesniej pociętych podciągów //[22-06-2024]
			ustrOut += daWord[i] + " ";
//      #if defined(_DEBUGINFO_)
//				ustrOut += "\n";
//			#endif
		}
	}

	return ustrOut;
}
//---------------------------------------------------------------------------
UnicodeString __fastcall TStrongWindow::_SearchVersWordHbr(const UnicodeString &_custrIn)
/**
	OPIS METOD(FUNKCJI): //[01-08-2024]
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
	iFind = ustrOp.Pos(this->LEditSearchNumberStr->Text.SubString(2, 4));

	if(iFind > 0)
	{
		ustrModify = Format("<sup>%s%s%s",
			ARRAYOFCONST(( custrStyleFStart, this->LEditSearchNumberStr->Text.SubString(2, 4), custrStyleFStop )));
		ustrTo = Format("<sup>%s", ARRAYOFCONST(( this->LEditSearchNumberStr->Text.SubString(2, 4) )) );
//		#if defined(_DEBUGINFO_)
//			GsDebugClass::WriteDebug(Format("%s", ARRAYOFCONST(( ustrModify ))));
//		#endif
		ustrOut = StringReplace(ustrOp, ustrTo, ustrModify, TReplaceFlags());
	}

	return ustrOut;
}
//---------------------------------------------------------------------------
