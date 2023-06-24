#ifndef UdpServerWidget_H
#define UdpServerWidget_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QUdpSocket>

class UdpServerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UdpServerWidget(QWidget *parent);
private:
    QLabel *infolabel;
    QLabel *countLabel;
    QLineEdit *ipLineEdit;
    QPushButton *startBtn;

    QUdpSocket *udpSocket;//

    QString getLocalIP();//获取本机IP地址
signals:

};

#endif // UdpServerWidget_H
