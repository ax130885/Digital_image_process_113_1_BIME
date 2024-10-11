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

    // 如果有上傳圖片 才執行所有功能
    show_image_on_grphics_view(image, ui->originalimage);

    // 空間濾波
    // 取得spinbox設置的kernel size
    int spatialFilter_kernelSize = ui->spatialFilter_kernelSize_spinbox->value();
    // 取得comboBox設置的濾波種類
    QString spatialFilterType = ui->spatialFilter_comboBox->currentText();
    // 計算空間濾波圖像
    std::unique_ptr<QImage> spatialFilterImage = sp.spatialFilter(image, spatialFilter_kernelSize, spatialFilterType);
    show_image_on_grphics_view(spatialFilterImage, ui->spatialFilterImage);

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

void MainWindow::on_spatialFilter_kernelSize_spinbox_valueChanged()
{
    if (image)
    {
        // 空間濾波
        // 取得spinbox設置的kernel size
        int spatialFilter_kernelSize = ui->spatialFilter_kernelSize_spinbox->value();
        // 取得comboBox設置的濾波種類
        QString spatialFilterType = ui->spatialFilter_comboBox->currentText();
        // 計算空間濾波圖像
        std::unique_ptr<QImage> spatialFilterImage = sp.spatialFilter(image, spatialFilter_kernelSize, spatialFilterType);
        show_image_on_grphics_view(spatialFilterImage, ui->spatialFilterImage);
    }
}

void MainWindow::on_spatialFilter_comboBox_currentTextChanged()
{
    if (image)
    {
        // 空間濾波
        // 取得spinbox設置的kernel size
        int spatialFilter_kernelSize = ui->spatialFilter_kernelSize_spinbox->value();
        // 取得comboBox設置的濾波種類
        QString spatialFilterType = ui->spatialFilter_comboBox->currentText();
        // 計算空間濾波圖像
        std::unique_ptr<QImage> spatialFilterImage = sp.spatialFilter(image, spatialFilter_kernelSize, spatialFilterType);
        show_image_on_grphics_view(spatialFilterImage, ui->spatialFilterImage);
    }
}
