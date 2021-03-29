#include "decipherwindow.h"
#include "ui_decipherwindow.h"

DecipherWindow::DecipherWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DecipherWindow)
{
    ui->setupUi(this);
}

DecipherWindow::~DecipherWindow()
{
    delete ui;
}
