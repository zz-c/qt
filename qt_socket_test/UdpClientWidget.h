#ifndef UdpClientWidget_H
#define UdpClientWidget_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QLineEdit>

#include <QUdpSocket>
//#include <QLineEdit>


class UdpClientWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UdpClientWidget(QWidget *parent);
public slots:
    void onSocketReadyRead();//读取socket传入的数据
private:
    QLabel *infolabel;
    QLabel *countLabel;
    QLineEdit *ipLineEdit;
    QPushButton *startBtn;

    QUdpSocket *udpSocket;//
    QString getLocalIP();//获取本机IP地址

};

#endif // UdpClientWidget_H
