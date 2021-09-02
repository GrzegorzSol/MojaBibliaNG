#include "setupswindow.h"
#include "ui_setupswindow.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include "globalvar.h"
#include "mblitelibrary.h"

/*
#if defined(_DEBUGINFO_)
 qDebug() << "";
#endif

#if defined(_DEBUGINFO_)
  qDebug("%d", 12);
#endif
*/

enum {//Numery zakładek
      enSheet_Colors, enSheetFlags, enSheetMedia,
      //Tagi dla QPushButton, od ustawiania kolorów, na pierwszej zakładce
      enTag_ColorBackgroundMainText = 100,
      enTag_ColorTextFullTranslates,
      enTag_ColorAdressFullTranslates,
      enTag_ColorTextOryginalTr,
      enTag_ColorNameOryginalTr,
      enTag_ColorAdressoryginalTr,
      //Przełączniki
      enTag_FlagDisplayinfoOnStart = 200,
      //Ustawianie ścieżek dostępu do katalogów z multimadiami
      enTag_PathMultimedia_1 = 300,
      enTag_PathMultimedia_2,
      enTag_PathMultimedia_3,
      enTag_PathMultimedia_4,
      //Pozostałe objekty klasy QPushButton
      enTag_SaveConfig = 400,
      enTag_HelpConfig,
      enTag_RejectConfig,
      //Ustawienia czcionek
      enTag_FontMainText = 500,
      enTag_FontAdressVers,
      enTag_FontTranslates,
      //Ustawienia wielkości czcionek
      enTag_FontMainTextSize = 600,
      enTag_FontAdressVersSize,
      enTag_FontTranslatesSize
     };
//Właściwości
const char PropSetupsColorsTag[] = "usp_PropSetupsColorsTag", //Właściwości dla ustawiania kolorów
           PropSetupsFlags[] = "usp_PropSetupsFlags", //Właściwości dla przełączników flag
           PropSetupsMultimediaPath[] = "usp_PropSetupsMultimediaPath", //Właściwości dla ustawiania ścieżek
           PropSetupsOtherPButtons[] = "usp_PropSetupsOtherPButtons", //Właściwości dla głównych przycisków
           //Właściwości dla objektów klasy QPushButton do wyboru czcionek
           PropSetupsFonts[] = "usp_PropsetupsFonts", //Właściwości taga dla objektu QPushButton
           PropSetupSizeFont[] = "usp_PropsetupSizeFont"; //Właściwość wielkości czcionki dla objektu klasy QPushbutton
//Teksty na zakładkach
QStringList QSListTextSheets = {"Ustawienie wyglądu tekstu biblijnego", "Przelączniki dla aplikacji", "Ustawienia dla multimediów"},
            QSListResourcesLView = {":/Setups/gfx/Wygląd aplikacji.png", ":/Setups/gfx/Przełącznik flag.png", ":/Setups/gfx/ŚcierzkiDostępuDoMultimediów.png"};

SetupsWindow::SetupsWindow(QWidget *parent) : QDialog(parent), ui(new Ui::SetupsWindow)
/**
   OPIS METOD(FUNKCJI): Metoda tworząca okno
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  this->ui->setupUi(this);
  //Odczyt konfiguracji
  this->_ReadAllConfig();
  //Tekst na zakładkach, na QListWidgecie
  for(int i=0; i<this->ui->PControlSelected->count(); i++)
  {
    this->ui->PControlSelected->setTabText(i, QSListTextSheets.at(i));
    QListWidgetItem *newItem = new QListWidgetItem(QIcon(QSListResourcesLView.at(i)), QSListTextSheets.at(i));
    this->ui->LViewAllSheets->addItem(newItem);
  }
  this->ui->PControlSelected->setCurrentIndex(0);
  this->ui->LViewAllSheets->setCurrentRow(0);
  this->_InitAllSignalAndTags();

  this->_RefreshPreviewText();
}
//---------------------------------------------------------------------------
SetupsWindow::~SetupsWindow()
/**
   OPIS METOD(FUNKCJI): Metoda destruktora
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  delete this->ui;
}
//---------------------------------------------------------------------------
void SetupsWindow::_InitAllSignalAndTags()
/**
   OPIS METOD(FUNKCJI): Definiowanie wszystkich sygnałów i tagów
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //Sygnały dla QListWidget
  connect(this->ui->LViewAllSheets, SIGNAL(currentRowChanged(int)), this->ui->PControlSelected, SLOT(setCurrentIndex(int)));
  //Sygnały dla QTabWidget
  connect(this->ui->PControlSelected, SIGNAL(tabBarClicked(int)), this, SLOT(_OnClickLViewWidgetIndex(int)));
  //Sygnały dla QPushButton
  connect(this->ui->PButtonColorBackGroundMainText, SIGNAL(clicked()), this, SLOT(_OnClickButtonsAllLayoutConfig()));
  connect(this->ui->PButtonColorFontFullTranslate, SIGNAL(clicked()), this, SLOT(_OnClickButtonsAllLayoutConfig()));
  connect(this->ui->PButtonColorAdressFulltranslate, SIGNAL(clicked()), this, SLOT(_OnClickButtonsAllLayoutConfig()));
  connect(this->ui->PButtonColorTextOryginalTr, SIGNAL(clicked()), this, SLOT(_OnClickButtonsAllLayoutConfig()));
  connect(this->ui->PButtonColorNameOryginalTr, SIGNAL(clicked()), this, SLOT(_OnClickButtonsAllLayoutConfig()));
  connect(this->ui->PButtonColorAdressOryginalTr, SIGNAL(clicked()), this, SLOT(_OnClickButtonsAllLayoutConfig()));
  //Synały dla ustawiania ścieżek dostępu
  connect(this->ui->PButtonSelectPathmedia_1, SIGNAL(clicked()), this, SLOT(_OnClickButtonsAllPathMultiConfig()));
  connect(this->ui->PButtonSelectPathmedia_2, SIGNAL(clicked()), this, SLOT(_OnClickButtonsAllPathMultiConfig()));
  connect(this->ui->PButtonSelectPathmedia_3, SIGNAL(clicked()), this, SLOT(_OnClickButtonsAllPathMultiConfig()));
  connect(this->ui->PButtonSelectPathmedia_4, SIGNAL(clicked()), this, SLOT(_OnClickButtonsAllPathMultiConfig()));
  //Sygnały dla głównych przycisków
  connect(this->ui->PButtonSetupSave, SIGNAL(clicked()), this, SLOT(_OnClickButtonsAllOtherConfig()));
  connect(this->ui->PButtonSetupHelp, SIGNAL(clicked()), this, SLOT(_OnClickButtonsAllOtherConfig()));
  connect(this->ui->PButtonSetupCancel, SIGNAL(clicked()), this, SLOT(_OnClickButtonsAllOtherConfig()));
  //Sygnały dla ustawiania czcionek
  connect(this->ui->PButtonFontMainText, SIGNAL(clicked()), this, SLOT(_OnClickButtonsFonts()));
  connect(this->ui->PButtonFontAdressMainText, SIGNAL(clicked()), this, SLOT(_OnClickButtonsFonts()));
  connect(this->ui->PButtonFontNameTranslatestText, SIGNAL(clicked()), this, SLOT(_OnClickButtonsFonts()));

  connect(this->ui->SpBoxFontMainText, SIGNAL(valueChanged(int)), this, SLOT(_OnValuechangeAllSpBox(int)));
  connect(this->ui->SpBoxFontAdressText, SIGNAL(valueChanged(int)), this, SLOT(_OnValuechangeAllSpBox(int)));
  connect(this->ui->SpBoxFontTranslateText, SIGNAL(valueChanged(int)), this, SLOT(_OnValuechangeAllSpBox(int)));
  //Sygnały dla QCheckbox
  connect(this->ui->CBoxIsDisplaySplash, SIGNAL(clicked()), this, SLOT(_OnClickCBoxAllConfig()));
  //Ustawianie właściwości dla przycisków wyboru kolorów
  this->ui->PButtonColorBackGroundMainText->setProperty(PropSetupsColorsTag, enTag_ColorBackgroundMainText);
  this->ui->PButtonColorFontFullTranslate->setProperty(PropSetupsColorsTag, enTag_ColorTextFullTranslates);
  this->ui->PButtonColorAdressFulltranslate->setProperty(PropSetupsColorsTag, enTag_ColorAdressFullTranslates);
  this->ui->PButtonColorTextOryginalTr->setProperty(PropSetupsColorsTag, enTag_ColorTextOryginalTr);
  this->ui->PButtonColorNameOryginalTr->setProperty(PropSetupsColorsTag, enTag_ColorNameOryginalTr);
  this->ui->PButtonColorAdressOryginalTr->setProperty(PropSetupsColorsTag, enTag_ColorAdressoryginalTr);
  //Ustawienia właściwości dla flag
  this->ui->CBoxIsDisplaySplash->setProperty(PropSetupsFlags, enTag_FlagDisplayinfoOnStart);
  //Ustawienia właściwości dla ścieżek dostępu do multimediów
  this->ui->PButtonSelectPathmedia_1->setProperty(PropSetupsMultimediaPath, enTag_PathMultimedia_1);
  this->ui->PButtonSelectPathmedia_2->setProperty(PropSetupsMultimediaPath, enTag_PathMultimedia_2);
  this->ui->PButtonSelectPathmedia_3->setProperty(PropSetupsMultimediaPath, enTag_PathMultimedia_3);
  this->ui->PButtonSelectPathmedia_4->setProperty(PropSetupsMultimediaPath, enTag_PathMultimedia_4);
  //Ustwienia właściwości dla pozostałych objektów klasy QPushButton
  this->ui->PButtonSetupSave->setProperty(PropSetupsOtherPButtons, enTag_SaveConfig);
  this->ui->PButtonSetupHelp->setProperty(PropSetupsOtherPButtons, enTag_HelpConfig);
  this->ui->PButtonSetupCancel->setProperty(PropSetupsOtherPButtons, enTag_RejectConfig);
  //Ustawienie właściwości dla ustawiania czcionek, przy ich wyborze
  this->ui->PButtonFontMainText->setProperty(PropSetupsFonts, enTag_FontMainText);
  this->ui->PButtonFontAdressMainText->setProperty(PropSetupsFonts, enTag_FontAdressVers);
  this->ui->PButtonFontNameTranslatestText->setProperty(PropSetupsFonts, enTag_FontTranslates);

  this->ui->SpBoxFontMainText->setProperty(PropSetupsFonts, enTag_FontMainText);
  this->ui->SpBoxFontAdressText->setProperty(PropSetupsFonts, enTag_FontAdressVers);
  this->ui->SpBoxFontTranslateText->setProperty(PropSetupsFonts, enTag_FontTranslates);
}
//---------------------------------------------------------------------------
void SetupsWindow::_RefreshPreviewText()
/**
   OPIS METOD(FUNKCJI): Odświerzenie podglądy wyświetlania wersetów po zmianie ustawień
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  const QString qstrFontMain=QString(";font-size:%1pt;font-family:%2;}\n").arg(this->ui->SpBoxFontMainText->value()).arg(this->ui->PButtonFontMainText->text()),
                qstrFontAdressMain=QString(";font-size:%1pt;font-family:%2;}\n").arg(this->ui->SpBoxFontAdressText->value()).arg(this->ui->PButtonFontAdressMainText->text()),
                qstrFontNameTranslatesMain=QString(";font-size:%1pt;font-family:%2;}\n").arg(this->ui->SpBoxFontTranslateText->value()).arg(this->ui->PButtonFontNameTranslatestText->text()),
  //Tekst w formacie html, który zostanie wyświetlony w objekcie klasy TextEdit, po zmianie ustawień konfiguracji.
  //Kolory poszczególnych części skaładowych są pobirane bezpośrednio z przycisków objetów klasy QPushbutton, z pola text()
  //Również nazwy czcionek są pobierane w identyczny sposób. Natomiast wielkość czcionek jest pobirana z objetów klasy QSpinBox, z pola value()
                qstrTextPreview = QString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n") +
      "<html><head>\n" +
      "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n" +
      "<title>Wybrany rozdział, dla dostępnych tłumaczeń</title>\n" +
      "<style type=\"text/css\">\n" +
      //Styl adresu pełnego tłumaczenia
      ".styleFullColorAdressTranslates {color:" + this->ui->PButtonColorAdressFulltranslate->text() + qstrFontAdressMain +
      //Styl tekstu dla pełnych tłumaczeń
      ".styleFullText {color: #000000" + qstrFontMain +
      //Styl nazwy pełnego tłumaczenia
      ".styleFullTranslates {color:" +  this->ui->PButtonColorFontFullTranslate->text() + qstrFontNameTranslatesMain +
      //Styl braku tłumaczenia
      ".styleNoTranslate {color: #FF0000;font-size:16pt;font-family:Times New Roman;}\n" +
      //Styl dla tekstu dla oryginalnych tłumaczeń
      ".styleOrygin {color:" + this->ui->PButtonColorTextOryginalTr->text() + qstrFontMain +
      //Styl dla adresu oryginalnego tłumaczenia
      ".styleAdressVersOryg {color:" + this->ui->PButtonColorAdressOryginalTr->text() + qstrFontAdressMain +
      //Styl nazwy oryginalnego tłumaczenia
      ".styleNameVersOryg {color:" + this->ui->PButtonColorNameOryginalTr->text() + qstrFontNameTranslatesMain +

      "body {background-color:" + this->ui->PButtonColorBackGroundMainText->text() + ";}\n" +// ";font-size:14pt;font-family:Times New Roman;}\n" +
      "</style></head><body>\n" +

      "<span class=styleFullColorAdressTranslates> Hbr 11:1 </span>" +
      "<span class=styleFullText> To jest ustawienie dla wersetu wybranego rozdziału, z pełnego pierwszego tłumaczenia </span>" +
      "<span class=styleFullTranslates> Nazwa pełnego tłumaczenia </span>" +
      "<br>" +
      "<span class=styleFullColorAdressTranslates> Hbr 11:1 </span>" +
      "<span class=styleFullText> To jest ustawienie dla wersetu wybranego rozdziału, z pełnego drugiego tłumaczenia </span>" +
      "<span class=styleFullTranslates> Nazwa pełnego tłumaczenia </span>" +
      "<br>" +
      "<span class=styleFullColorAdressTranslates> Hbr 11:1 </span>" +
      "<span class=styleFullText> To jest ustawienie dla wersetu wybranego rozdziału, z pełnego trzeciego tłumaczenia </span>" +
      "<span class=styleFullTranslates> Nazwa pełnego tłumaczenia </span>" +
      "<br>" +

      "<span class=styleAdressVersOryg> Hbr 11:1 </span>" +
      "<span class=styleOrygin> To jest ustawienie dla wersetu wybranego rozdziału, z pełnego czwartego tłumaczenia </span>" +
      "<span class=styleNameVersOryg> Nazwa częściowego(oryginalnego) tłumaczenia </span>" +
      "<br>" +
      "<span class=styleAdressVersOryg> Hbr 11:1 </span>" +
      "<span class=styleOrygin> To jest ustawienie dla wersetu wybranego rozdziału, z pełnego czwartego tłumaczenia </span>" +
      "<span class=styleNameVersOryg> Nazwa częściowego(oryginalnego) tłumaczenia </span>" +
      "<br>" +

      "</body></html>";

  this->ui->TEditDisplayTest->setHtml(qstrTextPreview);
}
//---------------------------------------------------------------------------
void SetupsWindow::_OnClickLViewWidgetIndex(int itemIndex)
/**
   OPIS METOD(FUNKCJI): SLOT
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QTabWidget *pQTabWidget = qobject_cast<QTabWidget *>(QObject::sender());
  if(!pQTabWidget) return;
  //---
  this->ui->LViewAllSheets->setCurrentRow(itemIndex);
}
//---------------------------------------------------------------------------
void SetupsWindow::_OnClickButtonsAllLayoutConfig()
/**
   OPIS METOD(FUNKCJI): Wspólny slot dla QPushButton ustawiania wyglądu
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QPushButton *pQPushButton = qobject_cast<QPushButton *>(QObject::sender());
  if(!pQPushButton) return;
  //---

  //Kolory dla QPushButton ustawiania kolorów podkładu
  QPalette paletteButton = pQPushButton->palette();

  QColorDialog pButtonCDialog = QColorDialog(paletteButton.color(QPalette::Button), this);
  //pButtonCDialog.setOptions(QColorDialog::DontUseNativeDialog);
  //pButtonCDialog.setOptions(QColorDialog::ShowAlphaChannel);
  int iResult = pButtonCDialog.exec();
  if(iResult == QDialog::Rejected)
  {
    return;
  }
  QColor color = pButtonCDialog.selectedColor();
  paletteButton.setColor(QPalette::Button, color);
  pQPushButton->setPalette(paletteButton);
  pQPushButton->update();
  pQPushButton->setText(color.name()); //Wpisanie koloru do objektu klasy QPushButton

  int iProperty = pQPushButton->property(PropSetupsColorsTag).toInt();
  switch(iProperty)
  {
    case enTag_ColorBackgroundMainText:
    {

    }
    break;
    //---
    case enTag_ColorTextFullTranslates:
    {

    }
    break;
    //---
    case enTag_ColorAdressFullTranslates:
    {

    }
    break;
    //---
    case enTag_ColorTextOryginalTr:
    {

    }
    break;
    //---
    case enTag_ColorNameOryginalTr:
    {

    }
    break;
    //---
    case enTag_ColorAdressoryginalTr:
    {

    }
    break;
    //---
  }

  //Uaktualnienie podglądy tekstu biblijnego po zmianie parametrów konfiguracji
  this->_RefreshPreviewText();
}
//---------------------------------------------------------------------------
void SetupsWindow::_OnClickButtonsAllPathMultiConfig()
/**
   OPIS METOD(FUNKCJI): Wspólny slot dla QPushButton ustawiania ścieżek dostępu do multimediów
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QPushButton *pQPushButton = qobject_cast<QPushButton *>(QObject::sender());
  if(!pQPushButton) return;
  //---
  int iProperty = pQPushButton->property(PropSetupsMultimediaPath).toInt();
  #if defined(_DEBUGINFO_)
    qDebug("_OnClickButtonsAllConfig: %d", iProperty);
  #endif
  QString qstrSelectDirectory;
  QFileDialog pathDirectory(this);
  pathDirectory.setFileMode(QFileDialog::Directory);
  pathDirectory.setOption(QFileDialog::ShowDirsOnly, true);

  if(pathDirectory.exec())
  {
    qstrSelectDirectory = pathDirectory.directory().toNativeSeparators(pathDirectory.directory().absolutePath());
    switch(iProperty)
    {
      case enTag_PathMultimedia_1:
      {
        this->ui->LEditPathMedias_1->setText(qstrSelectDirectory);
      }
      break;
      //---
      case enTag_PathMultimedia_2:
      {
        this->ui->LEditPathMedias_2->setText(qstrSelectDirectory);
      }
      break;
      //---
      case enTag_PathMultimedia_3:
      {
        this->ui->LEditPathMedias_3->setText(qstrSelectDirectory);
      }
      break;
      //---
      case enTag_PathMultimedia_4:
      {
        this->ui->LEditPathMedias_4->setText(qstrSelectDirectory);
      }
      break;
    }
  }
}
//---------------------------------------------------------------------------
void SetupsWindow::_OnClickButtonsFonts()
/**
   OPIS METOD(FUNKCJI): Wspólny slot dla ustawiania czcionek
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QPushButton *pQPushButton = qobject_cast<QPushButton *>(QObject::sender());
  if(!pQPushButton) return;
  //---
  int iPropertyTag = pQPushButton->property(PropSetupsFonts).toInt(); //Odczyt właściwości taga dla wybranego objektu klasy QPushButton do wyboru czcionki
  //Stworzenie tymczasowego objektu klasy QFont, z nazwa czcionki odczytana objektu klasy QPushButton,
  //i wielkością odczytana z właściwości "PropsetupSizeFont", tego objektu
  QFont myFont(pQPushButton->text(), pQPushButton->property(PropSetupSizeFont).toInt());
  QFontDialog fontDialog(myFont, this);

  if(fontDialog.exec())
  {
    QFont selectedFont = fontDialog.selectedFont();
    pQPushButton->setText(selectedFont.family());
    pQPushButton->setFont(selectedFont); //Wybrana czcionka staje się czcionką przycisku

    switch(iPropertyTag)
    {
      case enTag_FontMainText:
        this->ui->SpBoxFontMainText->setValue(selectedFont.pointSize());
      break;
      //---
      case enTag_FontAdressVers:
        this->ui->SpBoxFontAdressText->setValue(selectedFont.pointSize());
      break;
      //---
      case enTag_FontTranslates:
        this->ui->SpBoxFontTranslateText->setValue(selectedFont.pointSize());
      break;
    }
    //Zmiana właściwości "PropsetupSizeFont" dla objektu klasy QPushButton, zawierajacej wybraną wielkość wybranej czcionki
    pQPushButton->setProperty(PropSetupSizeFont, selectedFont.pointSize());

    this->_RefreshPreviewText();
  }
}
//---------------------------------------------------------------------------
void SetupsWindow::_OnValuechangeAllSpBox(int inewValue)
/**
   OPIS METOD(FUNKCJI): Wspólny slot zmainy wartości dla objektów klasy QSpinbox
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QSpinBox *pQSpinBox = qobject_cast<QSpinBox *>(QObject::sender());
  if(!pQSpinBox) return;
  //---
  int iPropertyTag = pQSpinBox->property(PropSetupsFonts).toInt();

  switch(iPropertyTag)
  {
    //Ustawianie właściwości "PropSetupSizeFont" dla objektu klasy QPushButton, nowej wartości wielkości czcionki
    case enTag_FontMainText:
      this->ui->PButtonFontMainText->setProperty(PropSetupSizeFont, inewValue);
    break;
    //---
    case enTag_FontAdressVers:
      this->ui->PButtonFontAdressMainText->setProperty(PropSetupSizeFont, inewValue);
    break;
    //---
    case enTag_FontTranslates:
      this->ui->PButtonFontNameTranslatestText->setProperty(PropSetupSizeFont, inewValue);
    break;
  }

  this->_RefreshPreviewText();
}
//---------------------------------------------------------------------------
void SetupsWindow::_OnClickCBoxAllConfig()
/**
   OPIS METOD(FUNKCJI): Wspólny slot dla QCheckBox
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QCheckBox *pQCheckBox = qobject_cast<QCheckBox *>(QObject::sender());
  if(!pQCheckBox) return;
  //---
  int iProperty = pQCheckBox->property(PropSetupsFlags).toInt();
  #if defined(_DEBUGINFO_)
    qDebug() << "_OnClickCBoxAllConfig";
  #endif
  switch(iProperty)
  {
    case enTag_FlagDisplayinfoOnStart:
    {

    }
    break;
    //---
  }
}
//---------------------------------------------------------------------------
void SetupsWindow::_ReadAllConfig()
/**
   OPIS METOD(FUNKCJI): Odczyt konfiguracji
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QRgb iRGBTemp;
  QFont tempFont;

  //Odczyt flag
  GlobalVar::Global_ConfigFile->beginGroup(GlobalVar::GlobalIni_Flags_Main);
    bool IsShowInfoStart = GlobalVar::Global_ConfigFile->value(GlobalVar::GloalIni_IsDisplaySplash, true).toBool();
    this->ui->CBoxIsDisplaySplash->setChecked(IsShowInfoStart);
  GlobalVar::Global_ConfigFile->endGroup();
  //Odczyt ścieżek dostępu
  GlobalVar::Global_ConfigFile->beginGroup(GlobalVar::GlobalIni_MainSection_Main);
    this->ui->LEditPathMedias_1->setText(GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_PathMultiM1, "").toString());
    this->ui->LEditPathMedias_2->setText(GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_PathMultiM2, "").toString());
    this->ui->LEditPathMedias_3->setText(GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_PathMultiM3, "").toString());
    this->ui->LEditPathMedias_4->setText(GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_PathMultiM4, "").toString());
  GlobalVar::Global_ConfigFile->endGroup();
  //Odczyt głównych kolorów tekstu biblijunego
  GlobalVar::Global_ConfigFile->beginGroup(GlobalVar::GlobalIni_ColorsSection_Main);
    //Kolor podkładu pod wyswietlany tekst
    iRGBTemp = (QRgb)GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_ColorBackGroundMainText, (QRgb)4284153797).toInt();
    SetupColorPButton(this->ui->PButtonColorBackGroundMainText, iRGBTemp);
    //Kolor nazwy dla pełnego tłumaczenia
    iRGBTemp = (QRgb)GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_ColorFontNameFullTranslate, (QRgb)4294901760).toInt();
    SetupColorPButton(this->ui->PButtonColorFontFullTranslate, iRGBTemp);
    //Kolor czcionki adresu pełnych tłumaczeń
    iRGBTemp = (QRgb)GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_ColorAdressFulltranslate, (QRgb)4294901760).toInt();
    SetupColorPButton(this->ui->PButtonColorAdressFulltranslate, iRGBTemp);
    //Kolor tekstu dla częściowych, oryginalnych tłumaczeń
    iRGBTemp = (QRgb)GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_ColorTextOryginalTr, (QRgb)0).toInt();
    SetupColorPButton(this->ui->PButtonColorTextOryginalTr, iRGBTemp);
    //Kolor nazwy częściowych, oryginalnych tłumaczeń
    iRGBTemp = (QRgb)GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_ColorNameOryginalTr, (QRgb)4294901760).toInt();
    SetupColorPButton(this->ui->PButtonColorNameOryginalTr, iRGBTemp);
    //Kolor adresu częściowych, oryginalnych tłumaczeń
    iRGBTemp = (QRgb)GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_ColorAdressOryginalTr, (QRgb)4294901760).toInt();
    SetupColorPButton(this->ui->PButtonColorAdressOryginalTr, iRGBTemp);
  GlobalVar::Global_ConfigFile->endGroup();
  //Odczyt ustawień czcionek
  GlobalVar::Global_ConfigFile->beginGroup(GlobalVar::GlobalIni_FontsSetupSection_Main);
    this->ui->PButtonFontMainText->setText(GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_FontMainText, "Times New Roman").toString());
    this->ui->SpBoxFontMainText->setValue(GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_FontMainTextSize, 16).toInt());
    tempFont.setFamily(this->ui->PButtonFontMainText->text());
    tempFont.setPointSize(this->ui->SpBoxFontMainText->value());
    this->ui->PButtonFontMainText->setFont(tempFont);

    this->ui->PButtonFontAdressMainText->setText(GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_FontAdressVersText, "Times New Roman").toString());
    this->ui->SpBoxFontAdressText->setValue(GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_FontAdressVersTextSize, 14).toInt());
    tempFont.setFamily(this->ui->PButtonFontAdressMainText->text());
    tempFont.setPointSize(this->ui->SpBoxFontAdressText->value());
    this->ui->PButtonFontAdressMainText->setFont(tempFont);

    this->ui->PButtonFontNameTranslatestText->setText(GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_FontNameTranslateText, "Times New Roman").toString());
    this->ui->SpBoxFontTranslateText->setValue(GlobalVar::Global_ConfigFile->value(GlobalVar::GlobalIni_FontNameTranslateTextSize, 12).toInt());
    tempFont.setFamily(this->ui->PButtonFontNameTranslatestText->text());
    tempFont.setPointSize(this->ui->SpBoxFontTranslateText->value());
    this->ui->PButtonFontNameTranslatestText->setFont(tempFont);
  GlobalVar::Global_ConfigFile->endGroup();
  //Ustawienie dodatkowej właściwości "PropsetupSizeFont" wielkości czcionek dla objektów klasy QPushButton do wyboru czcionek
  this->ui->PButtonFontMainText->setProperty(PropSetupSizeFont, this->ui->SpBoxFontMainText->value());
  this->ui->PButtonFontAdressMainText->setProperty(PropSetupSizeFont, this->ui->SpBoxFontAdressText->value());
  this->ui->PButtonFontNameTranslatestText->setProperty(PropSetupSizeFont, this->ui->SpBoxFontTranslateText->value());
}
//---------------------------------------------------------------------------
void SetupsWindow::_WriteAllConfig()
/**
   OPIS METOD(FUNKCJI): Zapis konfiguracji
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QRgb iRGBTemp;

  //Odczyt flag
  GlobalVar::Global_ConfigFile->beginGroup(GlobalVar::GlobalIni_Flags_Main);
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GloalIni_IsDisplaySplash, this->ui->CBoxIsDisplaySplash->isChecked());
  GlobalVar::Global_ConfigFile->endGroup();
  //Zapis ścieżek dostępu
  GlobalVar::Global_ConfigFile->beginGroup(GlobalVar::GlobalIni_MainSection_Main);
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_PathMultiM1, this->ui->LEditPathMedias_1->text());
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_PathMultiM2, this->ui->LEditPathMedias_2->text());
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_PathMultiM3, this->ui->LEditPathMedias_3->text());
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_PathMultiM4, this->ui->LEditPathMedias_4->text());
  GlobalVar::Global_ConfigFile->endGroup();
  //Zapis głównych kolorów tekstu biblijunego
  GlobalVar::Global_ConfigFile->beginGroup(GlobalVar::GlobalIni_ColorsSection_Main);
    //Kolor podkładu pod wyswietlany tekst
    iRGBTemp = ReadColorPButton(this->ui->PButtonColorBackGroundMainText);
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_ColorBackGroundMainText, iRGBTemp);
    //Kolor nazwy dla pełnego tłumaczenia
    iRGBTemp = ReadColorPButton(this->ui->PButtonColorFontFullTranslate);
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_ColorFontNameFullTranslate, iRGBTemp);
    //Kolor czcionki adresu pełnych tłumaczeń
    iRGBTemp = ReadColorPButton(this->ui->PButtonColorAdressFulltranslate);
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_ColorAdressFulltranslate, iRGBTemp);
    //Kolor tekstu dla częściowych, oryginalnych tłumaczeń
    iRGBTemp = ReadColorPButton(this->ui->PButtonColorTextOryginalTr);
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_ColorTextOryginalTr, iRGBTemp);
    //Kolor nazwy częściowych, oryginalnych tłumaczeń
    iRGBTemp = ReadColorPButton(this->ui->PButtonColorNameOryginalTr);
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_ColorNameOryginalTr, iRGBTemp);
    //Kolor adresu częściowych, oryginalnych tłumaczeń
    iRGBTemp = ReadColorPButton(this->ui->PButtonColorAdressOryginalTr);
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_ColorAdressOryginalTr, iRGBTemp);
  GlobalVar::Global_ConfigFile->endGroup();
  //Zapis ustawień czcionek
  GlobalVar::Global_ConfigFile->beginGroup(GlobalVar::GlobalIni_FontsSetupSection_Main);
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_FontMainText, this->ui->PButtonFontMainText->text());
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_FontMainTextSize, this->ui->SpBoxFontMainText->value());

    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_FontAdressVersText, this->ui->PButtonFontAdressMainText->text());
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_FontAdressVersTextSize, this->ui->SpBoxFontAdressText->value());

    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_FontNameTranslateText, this->ui->PButtonFontNameTranslatestText->text());
    GlobalVar::Global_ConfigFile->setValue(GlobalVar::GlobalIni_FontNameTranslateTextSize, this->ui->SpBoxFontTranslateText->value());
  GlobalVar::Global_ConfigFile->endGroup();
}
//---------------------------------------------------------------------------
void SetupsWindow::_OnClickButtonsAllOtherConfig()
/**
   OPIS METOD(FUNKCJI): Wspólny slot dla QPushButton pozostałych
   OPIS ARGUMENTÓW:
   OPIS ZMIENNYCH:
   OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QPushButton *pQPushButton = qobject_cast<QPushButton *>(QObject::sender());
  if(!pQPushButton) return;
  //---
  int iProperty = pQPushButton->property(PropSetupsOtherPButtons).toInt();

  switch(iProperty)
  {
    case enTag_SaveConfig:
    {
      this->_WriteAllConfig();
      //this->setResult(QDialog::Accepted);
      this->done(QDialog::Accepted);
    }
    break;
    //---
    case enTag_HelpConfig:
    {

    }
    break;
    //---
    case enTag_RejectConfig:
    {
      this->done(QDialog::Rejected);
    }
    break;
  }
}
//---------------------------------------------------------------------------
