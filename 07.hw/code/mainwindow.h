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

private slots:

    void on_uploadfile_clicked();

    void on_uploadfile_2_clicked();

    void on_uploadfile_3_clicked();

    void on_uploadfile_4_clicked();

    void on_uploadfile_5_clicked();

    void on_uploadfile_6_clicked();

    void on_KspinBox_valueChanged(int arg1);

    void on_MdoubleSpinBox_valueChanged(double arg1);

    void on_scaleXSpinBox_valueChanged(double arg1);

    void on_scaleYSpinBox_valueChanged(double arg1);

    void on_amplitudeSpinBox_valueChanged(double arg1);

    void on_frequencySpinBox_valueChanged(double arg1);

    void on_phaseSpinBox_valueChanged(double arg1);

    void on_levelSpinBox_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    GeneralProcess gp;
    SpecificProcess sp;
    std::unique_ptr<QImage> image;
    std::unique_ptr<QImage> image1;
    std::unique_ptr<QImage> image2;
    std::unique_ptr<QImage> image3;
};
#endif // MAINWINDOW_H
