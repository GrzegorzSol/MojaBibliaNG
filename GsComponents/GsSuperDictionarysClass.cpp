#pragma hdrstop

#include "GsSuperDictionarysClass.h"
#include "uGlobalVar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

enum enLineIndexDict {
	enLineGrec_NumberStrong, enLineGrec_GrecWord, enLineGrec_Phonetically, enLineGrec_GrammForm,
	enLineGrec_NumberApp, enLineGrec_Origin, enLineGrec_Translate, enLineGrec_Apperances,
	enLineGrec_ApperDecode, enLineGrec_Count,
	//---
	enLineHbr_NumberStrong=0, enLineHbr_HbrWord, enLineHbr_Phonetically, enLineHbr_GramForm,
	enLineHbr_NumberApp, enLineHbr_Translate1, enLineHbr_Translate2, enLineHbr_Apperances,
	enLineHbr_ApperDecode, enLineHbr_Count
};

//KLASY DLA OBJEKTÓW DLA KAŻDEGO SŁOWA W JĘZUKU HEBRAJSKIM I GRECKIM, WEDŁÓG KODÓW STRONGA
/****************************************************************************
 * 										KLASA BaseSuperDictionarysItem                        *
 ****************************************************************************/
__fastcall BaseSuperDictionarysItem::BaseSuperDictionarysItem()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
__fastcall BaseSuperDictionarysItem::~BaseSuperDictionarysItem()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}

/****************************************************************************
 * 										KLASA SuperDictionaryItemGrec                         *
 ****************************************************************************/
__fastcall SuperDictionaryItemGrec::SuperDictionaryItemGrec()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
__fastcall SuperDictionaryItemGrec::~SuperDictionaryItemGrec()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}

/****************************************************************************
 * 											KLASA SuperDictionaryItemHbr                        *
 ****************************************************************************/
__fastcall SuperDictionaryItemHbr::SuperDictionaryItemHbr()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
__fastcall SuperDictionaryItemHbr::~SuperDictionaryItemHbr()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}

//KLASY DO TWORZENIA I ODCZYTYWANIA POSZCZEGÓLNYCH INFORMACJI O SŁOWACH WEDŁUG KODÓW STRONGA
//DLA SŁOWNIKÓW HEBRAJSKO-POLSKIEGO I GRECKO-POLSKIEGO
/****************************************************************************
 * 											 KLASA BaseSuperDictionarys                         *
 ****************************************************************************/
__fastcall BaseSuperDictionaries::BaseSuperDictionaries(const UnicodeString _pathGrecSDict, const UnicodeString _pactHbrSDict)
	: pathGrecSDict(_pathGrecSDict), pactHbrSDict(_pactHbrSDict)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug("Konstruktor BaseSuperDictionarys");
//	#endif
	this->_pHSListFullDictGrek = new THashedStringList();
	if(!this->_pHSListFullDictGrek) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));

	this->_pHSListFullDictHbr = new THashedStringList();
	if(!this->_pHSListFullDictHbr) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));

	this->_pListGrecItems = new TList();
	if(!this->_pListGrecItems) throw(Exception("Błąd inicjalizacji objektu TList"));

	this->_pListHbrItems = new TList();
	if(!this->_pListHbrItems) throw(Exception("Błąd inicjalizacji objektu TList"));
}
//---------------------------------------------------------------------------
__fastcall BaseSuperDictionaries::~BaseSuperDictionaries()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("Ile pListGrecItems: %d, Ile pListHbrItems: %d", ARRAYOFCONST((this->_pListGrecItems->Count, this->_pListHbrItems->Count))));
//	#endif
	if(this->_pHSListFullDictGrek) {delete this->_pHSListFullDictGrek; this->_pHSListFullDictGrek = nullptr;}
	if(this->_pHSListFullDictHbr) {delete this->_pHSListFullDictHbr; this->_pHSListFullDictHbr = nullptr;}

	for(int i=0; i<this->_pListGrecItems->Count; ++i)
	{
		//Zwalnianie poszczególnych rekordów z listy
		SuperDictionaryItemGrec *pSuperDictionaryItemGrec = static_cast<SuperDictionaryItemGrec *>(this->_pListGrecItems->Items[i]);
		if(pSuperDictionaryItemGrec)
		{
			delete pSuperDictionaryItemGrec;
			pSuperDictionaryItemGrec = nullptr;
		}
	}
	delete this->_pListGrecItems; this->_pListGrecItems = nullptr;
	//---
	for(int i=0; i<this->_pListHbrItems->Count; ++i)
	{
		//Zwalnianie poszczególnych rekordów z listy
		SuperDictionaryItemHbr *pSuperDictionaryItemHbr = static_cast<SuperDictionaryItemHbr *>(this->_pListHbrItems->Items[i]);
		if(pSuperDictionaryItemHbr)
		{
			delete pSuperDictionaryItemHbr;
			pSuperDictionaryItemHbr = nullptr;
		}
	}
	delete this->_pListHbrItems; this->_pListHbrItems = nullptr;

//  #if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug("Destruktor BaseSuperDictionarys");
//	#endif
}
/****************************************************************************
 * 										KLASA CreateSuperDictionarys                         *
 ****************************************************************************/
#if defined(_CREATESDICT_)
__fastcall CreateSuperDictionaries::CreateSuperDictionaries(const UnicodeString _pathGrecSDict, const UnicodeString _pactHbrSDict)
	: BaseSuperDictionaries(_pathGrecSDict, _pactHbrSDict)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug("Konstruktor CreateSuperDictionarys");
//		GsDebugClass::WriteDebug(Format("_pathGrecSDict: \"%s\"\n_pactHbrSDict: \"%s\"", ARRAYOFCONST((_pathGrecSDict, _pactHbrSDict))));
//	#endif
}
//---------------------------------------------------------------------------
__fastcall CreateSuperDictionaries::~CreateSuperDictionaries()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug("Destruktor CreateSuperDictionarys");
//	#endif
}
//---------------------------------------------------------------------------
void __fastcall CreateSuperDictionaries::CreateGrecDictionaries()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	const UnicodeString custrPath = TPath::Combine(System::Sysutils::ExtractFilePath(Application->ExeName), "StrongFiles");
	UnicodeString ustrFileRead;

	THashedStringList *_pHSListStrongDictGrek = new THashedStringList();
	if(!_pHSListStrongDictGrek) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));

	this->_pHSListFullDictGrek->Clear();
	try
	{
		try
		{
			this->_pHSListFullDictGrek->BeginUpdate();
			for(int iIndex=1; iIndex<ciMaxStrongGrecCount; ++iIndex) // ciMaxStrongCount
			{
				ustrFileRead = TPath::Combine(custrPath, Format("G%d.txt", ARRAYOFCONST((iIndex))));
				if(TFile::Exists(ustrFileRead))
				{
					_pHSListStrongDictGrek->LoadFromFile(ustrFileRead, TEncoding::UTF8);
					_pHSListStrongDictGrek->Insert(0, Format("#G%d", ARRAYOFCONST((iIndex))));
					this->_pHSListFullDictGrek->AddStrings(_pHSListStrongDictGrek);
				}
			}
			this->_pHSListFullDictGrek->EndUpdate();
      MessageBox(NULL, L"Stworzono plik słownika grecko-polskiego!", L"Błąd aplikacji", MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
		}
		catch(const Exception& e)
		{
			MessageBox(NULL, e.Message.c_str(), L"Błąd aplikacji", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	}
	__finally
	{
		if(_pHSListStrongDictGrek) {delete _pHSListStrongDictGrek; _pHSListStrongDictGrek = nullptr;}
		this->_pHSListFullDictGrek->SaveToFile("SuperGrecDict.mbdict", TEncoding::UTF8);
	}
}
//---------------------------------------------------------------------------
void __fastcall CreateSuperDictionaries::CreateHbrDictionaries()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  const UnicodeString custrPath = TPath::Combine(System::Sysutils::ExtractFilePath(Application->ExeName), "StrongFiles");
	UnicodeString ustrFileRead;

	THashedStringList *_pHSListStrongDictHbr = new THashedStringList();
	if(!_pHSListStrongDictHbr) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));

	this->_pHSListFullDictHbr->Clear();
	try
	{
		try
		{
			this->_pHSListFullDictHbr->BeginUpdate();
			for(int iIndex=1; iIndex<ciMaxStrongHbrCount; ++iIndex) // ciMaxStrongCount
			{
				ustrFileRead = TPath::Combine(custrPath, Format("H%d.txt", ARRAYOFCONST((iIndex))));
				if(TFile::Exists(ustrFileRead))
				{
					_pHSListStrongDictHbr->LoadFromFile(ustrFileRead, TEncoding::UTF8);
					_pHSListStrongDictHbr->Insert(0, Format("#H%d", ARRAYOFCONST((iIndex))));
					_pHSListStrongDictHbr->Strings[enLineHbr_Apperances] = StringReplace(_pHSListStrongDictHbr->Strings[enLineHbr_Apperances], "_", ":", TReplaceFlags() << rfReplaceAll);
					this->_pHSListFullDictHbr->AddStrings(_pHSListStrongDictHbr);
        }
			}

			this->_pHSListFullDictHbr->EndUpdate();
			MessageBox(NULL, L"Stworzono plik słownika hebrajsko-polskiego!", L"Błąd aplikacji", MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
		}
    catch(const Exception& e)
		{
			MessageBox(NULL, e.Message.c_str(), L"Błąd aplikacji", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	}
	__finally
	{
		if(_pHSListStrongDictHbr) {delete _pHSListStrongDictHbr; _pHSListStrongDictHbr = nullptr;}
		this->_pHSListFullDictHbr->SaveToFile("SuperHbrDict.mbdict", TEncoding::UTF8);
  }
}
#endif
/****************************************************************************
 * 										KLASA ManagerSuperDictionarys                         *
 ****************************************************************************/
__fastcall ManagerSuperDictionaries::ManagerSuperDictionaries(const UnicodeString _pathGrecSDict, const UnicodeString _pactHbrSDict)
	: BaseSuperDictionaries(_pathGrecSDict, _pactHbrSDict)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug("Konstruktor ManagerSuperDictionarys");
//    GsDebugClass::WriteDebug(Format("_pathGrecSDict: \"%s\"\n_pactHbrSDict: \"%s\"", ARRAYOFCONST((_pathGrecSDict, _pactHbrSDict))));
//	#endif
}
//---------------------------------------------------------------------------
__fastcall ManagerSuperDictionaries::~ManagerSuperDictionaries()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug("Destruktor ManagerSuperDictionarys");
//	#endif
}
//---------------------------------------------------------------------------
void __fastcall ManagerSuperDictionaries::ReadGrecDictionary()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	SuperDictionaryItemGrec *pSuperDictionaryItemGrec=nullptr;

	if(!TFile::Exists(this->pathGrecSDict))
	{
		MessageBox(NULL, L"Brak słownika grecko-polskiego: SuperGrecDict.mbdict!", L"Błąd aplikacji", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		return;
	}
	//---
	this->_pHSListFullDictGrek->Clear();

	try
	{
		try
		{
			this->_pHSListFullDictGrek->LoadFromFile(this->pathGrecSDict, TEncoding::UTF8);
			int iInd=0, iStrong=5610;

			for(int iIndex=1; iIndex<ciMaxStrongGrecCount; ++iIndex)
			{
				iInd = iIndex - 1;
				pSuperDictionaryItemGrec = new SuperDictionaryItemGrec();
				if(!pSuperDictionaryItemGrec) throw(Exception("Błąd inicjalizacji objektu SuperDictionaryItemGrec"));

				if((iIndex > 3202) && (iIndex < 3303))
				{

				}
				else
				{
					if(iIndex > 3202) iInd = iIndex - 101; else iInd = iIndex - 1;
					pSuperDictionaryItemGrec->ustrGrecWord = this->_pHSListFullDictGrek->Strings[(iInd * enLineGrec_Count) + enLineGrec_GrecWord];
					pSuperDictionaryItemGrec->ustrPhonetically = this->_pHSListFullDictGrek->Strings[(iInd * enLineGrec_Count) + enLineGrec_Phonetically];
					pSuperDictionaryItemGrec->ustrGrammForm = this->_pHSListFullDictGrek->Strings[(iInd * enLineGrec_Count) + enLineGrec_GrammForm];
					pSuperDictionaryItemGrec->ustrNumberApp = this->_pHSListFullDictGrek->Strings[(iInd * enLineGrec_Count) + enLineGrec_NumberApp];
					pSuperDictionaryItemGrec->ustrOrigin = this->_pHSListFullDictGrek->Strings[(iInd * enLineGrec_Count) + enLineGrec_Origin];
					pSuperDictionaryItemGrec->ustrTranslate = this->_pHSListFullDictGrek->Strings[(iInd * enLineGrec_Count) + enLineGrec_Translate];
					pSuperDictionaryItemGrec->ustrApperances = this->_pHSListFullDictGrek->Strings[(iInd * enLineGrec_Count) + enLineGrec_Apperances];
					pSuperDictionaryItemGrec->ustrApperDecode = this->_pHSListFullDictGrek->Strings[(iInd * enLineGrec_Count) + enLineGrec_ApperDecode];//.Trim();
				}
				pSuperDictionaryItemGrec->StrongNumber = iIndex;

				this->_pListGrecItems->Add(pSuperDictionaryItemGrec);
			}
		}
		catch(const Exception& e)
		{
			MessageBox(NULL, e.Message.c_str(), L"Błąd aplikacji", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	}
	__finally
	{

  }
}
//---------------------------------------------------------------------------
void __fastcall ManagerSuperDictionaries::ReadHbrDictionary()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	SuperDictionaryItemHbr *pSuperDictionaryItemHbr=nullptr;

	if(!TFile::Exists(this->pactHbrSDict))
	{
		MessageBox(NULL, L"Brak słownika hebrajsko-polskiego: SuperHbrDict.mbdict!", L"Błąd aplikacji", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		return;
	}
	//---
	this->_pHSListFullDictHbr->Clear();

	try
	{
		try
		{
			this->_pHSListFullDictHbr->LoadFromFile(this->pactHbrSDict, TEncoding::UTF8);
			int iInd=0;

			for(int iIndex=1; iIndex<ciMaxStrongHbrCount; ++iIndex)
			{
				iInd = iIndex - 1;
				pSuperDictionaryItemHbr = new SuperDictionaryItemHbr();
				if(!pSuperDictionaryItemHbr) throw(Exception("Błąd inicjalizacji objektu SuperDictionaryItemHbr"));

				pSuperDictionaryItemHbr->StrongNumber = iIndex;
				pSuperDictionaryItemHbr->ustrHbrWord = this->_pHSListFullDictHbr->Strings[(iInd * enLineHbr_Count) + enLineHbr_HbrWord];
				pSuperDictionaryItemHbr->ustrPhonetically = this->_pHSListFullDictHbr->Strings[(iInd * enLineHbr_Count) + enLineHbr_Phonetically];
				pSuperDictionaryItemHbr->ustrGrammForm = this->_pHSListFullDictHbr->Strings[(iInd * enLineHbr_Count) + enLineHbr_GramForm];
				pSuperDictionaryItemHbr->ustrNumberApp = this->_pHSListFullDictHbr->Strings[(iInd * enLineHbr_Count) + enLineGrec_NumberApp];
				pSuperDictionaryItemHbr->ustrTranslate1 = this->_pHSListFullDictHbr->Strings[(iInd * enLineHbr_Count) + enLineHbr_Translate1];
				pSuperDictionaryItemHbr->ustrTranslate2 = this->_pHSListFullDictHbr->Strings[(iInd * enLineHbr_Count) + enLineHbr_Translate2];
				pSuperDictionaryItemHbr->ustrApperances = this->_pHSListFullDictHbr->Strings[(iInd * enLineHbr_Count) + enLineHbr_Apperances];
				pSuperDictionaryItemHbr->ustrApperDecode = this->_pHSListFullDictHbr->Strings[(iInd * enLineHbr_Count) + enLineHbr_ApperDecode].Trim();

				this->_pListHbrItems->Add(pSuperDictionaryItemHbr);
			}
		}
		catch(const Exception& e)
		{
			MessageBox(NULL, e.Message.c_str(), L"Błąd aplikacji", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	}
	__finally
	{

  }
}
//---------------------------------------------------------------------------
SuperDictionaryItemGrec *__fastcall ManagerSuperDictionaries::GetStrongGrec(unsigned short int _usiStrong)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if(_usiStrong >= ciMaxStrongGrecCount) return nullptr;

	SuperDictionaryItemGrec *pSuperDictionaryItemGrec=nullptr;

	pSuperDictionaryItemGrec = static_cast<SuperDictionaryItemGrec *>(this->_pListGrecItems->Items[_usiStrong - 1]);

  return pSuperDictionaryItemGrec;
}
//---------------------------------------------------------------------------
SuperDictionaryItemHbr *__fastcall ManagerSuperDictionaries::GetStrongHbr(unsigned short int _usiStrong)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(_usiStrong >= ciMaxStrongHbrCount) return nullptr;

	SuperDictionaryItemHbr *pSuperDictionaryItemHbr=nullptr;

	pSuperDictionaryItemHbr = static_cast<SuperDictionaryItemHbr *>(this->_pListHbrItems->Items[_usiStrong - 1]);

	return pSuperDictionaryItemHbr;
}
//---------------------------------------------------------------------------



