#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString title = QString("qt_qmake V%1").arg("0.0.1");
    setWindowTitle(title);
    setStyleSheet(QString(".MainWindow{background-color:%1;}").arg("rgb(31,33,42)"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

