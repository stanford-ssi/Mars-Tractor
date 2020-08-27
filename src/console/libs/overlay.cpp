/** @file overlay.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#include <overlay.h>
#include <ui_overlay.h>

Overlay::Overlay(QWidget* parent)
    : QWidget(parent), ui(new Ui::Overlay)
{
    ui->setupUi(this);
}

void Overlay::paintEvent(QPaintEvent*)
{
    bool hasConnection = true;    // TODO: fix for true server connection
    QSvgRenderer* renderer;

    // Get base svg for widget
    if (hasConnection)
    {
        renderer = new QSvgRenderer(QString("assets/overlay/base.svg"));
    }
    // If not connected, paint disconnected.svg and return
    else
    {
        renderer = new QSvgRenderer(QString("assets/overlay/disconnected.svg"));
        QPainter painter(this);
        renderer->render(&painter);
        renderer->setViewBox(QRectF(0, 0, this->width(), this->height()));
        delete renderer;
        return;
    }
    renderer->setAspectRatioMode(Qt::KeepAspectRatio);

    // Paint base svg on widget
    QPainter painter(this);
    renderer->render(&painter);
    renderer->setViewBox(QRectF(0, 0, this->width(), this->height()));

    delete renderer;
}

Overlay::~Overlay()
{
    delete ui;
}

QPoint Overlay::locateCorner(QSize defaultSize, QSize viewBox)
{
    double defaultAR = (double)defaultSize.width() / (double)defaultSize.height();
    double viewAR = (double)viewBox.width() / (double)viewBox.height();

    //@var arCoeff lets us know which side of the svg borders the widget
    double arCoeff = viewAR / defaultAR;
    double width, height;
    int x, y;

    if (arCoeff > 1)
    {
        height = (double)viewBox.height();
        width = height * defaultAR;
        y = 0;
        x = (int)(.5 + ((double)viewBox.width() - width) / 2);
    }
    else if (arCoeff < 1)
    {
        width = (double)viewBox.width();
        height = width * 1 / defaultAR;
        x = 0;
        y = (int)(.5 + ((double)viewBox.height() - height) / 2);
    }
    else
    {
        x = 0;
        y = 0;
    }

    return QPoint(x, y);
}

double Overlay::getScale(QSize defaultSize, QSize viewBox)
{
    double result;
    QPoint corner = locateCorner(defaultSize, viewBox);

    // Since svg maintains aspect ratio, only height or width is needed
    double width = (double)viewBox.width() - 2 * corner.x();
    result = width / (double)defaultSize.width();

    return result;
}
