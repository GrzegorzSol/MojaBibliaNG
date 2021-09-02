#ifndef SELECTVERSWINDOW_H
#define SELECTVERSWINDOW_H

#include <QDialog>
#include "QGsReadBibleTextClass/qgsreadbibletextclass.h"

namespace Ui {
class SelectVersWindow;
}

class SelectVersWindow : public QDialog
{
  Q_OBJECT

public:
  explicit SelectVersWindow(QWidget *parent = nullptr);
  ~SelectVersWindow();

private:
  Ui::SelectVersWindow *ui;
  QGsWidgetSelectVers *_pQGsWidgetSelectVers;
};

#endif // SELECTVERSWINDOW_H
