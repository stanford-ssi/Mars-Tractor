/**
 * @file mainwindow.h
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <gamepad.h>
#include <iostream>
#include <string>
#include <client_interface.hpp>
#include <thread>
#include <SFML/Window/Joystick.hpp>

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

  protected:
    // void parse_messages();
void tmp_send(const std::string& msg);
    // std::thread


  private:
    Ui::MainWindow* ui;
    client_interface m_client;
};

#endif // MAINWINDOW_H
