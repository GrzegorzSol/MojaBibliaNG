#pragma hdrstop

#include "InitMBAppConst.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// --------------------------------- Zmienne --------------------------------
// Tablica struktur InfoAllBooks, z parametrami ksiąg biblijnych
const InfoAllBooks AppCTable_InfoAllBooks[GlobalVar::Global_NumberBooks] =
{	//--- Stary Testament
	InfoAllBooks(1,	"1 Mojżeszowa",									"1Moj",		50), //0
	InfoAllBooks(2, "2 Mojżeszowa",									"2Moj",		40), //1
	InfoAllBooks(3,	"3 Mojżeszowa",									"3Moj",		27), //2
	InfoAllBooks(4,	"4 Księga Mojżeszowa",					"4Moj",		 36), //3
	InfoAllBooks(5,	"5 Księga Mojżeszowa",					"5Moj",		34), //4
	InfoAllBooks(6,	"Księga Jozuego",								"Joz",		24), //5
	InfoAllBooks(7,	"Księga Sędziów",								"Sędź",		21), //6
	InfoAllBooks(8,	"Księga Rut",										"Rut",		4),	 //7
	InfoAllBooks(9,	"1 Księga Samuela",							"1Sam",		31), //8
	InfoAllBooks(10,	"2 Księga Samuela",							"2Sam",		24), //9
	InfoAllBooks(11,	"1 Księga Królewska",						"1Król",	22), //10
	InfoAllBooks(12,	"2 Księga Królewska",						"2Król",	25), //11
	InfoAllBooks(13,	"1 Księga Kronik",							"1Kron",		29), //12
	InfoAllBooks(14,	"2 Księga Kronik",							"2Kron",		36), //13
	InfoAllBooks(15,	"Księga Ezdrasza",							"Ezdr",		10), //14
	InfoAllBooks(16,	"Księga Nechemiasza",						"Nech",		13), //15
	InfoAllBooks(17,	"Księga Estery",								"Est",		10), //16
	InfoAllBooks(18,	"Księga Joba",									"Job",		42), //17
	InfoAllBooks(19,	"Księga Psalmów",								"Ps",			150),//18
	InfoAllBooks(20,	"Przypowieści Salomona",				"Przyp",	31), //19
	InfoAllBooks(21,	"Księga Kaznodziei Salomona",		"Kazn",		12), //20
	InfoAllBooks(22,	"Pieśni nad Pieśniami",					"PnP",		8),	 //21
	InfoAllBooks(23,	"Księga Izajasza",							"Iz",			66), //22
	InfoAllBooks(24,	"Księga Jeremiasza",						"Jer",		52), //23
	InfoAllBooks(25,	"Treny",												"Tren",		5),	 //24
	InfoAllBooks(26,	"Księga Ezechiela",							"Ez",			48), //25
	InfoAllBooks(27,	"Księga Daniela",								"Dan",		14), //26
	InfoAllBooks(28,	"Księga Ozeasza",								"Oz",			14), //27
	InfoAllBooks(29,	"Księga Joela",									"Jo",			3),	 //28
	InfoAllBooks(30,	"Księga Amosa",									"Am",			9),	 //29
	InfoAllBooks(31,	"Księga Abdiasza",							"Abd",		1),	 //30
	InfoAllBooks(32,	"Księga Jonasza",								"Jon",		4),	 //31
	InfoAllBooks(33,	"Księga Micheasza",							"Mich",		7),	 //32
	InfoAllBooks(34,	"Księga Nahuma",								"Nah",		3),	 //33
	InfoAllBooks(35,	"Księga Habakuka",							"Hab",		3),	 //34
	InfoAllBooks(36,	"Księga Sofoniasza",						"Sof",		3),	 //35
	InfoAllBooks(37,	"Księga Aggeusza",							"Agg",		2),	 //36
	InfoAllBooks(38,	"Księga Zachariasza",						"Zach",		14), //37
	InfoAllBooks(39,	"Księga Malachiasza",						"Mal",		3),	 //38
	//--- Nowy Testament
	InfoAllBooks(40,	"Ewangelia Mateusza",						"Mt",			28), //39
	InfoAllBooks(41,	"Ewangelia Marka",							"Mk",			16), //40
	InfoAllBooks(42,	"Ewangelia Łukasza",						"Łk",			24), //41
	InfoAllBooks(43,	"Ewangelia Jana",								"Jan",		21), //42
	InfoAllBooks(44,	"Dzieje Apostolskie",						"DzAp",		28), //43
	InfoAllBooks(45,	"List Pawła do Rzymian",				"Rzym",		16), //44
	InfoAllBooks(46,	"1 List Pawła do Koryntian",		"1Kor",		16), //45
	InfoAllBooks(47,	"2 List Pawła do Koryntian",		"2Kor",		13), //46
	InfoAllBooks(48,	"List Pawła do Galacjan",				"Gal",		6),	 //47
	InfoAllBooks(49,	"List Pawła do Efezjan",				"Efez",		6),	 //48
	InfoAllBooks(50,	"List Pawła do Filipian",				"Filip",	4),	 //49
	InfoAllBooks(51,	"List Pawła do Kolosan",				"Kol",		4),	 //50
	InfoAllBooks(52,	"1 List Pawła do Tesaloniczan",	"1Tes",		5),	 //51
	InfoAllBooks(53,	"2 List Pawła do Tesaloniczan",	"2Tes",		3),	 //52
	InfoAllBooks(54,	"1 List Pawła do Tymoteusza",		"1Tym",		6),	 //53
	InfoAllBooks(55,	"2 List Pawła do Tymoteusza",		"2Tym",		4),	 //54
	InfoAllBooks(56,	"List Pawła do Tytusa",					"Tyt",		3),	 //55
	InfoAllBooks(57,	"List Pawła do Filemona",				"Filem",	1),	 //56
	InfoAllBooks(58,	"List do Hebrajczyków",					"Hbr",		13), //57
	InfoAllBooks(59,	"List Jakuba",									"Jak",		5),	 //58
	InfoAllBooks(60,	"1 List Piotra",								"1Pt",		5),	 //59
	InfoAllBooks(61,	"2 List Piotra",								"2Pt",		3),	 //60
	InfoAllBooks(62,	"1 List Jana",									"1Jan",		5),	 //61
	InfoAllBooks(63,	"2 List Jana",									"2Jan",		1),	 //62
	InfoAllBooks(64,	"3 List Jana",									"3Jan",		1),	 //63
	InfoAllBooks(65,	"List Judy",										"Jud",		1),	 //64
	InfoAllBooks(66,	"Objawienie Jana",							"Obj",		22), //65
	//--- Apokryfy
	InfoAllBooks(67,	"Księga Tobiasza",							"Tob",		14), //66
	InfoAllBooks(68,	"Księga Judyty",								"Judyt",	16), //67
	InfoAllBooks(69,	"Księga I Machabejska",					"1Mach",	16), //68
	InfoAllBooks(70,	"Księga II Machabejska",				"2Mach",	15), //69
	InfoAllBooks(71,	"Księga Mądrości",							"Mądr",		19), //70
	InfoAllBooks(72,	"Księga Syracha",								"Syr",		51), //71
	InfoAllBooks(73,	"Księga Barucha",								"Bar",		6)	 //72
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
	ustrRet = Format("%s %s:%s", ARRAYOFCONST((ustrBook, ustrChapt, ustrVers)));

	return ustrRet;
}