#ifndef GENERALPROCESS_H
#define GENERALPROCESS_H

#include <QObject>
#include <QImage>

#include <tuple>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
// <opencv2/ximgproc.hpp>
class GeneralProcess : public QObject
{
    Q_OBJECT
public:
    explicit GeneralProcess(QObject *parent = nullptr);
    std::unique_ptr<QImage> UploadFile();
    // HW1
    std::unique_ptr<QImage> calculateGrayHistogram(std::unique_ptr<QImage> &image);
    std::unique_ptr<QImage> calculateRGBHistogram(std::unique_ptr<QImage> &image);
    std::unique_ptr<QImage> binaryzation(std::unique_ptr<QImage> &image, int *threshold_rgb);
    // HW2
    std::unique_ptr<QImage> scaleImageBilinear(std::unique_ptr<QImage> &image, const int *newWidth, const int *newHeight);
    std::unique_ptr<QImage> scaleImageNearestNeighbor(std::unique_ptr<QImage> &image, const int *newWidth, const int *newHeight);
    std::unique_ptr<QImage> quantization(std::unique_ptr<QImage> &image, int *bits);
    std::unique_ptr<QImage> adjustBrightness(std::unique_ptr<QImage> &image, int *brightness);
    std::unique_ptr<QImage> adjustContrast(std::unique_ptr<QImage> &image, float *contrast);
    std::unique_ptr<QImage> equalizeHistogramGrayImage(std::unique_ptr<QImage> &image);
    std::unique_ptr<QImage> equalizeHistogramRGBImage(std::unique_ptr<QImage> &image);
    // HW3
    std::unique_ptr<QImage> spatialFilter(std::unique_ptr<QImage> &image, int kernelSize = 3, QString spatialFilterType = "median 中位");
    std::unique_ptr<QImage> paddingImage(std::unique_ptr<QImage> &image, int kernelSize = 3, QString type = "zero");
    std::unique_ptr<QImage> sobelEdgeDetect(std::unique_ptr<QImage> &image);
    std::unique_ptr<QImage> MarrHildrethEdgeDetection(const QImage &image, int kernelSize, double sigma, double threshold);
    std::unique_ptr<QImage> localMeanContrastEnhancement(std::unique_ptr<QImage> &image, int kernelSize, double k0 = 0.0, double k1 = 0.25, double k2 = 0.0, double k3 = 0.1, double C = 228);
    // HW4
    std::tuple<cv::Mat, std::unique_ptr<QImage>, std::unique_ptr<QImage>> fft(const QImage &image, const QString show = "no_show");
    std::unique_ptr<QImage> ifft(cv::Mat shift_dft);
    // HW5
    // rgb2cmy
    std::unique_ptr<QImage> rgb2cmy(std::unique_ptr<QImage> &image);
    // rgb2hsi
    std::unique_ptr<QImage> rgb2hsi(std::unique_ptr<QImage> &image);
    // rgb2xzy
    std::unique_ptr<QImage> rgb2xyz(std::unique_ptr<QImage> &image);
    // rgb2lab
    std::unique_ptr<QImage> rgb2lab(std::unique_ptr<QImage> &image);
    // rgb2yuv
    std::unique_ptr<QImage> rgb2yuv(std::unique_ptr<QImage> &image);
    // 建立偽彩色表，根據傳入的 RGB 值生成一個色表。
    QVector<QColor> createPseudoColorTable(int red, int green, int blue);
    // 將偽彩色表轉換為 QImage，以便顯示或視覺化。
    std::unique_ptr<QImage> createColorTableImage(const QVector<QColor> &colorTable);
    // 將偽彩色表應用到灰階影像，生成偽彩色影像。
    std::unique_ptr<QImage> applyPseudoColor(const std::unique_ptr<QImage> &image, const QVector<QColor> &colorTable);
    // K-means segmentation
    std::unique_ptr<QImage> kMeansSegmentation(std::unique_ptr<QImage> &image, int k);

    // HW6
    // trapezoidal geometric transformation (梯形幾何轉換)
    std::unique_ptr<QImage> trapezoidalGeometricTransformation(std::unique_ptr<QImage> &image, double topBase, double bottomBase, double h); // topBase: 上底, bottomBase: 下底, h: 高
    // wavy geometric transformation (波浪幾何轉換)
    std::unique_ptr<QImage> wavyGeometricTransformation(std::unique_ptr<QImage> &image, double amplitude, double frequency, double phase);
    // circular geometric transformation (圓形幾何轉換)
    std::unique_ptr<QImage> circularGeometricTransformation(std::unique_ptr<QImage> &image, double radius);

    // 小波轉換
    void dwt(const cv::Mat &src, cv::Mat &low, cv::Mat &highH, cv::Mat &highV, cv::Mat &highD, int level);
    // 逆小波轉換
    void idwt(const cv::Mat &low, const cv::Mat &highH, const cv::Mat &highV, const cv::Mat &highD, cv::Mat &dst, int level);
    // 使用小波轉換進行影像融合
    std::unique_ptr<QImage> imageFusion(std::unique_ptr<QImage> &image1, std::unique_ptr<QImage> &image2, int level, QString waveletType = "Haar");

    // 計算歐幾里得距離
    double euclideanDistance(const cv::Vec3b &p1, const cv::Vec3b &p2);
    // Simple Linear Iterative Clustering (SLIC) 實作超像素區域分割
    std::unique_ptr<QImage> SLIC(std::unique_ptr<QImage> &image, int K, int m = 10, int maxIter = 10); // K: 超像素區域數量, m: 超像素區域大小, maxIter: 最大迭代次數

signals:

private:
    // HW3 for MarrHildrethEdgeDetection
    std::vector<std::vector<double>> createLoGKernel(double sigma, int kernelSize);
    std::vector<std::vector<double>> applyLoGFilter(const QImage &image, const std::vector<std::vector<double>> &kernel);
    std::unique_ptr<QImage> applyZeroCrossing(const std::vector<std::vector<double>> &logResponse, double threshold);
};

#endif // GENERALPROCESS_H