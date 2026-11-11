#pragma hdrstop

#include "InitMBAppConst.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// --------------------------------- Zmienne --------------------------------
// Tablica struktur InfoAllBooks, z parametrami ksiąg biblijnych
const InfoAllBooks AppCTable_InfoAllBooks[GlobalVar::Global_NumberBooks] =
{	//--- Stary Testament
	InfoAllBooks(1,	L"1 Mojżeszowa",									L"1Moj",		50), //0
	InfoAllBooks(2, L"2 Mojżeszowa",									L"2Moj",		40), //1
	InfoAllBooks(3,	L"3 Mojżeszowa",									L"3Moj",		27), //2
	InfoAllBooks(4,	L"4 Księga Mojżeszowa",					L"4Moj",		 36), //3
	InfoAllBooks(5,	L"5 Księga Mojżeszowa",					L"5Moj",		34), //4
	InfoAllBooks(6,	L"Księga Jozuego",								L"Joz",		24), //5
	InfoAllBooks(7,	L"Księga Sędziów",								L"Sędź",		21), //6
	InfoAllBooks(8,	L"Księga Rut",										L"Rut",		4),	 //7
	InfoAllBooks(9,	L"1 Księga Samuela",							L"1Sam",		31), //8
	InfoAllBooks(10,	L"2 Księga Samuela",							L"2Sam",		24), //9
	InfoAllBooks(11,	L"1 Księga Królewska",						L"1Król",	22), //10
	InfoAllBooks(12,	L"2 Księga Królewska",						L"2Król",	25), //11
	InfoAllBooks(13,	L"1 Księga Kronik",							L"1Kron",		29), //12
	InfoAllBooks(14,	L"2 Księga Kronik",							L"2Kron",		36), //13
	InfoAllBooks(15,	L"Księga Ezdrasza",							L"Ezdr",		10), //14
	InfoAllBooks(16,	L"Księga Nechemiasza",						L"Nech",		13), //15
	InfoAllBooks(17,	L"Księga Estery",								L"Est",		10), //16
	InfoAllBooks(18,	L"Księga Joba",									L"Job",		42), //17
	InfoAllBooks(19,	L"Księga Psalmów",								L"Ps",			150),//18
	InfoAllBooks(20,	L"Przypowieści Salomona",				L"Przyp",	31), //19
	InfoAllBooks(21,	L"Księga Kaznodziei Salomona",		L"Kazn",		12), //20
	InfoAllBooks(22,	L"Pieśni nad Pieśniami",					L"PnP",		8),	 //21
	InfoAllBooks(23,	L"Księga Izajasza",							L"Iz",			66), //22
	InfoAllBooks(24,	L"Księga Jeremiasza",						L"Jer",		52), //23
	InfoAllBooks(25,	L"Treny",												L"Tren",		5),	 //24
	InfoAllBooks(26,	L"Księga Ezechiela",							L"Ez",			48), //25
	InfoAllBooks(27,	L"Księga Daniela",								L"Dan",		14), //26
	InfoAllBooks(28,	L"Księga Ozeasza",								L"Oz",			14), //27
	InfoAllBooks(29,	L"Księga Joela",									L"Jo",			3),	 //28
	InfoAllBooks(30,	L"Księga Amosa",									L"Am",			9),	 //29
	InfoAllBooks(31,	L"Księga Abdiasza",							L"Abd",		1),	 //30
	InfoAllBooks(32,	L"Księga Jonasza",								L"Jon",		4),	 //31
	InfoAllBooks(33,	L"Księga Micheasza",							L"Mich",		7),	 //32
	InfoAllBooks(34,	L"Księga Nahuma",								L"Nah",		3),	 //33
	InfoAllBooks(35,	L"Księga Habakuka",							L"Hab",		3),	 //34
	InfoAllBooks(36,	L"Księga Sofoniasza",						L"Sof",		3),	 //35
	InfoAllBooks(37,	L"Księga Aggeusza",							L"Agg",		2),	 //36
	InfoAllBooks(38,	L"Księga Zachariasza",						L"Zach",		14), //37
	InfoAllBooks(39,	L"Księga Malachiasza",						L"Mal",		3),	 //38
	//--- Nowy Testament
	InfoAllBooks(40,	L"Ewangelia Mateusza",						L"Mt",			28), //39
	InfoAllBooks(41,	L"Ewangelia Marka",							L"Mk",			16), //40
	InfoAllBooks(42,	L"Ewangelia Łukasza",						L"Łk",			24), //41
	InfoAllBooks(43,	L"Ewangelia Jana",								L"Jan",		21), //42
	InfoAllBooks(44,	L"Dzieje Apostolskie",						L"DzAp",		28), //43
	InfoAllBooks(45,	L"List Pawła do Rzymian",				L"Rzym",		16), //44
	InfoAllBooks(46,	L"1 List Pawła do Koryntian",		L"1Kor",		16), //45
	InfoAllBooks(47,	L"2 List Pawła do Koryntian",		L"2Kor",		13), //46
	InfoAllBooks(48,	L"List Pawła do Galacjan",				L"Gal",		6),	 //47
	InfoAllBooks(49,	L"List Pawła do Efezjan",				L"Efez",		6),	 //48
	InfoAllBooks(50,	L"List Pawła do Filipian",				L"Filip",	4),	 //49
	InfoAllBooks(51,	L"List Pawła do Kolosan",				L"Kol",		4),	 //50
	InfoAllBooks(52,	L"1 List Pawła do Tesaloniczan",	L"1Tes",		5),	 //51
	InfoAllBooks(53,	L"2 List Pawła do Tesaloniczan",	L"2Tes",		3),	 //52
	InfoAllBooks(54,	L"1 List Pawła do Tymoteusza",		L"1Tym",		6),	 //53
	InfoAllBooks(55,	L"2 List Pawła do Tymoteusza",		L"2Tym",		4),	 //54
	InfoAllBooks(56,	L"List Pawła do Tytusa",					L"Tyt",		3),	 //55
	InfoAllBooks(57,	L"List Pawła do Filemona",				L"Filem",	1),	 //56
	InfoAllBooks(58,	L"List do Hebrajczyków",					L"Hbr",		13), //57
	InfoAllBooks(59,	L"List Jakuba",									L"Jak",		5),	 //58
	InfoAllBooks(60,	L"1 List Piotra",								L"1Pt",		5),	 //59
	InfoAllBooks(61,	L"2 List Piotra",								L"2Pt",		3),	 //60
	InfoAllBooks(62,	L"1 List Jana",									L"1Jan",		5),	 //61
	InfoAllBooks(63,	L"2 List Jana",									L"2Jan",		1),	 //62
	InfoAllBooks(64,	L"3 List Jana",									L"3Jan",		1),	 //63
	InfoAllBooks(65,	L"List Judy",										"Jud",		1),	 //64
	InfoAllBooks(66,	L"Objawienie Jana",							"Obj",		22), //65
	//--- Apokryfy
	InfoAllBooks(67,	L"Księga Tobiasza",							L"Tob",		14), //66
	InfoAllBooks(68,	L"Księga Judyty",								L"Judyt",	16), //67
	InfoAllBooks(69,	L"Księga I Machabejska",					L"1Mach",	16), //68
	InfoAllBooks(70,	L"Księga II Machabejska",				L"2Mach",	15), //69
	InfoAllBooks(71,	L"Księga Mądrości",							L"Mądr",		19), //70
	InfoAllBooks(72,	L"Księga Syracha",								L"Syr",		51), //71
	InfoAllBooks(73,	L"Księga Barucha",								L"Bar",		6)	 //72
};	//Tablica struktur InfoAllBooks, opisująca parametry ksiąg biblijnych

// --------------------------------- Funkcje --------------------------------
__fastcall UnicodeString AppFun_GetStringAddressVers(const UnicodeString &custrTextAddress)
/**
	OPIS METOD(FUNKCJI): Funkcja zwraca czytelny adres wersetu z wersji zakodowanej
	OPIS ARGUMENTÓW: const UnicodeString &custrTextAddress - Wersja zakodowana
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI): UnicodeString - Czytelny adres
*/
{
	UnicodeString ustrRet, ustrBook, ustrChapt, ustrVers;

	ustrBook = AppCTable_InfoAllBooks[custrTextAddress.SubString(1, 3).ToIntDef(0) - 1].ShortNameBook;
	ustrChapt = custrTextAddress.SubString(4, 3).ToIntDef(1);
	ustrVers = custrTextAddress.SubString(7, 3).ToIntDef(1);

	//----- Tworzenie adresu wersetu
	ustrRet = Format(L"%s %s:%s", ARRAYOFCONST((ustrBook, ustrChapt, ustrVers)));

	return ustrRet;
}