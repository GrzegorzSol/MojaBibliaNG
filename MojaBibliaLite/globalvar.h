#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include <QDir>
#include <QSettings>
//#define _DEBUGINFO_  //Używanie okna konsoli do debugowania aplikacji
#if defined(_DEBUGINFO_)
  #include <QDebug>
#endif

enum {enAction_Search = 100, enAction_Setup, enAction_CloseSheet, enAction_SaveActiveSheet, enAction_ResizeText, enAction_Informations};

struct GlobalVar
{
 public:
  static void GFunInitGlobal(); //Inicjalizacja
  //---
  static QString Global_GetDirData, //Ścieżka dostępu do katalogu z danymi
                 Global_GetConfigFile,	//Ścieżka do pliku konfiguracyjnego
                 Global_GetPathBackgroundWindow,//Grafika z podkładem okna głównego
                 Global_GetPathHistorySearch,//Ścieżka dostępu do histori wyszukiwań
                 //Global_GetPathStyle,  //Ścieżka dostępu do katalogu ze stylami
                 Global_SheetStr; //Zmienna która zawiera aktualny styl
  //----- Sekcje Main pliku ini
  const static QString
  //----- Główna sekcja MAIN pliku ini
    GlobalIni_MainSection_Main,
    GlobalIni_PathMultiM1, GlobalIni_PathMultiM2, GlobalIni_PathMultiM3, GlobalIni_PathMultiM4, //Ścieżki dostępu do wybranych katalogów z multimediami
    GlobalIni_AppWidth, GlobalIni_AppHeight, //Szerokość i wysokość głównego okna
  //----- Sekcja ParametersSetupsSearch
  GlobalIni_ParametersSetupsSearch_Main, //Główna sekcja ParametersSetupsSearch
    GlobalIni_IsMemorySetupsSearch, //Czy zapamiętywać parametry wyszukiwania
    GlobalIni_Translate, //Tłumaczenie
    GlobalIni_SetupRangeBooks,//Zakres ksiąg
    GlobalIni_StartUserRange, //Początek zakresu wyszukiwań
    GlobalIni_StopUserRange,  //Koniec zakresu wyszukiwań
    GlobalIni_TextSearch, //Tekst wyszukiwany
    GlobalIni_IsSizeTextSearch, //Podczas wyszukiwania jest brana wielkość liter
    GlobalIni_IsRegSearch, //Podczas wyszukiwania są używane wyrażenia regularne
  //----- Sekcja Flags pliku ini
  GlobalIni_Flags_Main,   //Sekcja FLAGS pliku ini
    GloalIni_IsDisplaySplash,//Czy wyświetlać winiete podczas startu aplikacji
  //----- Sekcje Colors pliku ini
  GlobalIni_ColorsSection_Main,         //Główna sekcja COLORS pliku ini
    GlobalIni_ColorBackGroundMainText,  //Kolor podkładu pod wyswietlany tekst
    GlobalIni_ColorFontNameFullTranslate,   //Kolor nazwy dla pełnego tłumaczenia
    GlobalIni_ColorAdressFulltranslate, //Kolor adresu, wersetu dla tłumaczeń całych
    GlobalIni_ColorTextOryginalTr,  //Kolor czcionki oryginalnych, częściowych tłumaczeń
    GlobalIni_ColorNameOryginalTr,  //Kolor czcionki nazwy oryginalnych częściowych tłumaczeń
    GlobalIni_ColorAdressOryginalTr,//Kolor adresu częściowych oryginalnych tłumaczeń
  //----- Sekcja ColorsSetups pliku ini
  GlobalIni_ColorsSetupsSection_Main, //Główna sekcja ColorsSetups
    GlobalIni_ColorsSetupsBackGroundAllListSearch, //Kolor podkłady dla wyświetlenia wszystkich znalezionych wersetów
    GlobalIni_ColorsSetupBackGroundStatistictBookSearch,//Kolor podkładu dla wyświetlenia znalezionych wersetów w wybranej księdze
    GlobalIni_ColorsSetupBackGroundSelectVers,      //Kolor podkładu dla wyświetlenie pojedyńczego wybranego wersetu

  //----- Sekcja ustawiania czcionek
  GlobalIni_FontsSetupSection_Main, //Główna sekcja od czcionek
    GlobalIni_FontMainText, //Czcionka głównego tekstu biblijnego
    GlobalIni_FontMainTextSize,//Wielkość czcionki głównego tekstu bilijnego
    GlobalIni_FontAdressVersText,//Czcionka adresu wersetu w głównym oknie
    GlobalIni_FontAdressVersTextSize,//Wielkość czcionki adresu wersetu w głównym oknie
    GlobalIni_FontNameTranslateText,//Czcionka nazwy tłumaczenia w głównym oknie
    GlobalIni_FontNameTranslateTextSize;//Wielkość czcionki nazwy tłumaczenia w głównym oknie

  static QSettings *Global_ConfigFile;			 //Globalny wskażnik na plik konfiguracyjny
};

#endif // GLOBALVAR_H
