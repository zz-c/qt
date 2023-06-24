#include "TcpClientWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

TcpClientWidget::TcpClientWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainVLayout = new QVBoxLayout(this);
    mainVLayout->setContentsMargins(0,0,0,0);
    mainVLayout->setSpacing(0);

    infolabel = new QLabel(this);
    infolabel->setStyleSheet(".QLabel{color:rgb(255,255,255);font-size:34px;}");
    infolabel->setText("输入ip并点击开始");

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
    ipLineEdit->setPlaceholderText("请输入服务端ip");
    ipLineEdit->setStyleSheet(".QLineEdit{color:rgb(0,0,0);font-size:15px;border:1px solid rgb(217,217,217);border-radius: 3px; padding: 1px;}\
                               .QLineEdit:hover {border:1px solid rgb(64,65,66);}");
    ipLineEdit->setClearButtonEnabled(true);
    ipLineEdit->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    ipLineEdit->setCursorPosition(0);
    ipLineEdit->setText("127.0.0.1");

    startBtn = new QPushButton(recordWidget);
    startBtn->setFixedSize(120,40);
    startBtn->setCursor(Qt::PointingHandCursor);
    startBtn->setText("开始");
    connect(startBtn,&QPushButton::clicked,this,[this](){
        //创建套接字
        m_client = new QTcpSocket(this);
        //连接服务器
        QString ip = ipLineEdit->text();
        m_client->connectToHost(QHostAddress(ip), 9999);
        infolabel->setText(ip+"已连接");
        //通过信号接收服务器数据
        connect(m_client, &QTcpSocket::readyRead, this, &TcpClientWidget::slotReadyRead);
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




    //发送按钮
    //connect(ui->btnSend, &QPushButton::clicked, this, &TCPClient::slotSendMsg);
}

void TcpClientWidget::slotReadyRead()
{
    long long currentTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count()/1000;
    long long sendTime;
    //接收数据
    QByteArray array = m_client->readAll();
    sscanf(array,"%lld",&sendTime); //注意此处有&
    //QMessageBox::information(this, "Server Message", array);
    long long delayTime = currentTime - sendTime;
    qDebug()<<"TcpClient read:"<<sendTime<<"delayTime"<<delayTime;
    avgDelayTime = (avgDelayTime*packetNumCount+delayTime)/(packetNumCount+1);
    packetNumCount++;
    QString countInfo="已接收:";
    countInfo.append(QString::number(packetNumCount, 10));
    countInfo.append(",大小:");
    packetSizeCount += array.size();
    countInfo.append(QString::number(packetSizeCount, 10));
    countInfo.append(",平均延迟:");
    countInfo.append(QString::number(avgDelayTime, 10));
    countLabel->setText(countInfo);
}


void TcpClientWidget::slotSendMsg()
{
    //发送数据
//    QString text = ui->textEdit->toPlainText();
//    m_client->write(text.toUtf8());
//    ui->textEdit->clear();
}
