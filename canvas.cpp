#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent), drawing(false)
{
    setAttribute(Qt::WA_StaticContents);
    setStyleSheet("background-color: white;");
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw lines
    painter.setPen(QPen(Qt::black, 5));
    for (const Line &line : lines) {
        painter.drawLine(line.start, line.end);
    }

    // Draw version text (bottom-right)
    QString versionText = "alpha 0.0.1";

    QFont font;
    font.setPointSize(10);
    painter.setFont(font);
    painter.setPen(Qt::black);

    QRect rect = painter.viewport();
    painter.drawText(
        rect.adjusted(0, 0, -10, -10),
        Qt::AlignBottom | Qt::AlignRight,
        versionText
        );
}


void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        lastPoint = event->pos();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (drawing) {
        Line line;
        line.start = lastPoint;
        line.end = event->pos();
        lines.append(line);

        lastPoint = event->pos();
        update(); // repaint
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        drawing = false;
    }
}
