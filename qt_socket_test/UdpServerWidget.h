#ifndef UdpServerWidget_H
#define UdpServerWidget_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QThread>
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

class WorkerUdpThread : public QThread
{
    Q_OBJECT

public:
    WorkerUdpThread(QObject *parent = nullptr);

    void init(QUdpSocket *udpSocket,QHostAddress qHostAddress);

protected:
    void run();
private:
    QUdpSocket *udpSocket;//
    QHostAddress qHostAddress;

signals:
    void sigResult();
};

#endif // UdpServerWidget_H
