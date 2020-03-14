#ifndef uGlobalVarH
#define uGlobalVarH
//---------------------------------------------------------------------------
#include <Forms.hpp>
#include <System.IniFiles.hpp>
//#define _DEBUGINFO_  //Używanie okna konsoli do debugowania aplikacji
//#define _FULL_DEBUG_ //Używane do pełnej kontroli wersji release
#if defined(_DEBUGINFO_)
	#include "GsDebugClass.h"
#endif
/*
	Całkowicie publiczna i statyczna klasa globalnych zmiennych, dostępnych wszystkim modułom
*/
struct GlobalVar
{
	const static UnicodeString Global_custrGetExeDir,           //Ścieżka dostępu do katalogu głównego programu;
                             Global_custrNameIVerFile,        //Nazwa pliku z wersją aplikacji. Plik słuzy do sparawdzamia aktualnej wersji
                             Global_custrGetVersionUpdate,    //Ścieżka dostepu do pilku tekstowego z wersją, do aktualizacji
														 Global_custrImagesPreviewStyles, //Ścieżka dostępu do katalogu z grafiką podglądów stylów
														 Global_custrGetDataDir,          //Ścieżka dostępu do katalogu z danymi aplikacji
														 Global_custrGetConfigFile,				//Ścieżka do pliku konfiguracyjnego
														 //Global_custrPathFileStartDisplay,		//Ściezka dostępu do grafiki wyświetlanej podczas startu aplikacj
														 //Global_custrExtendInfoTranslate,	//Rozszerzenie pliku z informacją o danym tłumaczeniu. Plik ten tworzy sie przez dodanie tego
                             Global_custrPathBackgroundWindow,//Grafika z podkładem okna głównego
														 Global_custrExtendCommentsFiles, //Rozszerzenie plików z komentarzami
														 //Global_custrExtendCommentsPlain, //Rozszerzenie plików z komentarzem, bez formatowania, jako czysty tekst
														 Global_custrPathFileInterlinear,			//Ścieżka dostępu do pliku ze słownikiem gracko-polskim, do wyświetlenia tłumaczenia interlinearnego
														 Global_custrPathMultimediaFilesData,//Ścieżka dostępu do danych multimedialnych
														 Global_custrPathFileFavoriteVers,    //Ścieżka dostępu do pliku z listą ulubionych wersetów
														 Global_custrPathdirComments,      //Katalog do pojedyńczych plików z komentarzami do wersetów
														 //--- Ustawienia parametrów połączenia z siecią, w celu akyualizacji
														 Global_custrFTPSourceVersionFile, //Ścieżka sieciowa do pliku wersji
														 Global_custrFTPSourceApplicFile, //Ścieżka sieciowa do głównego pliku aplikacji
														 Global_custrHostName, //Adres hosta
														 Global_custrUserHost, //Nazwa użytkownika
														 Global_custrPassword, //Hasło do hosta
                             Global_custrNameUpd,  //nazwa aplikacji zewnętrznej do aktualizacji
														 Global_ustrPathApplicUpdate,   //Ścieżka dostępu do konsolowej aplikacji do aktualizacji
														 Global_ustrMutexName,  //Mutekst główny aplikacji
                             Global_ustrNameDirUpdate,//nazwa katalogu z poprawkami
/*****************************************************************************
 *               Stałe dla pliku konfiguracyjnego typu ini                   *
 *****************************************************************************/
														 //----- Sekcje Main pliku ini
														 GlobalIni_MainSection_Main,           //Główna sekcja Main pliku ini
																GlobalIni_PathMultiM1, GlobalIni_PathMultiM2, GlobalIni_PathMultiM3, //Ścieżki dostępu do wybranych katalogów z multimediami
																GlobalIni_AppWidth, GlobalIni_AppHeight, //Szerokość i wysokość głównego okna
																GlobalIni_LoadBooksOnExit, //Lista otwartych ksią i rozdziałów w momencie zamknięcia aplikacji
														 //----- Sekcje Flags pliku ini
														 GlobalIni_FlagsSection_Main,          //Główna sekcja FLAGS pliku ini
																GlobalIni_IsDisplaySplashStart, //Czy wyświetlać winiete startową podczas startu aplikacji
																GlobalIni_IsRequestEnd,         //czy pytać o zamknięcie aplikacji
																GlobalIni_IsOnlyOne,            //Dozwolona tylko jedna kopia aplikacji
																GlobalIni_IsAutoFindUpdate,       //Czy sprawdzać aktualizacje podczas uruchamiania aplikacji
                                GlobalIni_IsLoadBooksOnInit, //Czy po ponownym uruchomieniu aplikacji, będą wczytywane kksięgi, które zostały ostatnio zamknięte podczas opuszczania aplikacji?
																//GlobalIni_IsStartInfo,          //Podczas startu aplikacji czy jest wyświetlane powitanie
														 //----- Sekcje Colors pliku ini
														 GlobalIni_ColorsSection_Main,         //Główna sekcja COLORS pliku ini
																GlobalIni_ColorFavoritesVers,       //Kolor zaznaczenie ulubionych wersetów
																GlobalIni_ColorCommentVers,         //Kolor zaznaczenie wersetów, do których istnieje komentarz
																GlobalIni_ColorBackgroundText,      //Kolor podkładu pod wyswietlany tekst
																GlobalIni_ColorAdressVersFullTranslates, //Kolor adresu, wersetu dla pełnego tłumaczenia
																GlobalIni_ColorAdressVersPartTranslates, //Kolor adresu, wersetu dla tłumaczeń częściowych(oryginalnych, lub innych)
																GlobalIni_ColorNameFullTranslates,  //Kolor nazwy pełnego tłumaczenia
																GlobalIni_ColorNamePartTranslates,  //Kolor nazwy częściowego tłumaczenia
																GlobalIni_ColorBackgroundMarkerComment,//Kolor podkładu dla znacznika, istnienia komentarza dla wersetu
																GlobalIni_ColorOryginalTranslates,  //Kolor czcionki, dla oryginalnych tłumaczeń
																GlobalIni_ColorNameOryginalTranslate, //Kolor nazwy oryginalnego tłumaczenia
																GlobalIni_ColorAdressOryginalTranslate, //Kolor adresu oryginalnego tłumaczenia
														 //----- Sekcja Others
														 GlobalIni_OthersSection,           //Główna sekcja OTHERS
																GlobalIni_OtherSizeFontMain,    //Wielkość głównej czcionki tekstu wersetu
																GlobalIni_OtherSizeFontAdress,  //Wielkość czcionki, adresu wersetu
																GlobalIni_OtherSizeFontNameTranslators, //Wielkość czcionki nazwy tłumaczeń
																GlobalIni_FontNameMain,           //Nazwa głównej czcionki
																GlobalIni_FontNameAdress,         //Nazwa czcionki adresu wersetu
																GlobalIni_FontNameTranslators,    //Nazwa czcionki nazwy tłymaczenia
														 //----- Sekcje Translates
														 GlobalIni_TranslatesSection_Main, 				//Główna sekcja TRANSLATES pliku ini
																GlobalIni_ExcludeTranslates;    //Tłumaczenia nie wyświetlane
 //----- Wersje plików i bibliotek
 static UnicodeString Global_ustrVerGsReadBibleTextClass, //Wersja biblioteki GsReadBibleTextClass
											Global_ustrVerAplicMain, 						//Wersja głównej biblioteki
											//--- Ustawienia parametrów połączenia z siecią, w celu akyualizacji
											Global_custrLocalVersionFile, //Ścieżka dostępu lokalna, do pobranego pliku wersji
											Global_custrLocalApplicFile; //Ścieżka dostępu lokalna, do pobranej aplikacji
 const static unsigned char cuchABlendValue; //Współczynnik przezroczystości okna, gdy jest nieaktywne
//***************************************************************************
	static TStringList *Global_SListPathMultiM;  //Ścieżki dostępu do wybranych, przez użytkownika katalogów z multimediami
	static TMemIniFile *Global_ConfigFile;			 //Globalny wskażnik na plik konfiguracyjny
	static TStringDynArray SDirTranslatesList;   //Lista ścieżek dostępu do, wszystkich dostępnych tłumaczeń
	static THashedStringList *Global_HSListAllFavoritiesVers; //String lista do wszystkich ulubionych wesrsetów
	static int iReturnUpdate; //Wynik działania procedury sprawdzającej dostępność nowej wersji na serwerze.
														//iReturnUpdate == -1, wersja na komputarze jest nowsza niż na serwerze
														//iReturnUpdate == 0, obje wersje są jednakowe, nie potrzeba aktualizacji
										 				//iReturnUpdate == 1, wersja na komputerze jest starsza niż na serwerze, potrzeba zaktualizować
};
#endif
