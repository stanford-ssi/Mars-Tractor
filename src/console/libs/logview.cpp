/**
 * @file logview.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#include <logview.h>
#include <ui_logview.h>

LogView::LogView(QWidget* parent) : QWidget(parent), ui(new Ui::LogView)
{
    ui->setupUi(this);
    ui->layout->setAlignment(Qt::AlignTop);

    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(on_lineEdit_returnPressed()));
    connect(ui->scrollArea, SIGNAL(resizeEvent()), this, SLOT(on_scrollArea_resize()));
}

LogView::~LogView() { delete ui; }

void LogView::addLog(const std::string& text)
{
    // Construct log message widget
    QLabel* message = constructLog(QString(text.c_str()));

    ui->layout->addWidget(message);
}

void LogView::on_lineEdit_returnPressed()
{
    QString text = ui->lineEdit->text();

    if (!text.isEmpty())
    {
        ui->lineEdit->setText("");
        QLabel* label = constructLog(text);
        ui->layout->addWidget(label);
    }
}

QLabel* LogView::constructLog(const QString& text)
{
    QLabel* result = new QLabel();

    result->setText(text);
    result->setWordWrap(true);
    // result->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    return result;
}

void LogView::on_scrollArea_resize()
{
    ui->scrollAreaWidgetContents->setFixedWidth(ui->scrollArea->width());
}