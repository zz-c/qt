#ifndef INDEXWIDGET_H
#define INDEXWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>

class TcpServerWidget;
class TcpClientWidget;
class UdpServerWidget;
class UdpClientWidget;
class Udp2ServerWidget;
class Udp2ClientWidget;


namespace Ui {
class IndexWidget;
}

class IndexWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IndexWidget(QWidget *parent = nullptr);
    ~IndexWidget();

private:
    void initUi();
    void initSettings();
    QWidget* initLeftWidget();
    QWidget* initRightWidget();

    //按钮无背景
    const QString left_btn_no_background = ".QPushButton {color:rgb(255,255,255);font-size:18px;border:1px solid rgb(76,76,76); border-radius: 3px;padding: 2px;}\
        .QPushButton:hover {background-color: rgb(53,53,53);}\
        .QPushButton:focus{outline: none;}";
    //按钮无背景-选中
    const QString left_btn_no_background_selected = ".QPushButton {color:rgb(221,58,95);background-color: rgb(53,53,53);font-size:18px;border:1px solid rgb(76,76,76); border-radius: 3px;padding: 2px;}\
        .QPushButton:focus{outline: none;}";
    QPushButton *tcpServerBtn;
    QPushButton *tcpClientBtn;
    QPushButton *udpServerBtn;
    QPushButton *udpClientBtn;
    QPushButton *udp2ServerBtn;
    QPushButton *udp2ClientBtn;


    QStackedWidget *rightStackedWidget;
    TcpServerWidget *tcpServerWidget;
    TcpClientWidget *tcpClientWidget;
    UdpServerWidget *udpServerWidget;
    UdpClientWidget *udpClientWidget;
    Udp2ServerWidget *udp2ServerWidget;
    Udp2ClientWidget *udp2ClientWidget;

};

#endif
