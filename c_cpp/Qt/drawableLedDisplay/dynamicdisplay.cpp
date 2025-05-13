
#include "dynamicdisplay.h"

/* Custom scene's libraries: */
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QObject>
#include <QPointF>
#include <QStaticText>

/* Custom view's libraries: */
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QColor>
#include <QFont>

/* Custom scene & view common libraries: */
#include <cstddef>  /* size_t */
#include <cstdint>  /* uint[8|16|..]_t */
#include <string>

#include "structure/led.h"      /* struct LED */
#include "structure/display.h"  /* struct LEDDisplay */

/* ************************************************************************** *
 * ***                     CUSTOMISED DRAWABLE SCENE                      *** *
 * ************************************************************************** */

/*DisplayScene::DisplayScene() {
    /* Private var. init. * /
    //...

    /* QGraphicsScene super functions call * /
    setBackgroundBrush(Qt::lightGray);
}*/

DisplayScene::DisplayScene(QObject *parent) : QGraphicsScene(parent) {
    /* Private var. init. */
    //...

    /* QGraphicsScene super functions call */
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
/* ************************************************************************** */

/* ************************************************************************** *
 * ***    CUSTOMISED VIEW THAT USES THE DEDICATED DRAWABLE SCENE ABOVE    *** *
 * ************************************************************************** */
DynamicDisplay::DynamicDisplay() {
    /* Private var. init. */
    scene = new DisplayScene(this);
    xRay  = false;

    /* QGraphicsScene super functions call */
    //...
}

DynamicDisplay::~DynamicDisplay() {

}

void DynamicDisplay::setSceneRect(qreal x, qreal y, qreal w, qreal h) {
    scene->setSceneRect(x, y, w, h);
    this->setScene(scene);
    this->setDragMode(DragMode::ScrollHandDrag);
}

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

void DynamicDisplay::setDisplay(const struct LEDDisplay& display) {
    scene->setDisplay(display);
    updateScene();
}

const struct LEDDisplay& DynamicDisplay::getDisplay() {
    return scene->getDisplay();
}

size_t DynamicDisplay::getNumberOfLeds() {
    return scene->getNumberOfLeds();
}

void DynamicDisplay::setLedColor(int idx, QColor color) {
    scene->setLedAtIndex(idx, color.red(), color.green(), color.blue());
}

void DynamicDisplay::toggleXRay() {
    xRay = !xRay;
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

//void DynamicDisplay::paintEvent(QPaintEvent *pQEvent) {}
/* ************************************************************************** */
