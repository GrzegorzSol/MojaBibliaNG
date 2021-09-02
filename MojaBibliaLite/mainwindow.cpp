#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "searchwindow.h"
#include "setupswindow.h"
#include "informationswindow.h"
#include "selectverswindow.h"
#include "QGsReadBibleTextClass/qgsreadbibletextclass.h"
#include "globalvar.h"
#include <QScreen>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
/*
#if defined(_DEBUGINFO_)
 qDebug() << "";
#endif

#if defined(_DEBUGINFO_)
  qDebug("%d", 12);
#endif
*/

QString qstrNamesToolTabs[]  = {"Księgi biblijne", "Multimedia"};
enum {enToolsTabsBooks, enToolsTabsMultimedia, enToolsTabCount};

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
/**
   OPIS METOD(FUNKCJI): Metoda tworząca główne okno
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
 */
{
 this->ui->setupUi(this);
 //Plik konfiguracyjny
 GlobalVar::Global_ConfigFile = new QSettings(GlobalVar::Global_GetConfigFile, QSettings::IniFormat);
 //Wyświetlanie winiety jeśli jest tak ustawione
 this->_StartShowInformations();
 //Przenoszenie objektów myszką
 this->setAcceptDrops(true);
 //Podkład graficzny
 this->_pQGsLabelClass = new QLabel(this);
 this->_pQGsLabelClass->lower();
 //---Nazwy zakładek w objkcie typu PageControl, narzędzi
 QIcon iconTabsToolsBooks, iconTabsToolsMultimedia;
 //Ikony dla zakładek narzędzi
 iconTabsToolsBooks.addFile(":/TreeBooks/gfx/PismoŚwięte.png", QSize(), QIcon::Normal, QIcon::Off);
 iconTabsToolsMultimedia.addFile(":/Other/gfx/ZakładkaMultimediów.png", QSize(), QIcon::Normal, QIcon::Off);
 for(int i=0; i<this->ui->PageControlTools->count(); i++)
 {
    this->ui->PageControlTools->setTabText(i, qstrNamesToolTabs[i]);
    //Ikony dla zakładek narzędzi
    switch(i)
    {
      case enToolsTabsBooks: this->ui->PageControlTools->setTabIcon(enToolsTabsBooks, iconTabsToolsBooks); break;
      case enToolsTabsMultimedia: this->ui->PageControlTools->setTabIcon(enToolsTabsMultimedia, iconTabsToolsMultimedia); break;
    }
 }
 //---
 this->setWindowTitle(QString("%1 v%2  (c) Grzegorz Sołtysik - data kompilacji: %3").arg(APP_NAME_STRING).arg(APP_VERSION_STRING).arg(__DATE__));
 //this->setWindowTitle(QString(APP_NAME_STRING) + " v" + APP_VERSION_STRING + " (c) Grzegorz Sołtysik");
 this->_InitAllSignalsToolTips(); //Inicjalizacja wszystkich sygnałów i podpowiedzi, oraz tagów
 //Objekt klasy QGsMainTabWidgetClass, jest tworzona nie w this->ui by nie trzeba było wczytywać do pliku ui_mainwindow.h
 //deklaracji i definicji klasy QGsMainTabWidgetClass (który jest w nagłówku QGsReadBibleTextClass/qgsreadbibletextclass.h)
 QGsMainTabWidgetClass *pQGsMainTabWidgetClass = new QGsMainTabWidgetClass(this->ui->splitter);
 this->ui->splitter->addWidget(pQGsMainTabWidgetClass);


 //Odczytywanie konfiguracji
 int iWidth, iHeight;
 GlobalVar::Global_ConfigFile->beginGroup(GlobalVar::GlobalIni_MainSection_Main);
  iWidth = GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_AppWidth, 1280).toInt();
  iHeight  = GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_AppHeight, 720).toInt();
 GlobalVar::Global_ConfigFile->endGroup();

 this->resize(iWidth, iHeight); //Zmiana wielkości okna głównego, odczytanej z pliku konfiguracyjnego

 QScreen *pScreen = this->screen(); //Wskaźnik na ekran

 const QRect qScreenRect = pScreen->availableGeometry(); //Wymiary ekranu
 this->move(qScreenRect.width() / 2 - (iWidth / 2), qScreenRect.height() / 2 - (iHeight / 2));

 QGsReadBibleTextData::QInitMyBible(pQGsMainTabWidgetClass);
 QGsReadBibleTextData::QCreateTreeBooks(this->ui->TabSheetBooks, this->ui->verticalLayout_3);

 //Chowanie głównego objektu klasy QGsMainTabWidgetClass
 QGsReadBibleTextData::pQGsPageControl->setVisible(QGsReadBibleTextData::pQGsPageControl->count() > 0);
  //Aktywna zakładka z listą ksiąg
 this->ui->PageControlTools->setCurrentIndex(0);
}
//---------------------------------------------------------------------------
MainWindow::~MainWindow()
/**
  OPIS METOD(FUNKCJI): Metoda tworząca główne okno
  OPIS ARGUMENTÓW:
  OPIS ZMIENNYCH:
  OPIS WYNIKU METODY(FUNKCJI):
*/
{
 //Zapisywanie ustawień do konfiguracji, przed zamknięciem aplikacji
 GlobalVar::Global_ConfigFile->beginGroup(GlobalVar::GlobalIni_MainSection_Main);
  GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_AppWidth, this->width());
  GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_AppHeight, this->height());
 GlobalVar::Global_ConfigFile->endGroup();
 delete GlobalVar::Global_ConfigFile; GlobalVar::Global_ConfigFile=nullptr;
 //Zamknięcie głównych zasobów aplikacji
 QGsReadBibleTextData::QCloseMyBible();
 delete ui;
}
//---------------------------------------------------------------------------
void MainWindow::_StartShowInformations()
/**
    OPIS METOD(FUNKCJI): Wyświetlenie informacji (winiety) podczas uruchamiania aplikacji
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{
  GlobalVar::Global_ConfigFile->beginGroup(GlobalVar::GlobalIni_Flags_Main);
    bool IsShowInfoStart = GlobalVar::Global_ConfigFile->value(GlobalVar::GloalIni_IsDisplaySplash, true).toBool();
  GlobalVar::Global_ConfigFile->endGroup();
  if(IsShowInfoStart)
  {
   InformationsWindow *pInformationsWindow = new InformationsWindow(this, false);
   if(pInformationsWindow)
   {
     pInformationsWindow->setModal(false);
     Qt::WindowFlags flags = pInformationsWindow->windowFlags();
     pInformationsWindow->setWindowFlags(flags | Qt::WindowStaysOnTopHint);

     pInformationsWindow->show();
   }
  }
}
//---------------------------------------------------------------------------
void MainWindow::_InitAllSignalsToolTips()
/**
    OPIS METOD(FUNKCJI): Inicjalizacja wszystkich sygnałów i podpowiedzi, oraz tagów
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{
 this->ui->ActSearch->setData(enAction_Search);
 this->ui->ActSetups->setData(enAction_Setup);
 this->ui->ActCloseActiveSheet->setData(enAction_CloseSheet);
 this->ui->ActSaveToFile->setData(enAction_SaveActiveSheet);
 this->ui->ActResizeText->setData(enAction_ResizeText);
 this->ui->ActInformations->setData(enAction_Informations);

 connect(this->ui->ActSearch, SIGNAL(triggered()), this, SLOT(_Act_SearchBibleText())); //Uruchamianie wyszukiwania
 connect(this->ui->ActSetups, SIGNAL(triggered()), this, SLOT(_Act_SetupsWindow())); //Uruchamianie ustawienia
 connect(this->ui->ActCloseActiveSheet, SIGNAL(triggered()), this, SLOT(_Act_CloseSheetActiv())); //Zamknięcie aktywnej zakładki
 connect(this->ui->ActSaveToFile, SIGNAL(triggered()), this, SLOT(_Act_SavetoFile())); //Zapisanie aktywnej zakładki
 connect(this->ui->ActResizeText, SIGNAL(triggered()), this, SLOT(_Act_ResizeToolsTabs())); //Zmiana wielkości obszaru tekstu
 connect(this->ui->ActInformations, SIGNAL(triggered()), this, SLOT(_Act_Informations())); //Informacja o aplikacji
 connect(this->ui->ActSelectVers, SIGNAL(triggered()), this, SLOT(_Act_SelectVers())); //Wybór wersetu
}
//---------------------------------------------------------------------------
void MainWindow::_Act_SearchBibleText()
/**
    OPIS METOD(FUNKCJI):
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QAction *pAction = qobject_cast<QAction *>(QObject::sender());
  if(!pAction) return;
  //---
 SearchWindow *pSearchWindow = new SearchWindow(this);
 if(pSearchWindow)
 {
  pSearchWindow->setModal(true);
  pSearchWindow->exec();
  delete pSearchWindow; pSearchWindow = nullptr;
 }
}
//---------------------------------------------------------------------------
void MainWindow::_Act_SetupsWindow()
/**
    OPIS METOD(FUNKCJI):
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QAction *pAction = qobject_cast<QAction *>(QObject::sender());
  if(!pAction) return;
  //---
  SetupsWindow *pSetupsWindow = new SetupsWindow(this);
  if(pSetupsWindow)
  {
    pSetupsWindow->setModal(true);
    pSetupsWindow->exec();
    if(pSetupsWindow->result() == QDialog::Accepted)
    //jaki kod zwrócił dialog konfiguracji alikacji
    {
      QGsReadBibleTextData::QSetupVariables(); //Zmiana kolorów
    }
    delete pSetupsWindow; pSetupsWindow = nullptr;
  }
}
//---------------------------------------------------------------------------
void MainWindow::_Act_CloseSheetActiv()
/**
    OPIS METOD(FUNKCJI): Zamknięcie aktywnej zakładki
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QAction *pAction = qobject_cast<QAction *>(QObject::sender());
  if(!pAction) return;
  //---
  QGsTabSheetBookClass *pQGsTabSheetBookClass = dynamic_cast<QGsTabSheetBookClass *>(QGsReadBibleTextData::pQGsPageControl->currentWidget());
  if(pQGsTabSheetBookClass)
  {
    QGsReadBibleTextData::pQGsPageControl->removeTab(QGsReadBibleTextData::pQGsPageControl->currentIndex());
    delete pQGsTabSheetBookClass; pQGsTabSheetBookClass = nullptr;
    //Dezaktywacja przycisku w wupadku braku zakładek z tekstem rozdziału biblijnego
    this->ui->ActCloseActiveSheet->setEnabled(QGsReadBibleTextData::pQGsPageControl->count() > 0);
    //Schowanie lub nie, zakładek narzędzi
    this->ui->ActResizeText->setChecked(QGsReadBibleTextData::pQGsPageControl->count() > 0);
    this->ui->ActResizeText->setEnabled(QGsReadBibleTextData::pQGsPageControl->count() > 0);
    emit this->ui->ActResizeText->triggered();
  }
  //Aktywacja akcji zapisu aktywna zaleźnie od tego czy jest jakiś rozdział wczytany
  this->ui->ActSaveToFile->setEnabled(QGsReadBibleTextData::pQGsPageControl->count() > 0);
  //Chowanie głównego objektu klasy QGsMainTabWidgetClass
  QGsReadBibleTextData::pQGsPageControl->setVisible(QGsReadBibleTextData::pQGsPageControl->count() > 0);
}
//---------------------------------------------------------------------------
void MainWindow::_Act_SavetoFile()
/**
    OPIS METOD(FUNKCJI): Zapisanie do pliku typu html, aktywnej zakładki z tekstem rozdziału wybranej księgi
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QAction *pAction = qobject_cast<QAction *>(QObject::sender());
  if(!pAction) return;
  //---
  QStringList  qlSelectSaveFile;
  QString qstrSaveText;
  QFileDialog saveFile(this);
  saveFile.setFileMode(QFileDialog::AnyFile); //Ta opcja sprawia, że użytkownik może zaznaczyć tylko jeden plik (nawet nieistniejący)
  saveFile.setNameFilter("Pliki dla przeglądarki (*.html *.htm)");
  saveFile.setAcceptMode(QFileDialog::AcceptSave);
  if(saveFile.exec())
  {
    qlSelectSaveFile = saveFile.selectedFiles();

    QGsTabSheetBookClass *pQGsTabSheetBookClass = dynamic_cast<QGsTabSheetBookClass *>(QGsReadBibleTextData::pQGsPageControl->currentWidget());
    if(pQGsTabSheetBookClass)
    {
      QTextEdit *pQTextEdit = pQGsTabSheetBookClass->QGetTextEdit();
      qstrSaveText = pQTextEdit->toHtml();
      QFile fileSave(qlSelectSaveFile.at(0));
      if(fileSave.open(QIODevice::WriteOnly | QIODevice::Text))
      //Właściwy zapis pliku
      {
        QTextStream saveStream(&fileSave);
        saveStream.setCodec("UTF-8");

        saveStream << qstrSaveText;
        fileSave.close();
      }
    }
  }
}
//---------------------------------------------------------------------------
void MainWindow::_Act_ResizeToolsTabs()
/**
    OPIS METOD(FUNKCJI): Schowanie lub nie, zakładek narzędzi
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QAction *pAction = qobject_cast<QAction *>(QObject::sender());
  if(!pAction) return;
  //---
  //if(!QGsReadBibleTextData::pQGsPageControl->isVisible()) return;
  //---
  QList<int> currentSizes = this->ui->splitter->sizes();
  if(pAction->isChecked()) currentSizes[0] = this->ui->PageControlTools->minimumWidth(); else currentSizes[0] = this->ui->PageControlTools->maximumWidth();

  this->ui->splitter->setSizes(currentSizes);
}
//---------------------------------------------------------------------------
void MainWindow::_Act_Informations()
/**
    OPIS METOD(FUNKCJI): Informacja o aplikacji
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QAction *pAction = qobject_cast<QAction *>(QObject::sender());
  if(!pAction) return;
  //---
  InformationsWindow *pInformationsWindow = new InformationsWindow(this);
  if(pInformationsWindow)
  {
    pInformationsWindow->setModal(true);
    pInformationsWindow->exec();

    delete pInformationsWindow; pInformationsWindow = nullptr;
  }
}
//---------------------------------------------------------------------------
void MainWindow::_Act_SelectVers()
/**
    OPIS METOD(FUNKCJI):
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QAction *pAction = qobject_cast<QAction *>(QObject::sender());
  if(!pAction) return;
  //---
  SelectVersWindow *pSelectVersWindow = new SelectVersWindow(this);
  if(pSelectVersWindow)
  {
    pSelectVersWindow->setModal(true);
    pSelectVersWindow->exec();

    delete pSelectVersWindow; pSelectVersWindow = nullptr;
  }
}
//---------------------------------------------------------------------------
void MainWindow::closeEvent(QCloseEvent *event)
/**
    OPIS METOD(FUNKCJI):
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //QMessageBox::setIcon(QMessageBox::Question);
  QMessageBox::StandardButton iRet = QMessageBox::question(this, "Pytanie aplikacji",
    "Jesteś pewny że chcesz opuścić aplikacje?\n", QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::No);

  if(iRet != QMessageBox::Yes)
    {event->ignore();}
  else
    {event->accept();}
}
//---------------------------------------------------------------------------
bool MainWindow::event(QEvent *e)
/**
    OPIS METOD(FUNKCJI):
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if(e->type()==QEvent::StatusTip)
  {
    QStatusTipEvent *ev = dynamic_cast<QStatusTipEvent *>(e);
    if(ev)
    {
      this->ui->MainStatusBar->showMessage(ev->tip());
      return true;
    }
  }
  else if(e->type()==QEvent::Resize)
  {
    if(!QFile::exists(GlobalVar::Global_GetPathBackgroundWindow))
    {
      return QMainWindow::event(e);
    }
    this->_pQGsLabelClass->setGeometry(0, 0, this->width(), this->height());
    QPixmap _qPixmapImage(GlobalVar::Global_GetPathBackgroundWindow);
    QPixmap qPixmapImage = _qPixmapImage.scaled(this->_pQGsLabelClass->width(), this->_pQGsLabelClass->height(), Qt::IgnoreAspectRatio);

    this->_pQGsLabelClass->setPixmap(qPixmapImage);
  }

  return QMainWindow::event(e);
}
//---------------------------------------------------------------------------
void MainWindow::dropEvent(QDropEvent* event)
/**
 OPIS METOD(FUNKCJI):
 OPIS ARGUMENTÓW:
 OPIS ZMIENNYCH:
 OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QGsReadBibleTextData::pQGsPageControl->dropEvent(event);
}
//---------------------------------------------------------------------------
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
/**
 OPIS METOD(FUNKCJI):
 OPIS ARGUMENTÓW:
 OPIS ZMIENNYCH:
 OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QGsReadBibleTextData::pQGsPageControl->dragEnterEvent(event);
}
//---------------------------------------------------------------------------

