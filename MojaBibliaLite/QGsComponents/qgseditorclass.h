#ifndef QGSEDITORCLASS_H
#define QGSEDITORCLASS_H

#include <QWidget>
//Deklaracje klas by nie wczytywać niepotrzebnych nagłówków
class QPrinter;
class QTextEdit;
class QTextCharFormat;
class QLabel;
class QFontComboBox;
class QComboBox;
class QPushButton;
class QToolBar;
class QMenu;
class QActionGroup;
//Deklaracja głównej klasy kontrolki
class QGsEditorClass : public QWidget
{
  Q_OBJECT
public:
  explicit QGsEditorClass(QWidget *parent = nullptr);
  ~QGsEditorClass();
  QString currentFile; //Aktualnie wczytany plik

private slots:
  void _OnAllAction();

  void _OnSave();
  void _OnSaveAs();
  void _OnOpen();
  void _OnSelectstyleFormat(int iIndex);
  void _OnTextAlign(QAction *_pAction);

  void _OnCursorChanged();
  void _OnActivatedAllCBox(const QString &cqstr);
  void _OnSelectAllColorsMenuFont(QAction *pAction); //Slot wyboru koloru czcionki i podkładu

  void _OnCurrentCharFormatChanged(const QTextCharFormat &);
  void _OnClipboardDataChanged();
  void _OnPrintPreviewFile();
  void _OnPrintPreview(QPrinter *printer);

private:
    QToolBar *_pTBarFunctions, *_pTBarStylesText;
    QTextEdit *_pTextEdit;
    QFontComboBox *_pCBoxSelectFont;
    QComboBox *_pCBoxSizesFont, *_pCBoxSetStyles;
    QLabel *_pLabelPathFileLoad;

    QAction *_pActSave,
            *_pActSaveAs,
            *_pActOpen,
            *_pActClear,
            *_pActCopy,
            *_pActCut,
            *_pActPaste,
            *_pActFind,
            *_pActFindReplace,
            *_pActUndo,
            *_pActRedo,
            *_pActBold,
            *_pActItalic,
            *_pActUnderLine,
            *_pActStrikeOut,
            *_pActLeftAll,
            *_pActCenter,
            *_pActRightAll,
            *_pActJustify,
            *_pActPrint,
            *_pActprintPreview;

    QMenu *_pColorsMenuFont, //Kolor fontu
          *_pColorBackgroundMenuFont; //Kolor podkładu fontu
    QPushButton *_pButtonFontColor,
                *_pButtonFontBackgroundColor;
    QActionGroup *_pActAlignGroup;

    void _CreateColorMenu();
    void _ConnectedAll();
    void _CreateMainActions(); //Tworzenie głównych akcji
    void _CreateControlSelectFonts(); //Tworzenie kontrolki(lek) do wybierania czcionek
    void _SetDataActions(); //Dodawanie pomocniczych danych do głównych akcji
};

#endif // QGSEDITORCLASS_H
