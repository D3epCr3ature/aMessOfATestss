#ifndef __DISPLAY_SCENE_H__
#define __DISPLAY_SCENE_H__

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QPaintEvent>

#include <cstdint>

#include "structure/display.h"

class DisplayScene : public QGraphicsScene {

public:
    DisplayScene();
    explicit DisplayScene(QObject *parent = nullptr);
    virtual ~DisplayScene();

    void addLedToDisplay(const QPointF &pos, double radius,
                         std::string type = "WS281x", double angle = 0.0,
                         double pitch = 2.54);

    void removeLedAt(int idx);
    size_t getNumberOfLeds();
    struct LED getLedAtIndex(int i);
    void       setLedAtIndex(int i, uint8_t r, uint8_t g, uint8_t b);

    void setDisplay(const struct LEDDisplay& display);
    const struct LEDDisplay& getDisplay();


protected:
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)    override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)   override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    //void drawLedTo(const QPointF &pos);

    QPixmap *image;
    QGraphicsPixmapItem *item;
    bool xRayOn;

    struct LEDDisplay display;
};

#endif // __DISPLAY_SCENE_H__
