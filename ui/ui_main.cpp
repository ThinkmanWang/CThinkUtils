#include <stdio.h>
#include <stdlib.h>

#include <qapplication.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <qinputdialog.h>
#include <qstring.h>

#include "log.h"

int test1(int argc, char** argv)
{
    QApplication a( argc, argv );

    QPushButton hello( "Hello world!", NULL);
    hello.resize( 100, 30 );

    hello.show();
    return a.exec();
}

int test_inputdialog(int argc, char** argv)
{
    QApplication a( argc, argv );
    bool bOK = false;
    int nRet = QInputDialog::getInt(NULL
            , "Application name"
            , "Please enter a number"
            , 1, INT32_MIN, INT32_MAX, 1
            , &bOK);

    if (bOK) {
        log_debug("%d", nRet);
    }

    return a.exec();
}

int main(int argc, char** argv)
{
//    return test1(argc, argv);
    return test_inputdialog(argc, argv);
}

