#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cipherwindow.h"
#include "decipherwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString action = ui->ActionBox->currentText();

    cw = new CipherWindow();
    dw = new DecipherWindow();

    if (action == "Cipher") {
        cw->show();
    } else {
        dw->show();
    }

    this->close();
}
