/** @file overlay.h
 * -----------------------------
 * @brief Defines dualshock overlay.
 * @author Bartolone, Kai
 * @date August 2020
 */

#ifndef OVERLAY_H
#define OVERLAY_H

#include <QMouseEvent>
#include <QPaintDevice>
#include <QPainter>
#include <QSvgRenderer>
#include <QWidget>
#include <cmath>
#include <gamepad.h>
#include <iostream>
#include <unordered_map>

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

    // /** @fn load
    //  * -----------------------------
    //  * Loads a gamepad pointer to display overlays.
    //  */
    // void load(Gamepad* gamepad);

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

    /**
     * @fn mousePressEvent
     * -----------------------------
     * FOR DEMO PURPOSES ONLY
     */
    void mousePressEvent(QMouseEvent* event) override;

    Gamepad gamepad;

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

    /**
     * @fn drawAll
     * -----------------------------
     * Draws all activation overlays.
     * @param scale is take the base svg renderer
     */
    void drawAll(QPaintDevice* device, QPoint corner, double scale);

    /**
     * @fn paintTest
     * -----------------------------
     * Draws all button overlays in a loop
     * ONLY FOR TEST - will not be able to resize widget
     * @param scale is take the base svg renderer
     */
    void paintTest(QPaintDevice* device, QPoint corner, double scale);
};

#endif // OVERLAY_H
