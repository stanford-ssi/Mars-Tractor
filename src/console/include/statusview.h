/** @file statusview.h
 * -----------------------------
 * @brief Defines connection icon at bottom right of gui.
 * @author Bartolone, Kai
 * @date August 2020
 */

#ifndef STATUSVIEW_H
#define STATUSVIEW_H

#include <QWidget>

namespace Ui {
class StatusView;
}

class StatusView : public QWidget
{
    Q_OBJECT

public:
    explicit StatusView(QWidget *parent = nullptr);
    ~StatusView();

private:
    Ui::StatusView *ui;
};

#endif // STATUSVIEW_H
