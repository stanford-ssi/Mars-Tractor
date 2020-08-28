#include <mainwindow.h>
#include <ui_mainwindow.h>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget_4->setVisible(false);
    ui->scrollArea_2->setVisible(false);
    ui->textBrowser->setVisible(false);
}

MainWindow::~MainWindow() { delete ui; }