#include "informationswindow.h"
#include "ui_informationswindow.h"
#include <QMouseEvent>

/*
#if defined(_DEBUGINFO_)
 qDebug() << "";
#endif

#if defined(_DEBUGINFO_)
  qDebug("%d", 12);
#endif
*/

InformationsWindow::InformationsWindow(QWidget *parent, bool _bNormal) :
  QDialog(parent), ui(new Ui::InformationsWindow), bNormalStart(_bNormal)
/**
   OPIS METOD(FUNKCJI): Metoda tworząca okno
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  this->ui->setupUi(this);
  //
  this->ui->LabelLogoApplic->setFocus();
  this->_pMyTimer = new QTimer(this);

  connect(this->_pMyTimer, SIGNAL(timeout()), this, SLOT(_MyTimerSlot()));
  connect(this->ui->TEditInformationsApplic, SIGNAL(selectionChanged()), this, SLOT(close()));

  this->setWindowOpacity(0.0);
  this->_pMyTimer->start(18);

  this->ui->TEditInformationsApplic->setText(QString("\n%1 v%2  (c) Grzegorz Sołtysik - data kompilacji: %3\n %4").
    arg(APP_NAME_STRING).arg(APP_VERSION_STRING).arg(__DATE__).
    arg(QString("Aplikacja do studiowania Pisma Świętego.") +
      "W jej skład wchodzą polskie przekłady biblii, w wersji protestanckiej jak i katolickiej (zawierającej apokryfy)." +
      "Aplikacja również posiada dostęp do tekstów oryginalnych, w języku greckim (Nowy Testament, Septuaginta), jak i hebrajskim (Stary Testament).\n" +
      "OSTRZEŻENIE: Aktualna wersja jest wersją rozwojową (tzw. beta), dlatego może działać niestabilnie!\n\n" +
      "\tOpis licencji dla aplikacji Moja Biblia Lite:\n" +
      "Produkt ten posiada licencje FreeWare, więc jest przeznaczony do darmowego rozpowszechniania, ale bez czerpania jakichkolwiek korzyści finansowych.\n" +
      "Kod źródłowy projektu jest upubliczniony na stronie: „https://github.com/GrzegorzSol/MojaBibliaNG_Git”, można go dowolnie modyfikować," +
      "jednak o wszystkich takich zabiegach autor pragnie być poinformowany, razem z przedstawieniem zmodyfikowanego kodu.\n" +
      "Aplikacja jest rozwijana pod patronatem zboru Kościoła Zielonoświątkowego w Oświęcimiu, a jej wyłącznym autorem jest Grzegorz Sołtysik.\n\n" +
      "Jej rozwój rozpoczął się od 2007 roku (kolejne wersje były przeprojektowywane, zmieniane itd.). Więcej informacji znajduje się pod adresem \"https://www.facebook.com/MojaBiblia/\"\n\n"));

}
//---------------------------------------------------------------------------
InformationsWindow::~InformationsWindow()
/**
   OPIS METOD(FUNKCJI): Metoda niszcząca okno
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if(this->_pMyTimer) {delete this->_pMyTimer; this->_pMyTimer = nullptr;}
  delete this->ui;
}
//---------------------------------------------------------------------------
void InformationsWindow::mousePressEvent(QMouseEvent *mevent)
/**
   OPIS METOD(FUNKCJI):
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if(mevent->button() == Qt::LeftButton) this->close();
}
//---------------------------------------------------------------------------
void InformationsWindow::_MyTimerSlot()
/**
   OPIS METOD(FUNKCJI): Slot dla timera
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  static double sdTimer;

  sdTimer += 0.01;

  this->setWindowOpacity(sdTimer);
  if(sdTimer >= 1.0)
  {
    this->_pMyTimer->stop();
    sdTimer = 0.0;
  }
}
//---------------------------------------------------------------------------
