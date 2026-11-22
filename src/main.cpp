#include <QApplication>
#include "ScannerWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ScannerWindow window;
    window.show();
    return app.exec();
}
