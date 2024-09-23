#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "generalprocess.h"
#include "specificprocess.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void show_image_on_grphics_view(std::unique_ptr<QImage> &image, QGraphicsView *graphicsView);
    void show_gray_hist_on_grphics_view(std::unique_ptr<QImage> &image, QGraphicsView *graphicsView);
    void show_rgb_hist_on_grphics_view(std::unique_ptr<QImage> &image, QGraphicsView *graphicsView);
    void show_origin_image(std::unique_ptr<QImage> &image);
    void show_gray_image(std::unique_ptr<QImage> &image1, std::unique_ptr<QImage> &image2);
    void show_gray_histogram(std::unique_ptr<QImage> &image1, std::unique_ptr<QImage> &image2);
    void show_diffGray(std::unique_ptr<QImage> &image);

private slots:
    void on_uploadfile_clicked();

    void on_threshold_rgb_spinbox_valueChanged();

    void on_threshold_weight_spinbox_valueChanged();

    void on_scale_height_lineEdit_textEdited();

    void on_scale_width_lineEdit_textEdited();

    void on_quantization_bits_spinbox_valueChanged();

    void on_brightness_spinbox_valueChanged();

    void on_contrast_spinbox_valueChanged();

private:
    Ui::MainWindow *ui;
    GeneralProcess gp;
    SpecificProcess sp;
    std::unique_ptr<QImage> image;
};
#endif // MAINWINDOW_H
