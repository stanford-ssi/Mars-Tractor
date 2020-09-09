/**
 * @file statusview.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#include "statusview.h"
#include "ui_statusview.h"

StatusView::StatusView(QWidget* parent) : QWidget(parent), ui(new Ui::StatusView)
{
    ui->setupUi(this);
}

StatusView::~StatusView() { delete ui; }

void StatusView::paintEvent(QPaintEvent*)
{
    QSvgRenderer* renderer;

    // Get correct status connection icon
    if (hasConnection)
    {
        renderer = new QSvgRenderer(QString("assets/icons/wifi.svg"));
    }
    else
    {
        renderer = new QSvgRenderer(QString("assets/icons/plug.svg"));
    }
    renderer->setAspectRatioMode(Qt::KeepAspectRatio);

    // Paint icon on widget
    QPainter painter(this);
    renderer->render(&painter);
    renderer->setViewBox(QRectF(0, 0, this->width(), this->height()));

    delete renderer;
}

void StatusView::changeConnectionStatus(bool status)
{
    hasConnection = status;
    repaint();
}