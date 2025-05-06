#include "displayscene.h"

#include <QApplication>
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
    static size_t i = 0;
    static int x = 0, y = 0;
    static struct LED led;

    /* Shift + Right click: Remove LED under cursor */
    if (QApplication::keyboardModifiers() == Qt::ShiftModifier && mouseEvent->button() == Qt::RightButton) {
        x = mouseEvent->scenePos().x();
        y = mouseEvent->scenePos().y();

        for (i = 0; i < display.leds.size(); i++) {
            led = display.leds[i];
            if ((x >= led.position.x && x <= (led.position.x + led.radius)) &&
                (y >= led.position.y && y <= (led.position.y + led.radius)) ) {
                removeLedAt(i);
                break;
            }
        }
    /* Right click only: Add LED */
    } else if (mouseEvent->button() == Qt::RightButton) {
        addLedToDisplay(mouseEvent->scenePos(), 50);

    }
}

void DisplayScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    /*if (mouseEvent->button() == Qt::LeftButton) {
        drawLedTo(mouseEvent->scenePos());
    }*/
}

void DisplayScene::addLedToDisplay(const QPointF &pos, double radius,
                                   std::string type, double angle,
                                   double pitch) {
    static struct LED led;

    led.radius = radius;
    led.color  = typeof(led.color){0, 0, 0};
    led.type   = type;
    led.angle  = angle;
    led.pitch  = pitch;

    // Save Top-Left position relative to pixel's center
    led.position.x = pos.x() - radius / 2.0;
    led.position.y = pos.y() - radius / 2.0;

    display.leds.push_back(led);
}

inline void DisplayScene::removeLedAt(int idx) {
    static size_t i = 0;

    display.leds.erase(display.leds.begin()+idx);
}

size_t DisplayScene::getNumberOfLeds() {
    return display.leds.size();
}

struct LED DisplayScene::getLedAtIndex(int i) {
    return display.leds.at(i);
}

void DisplayScene::setLedAtIndex(int i, uint8_t r, uint8_t g, uint8_t b) {
    struct LED& led = display.leds.at(i);

    led.color.r = r;
    led.color.g = g;
    led.color.b = b;
}

void DisplayScene::setDisplay(const struct LEDDisplay& display) {
    this->display = display;
}

const struct LEDDisplay& DisplayScene::getDisplay() {
    return display;
}
