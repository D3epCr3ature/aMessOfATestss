#include "dynamicdisplay.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

//DynamicDisplay::DynamicDisplay() : scene(new DisplayScene(this)) {
DynamicDisplay::DynamicDisplay() : scene(new QGraphicsScene(this)) {
    connect(scene, SIGNAL(mousePressEvent), scene, "Test");

    scene->setBackgroundBrush(Qt::lightGray);
}

void DynamicDisplay::drawLedTo(const QPointF &pos) {
    struct LED tmp;
    tmp.id = leds.size();
    tmp.radius = 50;
    qreal halfRadius = tmp.radius / 2;
    // Save Top-Left position relative to pixel's center
    tmp.position.x = pos.x()-halfRadius;
    tmp.position.y = pos.y()-halfRadius;

    tmp.color = {0, 0, 0};
    leds.push_back(tmp);

    scene->addEllipse(tmp.position.x, tmp.position.y, tmp.radius, tmp.radius,
                      QPen(Qt::black),
                      QColor(tmp.color.r, tmp.color.g, tmp.color.b));
}

void DynamicDisplay::setSceneDimensions(qreal x, qreal y, qreal w, qreal h) {
    worldRelativePos.setX(x);
    worldRelativePos.setY(y);
    worldWidth  = w;
    worldHeight = h;

    scene->setSceneRect(x, y, w, h);

    this->setScene(scene);
    //this->fitInView(scene->sceneRect());
}

void DynamicDisplay::setLedColor(int idx, QColor color) {
    static unsigned char r = 0, g = 0, b = 0;
    r = color.red();
    g = color.green();
    b = color.blue();
    leds.at(idx).color = { r, g, b };
}

size_t DynamicDisplay::getNumberOfLeds() {
    return leds.size();
}

/*void DynamicDisplay::mouseMoveEvent(QMouseEvent *event) {
    /* Idea for making a preview * /
    if (mouseEvent->button() == Qt::LeftButton &&
        stripMode && inPreview) {
        drawLedPreviewTo(mouseEvent->scenePos()); // -> Use a 2nd QPixImage
    }
}*/

void DynamicDisplay::mousePressEvent(QMouseEvent *event) {
    /* This work, but cursor's offset is weird ... */
    static QPointF pos;
    if (event->button() == Qt::LeftButton) {
        pos = event->scenePosition();
        pos.setX(pos.x() - worldRelativePos.x());
        pos.setY(pos.y() + worldRelativePos.y());
        //pos.setY(pos.y() + scene->sceneRect().y() / 2);
        drawLedTo(pos);
    }
}

void DynamicDisplay::mouseReleaseEvent(QMouseEvent *event) {
    /*if (mouseEvent->button() == Qt::LeftButton) {
        drawLedTo(mouseEvent->scenePos());
    }*/
}

void DynamicDisplay::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    /* This doesn't work ... */
    static QPointF pos;
    if (event->button() == Qt::LeftButton) {
        pos = event->scenePos();
        drawLedTo(pos);
    }
}

//void DynamicDisplay::paintEvent(QPaintEvent *pQEvent) {
void DynamicDisplay::updateScene() {
    static int i = 0;
    scene->clear();
    for (i = 0; i < leds.size(); i++) {
        auto led = leds.at(i);
        auto color = QColor(led.color.r, led.color.g, led.color.b);
        scene->addEllipse(led.position.x, led.position.y, led.radius, led.radius, QPen(Qt::black), color);
    }
}
