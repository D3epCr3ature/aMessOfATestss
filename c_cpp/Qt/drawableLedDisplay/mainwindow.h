#ifndef __MAIN__WINDOW_H__
#define __MAIN__WINDOW_H__

//#include <QDialog>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QCheckBox>

#include "dynamicdisplay.h"

//class MainWindow : public QDialog
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void paintEvent(QPaintEvent *pQEvent) override;

private:
    QLabel *lblNbrOfLeds = nullptr;

    QLabel *lblLedIdxToModify       = nullptr;
    QSpinBox *spinBoxLedIdxToModify = nullptr;

    QPushButton *btnApplyLedModif   = nullptr;
    QSlider     *sliderRed   = nullptr;
    QSlider     *sliderGreen = nullptr;
    QSlider     *sliderBlue  = nullptr;

    DynamicDisplay *display = nullptr;
    QSlider     *sliderZoom = nullptr;
    QCheckBox   *xRayCheckBox = nullptr;

    QPushButton *openButton = nullptr;
    QPushButton *saveButton = nullptr;

    QGridLayout *mainLayout;

    QLabel *lblTest = nullptr;
};

#endif // __MAIN__WINDOW_H__
