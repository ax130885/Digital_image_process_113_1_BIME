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
    double scaleX = ui->scaleXSpinBox->value(); // x 軸縮放比例
    double scaleY = ui->scaleYSpinBox->value(); // y 軸縮放比例

    // 梯形幾何轉換
    std::unique_ptr<QImage> trapezoidalGeometricTransformationImage = gp.trapezoidalGeometricTransformation(image, scaleX, scaleY);
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
    std::unique_ptr<QImage> circularGeometricTransformationImage = gp.circularGeometricTransformation(image);
    if (circularGeometricTransformationImage)
    {
        show_image_on_grphics_view(circularGeometricTransformationImage, ui->circularGeometricTransformationImage);
    }
}

void MainWindow::on_scaleXSpinBox_valueChanged(double arg1)
{
    if (!image)
    {
        return;
    }

    // 梯形幾何轉換
    // 取得參數
    double scaleX = ui->scaleXSpinBox->value(); // x 軸縮放比例
    double scaleY = ui->scaleYSpinBox->value(); // y 軸縮放比例

    // 梯形幾何轉換
    std::unique_ptr<QImage> trapezoidalGeometricTransformationImage = gp.trapezoidalGeometricTransformation(image, scaleX, scaleY);
    if (trapezoidalGeometricTransformationImage)
    {
        show_image_on_grphics_view(trapezoidalGeometricTransformationImage, ui->trapezoidalGeometricTransformationImage);
    }
}

void MainWindow::on_scaleYSpinBox_valueChanged(double arg1)
{
    if (!image)
    {
        return;
    }

    // 梯形幾何轉換
    // 取得參數
    double scaleX = ui->scaleXSpinBox->value(); // x 軸縮放比例
    double scaleY = ui->scaleYSpinBox->value(); // y 軸縮放比例

    // 梯形幾何轉換
    std::unique_ptr<QImage> trapezoidalGeometricTransformationImage = gp.trapezoidalGeometricTransformation(image, scaleX, scaleY);
    if (trapezoidalGeometricTransformationImage)
    {
        show_image_on_grphics_view(trapezoidalGeometricTransformationImage, ui->trapezoidalGeometricTransformationImage);
    }
}

void MainWindow::on_amplitudeSpinBox_valueChanged(double arg1)
{
    if (!image)
    {
        return;
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
}

void MainWindow::on_frequencySpinBox_valueChanged(double arg1)
{
    if (!image)
    {
        return;
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
}

void MainWindow::on_phaseSpinBox_valueChanged(double arg1)
{
    if (!image)
    {
        return;
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
}

// prob2.
void MainWindow::on_uploadfile_2_clicked()
{
    if (image1 == nullptr || image2 == nullptr)
    {
        QMessageBox::critical(this, "Error", "Please upload images 1 & 2 first.");
        return;
    }

    // 使用小波轉換進行影像融合
    // 取得參數
    int level = ui->levelSpinBox->value(); // 層級
    QString waveletType = "Haar";          // 小波類型
    // 小波轉換
    std::vector<std::unique_ptr<QImage>> images;
    auto image1_temp = std::make_unique<QImage>(*this->image1);
    auto image2_temp = std::make_unique<QImage>(*this->image2);
    images.push_back(std::move(image1_temp));
    images.push_back(std::move(image2_temp));
    if (image3 != nullptr)
    {
        auto image3_temp = std::make_unique<QImage>(*this->image3);
        images.push_back(std::move(image3_temp));
    }
    // images.push_back(std::move(image1));
    // images.push_back(std::move(image2));
    // images.push_back(std::move(image3));
    std::unique_ptr<QImage> imageFusionImage = gp.imageFusion(images, level, waveletType);
    if (imageFusionImage)
    {
        show_image_on_grphics_view(imageFusionImage, ui->imageFusionImage);
    }
}

void MainWindow::on_uploadfile_4_clicked()
{
    GeneralProcess gp(this);
    SpecificProcess sp(this);

    // 上傳第一個檔案
    image1 = gp.UploadFile(); // 使用 unique_ptr 接收返回值

    // 如果 image1 是 nullptr，則退出
    if (!image1)
    {
        return; // 如果 image1 是 nullptr，則退出
    }

    // 顯示第一張原圖
    show_image_on_grphics_view(image1, ui->originalImage_2);
}

void MainWindow::on_uploadfile_5_clicked()
{
    // 上傳第二個檔案
    image2 = gp.UploadFile(); // 使用 unique_ptr 接收返回值

    // 如果 image2 是 nullptr，則退出
    if (!image2)
    {
        return; // 如果 image2 是 nullptr，則退出
    }

    // 顯示第二張原圖
    show_image_on_grphics_view(image2, ui->originalImage_3); // 假設 originalImage_3 是第二個 QGraphicsView 的名稱
}

void MainWindow::on_uploadfile_6_clicked()
{
    image3 = gp.UploadFile(); // 使用 unique_ptr 接收返回值

    // 如果 image3 是 nullptr，則退出
    if (!image3)
    {

        QMessageBox::critical(this, "Error", "Please upload images 1 & 2 first.");
        return; // 如果 image3 是 nullptr，則退出
    }

    // 顯示第三張原圖
    show_image_on_grphics_view(image3, ui->originalImage_4); // 假設 originalImage_4 是第三個 QGraphicsView 的名稱
}

void MainWindow::on_levelSpinBox_valueChanged(double arg1)
{
    if (image1 == nullptr || image2 == nullptr)
    {
        return;
    }

    // 使用小波轉換進行影像融合
    // 取得參數
    int level = ui->levelSpinBox->value(); // 層級
    QString waveletType = "Haar";          // 小波類型
    // 小波轉換
    std::vector<std::unique_ptr<QImage>> images;
    auto image1_temp = std::make_unique<QImage>(*this->image1);
    auto image2_temp = std::make_unique<QImage>(*this->image2);
    images.push_back(std::move(image1_temp));
    images.push_back(std::move(image2_temp));
    if (image3 != nullptr)
    {
        auto image3_temp = std::make_unique<QImage>(*this->image3);
        images.push_back(std::move(image3_temp));
    }
    // images.push_back(std::move(image1));
    // images.push_back(std::move(image2));
    // images.push_back(std::move(image3));
    std::unique_ptr<QImage> imageFusionImage = gp.imageFusion(images, level, waveletType);
    if (imageFusionImage)
    {
        show_image_on_grphics_view(imageFusionImage, ui->imageFusionImage);
    }

}

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
    int k = ui->KspinBox->value();          // 超像素數量
    double m = ui->MdoubleSpinBox->value(); // 超像素大小
    // SLIC
    std::tuple<std::unique_ptr<QImage>, std::unique_ptr<QImage>, std::unique_ptr<QImage>> SLICImage = gp.SLIC(image, k, m);
    if (std::get<0>(SLICImage))
    {
        show_image_on_grphics_view(std::get<0>(SLICImage), ui->boundaryImage);
    }
    if (std::get<1>(SLICImage))
    {
        show_image_on_grphics_view(std::get<1>(SLICImage), ui->segmentedImage);
    }
}

void MainWindow::on_KspinBox_valueChanged(int arg1)
{
    if (!image)
    {
        return;
    }
    // 取得參數
    int k = ui->KspinBox->value();          // 超像素數量
    double m = ui->MdoubleSpinBox->value(); // 超像素大小
    // SLIC
    std::tuple<std::unique_ptr<QImage>, std::unique_ptr<QImage>, std::unique_ptr<QImage>> SLICImage = gp.SLIC(image, k, m);
    if (std::get<0>(SLICImage))
    {
        show_image_on_grphics_view(std::get<0>(SLICImage), ui->boundaryImage);
    }
    if (std::get<1>(SLICImage))
    {
        show_image_on_grphics_view(std::get<1>(SLICImage), ui->segmentedImage);
    }
}

void MainWindow::on_MdoubleSpinBox_valueChanged(double arg1)
{
    if (!image)
    {
        return;
    }
    // 取得參數
    int k = ui->KspinBox->value();          // 超像素數量
    double m = ui->MdoubleSpinBox->value(); // 超像素大小
    // SLIC
    std::tuple<std::unique_ptr<QImage>, std::unique_ptr<QImage>, std::unique_ptr<QImage>> SLICImage = gp.SLIC(image, k, m);
    if (std::get<0>(SLICImage))
    {
        show_image_on_grphics_view(std::get<0>(SLICImage), ui->boundaryImage);
    }
    if (std::get<1>(SLICImage))
    {
        show_image_on_grphics_view(std::get<1>(SLICImage), ui->segmentedImage);
    }
}



