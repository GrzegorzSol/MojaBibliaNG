#ifndef SETUPSWINDOW_H
#define SETUPSWINDOW_H

#include <QDialog>

namespace Ui {
class SetupsWindow;
}

class SetupsWindow : public QDialog
{
  Q_OBJECT

public:
  explicit SetupsWindow(QWidget *parent = nullptr);
  ~SetupsWindow();

private:
  Ui::SetupsWindow *ui;
};

#endif // SETUPSWINDOW_H
