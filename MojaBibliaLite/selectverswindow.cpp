#include "selectverswindow.h"
#include "ui_selectverswindow.h"
#include "globalvar.h"

/*
#if defined(_DEBUGINFO_)
 qDebug() << "";
#endif

#if defined(_DEBUGINFO_)
  qDebug("%d", 12);
#endif
*/

SelectVersWindow::SelectVersWindow(QWidget *parent) : QDialog(parent),
  ui(new Ui::SelectVersWindow)
/**
   OPIS METOD(FUNKCJI): Metoda tworząca okno
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  this->ui->setupUi(this);

  this->_pQGsWidgetSelectVers = new QGsWidgetSelectVers(this);
  this->ui->verticalLayout->insertWidget(0, this->_pQGsWidgetSelectVers);

  //QStringList qsList;
  //QGsReadBibleTextData::QGetSelectVerAllTranslate(0, 1, 2, qsList);
}
//---------------------------------------------------------------------------
SelectVersWindow::~SelectVersWindow()
/**
   OPIS METOD(FUNKCJI): Metoda destruktora
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  delete this->ui;
}
//---------------------------------------------------------------------------
