#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QDialog>
#include <QListWidgetItem>

#include <QStyledItemDelegate>
#include <QPainter>
#include <QProgressBar>
#include <QColor>
#include <QApplication>
#include <QTextEdit>

//---Typy wyświetlania informacji w trybie html,
enum EnTypeDisplayHTML {
                        enTypeDisplay_ResultsearchAll=1000,    //Wyświetlanie wszystkich znalezionych wersetów
                        enTypeDisplay_ResultSearchSelectBook,  //Wyświetlanie znelozionych wersetów dla konkretnej księgi
                        enTypeDisplay_ResultSelectVers         //Wyświetlanie wybranego wersetu z listy wszystkich znalezionych wesetów
                       };

/*
 *  Klasa MyDelegate
*/
class MyDelegate : public QStyledItemDelegate
{
  Q_OBJECT
  public:
  MyDelegate(QObject *parent=0) : QStyledItemDelegate (parent){}
  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
//---------------------------------------------------------------------------
namespace Ui {
class SearchWindow;
}

class SearchWindow : public QDialog
{
 Q_OBJECT

public:
 explicit SearchWindow(QWidget *parent = nullptr);
 ~SearchWindow();
    
private slots:
  void _OnClickButtonHelpReg(); //Przycisk pomocy dla składni wyszukiwań za pomocą wyrażeń regularnych
  void _OnClickButtonStartSearch(); //Przycisk rozpoczęcia wyszukiwania
  void _OnClickButtonHelpSearch(); //Pomoc dla wyszukiwania
  void _OnClickButtonExitSearch(); //Wyjście z wyszukiwania
  void _OnClickButtonSaveSearchConfig(); //Zapis konfiguracji wyszukiwania

  void _OnClickSelectColors(); //Wybór kolorów

  void _OnSetCurentCBoxIndexChange(int iIndex); //Zmieniłeś wybór elementu w QComboBox

  void _OnClickLViewWidgetItem(QListWidgetItem *item); //Kliknąłeś na pozycje listy
  void _OnTextChanged(const QString &text); //Zmieniłeś zawartość pola do wpisywania tekstu wyszukiwanego

private:
 Ui::SearchWindow *ui;
 void _InitSignalsAndTags();
 QStringList _QListSearchResult; //Lista wszystkich wyszukanych wersetów w stanie surowym
 void _DisplayListTextHTML(QTextEdit *_pWebBrowser, const QStringList &_QListAnyVers, const EnTypeDisplayHTML _TypeDisplayHTML, const int iSelectDisplayVerset=-1);
 void _ReadAllConfig();
 void _WriteAllConfig();
};

#endif // SEARCHWINDOW_H
