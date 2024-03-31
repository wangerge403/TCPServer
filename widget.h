#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:  //槽函数声明
    void newConnection_Slot();

    void on_closeServer_button_clicked();

    void readyRead_Slot();

    void on_send_button_clicked();

    void on_openServer_button__clicked();

private:
    Ui::Widget *ui;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket; // 套接字声明
};

#endif // WIDGET_H
