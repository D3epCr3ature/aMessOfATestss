#ifndef SEGMENTDISPLAY_H
#define SEGMENTDISPLAY_H

#include <QColor>
#include <QList>
#include <QPainterPath>
#include <QWidget>

class SegmentsDisplay: public QWidget {

public:
    SegmentsDisplay(QWidget *pQParent = nullptr);
    virtual ~SegmentsDisplay() = default;

    SegmentsDisplay(const SegmentsDisplay&) = delete;
    SegmentsDisplay& operator=(const SegmentsDisplay&) = delete;

    int getNSegments(void);
    void setSegmentColor(int idx, QColor color);
    void setPainterScaleX(qreal _scaleX);
    void setPainterScaleY(qreal _scaleY);
    void toggleXRay(void);

protected:
    virtual void paintEvent(QPaintEvent *pQEvent) override;

private:
    QList<QColor> segsColor;
    QList<QPainterPath> paths;
    qreal scaleX, scaleY;
    bool xRayOn = false;
};

#endif // SEGMENTDISPLAY_H
