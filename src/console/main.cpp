#include <mainwindow.h>

#include <QFontDatabase>
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QFontDatabase::addApplicationFont("://Ubuntu-R.ttf");
    qApp->setFont(QFont("Ubuntu", 11, QFont::Normal, false));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
