#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QDialog>
#include <QListWidgetItem>

#include <QStyledItemDelegate>
#include <QPainter>
#include <QProgressBar>
#include <QColor>
#include <QApplication>

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

  void _OnSetCuurentIndexChange(int iIndex); //Zmieniłeś wybór elementu w QComboBox

  void _OnClickItem(QListWidgetItem *item); //Kliknąłeś na pozycje listy
  void _OnTextChanged(const QString &text); //Zmieniłeś zawartość pola do wpisywania tekstu wyszukiwanego

private:
 Ui::SearchWindow *ui;
 void _InitSignalsAndTags();
};

#endif // SEARCHWINDOW_H
