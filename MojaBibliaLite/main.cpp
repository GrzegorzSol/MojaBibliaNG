#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QStyleFactory>
#include "globalvar.h"
//#include "informationswindow.h"

int main(int argc, char *argv[])
/**
  OPIS METOD(FUNKCJI): Metoda tworząca główne okno
  OPIS ARGUMENTÓW:
  OPIS ZMIENNYCH:
  OPIS WYNIKU METODY(FUNKCJI):
*/
{
 QApplication a(argc, argv);

 QStyle *pQStyle = QStyleFactory::create("Fusion");

 if(pQStyle) a.setStyle(pQStyle);

 a.setApplicationVersion(APP_VERSION_STRING);
 a.setApplicationName(APP_NAME_STRING);
 a.setOrganizationName("MojaBibliaLite");
 a.setOrganizationDomain("MojaBibliaLite.com");

 //Inicjalizacje wszystkich danych
 //W metodzie sprawdzane jest czy istnieje katalog z danymi, jeśli nie aplikacja zostaje przerwana z kodem błędu
 GlobalVar::GFunInitGlobal();

 a.setStyleSheet(GlobalVar::Global_SheetStr);

 MainWindow w;
 w.show();
 return a.exec();
}
