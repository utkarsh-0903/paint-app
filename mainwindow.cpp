#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawingarea.h"

#include <QToolBar>
#include <QAction>
#include <QColorDialog>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    DrawingArea *area = new DrawingArea(this);
    setCentralWidget(area);

    QToolBar *toolBar = addToolBar("Tools");

    QAction *penAct = toolBar->addAction("Pen");
    QAction *pencilAct = toolBar->addAction("Pencil");
    QAction *eraserAct = toolBar->addAction("Eraser");
    QAction *lineAct = toolBar->addAction("Line");
    QAction *rectAct = toolBar->addAction("Rectangle");
    QAction *circleAct = toolBar->addAction("Circle");
    QAction *colorAct = toolBar->addAction("Color");
    QAction *whiteBoardAct = toolBar->addAction("Whiteboard");
    QAction *blackBoardAct = toolBar->addAction("Blackboard");
    QAction *clearAct = toolBar->addAction("Clear");
    QAction *saveAct = toolBar->addAction("Save");

    connect(penAct, &QAction::triggered, this, [=]() {
        area->setTool(Pen);
    });

    connect(pencilAct, &QAction::triggered, this, [=]() {
        area->setTool(Pencil);
    });

    connect(eraserAct, &QAction::triggered, this, [=]() {
        area->setTool(Eraser);
    });

    connect(lineAct, &QAction::triggered, this, [=]() {
        area->setTool(Line);
    });

    connect(rectAct, &QAction::triggered, this, [=]() {
        area->setTool(Rectangle);
    });

    connect(circleAct, &QAction::triggered, this, [=]() {
        area->setTool(Circle);
    });

    connect(colorAct, &QAction::triggered, this, [=]() {
        QColor color = QColorDialog::getColor(Qt::black, this, "Select Color");
        if (color.isValid())
            area->setColor(color);
    });

    connect(whiteBoardAct, &QAction::triggered, this, [=]() {
        area->setBackground(Qt::white);
        area->setColor(Qt::black);
    });

    connect(blackBoardAct, &QAction::triggered, this, [=]() {
        area->setBackground(Qt::black);
        area->setColor(Qt::white);
    });

    connect(clearAct, &QAction::triggered, this, [=]() {
        area->clear();
    });

    connect(saveAct, &QAction::triggered, this, [=]() {
        QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG Image (*.png)");
        if (!fileName.isEmpty()) {
            area->grab().save(fileName);
        }
    });

    setWindowTitle("Qt Whiteboard / Blackboard / Paint App");
    resize(1000, 700);
}

MainWindow::~MainWindow()
{
}
