#ifndef MBLITELIBRARY_H
#define MBLITELIBRARY_H

#include <QString>
#include <QObject>

extern bool LoadFileToStrList(QStringList &_QSList, const QString _Path);
extern bool SaveStrListToFile(const QStringList &_QSList, const QString _Path);

#endif // MBLITELIBRARY_H
