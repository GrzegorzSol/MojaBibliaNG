#ifndef GsSuperDictionarysClassH
#define GsSuperDictionarysClassH

#include <System.IniFiles.hpp>

#if defined(_DEBUGINFO_)
	#include "GsDebugClass.h"
#endif
//#define _CREATESDICT_
//---------------------------------------------------------------------------

static const int ciMaxStrongGrecCount=5625, //Maksymalny numer słowa w greckim nowym testamencie, według numeracji Stronga
								 ciMaxStrongHbrCount=8674;  //Maksymalny numer słowa w hebrajskim starym testamencie, według numeracji Stronga

//KLASY DLA OBJEKTÓW DLA KAŻDEGO SŁOWA W JĘZUKU HEBRAJSKIM I GRECKIM, WEDŁÓG KODÓW STRONGA
/****************************************************************************
 * 										KLASA BaseSuperDictionarysItem                        *
 ****************************************************************************/
class BaseSuperDictionarysItem : public TObject
{
	public:
		__fastcall BaseSuperDictionarysItem();
		virtual __fastcall ~BaseSuperDictionarysItem();
		//---
		short unsigned int StrongNumber;
};

/****************************************************************************
 * 										KLASA SuperDictionaryItemGrec                         *
 ****************************************************************************/
class SuperDictionaryItemGrec : public BaseSuperDictionarysItem
{
	public:
		__fastcall SuperDictionaryItemGrec();
		virtual __fastcall ~SuperDictionaryItemGrec();
		//---
		UnicodeString ustrGrecWord,
									ustrPhonetically,
									ustrGrammForm,
									ustrNumberApp,
									ustrOrigin,
									ustrTranslate,
									ustrApperances,
									ustrApperDecode;
};

/****************************************************************************
 * 											KLASA SuperDictionaryItemHbr                        *
 ****************************************************************************/
class SuperDictionaryItemHbr : public BaseSuperDictionarysItem
{
	public:
		__fastcall SuperDictionaryItemHbr();
		virtual __fastcall ~SuperDictionaryItemHbr();
		//---
		UnicodeString ustrHbrWord,
									ustrPhonetically,
									ustrGrammForm,
									ustrNumberApp,
									ustrTranslate1,
									ustrTranslate2,
									ustrApperances,
									ustrApperDecode;
};

//KLASY DO TWORZENIA I ODCZYTYWANIA POSZCZEGÓLNYCH INFORMACJI O SŁOWACH WEDŁUG KODÓW STRONGA
//DLA SŁOWNIKÓW HEBRAJSKO-POLSKIEGO I GRECKO-POLSKIEGO
/****************************************************************************
 * 											 KLASA BaseSuperDictionaries                        *
 ****************************************************************************/
class BaseSuperDictionaries : public TObject
{
	friend class CreateSuperDictionaries;
	friend class ManagerSuperDictionaries;

	public:
		__fastcall BaseSuperDictionaries(const UnicodeString _pathGrecSDict, const UnicodeString _pactHbrSDict);
		virtual __fastcall ~BaseSuperDictionaries();
		//---
		const UnicodeString pathGrecSDict, pactHbrSDict;
	private:
		THashedStringList *_pHSListFullDictGrek=nullptr,
                      *_pHSListFullDictHbr=nullptr;
		TList *_pListGrecItems=nullptr,
					*_pListHbrItems=nullptr;
};

/****************************************************************************
 * 										KLASA CreateSuperDictionaries                         *
 ****************************************************************************/
#if defined(_CREATESDICT_)
class CreateSuperDictionaries : public BaseSuperDictionaries
{
	public:
		__fastcall CreateSuperDictionaries(const UnicodeString _pathGrecSDict, const UnicodeString _pactHbrSDict);
		virtual __fastcall ~CreateSuperDictionaries();
		//---
		void __fastcall CreateGrecDictionaries();
		void __fastcall CreateHbrDictionaries();
};
#endif

/****************************************************************************
 * 										KLASA ManagerSuperDictionaries                        *
 ****************************************************************************/
class ManagerSuperDictionaries : public BaseSuperDictionaries
{
	public:
		__fastcall ManagerSuperDictionaries(const UnicodeString _pathGrecSDict, const UnicodeString _pactHbrSDict);
		virtual __fastcall ~ManagerSuperDictionaries();
		//---
		void __fastcall ReadGrecDictionary();
		void __fastcall ReadHbrDictionary();
		SuperDictionaryItemGrec *__fastcall GetStrongGrec(unsigned short int _usiStrong=1);
		SuperDictionaryItemHbr *__fastcall GetStrongHbr(unsigned short int _usiStrong=1);
};
//---------------------------------------------------------------------------

#endif
