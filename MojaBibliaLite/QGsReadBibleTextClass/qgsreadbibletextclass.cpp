#include "qgsreadbibletextclass.h"

#include "globalvar.h"
#include "mblitelibrary.h"
#include <QApplication>
#include <QToolBar>
#include <QDragEnterEvent>
#include <QMenu>
#include <QHeaderView>
#include <QObject>

static QStringList ErrorSList;

/*
#if defined(_DEBUGINFO_)
 qDebug() << "";
#endif

#if defined(_DEBUGINFO_)
  qDebug("%d", 12);
#endif
*/

/****************************************************************************
 *                        Klasalasa QGsReadBibleTextClass                   *
 ****************************************************************************/
QGsReadBibleTextClass::QGsReadBibleTextClass(const QString _PathDir) : uiCountPol(0), uiCountOryg(0)
/**
   OPIS METOD(FUNKCJI): Konstruktor
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QGsReadBibleTextData::pQGsReadBibleTextClass = this;

  this->_QLoadAllTranslates(_PathDir);
}
//---------------------------------------------------------------------------
QGsReadBibleTextClass::~QGsReadBibleTextClass()
/**
   OPIS METOD(FUNKCJI): Destruktor
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QGsReadBibleTextItem *pQGsReadBibleTextItem=nullptr;
  for(int i=0; i<this->_QListItemsTranslates.count(); i++)
  {
    pQGsReadBibleTextItem = this->_QListItemsTranslates.at(i);
    if(pQGsReadBibleTextItem) {delete pQGsReadBibleTextItem; pQGsReadBibleTextItem = nullptr;}
  }
  this->_QListItemsTranslates.clear(); //Lista tłumaczeń. Klas QGsReadBibleTextItem
}
//---------------------------------------------------------------------------
void QGsReadBibleTextClass::_QLoadAllTranslates(const QString _PathDir)
/**
   OPIS METOD(FUNKCJI): załadowanie wszystkich tłumaczeń biblii
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QStringList qSListFilter; //ustawienie filtra dla listy tłumaczeń
  EnTypeTranslate qenTypeTranslate; //Typ tłumaczenia, typu EnTypeTranslate
  //unsigned char uchIndex=0;
  QDir dirTemp(_PathDir);
  qSListFilter << QGsReadBibleTextData::QGsExtendFileTranslateFull << QGsReadBibleTextData::QGsExtendFileTranslateGrecOrg <<
                  QGsReadBibleTextData::QGsExtendFileTranslateHbrOrg;
  //Pozyskiwanie listy tłumaczeń
  QFileInfoList SDirTranslatesList = dirTemp.entryInfoList(qSListFilter, QDir::Files, QDir::Name | QDir::IgnoreCase);

  for(unsigned char uchIndex=0; uchIndex<SDirTranslatesList.count(); uchIndex++)
  {
    //Oznaczanie typów tłumaczeń
    if(SDirTranslatesList.at(uchIndex).suffix() == QGsReadBibleTextData::QGsExtendNoAsteriskFileTranslateFull)
    {qenTypeTranslate = enTypeTr_Full; this->uiCountPol++;}
    else if(SDirTranslatesList.at(uchIndex).suffix() == QGsReadBibleTextData::QGsExtendNoAsteriskFileTranslateGrecOrg)
    {qenTypeTranslate = enTypeTr_Greek; this->uiCountOryg++;}
    else if(SDirTranslatesList.at(uchIndex).suffix() == QGsReadBibleTextData::QGsExtendNoAsteriskFileTranslateHbrOrg)
    {qenTypeTranslate = enTypeTr_Hebrew; this->uiCountOryg++;}

    QGsReadBibleTextItem *pQGsReadBibleTextItem = new QGsReadBibleTextItem(SDirTranslatesList.at(uchIndex).filePath(), qenTypeTranslate, uchIndex);
    if(pQGsReadBibleTextItem)
    {
      this->_QListItemsTranslates.append(pQGsReadBibleTextItem); //Dodawanie objektu klasy QGsReadBibleTextItem tłumaczenia
      this->_QListAllTrChap.append(QStringList()); //Dodanie pustej QStringList'y, na wszystkie tłumaczenia dla wybranej księgi i rozdziału
    }
  }
}
//---------------------------------------------------------------------------
void QGsReadBibleTextClass::_QClearListAllTrChap(const bool bIsRemoveList)
/**
   OPIS METOD(FUNKCJI): Zwolnienie zawartości listy _QListAllTrChap.
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  #if defined(_DEBUGINFO_)
    qDebug() << "QGsReadBibleTextClass::_QClearListAllTrChap()";
  #endif
  for(int i=0; i<this->_QListAllTrChap.count(); i++)
  {
    this->_QListAllTrChap[i].clear();//Tylko czyszczenie ISTNIEJĄCYCH string list, na wybrany rozdział ze wszystkich tłumaczeń!!!
  }
  if(bIsRemoveList) this->_QListAllTrChap.clear();
}
//---------------------------------------------------------------------------
QStringList &QGsReadBibleTextClass::QGetSelectBookTranslate(const int iGetTranslate, const int iGetBook)
/**
   OPIS METOD(FUNKCJI): Metoda zwraca adres QStringList na pozycje określonej księgi i tłumaczenia
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if(iGetTranslate >= this->_QListItemsTranslates.count()) return ErrorSList;

  QGsReadBibleTextItem *pGsReadBibleTextItem = this->_QListItemsTranslates.at(iGetTranslate);
  if(pGsReadBibleTextItem)
  {
    return pGsReadBibleTextItem->_QListAllListBooks[iGetBook];
  }
  return ErrorSList;
}
//---------------------------------------------------------------------------
bool QGsReadBibleTextClass::_QGetAllTranslatesChapter(const int iGetBook, const int iGetChap)
/**
   OPIS METOD(FUNKCJI): Konstruowanie listy z wybranym rozdziałem, wybranej księgi dla wszystkich tłumaczeń
                        Metoda wywoływana QGsReadBibleTextData::QOpenSelectBookAndChapter()
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QStringList _pTempQSList;
  int iFindChapter=0; //Szukany rozdział
  this->_QClearListAllTrChap();

  for(int i=0; i<this->_QListItemsTranslates.count(); i++)
  {
    _pTempQSList = this->QGetSelectBookTranslate(i, iGetBook); //String lista wybranej księgi kolejnego tłumaczenia

    for(int iVers=0; iVers<_pTempQSList.count(); iVers++)
    {
      //Wyszukiwanie wybranego rozdziału w wybranej księdze, dla kolejnego tłumaczenia
      iFindChapter = _pTempQSList.at(iVers).midRef(3, 3).toInt();//Odczyt rozdziału kolejnego wersetu
      if(iFindChapter==iGetChap+1) //Rozdziały w tekście żródłowym są numerowane od 1
      {
        this->_QListAllTrChap[i].append(_pTempQSList.at(iVers));
      }
    }
  }
  return true;
}
//---------------------------------------------------------------------------
void QGsReadBibleTextClass::QDisplayAllTextInHTML(QTextEdit *_pWebBrowser, const int iSelectTranslate)
/**
   OPIS METOD(FUNKCJI): Metoda łączy w jedną całość jako kod Html tekst, ze wszystkich tłumaczeń, wybranej księgi i rozdziału.
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if(this->_QListAllTrChap.count() == 0) return;

  unsigned char uiTranslatesIndex;
  int iIndex=0, //Indeks wersetów w równoległym tłumaczeniu, lub pojedyńczym
      iBook, //Numer księgi odczytany z pliku tekstu biblijnego konkretnego tłumaczenia
      iChapt, //Numer rozdziału odczytany z pliku tekstu biblijnego konkretnego tłumaczenia
      iVers; //Numer wersetu odczytany z pliku tekstu biblijnego konkretnego tłumaczenia
  QString pStrBuilder = QGsReadBibleTextData::QGsHTMLHeaderText, //Tekst do wyświetlenia, utworzony z połączenia poszczególnych tłumaczeń
          qstrNameBook; //Skrócona nazwa księgi

  //Wyłuskanie aktywnej zakładki
  QGsTabSheetBookClass *pQGsTabSheetBookClass = static_cast<QGsTabSheetBookClass *>(QGsReadBibleTextData::pQGsPageControl->currentWidget());
  if(!pQGsTabSheetBookClass) return;
  //---
  do
  //Pętla obracająca się przez kolejne wersety wybranej księgi i rodziału, wszystkich dostępnych tłumaczeń (for)
  {
    //Jeśli chcemy tylko jedno tłumaczenie, to licznik tłumaczeń = 1
    if(iSelectTranslate>-1) uiTranslatesIndex = 1; else uiTranslatesIndex = this->_QListAllTrChap.count();
    //---
    for(int i=0; i<this->_QListAllTrChap.count(); i++) //Lista klasy QStringList, zawierających tekst wszystkich dostępnych tłumaczeń, z wybranego rodziału.
    //Dodawanie pokolei równoległych wersetów ze wszystkich tłumaczeń
    {
      if((iSelectTranslate>-1) && (i!=iSelectTranslate))
                //Jeśli ma być wyświetlone konkretne tłumaczenie
                //iSelectTranslate>-1, czyli nie wszyskie tłumaczenia (iSelectTranslate==-1)
                //i!=iSelectTranslate, pętla jest w niewybranym tłumaczeniu
                {continue;}

      //Wyłuskanie wskaźnika na objekt typu QGsReadBibleTextItem, konkretnego tłumaczenia
      //Wyłuskanie wskaźnika GsReadBibleTextItem konkretnego tłumaczenia, w celu sprawdzenia typu tłumaczenia
      QGsReadBibleTextItem *pQGsReadBibleTextItem = this->QGetTranslateClass(i);
      //Wyłuskanie QStringListy konkretnego tłumaczenia
      QStringList pTempSList = this->_QListAllTrChap.at(i); //QStringList wybranego rozdziału wybranej księgi
      //Gdy string lista pusta (hebrajski tekst w nowym testamencie, grecki tekst w starym testamencie), to nie wpływa na opuszczenie pętli do, while.
      if(pTempSList.count() == 0)
      //Gdy lista konkretnego tłumaczenia i rozdziału jest pusta, bo brak księgi.
      {
        uiTranslatesIndex--;
        if(iSelectTranslate>-1)
        {pStrBuilder.append("<span class=styleNoTranslate>To tłumaczenie nie zawiera tekstu, wybranej księgi!</span>");}

        continue; //Idę do następnego tłumaczenia, czyli do następnej QStringListy, listy this->_QListAllTrChap
      }
      if(iIndex < pTempSList.count())
      //Istnieją jeszcze wersety dla aktualnego tłumaczenia
      {
        //Dodawanie kolejnego wersetu
        if(!pTempSList.at(iIndex).isEmpty())
        {
          iBook = pTempSList.at(iIndex).midRef(0, 3).toInt();
          iChapt = pTempSList.at(iIndex).midRef(3, 3).toInt();
          iVers = pTempSList.at(iIndex).midRef(6, 3).toInt();
          qstrNameBook =  QGsReadBibleTextData::QGsInfoAllBooks[iBook-1].ShortNameBook;

          //wyświetlanie wersetu zależnie od typu tłumaczenia. Całościowe, lub częściowe, oryginalne
          if(pQGsReadBibleTextItem->enTypeTranslate == enTypeTr_Full)
          {
            pStrBuilder.append(QString("<span class=styleFullColorAdressTranslates>%1 %2:%3 </span>").arg(qstrNameBook).arg(iChapt).arg(iVers));
            pStrBuilder.append(QString("<span class=styleFullText> %1 </span>").
                               arg(pTempSList.at(iIndex).midRef(10)));
            pStrBuilder.append(QString("<span class=styleFullTranslates> [%1] </span>").arg(pQGsReadBibleTextItem->NameTranslate));
          }
          else if((pQGsReadBibleTextItem->enTypeTranslate == enTypeTr_Greek) || (pQGsReadBibleTextItem->enTypeTranslate == enTypeTr_Hebrew))
          {
            pStrBuilder.append(QString("<span class=styleAdressVersOryg>%1 %2:%3 </span>").arg(qstrNameBook).arg(iChapt).arg(iVers));
            pStrBuilder.append(QString("<span class=styleOrygin> %1 </span>").
                               arg(pTempSList.at(iIndex).midRef(10)));
            pStrBuilder.append(QString("<span class=styleNameVersOryg> [%1] </span>").arg(pQGsReadBibleTextItem->NameTranslate));
          }
          pStrBuilder.append("<br>");
        }
      }
      else
      //Aktualne tłumaczenie nie ma już wersetów, licznik tłumaczeń zostaje zmniejszony o 1
      {
        uiTranslatesIndex--;
      }
      //if(uiTranslatesIndex > 0) pStrBuilder.append("<br>");
      //if(i < (this->_QListAllTrChap.count()-1)) pStrBuilder.append("<br>");
    }
    iIndex++;
    if(uiTranslatesIndex >= cucMaxCountTranslates) uiTranslatesIndex=0; //Zabezpieczenie przed przekęceniem licznika
    if((iSelectTranslate == -1) && (uiTranslatesIndex > 0))
    {
      pStrBuilder.append("<hr>"); //Pozioma kreska;
    }
  }while(uiTranslatesIndex > 0);
  pStrBuilder.append("</body></html>");

  _pWebBrowser->setHtml(pStrBuilder);
  //_pWebBrowser->setPlainText(pStrBuilder);
}
//---------------------------------------------------------------------------
QGsReadBibleTextItem *QGsReadBibleTextClass::QGetTranslateClass(const int iNumberTrans)
/**
   OPIS METOD(FUNKCJI): Metoda zwraca wskaźnik na klasę wybranego tłumaczenia
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if(iNumberTrans >= this->_QListItemsTranslates.count()) return nullptr;
  QGsReadBibleTextItem *pQGsReadBibleTextItem = this->_QListItemsTranslates[iNumberTrans];
  return pQGsReadBibleTextItem;
}
//---------------------------------------------------------------------------
void QGsReadBibleTextClass::_QGetInfoNameTranslate(const int i, QString &NameTranslate)
/**
   OPIS METOD(FUNKCJI): Zwraca nazwę tłumaczenia o numerze i
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if(i >= this->_QListItemsTranslates.count()) {NameTranslate = "Zły numer tłumaczenia!"; return;}
  QGsReadBibleTextItem *pGsReadBibleTextItem = this->_QListItemsTranslates[i];
  if(pGsReadBibleTextItem) NameTranslate = pGsReadBibleTextItem->NameTranslate;
}
/****************************************************************************
 *                        Klasalasa QGsTreeWidgetItem                       *
 ****************************************************************************/
QGsTreeWidgetItem::QGsTreeWidgetItem(int type) : QTreeWidgetItem(type)
/**
    OPIS METOD(FUNKCJI):
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
QGsTreeWidgetItem::QGsTreeWidgetItem(QTreeWidget *parent, int type) : QTreeWidgetItem(parent, type)
/**
    OPIS METOD(FUNKCJI):
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
QGsTreeWidgetItem::QGsTreeWidgetItem(QGsTreeWidgetItem *parent, int type) : QTreeWidgetItem(parent, type)
/**
    OPIS METOD(FUNKCJI):
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
QGsTreeWidgetItem::~QGsTreeWidgetItem()
/**
    OPIS METOD(FUNKCJI):
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
/****************************************************************************
 *                        Klasalasa QGsTreeBibleClass                       *
 ****************************************************************************/
QGsTreeBibleClass::QGsTreeBibleClass(QWidget *parent) : QTreeWidget(parent)
/**
   OPIS METOD(FUNKCJI): Konstruktor
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  unsigned char uiLicz=0;	//Licznik ksiąg
  const QStringList QNameHeader = QStringList() << "Nazwa księgi" << "Skrót księgi" << "Ilość rozdziałów";
  QString qstrSetFont;

  #if defined(Q_OS_MACOS)
    qstrSetFont = "Arial";

  #elif defined(Q_OS_LINUX)
    qstrSetFont = "DejaVu";

  #elif defined(Q_OS_WINDOWS)
    qstrSetFont = "Arial";

  #else
  #endif

  QHeaderView *pHeader = this->header();
  //pHeader->setMinimumHeight(32); pHeader->setMaximumHeight(32);

  this->setContextMenuPolicy(Qt::CustomContextMenu);//Podpięcie menu kontekstowego do objektu, klasy GsTreeBibleClass
  connect(this, SIGNAL(customContextMenuRequested(QPoint)), this,
    SLOT(_QGsTrViewCustomCMenuReq(QPoint)));

  connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this,
          SLOT(_QGsTreeDblClick(QTreeWidgetItem*, int)));  //Podwójne kliknięcie na pozycje księgi, w drzewie

  QFont fontTree(qstrSetFont, 10, QFont::Bold), fontThis(qstrSetFont, 10, QFont::Normal), fontBooks(qstrSetFont, 10, QFont::Normal),
        fontHeader(qstrSetFont, 10, QFont::Bold);

  QBrush brushGroups(Qt::blue), brushRoot(Qt::red), brushHeader(Qt::green);
  pHeader->setFont(fontHeader);
  //this->setMaximumWidth(400);
  this->setHeaderLabels(QNameHeader);
  this->setColumnWidth(enHeaderFullName, 180); // ustawiam rozmiar pierwszej kolumny
  this->setFont(fontThis);

  QGsTreeWidgetItem *pNodeMainRoot = new QGsTreeWidgetItem(this);
  pNodeMainRoot->setText(enHeaderFullName, "Księgi Biblijne");
  pNodeMainRoot->setFont(enHeaderFullName, fontTree);
  pNodeMainRoot->setForeground(enHeaderFullName, brushRoot);
  pNodeMainRoot->setIcon(enHeaderFullName, QIcon(":/TreeBooks/gfx/PismoŚwięte.png"));

  for(int iGroupBooks=0; iGroupBooks<QGsReadBibleTextData::QGsNumberGroups; iGroupBooks++)
    //Dodawanie grup ksiąg do korzenia
  {
    QGsTreeWidgetItem *pGroupBook = new QGsTreeWidgetItem(pNodeMainRoot);
    pGroupBook->setText(enHeaderFullName, QGsReadBibleTextData::QGsNamesTableNameGroupBook[iGroupBooks]);
    pGroupBook->setFont(enHeaderFullName, fontTree);
    pGroupBook->setForeground(enHeaderFullName, brushGroups);
    pGroupBook->setIcon(enHeaderFullName, QIcon(":/TreeBooks/gfx/GrupaKsiąg.png"));

    for(int iBooks=0; iBooks<QGsReadBibleTextData::QGsTableNameGroupBook[iGroupBooks]; iBooks++)
      //Dodawanie poszczególnych ksiąg do grup
    {
      QGsTreeWidgetItem *pBooks = new QGsTreeWidgetItem(pGroupBook);
      pBooks->setText(enHeaderFullName, QGsReadBibleTextData::QGsInfoAllBooks[uiLicz].FullNameBook); //Nazwa księgi
      pBooks->setFont(enHeaderFullName, fontBooks);
      pBooks->setText(enHeaderShortName, QGsReadBibleTextData::QGsInfoAllBooks[uiLicz].ShortNameBook); //Skrót nazwy księgi
      pBooks->setText(enHeaderCountChapt, QString("%1").arg(QGsReadBibleTextData::QGsInfoAllBooks[uiLicz].ucCountChapt)); //Liczba rozdziałów
      pBooks->setIcon(enHeaderFullName, QIcon(":/TreeBooks/gfx/Księga.png"));
      pBooks->ucIndexBook = uiLicz;
      pBooks->ucCountChapt = QGsReadBibleTextData::QGsInfoAllBooks[uiLicz].ucCountChapt; //Ilość rozdziałów
      uiLicz++;	//Licznik ksiąg
    }
  }
  QGsReadBibleTextData::pGsTreeBibleClass = this; //Wswkaźnik na drzewo ksiąg
  //--- Rozwinięcie całej listy
  this->expandAll();
  //--- Drag and Drop
  this->setDragEnabled(true);
  this->setDragDropMode(QAbstractItemView::DragOnly);
}
//---------------------------------------------------------------------------
QGsTreeBibleClass::~QGsTreeBibleClass()
/**
   OPIS METOD(FUNKCJI): Destruktor
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
void QGsTreeBibleClass::_QGsTreeDblClick(QTreeWidgetItem* _MyItem, int _column)
/**
   OPIS METOD(FUNKCJI): Podwójne kliknięcie na gałąź drzewa ksiąg biblijnych
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QGsTreeBibleClass *pTree = qobject_cast<QGsTreeBibleClass *>(QObject::sender());
  if(!pTree) return;
  //---
  //Jeśli brak tłumaczeń to wyjdź
  if(QGsReadBibleTextData::pQGsReadBibleTextClass->_QListItemsTranslates.count()==0) return;

  if(_MyItem->childCount() == 0) //Brak potomków, więc nazwa księgi
  {
    QGsTreeWidgetItem *pQGsTreeWidgetItem = dynamic_cast<QGsTreeWidgetItem *>(_MyItem);
    if(!pQGsTreeWidgetItem) return;
    //---Dodanie nowej zakładki i wczytanie pierwszego rozdziału z wybranej księgi
    QGsReadBibleTextData::QOpenSelectBookAndChapter(pQGsTreeWidgetItem->ucIndexBook+1, 1);
  }
}
//---------------------------------------------------------------------------
void QGsTreeBibleClass::_QGsTrViewCustomCMenuReq(const QPoint &pos)
/**
   OPIS METOD(FUNKCJI): Obsługa podręcznego meu
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QGsTreeBibleClass *pTree = qobject_cast<QGsTreeBibleClass *>(QObject::sender());
  if(!pTree) return;
  //---
  //Jeśli brak tłumaczeń to wyjdź
  if(QGsReadBibleTextData::pQGsReadBibleTextClass->_QListItemsTranslates.count()==0) return;

  QGsTreeWidgetItem *pQGsTreeWidgetItem = dynamic_cast<QGsTreeWidgetItem *>(pTree->currentItem());
  if(!pQGsTreeWidgetItem) return;
  //---
  QPoint globalPos = this->mapToGlobal(pos);
  QMenu myMenu;

  QIcon iconOpenChapter;
  iconOpenChapter.addFile(":/TreeBooks/gfx/MenuRozdział.png", QSize(), QIcon::Normal, QIcon::Off);

  for(int iLiczChapt=0; iLiczChapt<pQGsTreeWidgetItem->ucCountChapt; iLiczChapt++)
  {
    QAction* menuAction = myMenu.addAction(iconOpenChapter, QString("%1 rozdział").arg(iLiczChapt +1));
    menuAction->setData(iLiczChapt);
  }
  //Wybrana pozycja z podręcznego menu
  QAction* selectedItem = myMenu.exec(globalPos);

  //---Dodanie nowej zakładki
  QGsTabSheetBookClass *pQGsTabSheetBookClass=nullptr;
  pQGsTabSheetBookClass = new QGsTabSheetBookClass(nullptr, pQGsTreeWidgetItem->ucIndexBook);
  //Uaktualnienie w klasie QGsTabSheetBookClass, pola aktualnego rozdziału
  pQGsTabSheetBookClass->_ShucIndexChapt = selectedItem->data().toInt();
  //Uaktualnienie listy wyboru rozdziałów
  pQGsTabSheetBookClass->_pCBoxAllChapters->setCurrentIndex(pQGsTabSheetBookClass->_ShucIndexChapt);
  //Dodanie zakładki
  QGsReadBibleTextData::pQGsPageControl->addTab(pQGsTabSheetBookClass, iconOpenChapter, pQGsTreeWidgetItem->text(0));
  QGsReadBibleTextData::pQGsPageControl->setCurrentWidget(pQGsTabSheetBookClass); //Nowo utworzona zakładka, jest aktualną
  //Wczytanie i wyświetlenie wybranej księgi i wybranego rozdziału
  QGsReadBibleTextData::pQGsReadBibleTextClass->_QGetAllTranslatesChapter(pQGsTreeWidgetItem->ucIndexBook, pQGsTabSheetBookClass->_ShucIndexChapt);
  QGsReadBibleTextData::pQGsReadBibleTextClass->QDisplayAllTextInHTML(pQGsTabSheetBookClass->_pQTextEdit);
  #if defined(_DEBUGINFO_)
    qDebug() << "pQGsTabSheetBookClass->_ShucIndexChapt: " << pQGsTabSheetBookClass->_ShucIndexChapt;
  #endif
  pQGsTabSheetBookClass->_pQProgressBarChapt->setValue(pQGsTabSheetBookClass->_ShucIndexChapt); //Wskaźnik księgi
}
/****************************************************************************
 *            Całkowicie statyczna klasalasa QGsReadBibleTextData            *
 ****************************************************************************/
//Rozszerzenie plików
const QString QGsReadBibleTextData::QGsExtendFileTranslateFull = "*.pltmb", //Rozszerzenie właściwego pliku z tłumaczeniem biblijnym JAKO WZORZEC!!!
QGsReadBibleTextData::QGsExtendFileTranslateGrecOrg = "*.grtmb",//Stałą z rozszerzeniem pliku z tłumaczeniem oryginalnym, greckim JAKO WZORZEC!!!
QGsReadBibleTextData::QGsExtendFileTranslateHbrOrg = "*.hbtmb",//Stałą z rozszerzeniem pliku z tłumaczeniem oryginalnym, hebrajskim JAKO WZORZEC!!!
QGsReadBibleTextData::QGsExtendFileTranslateAll = "*tmb",//Stałą z końcówką (bez dwuch pierwszych liter) rozszerzenia pliku z KAŻDYM tłumaczeniem JAKO WZORZEC!!!
QGsReadBibleTextData::QGsExtendNoAsteriskFileTranslateFull = "pltmb", //Rozszerzenie właściwego pliku z tłumaczeniem biblijnym BEZ WZORCA!!!
QGsReadBibleTextData::QGsExtendNoAsteriskFileTranslateGrecOrg = "grtmb",//Stałą z rozszerzeniem pliku z tłumaczeniem oryginalnym, greckim BEZ WZORCA!!!
QGsReadBibleTextData::QGsExtendNoAsteriskFileTranslateHbrOrg = "hbtmb",//Stałą z rozszerzeniem pliku z tłumaczeniem oryginalnym, hebrajskim BEZ WZORCA!!!
QGsReadBibleTextData::QGsExtendNoAsteriskInfoTranslate = "mbin";	//Rozszerzenie pliku z informacją o danym tłumaczeniu BEZ WZORCA!!!
//--- Domyślne zawartosci nagłówków kodu html, dla wyświetlania tekstów wersetów w głównym oknie, oknie wyszukiwań, oraz oknie wyboru wersetu
QString QGsReadBibleTextData::QGsHTMLHeaderText = ""; //Nagłówek wyświetla w formie html, głównego tekstu

QGsReadBibleTextClass *QGsReadBibleTextData::pQGsReadBibleTextClass = nullptr;	//Wskaźnik na główną klasę
QGsMainTabWidgetClass *QGsReadBibleTextData::pQGsPageControl = nullptr; //Wskaźnik na objekt, klasy TPageControl, na którym będą umieszczane zakładki
QGsTreeBibleClass *QGsReadBibleTextData::pGsTreeBibleClass = nullptr; //Wskaźnik na drzewo ksiąg
//Tablica struktur opisująca parametry ksiąg biblijnych, potrzebna przy tworzeniu drzewa struktury bibli
const QInfoAllBooks QGsReadBibleTextData::QGsInfoAllBooks[QGsReadBibleTextData::QGsNumberBooks] =
{
  //--- Stary Testament
  QInfoAllBooks(1,	"1 Mojżeszowa", 						    "1Moj", 	50),
  QInfoAllBooks(2, "2 Mojżeszowa", 							  "2Moj", 	40), //1
  QInfoAllBooks(3,	"3 Mojżeszowa", 							  "3Moj", 	27), //2
  QInfoAllBooks(4,	"4 Księga Mojżeszowa", 		 	 	  "4Moj", 	 36), //3
  QInfoAllBooks(5,	"5 Księga Mojżeszowa",     	 	  "5Moj",   34), //4
  QInfoAllBooks(6,	"Księga Jozuego",          			"Joz",    24), //5
  QInfoAllBooks(7,	"Księga Sędziów",          			"Sędź",   21), //6
  QInfoAllBooks(8,	"Księga Rut",              			"Rut",    4),  //7
  QInfoAllBooks(9,	"1 Księga Samuela",        			"1Sam",   31), //8
  QInfoAllBooks(10,	"2 Księga Samuela",        			"2Sam",   24), //9
  QInfoAllBooks(11,	"1 Księga Królewska",        		"1Król",  22), //10
  QInfoAllBooks(12,	"2 Księga Królewska",        		"2Król",  25), //11
  QInfoAllBooks(13,	"1 Księga Kronik",           		"1Kron",    29), //12
  QInfoAllBooks(14,	"2 Księga Kronik",           		"2Kron",    36), //13
  QInfoAllBooks(15,	"Księga Ezdrasza",           		"Ezdr",   10), //14
  QInfoAllBooks(16,	"Księga Nechemiasza",        		"Nech",   13), //15
  QInfoAllBooks(17,	"Księga Estery",             		"Est",    10), //16
  QInfoAllBooks(18,	"Księga Joba",               		"Job",    42), //17
  QInfoAllBooks(19,	"Księga Psalmów",            		"Ps",     150),//18
  QInfoAllBooks(20,	"Przypowieści Salomona",     		"Przyp",  31), //19
  QInfoAllBooks(21,	"Księga Kaznodziei Salomona",		"Kazn",   12), //20
  QInfoAllBooks(22,	"Pieśni nad Pieśniami",      		"PnP",    8),  //21
  QInfoAllBooks(23,	"Księga Izajasza",           		"Iz",     66), //22
  QInfoAllBooks(24,	"Księga Jeremiasza",         		"Jer",    52), //23
  QInfoAllBooks(25,	"Treny",                     		"Tren",   5),  //24
  QInfoAllBooks(26,	"Księga Ezechiela",          		"Ez",     48), //25
  QInfoAllBooks(27,	"Księga Daniela",            		"Dan",    14), //26
  QInfoAllBooks(28,	"Księga Ozeasza",            		"Oz",     14), //27
  QInfoAllBooks(29,	"Księga Joela",              		"Jo",     3),  //28
  QInfoAllBooks(30,	"Księga Amosa",              		"Am",     9),  //29
  QInfoAllBooks(31,	"Księga Abdiasza",           		"Abd",    1),  //30
  QInfoAllBooks(32,	"Księga Jonasza",            		"Jon",    4),  //31
  QInfoAllBooks(33,	"Księga Micheasza",          		"Mich",   7),  //32
  QInfoAllBooks(34,	"Księga Nahuma",             		"Nah",    3),  //33
  QInfoAllBooks(35,	"Księga Habakuka",           		"Hab",    3),  //34
  QInfoAllBooks(36,	"Księga Sofoniasza",         		"Sof",    3),  //35
  QInfoAllBooks(37,	"Księga Aggeusza",           		"Agg",    2),  //36
  QInfoAllBooks(38,	"Księga Zachariasza",        		"Zach",   14), //37
  QInfoAllBooks(39,	"Księga Malachiasza",        		"Mal",    3),  //38
  //--- Nowy Testament
  QInfoAllBooks(40,	"Ewangelia Mateusza",    		 		"Mt",     28), //39
  QInfoAllBooks(41,	"Ewangelia Marka",           		"Mk",     16), //40
  QInfoAllBooks(42,	"Ewangelia Łukasza",         		"Łk",     24), //41
  QInfoAllBooks(43,	"Ewangelia Jana",            		"Jan",    21), //42
  QInfoAllBooks(44,	"Dzieje Apostolskie",        		"DzAp",   28), //43
  QInfoAllBooks(45,	"List Pawła do Rzymian",     		"Rzym",   16), //44
  QInfoAllBooks(46,	"1 List Pawła do Koryntian", 		"1Kor",   16), //45
  QInfoAllBooks(47,	"2 List Pawła do Koryntian", 		"2Kor",   13), //46
  QInfoAllBooks(48,	"List Pawła do Galacjan",    		"Gal",    6),  //47
  QInfoAllBooks(49,	"List Pawła do Efezjan",     		"Efez",   6),  //48
  QInfoAllBooks(50,	"List Pawła do Filipian",    		"Filip",  4),  //49
  QInfoAllBooks(51,	"List Pawła do Kolosan",     		"Kol",    4),  //50
  QInfoAllBooks(52,	"1 List Pawła do Tesaloniczan",	"1Tes",   5),  //51
  QInfoAllBooks(53,	"2 List Pawła do Tesaloniczan",	"2Tes",   3),  //52
  QInfoAllBooks(54,	"1 List Pawła do Tymoteusza",  	"1Tym",   6),  //53
  QInfoAllBooks(55,	"2 List Pawła do Tymoteusza",  	"2Tym",   4),  //54
  QInfoAllBooks(56,	"List Pawła do Tytusa",         "Tyt",    3),  //55
  QInfoAllBooks(57,	"List Pawła do Filemona",       "Filem",  1),  //56
  QInfoAllBooks(58,	"List do Hebrajczyków",         "Hbr",    13), //57
  QInfoAllBooks(59,	"List Jakuba",                  "Jak",    5),  //58
  QInfoAllBooks(60,	"1 List Piotra",                "1Pt",    5),  //59
  QInfoAllBooks(61,	"2 List Piotra",                "2Pt",    3),  //60
  QInfoAllBooks(62,	"1 List Jana",                  "1Jan",   5),  //61
  QInfoAllBooks(63,	"2 List Jana",                  "2Jan",   1),  //62
  QInfoAllBooks(64,	"3 List Jana",                  "3Jan",   1),  //63
  QInfoAllBooks(65,	"List Judy",                    "Jud",    1),  //64
  QInfoAllBooks(66,	"Objawienie Jana",              "Obj",    22), //65
  //--- Apokryfy
  QInfoAllBooks(67,	"Księga Tobiasza",              "Tob",    14), //66
  QInfoAllBooks(68,	"Księga Judyty",                "Judyt",  16), //67
  QInfoAllBooks(69,	"Księga I Machabejska",         "1Mach",  16), //68
  QInfoAllBooks(70,	"Księga II Machabejska",        "2Mach",  15), //69
  QInfoAllBooks(71,	"Księga Mądrości",              "Mądr",   19), //70
  QInfoAllBooks(72,	"Księga Syracha",               "Syr",    51), //71
  QInfoAllBooks(73,	"Księga Barucha",               "Bar",    6)   //72
};
//Tablica struktur PairsGroupBooks, danych dla grup ksiąg biblijnych, dla funkcji wyszukiwania
const QPairsGroupBooks QGsReadBibleTextData::QGsPairsGroupBible[QGsReadBibleTextData::QGsNumberAllGroups] =
{
  _QPairsGroupBooks(0, 72),    //Wszystkie księgi wraz z apokryfami ->_PairsGroupBooks(const char ucStartRange, ucStopRange);
  _QPairsGroupBooks(0, 65),    //Wszystkie księgi, bez apokryfów
  _QPairsGroupBooks(0, 38),    //Księgi Starego Testamentu
  _QPairsGroupBooks(39, 65),   //Księgi Nowego Testamentu
  _QPairsGroupBooks(66, 72),   //Księgi apokryficzne
  _QPairsGroupBooks(-1, -1),   //Własny zakres
  _QPairsGroupBooks(-1, -1)    //Pojedyńcza księga
};
const QString QGsReadBibleTextData::QGsNameAllRanges[en_GrSearch_Count] =
  {"Całe Pismo Święte", "Protestancki kanon Pisma Świętego", "Stary Testament", "Nowy Testament", "Apokryfy", "Własny zakres", "Pojedyńcza księga"};
const unsigned char QGsReadBibleTextData::QGsTableNameGroupBook[QGsReadBibleTextData::QGsNumberGroups] = {39, 27, 7}; //Ilość ksiąg w poszczególnych grupack bibli
const QString QGsReadBibleTextData::QGsNamesTableNameGroupBook[QGsReadBibleTextData::QGsNumberGroups] = {"Stary Testament", "Nowy Testament", "Księgi Apokryficzne"}; //Nazwy ksiąg w poszczególnych grupack bibli
//---------------------------------------------------------------------------
//const unsigned char QGsReadBibleTextData::QGsTableNameGroupBook[QGsReadBibleTextData::QGsNumberGroups] = {39, 27, 7}; //Ilość ksiąg w poszczególnych grupack bibli
//const QString QGsReadBibleTextData::QGsNamesTableNameGroupBook[QGsReadBibleTextData::QGsNumberGroups] = {"Stary Testament", "Nowy Testament", "Księgi Apokryficzne"}; //Nazwy ksiąg w poszczególnych grupack bibli
//---------------------------------------------------------------------------
void QGsReadBibleTextData::QInitMyBible(QGsMainTabWidgetClass *pPageControlBibleText)
/**
   OPIS METOD(FUNKCJI): Inicjalizacja głównej klasy, metoda wywoływana w głównym oknie
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QGsReadBibleTextData::pQGsPageControl = pPageControlBibleText; //Wskaźnik na objekt, klasy TPageControl, na którym będą umieszczane zakładki
  QGsReadBibleTextData::QSetupVariables(); //Musi być po przypisaniu wskaźnika QGSTabWidget do statycznego pola klasy QGsReadBibleTextData
  QGsReadBibleTextData::pQGsReadBibleTextClass = new QGsReadBibleTextClass(GlobalVar::Global_GetDirData); //Wskaźnik na główną klasę

  //pPageControlBibleText->setStyleSheet("QTabBar::tab:selected {background-color: #DDAA00;}");
}
//---------------------------------------------------------------------------
void QGsReadBibleTextData::QSetupVariables()
/**
  OPIS METOD(FUNKCJI): Ustawienie zmiennych dla klasy
  OPIS ARGUMENTÓW:
  OPIS ZMIENNYCH:
  OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QRgb iRGBTemp;
  QColor colorTemp;
  QString BackgroundColorFullTranslate, ColorNameFullTranslates,
          ColorAdressFullTranslates, ColorTextOryginalTranslates,
          ColorAdressOryginalVers, ColorNameOryginaltranslates;
  //Odczyt głównych kolorów tekstu biblijunego
  GlobalVar::Global_ConfigFile->beginGroup(GlobalVar::GlobalIni_ColorsSection_Main);
    //Kolor podkładu pod wyswietlany tekst
    iRGBTemp = (QRgb)GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_ColorBackGroundMainText, (QRgb)4284153797).toInt();
    colorTemp.setRgb(iRGBTemp);
    BackgroundColorFullTranslate = colorTemp.name();
    //Kolor nazwy dla pełnego tłumaczenia
    iRGBTemp = (QRgb)GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_ColorFontNameFullTranslate, (QRgb)4294901760).toInt();
    colorTemp.setRgb(iRGBTemp);
    ColorNameFullTranslates = colorTemp.name();
    //Kolor czcionki adresu pełnych tłumaczeń
    iRGBTemp = (QRgb)GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_ColorAdressFulltranslate, (QRgb)4294901760).toInt();
    colorTemp.setRgb(iRGBTemp);
    ColorAdressFullTranslates = colorTemp.name();
    //Kolor tekstu dla częściowych, oryginalnych tłumaczeń
    iRGBTemp = (QRgb)GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_ColorTextOryginalTr, (QRgb)4294901760).toInt();
    colorTemp.setRgb(iRGBTemp);
    ColorTextOryginalTranslates = colorTemp.name();
    //Kolor nazwy częściowych, oryginalnych tłumaczeń
    iRGBTemp = (QRgb)GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_ColorNameOryginalTr, (QRgb)4294901760).toInt();
    colorTemp.setRgb(iRGBTemp);
    ColorNameOryginaltranslates = colorTemp.name();
    //Kolor adresu oryginalnego wersetu
    iRGBTemp = (QRgb)GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_ColorAdressOryginalTr, (QRgb)4294901760).toInt();
    colorTemp.setRgb(iRGBTemp);
    ColorAdressOryginalVers = colorTemp.name();
  GlobalVar::Global_ConfigFile->endGroup();

  QGsReadBibleTextData::QGsHTMLHeaderText = QString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n") +
      "<html><head>\n" +
      "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n" +
      "<title>Wybrany rozdział, dla dostępnych tłumaczeń</title>\n" +
      "<style type=\"text/css\">\n" +
      //Styl adresu pełnego tłumaczenia
      ".styleFullColorAdressTranslates {color:" + ColorAdressFullTranslates + "; font-size:14pt;font-family:Times New Roman;}\n" +
      //Styl tekstu dla pełnych tłumaczeń
      ".styleFullText {color: #000000;font-size:16pt;font-family:Times New Roman;}\n" +
      //Styl nazwy pełnego tłumaczenia
      ".styleFullTranslates {color:" +  ColorNameFullTranslates + ";font-size:12pt;font-family:Times New Roman;}\n" +
      //Styl braku tłumaczenia
      ".styleNoTranslate {color: #FF0000;font-size:16pt;font-family:Times New Roman;}\n" +
      //Styl dla tekstu dla oryginalnych tłumaczeń
      ".styleOrygin {color:" + ColorTextOryginalTranslates + ";font-size:16pt;font-family:Times New Roman;}\n" +
      //Styl dla adresu oryginalnego tłumaczenia
      ".styleAdressVersOryg {color:" + ColorAdressOryginalVers + "; font-size:14pt;font-family:Times New Roman;}\n" +
      //Styl nazwy oryginalnego tłumaczenia
      ".styleNameVersOryg {color:" + ColorNameOryginaltranslates + ";font-size:12pt;font-family:Times New Roman;}\n"

      "body {background-color:" + BackgroundColorFullTranslate + ";font-size:14pt;font-family:Times New Roman;}\n" +
      "</style></head><body>\n";

  if(!QGsReadBibleTextData::pQGsPageControl) return; //Objekt klasy QGSTabWidget został zainicjowany
  if(QGsReadBibleTextData::pQGsPageControl->count() > 0) //Istnieje zakładka z tekstem
  {
    QGsTabSheetBookClass *pQGsTabSheetBookClass = static_cast<QGsTabSheetBookClass *>(QGsReadBibleTextData::pQGsPageControl->currentWidget());
    if(pQGsTabSheetBookClass)
    {
      QGsReadBibleTextData::pQGsReadBibleTextClass->QDisplayAllTextInHTML(pQGsTabSheetBookClass->_pQTextEdit);
    }
  }
}
//---------------------------------------------------------------------------
void QGsReadBibleTextData::QCloseMyBible()
/**
   OPIS METOD(FUNKCJI): Zzamknięcie wszystkich zasobów. Metoda wywoływana w głównym oknie
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if(QGsReadBibleTextData::pQGsReadBibleTextClass) delete QGsReadBibleTextData::pQGsReadBibleTextClass;
  QGsReadBibleTextData::pQGsReadBibleTextClass = nullptr;
}
//---------------------------------------------------------------------------
void QGsReadBibleTextData::QCreateTreeBooks(QWidget *pParentWidget, QLayout *pQLayout)
/**
   OPIS METOD(FUNKCJI): Stworzenie drzewa ksiąg biblijnych i dodanie ich do okna
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QGsTreeBibleClass *pQGsTreeBibleClass = new QGsTreeBibleClass(pParentWidget); //Wywołanie konstruktora własnej klasy potomnej Z QTreeWidget
  if(pQGsTreeBibleClass)
  {
    pQLayout->addWidget(pQGsTreeBibleClass); //Dodanie do okna
  }
}
//---------------------------------------------------------------------------
void QGsReadBibleTextData::QOpenSelectBookAndChapter(const int _iBook, const int _iChapt)
/**
   OPIS METOD(FUNKCJI): Otwarcie zakładki i wczytanie konkretnej księgi i rozdziału.
                        Metoda wywoływana w QGsTreeBibleClass::_QGsTreeDblClick()
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QGsTreeWidgetItem *pQGsTreeWidgetItem = dynamic_cast<QGsTreeWidgetItem *>(QGsReadBibleTextData::pGsTreeBibleClass->currentItem());
  //Tworzenie ikony zakładki
  QIcon iconOpenChapter;
  iconOpenChapter.addFile(":/TreeBooks/gfx/MenuRozdział.png", QSize(), QIcon::Normal, QIcon::Off);
  //---Dodanie nowej zakładki
  QGsTabSheetBookClass *pQGsTabSheetBookClass=nullptr;
  pQGsTabSheetBookClass = new QGsTabSheetBookClass(nullptr, pQGsTreeWidgetItem->ucIndexBook);
  pQGsTabSheetBookClass->_ShucIndexChapt = 0; //Numer rozdziału
  QGsReadBibleTextData::pQGsPageControl->addTab(pQGsTabSheetBookClass, iconOpenChapter, pQGsTreeWidgetItem->text(0));
  QGsReadBibleTextData::pQGsPageControl->setCurrentWidget(pQGsTabSheetBookClass); //Nowo utworzona zakładka, jest aktualną

  QGsReadBibleTextData::pQGsReadBibleTextClass->_QGetAllTranslatesChapter(_iBook-1, _iChapt-1);
  QGsReadBibleTextData::pQGsReadBibleTextClass->QDisplayAllTextInHTML(pQGsTabSheetBookClass->_pQTextEdit);
}
//---------------------------------------------------------------------------
unsigned char QGsReadBibleTextData::QCountTranslates()
/**
   OPIS METOD(FUNKCJI): Metoda zwraca ilość tłumaczeń
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  return QGsReadBibleTextData::pQGsReadBibleTextClass->QGetCountTranslates();
}
//---------------------------------------------------------------------------
QGsReadBibleTextItem *QGsReadBibleTextData::QGetTranslate(const unsigned char cucNumberTrans)
/**
   OPIS METOD(FUNKCJI): Metoda zwraca wskaźnik na klasę wybranego tłumaczenia
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  return QGsReadBibleTextData::pQGsReadBibleTextClass->QGetTranslateClass(cucNumberTrans);
}
//---------------------------------------------------------------------------
void QGsReadBibleTextData::QGetInfoNameTranslate(const unsigned char i, QString &NameTranslate)
/**
   OPIS METOD(FUNKCJI): Nazwa wybranego tłumaczenia
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QGsReadBibleTextData::pQGsReadBibleTextClass->_QGetInfoNameTranslate(i, NameTranslate);
}
//---------------------------------------------------------------------------
QStringList &QGsReadBibleTextData::QGetSelectBoksInTranslate(QGsReadBibleTextItem *pQGsReadBibleTextItem, const unsigned char uiIndexBook)
/**
    OPIS METOD(FUNKCJI): Wyodrębnienie konkretnej księgi(sciIndex), z wybranej struktury tłumaczenia (QGetTranslate)
    OPIS ARGUMENTÓW: QGsReadBibleTextItem *pQGsReadBibleTextItem - Wskaźnik na strukturę QGsReadBibleTextItem, opisującą wybrane tłumaczenie
                     const signed char scIndexBook - Numer księgi
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{
  return pQGsReadBibleTextItem->_QListAllListBooks[uiIndexBook]; //Wyciągnięcie księgi z listy ksiąg, dla konkretnego tłumaczenia
}
//---------------------------------------------------------------------------
QString QGsReadBibleTextData::QConvertVerses(const QString &qstrVerse)
/**
    OPIS METOD(FUNKCJI): Konwersja adresu wybranego wersetu, na normalna formę
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QString qstrRes;

  unsigned char ucBook = qstrVerse.midRef(0, 3).toInt() - 1,
                ucChapt = qstrVerse.midRef(3, 3).toInt(),
                ucVers = qstrVerse.midRef(6, 3).toInt();

  qstrRes = QString("%1 %2:%3 %4").arg(QGsReadBibleTextData::QGsInfoAllBooks[ucBook].ShortNameBook).arg(ucChapt).arg(ucVers).arg(qstrVerse.midRef(10));
  return qstrRes;
}
/****************************************************************************
 *                    KLASA MyObjectVers                                    *
 ****************************************************************************/
/*
QMyObjectVers::QMyObjectVers(const QString &HeadVers)
{
  this->ucBook = static_cast<unsigned char>(HeadVers.midRef(0, 3).toInt() - 1);
  this->ucChapt = static_cast<unsigned char>(HeadVers.midRef(3, 3).toInt());
  this->ucVers = static_cast<unsigned char>(HeadVers.midRef(6, 3).toInt());

  this->BookChaptVers = QString("%1 %2:%3").arg(QGsReadBibleTextData::QGsInfoAllBooks[this->ucBook].ShortNameBook).arg(this->ucChapt).arg(this->ucVers);
}
//---------------------------------------------------------------------------
QMyObjectVers::~QMyObjectVers()
{

}
*/
/****************************************************************************
 *                     Klasa QGsReadBibleTextItem                           *
 ****************************************************************************/
QGsReadBibleTextItem::QGsReadBibleTextItem(const QString _PathTransl, EnTypeTranslate IdenTypeTranslate, const unsigned char cucIndex)
  : IsActiveTranslate(true),	//Czy tłumaczenie jest aktywne, czyli czy jest wyświetlane
    enTypeTranslate(IdenTypeTranslate)
  /**
        OPIS METOD(FUNKCJI):
        OPIS ARGUMENTÓW:
        OPIS ZMIENNYCH:
        OPIS WYNIKU METODY(FUNKCJI):
     */
{
  unsigned char iGetBook=0;
  QStringList _tempStringList;
  bool bOk; //Wynik konwersji do int

  this->ucIndexTranslate = cucIndex; //Indeks tłumaczenia
  bool iResult = LoadFileToStrList(_tempStringList, _PathTransl);

  if(iResult)
  {
    this->NameTranslate = _tempStringList.at(0); //Nazwa tłumaczenia
    //----- Wczytanie poszczególnych ksiąg do poszczególnych string list
    for(int iIndex=1; iIndex<_tempStringList.count(); iIndex++)
    //Przegląd całego tekstu tłumaczenia, w celu wyodrębnienia poszczególnych ksiąg, i umieszczenia ich w odpowiednich string listach
    //Pętla rozpoczyna się od pozycji 1, gdyż pozycja 0, to nazwa tłumaczenia.
    {
      //KSIĘGI LICZONE SĄ OD ZERA!!! Odczytanie numeru księgi
      iGetBook = static_cast<unsigned char>(_tempStringList.at(iIndex).midRef(0, 3).toInt(&bOk)-1); //Odczyt numeru księgi
      if(!bOk) return;
      if(iIndex==1) this->ucStartBook = iGetBook; //Początkowy numer księgi (od jakiej księgi zaczyna się tłumaczenie)
      //Umieszczenie tekstu zależnie od numeru księgi, w odpowiedniej string liście, o indeksie równym numerowi księgi
      this->_QListAllListBooks[iGetBook].append(_tempStringList.at(iIndex));
    }
    this->ucCountBooks = iGetBook - this->ucStartBook + 1; //Ilość ksiąg w tłumaczeniu
  }
  this->uiVersCount = _tempStringList.count();
}
//---------------------------------------------------------------------------
QGsReadBibleTextItem::~QGsReadBibleTextItem()
/**
   OPIS METOD(FUNKCJI):
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
/****************************************************************************
 *                          Klasa GsMainTabWidgetClass                      *
 ****************************************************************************/
QGsMainTabWidgetClass::QGsMainTabWidgetClass(QWidget *parent) : QTabWidget(parent)
/**
 OPIS METOD(FUNKCJI):
 OPIS ARGUMENTÓW:
 OPIS ZMIENNYCH:
 OPIS WYNIKU METODY(FUNKCJI):
*/
{
  this->setAutoFillBackground(true);
  //--- Drag and Drop
  this->setAcceptDrops(true);
}
//---------------------------------------------------------------------------
QGsMainTabWidgetClass::~QGsMainTabWidgetClass()
/**
 OPIS METOD(FUNKCJI):
 OPIS ARGUMENTÓW:
 OPIS ZMIENNYCH:
 OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
void QGsMainTabWidgetClass::dropEvent(QDropEvent* event)
/**
 OPIS METOD(FUNKCJI):
 OPIS ARGUMENTÓW:
 OPIS ZMIENNYCH:
 OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if(event->source()->metaObject()->className() == QString("QGsTreeBibleClass"))
  {
    QGsTreeBibleClass *pQGsTreeBibleClass  = qobject_cast<QGsTreeBibleClass *>(event->source());
    if(pQGsTreeBibleClass)
    {
      QGsTreeWidgetItem *pQGsTreeWidgetItem = dynamic_cast<QGsTreeWidgetItem *>(pQGsTreeBibleClass->currentItem());
      if(pQGsTreeWidgetItem)
      {
        if(pQGsTreeWidgetItem->childCount()==0)
        {
          //qInfo() << pQGsTreeWidgetItem->text(0);
          emit pQGsTreeBibleClass->itemDoubleClicked(pQGsTreeWidgetItem, 0);
        }
      }
    }
  }
}
//---------------------------------------------------------------------------
void QGsMainTabWidgetClass::dragEnterEvent(QDragEnterEvent *event)
/**
 OPIS METOD(FUNKCJI):
 OPIS ARGUMENTÓW:
 OPIS ZMIENNYCH:
 OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if(event->source()->metaObject()->className() == QString("QGsTreeBibleClass"))
  {
    QGsTreeBibleClass *pQGsTreeBibleClass  = qobject_cast<QGsTreeBibleClass *>(event->source());
    if(pQGsTreeBibleClass)
    {
      QGsTreeWidgetItem *pQGsTreeWidgetItem = dynamic_cast<QGsTreeWidgetItem *>(pQGsTreeBibleClass->currentItem());
      if(pQGsTreeWidgetItem)
      {
        if(pQGsTreeWidgetItem->childCount()==0)
        {
          event->acceptProposedAction(); //Akceptacja możliwości upuszczenia pozycji
        }
      }
    }
  }
}
/****************************************************************************
 *                          Klasa GsTabSheetClass                           *
 ****************************************************************************/
enum {enNextChapt=100, enPrevChapt, enNextBook, enPrevBook};

QGsTabSheetBookClass::QGsTabSheetBookClass(QWidget *parent, const unsigned char ucSelectBook) : QWidget(parent), _ShucIndexBook(ucSelectBook)
/**
 OPIS METOD(FUNKCJI):
 OPIS ARGUMENTÓW: QWidget *parent - wskaźnik na przodka i chyba właściciela
                  unsigned char ucSelectBook - wybrana księga
 OPIS ZMIENNYCH:
 OPIS WYNIKU METODY(FUNKCJI):
*/
{
  this->_ShucIndexChapt = 0;
  QString qstrInfo;
  this->_ShucIndexChapt = 0; //Do czasu napisanie wyboru rozdziału z menu podręcznego drzewa ksiąg
  QIcon iconTranslate;
  iconTranslate.addFile(":/SheetText/gfx/PrzekładBiblii.png", QSize(), QIcon::Normal, QIcon::Off);
  //Główny widok dla pionowego ułożenia widgetów
  QVBoxLayout *pMainVLayout = new QVBoxLayout(this);

  pMainVLayout->setContentsMargins(1,1,1,1);
  pMainVLayout->setSpacing(2);
  QHBoxLayout *pTextProgressHLayout = new QHBoxLayout();
  pTextProgressHLayout->setSpacing(2);

  //Główny objekt wyświetlający wybrany tekst
  this->_pQTextEdit = new QTextEdit(this);
  this->_pQTextEdit->setReadOnly(true);
  //this->_pQTextBrowser->setLineWrapMode(QTextEdit::NoWrap);
  //Wskażnik umiejscowienia aktualnego tekstu względem księgi
  this->_pQProgressBarChapt = new QProgressBar(this);
  this->_pQProgressBarChapt->setOrientation(Qt::Vertical);
  this->_pQProgressBarChapt->setMaximumSize(QSize(10, 16777215));
  //this->_pQProgressBarChapt->setStyleSheet("selection-background-color: rgb(255, 0, 0);");

  this->_pTabWidgetTranslates = new QTabWidget(this);
  this->_pTabWidgetTranslates->setMaximumSize(QSize(16777215, 78));
  //this->_pTabWidgetTranslates->setStyleSheet("QTabBar::tab:selected {background-color: #88AA33;}");
  for(int i=0; i<=QGsReadBibleTextData::pQGsReadBibleTextClass->_QListItemsTranslates.count(); i++)
  {
    QWidget *myWidget = new QWidget(this);
    QVBoxLayout *pInfoVLayout = new QVBoxLayout(myWidget);
    pInfoVLayout->setContentsMargins(1,1,1,1);
    //---
    QTextEdit *_pQTextInfo = new QTextEdit(this);
    _pQTextInfo->setReadOnly(true);
    pInfoVLayout->addWidget(_pQTextInfo);

    if(i==0)
    {
      this->_pTabWidgetTranslates->addTab(myWidget, iconTranslate, "Wszystkie tłumaczenia");
      qstrInfo = QString("Wszystkie tłumaczenia");
    }
    else
    {
      QGsReadBibleTextItem *pQGsReadBibleTextItem = QGsReadBibleTextData::pQGsReadBibleTextClass->QGetTranslateClass(i-1); //Wyłuskanie wskaźnika GsReadBibleTextItem konkretnego tłumaczenia, w celu sprawdzenia nazwy tłumaczenia
      this->_pTabWidgetTranslates->addTab(myWidget, iconTranslate, pQGsReadBibleTextItem->NameTranslate);
      qstrInfo = QString("Nazwa tłumaczenia: %1\nIlość wszystkich wersetów: %2").arg(pQGsReadBibleTextItem->NameTranslate).arg(pQGsReadBibleTextItem->uiVersCount);
    }
    _pQTextInfo->setText(qstrInfo);
  }
  QToolBar *_pQToolBar = new QToolBar(this);
  //QHBoxLayout *pToolsQHBoxLayout = new QHBoxLayout();
  //pToolsQHBoxLayout->setContentsMargins(1,1,1,1);
  //pToolsQHBoxLayout->addWidget(_pQToolBar);

  QIcon iconNextChapt, iconPrevChapt, iconNextBook, iconPrevBook, iconSelectChapter;
  iconNextChapt.addFile(":/SheetText/gfx/NastępnyRozdział.png", QSize(), QIcon::Normal, QIcon::Off);
  iconPrevChapt.addFile(":/SheetText/gfx/PoprzedniRozdział.png", QSize(), QIcon::Normal, QIcon::Off);
  iconNextBook.addFile(":/SheetText/gfx/NastępnaKsięga.png", QSize(), QIcon::Normal, QIcon::Off);
  iconPrevBook.addFile(":/SheetText/gfx/PoprzedniaKsięga.png", QSize(), QIcon::Normal, QIcon::Off);
  iconSelectChapter.addFile(":/SheetText/gfx/WybierzRozdział.png", QSize(), QIcon::Normal, QIcon::Off);

  this->pActionNextChapter = new QAction(this);
  this->pActionNextChapter->setIcon(iconNextChapt);
  this->pActionPrevChapter = new QAction(this);
  this->pActionPrevChapter->setIcon(iconPrevChapt);
  this->pActionNextBook = new QAction(this);
  this->pActionNextBook->setIcon(iconNextBook);
  this->pActionPrevBook = new QAction(this);
  this->pActionPrevBook->setIcon(iconPrevBook);

  this->pActionNextChapter->setData(enNextChapt);
  this->pActionPrevChapter->setData(enPrevChapt);
  this->pActionNextBook->setData(enNextBook);
  this->pActionPrevBook->setData(enPrevBook);

  _pQToolBar->addAction(this->pActionNextBook);
  _pQToolBar->addAction(this->pActionNextChapter);
  _pQToolBar->addAction(this->pActionPrevChapter);
  _pQToolBar->addAction(this->pActionPrevBook);

  pMainVLayout->addWidget(_pQToolBar);
  pMainVLayout->addLayout(pTextProgressHLayout);
  pTextProgressHLayout->addWidget(this->_pQTextEdit);
  pTextProgressHLayout->addWidget(this->_pQProgressBarChapt);

  pMainVLayout->addWidget(this->_pTabWidgetTranslates);

  //----- Sygnał wyboru przekładu
  connect(this->_pTabWidgetTranslates, SIGNAL(currentChanged(int)), this, SLOT(_SelectTranslate(int)));
  //----- Sygnały z przycisków ToolBar podpięte do jednego prywatnego slotu
  connect(this->pActionNextChapter, SIGNAL(triggered()), this, SLOT(_NextPrevAll()));
  connect(this->pActionPrevChapter, SIGNAL(triggered()), this, SLOT(_NextPrevAll()));
  connect(this->pActionNextBook, SIGNAL(triggered()), this, SLOT(_NextPrevAll()));
  connect(this->pActionPrevBook, SIGNAL(triggered()), this, SLOT(_NextPrevAll()));
  //Test tymczasowo
  this->_pCBoxAllChapters = new QComboBox();
  for(int i=0; i<QGsReadBibleTextData::QGsInfoAllBooks[ucSelectBook].ucCountChapt; i++)
  {
    this->_pCBoxAllChapters->addItem(iconSelectChapter, QString("Rozdział numer: %1").arg(i+1), i);
  }
  _pQToolBar->addWidget(this->_pCBoxAllChapters);

  connect(this->_pCBoxAllChapters, SIGNAL(activated(int)), this, SLOT(_CBoxSelectIndexChapt(int)));

  this->_UpdateDisplayButtonsAndText(); //Uaktualnienie stanu przycisków przewijania i tytułu zakładki

  this->_pQProgressBarChapt->setMaximum(QGsReadBibleTextData::QGsInfoAllBooks[this->_ShucIndexBook].ucCountChapt - 1);
  this->_pQProgressBarChapt->setValue(0);

  QGsReadBibleTextData::pQGsPageControl->setVisible(true);
  //Procedura wyłuskania wskaźnika na objekt QAction, zamykania aktywnej zakładki
  QWidget *pActiveWindow = QApplication::activeWindow(); //Wyłuskanie wskaźnika na główne okno
  int iSelectAction=0; //Identyfikacja szukanej akcji
  if(pActiveWindow)
  {
    for(int i=0; i<pActiveWindow->children().count(); i++)
    //Liczenie objectów potomnych głównego okna
    {
      QObject *pObject = pActiveWindow->children().at(i); //Wskaźnik typu QObject
      if(pObject->metaObject()->className() == QString("QAction"))
      //Akceptacja objektów tylko typu QAction
      {
        QAction *pAction = dynamic_cast<QAction *>(pObject); //Wskaźnik typu QAction
        if(pAction)
        {
          iSelectAction = pAction->data().toInt();
          switch(iSelectAction)
          {
            case enAction_CloseSheet:
            //Akceptacja tylko objektu typu QAction, z polem danych odpowiadającym objectowi do zamykania aktywnej zakładki
            {
              pAction->setEnabled(true); //Aktywacja objektu, klasy QAction
            }
            break;
            //---
            case enAction_ResizeText:
            //Akceptacja tylko objektu typu QAction, z polem danych odpowiadającym objectowi do zamykania szerokości tekstu biblijnego
            //Schowanie zakładek narzędzi
            {
              pAction->setEnabled(true);  //Aktywacja akcji zmiany obszaru wyświetlania tekstu
              pAction->setChecked(true);  //Schowanie panela panela z narzędziami
              emit pAction->triggered();
            }
            break;
            //---
            case enAction_SaveActiveSheet:
            //Akceptacja tylko objektu typu QAction, z polem danych odpowiadającym objectowi do zapisywania rozdziały w  aktywnej zakładki
            {
              pAction->setEnabled(true);
            }
            break;
            //---
          }
        }
      }
    }
  }

}
//---------------------------------------------------------------------------
QGsTabSheetBookClass::~QGsTabSheetBookClass()
/**
 OPIS METOD(FUNKCJI):
 OPIS ARGUMENTÓW:
 OPIS ZMIENNYCH:
 OPIS WYNIKU METODY(FUNKCJI):
*/
{
}
//---------------------------------------------------------------------------
void QGsTabSheetBookClass::_NextPrevAll()
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
  int typeAction = pAction->data().toInt();

  switch(typeAction)
  {
    case enNextChapt: //Następny rozdział
    {
      if(this->_ShucIndexChapt < QGsReadBibleTextData::QGsInfoAllBooks[this->_ShucIndexBook].ucCountChapt - 1)
      {
        this->_ShucIndexChapt++;
        this->_pCBoxAllChapters->setCurrentIndex(this->_ShucIndexChapt);
        emit this->_pCBoxAllChapters->activated(this->_ShucIndexChapt);
      }
    }
    break;
    //---
    case enPrevChapt: //Poprzedni rozdział
    {
      if(this->_ShucIndexChapt > 0)
      {
        this->_ShucIndexChapt--;
        this->_pCBoxAllChapters->setCurrentIndex(this->_ShucIndexChapt);
        emit this->_pCBoxAllChapters->activated(this->_ShucIndexChapt);
      }
    }
    break;
    //---
    case enNextBook: //Następna księga
    {
      if(this->_ShucIndexBook < QGsReadBibleTextData::QGsNumberBooks-1)
      {
        this->_ShucIndexBook++;
        //Wskaźnik księgi
        this->_pQProgressBarChapt->setMaximum(QGsReadBibleTextData::QGsInfoAllBooks[this->_ShucIndexBook].ucCountChapt - 1);
        this->_ShucIndexChapt=0;
        this->_pCBoxAllChapters->setCurrentIndex(0);
        emit this->_pCBoxAllChapters->activated(0);
        //Tworzenie listy rozdziałów wybranej księgi, dla objektu, klasy QComboBox
        this->_pCBoxAllChapters->clear();
        for(int i=0; i<QGsReadBibleTextData::QGsInfoAllBooks[this->_ShucIndexBook].ucCountChapt; i++)
        {
          this->_pCBoxAllChapters->addItem(QString("Rozdział numer: %1").arg(i+1), i);
        }
        //Nazwa księgi na zakładce
        int iCurrentIndex = QGsReadBibleTextData::pQGsPageControl->currentIndex();
        QGsReadBibleTextData::pQGsPageControl->setTabText(iCurrentIndex, QGsReadBibleTextData::QGsInfoAllBooks[this->_ShucIndexBook].FullNameBook);
      }
    }
    break;
    //---
    case enPrevBook: //Poprzednia księga
    {
      if(this->_ShucIndexBook > 0)
      {
        this->_ShucIndexBook--;
        //Wskaźnik księgi
        this->_pQProgressBarChapt->setMaximum(QGsReadBibleTextData::QGsInfoAllBooks[this->_ShucIndexBook].ucCountChapt - 1);
        this->_ShucIndexChapt=0;
        this->_pCBoxAllChapters->setCurrentIndex(0);
        emit this->_pCBoxAllChapters->activated(0);
        //Tworzenie listy rozdziałów wybranej księgi, dla objektu, klasy QComboBox
        this->_pCBoxAllChapters->clear();
        for(int i=0; i<QGsReadBibleTextData::QGsInfoAllBooks[this->_ShucIndexBook].ucCountChapt; i++)
        {
          this->_pCBoxAllChapters->addItem(QString("Rozdział numer: %1").arg(i+1), i);
        }
        //Nazwa księgi na zakładce
        int iCurrentIndex = QGsReadBibleTextData::pQGsPageControl->currentIndex();
        QGsReadBibleTextData::pQGsPageControl->setTabText(iCurrentIndex, QGsReadBibleTextData::QGsInfoAllBooks[this->_ShucIndexBook].FullNameBook);
      }
    }
    break;
  }

  this->_UpdateDisplayButtonsAndText(); //Uaktualnienie stanu przycisków przewijania ksiąg i rozdziałów
}
//---------------------------------------------------------------------------
void QGsTabSheetBookClass::_CBoxSelectIndexChapt(int _iSelect)
/**
 OPIS METOD(FUNKCJI):
 OPIS ARGUMENTÓW:
 OPIS ZMIENNYCH:
 OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QComboBox *pComboBox = qobject_cast<QComboBox *>(QObject::sender());
  if(!pComboBox) return;
  //---
  QGsReadBibleTextData::pQGsReadBibleTextClass->_QGetAllTranslatesChapter(this->_ShucIndexBook, _iSelect);
  QGsReadBibleTextData::pQGsReadBibleTextClass->QDisplayAllTextInHTML(this->_pQTextEdit, this->_pTabWidgetTranslates->currentIndex()-1);

  this->_ShucIndexChapt = _iSelect;

  this->_UpdateDisplayButtonsAndText(); //Uaktualnienie stanu przycisków przewijania i tytułu zakładki
}
//---------------------------------------------------------------------------
void QGsTabSheetBookClass::_UpdateDisplayButtonsAndText()
/**
 OPIS METOD(FUNKCJI): Uaktualnienie stanu przycisków przewijania i tytułu zakładki
 OPIS ARGUMENTÓW:
 OPIS ZMIENNYCH:
 OPIS WYNIKU METODY(FUNKCJI):
*/
{
  this->pActionNextChapter->setEnabled(this->_ShucIndexChapt < QGsReadBibleTextData::QGsInfoAllBooks[this->_ShucIndexBook].ucCountChapt - 1);
  this->pActionPrevChapter->setEnabled(this->_ShucIndexChapt > 0);
  this->pActionNextBook->setEnabled(this->_ShucIndexBook < QGsReadBibleTextData::QGsNumberBooks - 1);
  this->pActionPrevBook->setEnabled(this->_ShucIndexBook > 0);

  #if defined(_DEBUGINFO_)
    qDebug() << "this->_ShucIndexChapt: " << this->_ShucIndexChapt;
  #endif

  this->_pQProgressBarChapt->setValue(this->_ShucIndexChapt); //Wskaźnik księgi
}
//---------------------------------------------------------------------------
void QGsTabSheetBookClass::_SelectTranslate(int _iSelectTranslate)

{
  QTabWidget *pQTabWidget = qobject_cast<QTabWidget *>(QObject::sender());
  if(!pQTabWidget) return;
  //---
  #if defined(_DEBUGINFO_)
    qDebug() << "_SelectTranslate _iSelect: " << _iSelectTranslate-1;
  #endif

  QGsReadBibleTextData::pQGsReadBibleTextClass->_QGetAllTranslatesChapter(this->_ShucIndexBook, this->_ShucIndexChapt);
  QGsReadBibleTextData::pQGsReadBibleTextClass->QDisplayAllTextInHTML(this->_pQTextEdit, _iSelectTranslate-1); //Jednak potrzebne 07-03-2021 !!!
}
//---------------------------------------------------------------------------
