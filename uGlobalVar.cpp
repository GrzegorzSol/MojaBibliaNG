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
										GlobalVar::Global_custrGetDataDir = TPath::Combine(GlobalVar::Global_custrGetExeDir, "Data"),      //Ścieżka dostępu do katalogu z danymi aplikacji
										GlobalVar::Global_custrGetConfigFile = TPath::Combine(GlobalVar::Global_custrGetExeDir, "ConfigFileMyBibleNG.ini"),	//Ścieżka do pliku konfiguracyjnego
										GlobalVar::Global_custrPathFileStartDisplay = TPath::Combine(GlobalVar::Global_custrGetDataDir, "startMyBibleNG.bmp"),	//Ściezka dostępu do grafiki wyświetlanej podczas startu aplikacji
										//GlobalVar::Global_custrExtendInfoTranslate = ".mbin",	//Rozszerzenie pliku z informacją o danym tłumaczeniu. Plik ten tworzy sie przez dodanie tego
										GlobalVar::Global_custrExtendCommentsFiles = ".bfc", //Rozszerzenie plików z komentarzami
										//GlobalVar::Global_custrExtendCommentsPlain = "tfc", //Rozszerzenie plików z komentarzem, bez formatowania, jako czysty tekst
										GlobalVar::Global_custrPathFileInterlinear = TPath::Combine(GlobalVar::Global_custrGetDataDir, "gnt.intrl"),			//Ścieżka dostępu do pliku ze słownikiem gracko-polskim, do wyświetlenia tłumaczenia interlinearnego
										GlobalVar::Global_custrPathMultimediaFilesData = TPath::Combine(GlobalVar::Global_custrGetExeDir, "MultiMediaFiles"),//Ścieżka dostępu do danych multimedialnych
										GlobalVar::Global_custrPathFileFavoriteVers = TPath::Combine(GlobalVar::Global_custrGetDataDir, "FavoritesVerses.fmb"),    //Ścieżka dostępu do pliku z listą ulubionych wersetów
										GlobalVar::Global_custrPathdirComments = TPath::Combine(GlobalVar::Global_custrGetDataDir, "CommentsFile"),      //Katalog do pojedyńczych plików z komentarzami do wersetów
/*****************************************************************************
 *               Stałe dla pliku konfiguracyjnego typu ini                   *
 *****************************************************************************/
										//----- Sekcje Main pliku ini
										GlobalVar::GlobalIni_MainSection_Main="MAIN",           //Główna sekcja MAIN pliku ini
												GlobalVar::GlobalIni_PathMultiM1="MultimediaPath1", GlobalVar::GlobalIni_PathMultiM2="MultimediaPath2", GlobalVar::GlobalIni_PathMultiM3="MultimediaPath3", //Ścieżki dostępu do wybranych katalogów z multimediami
												GlobalVar::GlobalIni_AppWidth="ApplicWinWidth", GlobalVar::GlobalIni_AppHeight="ApplicWinHeight", //Szerokość i wysokość głównego okna
                    //----- Sekcje Flags pliku ini
										GlobalVar::GlobalIni_FlagsSection_Main="FLAGS",         //Główna sekcja FLAGS pliku ini
												GlobalVar::GlobalIni_IsDisplaySplashStart="IsDisplaySplashStart", //Czy wyświetlać winiete startową podczas startu aplikacji
												GlobalVar::GlobalIni_IsRequestEnd="IsRequestEndApplication",      //czy pytać o zamknięcie aplikacji
												GlobalVar::GlobalIni_IsOnlyOne="IsOnlyOne",            //Dozwolona tylko jedna kopia aplikacji
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
										//----- Sekcja Others
										GlobalVar::GlobalIni_OthersSection="OTHERS",           //Główna sekcja OTHERS
												GlobalVar::GlobalIni_OtherSizeFontMain="OtherSizeFontMain",    //Wielkość głównej czcionki tekstu wersetu
												GlobalVar::GlobalIni_OtherSizeFontAdress="OtherSizeFontAdress",  //Wielkość czcionki, adresu wersetu
												GlobalVar::GlobalIni_OtherSizeFontNameTranslators="OtherSizeFontTranslators", //Wielkość czcionki nazwy tłumaczeń
												GlobalVar::GlobalIni_FontNameMain="FontnameMain",           //Nazwa głównej czcionki
												GlobalVar::GlobalIni_FontNameAdress="FontNameAdress",         //Nazwa czcionki adresu wersetu
												GlobalVar::GlobalIni_FontNameTranslators="FontNameTranslators",    //Nazwa czcionki nazwy tłymaczenia
										//----- Sekcje Translates
										GlobalVar::GlobalIni_TranslatesSection_Main="TRANSLATES", 				        //Główna sekcja TRANSLATES pliku ini
												GlobalVar::GlobalIni_ExcludeTranslates="ExcludeTranslates";    //Tłumaczenia nie wyświetlane
//----- Wersje plików i bibliotek
UnicodeString	GlobalVar::Global_ustrVerGsReadBibleTextClass = "", //Wersja biblioteki GsReadBibleTextClass
							GlobalVar::Global_ustrVerAplicMain = ""; //Wersja głównej biblioteki
//***************************************************************************
TStringList *GlobalVar::Global_SListPathMultiM=0;  //Ścieżki dostępu do wybranych, przez użytkownika katalogów z multimediami
TMemIniFile *GlobalVar::Global_ConfigFile=0;			 //Globalny wskażnik na plik konfiguracyjny
TStringDynArray GlobalVar::SDirTranslatesList;     //Lista ścieżek dostępu do, wszystkich dostępnych tłumaczeń
THashedStringList *GlobalVar::Global_HSListAllFavoritiesVers=0; //String lista do wszystkich ulubionych wesrsetów
int GlobalVar::iReturnUpdate=0; //Wynik działania procedury sprawdzającej dostępność nowej wersji na serwerze.
																//iReturnUpdate == -1, wersja na komputarze jest nowsza niż na serwerze
																//iReturnUpdate == 0, obje wersje są jednakowe, nie potrzeba aktualizacji
										 						//iReturnUpdate == 1, wersja na komputerze jest starsza niż na serwerze, potrzeba zaktualizować

