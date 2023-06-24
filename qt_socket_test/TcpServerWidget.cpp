#include "TcpServerWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
void TcpServerWidget::run(){
    while (true) {
        qDebug()<<"run";
        //std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

TcpServerWidget::TcpServerWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainVLayout = new QVBoxLayout(this);
    mainVLayout->setContentsMargins(0,0,0,0);
    mainVLayout->setSpacing(0);

    infolabel = new QLabel(this);
    infolabel->setStyleSheet(".QLabel{color:rgb(255,255,255);}");
    infolabel->setText("选择文件并点击开始");

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

    QPushButton *fileBtn= new QPushButton(this);
    fileBtn->setStyleSheet( ".QPushButton {color:rgb(64,65,66);font-family:Microsoft YaHei;font-size:14px;background-color:white; border:1px solid rgb(64,65,66); padding: 0px;}\
                           .QPushButton:pressed {background-color: rgba(240,240,240,0.8);}\
                           .QPushButton:hover {background-color: rgba(240,240,240,0.4); border-color:rgba(64,65,66,0.5);}\
                           .QPushButton:focus{outline: none;}");
    fileBtn->setFixedSize(100,40);
    fileBtn->setText("选择");
    connect(fileBtn,&QPushButton::clicked,this,[this](){
        //QString dirVal = QFileDialog::getExistingDirectory(this,"浏览","").trimmed();
        QString dirVal = QFileDialog::getOpenFileName(this, "选择要播放的文件","/","视频文件 (*.h264 *.flv *.rmvb *.avi *.mp4);; 所有文件 (*.*);; ");
        if(dirVal.length()>0){
            this->fileLineEdit->setText(dirVal);
            this->fileLineEdit->setCursorPosition(0);
            QSettings settings;
            settings.setValue("SETTINGS",dirVal);
        }

    });

    startBtn = new QPushButton(recordWidget);
    startBtn->setFixedSize(120,40);
    startBtn->setCursor(Qt::PointingHandCursor);
    startBtn->setText("开始");
    connect(startBtn,&QPushButton::clicked,this,[this](){
        if(this->fileLineEdit->text().isEmpty()){
            qDebug()<<"请选择文件"<<QDateTime::currentDateTime();;
            infolabel->setText("请选择文件");
        }
        if(m_server == NULL){
            m_server = new QTcpServer(this);
            //将套接字设置为监听模式
            m_server->listen(QHostAddress::Any, 9999);

            //通过信号接收客户端请求
            connect(m_server, &QTcpServer::newConnection, this, &TcpServerWidget::slotNewConnection);
            infolabel->setText("已建立服务端监听");
        }

    });

    recordHLayout->addWidget(fileNameLabel);
    recordHLayout->addWidget(fileLineEdit);
    recordHLayout->addWidget(fileBtn);
    recordHLayout->addWidget(startBtn);


    mainVLayout->addSpacing(50);
    mainVLayout->addWidget(infolabel,0,Qt::AlignHCenter);
    mainVLayout->addStretch(50);
    mainVLayout->addWidget(countLabel);
    mainVLayout->addStretch(50);
    mainVLayout->addWidget(recordWidget);
}

void TcpServerWidget::slotNewConnection(){
    if(m_client == NULL){
        //处理客户端的连接请求
        m_client = m_server->nextPendingConnection();
        //发送数据
//        m_client->write("connect success!!!");
//        m_client->flush();
        //连接信号, 接收客户端数据
        connect(m_client, &QTcpSocket::readyRead,this, &TcpServerWidget::slotReadyRead);
        //this->start();

        WorkerThread *workthread = new WorkerThread(this);
        workthread->init(m_client);
        workthread->start();

//        int n =0;
//        while(n<10){
//            qDebug()<<n<<"WorkerThread zzrun: threadId: "<<QThread::currentThreadId();
//            m_client->write("connect success2222!!!");
//            m_client->flush();
//            n++;
//            QThread::msleep(1000);
//        }
    }
}


void TcpServerWidget::slotReadyRead(){
    //接收数据
    QByteArray array = m_client->readAll();
    QMessageBox::information(this, "Client Message", array);
}

WorkerThread::WorkerThread(QObject *parent):QThread(parent){

}
void WorkerThread::init(QTcpSocket* m_client){
    this->m_client = m_client;
}
void WorkerThread::run(){
    /*
     死循环，让线程一直跑。或者处理完毕就退出
     */
    int n =0;
    size_t size = 1000;
    char buffer[size];
    memset(buffer, 0, size);
    while(n<10){
        QDateTime now = QDateTime::currentDateTime();  // 获取当前时间
        //uint time_t = now.toTime_t();
        qDebug()<<n<<"WorkerThread zzrun: threadId: "<<QThread::currentThreadId()<<"time_t"<<std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        //this->m_client->write("connect successzz!!!");
        //const void* buffer = (char*)malloc(1000);
        this->m_client->write(buffer,size);
        m_client->flush();
        n++;
        QThread::msleep(1000);
    }
    //free(buffer);

    //emit sigResult();
}
