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

private slots:
  void _OnClickLViewWidgetIndex(int itemIndex);
  void _OnClickButtonsAllLayoutConfig(); //Wspólny slot dla QPushButton
  void _OnClickButtonsAllPathMultiConfig(); //Wspólny slot dla QPushButton
  void _OnClickButtonsAllOtherConfig(); //Wspólny slot dla QPushButton
  void _OnClickButtonsFonts(); //Wspólny slot dla ustawiania czcionek
  void _OnClickCBoxAllConfig(); //Wspólny slot dla QCheckBox
  void _OnValuechangeAllSpBox(int inewValue); //Wspólny slot zmainy wartości dla objektów klasy QSpinbox

private:
  Ui::SetupsWindow *ui;
  void _InitAllSignalAndTags();
  void _ReadAllConfig();
  void _WriteAllConfig();
  void _RefreshPreviewText(); //Odświerzenie podglądy wyświetlania wersetów po zmianie ustawień
};

#endif // SETUPSWINDOW_H
