#ifndef GENERALPROCESS_H
#define GENERALPROCESS_H

#include <QObject>
#include <QImage>

class GeneralProcess : public QObject
{
    Q_OBJECT
public:
    explicit GeneralProcess(QObject *parent = nullptr);
    std::unique_ptr<QImage> UploadFile();
    std::unique_ptr<QImage> calculateGrayHistogram(std::unique_ptr<QImage> &image);
    std::unique_ptr<QImage> calculateRGBHistogram(std::unique_ptr<QImage> &image);
    std::unique_ptr<QImage> binaryzation(std::unique_ptr<QImage> &image, int *threshold_rgb);
    std::unique_ptr<QImage> scaleImageBilinear(std::unique_ptr<QImage> &image, const int *newWidth, const int *newHeight);
    std::unique_ptr<QImage> scaleImageNearestNeighbor(std::unique_ptr<QImage> &image, const int *newWidth, const int *newHeight);
    std::unique_ptr<QImage> quantization(std::unique_ptr<QImage> &image, int *bits);
    std::unique_ptr<QImage> adjustBrightness(std::unique_ptr<QImage> &image, int *brightness);
    std::unique_ptr<QImage> adjustContrast(std::unique_ptr<QImage> &image, float *contrast);
    std::unique_ptr<QImage> equalizeHistogramGrayImage(std::unique_ptr<QImage> &image);
    std::unique_ptr<QImage> equalizeHistogramRGBImage(std::unique_ptr<QImage> &image);

signals:

private:
};

#endif // GENERALPROCESS_H
