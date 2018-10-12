#include <cstdio>
#include <cstdlib>
#include <QApplication>

#include "CBSTreePrinterDlg.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    CBSTreePrinterDlg* pDialog = new CBSTreePrinterDlg(NULL);
    pDialog->show();

    return app.exec();
}

