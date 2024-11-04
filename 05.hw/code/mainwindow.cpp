#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "generalprocess.h"
#include "specificprocess.h"
#include <QImage>
#include <QGraphicsScene>
#include <QPixmap>
#include <QMessageBox>
#include <QFileDialog>
#include <QImageReader>
#include <QGraphicsPixmapItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 點擊上傳檔案按鈕 並且自動執行所有功能
void MainWindow::on_uploadfile_clicked()
{
    GeneralProcess gp(this);
    SpecificProcess sp(this);

    // 上傳檔案
    image = gp.UploadFile(); // 使用 unique_ptr 接收返回值

    // 如果 image 是 nullptr，則退出
    if (!image)
    {
        return; // 如果 image 是 nullptr，則退出
    }

    // 顯示原圖
    show_image_on_grphics_view(image, ui->originalimage);
}

// 顯示圖片(通用功能)
void MainWindow::show_image_on_grphics_view(std::unique_ptr<QImage> &image, QGraphicsView *graphicsView)
{
    // 將 QImage 轉換為 QPixmap
    QPixmap pixmap = QPixmap::fromImage(*image);

    // 創建 QGraphicsScene 並將其設定到 QGraphicsView
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(pixmap);

    // 設定 QGraphicsView 的 scene
    graphicsView->setScene(scene);
    graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio); // 調整視圖以適應圖片
}

// 留著當範例
// void MainWindow::on_ApplyFFT_clicked()
// {
//     if (image)
//     {
//         auto [shift_dft, fftImage_magnitude, fftImage_phase] = gp.fft(*image, "show");
//         if (fftImage_magnitude && fftImage_phase)
//         {
//             show_image_on_grphics_view(fftImage_magnitude, ui->fftImage_magnitude);
//             show_image_on_grphics_view(fftImage_phase, ui->fftImage_phase);
//         }

//         // IFFT
//         std::unique_ptr<QImage> ifftImage = gp.ifft(shift_dft);
//         if (ifftImage)
//         {

//             show_image_on_grphics_view(ifftImage, ui->ifftImage);
//         }
//         std::unique_ptr<QImage> diff = sp.diffImage(*image, *ifftImage);
//         if (diff)
//         {
//             show_image_on_grphics_view(diff, ui->diff);
//         }
//     }
// }
