#ifndef __DISPLAY_SCENE_H__
#define __DISPLAY_SCENE_H__

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QPaintEvent>

class DisplayScene : public QGraphicsScene {

public:
    DisplayScene();
    explicit DisplayScene(QObject *parent = nullptr);
    virtual ~DisplayScene();
    void drawLedTo(const QPointF &pos);


protected:
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)    override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)   override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    //void drawLedTo(const QPointF &pos);

    QPixmap *image;
    QGraphicsPixmapItem *item;
    bool xRayOn;
};

#endif // __DISPLAY_SCENE_H__
