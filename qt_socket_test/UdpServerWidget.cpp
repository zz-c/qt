#include "UdpServerWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHostInfo>

UdpServerWidget::UdpServerWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainVLayout = new QVBoxLayout(this);
    mainVLayout->setContentsMargins(0,0,0,0);
    mainVLayout->setSpacing(0);

    infolabel = new QLabel(this);
    infolabel->setStyleSheet(".QLabel{color:rgb(255,255,255);font-size:34px;}");
    infolabel->setText("点击开始");

    countLabel = new QLabel(this);
    countLabel->setStyleSheet(".QLabel{color:rgb(255,255,255);font-family:Microsoft YaHei;font-size:34px;}");
    countLabel->setText(QString("统计数据 "));

    QWidget * recordWidget = new QWidget(this);
    recordWidget->setFixedHeight(80);
    QHBoxLayout *recordHLayout = new QHBoxLayout(recordWidget);
    recordHLayout->setContentsMargins(0,0,0,0);
    recordHLayout->setSpacing(0);

    QLabel *fileNameLabel = new QLabel(this);
    fileNameLabel->setFixedWidth(60);
    fileNameLabel->setStyleSheet(".QLabel{color:rgb(255,255,255);font-size:15px;}");
    fileNameLabel->setText("ip");

    ipLineEdit = new QLineEdit(this);
    ipLineEdit->setFixedHeight(32);
    ipLineEdit->setPlaceholderText("服务端ip");
    ipLineEdit->setStyleSheet(".QLineEdit{color:rgb(0,0,0);font-size:15px;border:1px solid rgb(217,217,217);border-radius: 3px; padding: 1px;}\
                               .QLineEdit:hover {border:1px solid rgb(64,65,66);}");
    ipLineEdit->setClearButtonEnabled(true);
    ipLineEdit->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    ipLineEdit->setCursorPosition(0);
    ipLineEdit->setText(getLocalIP());

    startBtn = new QPushButton(recordWidget);
    startBtn->setFixedSize(120,40);
    startBtn->setCursor(Qt::PointingHandCursor);
    startBtn->setText("开始");

    udpSocket=new QUdpSocket(this);//用于与连接的客户端通讯的QTcpSocket
    connect(startBtn,&QPushButton::clicked,this,[this](){

        QString targetIP=ipLineEdit->text();
        QHostAddress targetAddr(targetIP);  //目标IP
        WorkerUdpThread *workerUdpThread = new WorkerUdpThread(this);
        workerUdpThread->init(this->udpSocket,targetAddr);
        workerUdpThread->start();

    });


    recordHLayout->addWidget(fileNameLabel);
    recordHLayout->addWidget(ipLineEdit);
    recordHLayout->addWidget(startBtn);

    mainVLayout->addSpacing(50);
    mainVLayout->addWidget(infolabel,0,Qt::AlignHCenter);
    mainVLayout->addStretch(50);
    mainVLayout->addWidget(countLabel);
    mainVLayout->addStretch(50);
    mainVLayout->addWidget(recordWidget);
}

QString UdpServerWidget::getLocalIP(){
    QString hostName=QHostInfo::localHostName();//本地主机名
    QHostInfo hostInfo=QHostInfo::fromName(hostName);
    QString localIP="";

    QList<QHostAddress> addList=hostInfo.addresses();//

    if (!addList.isEmpty())
        for (int i=0;i<addList.count();i++)
        {
            QHostAddress aHost=addList.at(i);
            if (QAbstractSocket::IPv4Protocol==aHost.protocol())
            {
                localIP=aHost.toString();
                break;
            }
        }
    return localIP;
}
WorkerUdpThread::WorkerUdpThread(QObject *parent):QThread(parent){

}
void WorkerUdpThread::init(QUdpSocket *udpSocket,QHostAddress qHostAddress){
    this->udpSocket = udpSocket;
    this->qHostAddress = qHostAddress;
}
void WorkerUdpThread::run(){
    int n =0;
    size_t size = 10000;
    char buffer[size];
    memset(buffer, 0, size);
    while(n<10){
        //qDebug()<<"UdpServerWidget::run "<<n;
        quint16 targetPort = 9998;  //目标端口号
//        QString msg = "发送内容"; //发送内容
//        QByteArray byteArray = msg.toUtf8();
        long long currentTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count()/1000;
        qDebug()<<n<<"WorkerThread zzrun: threadId: "<<QThread::currentThreadId()<<"time_t"<<currentTime<<"sizeof buffer"<<sizeof(buffer);
        sprintf(buffer,"%lld",currentTime);
        udpSocket->writeDatagram(buffer, size, this->qHostAddress, targetPort);  //发送函数
        n++;
        QThread::msleep(1000);
    }
}
