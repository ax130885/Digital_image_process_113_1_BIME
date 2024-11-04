#ifndef GENERALPROCESS_H
#define GENERALPROCESS_H

#include <QObject>
#include <QImage>

#include <tuple>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

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

signals:

private:
    // HW3 for MarrHildrethEdgeDetection
    std::vector<std::vector<double>> createLoGKernel(double sigma, int kernelSize);
    std::vector<std::vector<double>> applyLoGFilter(const QImage &image, const std::vector<std::vector<double>> &kernel);
    std::unique_ptr<QImage> applyZeroCrossing(const std::vector<std::vector<double>> &logResponse, double threshold);
};

#endif // GENERALPROCESS_H
