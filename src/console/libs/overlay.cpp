/** @file overlay.cpp
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */

#include <overlay.h>
#include <ui_overlay.h>

Overlay::Overlay(QWidget* parent) : QWidget(parent), ui(new Ui::Overlay) { ui->setupUi(this); }

void Overlay::paintEvent(QPaintEvent*)
{
    bool hasConnection = true; // TODO: fix for true server connection
    QSvgRenderer* renderer;

    // Get base svg for widget
    if (hasConnection)
    {
        renderer = new QSvgRenderer(QString("assets/overlay/base.svg"));
    }
    // If not connected, paint disconnected.svg and return
    else
    {
        renderer = new QSvgRenderer(QString("assets/overlay/disconnected.svg"));
        QPainter painter(this);
        renderer->render(&painter);
        renderer->setViewBox(QRectF(0, 0, this->width(), this->height()));
        delete renderer;
        return;
    }
    renderer->setAspectRatioMode(Qt::KeepAspectRatio);

    // Paint base svg on widget
    QPainter painter(this);
    renderer->render(&painter);
    renderer->setViewBox(QRectF(0, 0, this->width(), this->height()));

    QPoint corner = locateCorner(renderer->defaultSize(), renderer->viewBox().size());
    double scale = getScale(renderer->defaultSize(), renderer->viewBox().size());
    drawAll(this, corner, scale);

    delete renderer;
}

Overlay::~Overlay() { delete ui; }

QPoint Overlay::locateCorner(QSize defaultSize, QSize viewBox)
{
    double defaultAR = (double)defaultSize.width() / (double)defaultSize.height();
    double viewAR = (double)viewBox.width() / (double)viewBox.height();

    //@var arCoeff lets us know which side of the svg borders the widget
    double arCoeff = viewAR / defaultAR;
    double width, height;
    int x, y;

    if (arCoeff > 1)
    {
        height = (double)viewBox.height();
        width = height * defaultAR;
        y = 0;
        x = (int)(.5 + ((double)viewBox.width() - width) / 2);
    }
    else if (arCoeff < 1)
    {
        width = (double)viewBox.width();
        height = width * 1 / defaultAR;
        x = 0;
        y = (int)(.5 + ((double)viewBox.height() - height) / 2);
    }
    else
    {
        x = 0;
        y = 0;
    }

    return QPoint(x, y);
}

double Overlay::getScale(QSize defaultSize, QSize viewBox)
{
    double result;
    QPoint corner = locateCorner(defaultSize, viewBox);

    // Since svg maintains aspect ratio, only height or width is needed
    double width = (double)viewBox.width() - 2 * corner.x();
    result = width / (double)defaultSize.width();

    return result;
}

void Overlay::drawAll(QPaintDevice* device, QPoint corner, double scale)
{
    using namespace std;

    QPoint point = QPoint(0, 0);
    QSvgRenderer renderer;

    unordered_map<string, QPoint> icons = {
        {"cursor", {269, 119}},      {"dpad_down", {136, 255}},
        {"dpad_left", {92, 226}},    {"dpad_right", {165, 226}},
        {"dpad_up", {136, 181}},     {"home", {382, 344}},
        {"left_bumper", {109, 94}},  {"left_stick_pressed", {228, 308}},
        {"left_trigger", {108, 0}},  {"o_button", {682, 217}},
        {"right_bumper", {598, 94}}, {"right_stick_pressed", {484, 308}},
        {"right_trigger", {597, 0}}, {"square_button", {567, 217}},
        {"share", {227, 142}},       {"options", {551, 142}},
        {"right_stick", {484, 308}}, {"left_stick", {228, 308}},
        {"touchpad", {272, 122}},    {"triangle_button", {629, 159}},
        {"x_button", {629, 276}}};

    int i = 0;
    for (pair<string, QPoint> pair : icons)
    {
        if (i > 0) return;
        QPoint test;
        if (pair.second.x() == 0)
        {
            cout << pair.first << endl;
            i++;
            //{382, 382 - 38}{690, 217}
            test.setX(567 + 170 - 55);
            test.setY(217);
            cout << test.x() << " " << test.y() << endl;
        }
        else
        {
            cout << pair.first << endl;
            test.setX(pair.second.x());
            test.setY(pair.second.y());
        }

        string filename = "assets/overlay/" + pair.first + ".svg";
        renderer.load(QString(filename.c_str()));

        int width = (int)round((double)renderer.defaultSize().width() * scale);
        int height = (int)round((double)renderer.defaultSize().height() * scale);

        QPoint location = QPoint((int)round((double)test.x() * scale) + corner.x(),
                                 (int)round((double)test.y() * scale) + corner.y());
        cout << location.x() << " " << location.y() << " " << scale << endl;

        QImage image(width, height, QImage::Format_ARGB32);
        image.fill(Qt::transparent);
        QPainter imagePainter(&image);
        renderer.render(&imagePainter);

        cout << width << " " << height << endl;

        QPainter painter(device);
        painter.drawImage(location, image);
    }
}