#include <cstdio>
#include <cstdlib>
#include <QApplication>

#include "CBSTreePrinter.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    CBSTreePrinter* pDialog = new CBSTreePrinter(NULL);
    pDialog->show();

    return app.exec();
}
