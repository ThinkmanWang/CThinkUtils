#include <stdio.h>
#include <stdlib.h>

#include <qapplication.h>
#include <qpushbutton.h>
#include <qwidget.h>

int main(int argc, char** argv)
{
    QApplication a( argc, argv );

    QPushButton hello( "Hello world!", NULL);
    hello.resize( 100, 30 );

    hello.show();
    return a.exec();
}

