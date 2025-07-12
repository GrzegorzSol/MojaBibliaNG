/*
	Całkowicie publiczna i statyczna klasa globalnych zmiennych, dostępnych wszystkim modułom
*/
//---------------------------------------------------------------------------
#pragma hdrstop

#include "uGlobalVar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif
//---
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug("");
#endif
*/
// DEFINICJE STATYCZNYCH STAŁYCH KLASY GlobalVar
const UnicodeString GlobalVar::Global_custrNameIVerFile="MBibleNG.iver",				 //Nazwa pliku z wersją aplikacji. Plik słuzy do sparawdzamia aktualnej wersji
										GlobalVar::Global_custrGetExeDir = System::Sysutils::ExtractFilePath(Application->ExeName); // Ścieżka dostępu do katalogu głównego programu;
#if defined(_DEBUGINFO_)
	//Jeśli projekt jest kompilowany z oknem konsoli, dane dla aplikacji są pobierane nie standartowo z zewnętrznego katalogu
	const UnicodeString GlobalVar::Global_custrGetDataDir= "f:\\DevelopGS\\Dane dla MojaBiblia\\Data\\";					 // Ścieżka dostępu do katalogu z danymi aplikacji
#else
	//Kompilowanie bez kosoli, dane są umieszczone w standartowym miejscu
	const UnicodeString GlobalVar::Global_custrGetDataDir = TPath::Combine(GlobalVar::Global_custrGetExeDir, "Data");	 // Ścieżka dostępu do katalogu z danymi aplikacji
#endif
const UnicodeString GlobalVar::Global_custrGetVersionUpdate=TPath::Combine(GlobalVar::Global_custrGetExeDir, GlobalVar::Global_custrNameIVerFile),	 // Ścieżka dostepu do pilku tekstowego z wersją, do aktualizacji
										GlobalVar::Global_custrPathStrongDict=TPath::Combine(GlobalVar::Global_custrGetDataDir, "StrongDict.strdi"), // Ścieżka dostępu do pliku ze słownikiem stronga
										GlobalVar::Global_custrPathImagesStyles=TPath::Combine(GlobalVar::Global_custrGetDataDir, "PreviewsStyles"),		 // Ścieżka do katalogu z podglądem stylów graficznych aplikacji
										GlobalVar::Global_custrPathAllReadingPlan=TPath::Combine(GlobalVar::Global_custrGetDataDir, "ReadingPlan"),	// Ścieżka dostępu do katalogu z planami czytania biblii
										GlobalVar::GlobalPath_CurrentActivePlan=TPath::Combine(GlobalVar::Global_custrPathAllReadingPlan, "AktualnyPlan.jcp"),		 // Ścieżka dostepu do pliku z dziennikiem czytania aktualnego planu
										GlobalVar::Global_custrPathSearchFavorities=TPath::Combine(GlobalVar::Global_custrGetDataDir, "SearchFavorities"), // Ścieżka dostę[u do katalogu z ulubionymi plikami wyników wyszukiwania
										GlobalVar::Global_custrGetConfigFile=TPath::Combine(GlobalVar::Global_custrGetExeDir, "ConfigFileMyBibleNG.ini"),				// Ścieżka do pliku konfiguracyjnego
										GlobalVar::Global_custrPathLastUsedAddressFile=TPath::Combine(GlobalVar::Global_custrGetDataDir, "LastUsedAddress.lud"),// Ścieżka dostępu do pliku z ostatnio używanymi adresami
										GlobalVar::Global_custrPathGlobalHelp=TPath::Combine(GlobalVar::Global_custrGetExeDir, "HelpMojaBibliaNT.chm"),			// Ścieżka dostępu do pliku pomocy
										GlobalVar::Global_custrPathHistory=TPath::Combine(GlobalVar::Global_custrGetDataDir, "HistoryChaptersOpen.hco"),					// Ścieżka dostępu do pliku historii
//Graficzne loga z rozszerzeniem .gli
										GlobalVar::Global_custrPathBackgroundWindow=TPath::Combine(GlobalVar::Global_custrGetDataDir, "BackgroundWindowImg.gli"),// Grafika z podkładem okna głównego
										GlobalVar::Global_custrPathSearchLogo=TPath::Combine(GlobalVar::Global_custrGetDataDir, "SearchLogo.gli"),// Logo w oknie wyszukiwania
										GlobalVar::Global_custrPathSetupsLogo=TPath::Combine(GlobalVar::Global_custrGetDataDir, "SetupsLogo.gli"),// Logo w oknie ustawień
										GlobalVar::Global_custrPathBacgroundImageText=TPath::Combine(GlobalVar::Global_custrGetDataDir, "Tora.png"), // Logo główne podkładu
//---
										GlobalVar::Global_custrPathFileWordVersesExistGrec=TPath::Combine(GlobalVar::Global_custrGetDataDir, "WordToExistGrec.wte"), // Ścieżka dostępu do pliku z danymi wystapień w wersetach, dla tekstu greckiegoposzczególnych słów // [08-06-2024]
										GlobalVar::Global_custrPathFileWordVersesExistHbr=TPath::Combine(GlobalVar::Global_custrGetDataDir, "WordToExistHbr.wte"), // Ścieżka dostępu do pliku z danymi wystapień w wersetach, dla tekstu hebrajskiego, poszczególnych słów // [31-07-2024]
										GlobalVar::Global_custrPathFileInterlinear=TPath::Combine(GlobalVar::Global_custrGetDataDir, "gnt.intrl"),			// Ścieżka dostępu do pliku ze słownikiem gracko-polskim, do wyświetlenia tłumaczenia interlinearnego
										GlobalVar::Global_custrPathMultimediaFilesData=TPath::Combine(GlobalVar::Global_custrGetExeDir, "MultiMediaFiles"),// Ścieżka dostępu do danych multimedialnych
										GlobalVar::Global_custrPathFileFavoriteVers=TPath::Combine(GlobalVar::Global_custrGetDataDir, "FavoritesVerses.fmb"),		// Ścieżka dostępu do pliku z listą ulubionych wersetów
										GlobalVar::Global_custrPathDirComments=TPath::Combine(GlobalVar::Global_custrGetDataDir, "CommentsFile"),			// Katalog do pojedyńczych plików z komentarzami do wersetów
										GlobalVar::Global_custrPathHistorySearch=TPath::Combine(GlobalVar::Global_custrGetDataDir, "HistorySearch.fhs"),		 // Ścieżka dostępu do pliku z zapisaną historia tekstów wyszukiwanych
										GlobalVar::Global_custrPathImageBackgroundMainText=TPath::Combine(Global_custrGetDataDir, "backgroundmaintext.png"),	// Ściezka dostepu do grafiki jako podkładu dla głównego tekstu
										//----- Zabezpieczenie przed uruchomieniem drugiej kopi aplikacji
										GlobalVar::Global_ustrMutexName="MutexName_" + System::Sysutils::ExtractFileName(Application->ExeName);	//Mutekst główny aplikacji

void __fastcall GlobalVar::Global_InitGlobalVariables()
/**
	OPIS METOD(FUNKCJI): Ustawienie globalnych zmiennych dla całej aplikacji
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
//	#if defined(__BORLANDC__) && defined(__clang__) && defined(_WIN64) && defined(__MINGW64__)
//		#if defined(_DEBUGINFO_)
//			// Kompilator dla Win64 typu Modern
//			GsDebugClass::WriteDebug("BCC64X Modern");
//		#endif
//	#elif defined(__BORLANDC__) && defined(__clang__) && defined(_WIN64)
//		#if defined(_DEBUGINFO_)
//			// Tradycyjny kompilator dla Win64
//			GsDebugClass::WriteDebug("BCC64C Standart");
//		#endif
//	#elif defined(__BORLANDC__) && defined(__clang__) && defined(_WIN32) && !defined(_WIN64)
//		#if defined(_DEBUGINFO_)
//			// Tradycyjny kompilator dla Win32
//			GsDebugClass::WriteDebug("BCC32C i BCC32X Standart");
//		#endif
//	#endif
}
