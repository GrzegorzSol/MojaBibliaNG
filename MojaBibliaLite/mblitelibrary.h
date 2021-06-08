#ifndef MBLITELIBRARY_H
#define MBLITELIBRARY_H

#include <QString>
#include <QObject>
#include <QPushButton>

extern bool LoadFileToStrList(QStringList &_QSList, const QString _Path);
extern bool SaveStrListToFile(const QStringList &_QSList, const QString _Path);

extern void SetupColorPButton(QPushButton *pPButton, const QRgb iRGBInput);
extern QRgb ReadColorPButton(QPushButton *pPButton);

#endif // MBLITELIBRARY_H
