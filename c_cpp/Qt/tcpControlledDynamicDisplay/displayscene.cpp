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
    struct LED tmp;
    tmp.id = leds.size();
    tmp.radius = 50;
    qreal halfRadius = tmp.radius / 2;
    // Save Top-Left position relative to pixel's center
    tmp.position.x = pos.x()-halfRadius;
    tmp.position.y = pos.y()-halfRadius;

    tmp.color = {0, 0, 0};
    leds.push_back(tmp);

    this->addEllipse(tmp.position.x, tmp.position.y, tmp.radius, tmp.radius, QPen(Qt::black), Qt::transparent);
}

size_t DisplayScene::getNumberOfLeds() {
    return leds.size();
}

struct LED DisplayScene::getLedAtIndex(int i) {
    return leds.at(i);
}

void DisplayScene::setLedAtIndex(int i, unsigned char r, unsigned char g, unsigned char b) {
    leds.at(i).color.r = r;
    leds.at(i).color.g = g;
    leds.at(i).color.b = b;
}
