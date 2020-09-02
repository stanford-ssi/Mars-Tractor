#include <mainwindow.h>

#include <QFontDatabase>
#include <QtWidgets/QApplication>
#include <string>

Q_DECLARE_METATYPE(std::string)

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<std::string>();
    MainWindow w;
    w.show();
    return a.exec();
}
