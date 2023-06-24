#include "IndexWidget.h"
#include "ui_IndexWidget.h"
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QStackedWidget>

#include "TcpServerWidget.h"
#include "TcpClientWidget.h"

#include "About.h"

IndexWidget::IndexWidget(QWidget *parent) : QWidget(parent)
{
    initUi();
}

void IndexWidget::initUi(){
    QHBoxLayout *mainHLayout = new QHBoxLayout(this);
    mainHLayout->setContentsMargins(0,0,0,0);
    mainHLayout->setSpacing(0);

    QWidget *leftWidget = initLeftWidget();
    leftWidget->setFixedWidth(200);

    QWidget *rightWidget = initRightWidget();

    mainHLayout->addWidget(leftWidget);
    mainHLayout->addSpacing(2);
    mainHLayout->addWidget(rightWidget);
}
void IndexWidget::initSettings(){

}
QWidget* IndexWidget::initLeftWidget(){
    QWidget * widget = new QWidget(this);
    widget->setStyleSheet(QString(".QWidget{background-color:%1;}").arg("rgb(43,46,56)"));
    QVBoxLayout *widgetVLayout = new QVBoxLayout(widget);
    widgetVLayout->setContentsMargins(0,0,0,0);
    widgetVLayout->setSpacing(0);

    QSize size(160,50);

    tcpServerBtn = new QPushButton(widget);
    tcpServerBtn->setCursor(Qt::PointingHandCursor);
    tcpServerBtn->setStyleSheet(left_btn_no_background_selected);
    tcpServerBtn->setFixedSize(size);
    tcpServerBtn->setText("TCP SERVER");

    tcpClientBtn = new QPushButton(widget);
    tcpClientBtn->setCursor(Qt::PointingHandCursor);
    tcpClientBtn->setStyleSheet(left_btn_no_background);
    tcpClientBtn->setFixedSize(size);
    tcpClientBtn->setText("TCP CLIENT");

    udpServerBtn = new QPushButton(widget);
    udpServerBtn->setCursor(Qt::PointingHandCursor);
    udpServerBtn->setStyleSheet(left_btn_no_background);
    udpServerBtn->setFixedSize(size);
    udpServerBtn->setText("UDP SERVER");

    udpClientBtn = new QPushButton(widget);
    udpClientBtn->setCursor(Qt::PointingHandCursor);
    udpClientBtn->setStyleSheet(left_btn_no_background);
    udpClientBtn->setFixedSize(size);
    udpClientBtn->setText("UDP Client");

    udp2ServerBtn = new QPushButton(widget);
    udp2ServerBtn->setCursor(Qt::PointingHandCursor);
    udp2ServerBtn->setStyleSheet(left_btn_no_background);
    udp2ServerBtn->setFixedSize(size);
    udp2ServerBtn->setText("UDP2 SERVER");

    udp2ClientBtn = new QPushButton(widget);
    udp2ClientBtn->setCursor(Qt::PointingHandCursor);
    udp2ClientBtn->setStyleSheet(left_btn_no_background);
    udp2ClientBtn->setFixedSize(size);
    udp2ClientBtn->setText("UDP2 Client");

    connect(tcpServerBtn,&QPushButton::clicked,this,[this](){
        tcpServerBtn->setStyleSheet(left_btn_no_background_selected);
        tcpClientBtn->setStyleSheet(left_btn_no_background);
        udpServerBtn->setStyleSheet(left_btn_no_background);
        this->rightStackedWidget->setCurrentWidget(tcpServerWidget);
    });
    connect(tcpClientBtn,&QPushButton::clicked,this,[this](){
        tcpServerBtn->setStyleSheet(left_btn_no_background);
        tcpClientBtn->setStyleSheet(left_btn_no_background_selected);
        udpServerBtn->setStyleSheet(left_btn_no_background);
        this->rightStackedWidget->setCurrentWidget(tcpClientWidget);
    });

    // 文件菜单
    QMenu *settingsMenu = new QMenu(this);

    QAction *aboutAct = settingsMenu->addAction("关于");
    aboutAct->setShortcuts(QKeySequence::Preferences);
    connect(aboutAct, &QAction::triggered, this, [this]() {
        About dlg(this);
        dlg.exec();
    });
    QAction *logoutAct = settingsMenu->addAction("退出");
    logoutAct->setShortcuts(QKeySequence::Quit);
    connect(logoutAct, &QAction::triggered, this, [this]() {
        switch (QMessageBox::information(this,"提示","确认要退出吗？","确定","取消",0)){
        case 0:{

            QApplication* app;
            app->quit();
            break;
        }
        }
    });

    settingsMenu->addAction(logoutAct);

    QPushButton *settingsBtn = new QPushButton(widget);
    settingsBtn->setText("菜单");
    settingsBtn->setStyleSheet(".QPushButton {color:rgb(255,255,255);font-size:16px;border:1px solid rgb(76,76,76); border-radius: 3px;padding: 2px;}\
                               .QPushButton:hover {background-color: rgb(53,53,53);}\
                               .QPushButton:focus{outline: none;}");
    settingsBtn->setCursor(Qt::PointingHandCursor);
    settingsBtn->setFixedSize(90,32);
    connect(settingsBtn,&QPushButton::clicked,this,[this,settingsMenu](){
        settingsMenu->exec(QCursor::pos());
    });


    widgetVLayout->addSpacing(20);
    widgetVLayout->addWidget(tcpServerBtn,0,Qt::AlignHCenter);
    widgetVLayout->addSpacing(20);
    widgetVLayout->addWidget(tcpClientBtn,0,Qt::AlignHCenter);
    widgetVLayout->addSpacing(20);
    widgetVLayout->addWidget(udpServerBtn,0,Qt::AlignHCenter);
    widgetVLayout->addSpacing(20);
    widgetVLayout->addWidget(udpClientBtn,0,Qt::AlignHCenter);
    widgetVLayout->addSpacing(20);
    widgetVLayout->addWidget(udp2ServerBtn,0,Qt::AlignHCenter);
    widgetVLayout->addSpacing(20);
    widgetVLayout->addWidget(udp2ClientBtn,0,Qt::AlignHCenter);

    widgetVLayout->addStretch(10);
    widgetVLayout->addWidget(settingsBtn,0,Qt::AlignHCenter);
    widgetVLayout->addSpacing(20);

    return widget;
}
QWidget* IndexWidget::initRightWidget(){
    QWidget * widget = new QWidget(this);
    QVBoxLayout *widgetVLayout = new QVBoxLayout(widget);
    widgetVLayout->setContentsMargins(0,0,0,0);
    widgetVLayout->setSpacing(0);

    // StackedWidget start
    rightStackedWidget = new QStackedWidget(widget);
    rightStackedWidget->setStyleSheet(QString(".QStackedWidget{background-color:%1;}").arg("rgb(43,46,56)"));

    tcpServerWidget = new TcpServerWidget(this);
    tcpClientWidget = new TcpClientWidget(this);
    rightStackedWidget->addWidget(tcpServerWidget);
    rightStackedWidget->addWidget(tcpClientWidget);

    rightStackedWidget->setCurrentWidget(tcpServerWidget);
    // StackedWidget end

    widgetVLayout->addWidget(rightStackedWidget);

    return widget;
}

IndexWidget::~IndexWidget()
{

}
