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

    // // sobel 邊緣檢測
    // std::unique_ptr<QImage> sobelImage = gp.sobelEdgeDetect(image);
    // if (sobelImage)
    // {
    //     show_image_on_grphics_view(sobelImage, ui->sobelImage);
    // }

    // // Marr-Hildreth
    // // 取得spinbox設置的sigma
    // double sigma = ui->sigma_spinbox->value();
    // // 取得spinbox設置的threshold
    // double threshold = ui->threshold_spinbox->value();
    // // 計算 Marr-Hildreth 邊緣檢測圖像
    // std::unique_ptr<QImage> marrHildrethImage = gp.MarrHildrethEdgeDetection(*image, sigma, threshold);
    // if (marrHildrethImage)
    // {
    //     show_image_on_grphics_view(marrHildrethImage, ui->marrHildrethImage);
    // }

    // // 局部統計增強
    // // 取得spinbox設置的kernelSize
    // int kernelSize = ui->localStatisticalEnhancement_kernelSize_spinbox->value();
    // // 取得spinbox設置的k0
    // double k0 = ui->localStatisticalEnhancement_k0_spinbox->value();
    // // 取得spinbox設置的k1
    // double k1 = ui->localStatisticalEnhancement_k1_spinbox->value();
    // // 取得spinbox設置的k2
    // double k2 = ui->localStatisticalEnhancement_k2_spinbox->value();
    // // 取得spinbox設置的k3
    // double k3 = ui->localStatisticalEnhancement_k3_spinbox->value();
    // // 取得spinbox設置的C
    // double C = ui->localStatisticalEnhancement_C_spinbox->value();
    // // 計算局部統計增強圖像
    // std::unique_ptr<QImage> localMeanContrastEnhancementImage = gp.localMeanContrastEnhancement(image, kernelSize, k0, k1, k2, k3, C);
    // if (localMeanContrastEnhancementImage)
    // {
    //     show_image_on_grphics_view(localMeanContrastEnhancementImage, ui->localMeanContrastEnhancementImage);
    // }

    // 新功能... (開發過程 1.在ui拉好介面 2.在此取得所需的值 3.在generalprocess.h中新增函數 4.在generalprocess.cpp中實現函數 5.在此調用函數 6.使用show_image_on_grphics_view函數顯示圖片 7.定義取值方塊的槽函數也要做相同功能)
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

void MainWindow::on_ApplySpatialFilter_clicked()
{
    if (image)
    {
        // 空間濾波
        // 取得spinbox設置的kernel size
        int spatialFilter_kernelSize = ui->spatialFilter_kernelSize_spinbox->value();
        // 取得comboBox設置的濾波種類
        QString spatialFilterType = ui->spatialFilter_comboBox->currentText();
        // 計算空間濾波圖像
        std::unique_ptr<QImage> spatialFilterImage = gp.spatialFilter(image, spatialFilter_kernelSize, spatialFilterType);
        if (spatialFilterImage)
        {
            show_image_on_grphics_view(spatialFilterImage, ui->spatialFilterImage);
        }
    }
}

void MainWindow::on_ApplySobelandLoG_clicked()
{
    // sobel 邊緣檢測
    std::unique_ptr<QImage> sobelImage = gp.sobelEdgeDetect(image);
    if (sobelImage)
    {
        show_image_on_grphics_view(sobelImage, ui->sobelImage);
    }

    // Marr-Hildreth
    // 取得spinbox設置的kernelSize
    int kernelSize = ui->log_kernelSize_spinbox->value();
    // 取得spinbox設置的sigma
    double sigma = ui->log_sigma_spinbox->value();
    // 取得spinbox設置的threshold
    double threshold = ui->log_threshold_spinbox->value();
    // 計算 Marr-Hildreth 邊緣檢測圖像
    std::unique_ptr<QImage> marrHildrethImage = gp.MarrHildrethEdgeDetection(*image, kernelSize, sigma, threshold);
    if (marrHildrethImage)
    {
        show_image_on_grphics_view(marrHildrethImage, ui->marrHildrethImage);
    }
}

void MainWindow::on_ApplylocalMeanConstrastEnhancement_clicked()
{
    // 直方圖均衡化
    std::unique_ptr<QImage> equalizedImage = gp.equalizeHistogramRGBImage(image);
    if (equalizedImage)
    {
        show_image_on_grphics_view(equalizedImage, ui->equalizeHistogramRGBImage);
    }

    // 局部統計增強
    // 取得spinbox設置的kernelSize
    int kernelSize = ui->localStatisticalEnhancement_kernelSize_spinbox->value();
    // 取得spinbox設置的k0
    double k0 = ui->localStatisticalEnhancement_k0_spinbox->value();
    // 取得spinbox設置的k1
    double k1 = ui->localStatisticalEnhancement_k1_spinbox->value();
    // 取得spinbox設置的k2
    double k2 = ui->localStatisticalEnhancement_k2_spinbox->value();
    // 取得spinbox設置的k3
    double k3 = ui->localStatisticalEnhancement_k3_spinbox->value();
    // 取得spinbox設置的C
    double C = ui->localStatisticalEnhancement_C_spinbox->value();
    // 計算局部統計增強圖像
    std::unique_ptr<QImage> localMeanContrastEnhancementImage = gp.localMeanContrastEnhancement(image, kernelSize, k0, k1, k2, k3, C);
    if (localMeanContrastEnhancementImage)
    {
        show_image_on_grphics_view(localMeanContrastEnhancementImage, ui->localMeanContrastEnhancementImage);
    }
}
