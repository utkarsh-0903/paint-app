#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QImage>
#include <QColor>
#include <QPoint>

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);

    void setBrushColor(const QColor &color);
    void setBrushSize(int size);
    void setEraser(bool enabled);
    void clearCanvas();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawAt(const QPoint &pos);

    QImage m_image;
    QColor m_color;
    int m_brushSize;
    bool m_eraser;
    QPoint m_lastPos;
};

#endif // CANVAS_H

