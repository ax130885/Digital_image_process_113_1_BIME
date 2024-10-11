#include "specificprocess.h"
#include <QImage>
#include <QMessageBox>

SpecificProcess::SpecificProcess(QObject *parent)
    : QObject{parent}
{
}

// std::unique_ptr<QImage> SpecificProcess::grayscale_by_avg_rgb(std::unique_ptr<QImage> &image)
// {
//     // 獲取圖片的寬度和高度
//     int width = image->width();
//     int height = image->height();

//     // 創建一個新的 QImage 對象，並設置其大小和格式
//     auto grayImage = std::make_unique<QImage>(width, height, QImage::Format_Grayscale8);

//     // 遍歷每個像素
//     for (int y = 0; y < height; ++y)
//     {
//         for (int x = 0; x < width; ++x)
//         {
//             // 獲取像素的 RGB 值
//             QRgb pixel = image->pixel(x, y);
//             int red = qRed(pixel);
//             int green = qGreen(pixel);
//             int blue = qBlue(pixel);

//             // 計算灰階值 (平均)
//             int gray = static_cast<int>((red + green + blue) / 3);
//             // // 計算灰階值 (加權)
//             // int gray = static_cast<int>(0.299 * red + 0.587 * green + 0.114 * blue);

//             // 將灰階值設置為新像素的 RGB 值
//             grayImage->setPixel(x, y, qRgb(gray, gray, gray));
//         }
//     }

//     return grayImage; // 返回灰階圖像
// }

// std::unique_ptr<QImage> SpecificProcess::grayscale_by_eyes_weight_rgb(std::unique_ptr<QImage> &image)
// {
//     // 獲取圖片的寬度和高度
//     int width = image->width();
//     int height = image->height();

//     // 創建一個新的 QImage 對象，並設置其大小和格式
//     auto grayImage = std::make_unique<QImage>(width, height, QImage::Format_Grayscale8);

//     // 遍歷每個像素
//     for (int y = 0; y < height; ++y)
//     {
//         for (int x = 0; x < width; ++x)
//         {
//             // 獲取像素的 RGB 值
//             QRgb pixel = image->pixel(x, y);
//             int red = qRed(pixel);
//             int green = qGreen(pixel);
//             int blue = qBlue(pixel);

//             // // 計算灰階值 (平均)
//             // int gray = static_cast<int>((red + green + blue) / 3);
//             // 計算灰階值 (加權)
//             int gray = static_cast<int>(0.299 * red + 0.587 * green + 0.114 * blue);
//             // // 計算灰階值 (紅色, 測試用)
//             // int gray = static_cast<int>(1.0 * red + 0.0 * green + 0.0 * blue);

//             // 將灰階值設置為新像素的 RGB 值
//             grayImage->setPixel(x, y, qRgb(gray, gray, gray));
//         }
//     }

//     return grayImage; // 返回灰階圖像
// }

// std::unique_ptr<QImage> SpecificProcess::calculateGrayDifference(std::unique_ptr<QImage> &image1, std::unique_ptr<QImage> &image2)
// {
//     if (!image1 || !image2)
//     {
//         QMessageBox::critical(nullptr, "Error", "Invalid image pointers.");
//         return nullptr; // 返回 nullptr 表示錯誤
//     }

//     // 確保兩個圖像的大小相同
//     if (image1->size() != image2->size())
//     {
//         QMessageBox::critical(nullptr, "Error", "Image sizes do not match.");
//         return nullptr; // 返回 nullptr 表示錯誤
//     }

//     // 獲取圖片的寬度和高度
//     int width = image1->width();
//     int height = image1->height();

//     // 創建一個新的 QImage 對象，並設置其大小和格式
//     auto diffImage = std::make_unique<QImage>(width, height, QImage::Format_Grayscale8);

//     // 遍歷每個像素，計算兩個圖像的差異
//     for (int y = 0; y < height; ++y)
//     {
//         for (int x = 0; x < width; ++x)
//         {
//             // 獲取兩個圖像的像素值
//             int gray1 = qGray(image1->pixel(x, y));
//             int gray2 = qGray(image2->pixel(x, y));

//             // 計算差異
//             int diff = qAbs(gray1 - gray2);

//             // 將差異值設置為新像素的灰階值
//             diffImage->setPixel(x, y, qRgb(diff, diff, diff));
//         }
//     }

//     return diffImage; // 返回差異圖像
// }

std::unique_ptr<QImage> SpecificProcess::spatialFilter(std::unique_ptr<QImage> &image, int kernelSize, QString spatialFilterType)
{
    if (!image)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid image pointer.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    // 確保 kernelSize 為奇數
    if (kernelSize % 2 == 0)
    {
        QMessageBox::critical(nullptr, "Error", "Kernel size must be an odd number.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    // 獲取原圖的寬度和高度
    int origin_width = image->width();
    int origin_height = image->height();

    // 創建一個與原圖像大小相同的 QImage 對象，用於存儲濾波後的圖像
    auto spatialFilterImage = std::make_unique<QImage>(origin_width, origin_height, QImage::Format_RGB32);

    // 填充圖像(padding)
    auto paddedImage = paddingImage(image, kernelSize);

    // 獲取填充後的寬度和高度
    int width = paddedImage->width();
    int height = paddedImage->height();

    // 遍歷每個像素，進行空間濾波，濾波方式有：平均、中值、最大、最小
    for (int y = 0; y < height - kernelSize + 1; ++y) // height - kernelSize + 1 = origin_height
    {
        for (int x = 0; x < width - kernelSize + 1; ++x)
        {
            // 創建一個列表，把區域內的像素值存為一個列表
            std::vector<int> redValues;
            std::vector<int> greenValues;
            std::vector<int> blueValues;

            for (int j = 0; j < kernelSize; ++j)
            {
                for (int i = 0; i < kernelSize; ++i)
                {
                    QRgb pixel = paddedImage->pixel(x + i, y + j);
                    redValues.push_back(qRed(pixel));
                    greenValues.push_back(qGreen(pixel));
                    blueValues.push_back(qBlue(pixel));
                }
            }

            // 對區域內的像素值進行排序
            std::sort(redValues.begin(), redValues.end());
            std::sort(greenValues.begin(), greenValues.end());
            std::sort(blueValues.begin(), blueValues.end());

            // 計算濾波後的像素值
            int redValue = 0;
            int greenValue = 0;
            int blueValue = 0;

            if (spatialFilterType == "average 平均")
            {
                // 平均濾波
                for (int i = 0; i < kernelSize * kernelSize; ++i)
                {
                    redValue += redValues[i];
                    greenValue += greenValues[i];
                    blueValue += blueValues[i];
                }
                redValue /= kernelSize * kernelSize;
                greenValue /= kernelSize * kernelSize;
                blueValue /= kernelSize * kernelSize;
            }
            else if (spatialFilterType == "median 中位")
            {
                // 中值濾波
                redValue = redValues[kernelSize * kernelSize / 2];
                greenValue = greenValues[kernelSize * kernelSize / 2];
                blueValue = blueValues[kernelSize * kernelSize / 2];
            }
            else if (spatialFilterType == "max 最大")
            {
                // 最大值濾波
                redValue = redValues[kernelSize * kernelSize - 1];
                greenValue = greenValues[kernelSize * kernelSize - 1];
                blueValue = blueValues[kernelSize * kernelSize - 1];
            }
            else if (spatialFilterType == "min 最小")
            {
                // 最小值濾波
                redValue = redValues[0];
                greenValue = greenValues[0];
                blueValue = blueValues[0];
            }
            else // 回傳空影像
            {
                QMessageBox::critical(nullptr, "Error", "Invalid spatial filter type.");
                return std::move(image);
            }

            // 設置濾波後的像素值
            QRgb newPixel = qRgb(redValue, greenValue, blueValue);
            spatialFilterImage->setPixel(x, y, newPixel);
        }
    }
    return spatialFilterImage; // 返回濾波後的圖像
}

// 填充圖像(padding)
std::unique_ptr<QImage> SpecificProcess::paddingImage(std::unique_ptr<QImage> &image, int kernelSize, QString type)
{
    if (!image)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid image pointer.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    // 計算padding量
    int padding = (kernelSize - 1) / 2;

    // 獲取圖片的寬度和高度
    int width = image->width();
    int height = image->height();

    // 創建一個新的 QImage 對象，並設置其大小和格式
    auto paddedImage = std::make_unique<QImage>(width + 2 * padding, height + 2 * padding, QImage::Format_RGB32);

    if (type == "zero")
    {
        // 先填充邊界為0
        paddedImage->fill(qRgb(0, 0, 0));

        // 填充圖像的中心部分
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                paddedImage->setPixel(x + padding, y + padding, image->pixel(x, y));
            }
        }
    }
    else // 回傳空影像
    {
        QMessageBox::critical(nullptr, "Error", "Invalid padding type.");
        return nullptr;
    }

    return paddedImage; // 返回填充後的圖像
}
