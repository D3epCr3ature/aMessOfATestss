#include "mainwindow.h"

#include <QGraphicsView>

#include "displayscene.h"

MainWindow::MainWindow(QDialog *parent) : QDialog(parent) {
    display = new DynamicDisplay;

    lblNbrOfLeds      = new QLabel(QString("Number of LEDs: %1").arg(0));
    //lblNbrOfLeds      = new QLabel(QString("Number of LEDs: %1").arg(display->getNumberOfLeds()));

    lblLedIdxToModify     = new QLabel("LED to modify:");
    spinBoxLedIdxToModify = new QSpinBox;
    spinBoxLedIdxToModify->setValue(0);

    display->setSceneRect(lblLedIdxToModify->pos().x(),
                          lblLedIdxToModify->pos().y() * 2 + lblLedIdxToModify->height(),
                          600, 600);
    display->setMinimumSize(300, 300);

    // QMainWindow's approach (default QMainWindow's layout)
    //setCentralWidget((QGraphicsView *) display);
    // QDialog/QWidget's approach (custom layout)
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(lblNbrOfLeds, 0, 0, 1, 2);
    mainLayout->addWidget(lblLedIdxToModify, 0, 2, 1, 1);
    mainLayout->addWidget(spinBoxLedIdxToModify, 0, 3, 1, 1);
    mainLayout->addWidget(display, 1, 0, 1, 4);
}

MainWindow::~MainWindow() {}
