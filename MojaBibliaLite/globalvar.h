#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include <QDebug>
#include <QDir>
#include <QSettings>
#define _DEBUGINFO_  //Używanie okna konsoli do debugowania aplikacji
#if defined(_DEBUGINFO_)
  #include <QDebug>
#endif

enum {enAction_Search = 100, enAction_Setup, enAction_CloseSheet, enAction_SaveActiveSheet, enAction_ResizeText};

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
  const static QString GlobalIni_MainSection_Main,              //Główna sekcja MAIN pliku ini
                       GlobalIni_AppWidth, GlobalIni_AppHeight; //Szerokość i wysokość głównego okna
  //----- Sekcje Flags pliku ini

  static QSettings *Global_ConfigFile;			 //Globalny wskażnik na plik konfiguracyjny
};

#endif // GLOBALVAR_H
