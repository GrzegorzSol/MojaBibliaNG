#include "searchwindow.h"
#include "ui_searchwindow.h"
#include "globalvar.h"
#include "QGsReadBibleTextClass/qgsreadbibletextclass.h"
#include <QMessageBox>
#include <QPushButton>
#include "mblitelibrary.h"

/*
#if defined(_DEBUGINFO_)
 qDebug() << "";
#endif
*/
//enum {enAllButtonSearch_Search, enAllButtonSearch_Help, enAllButtonSearch_Cancel};

enum {enCBox_SelectRange=100, enCBox_SelectStartBook, enCBox_SelectStopBook};

QVector<int> GlobalResultsSearch(QGsReadBibleTextData::QGsNumberBooks); //Tablica wyników przeszukiwania
const QString GlobalHeaderListSearch = QString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n") +
    "<html><head>\n" +
    "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n" +
    "<title>Wybrany rozdział, dla dostępnych tłumaczeń</title>\n" +
    "<style type=\"text/css\">\n" +
    ".styleColorAdressTranslates {color: #0000FF; font-size:14pt;font-family:Times New Roman;}\n" +
    ".styleText {color: #000000;font-size:14pt;font-family:Times New Roman;}\n" +
    //#if !defined(Q_OS_MACOS)
    "body {background-color: #FFEEEE;font-size:14pt;font-family:Times New Roman;}\n" +
    //#endif
    "</style></head><body>\n";
;

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
   this->ui->CBoxStartSelectBook->setItemData(i, enCBox_SelectStartBook);
   this->ui->CBoxStopSelectBook->addItem(iconItems, QGsReadBibleTextData::QGsInfoAllBooks[i].FullNameBook);
   this->ui->CBoxStopSelectBook->setItemData(i, enCBox_SelectStopBook);
 }
 //Domyślnie wszystkie księgi do przeszukania
 this->ui->CBoxStartSelectBook->setCurrentIndex(0);
 this->ui->CBoxStopSelectBook->setCurrentIndex(QGsReadBibleTextData::QGsNumberBooks-1);
 //Definiowanie komponentu zakresu wyszukiwania
 QIcon iconRange(":/Search/gfx/WybórZakresu.png");
 for(int i=0; i<en_GrSearch_Count; i++)
 {
   this->ui->CBoxSelectRangeBooksSearch->addItem(iconRange, QGsReadBibleTextData::QGsNameAllRanges[i]);
   this->ui->CBoxSelectRangeBooksSearch->setItemData(i, enCBox_SelectRange);
 }
 this->ui->CBoxSelectRangeBooksSearch->setCurrentIndex(0);
 //Definiowanie listy tłumaczeń do wybrania
 //qDebug() << "QGsReadBibleTextData::QCountTranslates(): " << QGsReadBibleTextData::QCountTranslates();
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
 for(int i=0; i<_qsltemp.count(); i++)
  {this->ui->CBoxHistorySearch->addItem(_qsltemp.at(i));}
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

  delete this->ui;
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
  connect(this->ui->ButtonHelpRegExp, SIGNAL(pressed()), this, SLOT(_OnClickButtonHelpReg())); //Uruchamianie wyszukiwania
  connect(this->ui->ButtonSearchStart, SIGNAL(pressed()), this, SLOT(_OnClickButtonStartSearch())); //Rozpoczęcie wyszukiwania
  connect(this->ui->ButtonHelpSearch, SIGNAL(pressed()), this, SLOT(_OnClickButtonHelpSearch())); //Pomoc dla wyszukiwania
  connect(this->ui->ButtonExitSearch, SIGNAL(pressed()), this, SLOT(_OnClickButtonExitSearch())); //Wyjście z wyszukiwania

  connect(this->ui->CBoxSelectRangeBooksSearch, SIGNAL(currentIndexChanged(int)), this, SLOT(_OnSetCuurentIndexChange(int))); //Zmieniłeś wybór elementu w QComboBox
  connect(this->ui->CBoxStartSelectBook, SIGNAL(currentIndexChanged(int)), this, SLOT(_OnSetCuurentIndexChange(int))); //Zmieniłeś wybór elementu w QComboBox
  connect(this->ui->CBoxStopSelectBook, SIGNAL(currentIndexChanged(int)), this, SLOT(_OnSetCuurentIndexChange(int))); //Zmieniłeś wybór elementu w QComboBox

  connect(this->ui->LViewResultSearch, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(_OnClickItem(QListWidgetItem *))); //Kliknięto na pozycje listy wyników wyszukiwania
  connect(this->ui->CBoxHistorySearch, SIGNAL(currentTextChanged(const QString &)), this, SLOT(_OnTextChanged(const QString &)));
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
  QStringList pBookListText;
  QString qstrItem, qstrSameText, qstrConvText, qstrDisplayHtml=GlobalHeaderListSearch;
  int iPositionSearch=-1,
      iBook, //Numer księgi odczytany z pliku tekstu biblijnego konkretnego tłumaczenia
      iChapt, //Numer rozdziału odczytany z pliku tekstu biblijnego konkretnego tłumaczenia
      iVers; //Numer wersetu odczytany z pliku tekstu biblijnego konkretnego tłumaczenia

  for(int &i : GlobalResultsSearch) i=0;
  this->ui->LViewStatistic->clear();

  //Wyłuskanie konkretnego tłumaczenia, o numerze this->ui->CBoxSelectTranslates->currentIndex()
  QGsReadBibleTextItem *pQGsReadBibleTextItem = QGsReadBibleTextData::QGetTranslate(this->ui->CBoxSelectTranslates->currentIndex());
  if(pQGsReadBibleTextItem)
  {
    this->ui->LViewResultSearch->clear();

    for(int iIndexBook=this->ui->CBoxStartSelectBook->currentIndex(); iIndexBook <= this->ui->CBoxStopSelectBook->currentIndex(); iIndexBook++)
    {
      //Wyłuskanie konkretnej księgi, z konkretnego tłumaczenia
      pBookListText = QGsReadBibleTextData::QGetSelectBoksInTranslate(pQGsReadBibleTextItem, iIndexBook);

      for(int i=0; i<pBookListText.count(); i++)
      {
        qstrSameText = pBookListText.at(i).mid(csuiOffsetSameTextVers);//, csuiMaxSizeVers);//Sam tekst
        qstrConvText = QGsReadBibleTextData::QConvertVerses(pBookListText.at(i)); //Sam tekst
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
          QListWidgetItem *newitem = new QListWidgetItem(QIcon(":/Search/gfx/Szukaj.png"), qstrConvText);
          newitem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);//(Qt::AlignHCenter | Qt::AlignTop);
          this->ui->LViewResultSearch->addItem(newitem);
          GlobalResultsSearch[iIndexBook]++; //Wypełnianie listy wynikami, dla poszczególnych ksiąg
          //Dodawanie znalezionych wersetów by wyświetlić je w formie html
          iBook =  pBookListText.at(i).midRef(0, 3).toInt();
          iChapt =  pBookListText.at(i).midRef(3, 3).toInt();
          iVers =  pBookListText.at(i).midRef(6, 3).toInt();

          qstrDisplayHtml.append(QString("<span class=\"styleColorAdressTranslates\"> %1 %2:%3 </span>").arg(QGsReadBibleTextData::QGsInfoAllBooks[iBook-1].ShortNameBook).
              arg(iChapt).arg(iVers));
          qstrDisplayHtml.append(QString("<span class=\"styleText\">%1 </span>").arg(qstrSameText));
          qstrDisplayHtml.append("<br>");
        }
      }
    }
  }
  this->ui->StBarInfos->setText(QString("Znaleziono: %1 pozycji").arg(this->ui->LViewResultSearch->count()));
  qstrDisplayHtml.append("</body></html>");
  this->ui->TextEditSelectItemResult->setHtml(qstrDisplayHtml);

  //Lista ksiąg biblijnych dla statystyki wyszukiwania
  QIcon iconStatistic;
  iconStatistic.addFile(":/Search/gfx/StatystykaWyszukiwania.png", QSize(), QIcon::Normal, QIcon::Off);
  for(int i=0; i<QGsReadBibleTextData::QGsNumberBooks; i++)
  {
     QListWidgetItem *newItem = new QListWidgetItem();//(QIcon(":/Search/gfx/KsięgaStat.png"), QGsReadBibleTextData::QGsInfoAllBooks[i].FullNameBook);
     //newitem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);//(Qt::AlignHCenter | Qt::AlignTop);
     newItem->setData(Qt::DisplayRole, QGsReadBibleTextData::QGsInfoAllBooks[i].FullNameBook);
     newItem->setData(Qt::DecorationRole, iconStatistic);
     newItem->setData(Qt::UserRole, GlobalResultsSearch.at(i));
     newItem->setData(Qt::UserRole+1, this->ui->LViewResultSearch->count());

     this->ui->LViewStatistic->addItem(newItem);
  }
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
void SearchWindow::_OnSetCuurentIndexChange(int iIndex)
/**
   OPIS METOD(FUNKCJI): WZmieniono akrywny element w QComboBox
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QComboBox *pCBox = qobject_cast<QComboBox *>(QObject::sender());
  if(!pCBox) return;
  //---
  int iItemData = pCBox->itemData(iIndex).toInt();

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
void SearchWindow::_OnClickItem(QListWidgetItem *item)
/**
   OPIS METOD(FUNKCJI): Kliknięto na pozycje listy wyników wyszukiwania
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QListWidget *pQListWidget = qobject_cast<QListWidget *>(QObject::sender());
  if(!pQListWidget) return;
  //---
  this->ui->TextSelectItemResult->setText(item->text());
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
/*
 *  Metody klasy MyDelegate
*/
void MyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
/**
   OPIS METOD(FUNKCJI):
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if(option.state & QStyle::State_Selected)
  {
    painter->fillRect(option.rect, QColor(255, 0, 0));
  }

  QString title = index.data(Qt::DisplayRole).toString();

  QRect r = option.rect.adjusted(2, 0, 0, 0);
  QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
  QPixmap pix = icon.pixmap(r.size());

  int iValue = qvariant_cast<int>(index.data(Qt::UserRole));
  int iMax = qvariant_cast<int>(index.data(Qt::UserRole+1));

  const QPoint p = QPoint(2, (r.height() - pix.height())/2);
  painter->drawPixmap(r.topLeft() + p, pix);

  QStyleOptionProgressBar progressBarOption;

  progressBarOption.state = QStyle::State_Enabled;
  progressBarOption.direction = QApplication::layoutDirection();
  progressBarOption.fontMetrics = QApplication::fontMetrics();
  progressBarOption.minimum = 0;
  progressBarOption.maximum = iMax;

  QRect newRect = option.rect.adjusted(pix.width() + (pix.width() / 2), 1, 0, -1);
  progressBarOption.rect = newRect;
  if(iValue>0)
  {
    progressBarOption.text = QString("%1 - Znaleziono %2 pozycji").arg(title).arg(iValue);
  }
  else
  {
    progressBarOption.text = QString("%1 - Brak wystąpień").arg(title);
  }
  progressBarOption.textVisible = true;
  progressBarOption.textAlignment = Qt::AlignCenter;
  progressBarOption.progress = iValue;

  QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
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
