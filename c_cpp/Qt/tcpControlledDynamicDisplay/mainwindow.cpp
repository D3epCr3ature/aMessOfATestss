#include "mainwindow.h"

#include <QGraphicsView>

#include "displayscene.h"

//MainWindow::MainWindow(QDialog *parent) : QDialog(parent) {
MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    display = new DynamicDisplay;

    lblNbrOfLeds      = new QLabel(QString("Number of LEDs: %1").arg(0));
    //lblNbrOfLeds      = new QLabel(QString("Number of LEDs: %1").arg(display->getNumberOfLeds()));

    lblLedIdxToModify     = new QLabel("LED to modify:");
    spinBoxLedIdxToModify = new QSpinBox;
    spinBoxLedIdxToModify->setValue(0);

    btnApplyLedModif = new QPushButton("Apply color");
    sliderRed   = new QSlider(Qt::Orientation::Horizontal);
    sliderRed->setStyleSheet("QSlider::handle:horizontal {background-color: red;}");
    sliderRed->setMaximum(255);
    sliderRed->setMinimum(0);
    sliderGreen = new QSlider(Qt::Orientation::Horizontal);
    sliderGreen->setStyleSheet("QSlider::handle:horizontal {background-color: green;}");
    sliderGreen->setMaximum(255);
    sliderGreen->setMinimum(0);
    sliderBlue  = new QSlider(Qt::Orientation::Horizontal);
    sliderBlue->setStyleSheet("QSlider::handle:horizontal {background-color: blue;}");
    sliderBlue->setMaximum(255);
    sliderBlue->setMinimum(0);

    display->setSceneDimensions(lblLedIdxToModify->pos().x(),
                                lblLedIdxToModify->pos().y() * 2 + lblLedIdxToModify->height(),
                                600, 600);
    display->setMinimumSize(300, 300);

    lblTest = new QLabel("TESTING LABEL");

    // QMainWindow's approach (default QMainWindow's layout)
    //setCentralWidget((QGraphicsView *) display);
    // QDialog/QWidget's approach (custom layout)
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(lblNbrOfLeds, 0, 0, 1, 2);
    mainLayout->addWidget(lblLedIdxToModify, 0, 2, 1, 1);
    mainLayout->addWidget(spinBoxLedIdxToModify, 0, 3, 1, 1);
    mainLayout->addWidget(btnApplyLedModif, 0, 4, 1, 1);
    mainLayout->addWidget(display, 1, 0, 4, 4);
    mainLayout->addWidget(sliderRed  , 1, 4, 1, 1);
    mainLayout->addWidget(sliderGreen, 2, 4, 1, 1);
    mainLayout->addWidget(sliderBlue , 3, 4, 1, 1);
    mainLayout->addWidget(lblTest, 4, 4, 1, 1);

    /*connect(this, &MainWindow::mousePressEvent, this, [=](QMouseEvent *evt) {
        lblNbrOfLeds->setText(QString("Number of LEDs: %1").arg(display->getNumberOfLeds()));
    });*/

    connect(btnApplyLedModif, &QPushButton::clicked, this, [=](bool state) {
        display->setLedColor(spinBoxLedIdxToModify->value(),
                             QColor(sliderRed->value(),
                                    sliderGreen->value(),
                                    sliderBlue->value()));

        display->updateScene();
    });
}

MainWindow::~MainWindow() {}

void MainWindow::paintEvent(QPaintEvent *pQEvent) {
    display->updateScene();
}
