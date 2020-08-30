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
    ~Display();

    static QImage Mat2QImage(cv::Mat const& src);
    static cv::Mat QImage2Mat(QImage const& src);

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
    /**
     * @fn paintMat
     * -------------------------
     * Paints OpenCV mat object on widget. Can only be called in paintEvent.
     * @param img is the source image to be painted
     */
    void paintMat(QPaintDevice* device, const cv::Mat& src);
};

#endif // DISPLAY_H
