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

private:
    Ui::MainWindow *ui;
    GeneralProcess gp;
    SpecificProcess sp;
    std::unique_ptr<QImage> image;
};
#endif // MAINWINDOW_H
