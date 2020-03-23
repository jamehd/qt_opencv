#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFileDialog>
#include <QMessageBox>
#include <QPluginLoader>
#include <QFileInfoList>

#include "../Interface/cvplugininterface.h"

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
    void on_inputImgButton_pressed();

    void on_helpButton_pressed();

    void on_filterButton_pressed();

private:
    Ui::MainWindow *ui;

    void getPLuginList();
};

#endif // MAINWINDOW_H
