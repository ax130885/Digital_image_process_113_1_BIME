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

void MainWindow::on_uploadfile_clicked()
{
    GeneralProcess gp(this);
    SpecificProcess sp(this);

    // 上傳檔案
    image = gp.UploadFile(); // 使用 unique_ptr 接收返回值
    // show_origin_image(image);
    show_image_on_grphics_view(image, ui->originalimage);
    show_rgb_hist_on_grphics_view(image, ui->originalimage_rgb_histogram);

    // 計算灰階
    std::unique_ptr<QImage> grayImage_rgb = sp.grayscale_by_avg_rgb(image);
    std::unique_ptr<QImage> grayImage_weight = sp.grayscale_by_eyes_weight_rgb(image);
    // show_gray_image(grayImage_rgb, grayImage_weight);
    show_image_on_grphics_view(grayImage_rgb, ui->grayimage_rgb);
    show_image_on_grphics_view(grayImage_weight, ui->grayimage_weight);
    // show_gray_histogram(grayImage_rgb, grayImage_weight)
    show_gray_hist_on_grphics_view(grayImage_rgb, ui->grayhistogram_rgb);
    show_gray_hist_on_grphics_view(grayImage_weight, ui->grayhistogram_weight);

    // 計算差異
    std::unique_ptr<QImage> diffGray = sp.calculateGrayDifference(grayImage_rgb, grayImage_weight);
    // show_diffGray(diffGray);
    show_image_on_grphics_view(diffGray, ui->grayscalediff);
    show_gray_hist_on_grphics_view(diffGray, ui->graydiffhistogram);

    // 二值化
    // 取得spinbox設置的threshold值
    int threshold_rgb = ui->threshold_rgb_spinbox->value();
    int threshold_weight = ui->threshold_weight_spinbox->value();
    // 計算二值化圖像
    std::unique_ptr<QImage> binaryImage_rgb = gp.binaryzation(grayImage_rgb, &threshold_rgb);
    std::unique_ptr<QImage> binaryImage_weight = gp.binaryzation(grayImage_weight, &threshold_weight);
    show_image_on_grphics_view(binaryImage_rgb, ui->binaryimage_rgb);
    show_image_on_grphics_view(binaryImage_weight, ui->binaryimage_weight);
    show_gray_hist_on_grphics_view(binaryImage_rgb, ui->binaryhistogram_rgb);
    show_gray_hist_on_grphics_view(binaryImage_weight, ui->binaryhistogram_weight);

    // 縮放
    // 取得lineEdit設置的縮放大小
    int width = ui->scale_width_lineEdit->text().toInt();
    int height = ui->scale_height_lineEdit->text().toInt();
    // 計算縮放圖像
    std::unique_ptr<QImage> scaledImage = gp.scaleImageBilinear(image, &width, &height);
    show_image_on_grphics_view(scaledImage, ui->scaledImage);
    show_rgb_hist_on_grphics_view(scaledImage, ui->scaledImage_rgb_histogram);

    // 量化
    int bits = ui->quantization_bits_spinbox->value();
    std::unique_ptr<QImage> quantizedImage = gp.quantization(image, &bits);
    show_image_on_grphics_view(quantizedImage, ui->quantizedImage);
    show_rgb_hist_on_grphics_view(quantizedImage, ui->quantizedImage_rgb_histogram);

    // 調整亮度
    int brightness = ui->brightness_spinbox->value();
    std::unique_ptr<QImage> brightnessImage = gp.adjustBrightness(image, &brightness);
    show_image_on_grphics_view(brightnessImage, ui->brightnessImage);
    show_rgb_hist_on_grphics_view(brightnessImage, ui->brightnessImage_rgb_histogram);

    // 調整對比
    float contrast = ui->contrast_spinbox->value();
    std::unique_ptr<QImage> contrastImage = gp.adjustContrast(image, &contrast);
    show_image_on_grphics_view(contrastImage, ui->contrastImage);
    show_rgb_hist_on_grphics_view(contrastImage, ui->contrastImage_rgb_histogram);

    // 直方圖均衡
    std::unique_ptr<QImage> equalizedImage = gp.equalizeHistogramRGBImage(image);
    show_image_on_grphics_view(equalizedImage, ui->equalizedImage);
    show_rgb_hist_on_grphics_view(equalizedImage, ui->equalizedImage_rgb_histogram);

    // 新功能... (開發過程 1.在ui拉好介面 2.在此取得所需的值 3.在generalprocess.h中新增函數 4.在generalprocess.cpp中實現函數 5.在此調用函數 6.使用show_image_on_grphics_view函數顯示圖片 7.定義取值方塊的槽函數也要做相同功能)
}

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

void MainWindow::show_gray_hist_on_grphics_view(std::unique_ptr<QImage> &image, QGraphicsView *graphicsView)
{
    // 計算灰階直方圖
    std::unique_ptr<QImage> histImage = gp.calculateGrayHistogram(image);

    // 將 QImage 轉換為 QPixmap
    QPixmap pixmap = QPixmap::fromImage(*histImage); // 使用解引用來獲取 QImage

    // 創建 QGraphicsScene 並將其設定到 QGraphicsView
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(pixmap);

    // 假設 grayhistogram 是在 ui 中設計的 QGraphicsView 的名稱
    graphicsView->setScene(scene);
    graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio); // 調整視圖以適應圖片
}

void MainWindow::show_rgb_hist_on_grphics_view(std::unique_ptr<QImage> &image, QGraphicsView *graphicsView)
{
    // 計算 RGB 直方圖
    std::unique_ptr<QImage> histImage = gp.calculateRGBHistogram(image);

    // 將 QImage 轉換為 QPixmap
    QPixmap pixmap = QPixmap::fromImage(*histImage); // 使用解引用來獲取 QImage

    // 創建 QGraphicsScene 並將其設定到 QGraphicsView
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(pixmap);

    // 假設 rgbhistogram 是在 ui 中設計的 QGraphicsView 的名稱
    graphicsView->setScene(scene);
    graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio); // 調整視圖以適應圖片
}

void MainWindow::on_threshold_rgb_spinbox_valueChanged()
{
    // 二值化
    if (image)
    {
        // 取得spinbox設置的threshold值
        int threshold_rgb = ui->threshold_rgb_spinbox->value();
        // 計算二值化圖像
        std::unique_ptr<QImage> binaryImage_rgb = gp.binaryzation(image, &threshold_rgb);
        show_image_on_grphics_view(binaryImage_rgb, ui->binaryimage_rgb);
        show_gray_hist_on_grphics_view(binaryImage_rgb, ui->binaryhistogram_rgb);
    }
}

void MainWindow::on_threshold_weight_spinbox_valueChanged()
{
    // 二值化
    if (image)
    {
        // 取得spinbox設置的threshold值
        int threshold_weight = ui->threshold_weight_spinbox->value();
        // 計算二值化圖像
        std::unique_ptr<QImage> binaryImage_weight = gp.binaryzation(image, &threshold_weight);
        show_image_on_grphics_view(binaryImage_weight, ui->binaryimage_weight);
        show_gray_hist_on_grphics_view(binaryImage_weight, ui->binaryhistogram_weight);
    }
}

void MainWindow::on_scale_height_lineEdit_textEdited()
{
    // 縮放

    // 檢查數值範圍
    bool ok;
    int value = ui->scale_height_lineEdit->text().toInt(&ok);
    if (ok)
    {
        if (value < 1)
        {
            value = 1;
        }
        else if (value > 1080)
        {
            value = 1080;
        }
        ui->scale_height_lineEdit->setText(QString::number(value));
    }
    // 輸入不是數字時，設置為1
    else
    {
        ui->scale_height_lineEdit->setText("1");
    }

    if (image)
    {
        // 縮放
        // 取得lineEdit設置的縮放大小
        int width = ui->scale_width_lineEdit->text().toInt();
        int height = ui->scale_height_lineEdit->text().toInt();
        // 計算縮放圖像
        std::unique_ptr<QImage> scaledImage = gp.scaleImageBilinear(image, &width, &height);
        show_image_on_grphics_view(scaledImage, ui->scaledImage);
        show_rgb_hist_on_grphics_view(scaledImage, ui->scaledImage_rgb_histogram);
    }
}

void MainWindow::on_scale_width_lineEdit_textEdited()
{
    // 縮放

    // 檢查數值範圍
    bool ok;
    int value = ui->scale_width_lineEdit->text().toInt(&ok);
    if (ok)
    {
        if (value < 1)
        {
            value = 1;
        }
        else if (value > 1080)
        {
            value = 1080;
        }
        ui->scale_width_lineEdit->setText(QString::number(value));
    }
    // 輸入不是數字時，設置為1
    else
    {
        ui->scale_width_lineEdit->setText("1");
    }

    if (image)
    {
        // 縮放
        // 取得lineEdit設置的縮放大小
        int width = ui->scale_width_lineEdit->text().toInt();
        int height = ui->scale_height_lineEdit->text().toInt();
        // 計算縮放圖像
        std::unique_ptr<QImage> scaledImage = gp.scaleImageBilinear(image, &width, &height);
        show_image_on_grphics_view(scaledImage, ui->scaledImage);
        show_rgb_hist_on_grphics_view(scaledImage, ui->scaledImage_rgb_histogram);
    }
}

void MainWindow::on_quantization_bits_spinbox_valueChanged()
{
    // 量化
    int bits = ui->quantization_bits_spinbox->value();
    std::unique_ptr<QImage> quantizedImage = gp.quantization(image, &bits);
    show_image_on_grphics_view(quantizedImage, ui->quantizedImage);
    show_rgb_hist_on_grphics_view(quantizedImage, ui->quantizedImage_rgb_histogram);
}

void MainWindow::on_brightness_spinbox_valueChanged()
{
    // 調整亮度
    int brightness = ui->brightness_spinbox->value();
    std::unique_ptr<QImage> brightnessImage = gp.adjustBrightness(image, &brightness);
    show_image_on_grphics_view(brightnessImage, ui->brightnessImage);
    show_rgb_hist_on_grphics_view(brightnessImage, ui->brightnessImage_rgb_histogram);
}

void MainWindow::on_contrast_spinbox_valueChanged()
{
    // 調整對比
    float contrast = ui->contrast_spinbox->value();
    std::unique_ptr<QImage> contrastImage = gp.adjustContrast(image, &contrast);
    show_image_on_grphics_view(contrastImage, ui->contrastImage);
    show_rgb_hist_on_grphics_view(contrastImage, ui->contrastImage_rgb_histogram);
}
