/**
 * @file display.h
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#include <display.h>
#include <ui_display.h>

Display::Display(QWidget* parent) : QWidget(parent), ui(new Ui::Display) { ui->setupUi(this); }

void Display::paintEvent(QPaintEvent*)
{
    // Check if Mat object is empty
    if (screen.empty()) screen = cv::imread("assets/images/no_signal_screen.jpg");

    // using namespace std;
    // vector<uchar> buf;
    // cv::imencode(".jpg", screen, buf);

    // string frameData(buf.begin(), buf.end());
    // size_t test = frameData.find('}');

    // vector<uchar> buf2(frameData.begin(), frameData.end());
    // screen = cv::imdecode(buf2, 1);

    // Convert Mat image to QImage
    QImage img = Mat2QImage(screen);
    QImage scaled = img.scaled(QSize(this->width(), this->height()), Qt::KeepAspectRatio);

    // Draw image onto widget
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), scaled);
}

QImage Display::Mat2QImage(const cv::Mat& src)
{
    // Convert Mat to QImage colorspace
    cv::Mat temp;
    cv::cvtColor(src, temp, cv::COLOR_BGR2RGB);

    // Construct and return QImage
    QImage result((const uchar*)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    result.bits();
    return result;
}

cv::Mat Display::QImage2Mat(const QImage& src)
{
    cv::Mat result;
    cv::Mat tmp(src.height(), src.width(), CV_8UC3, (uchar*)src.bits(), src.bytesPerLine());
    cv::cvtColor(tmp, result, cv::COLOR_BGR2RGB);

    return result;
}

void Display::decodeFrame(const std::string& frameData)
{
    using namespace std;

    vector<uchar> buf(frameData.begin(), frameData.end());
    screen = cv::imdecode(buf, 1);

    repaint();
}