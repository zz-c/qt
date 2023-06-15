#include "IndexWidget.h"
#include "ui_IndexWidget.h"
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QHBoxLayout>

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

    mainHLayout->addWidget(leftWidget);
    mainHLayout->addSpacing(2);
}
void IndexWidget::initSettings(){

}
QWidget* IndexWidget::initLeftWidget(){
    QWidget * widget = new QWidget(this);
    widget->setStyleSheet(QString(".QWidget{background-color:%1;}").arg("rgb(43,46,56)"));
    QVBoxLayout *widgetVLayout = new QVBoxLayout(widget);
    widgetVLayout->setContentsMargins(0,0,0,0);
    widgetVLayout->setSpacing(0);

    // 文件菜单
    QMenu *settingsMenu = new QMenu(this);


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
    settingsBtn->setText("菜单q");
    settingsBtn->setStyleSheet(".QPushButton {color:rgb(255,255,255);font-size:16px;border:1px solid rgb(76,76,76); border-radius: 3px;padding: 2px;}\
                               .QPushButton:hover {background-color: rgb(53,53,53);}\
                               .QPushButton:focus{outline: none;}");
    settingsBtn->setCursor(Qt::PointingHandCursor);
    settingsBtn->setFixedSize(90,32);
    connect(settingsBtn,&QPushButton::clicked,this,[this,settingsMenu](){
        settingsMenu->exec(QCursor::pos());
    });


    widgetVLayout->addWidget(settingsBtn,0,Qt::AlignHCenter);

    return widget;
}
QWidget* IndexWidget::initRightWidget(){

}

IndexWidget::~IndexWidget()
{

}
