#ifndef __DYNAMIC_DISPLAY_H__
#define __DYNAMIC_DISPLAY_H__

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
//#include "displayscene.h"

#include "structure/led.h"

class DynamicDisplay : public QGraphicsView {

public:
    DynamicDisplay();
    void setSceneDimensions(qreal x, qreal y, qreal w, qreal h);

    void drawLedTo(const QPointF &pos);

    size_t getNumberOfLeds();

    struct LED getLedAtIndex(int i);
    void       setLedAtIndex(int i, unsigned char r, unsigned char g, unsigned char b);
    void setLedColor(int idx, QColor color);

    void updateScene();

protected:
    //virtual void mouseMoveEvent(QMouseEvent *mouseEvent) override;
    virtual void mousePressEvent(QMouseEvent *event)     override;
    virtual void mouseReleaseEvent(QMouseEvent *event)   override;

    //virtual void paintEvent(QPaintEvent *pQEvent) override;

private:
    QPoint worldRelativePos;
    size_t worldWidth, worldHeight;

    /* Scene components */
    QPixmap *image = nullptr;
    QGraphicsPixmapItem *item = nullptr;
    bool xRayOn;

    std::vector<LED> leds;

    /* Actual scene */
    //DisplayScene  *scene = nullptr;
    QGraphicsScene  *scene = nullptr;
};

#endif // __DYNAMIC_DISPLAY_H__
