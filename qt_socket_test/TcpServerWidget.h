#ifndef TcpServerWidget_H
#define TcpServerWidget_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QThread>
#include <QTcpServer>

class TcpServerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TcpServerWidget(QWidget *parent);

    void run();
private:
    QLabel *infolabel;
    QLabel *countLabel;
    QPushButton *startBtn;
    QLineEdit *fileLineEdit;

    QTcpServer* m_server;

signals:

};

class WorkerThread : public QThread
{
    Q_OBJECT

public:
    WorkerThread(QObject *parent = nullptr);


protected:
    void run();

signals:
    void sigResult();
};

#endif // TcpServerWidget_H
