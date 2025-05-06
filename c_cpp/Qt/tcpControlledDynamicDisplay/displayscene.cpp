#include "displayscene.h"

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QStaticText>

DisplayScene::DisplayScene() : xRayOn(false) {}

DisplayScene::DisplayScene(QObject *parent) : QGraphicsScene(parent), xRayOn(false) {
    setBackgroundBrush(Qt::lightGray);
}

DisplayScene::~DisplayScene() {

}

/*void DisplayScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    /* Idea for making a preview * /
    if (mouseEvent->button() == Qt::LeftButton &&
        stripMode && inPreview) {
        drawLedPreviewTo(mouseEvent->scenePos()); // -> Use a 2nd QPixImage
    }
}*/

void DisplayScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton) {
        drawLedTo(mouseEvent->scenePos());
    }
}

void DisplayScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    /*if (mouseEvent->button() == Qt::LeftButton) {
        drawLedTo(mouseEvent->scenePos());
    }*/
}

void DisplayScene::drawLedTo(const QPointF &pos) {
    qreal radius = 50;
    qreal halfRadius = radius / 2;
    this->addEllipse(pos.x()-halfRadius, pos.y()-halfRadius, radius, radius, QPen(Qt::black), Qt::blue);
}
