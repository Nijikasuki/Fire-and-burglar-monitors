#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QFile>
#include <QStandardPaths>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpClient = new QTcpSocket(this);
    tcpClient->abort();
    connect(tcpClient, SIGNAL(readyRead()), SLOT(ReadData()));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(ReadError(QAbstractSocket::SocketError)));

    QString tempDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    QFile file(tempDir + "\\conf.ini");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();
    QString str(t);
    file.close();
    if (!t.isEmpty())
    {
        QStringList lst = str.split(":");
        if (lst.size() == 2)
        {
            ui->EditIP->setEditText(lst[0]);
            ui->EditPort->setText(lst[1]);
        }
    }

//    tcpClient->connectToHost(ui->EditIP->text(), ui->EditPort->text().toUShort());
//    if (tcpClient->waitForConnected(1000))  // 连接成功则进入if{}
//    {
//        ui->BtnConn->setText("断开连接");
//        ui->BtnSend->setEnabled(true);
//    }
//    else
//    {
//        ui->BtnConn->setText("连接服务器");
//        ui->BtnSend->setEnabled(false);
//    }

    ui->BtnConn->setText("连接服务器");
    ui->BtnSend->setEnabled(false);
    ui->radioClient->setChecked(true);

    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(NewConnectionSlot()));
    ui->cbLstClients->setVisible(false);

    g_ptick = 0;
//    showMaximized();
}

MainWindow::~MainWindow()
{
    if (tcpServer->isListening()) {
        for(int i = lstClient.length() - 1; i >= 0; --i) //断开所有连接
        {
            lstClient[i]->disconnectFromHost();
            lstClient.removeAt(i);  //从保存的客户端列表中取去除
        }
        tcpServer->close();     //不再监听端口
    }

    if (tcpClient->state() == QAbstractSocket::ConnectedState)
    {
        tcpClient->abort();
        tcpClient->disconnectFromHost();
        tcpClient->close();
    }
    delete ui;
}

void MainWindow::GetLocalIPAddress()
{
    ui->EditIP->clear();

    QList<QHostAddress> lst = QNetworkInterface().allAddresses();
    for (int i = 0; i < lst.size(); ++i)
    {
        QHostAddress tha = lst[i];
        QString tstr = tha.toString();
        if (tha.isNull() || tha.isLoopback() || tha.protocol() != QAbstractSocket::IPv4Protocol ||
            (tha.toIPv4Address() & 0xFF) == 1)
            continue;
        else
        {
//            ui->EditIP->setEditText(lst[i].toString());   // 显示本地IP地址
//            break;
            ui->EditIP->addItem(tstr);
        }
    }
}

QByteArray MainWindow::HexStringToByteArray(QString HexString)
{
    bool ok;
    QByteArray ret;
    HexString = HexString.trimmed();
    HexString = HexString.simplified();
    QStringList sl = HexString.split(" ");

    foreach (QString s, sl) {
        if(!s.isEmpty())
        {
            uint32_t td = s.toUInt(&ok, 16);
            int pos = ret.size();
            if (ok)
            {
                do {
                    ret.insert(pos, td & 0xFF);
//                    ret.append(td & 0xFF);
                    td >>= 8;
                }while(td > 0);
            }
        }
    }
    qDebug()<<ret;
    return ret;
}

void MainWindow::DataProc(QString tstr)
{
    QStringList tlist = tstr.split(QRegExp("[:, ]"), QString::SkipEmptyParts);
    if (tstr.startsWith("T:") && tstr.length() > 30)
    {

        for (int i = 0; i < tlist.count(); ++i)
        {
            QString ss = tlist[i];

            if (ss.compare("T") == 0 && i + 1 < tlist.count())
            {
                //            float temp = tlist[i + 1].toFloat();
                ui->edit_temp->setText(tlist[i + 1]);
                ++i;
            }
            else if (ss.compare("A") == 0 && i + 3 < tlist.count())
            {
                ui->edit_ax->setText(tlist[i + 1]);
                ui->edit_ay->setText(tlist[i + 2]);
                ui->edit_az->setText(tlist[i + 3]);
                i += 3;
            }
            else if (ss.compare("G") == 0 && i + 3 < tlist.count())
            {
                ui->edit_gx->setText(tlist[i + 1]);
                ui->edit_gy->setText(tlist[i + 2]);
                ui->edit_gz->setText(tlist[i + 3]);
                i += 3;
            }
            else if (ss.compare("F") == 0 && i + 3 < tlist.count())
            {
                ui->edit_pitch->setText(tlist[i + 1]);
                ui->edit_roll->setText(tlist[i + 2]);
                ui->edit_yaw->setText(tlist[i + 3]);
                i += 3;
            }
            else if (i + 1 < tlist.count())
            {
                int type = tlist[i + 1].toInt();
                switch (type) {
                default:
                    ui->edit_warn->setText("无");
                    break;
                case 1:
                    ui->edit_warn->setText("温度报警");
                    break;
                case 2:
                    ui->edit_warn->setText("震动报警");
                    break;
                case 3:
                    ui->edit_warn->setText("温度、震动报警");
                    break;
                }
                ++i;
            }
        }
    }
    else if (tstr.startsWith("P:") && tlist.count() == 5)
    {
        int templmt, level, warnlen, upstep;
        templmt = tlist[1].toUInt();
        level = tlist[2].toUInt();
        warnlen = tlist[3].toUInt();
        upstep = tlist[4].toUInt();
        if ((templmt >= 0 && templmt <= 90) &&
            (level >= 0 && level <= 9) &&
            (warnlen >= 0 && warnlen <= 60) &&
            (upstep >= 100 && upstep <= 10000))
        {
            g_ptick = QDateTime::currentMSecsSinceEpoch() + 500;

            ui->spin_templmt->setValue(templmt);
            ui->cmb_mpustep->setCurrentIndex(level);
            ui->spin_warntime->setValue(warnlen);
            ui->spin_upstep->setValue(upstep / 1000.0);
        }
    }
}

void MainWindow::SendPara()
{
    if (QDateTime::currentMSecsSinceEpoch() > g_ptick)
    {
        int templmt = ui->spin_templmt->value();
        int level = ui->cmb_mpustep->currentIndex ( );
        int warnlen = ui->spin_warntime->value();
        int upstep = ui->spin_upstep->value() * 1000;

        QString tstr = QString::asprintf("PSET:%d,%d,%d,%d\n", templmt, level, warnlen, upstep);
        ui->EditSend->setText(tstr);
        on_BtnSend_clicked();
    }
}

void MainWindow::ReadData()
{
    QByteArray buffer = tcpClient->readAll();
    if(!buffer.isEmpty())
    {
        ui->EditRecv->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
//        ui->EditRecv->append(buffer);
        if (ui->chkHexDisp->isChecked())
        {
            QString tstr, t;
            for (int i = 0; i < buffer.size(); ++i)
            {
                t.asprintf("%02X ", buffer.data()[i]);
                tstr += t;
            }
            ui->EditRecv->insertPlainText(tstr);
        }
        else
        {
            QString tstr =QString(buffer);
            ui->EditRecv->insertPlainText(tstr);
            DataProc(tstr);
        }
    }
}

void MainWindow::ReadError(QAbstractSocket::SocketError)
{
    tcpClient->disconnectFromHost();
    ui->BtnConn->setText(tr("连接服务器"));
    ui->EditRecv->append(tr("服务器连接错误：%1").arg(tcpClient->errorString()));
    ui->BtnSend->setEnabled(false);
}

void MainWindow::NewConnectionSlot()
{
    currentClient = tcpServer->nextPendingConnection();
    lstClient.append(currentClient);
    connect(currentClient, SIGNAL(readyRead()), this, SLOT(ServerReadData()));
    connect(currentClient, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));

    if (ui->cbLstClients->count() == 0)
        ui->cbLstClients->addItem("全部连接");
    ui->cbLstClients->addItem(currentClient->peerAddress().toString());
    if (ui->cbLstClients->count() > 0)
        ui->BtnSend->setEnabled(true);

    QThread::msleep(500);
    ui->EditSend->setText("GETPARA\n");
    on_BtnSend_clicked();
}

void MainWindow::disconnectedSlot()
{
    for(int i = lstClient.length() - 1; i >= 0; --i)
    {
        if(lstClient[i]->state() == QAbstractSocket::UnconnectedState)
        {
            // 删除存储在combox中的客户端信息
            ui->cbLstClients->removeItem(ui->cbLstClients->findText(lstClient[i]->peerAddress().toString()));
            // 删除存储在tcpClient列表中的客户端信息
            lstClient[i]->destroyed();
            lstClient.removeAt(i);
        }
    }
    if (ui->cbLstClients->count() == 1)
    {
        ui->cbLstClients->clear();
        ui->BtnSend->setEnabled(false);
    }
}

void MainWindow::ServerReadData()
{
    // 由于readyRead信号并未提供SocketDecriptor，所以需要遍历所有客户端
    static QString IP_Port, IP_Port_Pre;
    for(int i = 0; i < lstClient.length(); ++i)
    {
        QByteArray buffer = lstClient[i]->readAll();
        if(buffer.isEmpty())
            continue;

        ui->EditRecv->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
        IP_Port = tr("[%1:%2]:").arg(lstClient[i]->peerAddress().toString()).arg(lstClient[i]->peerPort());

        // 若此次消息的地址与上次不同，则需显示此次消息的客户端地址
        if(IP_Port != IP_Port_Pre)
            ui->EditRecv->append(IP_Port);

        if (ui->chkHexDisp->isChecked())
        {
            QString tstr, t;
            for (int i = 0; i < buffer.size(); ++i)
            {
                t.asprintf("%02X ", buffer.data()[i]);
                tstr += t;
            }
            ui->EditRecv->insertPlainText(tstr);
        }
        else
        {
            QString tstr = QString(buffer);
            ui->EditRecv->insertPlainText(tstr);
            DataProc(tstr);
        }

        //更新ip_port
        IP_Port_Pre = IP_Port;
    }
}

void MainWindow::on_BtnConn_clicked()
{
    if (ui->radioClient->isChecked())
    {
        if (tcpClient->state() == QAbstractSocket::ConnectedState)
        {
            tcpClient->disconnectFromHost();    // 断开连接
            if (tcpClient->state() == QAbstractSocket::UnconnectedState || tcpClient->waitForDisconnected(1000))
            {
                ui->BtnConn->setText("连接服务器");
                ui->BtnSend->setEnabled(false);
            }
        }
        else
        {
            tcpClient->connectToHost(ui->EditIP->currentText(), ui->EditPort->text().toUShort());
            if (tcpClient->waitForConnected(1000))  // 连接成功则进入if{}
            {
                QString tempDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
                QFile file(tempDir + "\\conf.ini");
                file.open(QIODevice::WriteOnly | QIODevice::Text);
                file.write((ui->EditIP->currentText() + ":" + ui->EditPort->text()).toUtf8());
                file.close();
                ui->BtnConn->setText("断开连接");
                ui->BtnSend->setEnabled(true);
            }
            else
            {
                ui->EditRecv->append(tr("服务器连接错误：%1").arg(tcpClient->errorString()));
            }
        }
    }
    else
    {
        ui->cbLstClients->clear();
        if (tcpServer->isListening()) {
            for(int i = lstClient.length() - 1; i >= 0; --i) //断开所有连接
            {
                QTcpSocket *tt = lstClient.at(i);
                tt->disconnectFromHost();
                if (tt->state() == QAbstractSocket::UnconnectedState || tt->waitForDisconnected(1000))
                {
                 // 处理异常
                }
                lstClient.removeAt(i);  //从保存的客户端列表中取去除
            }
            tcpServer->close();     //不再监听端口
            ui->cbLstClients->clear();
            ui->BtnConn->setText("开始侦听");
            ui->BtnSend->setEnabled(false);
        }
        else {
            bool ok = tcpServer->listen(QHostAddress::AnyIPv4, ui->EditPort->text().toUShort());
            if(ok)
            {
                ui->BtnConn->setText("断开连接");
                ui->BtnSend->setEnabled(false);
            }
        }
    }
}

void MainWindow::on_BtnClearRecv_clicked()
{
    ui->EditRecv->clear();
}

void MainWindow::on_BtnSend_clicked()
{
    QString data = ui->EditSend->toPlainText();
    QByteArray tba;
    if (ui->chkHexSend->isChecked())
        tba = HexStringToByteArray(data);
    else
        tba = data.toLatin1();
    if (ui->radioClient->isChecked())
    {
        if(!data.isEmpty())
        {
            tcpClient->write(tba);
        }
    }
    else {
        //全部连接
        if(ui->cbLstClients->currentIndex() == 0)
        {
            for(int i=0; i < lstClient.length(); i++)
                lstClient[i]->write(tba);
        }
        else {
            QString clientIP = ui->cbLstClients->currentText();
            for(int i=0; i < lstClient.length(); i++)
            {
                if(lstClient[i]->peerAddress().toString() == clientIP)
                {
                    lstClient[i]->write(tba);
                    return; //ip:port唯一，无需继续检索
                }
            }
        }
    }
}

void MainWindow::on_radioClient_clicked()
{
    if (tcpClient->state() == QAbstractSocket::ConnectedState)
        return;

    // 服务器断开
    if (tcpServer->isListening())
    {
        for(int i = lstClient.size() - 1; i >= 0; --i) //断开所有连接
        {
            QTcpSocket *tt = lstClient.at(i);
            tt->disconnectFromHost();
            if (tt->state() == QAbstractSocket::UnconnectedState || tt->waitForDisconnected(1000))
            {

            }
            lstClient.removeAt(i);  //从保存的客户端列表中取去除
        }
        tcpServer->close();     //不再监听端口
    }
    ui->cbLstClients->clear();
    ui->cbLstClients->setVisible(false);
    ui->labelAddr->setText("服务器地址：");

    // 加载远程服务器地址、端口
    QString tempDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    QFile file(tempDir + "\\conf.ini");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();
    QString str(t);
    file.close();
    if (!t.isEmpty())
    {
        QStringList lst = str.split(":");
        if (lst.size() == 2)
        {
            ui->EditIP->setEditText(lst[0]);
            ui->EditPort->setText(lst[1]);
        }
    }

    if (tcpClient->state() == QAbstractSocket::UnconnectedState)
    {
        ui->BtnConn->setText("连接服务器");
        ui->BtnSend->setEnabled(false);
    }
    else {
        ui->BtnConn->setText("断开连接");
        ui->BtnSend->setEnabled(true);
    }
}

void MainWindow::on_radioServer_clicked()
{
    if (tcpServer->isListening())
        return;

    // 断开客户端
    tcpClient->disconnectFromHost();    // 断开连接
    if (tcpClient->state() == QAbstractSocket::UnconnectedState || tcpClient->waitForDisconnected(1000))
    {

    }

    // 获取本地IP地址
    GetLocalIPAddress();
    ui->BtnConn->setText("开始侦听");
    ui->BtnSend->setEnabled(false);

    ui->cbLstClients->clear();
    ui->cbLstClients->setVisible(true);
    ui->labelAddr->setText("本机地址：");
}

void MainWindow::on_rd_on_clicked()
{
    ui->EditSend->setText("UPON\n");
    on_BtnSend_clicked( );
}

void MainWindow::on_rd_off_clicked()
{
    ui->EditSend->setText("UPOFF\n");
    on_BtnSend_clicked();
}

void MainWindow::on_spin_templmt_valueChanged(int arg1)
{
    SendPara();
}

void MainWindow::on_cmb_mpustep_currentIndexChanged(int index)
{
    SendPara();
}

void MainWindow::on_spin_warntime_valueChanged(int arg1)
{
    SendPara();
}

void MainWindow::on_spin_upstep_valueChanged(double arg1)
{
    SendPara();
}
