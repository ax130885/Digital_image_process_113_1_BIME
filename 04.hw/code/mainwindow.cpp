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

void MainWindow::on_ApplyFFT_clicked()
{
    if (image)
    {
        auto [shift_dft, fftImage_magnitude, fftImage_phase] = gp.fft(*image, "show");
        if (fftImage_magnitude && fftImage_phase)
        {
            show_image_on_grphics_view(fftImage_magnitude, ui->fftImage_magnitude);
            show_image_on_grphics_view(fftImage_phase, ui->fftImage_phase);
        }

        // IFFT
        std::unique_ptr<QImage> ifftImage = gp.ifft(shift_dft);
        if (ifftImage)
        {

            show_image_on_grphics_view(ifftImage, ui->ifftImage);
        }
        std::unique_ptr<QImage> diff = sp.diffImage(*image, *ifftImage);
        if (diff)
        {
            show_image_on_grphics_view(diff, ui->diff);
        }
    }
}

void MainWindow::on_ApplyHLPF_clicked()
{
    if (image)
    {
        // 取得spinbox設置的D0
        double D0 = ui->prob2_D0_spinbox->value();
        // 取得spinbox設置的n
        int n = ui->prob2_n_spinbox->value();

        // 對原圖作傅立葉變換
        auto [shift_dft, _1, _2] = gp.fft(*image);

        // 計算理想低通濾波器圖像
        cv::Mat idealLowPass = sp.idealLowPassFilter(shift_dft, D0);
        if (!idealLowPass.empty())
        {
            std::unique_ptr<QImage> idealLowPassImage = gp.ifft(idealLowPass);
            show_image_on_grphics_view(idealLowPassImage, ui->idealLowPassImage);
        }

        // 計算高斯低通濾波器圖像
        cv::Mat gaussianLowPass = sp.gaussianLowPassFilter(shift_dft, D0);
        if (!gaussianLowPass.empty())
        {
            std::unique_ptr<QImage> gaussianLowPassImage = gp.ifft(gaussianLowPass);
            show_image_on_grphics_view(gaussianLowPassImage, ui->gaussianLowPassImage);
        }

        // 計算巴特沃斯低通濾波器圖像
        cv::Mat butterworthLowPass = sp.butterworthLowPassFilter(shift_dft, D0, n);
        if (!butterworthLowPass.empty())
        {
            std::unique_ptr<QImage> butterworthLowPassImage = gp.ifft(butterworthLowPass);
            show_image_on_grphics_view(butterworthLowPassImage, ui->butterworthLowPassImage);
        }

        // 計算理想高通濾波器圖像
        cv::Mat idealHighPass = sp.idealHighPassFilter(shift_dft, D0);
        if (!idealHighPass.empty())
        {
            std::unique_ptr<QImage> idealHighPassImage = gp.ifft(idealHighPass);
            show_image_on_grphics_view(idealHighPassImage, ui->idealHighPassImage);
        }

        // 計算高斯高通濾波器圖像
        cv::Mat gaussianHighPass = sp.gaussianHighPassFilter(shift_dft, D0);
        if (!gaussianHighPass.empty())
        {
            std::unique_ptr<QImage> gaussianHighPassImage = gp.ifft(gaussianHighPass);
            show_image_on_grphics_view(gaussianHighPassImage, ui->gaussianHighPassImage);
        }

        // 計算巴特沃斯高通濾波器圖像
        cv::Mat butterworthHighPass = sp.butterworthHighPassFilter(shift_dft, D0, n);
        if (!butterworthHighPass.empty())
        {
            std::unique_ptr<QImage> butterworthHighPassImage = gp.ifft(butterworthHighPass);
            show_image_on_grphics_view(butterworthHighPassImage, ui->butterworthHighPassImage);
        }
    }
}

void MainWindow::on_ApplyHomomorphic_clicked()
{
    if (image)
    {
        // 取得spinbox設置的gamma_H
        double gamma_H = ui->prob3_gamma_H_spinbox->value();
        // 取得spinbox設置的gamma_L
        double gamma_L = ui->prob3_gamma_L_spinbox->value();
        // 取得spinbox設置的D0
        double D0 = ui->prob3_D0_spinbox->value();
        // 取得spinbox設置的c
        double c = ui->prob3_c_spinbox->value();

        // 計算同態濾波(homomorphic)圖像
        std::unique_ptr<QImage> homomorphicImage = sp.homomorphicFilter(image, gamma_H, gamma_L, D0, c);
        if (homomorphicImage)
        {
            show_image_on_grphics_view(homomorphicImage, ui->homomorphicImage);
        }
    }
}

void MainWindow::on_ApplyMotionBlurred_clicked()
{
    if (image)
    {

        // 取得spinbox設置的T (曝光時間)
        double T = ui->prob4_T_spinbox->value();
        // 取得spinbox設置的a (X方向運動的距離)
        double a = ui->prob4_a_spinbox->value();
        // 取得spinbox設置的b (Y方向運動的距離)
        double b = ui->prob4_b_spinbox->value();
        // 取得spinbox設置的inverse_k
        double inverse_k = ui->prob4_inverse_k_spinbox->value();
        // 取得spinbox設置的wiener_k
        double wiener_k = ui->prob4_wiener_k_spinbox->value();

        // 對原圖作傅立葉變換
        auto [shift_dft, _1, _2] = gp.fft(*image);

        // 計算運動模糊圖像
        cv::Mat motionBlurred = sp.motionBlurred(shift_dft, a, b, T);
        std::unique_ptr<QImage> motionBlurredImage;

        if (!motionBlurred.empty())
        {
            motionBlurredImage = gp.ifft(motionBlurred);
            show_image_on_grphics_view(motionBlurredImage, ui->motionBlurredImage);
        }

        // 計算運動模糊+白高斯噪音sigma=20圖像
        double sigma = 20;
        std::unique_ptr<QImage> GaussianNoiseImage = sp.GaussianNoise(motionBlurredImage, sigma);
        if (GaussianNoiseImage)
        {
            show_image_on_grphics_view(GaussianNoiseImage, ui->GaussianNoiseImage);
        }

        // 計算inverse filter圖像 (F=G/H)
        cv::Mat inverseFilterOrigin = sp.inverseFilter(shift_dft, a, b, T, inverse_k);
        std::unique_ptr<QImage> inverseFilterOriginImage;
        if (!inverseFilterOrigin.empty())
        {
            inverseFilterOriginImage = gp.ifft(inverseFilterOrigin);
            show_image_on_grphics_view(inverseFilterOriginImage, ui->inverseFilterImage1);
        }

        auto [shift_dft_noise, _3, _4] = gp.fft(*GaussianNoiseImage);
        cv::Mat inverseFilter = sp.inverseFilter(shift_dft_noise, a, b, T, inverse_k);
        std::unique_ptr<QImage> inverseFilterImage;
        if (!inverseFilter.empty())
        {
            inverseFilterImage = gp.ifft(inverseFilter);
            show_image_on_grphics_view(inverseFilterImage, ui->inverseFilterImage2);
        }

        // 計算wiener濾波器圖像
        cv::Mat wienerFilter = sp.wienerFilter(shift_dft_noise, a, b, T, wiener_k);
        std::unique_ptr<QImage> wienerFilterImage;
        if (!wienerFilter.empty())
        {
            wienerFilterImage = gp.ifft(wienerFilter);
            show_image_on_grphics_view(wienerFilterImage, ui->wienerFilterImage);
        }

        // 原圖 - inverse filter圖像
        std::unique_ptr<QImage> diffImage_inv = sp.diffImage(*image, *inverseFilterImage);
        if (diffImage_inv)
        {
            show_image_on_grphics_view(diffImage_inv, ui->diffImage_inv);
        }

        // 原圖 - wiener濾波器圖像
        std::unique_ptr<QImage> diffImage_wiener = sp.diffImage(*image, *wienerFilterImage);
        if (diffImage_wiener)
        {
            show_image_on_grphics_view(diffImage_wiener, ui->diffImage_wiener);
        }
    }
}
