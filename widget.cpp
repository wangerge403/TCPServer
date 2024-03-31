#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("tcp服务");

    tcpServer = new QTcpServer(this);   //获取套接字
    tcpSocket = new QTcpSocket(this);

    // 客户端连接成功会发送newConnection()信号
    connect(tcpServer, &QTcpServer::newConnection, this, &Widget::newConnection_Slot);
    // connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection_Slot()));
}

Widget::~Widget()
{
    delete ui;
}


// 连接
void Widget::newConnection_Slot()
{
    while(tcpServer->hasPendingConnections())
    {
        tcpSocket = tcpServer->nextPendingConnection();
        qDebug() << "连接:" << tcpSocket;
        connect(tcpSocket, &QTcpSocket::readyRead, this, &Widget::readyRead_Slot);
    }
}

// 读取并显示到接收窗口
void Widget::readyRead_Slot()
{
    QByteArray buf = tcpSocket->readAll();
    QString message = QString::fromUtf8(buf);
    ui->receiveEdit->appendPlainText(message); // 追加到窗口
}
// 服务器开启
void Widget::on_openServer_button__clicked()
{
    bool result = tcpServer->listen(QHostAddress::Any, ui->portEdit->text().toUInt());
    if(result) {

        ui->connectState->setStyleSheet("QLabel {color: green}");
        ui->connectState->setText("开启成功！");

    } else {

        ui->connectState->setStyleSheet("QLabel {color: red}");
        ui->connectState->setText("开启失败！");

    }
}

// 关闭服务
void Widget::on_closeServer_button_clicked()
{
    tcpServer->close();
    if(!tcpServer->isListening()) {
        ui->connectState->setStyleSheet("QLabel {color: green}");
        ui->connectState->setText("已断开");
    } else {
        ui->connectState->setStyleSheet("QLabel {color: red}");
        ui->connectState->setText("断开失败");
    }
}


//发送数据
void Widget::on_send_button_clicked()
{
    // if()
    QByteArray data = ui->dataInfoEdit->text().toUtf8(); // 将字符串转换为UTF-8编码
    tcpSocket->write(data);
}


