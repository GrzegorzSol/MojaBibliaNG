#ifndef uGlobalVarH
#define uGlobalVarH
//---------------------------------------------------------------------------
#include <Forms.hpp>
#include <System.IniFiles.hpp>
#include <System.IOUtils.hpp>
#include <Vcl.HtmlHelpViewer.hpp>
#include "HelpMojaBibliaNT.h"
//#define _DEBUGINFO_	 //Używanie okna konsoli do debugowania aplikacji
#if defined(_DEBUGINFO_)
	#include "GsDebugClass.h"
#endif
//Stałe dla tablicy tekstów pomocy. Numery indeksów odpowiadaja indeksom icon w objekcie kImageListMainActive, klay TImageList
enum {enHelpTextIndex_CloseSheet=0,		//0.Zamknięcie aktywnej zakładki
			enHelpTextIndex_Search,					//1.Wyszukiwanie
			enHelpTextIndex_Setups,					//2.Ustawienia
			enHelpTextIndex_SaveChapter,		//3.Zapis aktualnego rozdziału
			enHelpTextIndex_ChoiceVers,			//4.Wybór i przegląd pojedyńczego wersetu
			enHelpTextIndex_InformHelp,			//5.Pomoc i informacje
			enHelpTextIndex_CorcondanceGrek,//6.Konkordancja grecka
			enHelpTextIndexSchemeVers,			//7.Projektowanie zależności logicznej między wersetami
			enHelpTextIndexViewAllResources,//8.Przegląd wszystkich dostępnych zasobów
			enHelpTextIndexResizeWork,			//9.Poszerzanie obszaru tekstu
			enHelpTextIndexFacePage,				//10.Odnośnik do strony FaceBook
			enHelpTextIndexUpdate,					//11.Sprawdzanie aktualizacji i ewentualny aktualizacje
			enHelpTextIndexLogoApplication, //12.Ikona z główną grafiką aplikacji
			enHelpTextIndexEditChapter,			//13.Edycja rozdziału
			enHelpTextIndex_MailChapt,			//14.Wyśli emailem rozdział
			enHelpTextIndex_ImageAndText,		//15.Tworzenie grafiki z tekstem
			enHelpTextIndex_Help,						//16.Pomocnik
			enHelpTextIndex_Count					  //17.
};
/*
	Całkowicie publiczna i statyczna klasa globalnych zmiennych, dostępnych wszystkim modułom
*/

struct GlobalVar
{
	inline const static UnicodeString Global_custrGetExeDir = System::Sysutils::ExtractFilePath(Application->ExeName),					 //Ścieżka dostępu do katalogu głównego programu;
																		Global_custrNameIVerFile="MBibleNG.iver",				 //Nazwa pliku z wersją aplikacji. Plik słuzy do sparawdzamia aktualnej wersji
																		Global_custrGetVersionUpdate=TPath::Combine(GlobalVar::Global_custrGetExeDir, GlobalVar::Global_custrNameIVerFile),		 //Ścieżka dostepu do pilku tekstowego z wersją, do aktualizacji
																		Global_custrImagesPreviewStyles, //Ścieżka dostępu do katalogu z grafiką podglądów stylów
																		#if defined(_DEBUGINFO_)
																				//Jeśli projekt jest kompilowany z oknem konsoli, dane dla aplikacji są pobierane nie standartowo z zewnętrznego katalogu
																				Global_custrGetDataDir= "f:\\DevelopGS\\Dane dla MojaBiblia\\Data\\",					 //Ścieżka dostępu do katalogu z danymi aplikacji
																		#else
																				//Kompilowanie bez kosoli, dane są umieszczone w standartowym miejscu
																				Global_custrGetDataDir = TPath::Combine(GlobalVar::Global_custrGetExeDir, "Data"),
																		#endif
																		//Global_custrPathTranslatesNotUse=TPath::Combine(GlobalVar::Global_custrGetDataDir, "NotUseTranslates"), //Ścieżka do katalogu z nieużywanymi tłumaczeniami //[31-05-2024]
																		Global_custrPathStrongDict=TPath::Combine(GlobalVar::Global_custrGetDataDir, "StrongDict.strdi"), // Ścieżka dostępu do pliku ze słownikiem stronga
																		Global_custrPathImagesStyles=TPath::Combine(GlobalVar::Global_custrGetDataDir, "PreviewsStyles"),		 //Ścieżka do katalogu z podglądem stylów graficznych aplikacji
																		Global_custrPathAllReadingPlan=TPath::Combine(GlobalVar::Global_custrGetDataDir, "ReadingPlan"),	//Ścieżka dostępu do katalogu z planami czytania biblii
																		Global_custrPathSearchFavorities=TPath::Combine(GlobalVar::Global_custrGetDataDir, "SearchFavorities"), //Ścieżka dostę[u do katalogu z ulubionymi plikami wyników wyszukiwania
																		Global_custrFileSearchFavExtend=".fsv",	 //Rozszerzenie ulubionych plików wyszukiwania  = "*.fsv";
																		Global_custrFileSearchInfoExtand=".isf", //Rozszerznie do pliku informacyjnego, bedącym dodatkiem do właściwego pliku ulubionych wyszukiwań
																		Global_custrGetConfigFile=TPath::Combine(GlobalVar::Global_custrGetExeDir, "ConfigFileMyBibleNG.ini"),				//Ścieżka do pliku konfiguracyjnego
																		Global_custrPathLastUsedAddressFile=TPath::Combine(GlobalVar::Global_custrGetDataDir, "LastUsedAddress.lud"),//Ścieżka dostępu do pliku z ostatnio używanymi adresami
																		Global_custrPathGlobalHelp=TPath::Combine(GlobalVar::Global_custrGetExeDir, "HelpMojaBibliaNT.chm"),			//Ścieżka dostępu do pliku pomocy
																		Global_custrPathHistory=TPath::Combine(GlobalVar::Global_custrGetDataDir, "HistoryChaptersOpen.hco"),					//Ściezka dostępu do pliku historii
																		//Graficne loga z rozszerzeniem .gli
																		Global_custrPathBackgroundWindow=TPath::Combine(GlobalVar::Global_custrGetDataDir, "BackgroundWindowImg.gli"),//Grafika z podkładem okna głównego
																		Global_custrPathSearchLogo=TPath::Combine(GlobalVar::Global_custrGetDataDir, "SearchLogo.gli"),//Logo w oknie wyszukiwania
																		Global_custrPathSetupsLogo=TPath::Combine(GlobalVar::Global_custrGetDataDir, "SetupsLogo.gli"),//Logo w oknie ustawień
																		Global_custrPathBacgroundImageText=TPath::Combine(GlobalVar::Global_custrGetDataDir, "Tora.png"),
																		//---
																		Global_custrExtendCommentsFiles=".bfc", //Rozszerzenie plików z komentarzami
																		Global_custrPathFileWordVersesExistGrec=TPath::Combine(GlobalVar::Global_custrGetDataDir, "WordToExistGrec.wte"), // Ścieżka dostępu do pliku z danymi wystapień w wersetach, dla tekstu greckiegoposzczególnych słów // [08-06-2024]
																		Global_custrPathFileWordVersesExistHbr=TPath::Combine(GlobalVar::Global_custrGetDataDir, "WordToExistHbr.wte"), // Ścieżka dostępu do pliku z danymi wystapień w wersetach, dla tekstu hebrajskiego, poszczególnych słów // [31-07-2024]
																		Global_custrPathFileInterlinear=TPath::Combine(GlobalVar::Global_custrGetDataDir, "gnt.intrl"),			//Ścieżka dostępu do pliku ze słownikiem gracko-polskim, do wyświetlenia tłumaczenia interlinearnego
																		Global_custrPathMultimediaFilesData=TPath::Combine(GlobalVar::Global_custrGetExeDir, "MultiMediaFiles"),//Ścieżka dostępu do danych multimedialnych
																		Global_custrPathFileFavoriteVers=TPath::Combine(GlobalVar::Global_custrGetDataDir, "FavoritesVerses.fmb"),		//Ścieżka dostępu do pliku z listą ulubionych wersetów
																		Global_custrPathDirComments=TPath::Combine(GlobalVar::Global_custrGetDataDir, "CommentsFile"),			//Katalog do pojedyńczych plików z komentarzami do wersetów
																		Global_custrPathHistorySearch=TPath::Combine(GlobalVar::Global_custrGetDataDir, "HistorySearch.fhs"),		 //Ścieżka dostępu do pliku z zapisaną historia tekstów wyszukiwanych
																		Global_custrPathImageBackgroundMainText=TPath::Combine(Global_custrGetDataDir, "backgroundmaintext.png"),  //Ściezka dostepu do grafiki jako podkładu dla głównego tekstu
																		//----- Zabezpieczenie przed uruchomieniem drugiej kopi aplikacji
																		Global_ustrMutexName="MutexName_" + System::Sysutils::ExtractFileName(Application->ExeName),	//Mutekst główny aplikacji
																		//----- Syle
																		Global_DefaultStyleName="Windows", //Domyślny styl
																		//----- Nazwa domyślnego tłumaczenia używanego do modułu konkordancji greckiej i słownika grecko-polskiego (nie w module Stronga!)
                                    // Tłumaczenie będzie można wybrać [02-06-2024]
																		Global_DefaultNameTranslateToDictionary="ELZEVIR TEXTUS RECEPTUS (1624)",// "TRO+"
																		/*****************************************************************************
																		*       Stałe dla pliku informacyjnego dla zapisu ulubionego wyszukiwania    *
																		******************************************************************************/
																		GlobalInfoSearch_Header="INFOFILESEARCH", //Nagłówek
																			GlobalInfoSearch_Name="Name", //Wyrażenie do wyszukiwania
																			GlobalInfoSearch_Translate="Translate", //Tłumaczenie brane pod uwagę podczas wyszukiwania
																			GlobalInfoSearch_RangeName="RangeName", //Nazwa zakresu wyszukiwania
																			GlobalInfoSearch_Range="Range", //Dokładny zakres wyszukiwania
                                      GlobalInfoSearch_Count="Count", //Ilość wystąpień
																		/*****************************************************************************
																		 *							 Stałe dla pliku konfiguracyjnego typu ini									 *
																		 *****************************************************************************/
																		//----- Sekcje Main pliku ini
																		GlobalIni_MainSection_Main="MAIN",					 //Główna sekcja MAIN pliku ini
																				GlobalIni_PathMultiM1="MultimediaPath1", GlobalIni_PathMultiM2="MultimediaPath2", GlobalIni_PathMultiM3="MultimediaPath3", //Ścieżki dostępu do wybranych katalogów z multimediami
																				GlobalIni_AppWidth="ApplicWinWidth", GlobalIni_AppHeight="ApplicWinHeight", //Szerokość i wysokość głównego okna
																				GlobalIni_LoadBooksOnExit="LoadBooksOnExit", //Lista otwartych ksiąg i rozdziałów w momencie zamknięcia aplikacji
																		//----- Sekcje Flags pliku ini
																		GlobalIni_FlagsSection_Main="FLAGS",				 //Główna sekcja FLAGS pliku ini
																				GlobalIni_IsDisplaySplashStart="IsDisplaySplashStart", //Czy wyświetlać winiete startową podczas startu aplikacji
																				GlobalIni_IsRequestEnd="IsRequestEndApplication",			 //czy pytać o zamknięcie aplikacji
																				GlobalIni_IsOnlyOne="IsOnlyOne",						//Dozwolona tylko jedna kopia aplikacji
																				GlobalIni_IsAutoFindUpdate="IsAutoFindUpdate",			 //Czy sprawdzać aktualizacje podczas uruchamiania aplikacji
																				GlobalIni_IsLoadBooksOnInit="IsLoadBooksOnInit", //Czy po ponownym uruchomieniu aplikacji, będą wczytywane kksięgi, które zostały ostatnio zamknięte podczas opuszczania aplikacji?
																				GlobalIni_IsTipsWindowStart="IsTipsWindowStart", //Czy po uruchomieniu aplikacji uruchomić okno szybkich podpowiedzi
																				GlobalIni_IsDisplayStartInfoTray="IsDisplayStartInfoTray", //Czy wyświetlać informacje o aplikacji w trayu, podczas uruchomienia aplikacji
																				GlobalIni_IsDisplayBackgroundImage="IsDisplayBackgroundImage", //Czy podkładem pod główny tekst bibli bedzie jednolity kolor, czy grafika
																		GlobalIni_ColorsSection_Main="COLORS",			 //Główna sekcja COLORS pliku ini
																				GlobalIni_ColorFavoritesVers="ColorsFavoritesVers",				//Kolor zaznaczenie ulubionych wersetów
																				GlobalIni_ColorCommentVers="ColorCommentVers",				 //Kolor zaznaczenie wersetów, do których istnieje komentarz
																				GlobalIni_ColorBackgroundText="ColorBackgroundText",			//Kolor podkładu pod wyswietlany tekst,
																				GlobalIni_ColorAdressVersFullTranslates="ColorAdressVersFullTranslates", //Kolor adresu, wersetu dla pełnego tłumaczenia
																				GlobalIni_ColorAdressVersPartTranslates="ColorAdressVersPartTranslates", //Kolor adresu, wersetu dla tłumaczeń częściowych(oryginalnych, lub innych)
																				GlobalIni_ColorNameFullTranslates="ColorNameFullTranslates",	//Kolor nazwy pełnego tłumaczenia
																				GlobalIni_ColorNamePartTranslates="ColorNamePartTranslates",	//Kolor nazwy częściowego tłumaczenia
																				GlobalIni_ColorBackgroundMarkerComment="ColorBackgroundMarkerComment", //Kolor podkładu dla znacznika, istnienia komentarza dla wersetu
																				GlobalIni_ColorBorderFavoritiesVers="ColorBorderFavoritiesVers", //Kolor obwódki wokół ulubionego wersetu
																				//----- Sekcja ColorsSetups pliku ini
																		GlobalIni_ColorsSetupsSection_Main="COLORSSETUPS", //Główna sekcja ColorsSetups
																				GlobalIni_ColorsSetupsBackGroundAllListSearch="ColorsSetupsBackGroundAllListSearch", //Kolor podkłady dla wyświetlenia wszystkich znalezionych wersetów
																				GlobalIni_ColorsSetupBackGroundSelectBookSearch="ColorsSetupBackGroundSelectBookSearch",//Kolor podkładu dla wyświetlenia znalezionych wersetów w wybranej księdze
																				GlobalIni_ColorsSetupBackGroundSelectVers="ColorsSetupBackGroundSelectVers",			//Kolor podkładu dla wyświetlenie pojedyńczego wybranego wersetu
																		//----- Sekcja ParametersSetupsSearch
																		GlobalIni_ParametersSetupsSearch_Main="PARAMETERSSETUPSSEARCH", //Główna sekcja ParametersSetupsSearch
																				GlobalIni_IsMemorySetupsSearch="IsMemorySetupsSearch", //Czy zapamiętywać parametry wyszukiwania
																				GlobalIni_Translate="SetupSearchTranslate", //Tłumaczenie
																				GlobalIni_SetupRangeBooks="SetupSearchRangeBooks",//Zakres ksiąg
																				GlobalIni_StartUserRange="SetupSearchStartUserRangeBook", //Początek zakresu wyszukiwań
																				GlobalIni_StopUserRange="SetupSearchStopUserRangeBook",	 //Koniec zakresu wyszukiwań
																				GlobalIni_TextSearch="SetupsSearchText", //Tekst wyszukiwany
																				GlobalIni_IsSizeTextSearch="IsSizeTextSearch", //Podczas wyszukiwania jest brana wielkość liter
																				GlobalIni_IsRegSearch="IsRegSearch", //Podczas wyszukiwania są używane wyrażenia regularne
																				//----- Sekcja Others
																		GlobalIni_OthersSection="OTHERS",						//Główna sekcja OTHERS
																				GlobalIni_OtherSizeFontMain="OtherSizeFontMain",		//Wielkość głównej czcionki tekstu wersetu
																				GlobalIni_OtherSizeFontAdress="OtherSizeFontAdress",	//Wielkość czcionki, adresu wersetu
																				GlobalIni_OtherSizeFontNameTranslators="OtherSizeFontTranslators", //Wielkość czcionki nazwy tłumaczeń
																				GlobalIni_FontNameMain="FontnameMain",					 //Nazwa głównej czcionki
																				GlobalIni_FontNameAdress="FontNameAdress",				 //Nazwa czcionki adresu wersetu
																				GlobalIni_FontNameTranslators="FontNameTranslators",		//Nazwa czcionki nazwy tłymaczenia
																				GlobalIni_SelectStyleName="SelectStyleName",				//Nazwa wybranego z listy tematu dla aplikacji
																				GlobalIni_GrahicsBackground="GrahicsBackground",  //Ścieżka dostępu do podkładu graficznego dla głównego okna.
                                                                                          //Grafika będzie widoczna tylko gdy nie będzie wczytana żadna księga biblijna  //[11-12-2023]
																		//----- Sekcje Translates
																		GlobalIni_TranslatesSection_Main="TRANSLATES",								//Główna sekcja TRANSLATES pliku ini
																				GlobalIni_ExcludeTranslates="ExcludeTranslates",		//Tłumaczenia nie wyświetlane
																				GlobalIni_SelectTranslateForDictConcord="SelectTranslateForDictConcord",
																		GlobalIni_ReadingPlan_Main="READINGPLAN",			//Główna sekcja ustawień planu czytania biblii
																				GlobalIni_TranslateRPlan="TypeTranslateReadingPlan",//Tłumaczenie używane w planie
																				GlobalIni_IDTranslateRPlan="IDTranslateReadingPlan",//Numer identyfikacyjny tłumaczenie wykorzystywanego w planie czytania
																				GlobalIni_SelectPlan="SelectReadingPlan",						//Wybrany planu
																				GlobalIni_StartDate="StarDateReadingPlan",				 //Data rozpoczęcia planu czytania biblii
																				GlobalIni_IsStartPlan="IsStartReadingPlan",				 //Czy rozpoczęto plan czytania Pisma Świetego
																				GlobalIni_FontPlan="FontDisplayNameReadingPlan",	 //Czcionka wyświetlana w planie czytania biblii
																				GlobalIni_SizeFontPlan="FontSizeDisplayReadingPlan",//Wielkość czcionki w planie
																				GlobalIni_SetRate="SetRateSpeakText",								//Szybkość czytania tekstu
																				GlobalIni_SetVolume="SetVolumeSpeakText",						//Głośność czytania
																		GlobalIni_SetupsSchemeVers="SETUPSSCHEMEVERS",          //Główna sekcja modułu ustawień powiązań wersetów
																				GlobalIni_SetSchemeColorLine="SetupSchemeColorLine",
																				GlobalIni_SetSchemeColorRot="SetupSchemeColorRot",
																				GlobalIni_SetSchemeColorSelect="SetupSchemeColorSelect",
                                        GlobalIni_SetSchemeWidthLine="SetupSchemeWidthLine",

																				GlobalPath_CurrentActivePlan=TPath::Combine(GlobalVar::Global_custrPathAllReadingPlan, "AktualnyPlan.jcp"),		 //Ścieżka dostepu do pliku z dziennikiem czytania aktualnego planu
																		Global_ustrFileReadingPlanExtend=".rpf";	 //Zmienić na stałą!? Rozszerzenie plików planów czytania = "*.rpf";
 //----- Wersje plików i bibliotek
	inline static UnicodeString Global_ustrVerGsReadBibleTextClass, //Wersja biblioteki GsReadBibleTextClass
															Global_ustrVerAplicMain,							//Wersja głównej biblioteki
															//--- Ustawienia parametrów połączenia z siecią, w celu akyualizacji
															Global_custrLocalVersionFile, //Ścieżka dostępu lokalna, do pobranego pliku wersji
															Global_custrLocalApplicFile; //Ścieżka dostępu lokalna, do pobranej aplikacji
	const static unsigned char cuchABlendValue; //Współczynnik przezroczystości okna, gdy jest nieaktywne
	inline bool static IsWindows10=false, //Zmienna wskazuje czy klasa została uruchomiona na systemie Windows 10
										 IsRunReload=false; //Czy potrzeba przeładować aplikcje po zmianie konfiguracji
	static const unsigned char Global_NumberBooks = 73; //Maksymalna ilość ksiąg w Piśmie Świętym
	static const int Global_MaxlengthVers = 10240; //Maksymalna długość pojedyńczego wersetu
//***************************************************************************
	inline static TStringList *Global_SListPathMultiM=nullptr,	//Ścieżki dostępu do wybranych, przez użytkownika katalogów z multimediami
														*Global_ItemsColor=nullptr;       //Lista kolorów do wyboru, dla objektu klasy TColorBox
	inline static TMemIniFile *Global_ConfigFile=nullptr;			 //Globalny wskażnik na plik konfiguracyjny
	inline static TStringDynArray SDirTranslatesList;		//Lista ścieżek dostępu do, wszystkich dostępnych tłumaczeń
	inline static THashedStringList *Global_HSListAllFavoritiesVers=nullptr, //String lista do wszystkich ulubionych wesrsetów
																	*Global_HListHistoryChapterOpen=nullptr; //String lista histori otwieranych rozdziałow księg biblijnych
	inline static int iReturnUpdate=-1; //Wynik działania procedury sprawdzającej dostępność nowej wersji na serwerze.
														// iReturnUpdate == -1, wersja na komputarze jest nowsza niż na serwerze
														// iReturnUpdate == 0, obje wersje są jednakowe, nie potrzeba aktualizacji
														// iReturnUpdate == 1, wersja na komputerze jest starsza niż na serwerze, potrzeba zaktualizować
	inline static const unsigned char Global_cucMaxCountTranslates=22, // Maksymalna ilość tłumaczeń
																		Global_cucMaxTranslatesSpecjalist=16; // Maksymalna ilość tłumaczeń specjalistycznych //[19-05-2024]
	inline static const UnicodeString Global_ColorsAllTranslates[GlobalVar::Global_cucMaxTranslatesSpecjalist] = //[19-05-2024]
		{RGBToWebColorStr(clWebAzure),
		 RGBToWebColorStr(clWebLemonChiffon),
		 RGBToWebColorStr(clWebPaleGreen),
		 RGBToWebColorStr(clWebLightSkyBlue),
		 RGBToWebColorStr(clWebPlum),
		 RGBToWebColorStr(clWebDarkTurquoise),
		 RGBToWebColorStr(clWebDarkSalmon),
		 RGBToWebColorStr(clWebGold)}; //Tablica kolorów tłumaczeń
};
#endif
