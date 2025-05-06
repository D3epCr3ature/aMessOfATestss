#ifndef __MAIN__WINDOW_H__
#define __MAIN__WINDOW_H__

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>

#include "dynamicdisplay.h"

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QDialog *parent = nullptr);
    ~MainWindow();

private:
    QLabel *lblNbrOfLeds = nullptr;

    QLabel *lblLedIdxToModify       = nullptr;
    QSpinBox *spinBoxLedIdxToModify = nullptr;

    DynamicDisplay *display = nullptr;

    QGridLayout *mainLayout;
};

#endif // __MAIN__WINDOW_H__
