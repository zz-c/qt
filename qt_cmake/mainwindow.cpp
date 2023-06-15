#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "IndexWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QString title = QString("qt_cmake V%1").arg("0.0.1");
    setWindowTitle(title);
    setStyleSheet(QString(".MainWindow{background-color:%1;}").arg("rgb(31,33,42)"));

    IndexWidget *index = new IndexWidget(this);
    setCentralWidget(index);
}

MainWindow::~MainWindow()
{
    delete ui;
}

