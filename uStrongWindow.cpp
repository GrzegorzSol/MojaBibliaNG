#include <vcl.h>
#pragma hdrstop

#include "uStrongWindow.h"
#include <System.IOUtils.hpp>
#include "uGlobalVar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
// Maksymalne numery dla słow greckich i hebrajskich
const int ciMaxNumHebr=8674,
					ciMaxNumGrec=5624,
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
																		"<title></title>\n</head>\n<body>\n",
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
	this->iSearchNumber = pLEdit->Text.SubString1(2, 4).ToIntDef(0); // [07-06-2024]
//  #if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("this->iSearchNumber: %d", ARRAYOFCONST(( this->iSearchNumber ))));
//	#endif
	if(this->CBoxSelectDict->ItemIndex == enSelect_Hebr)
	{
		if((this->iSearchNumber > ciMaxNumHebr) || (this->iSearchNumber < 1))
		{
			this->ButtStartSearch->Enabled = false;
      return;
		}
	}
	else if(this->CBoxSelectDict->ItemIndex == enSelect_Grec)
	{
		if((this->iSearchNumber > ciMaxNumGrec) || (this->iSearchNumber < 1))
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
	this->_pHListVerses->Clear();

	// Szukanie [07-06-2024] // [08-06-2024]
	for(int i=0; i<this->_pHSListStrong->Count; ++i)
	{
		ustrSignType = this->_pHSListStrong->Strings[i].SubString(1, 1);
		iSearchDig = this->_pHSListStrong->Strings[i].SubString(2, 4).ToIntDef(0);
		if((ustrSignType == ustrSignCurrent) && (iSearchDig == this->iSearchNumber))
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
		//this->ControlListVerses->ItemCount = this->_pHListVerses->Count;
		this->STextInfos->Caption = Format("Szukane słowo: \"%s\" Ilość wersetów , w których występuje słowo: %d",
			ARRAYOFCONST(( this->LEditSearchNumberStr->Text, this->_pHListVerses->Count)));
	}
	else
	{
		this->STextInfos->Caption = Format("Szukane słowo: \"%s\"", ARRAYOFCONST(( this->LEditSearchNumberStr->Text)));
	}
  this->ControlListVerses->ItemCount = this->_pHListVerses->Count;

	pStringStream->WriteString(custrHeadHTML); //Zapis nagłówka kodu html do strumienia
	pStringStream->WriteString(Format("<span style=\"font-size: x-large\"> %s </span>", ARRAYOFCONST(( ustrSearch ))));

	pStringStream->WriteString(custrEndHTML);
	pStringStream->Position = 0;

	IPersistStreamInit *psi;
		_di_IStream sa(*(new TStreamAdapter(pStringStream, soReference)));
		if(SUCCEEDED(this->WebBrowserStrong->Document->QueryInterface(IID_IPersistStreamInit, (void **)&psi)))
			{psi->Load(sa);}

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
      this->ButtStartSearchClick(this->ButtStartSearch);
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
	this->LabelItemAdresVers->Caption = this->_pHListVerses->Strings[AIndex];
}
//---------------------------------------------------------------------------

