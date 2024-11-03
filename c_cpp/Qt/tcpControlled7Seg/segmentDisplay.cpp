/**
 * Réf.:
 * QPainter:
 * - https://doc.qt.io/qt-6/qpainterpath.html
 * QPainter in QLayout:
 * - https://stackoverflow.com/questions/66068747/qt5-displaying-a-qpainter-with-layouts
 * Custom shape:
 * - https://stackoverflow.com/questions/13318572/how-to-draw-custom-shapes-in-qt-with-qpainter-or-qpainterpath-using-one-shape-or
 * Triangle drawing and filling with QPainter:
 * - https://stackoverflow.com/questions/19356747/how-to-draw-and-fill-a-triangle-with-qpainter
 * Update widget drawing on event (here button clicked):
 * - https://stackoverflow.com/questions/61623039/how-to-draw-something-with-qpainter-when-the-button-is-pushed
 */
#include "segmentDisplay.h"

#include <QDebug>
#include <QColor>
#include <QPainter>
#include <QPainterPath>
#include <QStaticText>
#include <QWidget>

SegmentsDisplay::SegmentsDisplay(QWidget* pQParent) :
    QWidget(pQParent), scaleX(1.), scaleY(1.) {

    int firstPointX = 35, firstPointY = 35;
    int spaceX  = 30, spaceY1 = 30;
    int length  = 200;
    int spaceY2 = 20;
    int vOffsetForHorizontalSegments = 3*spaceY2/2 + 2*spaceY1 + length;
    int vOffsetForVerticalSegments   = 2*spaceY1 + spaceY2 + length;
    QPainterPath tmps[7];

    /* Horizontal Segments ****** */
    for (int i = 0; i < 3; i++) {
        /* Set vertical offset */
        int vOffsetFromIdx = vOffsetForHorizontalSegments * i;

        // Initial Point ***************
        tmps[i].moveTo(firstPointX,
                       firstPointY + vOffsetFromIdx);

        // Draw segment
        tmps[i].lineTo(firstPointX + spaceX,
                       firstPointY - spaceY1 + vOffsetFromIdx);
        tmps[i].lineTo(firstPointX + spaceX + length,
                       firstPointY - spaceY1 + vOffsetFromIdx);
        tmps[i].lineTo(firstPointX + 2*spaceX + length,
                       firstPointY + vOffsetFromIdx);
        tmps[i].lineTo(firstPointX + spaceX + length,
                       firstPointY + spaceY1 + vOffsetFromIdx);
        tmps[i].lineTo(firstPointX + spaceX,
                       firstPointY + spaceY1 + vOffsetFromIdx);
        tmps[i].closeSubpath();
    }

    /* Vertical Segments (LEFT) ****** */
    firstPointY += spaceY2;
    for (int i = 0; i < 2; i++) {
        /* Set vertical offset */
        int vOffsetFromIdx = vOffsetForVerticalSegments * i;

        // Initial Point ***************
        tmps[5+i].moveTo(firstPointX,
                           firstPointY + vOffsetFromIdx);

        // Draw segment
        tmps[5+i].lineTo(firstPointX + spaceX,
                           firstPointY + spaceY1 + vOffsetFromIdx);
        tmps[5+i].lineTo(firstPointX + spaceX,
                           firstPointY + spaceY1 + length + vOffsetFromIdx);
        tmps[5+i].lineTo(firstPointX,
                           firstPointY + 2*spaceY1 + length + vOffsetFromIdx);
        tmps[5+i].lineTo(firstPointX - spaceX,
                           firstPointY + spaceY1 + length + vOffsetFromIdx);
        tmps[5+i].lineTo(firstPointX - spaceX,
                           firstPointY + spaceY1 + vOffsetFromIdx);
        tmps[5+i].closeSubpath();
    }

    /* Vertical Segments (RIGHT) ****** */
    firstPointX += (2*spaceX + length);
    for (int i = 0; i < 2; i++) {
        /* Set vertical offset */
        int vOffsetFromIdx = vOffsetForVerticalSegments * i;

        // Initial Point ***************
        tmps[3+i].moveTo(firstPointX,
                           firstPointY + vOffsetFromIdx);

        // Draw segment
        tmps[3+i].lineTo(firstPointX + spaceX,
                           firstPointY + spaceY1 + vOffsetFromIdx);
        tmps[3+i].lineTo(firstPointX + spaceX,
                           firstPointY + spaceY1 + length + vOffsetFromIdx);
        tmps[3+i].lineTo(firstPointX,
                           firstPointY + 2*spaceY1 + length + vOffsetFromIdx);
        tmps[3+i].lineTo(firstPointX - spaceX,
                           firstPointY + spaceY1 + length + vOffsetFromIdx);
        tmps[3+i].lineTo(firstPointX - spaceX,
                           firstPointY + spaceY1 + vOffsetFromIdx);
        tmps[3+i].closeSubpath();
    }

    paths.append(tmps[0]);  // Segment [0]        ---
    paths.append(tmps[3]);  // Segment [1]      |  0  |
    paths.append(tmps[4]);  // Segment [2]    5 |  6  | 1
    paths.append(tmps[2]);  // Segment [3]        ---
    paths.append(tmps[6]);  // Segment [4]      |     |
    paths.append(tmps[5]);  // Segment [5]    4 |  3  | 2
    paths.append(tmps[1]);  // Segment [6]        ---

    segsColor.append(QColor("red"   ));
    segsColor.append(QColor("orange"));
    segsColor.append(QColor("yellow"));
    segsColor.append(QColor("green" ));
    segsColor.append(QColor("cyan"  ));
    segsColor.append(QColor("blue"  ));
    segsColor.append(QColor("purple"));

    for (auto i = 0; i < segsColor.size(); i++)
        qDebug() << "Path[" << i << "]: {" << paths[i].currentPosition().x()
                 <<"," << paths[i].currentPosition().y() << "}\n";
}

int SegmentsDisplay::getNSegments(void) {
    return paths.size();
}

void SegmentsDisplay::setSegmentColor(int idx, QColor color) {
    segsColor[idx] = color;
}

void SegmentsDisplay::setPainterScaleX(qreal _scaleX) {
    scaleX = _scaleX;
}

void SegmentsDisplay::setPainterScaleY(qreal _scaleY) {
    scaleY = _scaleY;
}

void SegmentsDisplay::toggleXRay(void) {
    xRayOn = !xRayOn;
    update();
}

void SegmentsDisplay::paintEvent(QPaintEvent* pQEvent) {
    QPainter painter(this);
    painter.scale(scaleX, scaleY);
    if (xRayOn) {
        QStaticText text;
        QFont txtFont("Arial", 20, QFont::Bold, true);

        painter.setPen(QPen(QBrush(Qt::black), 3));
        for (int i = 0; i < paths.size(); i++) {
            painter.fillPath(paths[i], Qt::transparent);
            painter.drawPath(paths[i]);

            /* Segment numeration */
            text.setText(QString::number(i));
            painter.setFont(txtFont);
            if (i % 3) { /* Vertical segments */
                painter.drawStaticText(paths[i].currentPosition().x() -  10,
                                       paths[i].currentPosition().y() + 110,
                                       text);
            } else {     /* Horinzontal segments */
                painter.drawStaticText(paths[i].currentPosition().x() + 120,
                                       paths[i].currentPosition().y() -  20,
                                       text);
            }
        }
    } else {
        painter.setPen(Qt::NoPen);
        for (int i = 0; i < paths.size(); i++)
            painter.fillPath(paths[i], QBrush(segsColor[i]));
    }

    // call base class paint event to keep it working
    QWidget::paintEvent(pQEvent);
}
