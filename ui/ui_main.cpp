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
    /*
     static int getInt(QWidget *parent
                        , const QString &title
                        , const QString &label
                        , int value = 0
                        , int minValue = -2147483647
                        , int maxValue = 2147483647
                        , int step = 1
                        , bool *ok = nullptr
                        , Qt::WindowFlags flags = Qt::WindowFlags());
     */
    QApplication a( argc, argv );
    bool bOK = false;
    int nRet = QInputDialog::getInt(NULL
            , "Application name"
            , "Please enter a number"
            , 1, -2147483647, 2147483647, 1
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

