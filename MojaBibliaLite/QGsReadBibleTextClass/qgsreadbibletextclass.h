#ifndef QGSREADBIBLETEXTCLASS_H
#define QGSREADBIBLETEXTCLASS_H

#include <QTreeWidget>
#include <QBoxLayout>
//#include <QTextEdit>
#include <QProgressBar>
#include <QAction>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include "QGsComponents/qgseditorclass.h"

const static unsigned int csuiMaxSizeVers=512,//Dodac do wersji windowsowej!!!
                          csuiOffsetSameTextVers = 9;//Od którego znaku zaczyna się tekst wersetu

enum {enHeaderFullName, enHeaderShortName, enHeaderCountChapt, enHederCount}; //Numery kolumn w drzewie ksiąg biblijnych
const unsigned char cucMaxCountTranslates=12; //Maksymalna ilość tłumaczeń
class QGsTreeBibleClass;
class QGsReadBibleTextClass;
class QGsTreeWidgetItem;
class QGsReadBibleTextItem;
class QGsMainTabWidgetClass;
/*============================================================================
 =                          STRUKTURA InfoAllBooks                           =
 ============================================================================*/
typedef struct _QInfoAllBooks
{
 const unsigned char ucIndex;          //Numer księgi
 const QString FullNameBook;     //Pełna nazwa księgi
 const QString ShortNameBook;   //Skrót księgi
 const unsigned char ucCountChapt;     //Ilość rozdziałów
 _QInfoAllBooks(unsigned char _ucIndex, const QString _FullNameBook, const QString _ShortNameBook, unsigned char _ucCountChapt) : ucIndex(_ucIndex),
   FullNameBook(_FullNameBook), ShortNameBook(_ShortNameBook), ucCountChapt(_ucCountChapt)
 /**
   OPIS METOD(FUNKCJI): Konstruktor klasy _InfoAllBooks
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
 */
 {

 };
} QInfoAllBooks, *PQInfoAllBooks;
//Q_DECLARE_METATYPE(PQInfoAllBooks);  //Musi być
/*============================================================================
 =                          STRUKTURA PairsGroupBooks                        =
 ============================================================================*/
//Stałe dla tablicy GsReadBibleTextData::GsPairsGroupBible, grup ksiąg dla wyszukiwania
enum enQPartBooksSearch
{en_GrSearch_FullAll,  //Wszystkie księgi wraz z apokryfami
 en_GrSearch_All,      //Wszystkie księgi, bez apokryfów
 en_GrSearch_Old,      //Księgi Starego Testamentu
 en_GrSearch_New,      //Księgi Nowego Testamentu
 en_GrSearch_Apocr,    //Księgi apokryficzne
 en_UserRange,         //Własny zakres
 en_OneBook,           //Pojedyńcza księga
 en_GrSearch_Count
};
typedef struct _QPairsGroupBooks
{
  const signed char ucStartRange, ucStopRange;
  _QPairsGroupBooks(signed char _ucStartRange, signed char _ucStopRange) : ucStartRange(_ucStartRange), ucStopRange(_ucStopRange)
  /**
      OPIS METOD(FUNKCJI): Konstruktor klasy _PairsGroupBooks
      OPIS ARGUMENTÓW:
      OPIS ZMIENNYCH:
      OPIS WYNIKU METODY(FUNKCJI):
     */
  {
  }
} QPairsGroupBooks, *QPPairsGroupBooks;
/****************************************************************************
 *                        Klasalasa QGsReadBibleTextData                   *
 ****************************************************************************/
class QGsReadBibleTextData
{
  public:
  //Rozszerzenie plików
  const static QString QGsExtendFileTranslateFull, //Rozszerzenie właściwego pliku z tłumaczeniem biblijnym JAKO WZORZEC!!!
  QGsExtendFileTranslateGrecOrg,//Stałą z rozszerzeniem pliku z tłumaczeniem oryginalnym, greckim JAKO WZORZEC!!!
  QGsExtendFileTranslateHbrOrg,//Stałą z rozszerzeniem pliku z tłumaczeniem oryginalnym, hebrajskim JAKO WZORZEC!!!
  QGsExtendFileTranslateAll,//Stałą z końcówką (bez dwuch pierwszych liter) rozszerzenia pliku z KAŻDYM tłumaczeniem JAKO WZORZEC!!!
  QGsExtendNoAsteriskFileTranslateFull, //Rozszerzenie właściwego pliku z tłumaczeniem biblijnym BEZ WZORCA!!!
  QGsExtendNoAsteriskFileTranslateGrecOrg,//Stałą z rozszerzeniem pliku z tłumaczeniem oryginalnym, greckim BEZ WZORCA!!!
  QGsExtendNoAsteriskFileTranslateHbrOrg,//Stałą z rozszerzeniem pliku z tłumaczeniem oryginalnym, hebrajskim BEZ WZORCA!!!
  QGsExtendNoAsteriskInfoTranslate;	//Rozszerzenie pliku z informacją o danym tłumaczeniu BEZ WZORCA!!!
  //---
  static QString QGsHTMLHeaderText;
  static const QString QGsNameAllRanges[en_GrSearch_Count]; //Tablica nazw zakresów wyszukiwania
  static const QPairsGroupBooks QGsPairsGroupBible[en_GrSearch_Count]; //Tablica struktur PairsGroupBooks, danych dla grup ksiąg biblijnych,
  static const unsigned char QGsNumberAllGroups = en_GrSearch_Count,//Ilość grup bibli, do wyszukiwania
                             QGsNumberBooks = 73,	//Maksymalna ilość wszystkich ksiąg
                             QGsNumberGroups = 3,	//Ilość grup w drzewie struktury bibli
                             QGsTableNameGroupBook[QGsReadBibleTextData::QGsNumberGroups]; //Ilość ksiąg w poszczególnych grupach bibli
  //---
  static const QString QGsNamesTableNameGroupBook[QGsReadBibleTextData::QGsNumberGroups]; //Nazwy ksiąg w poszczególnych grupack bibli

  static const QInfoAllBooks QGsInfoAllBooks[QGsReadBibleTextData::QGsNumberBooks];	//Tablica struktur InfoAllBooks, opisująca parametry ksiąg biblijnych
  //---  Wskaźniki na niektóre klasy
  static QGsReadBibleTextClass* pQGsReadBibleTextClass;	//Wskaźnik na główną klasę
  static QGsMainTabWidgetClass *pQGsPageControl; //Wskaźnik na objekt, klasy QGsMainTabWidgetClass, na którym będą umieszczane zakładki
  static QGsTreeBibleClass *pGsTreeBibleClass; //Wskaźnik na drzewo ksiąg
  //---
  static void QCreateTreeBooks(QWidget *pParentWidget, QLayout *pQLayout);
  static void QInitMyBible(QGsMainTabWidgetClass *pPageControlBibleText); //Inicjalizacja głównej klasy
  static void QSetupVariables(); //Ustawienie zmiennych dla klasy
  static void QCloseMyBible(); //zamknięcie wszystkich zasobów
  static unsigned char QCountTranslates();	//Metoda zwraca ilość tłumaczeń
  static void QGetInfoNameTranslate(const unsigned char i, QString &NameTranslate); //Nazwa wybranego tłumaczenia
  static void QOpenSelectBookAndChapter(const int _iBook, const int _iChapt=0); //Otwarcie zakładki i wczytanie konkretnej księgi i rozdziału
  static QGsReadBibleTextItem *QGetTranslate(const unsigned char cucNumberTrans); //Metoda zwraca wskaźnik na klasę wybranego tłumaczenia
  static QStringList &QGetSelectBoksInTranslate(QGsReadBibleTextItem *pQGsReadBibleTextItem, const unsigned char uiIndexBook); //Wyodrębnienie konkretnej księgi(sciIndex), z wybranej struktury tłumaczenia (QGetTranslate)
  static int QCountVersSelectBookChapt(const int iBook, const int iChapt); //Metoda zwraca ilość wersetów dla wybranej księgi rozdziału
  //Metoda zwraca listę wybranego wersetu, dla wszystkich, dostępnych tłumaczeń
  static void QGetSelectVerAllTranslate(const unsigned char cucBook, const unsigned char cucChapt, const unsigned char cucVer, QStringList &qslistVers);

  static QString QConvertVerses(const QString &qstrVerse, bool bFuulVers=true); //Konwersja adresu wybranego wersetu, na normalna formę
};
/****************************************************************************
 *                     Klasa QGsReadBibleTextItem                           *
 ****************************************************************************/
//Typy tłumaczeń (w języku polskim, lub oryginalnym)
enum EnTypeTranslate {enTypeTr_Full=0x10,	//Cały przekład Pisma Świętego
                      enTypeTr_Greek,	//Tekst oryginalny Nowego Testamentu w języku greckim
                      enTypeTr_Hebrew	//Tekst oryginalny Starego Testamentu w języku hebrajskim
                     };
class QGsReadBibleTextItem
{
 friend class QGsReadBibleTextClass;
 friend class QGsTreeBibleClass;
 friend class QGsReadBibleTextData;

 QGsReadBibleTextItem(const QString _PathTransl, EnTypeTranslate IdenTypeTranslate, const unsigned char cucIndex);
 virtual ~QGsReadBibleTextItem();
 //---
 QStringList _QListAllListBooks[QGsReadBibleTextData::QGsNumberBooks];	//Lista wskaźników do wszystkich ksiąg tłumaczenia, o wielkości równej ilości ksiąg bibli
 //---
 bool IsActiveTranslate;	//Czy tłumaczenie jest aktywne, czyli czy jest wyświetlane
 unsigned char ucCountBooks, //Ilość ksiąg w tłumaczeniu (oryginalne tłumaczenia, katolickie)
               ucStartBook,	 //Od numeru jakiej księgi zaczyna się tłumaczenie
               ucIndexTranslate;//Numer tłumaczenia
 public:
  EnTypeTranslate enTypeTranslate; //Typ tłumaczenia, typu EnTypeTranslate (całe pismo, grecki nt. itd.)
  QString NameTranslate;	//Nazwa tłumaczenia
  unsigned int uiVersCount; //Ilość wszystkich wersetów w tłumaczeniu
};
/****************************************************************************
 *                        Klasa QGsReadBibleTextClass                   *
 ****************************************************************************/
class QGsReadBibleTextClass
{
 friend class QGsTreeBibleClass;
 friend class QGsReadBibleTextData;
 friend class QGsTabSheetBookClass;
 friend class QGsWidgetBarSelectVers;

  QGsReadBibleTextClass(const QString _PathDir);
  virtual ~QGsReadBibleTextClass();
  //---
  void _QLoadAllTranslates(const QString _PathDir); //załadowanie wszystkich tłumaczeń biblii
  void _QClearListAllTrChap(const bool bIsRemoveList=false); //Zwolnienie zawartości listy _QListAllTrChap.
  bool _QGetAllTranslatesChapter(const int iGetBook, const int iGetChap); //Konstruowanie listy z wybranym rozdziałem, wybranej księgi dla wszystkich tłumaczeń
  QStringList &QGetSelectBookTranslate(const int iGetTranslate, const int iGetBook); //Metoda zwraca adres QStringList na pozycje określonej księgi i tłumaczenia
  void QDisplayAllTextInHTML(QTextEdit *_pWebBrowser, const int iSelectTranslate=-1); //Metoda łączy w jedną całość jako kod Html tekst, ze wszystkich tłumaczeń, wybranej księgi i rozdziału.
  QGsReadBibleTextItem *QGetTranslateClass(const int iNumberTrans); //Metoda zwraca wskaźnik na klasę wybranego tłumaczenia
  inline unsigned char QGetCountTranslates() {return static_cast<unsigned char>(this->_QListItemsTranslates.count());}
  void _QGetInfoNameTranslate(const int i, QString &NameTranslate); //Zwraca nazwę tłumaczenia o numerze i
  //---
  QList<QGsReadBibleTextItem *> _QListItemsTranslates; //Lista tłumaczeń. Klas GsReadBibleTextItem. jest to lista QStringList, które
                                                       //przechowują tekst wybranej księgi rozdziału konkretnego tłumaczenia
  QList<QStringList> _QListAllTrChap; //Lista klasy QStringList, zawierających tekst wszystkich dostępnych tłumaczeń, z wybranej księgi i rodziału.
  unsigned int uiCountPol, uiCountOryg; //Ilość polskich i oryginalnych tłumaczeń
};
/****************************************************************************
 *                        Klasalasa prywatna QGsTreeWidgetItem              *
 ****************************************************************************/
class QGsTreeWidgetItem : public QTreeWidgetItem
{
 friend class QGsTreeBibleClass;
 friend class QGsReadBibleTextData;
 //---
 QGsTreeWidgetItem(int type=QTreeWidgetItem::Type);
 QGsTreeWidgetItem(QTreeWidget *parent, int type=QTreeWidgetItem::Type);
 QGsTreeWidgetItem(QGsTreeWidgetItem *parent, int type=QTreeWidgetItem::Type);
 virtual ~QGsTreeWidgetItem();
 //---
 unsigned char ucIndexBook,       //Numer księgi
               ucCountChapt;      //Ilość rozdziałów

};
/****************************************************************************
 *                        Klasalasa QGsTreeBibleClass                       *
 ****************************************************************************/
class QGsTreeBibleClass : public QTreeWidget
{
 //friend class QGsReadBibleTextData;
 Q_OBJECT
 public:
  explicit QGsTreeBibleClass(QWidget *parent = nullptr);
  virtual ~QGsTreeBibleClass();
 signals:

 public slots:

 private slots:
  void _QGsTreeDblClick(QTreeWidgetItem* _MyItem, int _column);
  void _QGsTrViewCustomCMenuReq(const QPoint &pos);
 private:
};
/****************************************************************************
 *                          Klasa GsMainTabWidgetClass                      *
 ****************************************************************************/
class QGsMainTabWidgetClass : public QTabWidget
{
 Q_OBJECT
 public:
  explicit QGsMainTabWidgetClass(QWidget *parent = nullptr);
  virtual ~QGsMainTabWidgetClass();
  //--- Metody służące do mechanizmu "drag and drop" muszą być publiczne, gdyż są wywoływane w głównej klasie aplikacji(głównego okna)
  virtual void dropEvent(QDropEvent* event) override;
  virtual void dragEnterEvent(QDragEnterEvent *event) override;
 signals:
 private slots:

 public slots:
};
/****************************************************************************
 *                          KLASA GsTabSheetClass                           *
 ****************************************************************************/
class QGsTabSheetBookClass : public QWidget
{
 friend class QGsReadBibleTextData;
 friend class QGsTreeBibleClass;

 Q_OBJECT
 public:
  explicit QGsTabSheetBookClass(QWidget *parent = nullptr, const unsigned char ucSelectBook=0);
  virtual ~QGsTabSheetBookClass();
  int QGetIndexBook() {return this->_ShucIndexBook;}
  QTextEdit *QGetTextEdit() {return this->_pQTextEdit;}
  //---
 signals:
 public slots:
 private slots:
  void _NextPrevAll(); //Slot przewijania rozdziału i księgi
  void _CBoxSelectIndexChapt(int _iSelect); //Slot wyboru rozdziału
  void _SelectTranslate(int _iSelect);  //Slot wyboru przekładu
 private:
  unsigned char _ShucIndexBook,   //Numer księgi
                _ShucIndexChapt;  //Numer rozdziału
  int iTag;

  QTextEdit *_pQTextEdit;  //Widget z głównym tekstem wybranej księgi i rozdziału
  QProgressBar *_pQProgressBarChapt; //Wskaźnik wizualny, pionoway, obrazujący w którym miejscu znajduje się aktualny rozdział
  QTabWidget *_pTabWidgetTranslates; //Wybór przekładów
  QAction *pActionNextChapter,
          *pActionPrevChapter,
          *pActionNextBook,
          *pActionPrevBook;
  QComboBox *_pCBoxAllChapters;
  //---
  void _UpdateDisplayButtonsAndText(); //Uaktualnienie stanu przycisków przewijania i tytułu zakładki
 protected:
};
/****************************************************************************
 *                      Klasalasa QGsWidgetBarSelectVers                       *
 ****************************************************************************/
class QGsWidgetBarSelectVers : public QWidget
{
  friend class QGsWidgetSelectVers;
  Q_OBJECT
private:
  explicit QGsWidgetBarSelectVers(QWidget *parent = nullptr);
  virtual ~QGsWidgetBarSelectVers();

private slots:
  void _OnAllCBoxIndexChange(int iIndex); //Wybrałeś pozycje z objektu klasy QComboBox
  void _OnAllNavigationsVers(); //nacisnąłeś przycisk klasy QPushButton

private:
  QComboBox *_pCBoxNameBooks,
            *_pCBoxChapters,
            *_pCBoxVers;
  QPushButton *_pPButtonDisplayVers,
              *_pPButtonNextVers,
              *_pPButtonPrevVers,
              *_pButtonCopyText,
              *_pButtonFavVers;
  QLabel *_pLabelDisplayAdress;

  QStringList _QSListSelectVers; //QStringLista wszystkich tłumaczeń wybranego wersetu

  void _InitSignalsAndTags();
  //Odświerzenie wyświetlania po zmianie wybranego wersetu
  void _DisplaySelectVers(const unsigned char cucBook, const unsigned char cucChapt, const unsigned char cucVer);
};
/****************************************************************************
 *                      Klasalasa QGsWidgetSelectVers                       *
 ****************************************************************************/
class QGsWidgetSelectVers : public QWidget
{
  friend class QGsWidgetBarSelectVers;
  Q_OBJECT
public:
  explicit QGsWidgetSelectVers(QWidget *parent = nullptr);
  virtual ~QGsWidgetSelectVers();

signals:

private:
    QGsWidgetBarSelectVers *_pQGsWidgetBarSelectVers;
    QTextEdit *_pTEditVers;

    QCheckBox *_pChBoxIsComment,
              *_pChBoxIsSelectTranslates,
              *_pChBoxIsDisplayButtons;

    QGsEditorClass *_pQGsEditorClass;
};

#endif // QGSREADBIBLETEXTCLASS_H
