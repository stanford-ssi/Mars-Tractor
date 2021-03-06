/**
 * @file mainwindow.h
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <client.hpp>
#include <gamepad.h>
#include <iostream>
#include <string>

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

  private:
    Ui::MainWindow* ui;
    TcpClient client;
};

#endif // MAINWINDOW_H
