#ifndef INDEXWIDGET_H
#define INDEXWIDGET_H

#include <QWidget>
#include <QPushButton>

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
    QPushButton *recordBtn;

};

#endif
