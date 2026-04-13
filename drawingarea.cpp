#include "drawingarea.h"
#include <QPainter>
#include <QMouseEvent>

DrawingArea::DrawingArea(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(800, 600);
    canvas = QImage(size(), QImage::Format_RGB32);
    backgroundColor = Qt::white;
    canvas.fill(backgroundColor);

    currentTool = Pen;
    currentColor = Qt::black;
    penSize = 3;
    drawing = false;
}

void DrawingArea::setTool(ToolType tool) { currentTool = tool; }
void DrawingArea::setColor(QColor color) { currentColor = color; }
void DrawingArea::setPenSize(int size) { penSize = size; }

void DrawingArea::setBackground(QColor bg)
{
    backgroundColor = bg;
    canvas.fill(bg);
    update();
}

void DrawingArea::clear()
{
    canvas.fill(backgroundColor);
    update();
}

void DrawingArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        startPoint = event->pos();
        lastPoint = startPoint;
    }
}

void DrawingArea::mouseMoveEvent(QMouseEvent *event)
{
    if (drawing && (currentTool == Pen || currentTool == Pencil || currentTool == Eraser)) {
        QPainter painter(&canvas);

        if (currentTool == Eraser)
            painter.setPen(QPen(backgroundColor, penSize * 2, Qt::SolidLine, Qt::RoundCap));
        else if (currentTool == Pencil)
            painter.setPen(QPen(currentColor.lighter(), 1, Qt::SolidLine, Qt::RoundCap));
        else
            painter.setPen(QPen(currentColor, penSize, Qt::SolidLine, Qt::RoundCap));

        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
        update();
    }
}

void DrawingArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (!drawing) return;

    QPainter painter(&canvas);
    painter.setPen(QPen(currentColor, penSize));

    if (currentTool == Line)
        painter.drawLine(startPoint, event->pos());
    else if (currentTool == Rectangle)
        painter.drawRect(QRect(startPoint, event->pos()));
    else if (currentTool == Circle)
        painter.drawEllipse(QRect(startPoint, event->pos()));

    drawing = false;
    update();
}

void DrawingArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0, 0, canvas);
}
