#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QWidget>
#include <QImage>
#include <QPoint>

enum ToolType { Pen, Pencil, Eraser, Line, Rectangle, Circle };

class DrawingArea : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingArea(QWidget *parent = nullptr);

    void setTool(ToolType tool);
    void setColor(QColor color);
    void setPenSize(int size);
    void clear();
    void setBackground(QColor bg);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QImage canvas;
    QPoint lastPoint;
    QPoint startPoint;
    bool drawing;

    ToolType currentTool;
    QColor currentColor;
    QColor backgroundColor;
    int penSize;
};

#endif
