#include "dynamicdisplay.h"

DynamicDisplay::DynamicDisplay() : scene(new DisplayScene(this)) {}

void DynamicDisplay::setSceneRect(qreal x, qreal y, qreal w, qreal h) {
    scene->setSceneRect(x, y, w, h);
    this->setScene(scene);
}

void DynamicDisplay::setLedColor(int idx, QColor color) {
    scene->setLedAtIndex(idx, color.red(), color.green(), color.blue());
}

size_t DynamicDisplay::getNumberOfLeds() {
    return scene->getNumberOfLeds();
}

/*void DynamicDisplay::mouseMoveEvent(QMouseEvent *event) {
    /* Idea for making a preview * /
    if (mouseEvent->button() == Qt::LeftButton &&
        stripMode && inPreview) {
        drawLedPreviewTo(mouseEvent->scenePos()); // -> Use a 2nd QPixImage
    }
}* /

void DynamicDisplay::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        scene->drawLedTo(event->scenePosition());
    }
}

void DynamicDisplay::mouseReleaseEvent(QMouseEvent *event) {
    /*if (mouseEvent->button() == Qt::LeftButton) {
        drawLedTo(mouseEvent->scenePos());
    }* /
}*/

//void DynamicDisplay::paintEvent(QPaintEvent *pQEvent) {
void DynamicDisplay::updateScene() {
    static int i = 0;
    for (i = 0; i < scene->getNumberOfLeds(); i++) {
        auto led = scene->getLedAtIndex(i);
        auto color = QColor(led.color.r, led.color.g, led.color.b);
        scene->addEllipse(led.position.x, led.position.y, led.radius, led.radius, QPen(Qt::black), color);
    }
}
