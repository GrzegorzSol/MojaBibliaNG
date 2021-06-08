#include "searchwindow.h"
#include "ui_searchwindow.h"
#include "globalvar.h"
#include "QGsReadBibleTextClass/qgsreadbibletextclass.h"
#include <QMessageBox>
#include <QColorDialog>
#include "mblitelibrary.h"

/*
#if defined(_DEBUGINFO_)
 qDebug() << "";
#endif
*/
//enum {enAllButtonSearch_Search, enAllButtonSearch_Help, enAllButtonSearch_Cancel};

//--- Właściwości użytkownika dla objektów
const char PropLWidgetTag[] = "usp_PropLWidget",
           PropCBoxTag[] = "usp_PropCBoxTag",
           PropButtonSelectColorTag[] = "usp_PropButtonSelectColorTag";

enum {//Dane dla pozycji QListWidgetItem, objektu this->ui->LViewStatistic, klasy QListWidget
  CI_ITEMS_STATISTIC_LIST_BOOK_RESULTS_DATA = Qt::UserRole, //Ilość znalezionych pozycji w danej księdze
  CI_ITEMS_STATISTIC_COUNTS_ALL_RESULTS_DATA, //Wszystkich znalezionych pozycji
  //Dane dla pozycji QListWidgetItem, objektu this->ui->LViewResultSearch, klasy QListWidget
  CI_ITEMS_RESULT_SEARCH_TEXT_DATA = Qt::UserRole+10, //Cały tekst wersetu z adresem
  //Zakładki dla objektu klasy QTabWidget
  enTabSheet_SetupSearch = 0,
  enTabSheet_Statistic,
  enTabSheet_Configs,
  //Tagi dla QComboBox
  enCBox_SelectRange=100, enCBox_SelectStartBook, enCBox_SelectStopBook,
  //Własności dla objektów klasy QListWidget
  enListWidgetResultSearch=200, enListWidgetStatistic,
  //Tagi dla QPushButton zmainy kolorów
  enColor_AllSearch=300, enColor_SelectVers, enColor_Statistic
};

SearchWindow::SearchWindow(QWidget *parent) : QDialog(parent), ui(new Ui::SearchWindow)
/**
   OPIS METOD(FUNKCJI): Metoda tworząca okno
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
 this->ui->setupUi(this);

 this->ui->PageTabInputSearchText->setCurrentIndex(0);
 this->ui->PageTabSelectVievResult->setCurrentIndex(0);
 //---
 QIcon iconItems;
 iconItems.addFile(":/TreeBooks/gfx/Księga.png", QSize(), QIcon::Normal, QIcon::Off);

 MyDelegate *pMyDelegate = new MyDelegate(this->ui->LViewStatistic);
 this->ui->LViewStatistic->setItemDelegate(pMyDelegate);

 //Wstępne ustawienia zawartości komponentów
   //Definiowanie komponentów wyboru ksiąg biblijnych
 for(int i=0; i<QGsReadBibleTextData::QGsNumberBooks; i++)
 {
   this->ui->CBoxStartSelectBook->addItem(iconItems, QGsReadBibleTextData::QGsInfoAllBooks[i].FullNameBook);
   this->ui->CBoxStopSelectBook->addItem(iconItems, QGsReadBibleTextData::QGsInfoAllBooks[i].FullNameBook);
 }
 //Domyślnie wszystkie księgi do przeszukania
 this->ui->CBoxStartSelectBook->setCurrentIndex(0);
 this->ui->CBoxStopSelectBook->setCurrentIndex(QGsReadBibleTextData::QGsNumberBooks-1);
 //Definiowanie komponentu zakresu wyszukiwania
 QIcon iconRange(":/Search/gfx/WybórZakresu.png");
 for(int i=0; i<en_GrSearch_Count; i++)
 {
   this->ui->CBoxSelectRangeBooksSearch->addItem(iconRange, QGsReadBibleTextData::QGsNameAllRanges[i]);
 }
 this->ui->CBoxSelectRangeBooksSearch->setCurrentIndex(0);
 //Definiowanie listy tłumaczeń do wybrania
 QString qstrNameTranslate;
 QIcon iconTranslates(":/Search/gfx/Tłumaczenia.png");
 if(QGsReadBibleTextData::QCountTranslates() > 0)
 {
   for(unsigned char i=0; i<QGsReadBibleTextData::QCountTranslates(); i++)
   {
      QGsReadBibleTextData::QGetInfoNameTranslate(i, qstrNameTranslate);
      this->ui->CBoxSelectTranslates->addItem(iconTranslates, qstrNameTranslate);
   }
 } else this->ui->CBoxSelectTranslates->setEnabled(false);
 //Inicjowanie tagów i podpinanie sygnałów
 this->_InitSignalsAndTags();
 this->ui->CBoxHistorySearch->setFocus();
 //Odczyt histori wyszukiwań i załadowanie jej do objektu, klasy QComboBox
 QStringList _qsltemp;
 LoadFileToStrList(_qsltemp, GlobalVar::Global_GetPathHistorySearch);
 //Inicjowanie tagów i podpinanie sygnałów
 //this->_InitSignalsAndTags();
 for(int i=0; i<_qsltemp.count(); i++)
  {this->ui->CBoxHistorySearch->addItem(_qsltemp.at(i));}
 //Stworzenie listy statystyki, której ilość elementów się nie zmienia i jest równa wszystkim dostępnym księgom
 QIcon iconStatistic;
 iconStatistic.addFile(":/Search/gfx/StatystykaWyszukiwania.png", QSize(), QIcon::Normal, QIcon::Off);
 for(int i=0; i<QGsReadBibleTextData::QGsNumberBooks; i++)
 {
    QListWidgetItem *newItem = new QListWidgetItem();//(QIcon(":/Search/gfx/KsięgaStat.png"), QGsReadBibleTextData::QGsInfoAllBooks[i].FullNameBook);
    newItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);//(Qt::AlignHCenter | Qt::AlignTop);
    newItem->setData(Qt::DisplayRole, QGsReadBibleTextData::QGsInfoAllBooks[i].FullNameBook);
    newItem->setData(Qt::DecorationRole, iconStatistic);
    this->ui->LViewStatistic->addItem(newItem);
 }
 //Domyślnie zakładka statystyki jest niwidoczna
 this->ui->PageTabInputSearchText->setTabVisible(enTabSheet_Statistic, false);
 //Odczyt pliku konfiguracyjnego
 this->_ReadAllConfig();
}
//---------------------------------------------------------------------------
SearchWindow::~SearchWindow()
/**
   OPIS METOD(FUNKCJI): Metoda destruktora
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //Zapis zmodifikowanej histori wyszukiwania
  QStringList _qslisttemp;
  for(int i=0; i<this->ui->CBoxHistorySearch->count(); i++)
    {_qslisttemp << this->ui->CBoxHistorySearch->itemText(i);}
  SaveStrListToFile(_qslisttemp, GlobalVar::Global_GetPathHistorySearch);

  //Zapisy do pliku konfiguracyjnego
   //Wygląd
  this->_WriteAllConfig();

  delete this->ui;
}
//---------------------------------------------------------------------------
void SearchWindow::_ReadAllConfig()
/**
   OPIS METOD(FUNKCJI): Odczyt konfiguracji
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QRgb iRGBTemp;

  GlobalVar::Global_ConfigFile->beginGroup(GlobalVar::GlobalIni_ColorsSetupsSection_Main);
   //Kolory dla QPushButton ustawiania kolorów podkładu
   iRGBTemp = (QRgb)GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_ColorsSetupsBackGroundAllListSearch, 11899830).toInt();
   SetupColorPButton(this->ui->ButtonColorAllSearch, iRGBTemp);
   //---
   iRGBTemp = (QRgb)GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_ColorsSetupBackGroundSelectVers, 11829830).toInt();
   SetupColorPButton(this->ui->ButtonColorSelectSearch, iRGBTemp);
   //---
   iRGBTemp = (QRgb)GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_ColorsSetupBackGroundStatistictBookSearch, 11829830).toInt();
   SetupColorPButton(this->ui->ButtonColorStatictic, iRGBTemp);
   //---
  GlobalVar::Global_ConfigFile->endGroup();
     //Flagi
  GlobalVar::Global_ConfigFile->beginGroup(GlobalVar::GlobalIni_ParametersSetupsSearch_Main);
    bool bIsmemoConfig = GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_IsMemorySetupsSearch, true).toBool();
    this->ui->ChBoxMemorySetups->setChecked(bIsmemoConfig);
    if(bIsmemoConfig)
    //Odczyt ustawień tylko w przypadku aktywaci zapamiętywania ustawień wyszukiwania
    {
     //Flagi
     this->ui->ChBoxIsRegEx->setChecked(GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_IsRegSearch, false).toBool());
     this->ui->ChBoxSearchSizeText->setChecked(GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_IsSizeTextSearch, false).toBool());
     //Parametry tekstu
     this->ui->CBoxSelectTranslates->setCurrentIndex(GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_Translate, 0).toInt());
     this->ui->CBoxSelectRangeBooksSearch->setCurrentIndex(GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_SetupRangeBooks, 0).toInt());
     this->ui->CBoxStartSelectBook->setCurrentIndex(GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_StartUserRange, 0).toInt());
     this->ui->CBoxStopSelectBook->setCurrentIndex(GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_StopUserRange, QGsReadBibleTextData::QGsNumberBooks-1).toInt());
    }
   GlobalVar::Global_ConfigFile->endGroup();
}
//---------------------------------------------------------------------------
void SearchWindow::_WriteAllConfig()
/**
   OPIS METOD(FUNKCJI): Zapis konfiguracji
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QRgb iRGBTemp;

  GlobalVar::Global_ConfigFile->beginGroup(GlobalVar::GlobalIni_ColorsSetupsSection_Main);
    //Kolory dla QPushButton ustawiania kolorów podkładu
    iRGBTemp = ReadColorPButton(this->ui->ButtonColorAllSearch);
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_ColorsSetupsBackGroundAllListSearch, iRGBTemp);
    //---
    iRGBTemp = ReadColorPButton(this->ui->ButtonColorSelectSearch);
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_ColorsSetupBackGroundSelectVers, iRGBTemp);
    //---
    iRGBTemp = ReadColorPButton(this->ui->ButtonColorStatictic);
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_ColorsSetupBackGroundStatistictBookSearch, iRGBTemp);
  GlobalVar::Global_ConfigFile->endGroup();
    //Flagi
  GlobalVar::Global_ConfigFile->beginGroup(GlobalVar::GlobalIni_ParametersSetupsSearch_Main);
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_IsRegSearch, this->ui->ChBoxIsRegEx->isChecked());
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_IsSizeTextSearch, this->ui->ChBoxSearchSizeText->isChecked());
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_IsMemorySetupsSearch, this->ui->ChBoxMemorySetups->isChecked());
    //Parametry tekstu
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_Translate, this->ui->CBoxSelectTranslates->currentIndex());
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_SetupRangeBooks, this->ui->CBoxSelectRangeBooksSearch->currentIndex());
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_StartUserRange, this->ui->CBoxStartSelectBook->currentIndex());
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_StopUserRange, this->ui->CBoxStopSelectBook->currentIndex());
  GlobalVar::Global_ConfigFile->endGroup();
}
//---------------------------------------------------------------------------
void SearchWindow::_OnClickButtonHelpReg()
/**
   OPIS METOD(FUNKCJI): Przycisk pomocy dla składni wyszukiwań za pomocą wyrażeń regularnych
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QPushButton *pButton = qobject_cast<QPushButton *>(QObject::sender());
  if(!pButton) return;
  //---
  QMessageBox::information(this, "Informacja dotycząca wyrażeń regularnych", QString(". - (kropka)=dowolny znak\n") +
      "^ - dopasuj występujące po operatorze wyrażenie do początku wiersza (początek linii)\n" +
      "$ - dopasuj poprzedzające wyrażenie do końca wiersza (koniec linii)\n" +
      "\\x - znaki specjalne, gdzie  x to znak specjalny np. \\$ zastąpi znak dolara\n" +
      "[lista] - zastępuje dowolny znak spośród tych wymienionych na liście, mogą to być, przedziały np. [0-9] lub [a-d]\n" +
      "[^lista] - pasuje do znaku nie podanego na liście\n" +
      "\\< - początek słowa\n" +
      "\\> - koniec słowa\n" +
      "\\w - jest równoważne [0-9a-zA-Z] lub [[:alnum:]] – zastępuje dowolną liczbę lub cyfrę\n" +
      "\\W - oznacza to samo co $[^[[:alnum:]]]\n" +
      "()  - grupowanie wyrażeń regularnych\n" +
      "| 	 - operator LUB\n" +
      "? 	 - dokładnie zero lub jeden element wcześniejszy\n" +
      "a|b - dopasuje wyrażenie  a lub wyrażenie  b\n" +
      "* 	 - dopasuj zero lub więcej wyrażeń znaku poprzedzający operator\n" +
      "+ 	 - jeden lub więcej elementów poprzedzających operator\n" +
      "{n} - poprzedzający element pasuje dokładnie n razy");
}
//---------------------------------------------------------------------------
void SearchWindow::_InitSignalsAndTags()
/**
   OPIS METOD(FUNKCJI): Inicjowanie tagów i podpinanie sygnałów
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //this->ui->LViewResultSearch->setUserData()

  connect(this->ui->ButtonHelpRegExp, SIGNAL(clicked()), this, SLOT(_OnClickButtonHelpReg())); //Uruchamianie wyszukiwania
  connect(this->ui->ButtonSearchStart, SIGNAL(clicked()), this, SLOT(_OnClickButtonStartSearch())); //Rozpoczęcie wyszukiwania
  connect(this->ui->ButtonHelpSearch, SIGNAL(clicked()), this, SLOT(_OnClickButtonHelpSearch())); //Pomoc dla wyszukiwania
  connect(this->ui->ButtonExitSearch, SIGNAL(clicked()), this, SLOT(_OnClickButtonExitSearch())); //Wyjście z wyszukiwania

  connect(this->ui->CBoxSelectRangeBooksSearch, SIGNAL(currentIndexChanged(int)), this, SLOT(_OnSetCurentCBoxIndexChange(int))); //Zmieniłeś wybór elementu w QComboBox
  connect(this->ui->CBoxStartSelectBook, SIGNAL(currentIndexChanged(int)), this, SLOT(_OnSetCurentCBoxIndexChange(int))); //Zmieniłeś wybór elementu w QComboBox
  connect(this->ui->CBoxStopSelectBook, SIGNAL(currentIndexChanged(int)), this, SLOT(_OnSetCurentCBoxIndexChange(int))); //Zmieniłeś wybór elementu w QComboBox

  connect(this->ui->LViewResultSearch, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(_OnClickLViewWidgetItem(QListWidgetItem *))); //Kliknięto na pozycje listy wyników wyszukiwania
  connect(this->ui->LViewStatistic, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(_OnClickLViewWidgetItem(QListWidgetItem *)));
  connect(this->ui->CBoxHistorySearch, SIGNAL(currentTextChanged(const QString &)), this, SLOT(_OnTextChanged(const QString &))); //Wybrano pozycje z objektu, klasy QComboBox, z historią wyszukiwania
  //Sygnay dla przycisków wyboru kolorów
  connect(this->ui->ButtonColorAllSearch, SIGNAL(clicked()), this, SLOT(_OnClickSelectColors()));
  connect(this->ui->ButtonColorSelectSearch, SIGNAL(clicked()), this, SLOT(_OnClickSelectColors()));
  connect(this->ui->ButtonColorStatictic, SIGNAL(clicked()), this, SLOT(_OnClickSelectColors()));
  this->ui->ButtonColorAllSearch->setProperty(PropButtonSelectColorTag, enColor_AllSearch);
  this->ui->ButtonColorSelectSearch->setProperty(PropButtonSelectColorTag, enColor_SelectVers);
  this->ui->ButtonColorStatictic->setProperty(PropButtonSelectColorTag, enColor_Statistic);
  //Ustawienia właściwości użytkownika dla objektów klasy QListWidget
  this->ui->LViewResultSearch->setProperty(PropLWidgetTag, enListWidgetResultSearch);
  this->ui->LViewStatistic->setProperty(PropLWidgetTag, enListWidgetStatistic);
  //Ustawienie właściwości użytkownika dla objektów klasy QComboBox
  this->ui->CBoxStartSelectBook->setProperty(PropCBoxTag, enCBox_SelectStartBook);
  this->ui->CBoxStopSelectBook->setProperty(PropCBoxTag, enCBox_SelectStopBook);
  this->ui->CBoxSelectRangeBooksSearch->setProperty(PropCBoxTag, enCBox_SelectRange);
}
//---------------------------------------------------------------------------
void SearchWindow::_OnClickButtonStartSearch()
/**
   OPIS METOD(FUNKCJI): Przycisk rozpoczęcia wyszukiwania
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QPushButton *pButton = qobject_cast<QPushButton *>(QObject::sender());
  if(!pButton) return;
  //---
  if(this->ui->CBoxHistorySearch->currentText().isEmpty()) return; //Brak tekstu do wyszukania
  //---
  //QVector<int> VListResultsSearch(QGsReadBibleTextData::QGsNumberBooks); //Tablica wyników przeszukiwania //Do przróbki!!!
  //int VListResultsSearch[QGsReadBibleTextData::QGsNumberBooks]; //Tablica wyników przeszukiwania
  QStringList pBookListText;
  QString qstrSameText, qstrConvText, qstrSameAdress, qstrTemp;
  const QString qstrStyleSearch="<span class=styleFound>";
  int iPositionSearch=-1, VListResultsSearch[QGsReadBibleTextData::QGsNumberBooks], //Tablica wyników przeszukiwania
      iBook, //Numer księgi odczytany z pliku tekstu biblijnego konkretnego tłumaczenia
      iChapt, //Numer rozdziału odczytany z pliku tekstu biblijnego konkretnego tłumaczenia
      iVers; //Numer wersetu odczytany z pliku tekstu biblijnego konkretnego tłumaczenia
  const int ciOffsetAdress=9;
  bool ok=false; //Czy konwersja ze QString na int przebiegła pomyślnie(true)
  QListWidgetItem *newItem=nullptr;

  for(int &i : VListResultsSearch) i=0;

  //Wyłuskanie konkretnego tłumaczenia, o numerze this->ui->CBoxSelectTranslates->currentIndex()
  QGsReadBibleTextItem *pQGsReadBibleTextItem = QGsReadBibleTextData::QGetTranslate(this->ui->CBoxSelectTranslates->currentIndex());
  if(pQGsReadBibleTextItem)
  {
    this->ui->SelectBookSearchEdit->clear(); //QTextEdit
    this->_QListSearchResult.clear(); //Lista wszystkich wyszukanych wersetów w stanie surowym
    this->ui->LViewResultSearch->clear(); //Lista znalezionych wersetów

    for(int iIndexBook=this->ui->CBoxStartSelectBook->currentIndex(); iIndexBook <= this->ui->CBoxStopSelectBook->currentIndex(); iIndexBook++)
    {
      //Wyłuskanie konkretnej księgi, z konkretnego tłumaczenia w stanie surowym
      pBookListText = QGsReadBibleTextData::QGetSelectBoksInTranslate(pQGsReadBibleTextItem, iIndexBook);

      for(int i=0; i<pBookListText.count(); i++)
      {
        qstrSameText = pBookListText.at(i).mid(csuiOffsetSameTextVers); //Sam tekst
        qstrConvText = QGsReadBibleTextData::QConvertVerses(pBookListText.at(i)); //Cały werset z adresem
        //Jeśli wyszukiwanie opiera się na wyrażeniach regularnych
        if(this->ui->ChBoxIsRegEx->checkState() == Qt::Checked)
        {
          iPositionSearch = qstrSameText.indexOf(QRegExp(this->ui->CBoxHistorySearch->currentText(), Qt::CaseInsensitive));
        }
        else
        {//Wyszukiwanie zwykłe
          iPositionSearch = qstrSameText.indexOf(this->ui->CBoxHistorySearch->currentText(), 0, Qt::CaseInsensitive); //A jak dwa razy występuje w wersecie?
        }

        if(iPositionSearch > -1)
        {
          iBook =  pBookListText.at(i).midRef(0, 3).toInt(&ok);
          iChapt =  pBookListText.at(i).midRef(3, 3).toInt(&ok);
          iVers =  pBookListText.at(i).midRef(6, 3).toInt(&ok);
          //---
          if(ok)
          {
            //Tworzenie QListWidget wszystkich znalezionych wersetów
            qstrSameAdress = QString("%1 %2:%3").arg(QGsReadBibleTextData::QGsInfoAllBooks[iBook-1].ShortNameBook).
                arg(iChapt).arg(iVers);
            QListWidgetItem *newitem = new QListWidgetItem(QIcon(":/Search/gfx/Szukaj.png"), qstrSameAdress); //Główną zawartością listy będą adresy, bez tekstu
            newitem->setData(CI_ITEMS_RESULT_SEARCH_TEXT_DATA, qstrConvText); //Prywatnymi danymi będzie cały tekst wersetu, razem z adresem
            newitem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//(Qt::AlignHCenter | Qt::AlignTop);
            this->ui->LViewResultSearch->addItem(newitem); //zawartością pozycji będzie sam adres
            VListResultsSearch[iIndexBook]++; //Wypełnianie listy wynikami dla statystyki, dla poszczególnych ksiąg

            //Zaznaczanie wyszukanego słowa w tekście wersetu //03-05-2021
            qstrTemp = pBookListText.at(i);
            qstrTemp = qstrTemp.insert(iPositionSearch + ciOffsetAdress, qstrStyleSearch);
            qstrTemp = qstrTemp.insert(iPositionSearch + ciOffsetAdress + this->ui->CBoxHistorySearch->currentText().count() + qstrStyleSearch.count(), QString("</span>"));
            //QStringLista wszystkich wyszukanych wersetów w stanie surowym
            this->_QListSearchResult.append(qstrTemp);
          } //if(ok)
        } //if(iPositionSearch > -1)
      } //for(int i=0; i<pBookListText.count(); i++)
    } //for(int iIndexBook=this->ui->CBoxStartSelectBook->currentIndex(); iIndexBook <= this->ui->CBoxStopSelectBook->currentIndex(); iIndexBook++)
  } //if(pQGsReadBibleTextItem)
  this->ui->StBarInfos->setText(QString("Znaleziono: %1 pozycji").arg(this->ui->LViewResultSearch->count()));
  this->_DisplayListTextHTML(this->ui->TextEditSelectItemResult, this->_QListSearchResult, enTypeDisplay_ResultsearchAll);

  //Lista ksiąg biblijnych dla statystyki wyszukiwania
  for(int i=0; i<QGsReadBibleTextData::QGsNumberBooks; i++)
  {
     newItem = this->ui->LViewStatistic->item(i); //Wyłuskanie pozycji listy statystyki
     if(!newItem) continue;
     //newItem->setData(CI_ITEMSSTATISTICLLlRESULTS_DATA, VListResultsSearch.at(i)); //Wszystkich znalezionych pozycji
     newItem->setData(CI_ITEMS_STATISTIC_LIST_BOOK_RESULTS_DATA, VListResultsSearch[i]); //Ilość znalezionych pozycji w danej księdze
     newItem->setData(CI_ITEMS_STATISTIC_COUNTS_ALL_RESULTS_DATA, this->ui->LViewResultSearch->count()); //Wszystkich znalezionych pozycji
  }
  //Zakładka statystyki widoczna
  this->ui->PageTabInputSearchText->setTabVisible(enTabSheet_Statistic, true);
}
//---------------------------------------------------------------------------
void SearchWindow::_OnClickButtonHelpSearch()
/**
   OPIS METOD(FUNKCJI): Pomoc dla wyszukiwania
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QPushButton *pButton = qobject_cast<QPushButton *>(QObject::sender());
  if(!pButton) return;
  //---
}
//---------------------------------------------------------------------------
void SearchWindow::_OnClickButtonExitSearch()
/**
   OPIS METOD(FUNKCJI): Wyjście z wyszukiwania
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QPushButton *pButton = qobject_cast<QPushButton *>(QObject::sender());
  if(!pButton) return;
  //---
}
//---------------------------------------------------------------------------
void SearchWindow::_OnClickSelectColors()
/**
   OPIS METOD(FUNKCJI): Wybór kolorów
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QPushButton *pButton = qobject_cast<QPushButton *>(QObject::sender());
  if(!pButton) return;
  //---
  QPalette palette = pButton->palette();

  QColorDialog pCDialog = QColorDialog(palette.color(QPalette::Button), this);
  //pCDialog.setOptions(QColorDialog::DontUseNativeDialog);
  int iResult = pCDialog.exec();
  if(iResult == QDialog::Rejected)
  {
    return;
  }
  QColor color = pCDialog.selectedColor();

  palette.setColor(QPalette::Button, color);
  pButton->setPalette(palette);
  pButton->update();
  //Wypisanie w objekcie klasy QPushButton koloru
  pButton->setText(color.name());
  //Aktualizacje wyświetlania, po zmianie kolorów
  if(this->_QListSearchResult.count() > 0)
  {
    //Aktualizacja selekcji pojedyńczego wersetu
    this->ui->LViewResultSearch->setCurrentRow(0);
    emit this->ui->LViewResultSearch->itemClicked(this->ui->LViewResultSearch->currentItem());
    //Aktualizacja listy wybranego rozdziały, w statystyce wyszukiwania
      //Odczyt pierwszej pozycji z list wszystkich wyszukanych wersetów, by odczytać numer księgi, która jest jednocześnie pozycją w liście
    int iSelectbook = this->_QListSearchResult.at(0).midRef(0, 3).toInt() - 1;
    this->ui->LViewStatistic->setCurrentRow(iSelectbook);
    emit this->ui->LViewStatistic->itemClicked(this->ui->LViewStatistic->currentItem());
    //Aktualizacja wyświetlania wszystkich znalezionych wersetów
    this->_DisplayListTextHTML(this->ui->TextEditSelectItemResult, this->_QListSearchResult, enTypeDisplay_ResultsearchAll);
  }
}
//---------------------------------------------------------------------------
void SearchWindow::_OnSetCurentCBoxIndexChange(int iIndex)
/**
   OPIS METOD(FUNKCJI): Zmieniono aktywny element w QComboBox
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QComboBox *pCBox = qobject_cast<QComboBox *>(QObject::sender());
  if(!pCBox) return;
  //---
  //int iItemData = pCBox->itemData(iIndex).toInt();
  int iItemData = pCBox->property(PropCBoxTag).toInt();

  //#if defined(_DEBUGINFO_)
  //  qDebug() << "itemData: " << iItemData;
  //#endif

  switch(iItemData)
  {
    case enCBox_SelectRange: //Objekt klasy QComboBox wyboru zakresu
    {
      if((pCBox->currentIndex() >= en_GrSearch_Count) || (pCBox->currentIndex()==-1)) return; //qgsreadbibletextclass.h
      //---
      this->ui->CBoxStartSelectBook->setEnabled(true);
      this->ui->CBoxStopSelectBook->setEnabled(true);
      switch(pCBox->currentIndex()) //Wybór pozycji z bjektu klasy QComboBox dla wyboru zakresu
      {
        /*
        case en_GrSearch_FullAll: //Wszystkie księgi, bez apokryfów
        break;
        //---
        case en_GrSearch_Old:      //Księgi Starego Testamentu
        break;
        //---
        case en_GrSearch_New:      //Księgi Nowego Testamentu
        break;
        //---
        case en_GrSearch_Apocr:    //Księgi apokryficzne
        break;
        //---
        */
        case en_UserRange:         //Własny zakres
        {
          this->ui->CBoxStartSelectBook->setCurrentIndex(0); //Tymczasowo
          this->ui->CBoxStopSelectBook->setCurrentIndex(0);
        }
        break;
        //---
        case en_OneBook:           //Pojedyńcza księga
        {
          this->ui->CBoxStartSelectBook->setCurrentIndex(0); //Tymczasowo
          this->ui->CBoxStopSelectBook->setCurrentIndex(0);
        }
        break;
        //---
        default:
        {
          this->ui->CBoxStartSelectBook->setCurrentIndex(QGsReadBibleTextData::QGsPairsGroupBible[pCBox->currentIndex()].ucStartRange);
          this->ui->CBoxStopSelectBook->setCurrentIndex(QGsReadBibleTextData::QGsPairsGroupBible[pCBox->currentIndex()].ucStopRange);
          this->ui->CBoxStartSelectBook->setEnabled(false);
          this->ui->CBoxStopSelectBook->setEnabled(false);
        }
        break;
      } //switch(pCBox->currentIndex())
    } //case enCBox_SelectRange:
    break;
    //---
    case enCBox_SelectStartBook: //Objekt klasy QComboBox wyboru księgi startu
    {
      if(this->ui->CBoxSelectRangeBooksSearch->currentIndex() == en_OneBook)
      //Taki sam wybór w stopie
      {
        this->ui->CBoxStopSelectBook->setCurrentIndex(pCBox->currentIndex());
      }
      else if(this->ui->CBoxSelectRangeBooksSearch->currentIndex() == en_UserRange)
      {
        if(pCBox->currentIndex() > this->ui->CBoxStopSelectBook->currentIndex())
        //Jeśli księga startu jest większa niż stop, to ustaw na tą sama księgę
        {
          pCBox->setCurrentIndex(this->ui->CBoxStopSelectBook->currentIndex());
        }
      }
    } //case enCBox_SelectStartBook:
    break;
    //---
    case enCBox_SelectStopBook: //Objekt klasy QComboBox wyboru księgi stopu
    {
      if(this->ui->CBoxSelectRangeBooksSearch->currentIndex() == en_OneBook)
      //Taki sam wybór w starcie
      {
        this->ui->CBoxStartSelectBook->setCurrentIndex(pCBox->currentIndex());
      }
      else if(this->ui->CBoxSelectRangeBooksSearch->currentIndex() == en_UserRange)
      {
        if(pCBox->currentIndex() < this->ui->CBoxStartSelectBook->currentIndex())
        //Jeśli księga stopu jest mniejsza niż start, to ustaw na tą sama księgę
        {
          pCBox->setCurrentIndex(this->ui->CBoxStartSelectBook->currentIndex());
        }
      }
    } //case enCBox_SelectStopBook:
    break;
  }
}
//---------------------------------------------------------------------------
void SearchWindow::_OnClickLViewWidgetItem(QListWidgetItem *item)
/**
   OPIS METOD(FUNKCJI): Kliknięto na pozycje listy wyników wyszukiwania, lub statystyki
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QListWidget *pQListWidget = qobject_cast<QListWidget *>(QObject::sender());
  if(!pQListWidget) return;
  //---
  int iResultSelect = pQListWidget->property(PropLWidgetTag).toInt();

  switch(iResultSelect)
  {
    case enListWidgetResultSearch: //Objekt klasy QListWidget dla wyszukanych wersetów
    {
      //Wyświetl aktualnie zaznaczoną pozycji z całej listy wyników wyszukiwania (currentRow)
      this->_DisplayListTextHTML(this->ui->TextSelectItemResultEdit, this->_QListSearchResult, enTypeDisplay_ResultSelectVers, pQListWidget->currentRow());
    }
    break;
    //---
    case enListWidgetStatistic: //Objekt klasy QListWidget dla statystyki
    {
      this->ui->SelectBookSearchEdit->clear();
      QStringList _tempQSLst;
      if(item->data(CI_ITEMS_STATISTIC_COUNTS_ALL_RESULTS_DATA).toInt() > 0) //Ilość znalezionych pozycji w danej księdze
      {
        int iSelectBook=pQListWidget->currentRow(),
            iSearchBook=0; //Numer księgi odczytany z pliku tekstu biblijnego konkretnego tłumaczenia
        bool ok=false;

        for(int i=0; i<this->_QListSearchResult.count(); i++)
        {
          iSearchBook = this->_QListSearchResult.at(i).midRef(0, 3).toInt(&ok)-1;
          if(ok && (iSearchBook == iSelectBook))
          {
            if(iSelectBook == iSearchBook)
            {
              _tempQSLst.append(this->_QListSearchResult.at(i));
            }

          } //if(ok && (iSearchBook == iSelectBook))
        } //for(int i=0; i<this->_QListSearchResult.count(); i++)
      }
      this->_DisplayListTextHTML(this->ui->SelectBookSearchEdit,_tempQSLst, enTypeDisplay_ResultSearchSelectBook);
      this->ui->SelectBookSearchEdit->moveCursor(QTextCursor::Start);
    }
    break;
  }
}
//---------------------------------------------------------------------------
void SearchWindow::_OnTextChanged(const QString &text)
/**
   OPIS METOD(FUNKCJI): Zmieniłeś zawartość pola do wpisywania tekstu wyszukiwanego
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QComboBox *pEditSearch = qobject_cast<QComboBox *>(QObject::sender());
  if(!pEditSearch) return;
  //Aktywacja rozpoczęcia wyszukiwania, tylko gdy został wpisany tekst wyszukiwany
  this->ui->ButtonSearchStart->setEnabled(!text.isEmpty());
}
//---------------------------------------------------------------------------
void SearchWindow::_DisplayListTextHTML(QTextEdit *_QTextView, const QStringList &_QListAnyVers, const EnTypeDisplayHTML _TypeDisplayHTML, const int iSelectDisplayVerset)
/**
   OPIS METOD(FUNKCJI):
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //Kolory dla QPushButton ustawiania kolorów podkładu
  QColor temp_colorAllSearch = this->ui->ButtonColorAllSearch->palette().color(QPalette::Button),
         temp_colorSelectSearch = this->ui->ButtonColorSelectSearch->palette().color(QPalette::Button),
         temp_colorStatisticSearch = this->ui->ButtonColorStatictic->palette().color(QPalette::Button);

  const QString qstrDisplayHeaderHTMLSearchAll = QString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">") +
      "<html><head>" +
      "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">" +
      "<title>Wyniki wyszukiwania</title>" +
      "<style type=\"text/css\">" +
      ".styleColorAdressTranslates {color: #FF0000; font-size:14pt;font-family:Times New Roman;}" +
      ".styleText {color: #000000;font-size:18pt;font-family:Times New Roman;}\n" +
      ".styleFound {background-color: #FFFF00;}" +
      "body {background-color:" + temp_colorAllSearch.name() +
        ";font-size:18pt;font-family:Times New Roman;}" +
      "</style></head><body>",
  qstrDisplayHeaderHTMLSearchBook = QString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">") +
      "<html><head>" +
      "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">" +
      "<title>Wyniki wyszukiwania</title>" +
      "<style type=\"text/css\">" +
      ".styleColorAdressTranslates {color: #FF0000; font-size:14pt;font-family:Times New Roman;}" +
      ".styleText {color: #000000;font-size:16pt;font-family:Times New Roman;}\n" +
      ".styleFound {background-color: #FFFF00;}" +
      "body {background-color:" + temp_colorStatisticSearch.name() +
        ";font-size:16pt;font-family:Times New Roman;}" +
      "</style></head><body>",
  qstrDisplayHeaderHTMLSelectSearchVers = QString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">") +
      "<html><head>" +
      "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">" +
      "<title>Wyniki wyszukiwania</title>" +
      "<style type=\"text/css\">" +
      ".styleColorAdressTranslates {color: #FF0000; font-size:24pt;font-family:Times New Roman;}" +
      ".styleText {color: #000000;font-size:24pt;font-family:Times New Roman;}\n" +
      ".styleFound {background-color: #FFFF00;}" +
      "body {background-color:" + temp_colorSelectSearch.name() +
        ";font-size:16pt;font-family:Times New Roman;}" +
      "</style></head><body>";
  QString qstrDefineDisplayHTML, qstrSameText, qstrSameAdress;
  int iBook, //Numer księgi odczytany z pliku tekstu biblijnego konkretnego tłumaczenia
      iChapt, //Numer rozdziału odczytany z pliku tekstu biblijnego konkretnego tłumaczenia
      iVers; //Numer wersetu odczytany z pliku tekstu biblijnego konkretnego tłumaczenia
  bool ok=false; //Czy konwersja ze QString na int przebiegła pomyślnie(true)
  //---
  switch(_TypeDisplayHTML)
  {
    case enTypeDisplay_ResultsearchAll:        //Wyświetlanie wszystkich znalezionych wersetów
      qstrDefineDisplayHTML = qstrDisplayHeaderHTMLSearchAll;
    break;
    //---
    case enTypeDisplay_ResultSearchSelectBook: //Wyświetlanie znelozionych wersetów dla konkretnej księgi
      qstrDefineDisplayHTML = qstrDisplayHeaderHTMLSearchBook;
    break;
    //---
    case enTypeDisplay_ResultSelectVers:       //Wyświetlanie wybranego wersetu z listy wszystkich znalezionych wesetów
      qstrDefineDisplayHTML = qstrDisplayHeaderHTMLSelectSearchVers;
    break;
  }

  for(int i=0; i<_QListAnyVers.count(); i++)
  {
    if((iSelectDisplayVerset > -1) && (i != iSelectDisplayVerset)) continue;
    qstrSameText = _QListAnyVers.at(i).mid(csuiOffsetSameTextVers); //Sam tekst
    iBook =  _QListAnyVers.at(i).midRef(0, 3).toInt(&ok);
    iChapt =  _QListAnyVers.at(i).midRef(3, 3).toInt(&ok);
    iVers =  _QListAnyVers.at(i).midRef(6, 3).toInt(&ok);
    qstrSameAdress = QString("%1 %2:%3").arg(QGsReadBibleTextData::QGsInfoAllBooks[iBook-1].ShortNameBook).
        arg(iChapt).arg(iVers); //Sam adres

    //Dodawanie kolejnego wersetu
    qstrDefineDisplayHTML.append(QString("<span class=\"styleColorAdressTranslates\"> %1 </span>").arg(qstrSameAdress));
    qstrDefineDisplayHTML.append(QString("<span class=\"styleText\">%1 </span>").arg(qstrSameText));
    qstrDefineDisplayHTML.append("<br>");
  }
  qstrDefineDisplayHTML.append("</body></html>");
  _QTextView->setHtml(qstrDefineDisplayHTML);
}
//---------------------------------------------------------------------------
void MyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
/**
   OPIS METOD(FUNKCJI):
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{

  int iValue = qvariant_cast<int>(index.data(CI_ITEMS_STATISTIC_LIST_BOOK_RESULTS_DATA));
  int iMax = qvariant_cast<int>(index.data(CI_ITEMS_STATISTIC_COUNTS_ALL_RESULTS_DATA));

  if((option.state & QStyle::State_Selected) && (iValue > 0)) //02-05-2021
  {
    painter->fillRect(option.rect, QColor(255, 0, 0));
  }

  QString title = index.data(Qt::DisplayRole).toString();

  QRect r = option.rect.adjusted(2, 0, 0, 0);
  QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
  QPixmap pix = icon.pixmap(r.size());

  const QPoint p = QPoint(2, (r.height() - pix.height())/2); //Rysowanie ikony
  painter->drawPixmap(r.topLeft() + p, pix);
  if(iValue > 0) //25-04-2021
  {
    QStyleOptionProgressBar progressBarOption;

    progressBarOption.state = QStyle::State_Enabled;
    progressBarOption.direction = QApplication::layoutDirection();
    progressBarOption.fontMetrics = QApplication::fontMetrics();
    progressBarOption.minimum = 0;
    progressBarOption.maximum = iMax;

    QRect newRect = option.rect.adjusted(pix.width() + (pix.width() / 2), 1, 0, -1);
    progressBarOption.rect = newRect;
    progressBarOption.text = QString("%1 - Znaleziono %2 pozycji").arg(title).arg(iValue);
    progressBarOption.textVisible = true;
    progressBarOption.textAlignment = Qt::AlignCenter;
    progressBarOption.progress = iValue;

    QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
  }
  else
  {
    //Pozycje ksiąg biblijnych, w których nie znaleziono wyszukiwanego słowa 25-04-2021
    QRect textRect = r.adjusted(22, 0, 0, 0);
    painter->setPen(QColor(160, 160, 160));
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, title);
  }
}
//---------------------------------------------------------------------------
QSize MyDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
/**
   OPIS METOD(FUNKCJI):
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QSize result = QStyledItemDelegate::sizeHint(option, index);
  return result;
}
//---------------------------------------------------------------------------
