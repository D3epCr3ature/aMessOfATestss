#include "dynamicdisplay.h"

DynamicDisplay::DynamicDisplay() : scene(new DisplayScene(this)) {}

void DynamicDisplay::setSceneRect(qreal x, qreal y, qreal w, qreal h) {
    scene->setSceneRect(x, y, w, h);
    this->setScene(scene);
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
