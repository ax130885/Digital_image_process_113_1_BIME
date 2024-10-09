#include "specificprocess.h"
#include <QImage>
#include <QMessageBox>

SpecificProcess::SpecificProcess(QObject *parent)
    : QObject{parent}
{
}

std::unique_ptr<QImage> SpecificProcess::grayscale_by_avg_rgb(std::unique_ptr<QImage> &image)
{
    // 獲取圖片的寬度和高度
    int width = image->width();
    int height = image->height();

    // 創建一個新的 QImage 對象，並設置其大小和格式
    auto grayImage = std::make_unique<QImage>(width, height, QImage::Format_Grayscale8);

    // 遍歷每個像素
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // 獲取像素的 RGB 值
            QRgb pixel = image->pixel(x, y);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            // 計算灰階值 (平均)
            int gray = static_cast<int>((red + green + blue) / 3);
            // // 計算灰階值 (加權)
            // int gray = static_cast<int>(0.299 * red + 0.587 * green + 0.114 * blue);

            // 將灰階值設置為新像素的 RGB 值
            grayImage->setPixel(x, y, qRgb(gray, gray, gray));
        }
    }

    return grayImage; // 返回灰階圖像
}

std::unique_ptr<QImage> SpecificProcess::grayscale_by_eyes_weight_rgb(std::unique_ptr<QImage> &image)
{
    // 獲取圖片的寬度和高度
    int width = image->width();
    int height = image->height();

    // 創建一個新的 QImage 對象，並設置其大小和格式
    auto grayImage = std::make_unique<QImage>(width, height, QImage::Format_Grayscale8);

    // 遍歷每個像素
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // 獲取像素的 RGB 值
            QRgb pixel = image->pixel(x, y);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            // // 計算灰階值 (平均)
            // int gray = static_cast<int>((red + green + blue) / 3);
            // 計算灰階值 (加權)
            int gray = static_cast<int>(0.299 * red + 0.587 * green + 0.114 * blue);
            // // 計算灰階值 (紅色, 測試用)
            // int gray = static_cast<int>(1.0 * red + 0.0 * green + 0.0 * blue);

            // 將灰階值設置為新像素的 RGB 值
            grayImage->setPixel(x, y, qRgb(gray, gray, gray));
        }
    }

    return grayImage; // 返回灰階圖像
}

std::unique_ptr<QImage> SpecificProcess::calculateGrayDifference(std::unique_ptr<QImage> &image1, std::unique_ptr<QImage> &image2)
{
    if (!image1 || !image2)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid image pointers.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    // 確保兩個圖像的大小相同
    if (image1->size() != image2->size())
    {
        QMessageBox::critical(nullptr, "Error", "Image sizes do not match.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    // 獲取圖片的寬度和高度
    int width = image1->width();
    int height = image1->height();

    // 創建一個新的 QImage 對象，並設置其大小和格式
    auto diffImage = std::make_unique<QImage>(width, height, QImage::Format_Grayscale8);

    // 遍歷每個像素，計算兩個圖像的差異
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // 獲取兩個圖像的像素值
            int gray1 = qGray(image1->pixel(x, y));
            int gray2 = qGray(image2->pixel(x, y));

            // 計算差異
            int diff = qAbs(gray1 - gray2);

            // 將差異值設置為新像素的灰階值
            diffImage->setPixel(x, y, qRgb(diff, diff, diff));
        }
    }

    return diffImage; // 返回差異圖像
}
