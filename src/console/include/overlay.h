/** @file overlay.h
 * -----------------------------
 * @brief Defines dualshock overlay.
 * @author Bartolone, Kai
 * @date August 2020
 */

#ifndef OVERLAY_H
#define OVERLAY_H

#include <QPaintDevice>
#include <QPainter>
#include <QSvgRenderer>
#include <QWidget>

namespace Ui
{
    class Overlay;
}

class Overlay : public QWidget
{
    Q_OBJECT

public:
    explicit Overlay(QWidget* parent = nullptr);
    ~Overlay();
/** Private Variables */
private:
    Ui::Overlay* ui;

protected:
/**
 * @fn painEvent
 * -----------------------------
 * Overloads default paint constructor in order to render dualshock overlay svgs.
 */
    void paintEvent(QPaintEvent*) override;

/** Private Functions */
private:
/**
 * @fn getScale
 * -----------------------------
 * Returns the scale of the base dualshock svg.
 * @param defaultSize is provided by a member function of the svg renderer
 * @param viewBox is the size of the widget the svg is drawn on
 */
    double getScale(QSize defaultSize, QSize viewBox);

/**
 * @fn locateCorner
 * -----------------------------
 * Locates the corner point of the base dualshock svg on the widget.
 * @param defaultSize is provided by a member function of the svg renderer
 * @param viewBox is the size of the widget the svg is drawn on
 */
    QPoint locateCorner(QSize defaultSize, QSize viewBox);
};

#endif    // OVERLAY_H