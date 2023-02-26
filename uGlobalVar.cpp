/*
	Całkowicie publiczna i statyczna klasa globalnych zmiennych, dostępnych wszystkim modułom
*/
//---------------------------------------------------------------------------
#pragma hdrstop

#include "uGlobalVar.h"
#include <System.IOUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)

const UnicodeString GlobalVar::Global_custrGetExeDir = System::Sysutils::ExtractFilePath(Application->ExeName), //Ścieżka dostępu do katalogu głównego programu;
										GlobalVar::Global_custrNameIVerFile = "MBibleNG.iver",        //Nazwa pliku z wersją aplikacji. Plik słuzy do sparawdzamia aktualnej wersji
										GlobalVar::Global_custrGetVersionUpdate = TPath::Combine(GlobalVar::Global_custrGetExeDir, GlobalVar::Global_custrNameIVerFile),    //Ścieżka dostepu do pilku tekstowego z wersją, do aktualizacji
										#if defined(_DEBUGINFO_)
											//Jeśli projekt jest kompilowany z oknem konsoli, dane dla aplikacji są pobierane nie standartowo z zewnętrznego katalogu
											GlobalVar::Global_custrGetDataDir = "f:\\DevelopGS\\Dane dla MojaBiblia\\Data\\",
										#else
											//Kompilowanie bez kosoli, dane są umieszczone w standartowym miejscu
											GlobalVar::Global_custrGetDataDir = TPath::Combine(GlobalVar::Global_custrGetExeDir, "Data"),      //Ścieżka dostępu do katalogu z danymi aplikacji
										#endif
										GlobalVar::Global_custrPathAllReadingPlan = TPath::Combine(GlobalVar::Global_custrGetDataDir, "ReadingPlan"),//Ścieżka dostępu do katalogu z planami czytania biblii
										GlobalVar::Global_custrGetConfigFile = TPath::Combine(GlobalVar::Global_custrGetExeDir, "ConfigFileMyBibleNG.ini"),	//Ścieżka do pliku konfiguracyjnego
										GlobalVar::Global_custrPathLastUsedAddressFile = TPath::Combine(GlobalVar::Global_custrGetDataDir, "LastUsedAddress.lud"),//Ścieżka dostępu do pliku z ostatnio używanymi adresami
										//Graficne loga z rozszerzeniem .gli
										GlobalVar::Global_custrPathBackgroundWindow = TPath::Combine(GlobalVar::Global_custrGetDataDir, "BackgroundWindowImg.gli"),//Grafika z podkładem okna głównego
										GlobalVar::Global_custrPathSearchLogo = TPath::Combine(GlobalVar::Global_custrGetDataDir, "SearchLogo.gli"),//Logo w oknie wyszukiwania
										GlobalVar::Global_custrPathSetupsLogo = TPath::Combine(GlobalVar::Global_custrGetDataDir, "SetupsLogo.gli"),//Logo w oknie ustawień
										//---
										GlobalVar::Global_custrExtendCommentsFiles = ".bfc", //Rozszerzenie plików z komentarzami
										//GlobalVar::Global_custrExtendCommentsPlain = "tfc", //Rozszerzenie plików z komentarzem, bez formatowania, jako czysty tekst
										GlobalVar::Global_custrPathFileInterlinear = TPath::Combine(GlobalVar::Global_custrGetDataDir, "gnt.intrl"),			//Ścieżka dostępu do pliku ze słownikiem gracko-polskim, do wyświetlenia tłumaczenia interlinearnego
										GlobalVar::Global_custrPathMultimediaFilesData = TPath::Combine(GlobalVar::Global_custrGetExeDir, "MultiMediaFiles"),//Ścieżka dostępu do danych multimedialnych
										GlobalVar::Global_custrPathFileFavoriteVers = TPath::Combine(GlobalVar::Global_custrGetDataDir, "FavoritesVerses.fmb"),    //Ścieżka dostępu do pliku z listą ulubionych wersetów
										GlobalVar::Global_custrPathDirComments = TPath::Combine(GlobalVar::Global_custrGetDataDir, "CommentsFile"),      //Katalog do pojedyńczych plików z komentarzami do wersetów
										GlobalVar::Global_custrPathHistorySearch = TPath::Combine(GlobalVar::Global_custrGetDataDir, "HistorySearch.fhs"),    //Ścieżka dostępu do pliku z zapisaną historia tekstów wyszukiwanych
										//--- Ustawienia parametrów połączenia z siecią, w celu akyualizacji
										GlobalVar::Global_custrFTPSourceVersionFile = "/public_html/wp-content/uploads/MojaBibliaNG/MBibleNG.iver", //Ścieżka sieciowa do pliku wersji
										GlobalVar::Global_custrFTPSourceApplicFile = "/public_html/wp-content/uploads/MojaBibliaNG/MojaBibliaNG.zip", //Ścieżka sieciowa do głównego pliku aplikacji
										GlobalVar::Global_custrHostName = "ftp.nasz-salem.pl", //Adres hosta
										GlobalVar::Global_custrUserHost = "naszsalem", //Nazwa użytkownika
										GlobalVar::Global_custrPassword = "OVpVwXtvdY", //Hasło do hosta
										GlobalVar::Global_custrNameUpd = "winmbupd.exe",  //nazwa aplikacji zewnętrznej do aktualizacji
										GlobalVar::Global_ustrPathApplicUpdate = TPath::Combine(GlobalVar::Global_custrGetExeDir, GlobalVar::Global_custrNameUpd),   //Ścieżka dostępu do konsolowej aplikacji do aktualizacji
										GlobalVar::Global_ustrMutexName = "MutexName_" + System::Sysutils::ExtractFileName(Application->ExeName),	//Nazwa mutexa, do sprawdzenie,  //Mutekst główny aplikacji
										GlobalVar::Global_ustrNameDirUpdate = "MojaBibliaNG",//nazwa katalogu z poprawkami
										//----- Ustawienia dotyczące pomocy i tipsów
										GlobalVar::Global_ustrDirHelp = TPath::Combine(GlobalVar::Global_custrGetDataDir, "HelpData"),	//Ścieżka dostępu do katalogu z plikami pomocy
										GlobalVar::Global_ustrExtPathHelp = "hlpmb",				//Rozszerzenie plików pomocy
										GlobalVar::Global_ustrCoreNameHelp = "FileHlp", //Główny rdzeń nazwy, do której będzie przyczepiony indeks pomocy
										//----- Ustawienia pomocy
										GlobalVar::Global_ustrExPathTipsImageHelp = "timg",//Rozszerzenie grafiki to tipsów
										GlobalVar::Global_ustrCorePathNameImageTips = "ImageTips", //Główny rdzeń nazwy pliku graficznego, do której będzie przyczepiony indeks pomocy tipsów
										//----- Ustawienia pomocu 2
										GlobalVar::Global_ustrCoreNameFileTips = "FileTips", //Rdzeń nazwy pliku wskazówek
										GlobalVar::Global_ustrExPathFileTips = "tfhlp",//Rozszerzenie plików wskazówek
                    //----- Syle
										GlobalVar::Global_DefaultStyleName = "Windows", //Domyślny styl
/*****************************************************************************
 *               Stałe dla pliku konfiguracyjnego typu ini                   *
 *****************************************************************************/
										//----- Sekcje Main pliku ini
										GlobalVar::GlobalIni_MainSection_Main="MAIN",           //Główna sekcja MAIN pliku ini
												GlobalVar::GlobalIni_PathMultiM1="MultimediaPath1", GlobalVar::GlobalIni_PathMultiM2="MultimediaPath2", GlobalVar::GlobalIni_PathMultiM3="MultimediaPath3", //Ścieżki dostępu do wybranych katalogów z multimediami
												GlobalVar::GlobalIni_AppWidth="ApplicWinWidth", GlobalVar::GlobalIni_AppHeight="ApplicWinHeight", //Szerokość i wysokość głównego okna
												GlobalVar::GlobalIni_LoadBooksOnExit="LoadBooksOnExit", //Lista otwartych ksiąg i rozdziałów w momencie zamknięcia aplikacji
										//----- Sekcje Flags pliku ini
										GlobalVar::GlobalIni_FlagsSection_Main="FLAGS",         //Główna sekcja FLAGS pliku ini
												GlobalVar::GlobalIni_IsDisplaySplashStart="IsDisplaySplashStart", //Czy wyświetlać winiete startową podczas startu aplikacji
												GlobalVar::GlobalIni_IsRequestEnd="IsRequestEndApplication",      //czy pytać o zamknięcie aplikacji
												GlobalVar::GlobalIni_IsOnlyOne="IsOnlyOne",            //Dozwolona tylko jedna kopia aplikacji
												GlobalVar::GlobalIni_IsAutoFindUpdate="IsAutoFindUpdate",       //Czy sprawdzać aktualizacje podczas uruchamiania aplikacji
												GlobalVar::GlobalIni_IsLoadBooksOnInit="IsLoadBooksOnInit", //Czy po ponownym uruchomieniu aplikacji, będą wczytywane kksięgi, które zostały ostatnio zamknięte podczas opuszczania aplikacji?
												GlobalVar::GlobalIni_IsTipsWindowStart="IsTipsWindowStart", //Czy po uruchomieniu aplikacji uruchomić okno szybkich podpowiedzi
										//----- Sekcje Colors pliku ini
										GlobalVar::GlobalIni_ColorsSection_Main="COLORS",       //Główna sekcja COLORS pliku ini
												GlobalVar::GlobalIni_ColorFavoritesVers="ColorsFavoritesVers",       //Kolor zaznaczenie ulubionych wersetów
												GlobalVar::GlobalIni_ColorCommentVers="ColorCommentVers",         //Kolor zaznaczenie wersetów, do których istnieje komentarz
												GlobalVar::GlobalIni_ColorBackgroundText="ColorBackgroundText",      //Kolor podkładu pod wyswietlany tekst,
												GlobalVar::GlobalIni_ColorAdressVersFullTranslates="ColorAdressVersFullTranslates", //Kolor adresu, wersetu dla pełnego tłumaczenia
												GlobalVar::GlobalIni_ColorAdressVersPartTranslates="ColorAdressVersPartTranslates", //Kolor adresu, wersetu dla tłumaczeń częściowych(oryginalnych, lub innych)
												GlobalVar::GlobalIni_ColorNameFullTranslates="ColorNameFullTranslates",  //Kolor nazwy pełnego tłumaczenia
												GlobalVar::GlobalIni_ColorNamePartTranslates="ColorNamePartTranslates",  //Kolor nazwy częściowego tłumaczenia
												GlobalVar::GlobalIni_ColorBackgroundMarkerComment="ColorBackgroundMarkerComment", //Kolor podkładu dla znacznika, istnienia komentarza dla wersetu
												GlobalVar::GlobalIni_ColorOryginalTranslates="ColorOryginalTranslates",  //Kolor czcionki, dla oryginalnych tłumaczeń
												GlobalVar::GlobalIni_ColorNameOryginalTranslate="ColorNameOryginalTranslate", //Kolor nazwy oryginalnego tłumaczenia
												GlobalVar::GlobalIni_ColorAdressOryginalTranslate="ColorAdressOryginalTranslate", //Kolor adresu oryginalnego tłumaczenia
                    //----- Sekcja ColorsSetups pliku ini
										GlobalVar::GlobalIni_ColorsSetupsSection_Main="COLORSSETUPS", //Główna sekcja ColorsSetups
												GlobalVar::GlobalIni_ColorsSetupsBackGroundAllListSearch="ColorsSetupsBackGroundAllListSearch", //Kolor podkłady dla wyświetlenia wszystkich znalezionych wersetów
												GlobalVar::GlobalIni_ColorsSetupBackGroundSelectBookSearch="ColorsSetupBackGroundSelectBookSearch",//Kolor podkładu dla wyświetlenia znalezionych wersetów w wybranej księdze
												GlobalVar::GlobalIni_ColorsSetupBackGroundSelectVers="ColorsSetupBackGroundSelectVers",      //Kolor podkładu dla wyświetlenie pojedyńczego wybranego wersetu
										//----- Sekcja ParametersSetupsSearch
										GlobalVar::GlobalIni_ParametersSetupsSearch_Main="PARAMETERSSETUPSSEARCH", //Główna sekcja ParametersSetupsSearch
												GlobalVar::GlobalIni_IsMemorySetupsSearch="IsMemorySetupsSearch", //Czy zapamiętywać parametry wyszukiwania
												GlobalVar::GlobalIni_Translate="SetupSearchTranslate", //Tłumaczenie
												GlobalVar::GlobalIni_SetupRangeBooks="SetupSearchRangeBooks",//Zakres ksiąg
												GlobalVar::GlobalIni_StartUserRange="SetupSearchStartUserRangeBook", //Początek zakresu wyszukiwań
												GlobalVar::GlobalIni_StopUserRange="SetupSearchStopUserRangeBook",  //Koniec zakresu wyszukiwań
												GlobalVar::GlobalIni_TextSearch="SetupsSearchText", //Tekst wyszukiwany
												GlobalVar::GlobalIni_IsSizeTextSearch="IsSizeTextSearch", //Podczas wyszukiwania jest brana wielkość liter
												GlobalVar::GlobalIni_IsRegSearch="IsRegSearch", //Podczas wyszukiwania są używane wyrażenia regularne
										//----- Sekcja Others
										GlobalVar::GlobalIni_OthersSection="OTHERS",           //Główna sekcja OTHERS
												GlobalVar::GlobalIni_OtherSizeFontMain="OtherSizeFontMain",    //Wielkość głównej czcionki tekstu wersetu
												GlobalVar::GlobalIni_OtherSizeFontAdress="OtherSizeFontAdress",  //Wielkość czcionki, adresu wersetu
												GlobalVar::GlobalIni_OtherSizeFontNameTranslators="OtherSizeFontTranslators", //Wielkość czcionki nazwy tłumaczeń
												GlobalVar::GlobalIni_FontNameMain="FontnameMain",           //Nazwa głównej czcionki
												GlobalVar::GlobalIni_FontNameAdress="FontNameAdress",         //Nazwa czcionki adresu wersetu
												GlobalVar::GlobalIni_FontNameTranslators="FontNameTranslators",    //Nazwa czcionki nazwy tłymaczenia
												GlobalVar::GlobalIni_SelectStyleName="SelectStyleName",        //Nazwa wybranego stylu
										//----- Sekcje Translates
										GlobalVar::GlobalIni_TranslatesSection_Main="TRANSLATES", 				        //Główna sekcja TRANSLATES pliku ini
												GlobalVar::GlobalIni_ExcludeTranslates="ExcludeTranslates",    //Tłumaczenia nie wyświetlane
										//----- Sekcja plany czytania biblii
										GlobalVar::GlobalIni_ReadingPlan_Main="READINGPLAN",     //Główna sekcja ustawień planu czytania biblii
											GlobalVar::GlobalIni_TranslateRPlan="TypeTranslateReadingPlan",//Tłumaczenie używane w planie
											GlobalVar::GlobalIni_IDTranslateRPlan="IDTranslateReadingPlan",//Numer identyfikacyjny tłumaczenie wykorzystywanego w planie czytania
											GlobalVar::GlobalIni_SelectPlan="SelectReadingPlan",           //Wybrany planu
											GlobalVar::GlobalIni_StartDate="StarDateReadingPlan",         //Data rozpoczęcia planu czytania biblii
											GlobalVar::GlobalIni_IsStartPlan="IsStartReadingPlan",        //Czy rozpoczęto plan czytania Pisma Świetego
											GlobalVar::GlobalIni_FontPlan="FontDisplayNameReadingPlan",   //Czcionka wyświetlana w planie czytania biblii
											GlobalVar::GlobalIni_SizeFontPlan="FontSizeDisplayReadingPlan",//Wielkość czcionki w planie
										GlobalVar::Global_ustrFileReadingPlanExtend=".rpf";   //Rozszerzenie plików planów czytania = "*.rpf";
//----- Wersje plików i bibliotek
UnicodeString	GlobalVar::Global_ustrVerGsReadBibleTextClass = "", //Wersja biblioteki GsReadBibleTextClass
							GlobalVar::Global_ustrVerAplicMain = "", //Wersja głównej biblioteki
							//--- Ustawienia parametrów połączenia z siecią, w celu akyualizacji
							GlobalVar::Global_custrLocalVersionFile = "", //Ścieżka dostępu lokalna, do pobranego pliku wersji
							GlobalVar::Global_custrLocalApplicFile = ""; //Ścieżka dostępu lokalna, do pobranej aplikacji
const unsigned char GlobalVar::cuchABlendValue = 200; //Współczynnik przezroczystości okna, gdy jest nieaktywne
bool GlobalVar::IsWindows10 = false; //Zmienna wskazuje czy klasa została uruchomiona na systemie Windows 10
//***************************************************************************
TStringList *GlobalVar::Global_SListPathMultiM=nullptr;  //Ścieżki dostępu do wybranych, przez użytkownika katalogów z multimediami
TMemIniFile *GlobalVar::Global_ConfigFile=nullptr;			 //Globalny wskażnik na plik konfiguracyjny
TStringDynArray GlobalVar::SDirTranslatesList;     //Lista ścieżek dostępu do, wszystkich dostępnych tłumaczeń
THashedStringList *GlobalVar::Global_HSListAllFavoritiesVers=nullptr; //String lista do wszystkich ulubionych wesrsetów
int GlobalVar::iReturnUpdate=-1; //Wynik działania procedury sprawdzającej dostępność nowej wersji na serwerze.
																//iReturnUpdate == -1, wersja na komputarze jest nowsza niż na serwerze
																//iReturnUpdate == 0, obje wersje są jednakowe, nie potrzeba aktualizacji
																//iReturnUpdate == 1, wersja na komputerze jest starsza niż na serwerze, potrzeba zaktualizować

