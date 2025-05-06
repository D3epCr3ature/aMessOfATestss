#include "mainwindow.h"

#include <QGraphicsView>

#include "dynamicdisplay.h"

#include "structure/display.h"

//MainWindow::MainWindow(QDialog *parent) : QDialog(parent) {
MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    display = new DynamicDisplay;

    lblNbrOfLeds = new QLabel(QString("Number of LEDs: %1").arg(display->getNumberOfLeds()));

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

    display->setSceneRect(lblLedIdxToModify->pos().x(),
                          lblLedIdxToModify->pos().y() * 2 + lblLedIdxToModify->height(),
                          2000, 2000);
    display->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    display->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    display->setMinimumSize(300, 300);

    sliderZoom = new QSlider(Qt::Orientation::Horizontal);
    sliderZoom->setMaximum(20);
    sliderZoom->setMinimum( 1);
    sliderZoom->setValue(10);

    xRayCheckBox = new QCheckBox("X-Ray");

    display->scale(sliderZoom->value() / 10, sliderZoom->value() / 10);

    openButton = new QPushButton("Open display");
    saveButton = new QPushButton("Save display");

    // QMainWindow's approach (default QMainWindow's layout)
    //setCentralWidget((QGraphicsView *) display);
    // QDialog/QWidget's approach (custom layout)

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(lblNbrOfLeds, 0, 0, 1, 2);
    mainLayout->addWidget(lblLedIdxToModify, 0, 2, 1, 1);
    mainLayout->addWidget(spinBoxLedIdxToModify, 0, 3, 1, 1);
    mainLayout->addWidget(btnApplyLedModif, 0, 4, 1, 1);
    mainLayout->addWidget(display, 1, 0, 10, 4);
    mainLayout->addWidget(sliderRed  , 1, 4, 1, 1);
    mainLayout->addWidget(sliderGreen, 2, 4, 1, 1);
    mainLayout->addWidget(sliderBlue , 3, 4, 1, 1);
    mainLayout->addWidget(openButton, 5, 4, 1, 1);
    mainLayout->addWidget(saveButton, 6, 4, 1, 1);
    mainLayout->addWidget(sliderZoom, 11, 0, 1, 4);
    mainLayout->addWidget(xRayCheckBox, 11, 4, 1, 1);

    lblTest = new QLabel("TESTING LABEL");
    mainLayout->addWidget(lblTest, 8, 4, 1, 1);

    connect(sliderZoom, &QSlider::valueChanged, this, [=](int value) {
        static int oldValue = 10;
        static double newScale = 0.0;
        newScale = 1 + (sliderZoom->value() - oldValue) / 10.0;
        display->scale(newScale, newScale);
        display->show();

        lblTest->setText(QString("Slider: %1 | newScale = %2").arg(sliderZoom->value()).arg(newScale));
        oldValue = sliderZoom->value();
    });

    connect(xRayCheckBox, &QCheckBox::checkStateChanged, this, [=](Qt::CheckState state){
        display->toggleXRay();
        display->updateScene();
    });

    connect(btnApplyLedModif, &QPushButton::clicked, this, [=](bool state) {
        display->setLedColor(spinBoxLedIdxToModify->value(),
                             QColor(sliderRed->value(),
                                    sliderGreen->value(),
                                    sliderBlue->value()));

        display->updateScene();
    });

    connect(openButton, &QPushButton::clicked, this, [=](bool state) {
        struct LEDDisplay tmp;
        if ( ! openDisplay(tmp) ) {
            return;
        }

        display->setDisplay(tmp);
        display->updateScene();
    });

    connect(saveButton, &QPushButton::clicked, this, [=](bool state) {
        saveDisplay(display->getDisplay());
    });
}

MainWindow::~MainWindow() {}

void MainWindow::paintEvent(QPaintEvent *pQEvent) {
    lblNbrOfLeds->setText(QString("Number of LEDs: %1").arg(display->getNumberOfLeds()));

    //display->updateScene();
    spinBoxLedIdxToModify->setMaximum(display->getNumberOfLeds());
}
