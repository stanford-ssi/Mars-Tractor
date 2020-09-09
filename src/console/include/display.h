/**
 * @file display.h
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <QPainter>
#include <QWidget>
#include <opencv2/opencv.hpp>

namespace Ui
{
class Display;
}

class Display : public QWidget
{
    Q_OBJECT

  public:
    explicit Display(QWidget* parent = nullptr);

    static QImage Mat2QImage(const cv::Mat& src);
    static cv::Mat QImage2Mat(const QImage& src);

  private:
    Ui::Display* ui;

  protected:
    /**
     * @fn painEvent
     * -----------------------------
     * Overloads default paint constructor in order to render dualshock overlay svgs.
     */
    void paintEvent(QPaintEvent*) override;

  private:
    cv::Mat screen;

  public slots:
    void decodeFrame(const std::string& frameData);
};

#endif // DISPLAY_H
