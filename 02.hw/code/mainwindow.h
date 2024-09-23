#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "generalprocess.h"
#include "specificprocess.h"

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

    void show_origin_image(std::unique_ptr<QImage> &image);
    void show_gray_image(std::unique_ptr<QImage> &image1, std::unique_ptr<QImage> &image2);
    void show_gray_histogram(std::unique_ptr<QImage> &image1, std::unique_ptr<QImage> &image2);
    void show_diffGray(std::unique_ptr<QImage> &image);

private slots:
    void on_uploadfile_clicked();

private:
    Ui::MainWindow *ui;
    GeneralProcess *gp;
    SpecificProcess *sp;
};
#endif // MAINWINDOW_H
