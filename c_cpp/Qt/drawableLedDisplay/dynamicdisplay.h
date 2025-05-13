/* ************************************************************************** *
 * ***                     CUSTOMISED DRAWABLE SCENE                      *** *
 * ************************************************************************** */
#ifndef __DISPLAY_SCENE_H__
#define __DISPLAY_SCENE_H__

/* Qt's libraries: */
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QPointF>

/* C/C++ standard libraries: */
#include <cstddef>  /* size_t */
#include <cstdint>  /* uint[8|16|..]_t */
#include <string>

/* Custom modules: */
#include "structure/display.h"  /* struct LEDDisplay */

class DisplayScene : public QGraphicsScene {

public:
    /* Constructor/Destructor */
    //DisplayScene();
    explicit DisplayScene(QObject *parent = nullptr);
    virtual ~DisplayScene();

    /* */
    void addLedToDisplay(const QPointF &pos, double radius,
                         std::string type = "WS281x", double angle = 0.0,
                         double pitch = 2.54);

    /* */
    void removeLedAt(int idx);

    /* */
    size_t getNumberOfLeds();

    /* */
    struct LED getLedAtIndex(int i);
    void       setLedAtIndex(int i, uint8_t r, uint8_t g, uint8_t b);

    /* */
    void setDisplay(const struct LEDDisplay& display);
    const struct LEDDisplay& getDisplay();

protected:
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)    override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)   override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    /* LED Display structure used for export/import as JSON */
    struct LEDDisplay display;
};

#endif // __DISPLAY_SCENE_H__
/* ************************************************************************** */

/* ************************************************************************** *
 * ***    CUSTOMISED VIEW THAT USES THE DEDICATED DRAWABLE SCENE ABOVE    *** *
 * ************************************************************************** */
#ifndef __DYNAMIC_DISPLAY_H__
#define __DYNAMIC_DISPLAY_H__

/* Qt's libraries: */
#include <QGraphicsView>
#include <QColor>
#include <QMouseEvent>

/* C/C++ standard libraries: */
#include <cstddef>  /* size_t */

/* Custom modules: */
#include "structure/display.h"

class DynamicDisplay : public QGraphicsView {

public:
    /* Constructor/Destructor */
    DynamicDisplay();
    virtual ~DynamicDisplay();

    /* Drawable scene modifiers */
    void setSceneRect(qreal x, qreal y, qreal w, qreal h);
    void updateScene();
    void clearScene();

    /* Drawable scene accessors */
    void setDisplay(const struct LEDDisplay& display);
    const struct LEDDisplay& getDisplay();
    size_t getNumberOfLeds();
    void setLedColor(int idx, QColor color);

    /* */
    void toggleXRay();

protected:
    //virtual void mouseMoveEvent(QMouseEvent *mouseEvent) override;
    //virtual void mousePressEvent(QMouseEvent *event)     override;
    virtual void mouseReleaseEvent(QMouseEvent *event)   override;

    //virtual void paintEvent(QPaintEvent *pQEvent) override;

private:
    DisplayScene  *scene;

    /* X-Ray view status */
    bool xRay = false;
};

#endif // __DYNAMIC_DISPLAY_H__
/* ************************************************************************** */
