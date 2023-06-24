#ifndef TcpServerWidget_H
#define TcpServerWidget_H

#include <QWidget>
#include <QPushButton>

class TcpServerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TcpServerWidget(QWidget *parent);
private:
    QPushButton *startBtn;

signals:

};

#endif // TcpServerWidget_H
