#include "TcpServerWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSettings>
#include <QFileDialog>

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
    infolabel->setText("TcpServer功能-开发中111111111111111/n2222222222222222222222");

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
            qDebug()<<"请选择文件";
            infolabel->setText("请选择文件");
        }
        //std::thread thread(run,this);
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
