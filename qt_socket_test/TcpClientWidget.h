#ifndef TcpClientWidget_H
#define TcpClientWidget_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTcpSocket>


class TcpClientWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TcpClientWidget(QWidget *parent);
public slots:
    void slotReadyRead();
    void slotSendMsg();
private:
    QLabel *infolabel;
    QLabel *countLabel;
    QPushButton *startBtn;
    QLineEdit *fileLineEdit;
    QTcpSocket* m_client;
signals:

};

#endif // TcpClientWidget_H
