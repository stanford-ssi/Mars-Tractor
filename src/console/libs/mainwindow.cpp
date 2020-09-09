/**
 * @file mainwindow.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#include <mainwindow.h>
#include <ui_mainwindow.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), client("192.168.1.62")
{
    ui->setupUi(this);
    connect(&client, &TcpClient::sendLog, ui->logView, &LogView::addLog);
    connect(&client, &TcpClient::sendConnectionStatus, ui->statusView,
            &StatusView::changeConnectionStatus);
    connect(&client, &TcpClient::sendFrame, ui->display, &Display::decodeFrame);
    connect(ui->logView, &LogView::sendCommand, ui->mainOverlay, &Overlay::react);
}
