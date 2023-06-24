#ifndef TcpServerWidget_H
#define TcpServerWidget_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>

class TcpServerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TcpServerWidget(QWidget *parent);

    void run();
public slots:
    void slotNewConnection();
    void slotReadyRead();

private:
    QLabel *infolabel;
    QLabel *countLabel;
    QPushButton *startBtn;
    QLineEdit *fileLineEdit;

    QTcpServer* m_server;
    QTcpSocket* m_client;

signals:

};

class WorkerThread : public QThread
{
    Q_OBJECT

public:
    WorkerThread(QObject *parent = nullptr);

    void init(QTcpSocket* m_client);

protected:
    void run();
private:
    QTcpSocket* m_client;

signals:
    void sigResult();
};

#endif // TcpServerWidget_H
