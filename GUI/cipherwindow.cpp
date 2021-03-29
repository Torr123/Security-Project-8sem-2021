#include "cipherwindow.h"
#include "ui_cipherwindow.h"
#include "mainwindow.h"

CipherWindow::CipherWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CipherWindow)
{
    ui->setupUi(this);
}

CipherWindow::~CipherWindow()
{
    delete ui;
}

void CipherWindow::on_pushButton_clicked()
{
    MainWindow *mw = new MainWindow();
    mw->show();

    this->close();
}
