#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtGui/QCloseEvent>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QSettings>

#include <opencv4/opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettings();
    turkishTranslator = new QTranslator(this);
    turkishTranslator->load(":/translations/translation_tr.qm");
    germanTranslator = new QTranslator(this);
    germanTranslator->load(":/translations/translation_de.qm");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_inputPushButton_pressed()
{
    const QString fileName
            = QFileDialog::getOpenFileName(this,
                                           tr("Open Input Image"),
                                           QDir::currentPath(),
                                           "Image (*.jpg *.png *.bmp)");
    if (QFile::exists(fileName)) {
        ui->inputLineEdit->setText(fileName);
    }
}

void MainWindow::on_outputPushButton_pressed()
{
    const QString fileName
            = QFileDialog::getSaveFileName(this,
                                           "Select Output Image",
                                           QDir::currentPath(),
                                           "*.jpg;;*.png;;*.bmp");

    if (!fileName.isEmpty()) {
        ui->outputLineEdit->setText(fileName);
        cv::Mat inpImg, outImg;
        inpImg = cv::imread(ui->inputLineEdit->text().toStdString());
        if (ui->medianBlurRadioButton->isChecked()) {
            cv::medianBlur(inpImg, outImg, 5);
        } else if (ui->gaussianBlurRatioButton->isChecked()) {
            cv::GaussianBlur(inpImg, outImg, cv::Size(5, 5), 1.25);
        }
        cv::imwrite(fileName.toStdString(), outImg);
        if (ui->displayImageCheckBox->isChecked()) {
            cv::imshow("Output Image", outImg);
        }
    }
}

void MainWindow::loadSettings()
{
    const QSettings settings("Packt", "Hello_Qt_OpenCV", this);
    ui->inputLineEdit->setText(settings.value("inputLineEdit", "").toString());
    ui->outputLineEdit->setText(settings.value("outputLineEdits", "").toString());
    ui->medianBlurRadioButton->setChecked(settings.value("medianBlurRadioButton", true).toBool());
    ui->gaussianBlurRatioButton->setChecked(settings.value("gaussianBlurRadioButton", false).toBool());
}

void MainWindow::saveSettings()
{
    QSettings settings("Packt", "Hello_Qt_OpenCV", this);
    settings.setValue("inputLineEdit", ui->inputLineEdit->text());
    settings.setValue("outputLineEdits", ui->outputPushButton->text());
    settings.setValue("medianBlurRadioButton", ui->medianBlurRadioButton->isChecked());
    settings.setValue("gaussianBlurRadioButton", ui->gaussianBlurRatioButton->isChecked());
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    const int result
            = QMessageBox::warning(this,
                                   "Exit",
                                   "Are you sure you wnat to close this program?",
                                   QMessageBox::Yes,
                                   QMessageBox::No);
    if (QMessageBox::Yes == result) {
        saveSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::on_actionTurkish_triggered()
{
    qApp->installTranslator(turkishTranslator);
}

void MainWindow::on_actionGerman_triggered()
{
    qApp->installTranslator(germanTranslator);
}

void MainWindow::on_actionEnglish_triggered()
{
    qApp->removeTranslator(turkishTranslator);
    qApp->removeTranslator(germanTranslator);
}


void MainWindow::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        ui->retranslateUi(this);
    } else {
        QMainWindow::changeEvent(event);
    }
}
