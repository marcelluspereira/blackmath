#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QtSerialPort/QSerialPort>
#include <QList>
#include <QByteArray>
#include <QComboBox>
#include <QDataStream>
#include <QTimer>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void browseFiles(void);
    int sendData(void);
};

#endif // MAINWINDOW_H
