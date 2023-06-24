#include "Udp2ServerWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

Udp2ServerWidget::Udp2ServerWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainVLayout = new QVBoxLayout(this);
    mainVLayout->setContentsMargins(0,0,0,0);
    mainVLayout->setSpacing(0);

    QLabel *label = new QLabel(this);
    label->setStyleSheet(".QLabel{color:rgb(255,255,255);}");
    label->setText("Udp2ServerWidget-开发中");
    mainVLayout->addSpacing(50);
    mainVLayout->addWidget(label,0,Qt::AlignHCenter);
    mainVLayout->addStretch(50);
}
