#include "dynamicdisplay.h"

#include <QGraphicsTextItem>

DynamicDisplay::DynamicDisplay() : scene(new DisplayScene(this)) {}

void DynamicDisplay::setSceneRect(qreal x, qreal y, qreal w, qreal h) {
    scene->setSceneRect(x, y, w, h);
    this->setScene(scene);
    this->setDragMode(DragMode::ScrollHandDrag);
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
}*/

void DynamicDisplay::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        updateScene();
    } else if (event->button() == Qt::LeftButton) {
        /* Re-arm ScrollHandGrab to reset previous grab */
        this->setDragMode(DragMode::NoDrag);
        this->setDragMode(DragMode::ScrollHandDrag);
    }
}

void DynamicDisplay::setDisplay(const struct LEDDisplay& display) {
    scene->setDisplay(display);
    updateScene();
}

const struct LEDDisplay& DynamicDisplay::getDisplay() {
    return scene->getDisplay();
}

void DynamicDisplay::toggleXRay() {
    xRay = !xRay;
}

//void DynamicDisplay::paintEvent(QPaintEvent *pQEvent) {
void DynamicDisplay::updateScene() {
    static int i = 0;

    scene->clear();

    if (xRay) {
        static QGraphicsTextItem *text;
        static QFont txtFont("Arial", 20, QFont::Bold, true /* italic */);

        for (i = 0; i < scene->getNumberOfLeds(); i++) {
            text = new QGraphicsTextItem;

            const auto &led = scene->getLedAtIndex(i);
            scene->addEllipse(led.position.x, led.position.y, led.radius, led.radius, QPen(Qt::black), Qt::transparent);

            text->setPos(led.position.x, led.position.y);
            text->setFont(txtFont);
            text->setPlainText(QString::number(i));
            scene->addItem(text);
        }
    } else {
        for (i = 0; i < scene->getNumberOfLeds(); i++) {
            auto led = scene->getLedAtIndex(i);
            auto color = QColor(led.color.r, led.color.g, led.color.b);
            scene->addEllipse(led.position.x, led.position.y, led.radius, led.radius, QPen(Qt::black), color);
        }
    }
}

void DynamicDisplay::clearScene() {
    scene->clear();
}
