/** @file mainwindow.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#include <mainwindow.h>
#include <ui_mainwindow.h>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ui->widget_4->setVisible(false);
    // ui->scrollArea_2->setVisible(false);
    // ui->textBrowser->setVisible(false);

    ui->label->setVisible(true);
    ui->label->setText("true");
    std::cout << ui->label->text().toStdString() << std::endl;
}

MainWindow::~MainWindow() { delete ui; }