#include <QApplication>
#include "canvas.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Canvas canvas;
    canvas.resize(800, 600);
    canvas.show();

    return app.exec();
}
