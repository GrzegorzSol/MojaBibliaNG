#include <QVBoxLayout>
#include <QMenu>
#include <QLabel>
#include <QPair>
#include <QFileDialog>
#include <QTextList>
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QTextEdit>
#include <QFontComboBox>
#include <QPushButton>
#include <QToolBar>

#if defined(QT_PRINTSUPPORT_LIB)
  #include <QtPrintSupport/qtprintsupportglobal.h>
  #if QT_CONFIG(printer)
    #if QT_CONFIG(printdialog)
      #include <QPrintDialog>
    #endif
    #include <QPrinter>

    #if QT_CONFIG(printpreviewdialog)
      #include <QPrintPreviewDialog>
    #endif
  #endif
#endif

#ifndef _DEBUGINFO_
  #include <QTextStream>
#endif

#include "qgseditorclass.h"
#include "globalvar.h"
#include "qgseditordataimages.h"

/*
#if defined(_DEBUGINFO_)
 qDebug() << "";
#endif

#if defined(_DEBUGINFO_)
  qDebug("%d", 12);
#endif
*/
//Definiowanie właściwości dla objektów
enum
{
  enAct_Save=100, enAct_SaveAs, enAct_Open, enAct_Clear, enAct_Copy, enAct_Cut, enAct_Paste,
  enAct_Find, enAct_FindReplace, enAct_Undo, enAct_Redo, enAct_Bold, enAct_Italic, enAct_UnderLine,
  enAct_StrikeOut, enAct_LeftAll, enAct_Center, enAct_RightAll, enAct_Justify, enAct_Print, enAct_PrintPreview,
  enCBox_FontName=200, enCBox_FontSize, enCBox_SetStyles,
  enMenu_FontColor=300, enMenu_FontBackgroundColor
};

//--- Właściwości użytkownika dla objektów
const char PropCBoxTag[] = "usp_PropCBoxTag",
           PropMenuTag[] = "usp_PropMenuTag";

typedef QPair<QColor, QString> PairItemsColors;
typedef QVector< PairItemsColors > VectorItemsColor;

QGsEditorClass::QGsEditorClass(QWidget *parent) : QWidget(parent)
/**
   OPIS METOD(FUNKCJI): Konstruktor klasy
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  this->setMaximumHeight(168);
  this->setMinimumHeight(168);

  this->_pTBarFunctions = new QToolBar(this);
  //this->_pTBarFunctions->setFloatable(true);

  this->_pTBarStylesText = new QToolBar(this);
  this->_pTextEdit = new QTextEdit(this);
  //Tworzenie głównych akcji
  this->_CreateMainActions();
  //Tworzenie kontrolki(lek) do wybierania czcionek
  this->_CreateControlSelectFonts();
  //Tworzenie kontrolek do ustawiania kolorów czcionki
  this->_CreateColorMenu();
  //Dodawanie pomocniczych danych do głównych akcji
  this->_SetDataActions();

  QVBoxLayout *pQVBoxLayout = new QVBoxLayout(this);
  pQVBoxLayout->setContentsMargins(0, 0, 0, 0);
  pQVBoxLayout->setSpacing(0);

  //Ścieżka dostępu wczytanego pliku
  this->_pLabelPathFileLoad = new QLabel(this);
  this->_pLabelPathFileLoad->setText(this->currentFile);
  _pLabelPathFileLoad->setFrameStyle(QFrame::Box | QFrame::Raised);

  pQVBoxLayout->addWidget(this->_pTBarFunctions);
  pQVBoxLayout->addWidget(this->_pTBarStylesText);
  pQVBoxLayout->addWidget(this->_pTextEdit);
  pQVBoxLayout->addWidget(this->_pLabelPathFileLoad);

  this->_pTextEdit->setCurrentFont(this->font());
  //Ustawienie domyślnej czcionki dla tekstu
  QTextCursor TextCursor = this->_pTextEdit->textCursor();
  QTextCharFormat TextCharFormat = TextCursor.charFormat();
  TextCharFormat.setFontFamily(this->_pTextEdit->currentFont().family());
  TextCharFormat.setFontPointSize(this->_pTextEdit->currentFont().pointSize());
  TextCursor.mergeCharFormat(TextCharFormat);
  TextCursor.setPosition(0);
  //this->_pTextEdit->setText("Grzegorz Sołtysik, Katarzyna, Lidia");
  //Ustawienie domyślnej wielkości tekstu
  int iIndex = this->_pCBoxSelectFont->findText(TextCharFormat.fontFamily());
  this->_pCBoxSelectFont->setCurrentIndex(iIndex);
  iIndex = this->_pCBoxSizesFont->findText(QString().number(TextCharFormat.fontPointSize()));
  this->_pCBoxSizesFont->setCurrentIndex(iIndex);
  //--- Podłączanie
  this->_ConnectedAll();
}
//---------------------------------------------------------------------------
void QGsEditorClass::_CreateMainActions()
/**
   OPIS METOD(FUNKCJI): Tworzenie głównych akcji i kontrolek
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QIcon iconSave(QPixmap::fromImage(QImage::fromData(ID_SAVE, sizeof(ID_SAVE)))),
        iconSaveAs(QPixmap::fromImage(QImage::fromData(ID_SAVE_AS, sizeof(ID_SAVE_AS)))),
        iconOpen(QPixmap::fromImage(QImage::fromData(ID_OPEN, sizeof(ID_OPEN)))),
        iconClear(QPixmap::fromImage(QImage::fromData(ID_CLEAR, sizeof(ID_CLEAR)))),
        iconCopy(QPixmap::fromImage(QImage::fromData(ID_COPY, sizeof(ID_COPY)))),
        iconCut(QPixmap::fromImage(QImage::fromData(ID_CUT, sizeof(ID_CUT)))),
        iconPaste(QPixmap::fromImage(QImage::fromData(ID_PASTE, sizeof(ID_PASTE)))),
        iconFind(QPixmap::fromImage(QImage::fromData(ID_FIND, sizeof(ID_FIND)))),
        iconFindReplace(QPixmap::fromImage(QImage::fromData(ID_FINDREPLACE, sizeof(ID_FINDREPLACE)))),
        iconUndo(QPixmap::fromImage(QImage::fromData(ID_UNDO, sizeof(ID_UNDO)))),
        iconRedo(QPixmap::fromImage(QImage::fromData(ID_REDO, sizeof(ID_REDO)))),
        iconBold(QPixmap::fromImage(QImage::fromData(ID_BOLD, sizeof(ID_BOLD)))),
        iconItalic(QPixmap::fromImage(QImage::fromData(ID_ITALIC, sizeof(ID_ITALIC)))),
        iconUnderLine(QPixmap::fromImage(QImage::fromData(ID_UNDERLINE, sizeof(ID_UNDERLINE)))),
        iconStrikeOut(QPixmap::fromImage(QImage::fromData(ID_STRIKEOUT, sizeof(ID_STRIKEOUT)))),
        iconLeftAll(QPixmap::fromImage(QImage::fromData(ID_LEFTALL, sizeof(ID_LEFTALL)))),
        iconCenter(QPixmap::fromImage(QImage::fromData(ID_CENTER, sizeof(ID_CENTER)))),
        iconRightAll(QPixmap::fromImage(QImage::fromData(ID_RIGHTALL, sizeof(ID_RIGHTALL)))),
        iconJustify(QPixmap::fromImage(QImage::fromData(ID_JUSTIFY, sizeof(ID_JUSTIFY)))),
        iconParagraph(QPixmap::fromImage(QImage::fromData(ID_PARAGRAPH, sizeof(ID_PARAGRAPH)))),
        iconPrint(QPixmap::fromImage(QImage::fromData(ID_PRINT, sizeof(ID_PRINT)))),
        iconPrintPreview(QPixmap::fromImage(QImage::fromData(ID_PRINTPREVIEW, sizeof(ID_PRINTPREVIEW))));

  this->setWindowModified(this->_pTextEdit->document()->isModified());

  this->_pActSave = this->_pTBarFunctions->addAction(iconSave, "Zapisz", this, SLOT(_OnSave()));
  this->_pActSave->setEnabled(this->_pTextEdit->document()->isModified()); //Wyłączenie opcji zapisu gdy bcoś zmieniono w dokumencie
  this->_pActSaveAs = this->_pTBarFunctions->addAction(iconSaveAs, "Zapisz jako...", this, SLOT(_OnSaveAs()));
  this->_pActSaveAs->setEnabled(this->_pTextEdit->document()->isModified()); //Wyłączenie opcji zapisu gdy bcoś zmieniono w dokumencie
  this->_pActOpen = this->_pTBarFunctions->addAction(iconOpen, "Otwórz...", this, SLOT(_OnOpen()));

  this->_pActClear = this->_pTBarFunctions->addAction(iconClear, "Skasuj zawartość", this->_pTextEdit, SLOT(clear()));
    this->_pTBarFunctions->addSeparator();
  this->_pActCopy = this->_pTBarFunctions->addAction(iconCopy, "Skopiuj zaznaczenie", this->_pTextEdit, SLOT(copy()));
  this->_pActCut = this->_pTBarFunctions->addAction(iconCut, "Wytnij zaznaczenie", this->_pTextEdit, SLOT(cut()));
  this->_pActPaste = this->_pTBarFunctions->addAction(iconPaste, "Wklej", this->_pTextEdit, SLOT(paste()));
    this->_pTBarFunctions->addSeparator();
  this->_pActFind = this->_pTBarFunctions->addAction(iconFind, "Wyszukaj...", this, SLOT(_OnAllAction()));
  this->_pActFindReplace = this->_pTBarFunctions->addAction(iconFindReplace, "Wyszukaj i podmień...", this, SLOT(_OnAllAction()));
      this->_pTBarFunctions->addSeparator();
  this->_pActUndo = this->_pTBarFunctions->addAction(iconUndo, "Cofnij", this->_pTextEdit, SLOT(undo()));
  this->_pActRedo = this->_pTBarFunctions->addAction(iconRedo, "Wróć cofnięcie", this->_pTextEdit, SLOT(redo()));
    this->_pTBarFunctions->addSeparator();
  this->_pActPrint = this->_pTBarFunctions->addAction(iconPrint, "Drukuj...", this, SLOT(_OnAllAction()));
  this->_pActprintPreview = this->_pTBarFunctions->addAction(iconPrintPreview, "Podgląd wydruku...", this, SLOT(_OnPrintPreviewFile()));
  //-------------------------------------------------------------------------
  //Styl czcionki
  this->_pActBold = this->_pTBarStylesText->addAction(iconBold, "Pogrubienie", this, SLOT(_OnAllAction()));
  this->_pActItalic = this->_pTBarStylesText->addAction(iconItalic, "Pochylenie", this, SLOT(_OnAllAction()));
  this->_pActUnderLine = this->_pTBarStylesText->addAction(iconUnderLine, "Podkreślenie", this, SLOT(_OnAllAction()));
  this->_pActStrikeOut = this->_pTBarStylesText->addAction(iconStrikeOut, "Przekreślenie", this, SLOT(_OnAllAction()));
    this->_pTBarStylesText->addSeparator();
  //Formatowanie tekstu
  this->_pActLeftAll = this->_pTBarStylesText->addAction(iconLeftAll, "Lewy margines");
  this->_pActCenter = this->_pTBarStylesText->addAction(iconCenter, "Wyśrodkowany");
  this->_pActRightAll = this->_pTBarStylesText->addAction(iconRightAll, "Prawy margines");
  this->_pActJustify = this->_pTBarStylesText->addAction(iconJustify, "Układanie tekstu");
    this->_pTBarStylesText->addSeparator();

  //Akcje Cut Copy
  #ifndef QT_NO_CLIPBOARD

    if (const QMimeData *md = QApplication::clipboard()->mimeData())
          this->_pActPaste->setEnabled(md->hasText());
    //---????
    this->_pActCopy->setEnabled(false);
    this->_pActCut->setEnabled(false);
  #endif
  //Akcje Undo i Redo
  this->_pActUndo->setEnabled(this->_pTextEdit->document()->isUndoAvailable());
  this->_pActRedo->setEnabled(this->_pTextEdit->document()->isRedoAvailable());
  //Formty czcionki jako akcje przełączalne
  this->_pActBold->setCheckable(true);
  this->_pActItalic->setCheckable(true);
  this->_pActUnderLine->setCheckable(true);
  this->_pActStrikeOut->setCheckable(true);

  this->_pActLeftAll->setCheckable(true);
  this->_pActLeftAll->setChecked(true);
  this->_pActCenter->setCheckable(true);
  this->_pActRightAll->setCheckable(true);
  this->_pActJustify->setCheckable(true);
  //Podłączenie do grupy akcji, akcji związanych z formatowaniem bloków
  this->_pActAlignGroup = new QActionGroup(this);
  this->_pActAlignGroup->addAction(this->_pActLeftAll);
  this->_pActAlignGroup->addAction(this->_pActCenter);
  this->_pActAlignGroup->addAction(this->_pActRightAll);
  this->_pActAlignGroup->addAction(this->_pActJustify);
}
//---------------------------------------------------------------------------
void QGsEditorClass::_CreateControlSelectFonts()
/**
   OPIS METOD(FUNKCJI): Tworzenie kontrolki(lek) do wybierania czcionek
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //Wybór czcionki
  this->_pCBoxSelectFont = new QFontComboBox(this);
  //Wybór wielkości czcionki
  this->_pCBoxSizesFont = new QComboBox(this);
  for(int i : QFontDatabase::standardSizes()) this->_pCBoxSizesFont->addItem(QString().setNum(i));
  //tworzenie objektu klasy QComboBox do wybór stylów
  this->_pCBoxSetStyles = new QComboBox(this);
  this->_pCBoxSetStyles->addItem("Standardowe");
  this->_pCBoxSetStyles->addItem(QIcon(QPixmap::fromImage(QImage::fromData(ID_STYLES_FILLCIRCLE, sizeof(ID_STYLES_FILLCIRCLE)))), "Symbol punktorów (Okrąg wypełniony)");
  this->_pCBoxSetStyles->addItem(QIcon(QPixmap::fromImage(QImage::fromData(ID_STYLES_EMPTYCIRCLE, sizeof(ID_STYLES_EMPTYCIRCLE)))), "Symbol punktorów (Okrąg pusty)");
  this->_pCBoxSetStyles->addItem(QIcon(QPixmap::fromImage(QImage::fromData(ID_STYLES_SQUARE, sizeof(ID_STYLES_SQUARE)))), "Symbol punktorów (Kwadrat)");
  this->_pCBoxSetStyles->addItem(QIcon(QPixmap::fromImage(QImage::fromData(ID_STYLES_NUMERIC, sizeof(ID_STYLES_NUMERIC)))), "Punktory listy (Numeryczny)");
  this->_pCBoxSetStyles->addItem(QIcon(QPixmap::fromImage(QImage::fromData(ID_STYLES_ALPHALOWER, sizeof(ID_STYLES_ALPHALOWER)))), "Punktory listy (Znak mały)");
  this->_pCBoxSetStyles->addItem(QIcon(QPixmap::fromImage(QImage::fromData(ID_STYLES_ALPHAUPPER, sizeof(ID_STYLES_ALPHAUPPER)))), "Punktory listy (Znak duzy)");
  this->_pCBoxSetStyles->addItem(QIcon(QPixmap::fromImage(QImage::fromData(ID_STYLES_ROMANLOWER, sizeof(ID_STYLES_ROMANLOWER)))), "Punktory listy (Rzymskie małe)");
  this->_pCBoxSetStyles->addItem(QIcon(QPixmap::fromImage(QImage::fromData(ID_STYLES_ROMANUPPER, sizeof(ID_STYLES_ROMANUPPER)))), "Punktory listy (Rzymskie duże)");

  QLabel *pLabelParagraph = new QLabel(" Punktowanie: ", this),
         *pLabelPixmapParagraph = new QLabel();
  pLabelPixmapParagraph->setPixmap(QPixmap::fromImage(QImage::fromData(ID_PARAGRAPH, sizeof(ID_PARAGRAPH))));

  //Dodawanie objektów klasy QCombobox do objektów klasy QToolbar
  this->_pTBarStylesText->addWidget(pLabelPixmapParagraph);
  this->_pTBarStylesText->addWidget(pLabelParagraph);
  this->_pTBarStylesText->addWidget(this->_pCBoxSetStyles);
  this->_pTBarStylesText->addSeparator();
  this->_pTBarStylesText->addWidget(this->_pCBoxSelectFont);
  this->_pTBarStylesText->addSeparator();
  this->_pTBarStylesText->addWidget(this->_pCBoxSizesFont);
  this->_pTBarStylesText->addSeparator();
  //Włąściwości objektów klasy QComboBox
  this->_pCBoxSelectFont->setProperty(PropCBoxTag, enCBox_FontName);
  this->_pCBoxSizesFont->setProperty(PropCBoxTag, enCBox_FontSize);
  this->_pCBoxSetStyles->setProperty(PropCBoxTag, enCBox_SetStyles);
}
//---------------------------------------------------------------------------
void QGsEditorClass::_SetDataActions()
/**
   OPIS METOD(FUNKCJI): Dodawanie pomocniczych danych do głównych akcji
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  this->_pActSave->setData(enAct_Save);
  this->_pActSaveAs->setData(enAct_SaveAs);
  this->_pActOpen->setData(enAct_Open);
  this->_pActClear->setData(enAct_Clear);
  this->_pActCopy->setData(enAct_Copy);
  this->_pActCut->setData(enAct_Cut);
  this->_pActPaste->setData(enAct_Paste),
  this->_pActFind->setData(enAct_Find),
  this->_pActFindReplace->setData(enAct_FindReplace),
  this->_pActUndo->setData(enAct_Undo),
  this->_pActRedo->setData(enAct_Redo),
  this->_pActBold->setData(enAct_Bold),
  this->_pActItalic->setData(enAct_Italic),
  this->_pActUnderLine->setData(enAct_UnderLine),
  this->_pActStrikeOut->setData(enAct_StrikeOut),
  this->_pActLeftAll->setData(enAct_LeftAll);
  this->_pActCenter->setData(enAct_Center),
  this->_pActRightAll->setData(enAct_RightAll),
  this->_pActJustify->setData(enAct_Justify);
  this->_pActPrint->setData(enAct_Print);
  this->_pActprintPreview->setData(enAct_PrintPreview);
}
//---------------------------------------------------------------------------
void QGsEditorClass::_ConnectedAll()
/**
   OPIS METOD(FUNKCJI): Podłączanie sygnałów
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  connect(this->_pTextEdit, SIGNAL(cursorPositionChanged()), this, SLOT(_OnCursorChanged()));
  connect(this->_pCBoxSelectFont, SIGNAL(textActivated(const QString&)), this, SLOT(_OnActivatedAllCBox(const QString&)));
  connect(this->_pCBoxSizesFont, SIGNAL(textActivated(const QString&)), this, SLOT(_OnActivatedAllCBox(const QString&)));
  connect(this->_pCBoxSetStyles, SIGNAL(activated(int)), this, SLOT(_OnSelectstyleFormat(int)));

  connect(this->_pTextEdit, SIGNAL(currentCharFormatChanged(const QTextCharFormat&)),
          this, SLOT(_OnCurrentCharFormatChanged(const QTextCharFormat&)));
  //Aktywność QAction Undo i Redo
  connect(this->_pTextEdit, SIGNAL(undoAvailable(bool)), this->_pActUndo, SLOT(setEnabled(bool)));
  connect(this->_pTextEdit, SIGNAL(redoAvailable(bool)), this->_pActRedo, SLOT(setEnabled(bool)));
  //Grupa formatowania tekstu
  connect(this->_pActAlignGroup, SIGNAL(triggered(QAction *)), this, SLOT(_OnTextAlign(QAction *)));

  connect(this->_pColorsMenuFont, SIGNAL(triggered(QAction *)), this, SLOT(_OnSelectAllColorsMenuFont(QAction *)));
  connect(this->_pColorBackgroundMenuFont, SIGNAL(triggered(QAction *)), this, SLOT(_OnSelectAllColorsMenuFont(QAction *)));
  //Aktywacja akcji zapisu zależnie od wskaźnika modyfikacji dokumentu
  connect(this->_pTextEdit->document(), SIGNAL(modificationChanged(bool)), this->_pActSave, SLOT(setEnabled(bool)));
  connect(this->_pTextEdit->document(), SIGNAL(modificationChanged(bool)), this->_pActSaveAs, SLOT(setEnabled(bool)));
  connect(this->_pTextEdit->document(), SIGNAL(modificationChanged(bool)), this, SLOT(setWindowModified(bool)));
  //Akcje Cut Copy
  #ifndef QT_NO_CLIPBOARD
    connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(_OnClipboardDataChanged()));
  #endif
}
//---------------------------------------------------------------------------
QGsEditorClass::~QGsEditorClass()
/**
   OPIS METOD(FUNKCJI): Destruktor klasy
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
void QGsEditorClass::_OnPrintPreviewFile()
/**
   OPIS METOD(FUNKCJI): Podgląd wydruku pliku
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  #if QT_CONFIG(printpreviewdialog)
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, SIGNAL(paintRequested(QPrinter *)), this, SLOT(_OnPrintPreview(QPrinter *)));
    preview.exec();
  #endif
}
//---------------------------------------------------------------------------
void QGsEditorClass::_OnPrintPreview(QPrinter *printer)
/**
   OPIS METOD(FUNKCJI): Podgląd wydruku
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  #ifdef QT_NO_PRINTER
    Q_UNUSED(printer);
  #else
    this->_pTextEdit->print(printer);
  #endif
}
//---------------------------------------------------------------------------
void QGsEditorClass::_OnClipboardDataChanged()
/**
   OPIS METOD(FUNKCJI):
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  #ifndef QT_NO_CLIPBOARD
    if (const QMimeData *md = QApplication::clipboard()->mimeData())
      this->_pActPaste->setEnabled(md->hasText());
  #endif
}
//---------------------------------------------------------------------------
void QGsEditorClass::_OnSave()
/**
   OPIS METOD(FUNKCJI): Zapisywanie tekstu pod bierząca nazwą
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QAction *pAction = qobject_cast<QAction *>(QObject::sender());
  if(!pAction) return;
  //---
  if(!this->currentFile.isEmpty())
  {
    QFile writeOpenFile(this->currentFile);
    if(writeOpenFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream writeStream(&writeOpenFile);
        writeStream.setCodec("UTF-8");

        writeStream << this->_pTextEdit->toHtml();
        writeOpenFile.close();
    }
  }
}
//---------------------------------------------------------------------------
void QGsEditorClass::_OnOpen()
/**
   OPIS METOD(FUNKCJI): Odczyt zapisanego pliku
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QAction *pAction = qobject_cast<QAction *>(QObject::sender());
  if(!pAction) return;
  //---
  QFileDialog fileDialogOpen(this);

  fileDialogOpen.setFileMode(QFileDialog::AnyFile);
  fileDialogOpen.setNameFilter("Wszystkie pliki (*.html *.htm *.txt *.lfc);;Plik komentarza LFC (*.lfc)");
  QStringList fileNames;
  QString fileName;

  if(fileDialogOpen.exec())
  {
    fileNames = fileDialogOpen.selectedFiles();
    fileName = fileNames.first();

    QFileInfo fileInfo(fileName);
    QString extension = fileInfo.suffix(); //Pobieram rozszerzenie wybranego pliku

    QFile openOpenFile(fileName);

    if(openOpenFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QTextStream readStream(&openOpenFile);
      readStream.setCodec("UTF-8");

      if(extension == "txt")
        this->_pTextEdit->setPlainText(readStream.readAll());
      else this->_pTextEdit->setHtml(readStream.readAll());

      openOpenFile.close();

      QTextCursor cursor = this->_pTextEdit->textCursor();
      cursor.movePosition(QTextCursor::End);
      this->_pTextEdit->setTextCursor(cursor);

      this->currentFile = fileName;
      this->_pLabelPathFileLoad->setText(this->currentFile);

      //this->_pActSave->setEnabled(true);
    }
  }
}
//---------------------------------------------------------------------------
void QGsEditorClass::_OnSaveAs()
/**
   OPIS METOD(FUNKCJI): Zapisywanie tekstu pod wybraną nazwa
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QAction *pAction = qobject_cast<QAction *>(QObject::sender());
  if(!pAction) return;
  //---
  QFileDialog fileDialogSave(this);
  QStringList fileNames;
  QString fileName;

  fileDialogSave.setFileMode(QFileDialog::AnyFile);
  fileDialogSave.setNameFilter("Plik komentarza LFC (*.lfc)");
  fileDialogSave.setAcceptMode(QFileDialog::AcceptSave);

  if(fileDialogSave.exec())
  {
    fileNames = fileDialogSave.selectedFiles();
    fileName = fileNames.first();

    QFile writeOpenFile(fileName);

    if(writeOpenFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      QTextStream writeStream(&writeOpenFile);
      writeStream.setCodec("UTF-8");

      writeStream << this->_pTextEdit->toHtml();
      writeOpenFile.close();

      this->currentFile = fileName; //Ustawienie aktualnego pliku
      this->_pLabelPathFileLoad->setText(this->currentFile);
      //this->_pActSave->setEnabled(true);
    }
  }
}
//---------------------------------------------------------------------------
void QGsEditorClass::_OnSelectstyleFormat(int iIndex)
/**
   OPIS METOD(FUNKCJI):
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QComboBox *pQComboBox = qobject_cast<QComboBox *>(QObject::sender());
  if(!pQComboBox) return;
  //---
  QTextCursor TextCursor = this->_pTextEdit->textCursor();

  if(iIndex != 0)
  {
    QTextListFormat::Style style = QTextListFormat::ListDisc;

    switch(iIndex)
    {
      case 1:
        style = QTextListFormat::ListDisc;
      break;
      //---
      case 2:
        style = QTextListFormat::ListCircle;
      break;
      //---
      case 3:
        style = QTextListFormat::ListSquare;
      break;
      //---
      case 4:
        style = QTextListFormat::ListDecimal;
      break;
      //---
      case 5:
        style = QTextListFormat::ListLowerAlpha;
      break;
      //---
      case 6:
        style = QTextListFormat::ListUpperAlpha;
      break;
      //---
      case 7:
        style = QTextListFormat::ListLowerRoman;
      break;
      //---
      case 8:
        style = QTextListFormat::ListUpperRoman;
      break;
    }

    TextCursor.beginEditBlock();
    QTextBlockFormat TextBlockFormat = TextCursor.blockFormat();
    QTextListFormat TextListFormat;

    if (TextCursor.currentList())
    {
      TextListFormat = TextCursor.currentList()->format();
    }
    else
    {
      TextListFormat.setIndent(TextBlockFormat.indent() + 1);
      TextBlockFormat.setIndent(0);
      TextCursor.setBlockFormat(TextBlockFormat);
    }

    TextListFormat.setStyle(style);
    TextCursor.createList(TextListFormat);

    TextCursor.endEditBlock();
  }
  else
  {
    QTextBlockFormat Blockformat;
    Blockformat.setObjectIndex(-1);
    TextCursor.mergeBlockFormat(Blockformat);
  }
}
//---------------------------------------------------------------------------
void QGsEditorClass::_OnTextAlign(QAction *_pAction)
/**
   OPIS METOD(FUNKCJI): Sygnał wybrania objektu klasy QAction, z grupu objektu, klasy QActionGroup
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QTextCursor TextCursor = this->_pTextEdit->textCursor();
  QTextBlockFormat textBlockFormat = TextCursor.blockFormat();
  //---
  if(_pAction == this->_pActLeftAll)
  {
    textBlockFormat.setAlignment(Qt::AlignLeft);
    TextCursor.mergeBlockFormat(textBlockFormat);
  }
  else if(_pAction == this->_pActCenter)
  {
    textBlockFormat.setAlignment(Qt::AlignCenter);
    TextCursor.mergeBlockFormat(textBlockFormat);
  }
  else if(_pAction == this->_pActRightAll)
  {
    textBlockFormat.setAlignment(Qt::AlignRight);
    TextCursor.mergeBlockFormat(textBlockFormat);
  }
  else if(_pAction == this->_pActJustify)
  {
    textBlockFormat.setAlignment(Qt::AlignJustify);
    TextCursor.mergeBlockFormat(textBlockFormat);
  }
}
//---------------------------------------------------------------------------
void QGsEditorClass::_OnAllAction()
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
  QTextCursor TextCursor = this->_pTextEdit->textCursor();
  QTextCharFormat TextCharFormat;
  QTextBlockFormat textBlockFormat = TextCursor.blockFormat();
  int iData = pAction->data().toInt();

  switch(iData)
  {
    case enAct_Find:
    {
    }
    break;
    //---
    case enAct_FindReplace:
    {
    }
    break;
    //---
    case enAct_Bold:
    {
      if(pAction->isChecked()) TextCharFormat.setFontWeight(QFont::Bold);
      else TextCharFormat.setFontWeight(QFont::Normal);
      TextCursor.mergeCharFormat(TextCharFormat);
    }
    break;
    //---
    case enAct_Italic:
    {
      TextCharFormat.setFontItalic(pAction->isChecked());
      TextCursor.mergeCharFormat(TextCharFormat);
    }
    break;
    //---
    case enAct_UnderLine:
    {
      TextCharFormat.setFontUnderline(pAction->isChecked());
      TextCursor.mergeCharFormat(TextCharFormat);
    }
    break;
    //---
    case enAct_StrikeOut:
    {
      TextCharFormat.setFontStrikeOut(pAction->isChecked());
      TextCursor.mergeCharFormat(TextCharFormat);
    }
    break;
    //---
  }
}
//---------------------------------------------------------------------------
void QGsEditorClass::_OnCursorChanged()
/**
   OPIS METOD(FUNKCJI): Sygnał przesunięcia kursora
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QTextEdit *pQTextEdit = qobject_cast<QTextEdit *>(QObject::sender());
  if(!pQTextEdit) return;
  //---
  QTextCursor TextCursor = pQTextEdit->textCursor();
  QTextBlockFormat textBlockFormat = TextCursor.blockFormat();

  this->_pActLeftAll->setChecked(textBlockFormat.alignment() == Qt::AlignLeft);
  this->_pActCenter->setChecked(textBlockFormat.alignment() == Qt::AlignCenter);
  this->_pActRightAll->setChecked(textBlockFormat.alignment() == Qt::AlignRight);
  this->_pActJustify->setChecked(textBlockFormat.alignment() == Qt::AlignJustify);
}
//---------------------------------------------------------------------------
void QGsEditorClass::_OnActivatedAllCBox(const QString &cqstr)
/**
   OPIS METOD(FUNKCJI): Wybrałeś pozycje z objektu klasy QComboBox
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QComboBox *pQComboBox = qobject_cast<QComboBox *>(QObject::sender());
  if(!pQComboBox) return;
  //---
  int iProperty = pQComboBox->property(PropCBoxTag).toInt();
  QTextCharFormat TextCharFormat;
  QTextCursor TextCursor = this->_pTextEdit->textCursor();

  switch(iProperty)
  {
    case enCBox_FontName:
    {
      TextCharFormat.setFontFamily(cqstr);
      TextCursor.mergeCharFormat(TextCharFormat);
    }
    break;
    //---
    case enCBox_FontSize:
    {
      TextCharFormat.setFontPointSize(QString(cqstr).toInt());
      TextCursor.mergeCharFormat(TextCharFormat);
    }
    break;
  }
}
//---------------------------------------------------------------------------
void QGsEditorClass::_CreateColorMenu()
/**
   OPIS METOD(FUNKCJI): Tworzenie menu dla objektu klasy QAction wyboru kolorów
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QTextCursor TextCursor = this->_pTextEdit->textCursor();
  QTextCharFormat TextCharFormat = TextCursor.charFormat();
  QColor colorForeground = TextCharFormat.foreground().color(),
         colorBackground  = TextCharFormat.background().color();

  this->_pColorsMenuFont = new QMenu(this);
  this->_pColorsMenuFont->setProperty(PropMenuTag, enMenu_FontColor);
  this->_pColorBackgroundMenuFont = new QMenu(this);
  this->_pColorBackgroundMenuFont->setProperty(PropMenuTag, enMenu_FontBackgroundColor);
  QPixmap pixmap(22, 22);

  VectorItemsColor VectorColors;
  VectorColors.append(qMakePair(QColor(Qt::white), QString("Biały")));
  VectorColors.append(qMakePair(QColor(Qt::black), QString("Czarny")));
  VectorColors.append(qMakePair(QColor(Qt::red), QString("Czerwony")));
  VectorColors.append(qMakePair(QColor(Qt::darkRed), QString("Ciemno czerwony")));
  VectorColors.append(qMakePair(QColor(Qt::green), QString("Zielony")));
  VectorColors.append(qMakePair(QColor(Qt::darkGreen), QString("Ciemno zielony")));
  VectorColors.append(qMakePair(QColor(Qt::blue), QString("Niebieski")));
  VectorColors.append(qMakePair(QColor(Qt::darkBlue), QString("Ciemno niebieski")));
  VectorColors.append(qMakePair(QColor(Qt::darkRed), QString("Ciemno czerwony")));
  VectorColors.append(qMakePair(QColor(Qt::cyan), QString("Cyjankowy")));
  VectorColors.append(qMakePair(QColor(Qt::darkCyan), QString("Ciemno cyjankowy")));
  VectorColors.append(qMakePair(QColor(Qt::magenta), QString("Różowy")));
  VectorColors.append(qMakePair(QColor(Qt::darkMagenta), QString("Fioletowy")));
  VectorColors.append(qMakePair(QColor(Qt::yellow), QString("Żółty")));
  VectorColors.append(qMakePair(QColor(Qt::darkYellow), QString("Ciemno żółty")));
  VectorColors.append(qMakePair(QColor(Qt::gray), QString("Szary")));
  VectorColors.append(qMakePair(QColor(Qt::darkGray), QString("Ciemno szary")));
  VectorColors.append(qMakePair(QColor(Qt::lightGray), QString("Jasno szary")));

  for(const PairItemsColors &cpair : VectorColors)
  {
    pixmap.fill(cpair.first);
    QAction *pAction = this->_pColorsMenuFont->addAction(pixmap, cpair.second);
    pAction->setData(cpair.first);

    pAction = this->_pColorBackgroundMenuFont->addAction(pixmap, cpair.second);
    pAction->setData(cpair.first);
  }
  //Dodanie objektów klasu QPushButton ustawień klorów czcionki
  QLabel *pLabelPixmapColorFont = new QLabel(this),
         *pLabelTextColorFont = new QLabel(" Kolor czcionki: ", this);
  pLabelPixmapColorFont->setPixmap(QPixmap::fromImage(QImage::fromData(ID_FONTCOLOR, sizeof(ID_FONTCOLOR))));

  this->_pButtonFontColor = new QPushButton(this);
  this->_pButtonFontColor->setAutoFillBackground(true);
  this->_pButtonFontColor->setFlat(true);

  QLabel *pLabelPixmapColorBackgroudFont = new QLabel(this),
         *pLabelTextColorBackgroundFont = new QLabel(" Kolor podkładu czcionki: ", this);
  pLabelPixmapColorBackgroudFont->setPixmap(QPixmap::fromImage(QImage::fromData(ID_FONTCOLORBACKGROUND, sizeof(ID_FONTCOLORBACKGROUND))));

  this->_pButtonFontBackgroundColor = new QPushButton(this);
  this->_pButtonFontBackgroundColor->setAutoFillBackground(true);
  this->_pButtonFontBackgroundColor->setFlat(true);

  this->_pButtonFontColor->setMenu(this->_pColorsMenuFont);
  this->_pButtonFontBackgroundColor->setMenu(this->_pColorBackgroundMenuFont);

  this->_pTBarStylesText->addWidget(pLabelPixmapColorFont);
  this->_pTBarStylesText->addWidget(pLabelTextColorFont);
  this->_pTBarStylesText->addWidget(this->_pButtonFontColor);
    this->_pTBarStylesText->addSeparator();
  this->_pTBarStylesText->addWidget(pLabelPixmapColorBackgroudFont);
  this->_pTBarStylesText->addWidget(pLabelTextColorBackgroundFont);
  this->_pTBarStylesText->addWidget(this->_pButtonFontBackgroundColor);
  //Ustawienia dla koloru czcionki
  QPalette paletteForeground = this->_pButtonFontColor->palette();
  paletteForeground.setColor(this->_pButtonFontColor->backgroundRole(), colorForeground);
  this->_pButtonFontColor->setPalette(paletteForeground);
  //Ustawienia dla koloru podkładu czcionki
  QPalette paletteBackground = this->_pButtonFontBackgroundColor->palette();
  paletteBackground.setColor(this->_pButtonFontBackgroundColor->backgroundRole(), colorBackground);
  this->_pButtonFontBackgroundColor->setPalette(paletteBackground);
}
//---------------------------------------------------------------------------
void QGsEditorClass::_OnSelectAllColorsMenuFont(QAction *pAction)
/**
   OPIS METOD(FUNKCJI): SLOT wyboru objektu klasy QAction, przy wybraniu pozycji z menu wyboru kolorów czcionki i jej podkładu
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QMenu *pMenu = qobject_cast<QMenu *>(QObject::sender());
  if(!pMenu) return;
  //---
  int iProperty = pMenu->property(PropMenuTag).toInt();

  QTextCharFormat TextCharFormat;
  QTextCursor TextCursor = this->_pTextEdit->textCursor();
  QColor color = pAction->data().value<QColor>();

  switch(iProperty)
  {
    case enMenu_FontColor:
    {
       TextCharFormat.setForeground(QBrush(color));
       TextCursor.mergeCharFormat(TextCharFormat);

       QPalette palette = this->_pButtonFontColor->palette();
       palette.setColor(this->_pButtonFontColor->backgroundRole(), color);
       this->_pButtonFontColor->setPalette(palette);
    }
    break;
    //---
    case enMenu_FontBackgroundColor:
    {
       TextCharFormat.setBackground(QBrush(color));
       TextCursor.mergeCharFormat(TextCharFormat);

       QPalette palette = this->_pButtonFontBackgroundColor->palette();
       palette.setColor(this->_pButtonFontBackgroundColor->backgroundRole(), color);
       this->_pButtonFontBackgroundColor->setPalette(palette);
    }
    break;
  }
}
//---------------------------------------------------------------------------
void QGsEditorClass::_OnCurrentCharFormatChanged(const QTextCharFormat &TextCharFormat)
/**
   OPIS METOD(FUNKCJI): Zmiana formatu znaku
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QTextEdit *pQTextEdit = qobject_cast<QTextEdit *>(QObject::sender());
  if(!pQTextEdit) return;
  //---
  QColor colorForeground = TextCharFormat.foreground().color(),
         colorBackground  = TextCharFormat.background().color();

  this->_pActBold->setChecked(TextCharFormat.fontWeight() == QFont::Bold);
  this->_pActItalic->setChecked(TextCharFormat.fontItalic());
  this->_pActUnderLine->setChecked(TextCharFormat.fontUnderline());
  this->_pActStrikeOut->setChecked(TextCharFormat.fontStrikeOut());
  //Odczyt czcionki dla bierzącego znaku i ustawienie objektu klasy QComboBox
  int iIndex = this->_pCBoxSelectFont->findText(TextCharFormat.fontFamily());
  this->_pCBoxSelectFont->setCurrentIndex(iIndex);
  //Odczyt wielkości czcionki
  iIndex = this->_pCBoxSizesFont->findText(QString().number((int)TextCharFormat.fontPointSize()));
  this->_pCBoxSizesFont->setCurrentIndex(iIndex);
  //Odczyt ustawienia dla koloru czcionki
  QPalette paletteForeground = this->_pButtonFontColor->palette();
  paletteForeground.setColor(this->_pButtonFontColor->backgroundRole(), colorForeground);
  this->_pButtonFontColor->setPalette(paletteForeground);
  //Odczyt ustawienia dla koloru podkładu czcionki
  QPalette paletteBackground = this->_pButtonFontBackgroundColor->palette();
  paletteBackground.setColor(this->_pButtonFontBackgroundColor->backgroundRole(), colorBackground);
  this->_pButtonFontBackgroundColor->setPalette(paletteBackground);
}
//---------------------------------------------------------------------------
