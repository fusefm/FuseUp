#include <QtGui/QApplication>
#include "FuseUp.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    FuseUp foo;
    foo.show();
    return app.exec();
}
