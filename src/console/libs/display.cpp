#include "display.h"
#include "ui_display.h"

Display::Display(QWidget* parent) : QWidget(parent), ui(new Ui::Display) { ui->setupUi(this); }

Display::~Display() { delete ui; }

void Display::paintEvent(QPaintEvent*) { paintMat(this, cv::Mat()); }

void Display::paintMat(QPaintDevice* device, const cv::Mat& src)
{
    cv::Mat test = cv::Mat(320, 240, CV_8UC3, cv::Scalar(0, 0, 0));
    QImage img = Mat2QImage(test);
    img.scaled(QSize(this->width(), this->height()), Qt::KeepAspectRatio);

    QPainter painter(device);
    painter.drawImage(QPoint(0, 0), img);
}

QImage Display::Mat2QImage(cv::Mat const& src)
{
    // Convert Mat to QImage colorspace
    cv::Mat temp;
    cv::cvtColor(src, temp, cv::COLOR_BGR2RGB);

    // Construct and return QImage
    QImage result((const uchar*)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    result.bits();
    return result;
}

cv::Mat Display::QImage2Mat(QImage const& src)
{
    cv::Mat tmp(src.height(), src.width(), CV_8UC3, (uchar*)src.bits(), src.bytesPerLine());
    cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
    cv::cvtColor(tmp, result, cv::COLOR_BGR2RGB);
    return result;
}