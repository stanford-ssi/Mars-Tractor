/**
 * @file display.h
 * -----------------------------
 * @author Bartolone, Kai
 * @date August 2020
 */
// #include <glib.h>
// #include <gst/gst.h>
// #include <gst/video/videooverlay.h>

#include <QApplication>
#include <QBoxLayout>
#include <QTimer>
#include <QWidget>
#include <display.h>
#include <ui_display.h>

Display::Display(QWidget* parent) : QWidget(parent), ui(new Ui::Display)
{
    ui->setupUi(this);
    /*
    if (!g_thread_supported()) g_thread_init(NULL);

    // // gst_init(&argc, &argv);

    // // prepare the pipeline

    GstElement* pipeline = gst_pipeline_new("xvoverlay");
    GstElement* src = gst_element_factory_make("ksvideosrc", NULL);
    GstElement* sink = gst_element_factory_make("glimagesink", NULL);
    // //   GstElement *pipeline;
    // //   pipeline =
    // //         gst_parse_launch
    // //         ("-v ksvideosrc do-stats=TRUE ! videoconvert ! qtvideosink",
    // //         NULL);
    gst_bin_add_many(GST_BIN(pipeline), src, sink, NULL);
    gst_element_link(src, sink);

    // // prepare the ui

    // // WId xwinid = window->winId();
    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(sink), this->winId());

    // // run the pipeline

    GstStateChangeReturn sret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
    if (sret == GST_STATE_CHANGE_FAILURE)
    {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
        // Exit application
        QTimer::singleShot(0, QApplication::activeWindow(), SLOT(quit()));
    }

    // gst_element_set_state(pipeline, GST_STATE_NULL);
    // gst_object_unref(pipeline);

    / Free resources /
    // if (msg != NULL) gst_message_unref(msg);
    // gst_object_unref(bus);
    // gst_element_set_state(pipeline, GST_STATE_NULL);
    // gst_object_unref(pipeline);
    */
}
