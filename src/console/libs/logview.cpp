#include "logview.h"
#include "ui_logview.h"

LogView::LogView(QWidget* parent) : QWidget(parent), ui(new Ui::LogView)
{
    ui->setupUi(this);
    addLog("suck");
}

LogView::~LogView() { delete ui; }

void LogView::addLog(const std::string& log)
{
    // Construct log message widget
    QLabel* message = new QLabel();
    message->setText(QString(log.c_str()));
    message->setWordWrap(true);

    ui->layout->addWidget(message);
}