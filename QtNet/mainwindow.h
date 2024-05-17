#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QNetworkInterface>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void GetLocalIPAddress();
    QByteArray HexStringToByteArray(QString HexString);
    void DataProc(QString tstr);
    void SendPara(void);

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpClient;
    QTcpServer *tcpServer;
    QList<QTcpSocket*> lstClient;
    QTcpSocket *currentClient;
    qint64 g_ptick;

private slots:
    void ReadData();
    void ReadError(QAbstractSocket::SocketError);

    void NewConnectionSlot();
    void disconnectedSlot();
    void ServerReadData();

    void on_BtnConn_clicked();
    void on_BtnClearRecv_clicked();
    void on_BtnSend_clicked();
    void on_radioClient_clicked();
    void on_radioServer_clicked();
    void on_rd_on_clicked();
    void on_rd_off_clicked();
    void on_spin_templmt_valueChanged(int arg1);
    void on_cmb_mpustep_currentIndexChanged(int index);
    void on_spin_warntime_valueChanged(int arg1);
    void on_spin_upstep_valueChanged(double arg1);
};

#endif // MAINWINDOW_H
