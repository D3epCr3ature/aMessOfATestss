#ifndef __DISPLAY_SCENE_H__
#define __DISPLAY_SCENE_H__

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QPaintEvent>

#include <vector>

#include "structure/led.h"

class DisplayScene : public QGraphicsScene {

public:
    DisplayScene();
    explicit DisplayScene(QObject *parent = nullptr);
    virtual ~DisplayScene();

    void drawLedTo(const QPointF &pos);
    size_t getNumberOfLeds();
    struct LED getLedAtIndex(int i);
    void       setLedAtIndex(int i, unsigned char r, unsigned char g, unsigned char b);

protected:
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)    override;
    //void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)   override;
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    //void drawLedTo(const QPointF &pos);

    QPixmap *image;
    QGraphicsPixmapItem *item;
    bool xRayOn;

    std::vector<LED> leds;
};

#endif // __DISPLAY_SCENE_H__
