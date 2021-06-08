#ifndef INFORMATIONSWINDOW_H
#define INFORMATIONSWINDOW_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class InformationsWindow;
}

class InformationsWindow : public QDialog
{
  Q_OBJECT

public:
  explicit InformationsWindow(QWidget *parent = nullptr, bool _bNormal=true);
  ~InformationsWindow();

protected:
  void mousePressEvent(QMouseEvent *) override;

private slots:
  void _MyTimerSlot();

private:
  Ui::InformationsWindow *ui;
  QTimer *_pMyTimer;
  bool bNormalStart;
};

#endif // INFORMATIONSWINDOW_H
