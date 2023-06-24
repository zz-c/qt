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
    infolabel->setStyleSheet(".QLabel{color:rgb(255,255,255);}");
    infolabel->setText("输入ip并点击开始");

    countLabel = new QLabel(this);
    countLabel->setStyleSheet(".QLabel{color:rgb(0,0,0);font-family:Microsoft YaHei;font-size:14px;}");
    countLabel->setText(QString("当前版本 "));


    QWidget * recordWidget = new QWidget(this);
    recordWidget->setFixedHeight(80);
    QHBoxLayout *recordHLayout = new QHBoxLayout(recordWidget);
    recordHLayout->setContentsMargins(0,0,0,0);
    recordHLayout->setSpacing(0);

    QLabel *fileNameLabel = new QLabel(this);
    fileNameLabel->setFixedWidth(60);
    fileNameLabel->setStyleSheet(".QLabel{color:rgb(255,255,255);font-size:15px;}");
    fileNameLabel->setText("文件路径");

    fileLineEdit = new QLineEdit(this);
    fileLineEdit->setFixedHeight(32);
    fileLineEdit->setPlaceholderText("请输入文件路径");
    fileLineEdit->setStyleSheet(".QLineEdit{color:rgb(0,0,0);font-size:15px;border:1px solid rgb(217,217,217);border-radius: 3px; padding: 1px;}\
                               .QLineEdit:hover {border:1px solid rgb(64,65,66);}");
    fileLineEdit->setClearButtonEnabled(true);
    fileLineEdit->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    //dirLineEdit->setText(SingletonUtils::getInstance()->getRecordDir());
    fileLineEdit->setCursorPosition(0);

    startBtn = new QPushButton(recordWidget);
    startBtn->setFixedSize(120,40);
    startBtn->setCursor(Qt::PointingHandCursor);
    startBtn->setText("开始");
    connect(startBtn,&QPushButton::clicked,this,[this](){
        //创建套接字
        m_client = new QTcpSocket(this);
        //连接服务器
        m_client->connectToHost(QHostAddress("127.0.0.1"), 9999);
        //通过信号接收服务器数据
        connect(m_client, &QTcpSocket::readyRead, this, &TcpClientWidget::slotReadyRead);
    });

    recordHLayout->addWidget(fileNameLabel);
    recordHLayout->addWidget(fileLineEdit);
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
    //接收数据
    QByteArray array = m_client->readAll();
    //QMessageBox::information(this, "Server Message", array);
    qDebug()<<"TcpClient read:"<<array;
}


void TcpClientWidget::slotSendMsg()
{
    //发送数据
//    QString text = ui->textEdit->toPlainText();
//    m_client->write(text.toUtf8());
//    ui->textEdit->clear();
}
