#include "mblitelibrary.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

/*
#if defined(_DEBUGINFO_)
 qDebug() << "";
#endif

#if defined(_DEBUGINFO_)
  qDebug("%d", 12);
#endif
*/

bool LoadFileToStrList(QStringList &_QSList, const QString _Path)
/**
    OPIS METOD(FUNKCJI): Wczytanie pliku tekstowego i załadowanie nim objektu klasy QStringList
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{
 _QSList.clear();
 QFile File(_Path);
 if(!File.open(QIODevice::ReadOnly | QIODevice::Text)) return false;

 QTextStream textStream(&File);
 textStream.setCodec("UTF-8");

 while(!textStream.atEnd())
 {
  _QSList << textStream.readLine();
 }

 File.close();
 return true;
}
//---------------------------------------------------------------------------
bool SaveStrListToFile(const QStringList &_QSList, const QString _Path)
/**
    OPIS METOD(FUNKCJI): Zapis zawartości objektu klasy QStringList do pliku tekstowego
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QFile File(_Path);
  if(!File.open(QIODevice::WriteOnly | QIODevice::Text)) return false;

  QTextStream textStream(&File);
  textStream.setCodec("UTF-8");

  for(int i=0; i<_QSList.count(); i++)
  {
    textStream << _QSList.at(i) << "\n";
  }

  File.close();
  return true;
}
//---------------------------------------------------------------------------
void SetupColorPButton(QPushButton *pPButton, const QRgb iRGBInput)
/**
    OPIS METOD(FUNKCJI): Wczytanie i zmiana koloru objektu typu QPushButton
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QColor colorTemp;
  QPalette paletteTemp; //Kolory dla QPushButton ustawiania kolorów podkładu

  colorTemp.setRgb(iRGBInput);
  paletteTemp.setColor(QPalette::Button, colorTemp);
  pPButton->setPalette(paletteTemp);
  pPButton->update();
  //Wypisanie w objekcie klasy QPushButton koloru
  pPButton->setText(colorTemp.name());
}
//---------------------------------------------------------------------------
QRgb ReadColorPButton(QPushButton *pPButton)
/**
    OPIS METOD(FUNKCJI): Odczyt koloru objektu typu QPushButton
    OPIS ARGUMENTÓW:
    OPIS ZMIENNYCH:
    OPIS WYNIKU METODY(FUNKCJI):
*/
{
  QRgb iRGBTemp;
  QColor colorTemp;
  QPalette paletteTemp; //Kolory dla QPushButton ustawiania kolorów podkładu

  paletteTemp = pPButton->palette();
  colorTemp = paletteTemp.color(QPalette::Button);
  iRGBTemp = colorTemp.rgb();

  return iRGBTemp;
}
//---------------------------------------------------------------------------
