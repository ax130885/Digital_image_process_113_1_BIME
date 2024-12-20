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
    // void show_gray_hist_on_grphics_view(std::unique_ptr<QImage> &image, QGraphicsView *graphicsView);
    // void show_rgb_hist_on_grphics_view(std::unique_ptr<QImage> &image, QGraphicsView *graphicsView);

private slots:
    void on_uploadfile_clicked();

    void on_ApplySpatialFilter_clicked();

    void on_ApplySobelandLoG_clicked();

    void on_ApplylocalMeanConstrastEnhancement_clicked();

private:
    Ui::MainWindow *ui;
    GeneralProcess gp;
    SpecificProcess sp;
    std::unique_ptr<QImage> image;
};
#endif // MAINWINDOW_H
