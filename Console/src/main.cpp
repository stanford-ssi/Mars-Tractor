#include <mainwindow.h>

#include <QFontDatabase>
#include <QtWidgets/QApplication>
// #include <glib.h>
// #include <gst/gst.h>
#include <string>

Q_DECLARE_METATYPE(std::string)

int main(int argc, char* argv[])
{
    // gst_init(&argc, &argv);
    QApplication a(argc, argv);

    qRegisterMetaType<std::string>();
    MainWindow w;
    w.show();
    return a.exec();
}
