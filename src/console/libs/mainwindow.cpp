#include <mainwindow.h>
#include <ui_mainwindow.h>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::paintEvent(QPaintEvent*) {
    bool hasConnection = true;    // TODO: fix for true server connection
    QSvgRenderer* renderer;

// Get correct svg for connection status
    if (hasConnection)
    {
        renderer = new QSvgRenderer(QString("assets/icons/wifi.svg"));
    }
    else
    {
        renderer = new QSvgRenderer(QString("assets/icons/plug.svg"));
    }
    renderer->setAspectRatioMode(Qt::KeepAspectRatio);

    // Paint base svg on widget
    QPainter painter(ui->icon);
    renderer->render(&painter);

    delete renderer;
    return;
}