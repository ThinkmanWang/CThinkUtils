
#ifndef CTHINKUTILS_CBSTREEPRINTER_H
#define CTHINKUTILS_CBSTREEPRINTER_H

#include <QWidget>
#include <QDialog>

class CBSTreePrinter : public QDialog {
    Q_OBJECT

public:
    explicit CBSTreePrinter(QWidget* pParent = nullptr);

private:
    void setupUi();

signals:

public slots:

private:

};


#endif //CTHINKUTILS_CBSTREEPRINTER_H
