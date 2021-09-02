#include "globalvar.h"
#include <QApplication>
#include <QMessageBox>

QString GlobalVar::Global_GetDirData, //Ścieżka dostępu do katalogu z danymi
        GlobalVar::Global_GetConfigFile,	//Ścieżka do pliku konfiguracyjnego
        GlobalVar::Global_GetPathBackgroundWindow, //Grafika z podkładem okna głównego
        GlobalVar::Global_GetPathHistorySearch,//Ścieżka dostępu do histori wyszukiwań
        GlobalVar::Global_SheetStr; //Zmienna która zawiera aktualny styl

const QString
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
//----- Sekcja Flags pliku ini
GlobalVar::GlobalIni_Flags_Main="FLAGS",   //Sekcja FLAGS pliku ini
    GlobalVar::GloalIni_IsDisplaySplash="IsDisplaySplash",//Czy wyświetlać winiete podczas startu aplikacji
//----- Sekcje Colors pliku ini
GlobalVar::GlobalIni_ColorsSection_Main="COLORSMAIN",         //Główna sekcja COLORS pliku ini
    GlobalVar::GlobalIni_ColorBackGroundMainText="ColorBackGroundMainText",  //Kolor podkładu pod wyswietlany tekst
    GlobalVar::GlobalIni_ColorFontNameFullTranslate="ColorFontNameFullTranslate",   //Kolor nazwy dla pełnego tłumaczenia
    GlobalVar::GlobalIni_ColorAdressFulltranslate="ColorAdressFulltranslate", //Kolor adresu, wersetu dla tłumaczeń całych
    GlobalVar::GlobalIni_ColorTextOryginalTr="ColorTextOryginalTr",  //Kolor czcionki oryginalnych, częściowych tłumaczeń
    GlobalVar::GlobalIni_ColorNameOryginalTr="ColorNameOryginalTr",  //Kolor czcionki nazwy oryginalnych częściowych tłumaczeń
    GlobalVar::GlobalIni_ColorAdressOryginalTr="ColorAdressOryginalTr",//Kolor adresu częściowych oryginalnych tłumaczeń
//----- Sekcja ColorsSetups pliku ini
GlobalVar::GlobalIni_ColorsSetupsSection_Main="COLORSSETUPS", //Główna sekcja ColorsSetups
    GlobalVar::GlobalIni_ColorsSetupsBackGroundAllListSearch="ColorsSetupsBackGroundAllListSearch", //Kolor podkłady dla wyświetlenia wszystkich znalezionych wersetów
    GlobalVar::GlobalIni_ColorsSetupBackGroundStatistictBookSearch="ColorsSetupBackGroundStatistictBookSearch",//Kolor podkładu dla wyświetlenia znalezionych wersetów w wybranej księdze
    GlobalVar::GlobalIni_ColorsSetupBackGroundSelectVers="ColorsSetupBackGroundSelectVers",
//----- Sekcje Main pliku ini
GlobalVar::GlobalIni_MainSection_Main="MAIN",           //Główna sekcja MAIN pliku ini
    GlobalVar::GlobalIni_PathMultiM1="MultimediaPath1", GlobalVar::GlobalIni_PathMultiM2="MultimediaPath2",
    GlobalVar::GlobalIni_PathMultiM3="MultimediaPath3", GlobalVar::GlobalIni_PathMultiM4="MultimediaPath4",//Ścieżki dostępu do wybranych katalogów z multimediami
    GlobalVar::GlobalIni_AppWidth="ApplicWinWidth", GlobalVar::GlobalIni_AppHeight="ApplicWinHeight", //Szerokość i wysokość głównego okna
//----- Sekcja ustawiania czcionek
GlobalVar::GlobalIni_FontsSetupSection_Main="FONTS", //Główna sekcja od czcionek
  GlobalVar::GlobalIni_FontMainText="FontMainText", //Czcionka głównego tekstu biblijnego
  GlobalVar::GlobalIni_FontMainTextSize="FontMainTextSize",//Wielkość czcionki głównego tekstu bilijnego
  GlobalVar::GlobalIni_FontAdressVersText="FontAdressVersText",//Czcionka adresu wersetu w głównym oknie
  GlobalVar::GlobalIni_FontAdressVersTextSize="FontAdressVersTextSize",//Wielkość czcionki adresu wersetu w głównym oknie
  GlobalVar::GlobalIni_FontNameTranslateText="FontNameTranslateText",//Czcionka nazwy tłumaczenia w głównym oknie
  GlobalVar::GlobalIni_FontNameTranslateTextSize="FontNameTranslateTextSize";//Wielkość czcionki nazwy tłumaczenia w głównym oknie

QSettings *GlobalVar::Global_ConfigFile=nullptr; //Globalny wskażnik na plik konfiguracyjny

void GlobalVar::GFunInitGlobal()
/**
  OPIS METOD(FUNKCJI): Metoda tworząca główne okno
  OPIS ARGUMENTÓW:
  OPIS ZMIENNYCH:
  OPIS WYNIKU METODY(FUNKCJI):
*/
{
  const QString //qcstrDirNameStyles = "Styles",
                qcstrDirNameData = "Data",
                qcstrNameConfig = "ConfigFileMyBibleNG.ini",
                qcstrNameHistory = "HistorySearch.fhs",
                qcstrNameBackgroundImage = "BackgroundWindowImg.gli";

  QDir dirTempMainDir(QApplication::applicationDirPath()), //Główny katalog aplikacji
       dirTempDataPath(dirTempMainDir.filePath(qcstrDirNameData)); //Ścieżka dostępu do katalogu z danymi

  //Główny katalog z danymi aplikacji
  GlobalVar::Global_GetDirData = dirTempDataPath.toNativeSeparators(dirTempDataPath.absolutePath());
  if(!dirTempDataPath.exists())
  {
    QMessageBox::critical(0, "Błąd krytyczny aplikacji",
      QString("Nieprawidłowo zainstalowana aplikacja.\nKatalog: \"%1\" nie istnieje!!!\nZ tego powodu aplikacja nie może pobrać niezbędnych danych do prawidłowej pracy.")
             .arg(GlobalVar::Global_GetDirData));
    exit(EXIT_FAILURE);
  }
  //Ścieżka dostępu do podkład okna głównego
  GlobalVar::Global_GetPathBackgroundWindow = QDir::toNativeSeparators(dirTempDataPath.filePath(qcstrNameBackgroundImage));
  //Ścieżka dostępu do histori wyszukiwań
  GlobalVar::Global_GetPathHistorySearch = QDir::toNativeSeparators(dirTempDataPath.filePath(qcstrNameHistory));

  //Ścieżka dostępu do pliku konfiguracyjnego
  GlobalVar::Global_GetConfigFile = QDir::toNativeSeparators(dirTempMainDir.filePath(qcstrNameConfig));

  //Style
  GlobalVar::Global_SheetStr =
     QString("") +
    "QProgressBar" +
    "{selection-background-color: #FF0000;}";
}
