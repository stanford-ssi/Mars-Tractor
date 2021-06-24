/**
 * @file mainwindow.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#include <mainwindow.h>
#include <ui_mainwindow.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_client(parent)
{
    ui->setupUi(this);
    // connect(&client, &TcpClient::sendLog, ui->logView, &LogView::addLog);
    // connect(&client, &TcpClient::sendConnectionStatus, ui->statusView,
    //         &StatusView::changeConnectionStatus);
    // connect(&client, &TcpClient::sendFrame, ui->display, &Display::decodeFrame);
    connect(ui->logView, &LogView::sendCommand, ui->mainOverlay, &Overlay::react);
    connect(ui->logView, &LogView::sendCommand, this, &MainWindow::tmp_send);

    // Network connections
    connect(&m_client, &client_interface::status_change, ui->statusView, &StatusView::changeConnectionStatus);
    connect(ui->statusView, &StatusView::go, [=]() { m_client.connect(ui->statusView->lineEditHostText(), ui->statusView->lineEditPortNumber());});
}
void MainWindow::tmp_send(const std::string& msg)
{
    message mm;
    mm.header.id = MESSAGE_TYPE::COMMAND;
    mm << msg;

char* ptr = (char*)mm.body.data();
while(*ptr != '\0')
{
  std::cout << *ptr;
  ptr++;
}
std::cout << std::endl;
    // mm.header.size = 64;
    m_client.send(mm);
}