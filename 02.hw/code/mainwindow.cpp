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
    delete gp;
    delete sp;
}

void MainWindow::on_uploadfile_clicked()
{
    GeneralProcess gp(this);
    SpecificProcess sp(this);

    // 上傳檔案
    std::unique_ptr<QImage> image = gp.UploadFile(); // 使用 unique_ptr 接收返回值
    show_origin_image(image);                        // 使用 .get() 來獲取指向的 QImage*

    // 計算灰階
    std::unique_ptr<QImage> grayImage_rgb = sp.grayscale_by_avg_rgb(image);
    std::unique_ptr<QImage> grayImage_weight = sp.grayscale_by_eyes_weight_rgb(image);
    show_gray_image(grayImage_rgb, grayImage_weight);
    show_gray_histogram(grayImage_rgb, grayImage_weight);

    // 計算差異
    std::unique_ptr<QImage> diffGray = sp.calculateGrayDifference(grayImage_rgb, grayImage_weight);
    show_diffGray(diffGray);

    // 二值化

    // 縮放

    // 量化

    // 調整亮度

    // 調整對比

    // 直方圖均衡
}

void MainWindow::show_origin_image(std::unique_ptr<QImage> &image)
{
    // 將 QImage 轉換為 QPixmap
    QPixmap pixmap = QPixmap::fromImage(*image);

    // 創建 QGraphicsScene 並將其設定到 QGraphicsView
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(pixmap);

    // 假設 originalimage 是在 ui 中設計的 QGraphicsView 的名稱
    ui->originalimage->setScene(scene);
    ui->originalimage->fitInView(scene->sceneRect(), Qt::KeepAspectRatio); // 調整視圖以適應圖片
}

void MainWindow::show_gray_image(std::unique_ptr<QImage> &image1, std::unique_ptr<QImage> &image2)
{
    // 將 QImage 轉換為 QPixmap
    QPixmap pixmap1 = QPixmap::fromImage(*image1);
    QPixmap pixmap2 = QPixmap::fromImage(*image2);

    // 創建 QGraphicsScene 並將其設定到 QGraphicsView
    QGraphicsScene *scene1 = new QGraphicsScene(this);
    scene1->addPixmap(pixmap1);

    QGraphicsScene *scene2 = new QGraphicsScene(this);
    scene2->addPixmap(pixmap2);

    // 假設 grayimage 是在 ui 中設計的 QGraphicsView 的名稱
    ui->grayimage_rgb->setScene(scene1);
    ui->grayimage_rgb->fitInView(scene1->sceneRect(), Qt::KeepAspectRatio); // 調整視圖以適應圖片

    ui->grayimage_weight->setScene(scene2);
    ui->grayimage_weight->fitInView(scene2->sceneRect(), Qt::KeepAspectRatio); // 調整視圖以適應圖片
}

void MainWindow::show_gray_histogram(std::unique_ptr<QImage> &image1, std::unique_ptr<QImage> &image2)
{
    // 計算灰階直方圖
    std::unique_ptr<QImage> histImage1 = gp->calculateHistogram(image1);
    std::unique_ptr<QImage> histImage2 = gp->calculateHistogram(image2);

    // 將 QImage 轉換為 QPixmap
    QPixmap pixmap1 = QPixmap::fromImage(*histImage1); // 使用解引用來獲取 QImage
    QPixmap pixmap2 = QPixmap::fromImage(*histImage2); // 使用解引用來獲取 QImage

    // 創建 QGraphicsScene 並將其設定到 QGraphicsView
    QGraphicsScene *scene1 = new QGraphicsScene(this);
    scene1->addPixmap(pixmap1);

    QGraphicsScene *scene2 = new QGraphicsScene(this);
    scene2->addPixmap(pixmap2);

    // 假設 grayhistogram 是在 ui 中設計的 QGraphicsView 的名稱
    ui->grayhistogram_rgb->setScene(scene1);
    ui->grayhistogram_rgb->fitInView(scene1->sceneRect(), Qt::KeepAspectRatio); // 調整視圖以適應圖片

    ui->grayhistogram_weight->setScene(scene2);
    ui->grayhistogram_weight->fitInView(scene2->sceneRect(), Qt::KeepAspectRatio); // 調整視圖以適應圖片
}

void MainWindow::show_diffGray(std::unique_ptr<QImage> &image)
{
    // 將 QImage 轉換為 QPixmap
    QPixmap pixmap = QPixmap::fromImage(*image);

    // 創建 QGraphicsScene 並將其設定到 QGraphicsView
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(pixmap);

    // 假設 grayscalediff 是在 ui 中設計的 QGraphicsView 的名稱
    ui->grayscalediff->setScene(scene);
    ui->grayscalediff->fitInView(scene->sceneRect(), Qt::KeepAspectRatio); // 調整視圖以適應圖片
}
