#include "globalvar.h"
#include <QApplication>
#include <QMessageBox>

QString GlobalVar::Global_GetDirData, //Ścieżka dostępu do katalogu z danymi
        GlobalVar::Global_GetConfigFile,	//Ścieżka do pliku konfiguracyjnego
        GlobalVar::Global_GetPathBackgroundWindow, //Grafika z podkładem okna głównego
        GlobalVar::Global_GetPathHistorySearch,//Ścieżka dostępu do histori wyszukiwań
        GlobalVar::Global_SheetStr; //Zmienna która zawiera aktualny styl
//----- Sekcje Main pliku ini
const QString GlobalVar::GlobalIni_MainSection_Main="MAIN",           //Główna sekcja MAIN pliku ini
              GlobalVar::GlobalIni_AppWidth="ApplicWinWidth", GlobalVar::GlobalIni_AppHeight="ApplicWinHeight"; //Szerokość i wysokość głównego okna
//----- Sekcje Flags pliku ini

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
                qcstrNameBackgroundImage = "BackgroundWindowImg.bmp";

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

  #if defined(_DEBUGINFO_)
    qDebug() << "GlobalVar::Global_GetPathBackgroundWindow: " << GlobalVar::Global_GetPathBackgroundWindow;
    qDebug() << "GlobalVar::Global_GetPathHistorySearch: " << GlobalVar::Global_GetPathHistorySearch;
  #endif

  //Style
  GlobalVar::Global_SheetStr =
     QString("") +
    "QProgressBar" +
    "{selection-background-color: #FF0000;}";
}
