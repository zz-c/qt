#include "UdpClientWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

UdpClientWidget::UdpClientWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainVLayout = new QVBoxLayout(this);
    mainVLayout->setContentsMargins(0,0,0,0);
    mainVLayout->setSpacing(0);

    QLabel *label = new QLabel(this);
    label->setStyleSheet(".QLabel{color:rgb(255,255,255);}");
    label->setText("UdpClientWidget-开发中");
    mainVLayout->addSpacing(50);
    mainVLayout->addWidget(label,0,Qt::AlignHCenter);
    mainVLayout->addStretch(50);
}
