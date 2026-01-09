#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent),
    m_color(Qt::red),
    m_brushSize(12),
    m_eraser(false)
{
    setAttribute(Qt::WA_StaticContents);
    m_image = QImage(size(), QImage::Format_ARGB32_Premultiplied);
    m_image.fill(Qt::transparent);
}

void Canvas::setBrushColor(const QColor &color)
{
    m_color = color;
    m_eraser = false;
}

void Canvas::setBrushSize(int size)
{
    m_brushSize = size;
}

void Canvas::setEraser(bool enabled)
{
    m_eraser = enabled;
}

void Canvas::clearCanvas()
{
    m_image.fill(Qt::transparent);
    update();
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0, 0, m_image);
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_lastPos = event->pos();
        drawAt(m_lastPos);
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        drawAt(event->pos());
        m_lastPos = event->pos();
    }
}

void Canvas::resizeEvent(QResizeEvent *event)
{
    if (width() > m_image.width() || height() > m_image.height()) {
        QImage newImage(event->size(), QImage::Format_ARGB32_Premultiplied);
        newImage.fill(Qt::transparent);

        QPainter p(&newImage);
        p.drawImage(0, 0, m_image);
        m_image = newImage;
    }
    QWidget::resizeEvent(event);
}

void Canvas::drawAt(const QPoint &pos)
{
    QPainter painter(&m_image);
    painter.setRenderHint(QPainter::Antialiasing, true);

    if (m_eraser) {
        painter.setCompositionMode(QPainter::CompositionMode_Clear);
        painter.setBrush(Qt::transparent);
    } else {
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.setBrush(m_color);
    }

    painter.setPen(Qt::NoPen);
    painter.drawEllipse(pos, m_brushSize / 2, m_brushSize / 2);

    update(QRect(pos - QPoint(m_brushSize, m_brushSize),
                 pos + QPoint(m_brushSize, m_brushSize)));
}
