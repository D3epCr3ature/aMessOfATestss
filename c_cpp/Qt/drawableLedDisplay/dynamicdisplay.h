#ifndef __DYNAMIC_DISPLAY_H__
#define __DYNAMIC_DISPLAY_H__

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>

#include "displayscene.h"
#include "structure/display.h"

class DynamicDisplay : public QGraphicsView {

public:
    DynamicDisplay();
    void setSceneRect(qreal x, qreal y, qreal w, qreal h);

    size_t getNumberOfLeds();
    void setLedColor(int idx, QColor color);

    void toggleXRay();

    void updateScene();
    void setDisplay(const struct LEDDisplay& display);
    const struct LEDDisplay& getDisplay();

    void clearScene();

protected:
    //virtual void mouseMoveEvent(QMouseEvent *mouseEvent) override;
    //virtual void mousePressEvent(QMouseEvent *event)     override;
    virtual void mouseReleaseEvent(QMouseEvent *event)   override;

    //virtual void paintEvent(QPaintEvent *pQEvent) override;

private:
    DisplayScene  *scene;

    bool xRay = false;
};

#endif // __DYNAMIC_DISPLAY_H__
