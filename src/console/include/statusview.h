/**
 * @file statusview.h
 * -----------------------------
 * @brief Defines connection icon at bottom right of gui.
 * @author Bartolone, Kai
 * @date August 2020
 */

#ifndef STATUSVIEW_H
#define STATUSVIEW_H

#include <QPainter>
#include <QSvgRenderer>
#include <QWidget>

namespace Ui
{
class StatusView;
}

class StatusView : public QWidget
{
    Q_OBJECT

  public:
    explicit StatusView(QWidget* parent = nullptr);
    ~StatusView();

  private:
    Ui::StatusView* ui;
    bool hasConnection = false;

  protected:
    /**
     * @fn painEvent
     * -----------------------------
     * Overloads default paint constructor in order to display connection status svg.
     */
    void paintEvent(QPaintEvent*) override;

  public slots:
    /**
     * @fn changeConnectionStatus
     * -------------------------
     * Changes hasConnection.
     */
    void changeConnectionStatus(bool status);
};

#endif // STATUSVIEW_H
