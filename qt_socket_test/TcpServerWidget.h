#ifndef TcpServerWidget_H
#define TcpServerWidget_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

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

signals:

};

#endif // TcpServerWidget_H
