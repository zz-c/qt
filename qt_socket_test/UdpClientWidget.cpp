#include "UdpClientWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHostInfo>

UdpClientWidget::UdpClientWidget(QWidget *parent) : QWidget(parent)
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
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(onSocketReadyRead()));
    connect(startBtn,&QPushButton::clicked,this,[this](){
        quint16 port = 9998; //本机UDP端口
        if (udpSocket->bind(port)){ //绑定端口成功
            infolabel->setText("**成功绑定端口：" +QString::number(udpSocket->localPort()));
        }

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

void UdpClientWidget::onSocketReadyRead()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());  //数据格式统一

        QHostAddress peerAddr;
        quint16 peerPort;
        udpSocket->readDatagram(datagram.data(),
                                datagram.size(),&peerAddr,&peerPort);   //接收数据
        QString str=datagram.data();    //数据转换为QT的ui界面使用的QString类型

        QString peer="[From "+peerAddr.toString()+":"+QString::number(peerPort)+"] ";

        //ui->plainTextEdit->appendPlainText(peer+str);
        countLabel->setText(peer+str);
    }
}



QString UdpClientWidget::getLocalIP(){
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

//void UdpClientWidget::onSocketReadyRead(){

//}

//void UdpClientWidget::on_pushButton_clicked(){

//}
