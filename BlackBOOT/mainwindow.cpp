/*

BlackBOOT

Copyright (c) <2019>, Marcellus Pereira <marcellus at laboratoriosacme.net>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the <project name> project.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    connect(ui->pbBrowseFiles, &QPushButton::clicked, this, &MainWindow::browseFiles );
    connect(ui->pbStart, &QPushButton::clicked, this, &MainWindow::sendData);

    const auto infos = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &info : infos)
        ui->cbPortSelection->addItem(info.portName());

    ui->statusBar->showMessage(tr("https://hackaday.io/project/162137-blackmath"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::browseFiles(void){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Firmware file"), "", tr("Loader files (*.ldr)"));

    ui->leFirmwarePath->setText(fileName);
}

int MainWindow::sendData(void){
    int errorCondition = 0;
    QSerialPort serialPort;

    serialPort.setPortName(ui->cbPortSelection->currentText());
    serialPort.setBaudRate(57600);

    if(serialPort.open(QIODevice::ReadWrite) == 0){
        ui->statusBar->showMessage(tr("Error opening serial port!\n"));
        errorCondition = 1;
    }
    else{
        // Envia '@'
        serialPort.putChar('@');

        //Aviso
        ui->statusBar->showMessage(tr("Sent: @\n"));

        //Recebe confirmação do Blackfin
        if(serialPort.waitForReadyRead(10000) == 0){
            //Erro lendo serial
            ui->statusBar->showMessage(tr("BlackMATH not responding. Please, try to reset the board!\n"));
            errorCondition = 1;
        }
        else{
            //Lê resposta da ROM BOOT
            QByteArray responseData = serialPort.readAll();
            while (serialPort.waitForReadyRead(1000)){
                responseData += serialPort.readAll();
            }

            QSerialPort::SerialPortError teste =serialPort.error();
            if(teste){
                serialPort.clearError();
            }


            ui->statusBar->showMessage(tr("Received " + responseData.toHex()+'\n'));

            //Pronto para enviar o programa
            //Lê bytes do disco
            QFile file(ui->leFirmwarePath->text());
            file.open(QIODevice::ReadOnly);
            QByteArray dadosParaSerial = file.readAll();
            file.close();

            //Configura barra de progresso
            ui->progressBar->setMaximum(static_cast <int>(file.size()));

            //Escreve na serial
            for(int i = 0; i < dadosParaSerial.size(); i++){
                serialPort.waitForBytesWritten(10);
                serialPort.putChar(dadosParaSerial.at(i));
                ui->progressBar->setValue(i);
                QThread::usleep(100);// msleep(1);
            }

            //Fim
            serialPort.waitForBytesWritten(10);
            serialPort.putChar(0);
            serialPort.close();
            ui->statusBar->showMessage(tr("All data sent.\n"));
            ui->progressBar->setValue(static_cast <int>(file.size()));
        }

    }

    return errorCondition;
}

