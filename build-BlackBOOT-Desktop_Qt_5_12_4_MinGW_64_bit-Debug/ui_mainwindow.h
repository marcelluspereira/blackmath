/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *leFirmwarePath;
    QPushButton *pbBrowseFiles;
    QPushButton *pbStart;
    QComboBox *cbPortSelection;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(605, 338);
        MainWindow->setIconSize(QSize(96, 96));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(210, 20, 161, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("Malgun Gothic"));
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 110, 71, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 170, 61, 16));
        leFirmwarePath = new QLineEdit(centralWidget);
        leFirmwarePath->setObjectName(QString::fromUtf8("leFirmwarePath"));
        leFirmwarePath->setGeometry(QRect(110, 170, 201, 20));
        leFirmwarePath->setCursor(QCursor(Qt::BlankCursor));
        pbBrowseFiles = new QPushButton(centralWidget);
        pbBrowseFiles->setObjectName(QString::fromUtf8("pbBrowseFiles"));
        pbBrowseFiles->setGeometry(QRect(340, 170, 75, 23));
        pbStart = new QPushButton(centralWidget);
        pbStart->setObjectName(QString::fromUtf8("pbStart"));
        pbStart->setGeometry(QRect(450, 100, 111, 91));
        cbPortSelection = new QComboBox(centralWidget);
        cbPortSelection->setObjectName(QString::fromUtf8("cbPortSelection"));
        cbPortSelection->setGeometry(QRect(110, 110, 111, 22));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(40, 240, 531, 23));
        progressBar->setValue(0);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 605, 17));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "BlackBOOT", nullptr));
        label->setText(QApplication::translate("MainWindow", "BlackBOOT", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Serial Port:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Firmware:", nullptr));
        pbBrowseFiles->setText(QApplication::translate("MainWindow", "Browse", nullptr));
        pbStart->setText(QApplication::translate("MainWindow", "START", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
