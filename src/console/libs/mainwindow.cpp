/**
 * @file mainwindow.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#include <mainwindow.h>
#include <ui_mainwindow.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), client("192.168.1.59")
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::mousePressEvent(QMouseEvent* e)
{
    using namespace std;
    if (e->button() == Qt::LeftButton)
    {
        string message = client.getNextMessage();
        if (message != "")
        {
            ui->logView->addLog(message);
        }
        std::cout << "checked for message" << std::endl;
    }
}