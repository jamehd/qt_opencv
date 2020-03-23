#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QTranslator>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_inputPushButton_pressed();

  void on_outputPushButton_pressed();

  void on_actionTurkish_triggered();

  void on_actionGerman_triggered();

  void on_actionEnglish_triggered();

private:
  Ui::MainWindow *ui;

  void loadSettings();
  void saveSettings();

  QTranslator *turkishTranslator;
  QTranslator *germanTranslator;

  // QWidget interface
protected:
  void closeEvent(QCloseEvent *event) override;
  void changeEvent(QEvent *) override;
};

#endif // MAINWINDOW_H
