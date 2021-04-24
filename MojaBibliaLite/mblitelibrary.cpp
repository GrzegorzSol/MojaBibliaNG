#include "mblitelibrary.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
//#include <QApplication>
//#include <QWidget>


bool LoadFileToStrList(QStringList &_QSList, const QString _Path)
/**
    OPIS METOD(FUNKCJI):
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
    OPIS METOD(FUNKCJI):
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
