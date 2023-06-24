#include "TcpServerWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

TcpServerWidget::TcpServerWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainVLayout = new QVBoxLayout(this);
    mainVLayout->setContentsMargins(0,0,0,0);
    mainVLayout->setSpacing(0);

    QLabel *label = new QLabel(this);
    label->setStyleSheet(".QLabel{color:rgb(255,255,255);}");
    label->setText("TcpServer功能-开发中111111111111111/n2222222222222222222222");

    QLabel *countLabel = new QLabel(this);
    countLabel->setStyleSheet(".QLabel{color:rgb(0,0,0);font-family:Microsoft YaHei;font-size:14px;}");
    countLabel->setText(QString("当前版本 "));



    QWidget * recordWidget = new QWidget(this);
    recordWidget->setFixedHeight(80);
    QHBoxLayout *recordHLayout = new QHBoxLayout(recordWidget);
    recordHLayout->setContentsMargins(0,0,0,0);
    recordHLayout->setSpacing(0);

    startBtn = new QPushButton(recordWidget);
    startBtn->setFixedSize(120,40);
    startBtn->setCursor(Qt::PointingHandCursor);
    startBtn->setText("开始");
    recordHLayout->addWidget(startBtn);


    mainVLayout->addSpacing(50);
    mainVLayout->addWidget(label,0,Qt::AlignHCenter);
    mainVLayout->addStretch(50);
    mainVLayout->addWidget(countLabel);
    mainVLayout->addStretch(50);
    mainVLayout->addWidget(recordWidget);
}
