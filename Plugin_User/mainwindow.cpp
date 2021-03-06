#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#define FILTERS_SUBFOLDER "/filter_plugins/"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    getPLuginList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getPLuginList()
{
    QDir filtersDir(qApp->applicationDirPath() + FILTERS_SUBFOLDER);
    QFileInfoList filters = filtersDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files, QDir::Name);

    qDebug() << filtersDir;

    foreach(QFileInfo filter, filters) {
        if (QLibrary::isLibrary(filter.absoluteFilePath())) {
            QPluginLoader pluginLoader(filter.absoluteFilePath(), this);
            if (dynamic_cast<CvPluginInterface*>(pluginLoader.instance())) {
                ui->filtersList->addItem(filter.fileName());
                pluginLoader.unload();
            } else {
                QMessageBox::warning(this,
                                     tr("Warning"),
                                     QString(tr("Make sure %1 is  a correct plugin for this application<br> "
                                                "and it 's not in use by some other application!")).arg(filter.fileName()));
            }
        } else {
            QMessageBox::warning(this,
                                 tr("Warning"),
                                 QString(tr("Make sure only plugin exist in plugins folder.<br>"
                                            "%1 is not a plugin.")).arg(filter.fileName()));

        }
    }

    if (ui->filtersList->count() <= 0) {
        QMessageBox::critical(this,
                              tr("No Plugin"),
                              QString(tr("This application cannot work without plugins!<br>"
                                         "Make sure that filter_plugins folder exitsts "
                                         "in the same folder as the application<br>"
                                         "and that there are some filter plugins inside it.")));

        this->setEnabled(false);
    }
}

void MainWindow::on_inputImgButton_pressed()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Input Image"),
                                                    QDir::currentPath(),
                                                    tr("Image") + " (*.jpg *.png *.bmp)");
    if (QFile::exists(fileName)) {
        ui->inputImgEdit->setText(fileName);
    }
}

void MainWindow::on_helpButton_pressed()
{
    if (ui->filtersList->currentRow() >= 0) {
        QPluginLoader pluginLoader(qApp->applicationDirPath() + FILTERS_SUBFOLDER + ui->filtersList->currentItem()->text());
        CvPluginInterface* plugin = dynamic_cast<CvPluginInterface*>(pluginLoader.instance());
        if (plugin) {
            QMessageBox::information(this, tr("Plugin Description"), plugin->description());
        } else {
            QMessageBox::warning(this,
                                 tr("Warning"),
                                 QString(tr("Make sure plugin %1 exists and is usable."))
                                 .arg(ui->filtersList->currentItem()->text()));
        }
    } else {
        QMessageBox::warning(this,
                             tr("Warning"),
                             QString(tr("First select a filter plugin from the list.")));
    }
}

void MainWindow::on_filterButton_pressed()
{
    if (ui->filtersList->currentRow() >= 0 and !ui->inputImgEdit->text().isEmpty()) {
        QPluginLoader pluginLoader(qApp->applicationDirPath() + FILTERS_SUBFOLDER + ui->filtersList->currentItem()->text());
        CvPluginInterface* plugin = dynamic_cast<CvPluginInterface*>(pluginLoader.instance());
        if (plugin) {
            if (QFile::exists(ui->inputImgEdit->text())) {
                cv::Mat inputImage, outputImage;
                inputImage = cv::imread(ui->inputImgEdit->text().toStdString());
                plugin->processImage(inputImage, outputImage);
                cv::imshow(tr("Filterd Image").toStdString(), outputImage);
            } else {
                QMessageBox::warning(this,
                                     tr("Warning"),
                                     QString(tr("Make sure %1 exists.")).arg(ui->inputImgEdit->text()));
            }
        } else {
            QMessageBox::warning(this,
                                 tr("Warning"),
                                 QString(tr("Make sure plugin %1 exists and is usable."))
                                 .arg(ui->filtersList->currentItem()->text()));
        }
    } else {
        QMessageBox::warning(this,
                             tr("Warning"),
                             QString(tr("First select a filter plugin from the list.")));
    }
}
