/** @file statusview.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#include "statusview.h"
#include "ui_statusview.h"

StatusView::StatusView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusView)
{
    ui->setupUi(this);
}

StatusView::~StatusView()
{
    delete ui;
}
