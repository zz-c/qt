﻿#include "About.h"
#include "ComLineWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QToolButton>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QUrl>
#include <QLabel>

About::About(QWidget *parent) : QDialog(parent)
{

    setWindowFlags(Qt::Dialog| Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_StyledBackground,true);
    setWindowTitle("关于");
    setFixedSize(660,340);

    mainVLayout = new QVBoxLayout(this);
    mainVLayout->setContentsMargins(0,0,0,0);
    mainVLayout->setSpacing(0);

    mainVLayout->addSpacing(10);
    initTopUi();
    mainVLayout->addSpacing(10);
    initBottomUi();
    mainVLayout->addStretch(10);
}

void About::initTopUi(){

    QWidget *outWidget = new QWidget(this);
    outWidget->setFixedSize(600,140);
    outWidget->setStyleSheet(".QWidget{background-color:rgb(205,205,205);border-radius: 5px;}");
    QVBoxLayout *outLayout = new QVBoxLayout(outWidget);
    outLayout->setContentsMargins(1,1,1,1);

    QWidget *topWidget = new QWidget(outWidget);
    topWidget->setStyleSheet(".QWidget{background-color:rgb(255,255,255);border-radius: 5px;}");
    QVBoxLayout *topLayout = new QVBoxLayout(topWidget);
    topLayout->setContentsMargins(0,0,0,0);
    // about logo+名称
    QWidget *logoWidget = new QWidget(topWidget);
    logoWidget->setFixedHeight(60);
    QHBoxLayout *logoHLayout = new QHBoxLayout(logoWidget);
    logoHLayout->setContentsMargins(0,0,0,0);

    QLabel *logo = new QLabel(logoWidget);
    logo->setPixmap(QIcon(":/images/logo.png").pixmap(36,40));

    QLabel *nameLabel = new QLabel(logoWidget);
    nameLabel->setStyleSheet(".QLabel{color:rgb(0,0,0);font-family:Microsoft YaHei;font-size:30px;}");
    nameLabel->setText(QCoreApplication::applicationName());

    logoHLayout->addSpacing(20);
    logoHLayout->addWidget(logo);
    logoHLayout->addSpacing(10);
    logoHLayout->addWidget(nameLabel);
    logoHLayout->addStretch(10);


    // about-声明
    QWidget *smWidget = new QWidget(topWidget);
    QHBoxLayout *smHLayout = new QHBoxLayout(smWidget);
    smHLayout->setContentsMargins(0,0,0,0);
    smWidget->setFixedHeight(60);

    QLabel *smContentLabel = new QLabel(smWidget);
    smContentLabel->setFixedWidth(500);
//    smContentLabel->setGeometry(QRect(328, 240, 329, 27*4)); //四倍行距
    smContentLabel->setWordWrap(true);
    smContentLabel->setText(tr("<p style='font-family:Microsoft YaHei;font-size:14px;margin:10px;line-height:25px;'>Qt开发。</p>"));
    smHLayout->addSpacing(10);
    smHLayout->addWidget(smContentLabel);
    smHLayout->addStretch(10);


    topLayout->addWidget(logoWidget);
    topLayout->addWidget(new ComLineWidget(this));
    topLayout->addWidget(smWidget);
    topLayout->addStretch(10);
    outLayout->addWidget(topWidget);
    mainVLayout->addWidget(outWidget,0,Qt::AlignHCenter);

}

void About::initBottomUi(){
    QWidget *outWidget = new QWidget(this);
    outWidget->setFixedSize(600,130);
    outWidget->setStyleSheet(".QWidget{background-color:rgb(205,205,205);border-radius: 5px;}");
    QVBoxLayout *outLayout = new QVBoxLayout(outWidget);
    outLayout->setContentsMargins(1,1,1,1);

    QWidget * bottomWidget = new QWidget(outWidget);
    bottomWidget->setStyleSheet(".QWidget{background-color:rgb(255,255,255);border-radius: 5px;}");
    QVBoxLayout *bottomVLayout = new QVBoxLayout(bottomWidget);
    bottomVLayout->setContentsMargins(20,10,20,10);

    QLabel *copyrightLabel = new QLabel(bottomWidget);
    copyrightLabel->setStyleSheet(".QLabel{color:rgb(0,0,0);font-family:Microsoft YaHei;font-size:14px;}");
    copyrightLabel->setText(QString("当前版本 V%1").arg(QCoreApplication::applicationVersion()));

    QLabel *authorLabel = new QLabel(bottomWidget);
    authorLabel->setStyleSheet(".QLabel{color:rgb(0,0,0);font-family:Microsoft YaHei;font-size:14px;}");
    authorLabel->setText(tr("qt"));
    authorLabel->setOpenExternalLinks(true);
    connect(authorLabel,&QLabel::linkActivated,this,[](const QString &link){
       QDesktopServices::openUrl(QUrl(link));
    });



    // 开源地址 start
    QWidget *osWidget = new QWidget(bottomWidget);// 开源地址
    osWidget->setFixedHeight(20);
    QHBoxLayout *osHLayout = new QHBoxLayout(osWidget);
    osHLayout->setContentsMargins(0,0,0,0);

    QLabel *osLabel = new QLabel(osWidget);
    osLabel->setStyleSheet(".QLabel{color:rgb(0,0,0);font-family:Microsoft YaHei;font-size:14px;}");
    osLabel->setText("开源地址");
    QToolButton *osAddressBtn = new QToolButton(osWidget);
    osAddressBtn->setCursor(Qt::PointingHandCursor);
    osAddressBtn->setStyleSheet("QToolButton{border:0px;font-family:Microsoft YaHei;font-size:13px;color:rgb(43,113,237)}");
    osAddressBtn->setText("https://github.com//zz-c/qt");
    connect(osAddressBtn,&QToolButton::clicked,this,[](){
        QDesktopServices::openUrl(QUrl("https://github.com//zz-c/qt"));
    });

    osHLayout->addWidget(osLabel);
    osHLayout->addSpacing(6);
    osHLayout->addWidget(osAddressBtn);
    osHLayout->addStretch(10);
    // 开源地址 end

    bottomVLayout->addSpacing(10);
    bottomVLayout->addWidget(copyrightLabel);
    bottomVLayout->addWidget(authorLabel);
    bottomVLayout->addSpacing(10);
    bottomVLayout->addWidget(new ComLineWidget(this));
    bottomVLayout->addWidget(osWidget);
    bottomVLayout->addStretch(10);

    outLayout->addWidget(bottomWidget);
    mainVLayout->addWidget(outWidget,0,Qt::AlignHCenter);

}
