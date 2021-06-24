/**
 * @file statusview.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#include "statusview.h"
#include "ui_statusview.h"
#include "mtconstants.h"

StatusView::StatusView(QWidget* parent) : QWidget(parent), ui(new Ui::StatusView){
    ui->setupUi(this);
    connect(ui->lineEditHost, SIGNAL(returnPressed()), this, SIGNAL(go()));
    connect(ui->lineEditPort, SIGNAL(returnPressed()), this, SIGNAL(go()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SIGNAL(go()));

    // Set default text to Robot IP address
    ui->lineEditHost->setText(QString(DEFAULT_ADDRESS));
    ui->lineEditPort->setText(QString(std::to_string(DEFAULT_PORT).c_str()));

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
    std::string StatusView::lineEditHostText(){
        return ui->lineEditHost->text().toStdString();
    }
    uint16_t StatusView::lineEditPortNumber(){
        return ui->lineEditPort->text().toUInt();
    }