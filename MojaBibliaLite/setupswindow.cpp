#include "setupswindow.h"
#include "ui_setupswindow.h"

SetupsWindow::SetupsWindow(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SetupsWindow)
/**
   OPIS METOD(FUNKCJI): Metoda tworząca okno
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
 */
{
  this->ui->setupUi(this);
}
//---------------------------------------------------------------------------
SetupsWindow::~SetupsWindow()
/**
   OPIS METOD(FUNKCJI): Metoda destruktora
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  delete ui;
}
//---------------------------------------------------------------------------
