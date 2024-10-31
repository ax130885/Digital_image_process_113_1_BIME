#ifndef SPECIFICPROCESS_H
#define SPECIFICPROCESS_H

#include <QObject>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

class SpecificProcess : public QObject
{
    Q_OBJECT
public:
    explicit SpecificProcess(QObject *parent = nullptr);
    // std::unique_ptr<QImage> grayscale_by_avg_rgb(std::unique_ptr<QImage> &image);
    // std::unique_ptr<QImage> grayscale_by_eyes_weight_rgb(std::unique_ptr<QImage> &image);
    // std::unique_ptr<QImage> calculateGrayDifference(std::unique_ptr<QImage> &image1, std::unique_ptr<QImage> &image2);
    std::unique_ptr<QImage> spatialFilter(std::unique_ptr<QImage> &image, int kernelSize = 3, QString spatialFilterType = "median 中位");
    std::unique_ptr<QImage> paddingImage(std::unique_ptr<QImage> &image, int kernelSize = 3, QString type = "zero");

    // HW4
    cv::Mat idealLowPassFilter(const cv::Mat &shift_dft, double D0);
    cv::Mat gaussianLowPassFilter(const cv::Mat &shift_dft, double D0);
    cv::Mat butterworthLowPassFilter(const cv::Mat &shift_dft, double D0, int n);
    cv::Mat idealHighPassFilter(const cv::Mat &shift_dft, double D0);
    cv::Mat gaussianHighPassFilter(const cv::Mat &shift_dft, double D0);
    cv::Mat butterworthHighPassFilter(const cv::Mat &shift_dft, double D0, int n);
    std::unique_ptr<QImage> homomorphicFilter(std::unique_ptr<QImage> &image, double gamma_H, double gamma_L, double D0, double c);
    // 直線動態模糊
    cv::Mat motionBlurred(const cv::Mat &shift_dft, double a, double b, double T);
    // 加入高斯雜訊
    std::unique_ptr<QImage> GaussianNoise(std::unique_ptr<QImage> &image, double sigma);
    // 單位脈衝響應
    cv::Mat unitImpulseResponse(const cv::Mat &shift_dft, double T);
    // 運動模糊衰退逆濾波器
    cv::Mat inverseFilter(const cv::Mat &shift_dft_noise, double a, double b, double T, double k);
    // 運動模糊衰退wiener濾波器
    cv::Mat wienerFilter(const cv::Mat &shift_dft_noise, double a, double b, double T, double k);
    // 計算空間域圖像差異
    std::unique_ptr<QImage> diffImage(const QImage &image1, const QImage &image2);

signals:

private:
};

#endif // SPECIFICPROCESS_H
