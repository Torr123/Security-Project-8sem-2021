#ifndef CIPHERWINDOW_H
#define CIPHERWINDOW_H

#include <QDialog>

namespace Ui {
class CipherWindow;
}

class CipherWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CipherWindow(QWidget *parent = nullptr);
    ~CipherWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CipherWindow *ui;
};

#endif // CIPHERWINDOW_H
