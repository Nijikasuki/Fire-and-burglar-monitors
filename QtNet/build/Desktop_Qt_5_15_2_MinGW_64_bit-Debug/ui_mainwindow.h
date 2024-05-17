/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *radioServer;
    QRadioButton *radioClient;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelAddr;
    QComboBox *EditIP;
    QLabel *label_2;
    QLineEdit *EditPort;
    QPushButton *BtnConn;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *EditRecv;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *chkHexDisp;
    QPushButton *BtnClearRecv;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QTextEdit *EditSend;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *chkHexSend;
    QPushButton *BtnSend;
    QSpacerItem *verticalSpacer_2;
    QComboBox *cbLstClients;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QLineEdit *edit_ay;
    QLabel *label_9;
    QLabel *label_7;
    QLineEdit *edit_pitch;
    QLabel *label_10;
    QLabel *label_8;
    QLineEdit *edit_ax;
    QLabel *label_12;
    QLineEdit *edit_gy;
    QLineEdit *edit_temp;
    QLineEdit *edit_gx;
    QLabel *label_4;
    QLabel *label_13;
    QLineEdit *edit_yaw;
    QLineEdit *edit_az;
    QLineEdit *edit_roll;
    QLabel *label_11;
    QLabel *label_5;
    QLineEdit *edit_gz;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *rd_on;
    QRadioButton *rd_off;
    QLineEdit *edit_warn;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_2;
    QLabel *label_17;
    QSpinBox *spin_templmt;
    QLabel *label_16;
    QDoubleSpinBox *spin_upstep;
    QLabel *label_15;
    QComboBox *cmb_mpustep;
    QLabel *label_14;
    QSpinBox *spin_warntime;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1126, 1032);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(20);
        font.setBold(false);
        label->setFont(font);
        label->setTextFormat(Qt::PlainText);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 50));
        QFont font1;
        font1.setPointSize(16);
        tabWidget->setFont(font1);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_5 = new QVBoxLayout(tab);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMaximumSize(QSize(16777215, 350));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_4 = new QGroupBox(groupBox_2);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        groupBox_4->setMinimumSize(QSize(10, 60));
        horizontalLayout_4 = new QHBoxLayout(groupBox_4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        radioServer = new QRadioButton(groupBox_4);
        radioServer->setObjectName(QString::fromUtf8("radioServer"));

        horizontalLayout_4->addWidget(radioServer);

        radioClient = new QRadioButton(groupBox_4);
        radioClient->setObjectName(QString::fromUtf8("radioClient"));

        horizontalLayout_4->addWidget(radioClient);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(groupBox_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        labelAddr = new QLabel(groupBox_2);
        labelAddr->setObjectName(QString::fromUtf8("labelAddr"));
        labelAddr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(labelAddr);

        EditIP = new QComboBox(groupBox_2);
        EditIP->setObjectName(QString::fromUtf8("EditIP"));
        EditIP->setEnabled(true);
        EditIP->setMinimumSize(QSize(200, 0));
        EditIP->setEditable(true);

        horizontalLayout_5->addWidget(EditIP);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_5->addWidget(label_2);

        EditPort = new QLineEdit(groupBox_2);
        EditPort->setObjectName(QString::fromUtf8("EditPort"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(EditPort->sizePolicy().hasHeightForWidth());
        EditPort->setSizePolicy(sizePolicy1);
        EditPort->setMinimumSize(QSize(200, 20));
        EditPort->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_5->addWidget(EditPort);


        verticalLayout->addLayout(horizontalLayout_5);


        horizontalLayout->addLayout(verticalLayout);

        BtnConn = new QPushButton(groupBox_2);
        BtnConn->setObjectName(QString::fromUtf8("BtnConn"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(BtnConn->sizePolicy().hasHeightForWidth());
        BtnConn->setSizePolicy(sizePolicy2);
        BtnConn->setMinimumSize(QSize(120, 0));
        BtnConn->setMaximumSize(QSize(10000, 16777215));

        horizontalLayout->addWidget(BtnConn);


        verticalLayout_5->addWidget(groupBox_2);

        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        EditRecv = new QTextEdit(groupBox);
        EditRecv->setObjectName(QString::fromUtf8("EditRecv"));
        EditRecv->setReadOnly(true);
        EditRecv->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        horizontalLayout_2->addWidget(EditRecv);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        chkHexDisp = new QCheckBox(groupBox);
        chkHexDisp->setObjectName(QString::fromUtf8("chkHexDisp"));

        verticalLayout_2->addWidget(chkHexDisp);

        BtnClearRecv = new QPushButton(groupBox);
        BtnClearRecv->setObjectName(QString::fromUtf8("BtnClearRecv"));
        BtnClearRecv->setMinimumSize(QSize(120, 0));

        verticalLayout_2->addWidget(BtnClearRecv);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_5->addWidget(groupBox);

        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(16777215, 150));
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        EditSend = new QTextEdit(groupBox_3);
        EditSend->setObjectName(QString::fromUtf8("EditSend"));

        horizontalLayout_3->addWidget(EditSend);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        chkHexSend = new QCheckBox(groupBox_3);
        chkHexSend->setObjectName(QString::fromUtf8("chkHexSend"));

        verticalLayout_3->addWidget(chkHexSend);

        BtnSend = new QPushButton(groupBox_3);
        BtnSend->setObjectName(QString::fromUtf8("BtnSend"));
        BtnSend->setMinimumSize(QSize(120, 0));

        verticalLayout_3->addWidget(BtnSend);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        cbLstClients = new QComboBox(groupBox_3);
        cbLstClients->setObjectName(QString::fromUtf8("cbLstClients"));
        cbLstClients->setMinimumSize(QSize(120, 0));

        verticalLayout_3->addWidget(cbLstClients);


        horizontalLayout_3->addLayout(verticalLayout_3);


        verticalLayout_5->addWidget(groupBox_3);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_6 = new QVBoxLayout(tab_2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        groupBox_5 = new QGroupBox(tab_2);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout = new QGridLayout(groupBox_5);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_3 = new QLabel(groupBox_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_3, 0, 2, 1, 1);

        edit_ay = new QLineEdit(groupBox_5);
        edit_ay->setObjectName(QString::fromUtf8("edit_ay"));
        edit_ay->setReadOnly(true);

        gridLayout_3->addWidget(edit_ay, 2, 1, 1, 1);

        label_9 = new QLabel(groupBox_5);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_9, 3, 2, 1, 1);

        label_7 = new QLabel(groupBox_5);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_7, 5, 0, 1, 1);

        edit_pitch = new QLineEdit(groupBox_5);
        edit_pitch->setObjectName(QString::fromUtf8("edit_pitch"));
        edit_pitch->setReadOnly(true);

        gridLayout_3->addWidget(edit_pitch, 4, 1, 1, 1);

        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_10, 2, 2, 1, 1);

        label_8 = new QLabel(groupBox_5);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_8, 4, 0, 1, 1);

        edit_ax = new QLineEdit(groupBox_5);
        edit_ax->setObjectName(QString::fromUtf8("edit_ax"));
        edit_ax->setReadOnly(true);

        gridLayout_3->addWidget(edit_ax, 1, 1, 1, 1);

        label_12 = new QLabel(groupBox_5);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_12, 4, 2, 1, 1);

        edit_gy = new QLineEdit(groupBox_5);
        edit_gy->setObjectName(QString::fromUtf8("edit_gy"));
        edit_gy->setReadOnly(true);

        gridLayout_3->addWidget(edit_gy, 3, 3, 1, 1);

        edit_temp = new QLineEdit(groupBox_5);
        edit_temp->setObjectName(QString::fromUtf8("edit_temp"));
        edit_temp->setReadOnly(true);

        gridLayout_3->addWidget(edit_temp, 0, 3, 1, 1);

        edit_gx = new QLineEdit(groupBox_5);
        edit_gx->setObjectName(QString::fromUtf8("edit_gx"));
        edit_gx->setReadOnly(true);

        gridLayout_3->addWidget(edit_gx, 1, 3, 1, 1);

        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_4, 1, 0, 1, 1);

        label_13 = new QLabel(groupBox_5);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_13, 5, 2, 1, 1);

        edit_yaw = new QLineEdit(groupBox_5);
        edit_yaw->setObjectName(QString::fromUtf8("edit_yaw"));
        edit_yaw->setReadOnly(true);

        gridLayout_3->addWidget(edit_yaw, 5, 1, 1, 1);

        edit_az = new QLineEdit(groupBox_5);
        edit_az->setObjectName(QString::fromUtf8("edit_az"));
        edit_az->setReadOnly(true);

        gridLayout_3->addWidget(edit_az, 3, 1, 1, 1);

        edit_roll = new QLineEdit(groupBox_5);
        edit_roll->setObjectName(QString::fromUtf8("edit_roll"));
        edit_roll->setReadOnly(true);

        gridLayout_3->addWidget(edit_roll, 4, 3, 1, 1);

        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_11, 1, 2, 1, 1);

        label_5 = new QLabel(groupBox_5);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_5, 2, 0, 1, 1);

        edit_gz = new QLineEdit(groupBox_5);
        edit_gz->setObjectName(QString::fromUtf8("edit_gz"));
        edit_gz->setReadOnly(true);

        gridLayout_3->addWidget(edit_gz, 2, 3, 1, 1);

        label_6 = new QLabel(groupBox_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_6, 3, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        rd_on = new QRadioButton(groupBox_5);
        rd_on->setObjectName(QString::fromUtf8("rd_on"));

        horizontalLayout_6->addWidget(rd_on);

        rd_off = new QRadioButton(groupBox_5);
        rd_off->setObjectName(QString::fromUtf8("rd_off"));

        horizontalLayout_6->addWidget(rd_off);


        gridLayout_3->addLayout(horizontalLayout_6, 0, 0, 1, 2);

        edit_warn = new QLineEdit(groupBox_5);
        edit_warn->setObjectName(QString::fromUtf8("edit_warn"));
        edit_warn->setReadOnly(true);

        gridLayout_3->addWidget(edit_warn, 5, 3, 1, 1);


        gridLayout->addLayout(gridLayout_3, 0, 0, 1, 1);


        verticalLayout_6->addWidget(groupBox_5);

        groupBox_6 = new QGroupBox(tab_2);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        gridLayout_2 = new QGridLayout(groupBox_6);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_17 = new QLabel(groupBox_6);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_17, 4, 0, 1, 1);

        spin_templmt = new QSpinBox(groupBox_6);
        spin_templmt->setObjectName(QString::fromUtf8("spin_templmt"));
        spin_templmt->setValue(30);

        gridLayout_2->addWidget(spin_templmt, 0, 1, 1, 1);

        label_16 = new QLabel(groupBox_6);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_16, 4, 2, 1, 1);

        spin_upstep = new QDoubleSpinBox(groupBox_6);
        spin_upstep->setObjectName(QString::fromUtf8("spin_upstep"));
        spin_upstep->setDecimals(1);
        spin_upstep->setMinimum(0.100000000000000);
        spin_upstep->setMaximum(10.000000000000000);
        spin_upstep->setSingleStep(0.100000000000000);

        gridLayout_2->addWidget(spin_upstep, 4, 3, 1, 1);

        label_15 = new QLabel(groupBox_6);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_15, 0, 2, 1, 1);

        cmb_mpustep = new QComboBox(groupBox_6);
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->addItem(QString());
        cmb_mpustep->setObjectName(QString::fromUtf8("cmb_mpustep"));

        gridLayout_2->addWidget(cmb_mpustep, 0, 3, 1, 1);

        label_14 = new QLabel(groupBox_6);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_14, 0, 0, 1, 1);

        spin_warntime = new QSpinBox(groupBox_6);
        spin_warntime->setObjectName(QString::fromUtf8("spin_warntime"));
        spin_warntime->setMaximum(60);
        spin_warntime->setValue(30);

        gridLayout_2->addWidget(spin_warntime, 4, 1, 1, 1);


        verticalLayout_6->addWidget(groupBox_6);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_3);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_4->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        cmb_mpustep->setCurrentIndex(7);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Qt\347\275\221\347\273\234\350\260\203\350\257\225\345\212\251\346\211\213 by 21041509\350\221\243\350\250\200 and 21041516\344\271\220\347\206\240", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\347\275\221\347\273\234\350\256\276\347\275\256", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\346\250\241\345\274\217\351\200\211\346\213\251", nullptr));
        radioServer->setText(QCoreApplication::translate("MainWindow", "TCP\346\234\215\345\212\241\345\231\250", nullptr));
        radioClient->setText(QCoreApplication::translate("MainWindow", "TCP\345\256\242\346\210\267\347\253\257", nullptr));
        labelAddr->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243\357\274\232", nullptr));
        EditPort->setText(QCoreApplication::translate("MainWindow", "6789", nullptr));
        BtnConn->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266\346\225\260\346\215\256", nullptr));
        chkHexDisp->setText(QCoreApplication::translate("MainWindow", "HEX\346\230\276\347\244\272", nullptr));
        BtnClearRecv->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\346\225\260\346\215\256", nullptr));
        chkHexSend->setText(QCoreApplication::translate("MainWindow", "HEX\345\217\221\351\200\201", nullptr));
        BtnSend->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\347\275\221\347\273\234\350\260\203\350\257\225", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "\347\233\221\346\265\213\346\225\260\346\215\256", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\270\251\345\272\246\357\274\232", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\350\247\222\351\200\237\345\272\246gz\357\274\232", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\350\210\252\345\220\221\350\247\222\357\274\232", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\350\247\222\351\200\237\345\272\246gy\357\274\232", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\344\277\257\344\273\260\350\247\222\357\274\232", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\346\250\252\346\273\232\350\247\222\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\212\240\351\200\237\345\272\246ax\357\274\232", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\346\212\245\350\255\246\347\212\266\346\200\201\357\274\232", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\350\247\222\351\200\237\345\272\246gx\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\345\212\240\351\200\237\345\272\246ay\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\345\212\240\351\200\237\345\272\246az\357\274\232", nullptr));
        rd_on->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250\344\270\212\344\274\240", nullptr));
        rd_off->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\344\270\212\344\274\240", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "\346\212\245\350\255\246\346\227\266\351\225\277\357\274\232", nullptr));
        spin_templmt->setSuffix(QCoreApplication::translate("MainWindow", "\342\204\203", nullptr));
        spin_templmt->setPrefix(QString());
        label_16->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\274\240\346\227\266\351\227\264\351\227\264\351\232\224\357\274\232", nullptr));
        spin_upstep->setSuffix(QCoreApplication::translate("MainWindow", "\347\247\222", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "\351\234\207\345\212\250\347\201\265\346\225\217\345\272\246\357\274\232", nullptr));
        cmb_mpustep->setItemText(0, QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
        cmb_mpustep->setItemText(1, QCoreApplication::translate("MainWindow", "1\347\272\247", nullptr));
        cmb_mpustep->setItemText(2, QCoreApplication::translate("MainWindow", "2\347\272\247", nullptr));
        cmb_mpustep->setItemText(3, QCoreApplication::translate("MainWindow", "3\347\272\247", nullptr));
        cmb_mpustep->setItemText(4, QCoreApplication::translate("MainWindow", "4\347\272\247", nullptr));
        cmb_mpustep->setItemText(5, QCoreApplication::translate("MainWindow", "5\347\272\247", nullptr));
        cmb_mpustep->setItemText(6, QCoreApplication::translate("MainWindow", "6\347\272\247", nullptr));
        cmb_mpustep->setItemText(7, QCoreApplication::translate("MainWindow", "7\347\272\247", nullptr));
        cmb_mpustep->setItemText(8, QCoreApplication::translate("MainWindow", "8\347\272\247", nullptr));
        cmb_mpustep->setItemText(9, QCoreApplication::translate("MainWindow", "9\347\272\247", nullptr));

        label_14->setText(QCoreApplication::translate("MainWindow", "\346\270\251\345\272\246\344\270\212\351\231\220\357\274\232", nullptr));
        spin_warntime->setSuffix(QCoreApplication::translate("MainWindow", "\347\247\222", nullptr));
        spin_warntime->setPrefix(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\351\230\262\347\201\253\351\230\262\347\233\227\347\233\221\346\265\213\345\231\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
