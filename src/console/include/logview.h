#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <QLabel>
#include <QWidget>

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

  private:
    Ui::LogView* ui;

  private:
    /**
     * @fn addLog
     * -------------------------
     * Displays log message in console window.
     */
    void addLog(const std::string& log);
};

#endif // LOGVIEW_H
