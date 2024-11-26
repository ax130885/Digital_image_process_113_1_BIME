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

// 點擊上傳檔案按鈕 並且自動執行所有功能
// prob1.
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
    show_image_on_grphics_view(image, ui->originalImage);

    // 梯形幾何轉換
    // 取得參數
    double topBase = ui->topBaseSpinBox->value();       // 上底
    double bottomBase = ui->bottomBaseSpinBox->value(); // 下底
    double h = ui->heightSpinBox->value();              // 高
    // 梯形幾何轉換
    std::unique_ptr<QImage> trapezoidalGeometricTransformationImage = gp.trapezoidalGeometricTransformation(image, topBase, bottomBase, h);
    if (trapezoidalGeometricTransformationImage)
    {
        show_image_on_grphics_view(trapezoidalGeometricTransformationImage, ui->trapezoidalGeometricTransformationImage);
    }

    // 波浪幾何轉換
    // 取得參數
    double amplitude = ui->amplitudeSpinBox->value(); // 振幅
    double frequency = ui->frequencySpinBox->value(); // 頻率
    double phase = ui->phaseSpinBox->value();         // 相位
    // 波浪幾何轉換
    std::unique_ptr<QImage> wavyGeometricTransformationImage = gp.wavyGeometricTransformation(image, amplitude, frequency, phase);
    if (wavyGeometricTransformationImage)
    {
        show_image_on_grphics_view(wavyGeometricTransformationImage, ui->wavyGeometricTransformationImage);
    }

    // 圓形幾何轉換
    // 取得參數
    double radius = ui->radiusSpinBox->value(); // 半徑
    // 圓形幾何轉換
    std::unique_ptr<QImage> circularGeometricTransformationImage = gp.circularGeometricTransformation(image, radius);
    if (circularGeometricTransformationImage)
    {
        show_image_on_grphics_view(circularGeometricTransformationImage, ui->circularGeometricTransformationImage);
    }
}

// prob2.
void MainWindow::on_uploadfile_2_clicked()
{
    GeneralProcess gp(this);
    SpecificProcess sp(this);

    // 上傳第一個檔案
    auto image1 = gp.UploadFile(); // 使用 unique_ptr 接收返回值

    // 如果 image1 是 nullptr，則退出
    if (!image1)
    {
        return; // 如果 image1 是 nullptr，則退出
    }

    // 顯示第一張原圖
    show_image_on_grphics_view(image1, ui->originalImage_2);

    // 上傳第二個檔案
    auto image2 = gp.UploadFile(); // 使用 unique_ptr 接收返回值

    // 如果 image2 是 nullptr，則退出
    if (!image2)
    {
        return; // 如果 image2 是 nullptr，則退出
    }

    // 顯示第二張原圖
    show_image_on_grphics_view(image2, ui->originalImage_3); // 假設 originalImage_3 是第二個 QGraphicsView 的名稱

    // 使用小波轉換進行影像融合
    // 取得參數
    int level = ui->levelSpinBox->value(); // 層級
    QString waveletType = "Haar";          // 小波類型
    // 小波轉換
    std::unique_ptr<QImage> imageFusionImage = gp.imageFusion(image1, image2, level, waveletType);
    if (imageFusionImage)
    {
        show_image_on_grphics_view(imageFusionImage, ui->imageFusionImage);
    }
}

// void MainWindow::on_blueBar_valueChanged(int value)
// {
//     // 如果 image 是 nullptr，則退出
//     if (!image)
//     {
//         return; // 如果 image 是 nullptr，則退出
//     }

//     // 讀取bar設定的色表值
//     int red = ui->redBar->value();
//     int green = ui->greenBar->value();
//     int blue = ui->blueBar->value();

//     // 更改label顯示的色表值
//     ui->redLabel->setText("red: " + QString::number(red));
//     ui->greenLabel->setText("green: " + QString::number(green));
//     ui->blueLabel->setText("blue: " + QString::number(blue));

//     // 建立偽彩色表
//     QVector<QColor> colorTable = gp.createPseudoColorTable(red, green, blue);

//     // 繪製偽彩色影像
//     std::unique_ptr<QImage> pseudoColorImage = gp.applyPseudoColor(image, colorTable);
//     if (pseudoColorImage)
//     {
//         show_image_on_grphics_view(pseudoColorImage, ui->pseudoColorImage);
//     }

//     // 繪製色表
//     std::unique_ptr<QImage> colorTableImage = gp.createColorTableImage(colorTable);
//     if (colorTableImage)
//     {
//         show_image_on_grphics_view(colorTableImage, ui->colorTableImage);
//     }
// }

// prob3.
void MainWindow::on_uploadfile_3_clicked()
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
    show_image_on_grphics_view(image, ui->originalimage_4);

    // Simple Linear Iterative Clustering (SLIC) 實作超像素區域分割
    // 取得參數
    int k = ui->KspinBox->value();             // 超像素數量
    int m = ui->MspinBox->value();             // 超像素大小
    int maxIter = ui->maxIterSpinBox->value(); // 最大迭代次數
    // SLIC
    std::unique_ptr<QImage> SLICImage = gp.SLIC(image, k, m, maxIter);
    if (SLICImage)
    {
        show_image_on_grphics_view(SLICImage, ui->SLICImage);
    }
}