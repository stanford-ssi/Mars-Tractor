/**
 * @file logview.h
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <QLabel>
#include <QWidget>
#include <string>

namespace Ui
{
class LogView;
}

class LogView : public QWidget
{
    Q_OBJECT

  public:
    explicit LogView(QWidget* parent = nullptr);
    ~LogView();

    /**
     * @fn addLog
     * -------------------------
     * Displays log message in console window.
     */
    void addLog(const std::string& text);

  private:
    Ui::LogView* ui;

  private:
    /**
     * @fn constructLog
     * -------------------------
     * Constructs a log widget to be displayed in the console.
     */
    QLabel* constructLog(const QString& text);

  private slots:
    /**
     * @fn on_lineEdit_returnPressed()
     * -------------------------
     * When enter is pressed, a command is logged to the logView
     */
    void on_lineEdit_returnPressed();

    /**
     * @fn on_scrollArea_resize()
     * -------------------------
     * Resizes scrollAreaContents to scrollArea
     */
    void on_scrollArea_resize();
};

#endif // LOGVIEW_H
