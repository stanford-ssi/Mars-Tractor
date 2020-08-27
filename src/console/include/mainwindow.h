/** @file mainwindow.h
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;

protected:
    /**
     * @fn painEvent
     * -----------------------------
     * Overloads default paint constructor in order to display connection icons. 
     */
    void paintEvent(QPaintEvent*) override;
};

#endif    // MAINWINDOW_H
