#ifndef SPECIFICPROCESS_H
#define SPECIFICPROCESS_H

#include <QObject>

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
signals:
};

#endif // SPECIFICPROCESS_H
