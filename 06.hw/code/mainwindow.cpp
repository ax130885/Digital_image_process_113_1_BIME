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

    // rgb2cmy
    std::unique_ptr<QImage> cmyImage = gp.rgb2cmy(image);
    if (cmyImage)
    {
        show_image_on_grphics_view(cmyImage, ui->cmyImage);
    }

    // rgb2hsi
    std::unique_ptr<QImage> hsiImage = gp.rgb2hsi(image);
    if (hsiImage)
    {
        show_image_on_grphics_view(hsiImage, ui->hsiImage);
    }

    // rgb2xyz
    std::unique_ptr<QImage> xyzImage = gp.rgb2xyz(image);
    if (xyzImage)
    {
        show_image_on_grphics_view(xyzImage, ui->xyzImage);
    }

    // rgb2lab
    std::unique_ptr<QImage> labImage = gp.rgb2lab(image);
    if (labImage)
    {
        show_image_on_grphics_view(labImage, ui->labImage);
    }

    // rgb2yuv
    std::unique_ptr<QImage> yuvImage = gp.rgb2yuv(image);
    if (yuvImage)
    {
        show_image_on_grphics_view(yuvImage, ui->yuvImage);
    }
}

// prob2.
void MainWindow::on_uploadfile_2_clicked()
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
    show_image_on_grphics_view(image, ui->originalImage_2);

    // 讀取bar設定的色表值
    int red = ui->redBar->value();
    int green = ui->greenBar->value();
    int blue = ui->blueBar->value();

    // 更改label顯示的色表值
    ui->redLabel->setText("red: " + QString::number(red));
    ui->greenLabel->setText("green: " + QString::number(green));
    ui->blueLabel->setText("blue: " + QString::number(blue));

    // 建立偽彩色表
    QVector<QColor> colorTable = gp.createPseudoColorTable(red, green, blue);

    // 繪製偽彩色影像
    std::unique_ptr<QImage> pseudoColorImage = gp.applyPseudoColor(image, colorTable);
    if (pseudoColorImage)
    {
        show_image_on_grphics_view(pseudoColorImage, ui->pseudoColorImage);
    }

    // 繪製色表
    std::unique_ptr<QImage> colorTableImage = gp.createColorTableImage(colorTable);
    if (colorTableImage)
    {
        show_image_on_grphics_view(colorTableImage, ui->colorTableImage);
    }
}

void MainWindow::on_redBar_valueChanged(int value)
{
    // 如果 image 是 nullptr，則退出
    if (!image)
    {
        return; // 如果 image 是 nullptr，則退出
    }

    // 讀取bar設定的色表值
    int red = ui->redBar->value();
    int green = ui->greenBar->value();
    int blue = ui->blueBar->value();

    // 更改label顯示的色表值
    ui->redLabel->setText("red: " + QString::number(red));
    ui->greenLabel->setText("green: " + QString::number(green));
    ui->blueLabel->setText("blue: " + QString::number(blue));

    // 建立偽彩色表
    QVector<QColor> colorTable = gp.createPseudoColorTable(red, green, blue);

    // 繪製偽彩色影像
    std::unique_ptr<QImage> pseudoColorImage = gp.applyPseudoColor(image, colorTable);
    if (pseudoColorImage)
    {
        show_image_on_grphics_view(pseudoColorImage, ui->pseudoColorImage);
    }

    // 繪製色表
    std::unique_ptr<QImage> colorTableImage = gp.createColorTableImage(colorTable);
    if (colorTableImage)
    {
        show_image_on_grphics_view(colorTableImage, ui->colorTableImage);
    }
}

void MainWindow::on_greenBar_valueChanged(int value)
{
    // 如果 image 是 nullptr，則退出
    if (!image)
    {
        return; // 如果 image 是 nullptr，則退出
    }

    // 讀取bar設定的色表值
    int red = ui->redBar->value();
    int green = ui->greenBar->value();
    int blue = ui->blueBar->value();

    // 更改label顯示的色表值
    ui->redLabel->setText("red: " + QString::number(red));
    ui->greenLabel->setText("green: " + QString::number(green));
    ui->blueLabel->setText("blue: " + QString::number(blue));

    // 建立偽彩色表
    QVector<QColor> colorTable = gp.createPseudoColorTable(red, green, blue);

    // 繪製偽彩色影像
    std::unique_ptr<QImage> pseudoColorImage = gp.applyPseudoColor(image, colorTable);
    if (pseudoColorImage)
    {
        show_image_on_grphics_view(pseudoColorImage, ui->pseudoColorImage);
    }

    // 繪製色表
    std::unique_ptr<QImage> colorTableImage = gp.createColorTableImage(colorTable);
    if (colorTableImage)
    {
        show_image_on_grphics_view(colorTableImage, ui->colorTableImage);
    }
}

void MainWindow::on_blueBar_valueChanged(int value)
{
    // 如果 image 是 nullptr，則退出
    if (!image)
    {
        return; // 如果 image 是 nullptr，則退出
    }

    // 讀取bar設定的色表值
    int red = ui->redBar->value();
    int green = ui->greenBar->value();
    int blue = ui->blueBar->value();

    // 更改label顯示的色表值
    ui->redLabel->setText("red: " + QString::number(red));
    ui->greenLabel->setText("green: " + QString::number(green));
    ui->blueLabel->setText("blue: " + QString::number(blue));

    // 建立偽彩色表
    QVector<QColor> colorTable = gp.createPseudoColorTable(red, green, blue);

    // 繪製偽彩色影像
    std::unique_ptr<QImage> pseudoColorImage = gp.applyPseudoColor(image, colorTable);
    if (pseudoColorImage)
    {
        show_image_on_grphics_view(pseudoColorImage, ui->pseudoColorImage);
    }

    // 繪製色表
    std::unique_ptr<QImage> colorTableImage = gp.createColorTableImage(colorTable);
    if (colorTableImage)
    {
        show_image_on_grphics_view(colorTableImage, ui->colorTableImage);
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
    show_image_on_grphics_view(image, ui->originalimage_3);

    // 取得設定的K值
    int k = ui->KspinBox->value();

    // k-means segmentation
    std::unique_ptr<QImage> KMeansSegRGBImage = gp.kMeansSegmentation(image, k);
    if (KMeansSegRGBImage)
    {
        show_image_on_grphics_view(KMeansSegRGBImage, ui->KMeansSegRGBImage);
    }

    // rgb2hsi
    std::unique_ptr<QImage> hsiImage = gp.rgb2hsi(image);
    // k-means segmentation
    std::unique_ptr<QImage> KMeansSegHSIImage = gp.kMeansSegmentation(hsiImage, k);
    if (KMeansSegHSIImage)
    {
        show_image_on_grphics_view(KMeansSegHSIImage, ui->KMeansSegHSIImage);
    }

    // rgb2lab
    std::unique_ptr<QImage> labImage = gp.rgb2lab(image);
    // k-means segmentation
    std::unique_ptr<QImage> KMeansSegLabImage = gp.kMeansSegmentation(labImage, k);
    if (KMeansSegLabImage)
    {
        show_image_on_grphics_view(KMeansSegLabImage, ui->KMeansSegLabImage);
    }
}

void MainWindow::on_KspinBox_valueChanged(int arg1)
{
    // 如果 image 是 nullptr，則退出
    if (!image)
    {
        return; // 如果 image 是 nullptr，則退出
    }

    // 取得設定的K值
    int k = ui->KspinBox->value();

    // k-means segmentation
    std::unique_ptr<QImage> KMeansSegRGBImage = gp.kMeansSegmentation(image, k);
    if (KMeansSegRGBImage)
    {
        show_image_on_grphics_view(KMeansSegRGBImage, ui->KMeansSegRGBImage);
    }

    // rgb2hsi
    std::unique_ptr<QImage> hsiImage = gp.rgb2hsi(image);
    // k-means segmentation
    std::unique_ptr<QImage> KMeansSegHSIImage = gp.kMeansSegmentation(hsiImage, k);
    if (KMeansSegHSIImage)
    {
        show_image_on_grphics_view(KMeansSegHSIImage, ui->KMeansSegHSIImage);
    }

    // rgb2lab
    std::unique_ptr<QImage> labImage = gp.rgb2lab(image);
    // k-means segmentation
    std::unique_ptr<QImage> KMeansSegLabImage = gp.kMeansSegmentation(labImage, k);
    if (KMeansSegLabImage)
    {
        show_image_on_grphics_view(KMeansSegLabImage, ui->KMeansSegLabImage);
    }
}
