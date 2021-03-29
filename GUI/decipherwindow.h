#ifndef DECIPHERWINDOW_H
#define DECIPHERWINDOW_H

#include <QDialog>

namespace Ui {
class DecipherWindow;
}

class DecipherWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DecipherWindow(QWidget *parent = nullptr);
    ~DecipherWindow();

private:
    Ui::DecipherWindow *ui;
};

#endif // DECIPHERWINDOW_H
