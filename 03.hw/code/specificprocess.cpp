#include "specificprocess.h"
#include <QImage>
#include <QMessageBox>

SpecificProcess::SpecificProcess(QObject *parent)
    : QObject{parent}
{
}

// 空間濾波器
std::unique_ptr<QImage> SpecificProcess::spatialFilter(std::unique_ptr<QImage> &image, int kernelSize, QString spatialFilterType)
{
    // 檢查圖像指標是否為空
    if (!image)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid image pointer.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    // 檢查 kernelSize 是否為奇數，必須是奇數才能進行濾波操作
    if (kernelSize % 2 == 0)
    {
        QMessageBox::critical(nullptr, "Error", "Kernel size must be an odd number.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    // 獲取原圖像的寬度和高度
    int origin_width = image->width();
    int origin_height = image->height();

    // 創建一個與原圖像大小相同的 QImage 來存放濾波後的結果
    auto spatialFilterImage = std::make_unique<QImage>(origin_width, origin_height, QImage::Format_RGB32);

    // 對原圖像進行 padding 操作，以便處理邊界
    auto paddedImage = paddingImage(image, kernelSize);

    // 獲取填充後的圖像寬度和高度
    int paddedWidth = paddedImage->bytesPerLine() / sizeof(QRgb);

    // 取得圖像的像素數據
    const QRgb *paddedData = reinterpret_cast<const QRgb *>(paddedImage->constBits());

    // 初始化存放 kernel 區域像素值的陣列
    std::vector<int> redValues(kernelSize * kernelSize);
    std::vector<int> greenValues(kernelSize * kernelSize);
    std::vector<int> blueValues(kernelSize * kernelSize);

// 使用 OpenMP 平行化來加速像素遍歷
#pragma omp parallel for collapse(2) schedule(dynamic)
    for (int y = 0; y < origin_height; ++y)
    {
        for (int x = 0; x < origin_width; ++x)
        {
            int index = 0; // 初始化索引，用來存取 kernel 中的每個像素值

            // 將 kernel 區域內的每個像素值存入相應的陣列
            for (int j = 0; j < kernelSize; ++j)
            {
                for (int i = 0; i < kernelSize; ++i)
                {
                    QRgb pixel = paddedData[(y + j) * paddedWidth + (x + i)];
                    redValues[index] = qRed(pixel);
                    greenValues[index] = qGreen(pixel);
                    blueValues[index] = qBlue(pixel);
                    ++index;
                }
            }

            // 初始化新的像素值
            int redValue = 0, greenValue = 0, blueValue = 0;

            // 根據不同的濾波器類型計算新的像素值
            if (spatialFilterType == "mean 平均")
            {
                int redSum = 0, greenSum = 0, blueSum = 0;
#pragma omp simd reduction(+ : redSum, greenSum, blueSum)
                for (int i = 0; i < kernelSize * kernelSize; ++i)
                {
                    redSum += redValues[i];
                    greenSum += greenValues[i];
                    blueSum += blueValues[i];
                }
                redValue = redSum / (kernelSize * kernelSize);
                greenValue = greenSum / (kernelSize * kernelSize);
                blueValue = blueSum / (kernelSize * kernelSize);
            }
            else if (spatialFilterType == "median 中位")
            {
                // 使用 std::nth_element 用途是找到第 n 大的元素 (每個參數的意思為: 起始位置, 第 n 大的元素位置, 結束位置)
                std::nth_element(redValues.begin(), redValues.begin() + redValues.size() / 2, redValues.end());
                std::nth_element(greenValues.begin(), greenValues.begin() + greenValues.size() / 2, greenValues.end());
                std::nth_element(blueValues.begin(), blueValues.begin() + blueValues.size() / 2, blueValues.end());
                redValue = redValues[redValues.size() / 2];
                greenValue = greenValues[greenValues.size() / 2];
                blueValue = blueValues[blueValues.size() / 2];
            }
            else if (spatialFilterType == "max 最大")
            {
                redValue = *std::max_element(redValues.begin(), redValues.end());
                greenValue = *std::max_element(greenValues.begin(), greenValues.end());
                blueValue = *std::max_element(blueValues.begin(), blueValues.end());
            }
            else if (spatialFilterType == "min 最小")
            {
                redValue = *std::min_element(redValues.begin(), redValues.end());
                greenValue = *std::min_element(greenValues.begin(), greenValues.end());
                blueValue = *std::min_element(blueValues.begin(), blueValues.end());
            }
            else // 無效的濾波器類型
            {
                QMessageBox::critical(nullptr, "Error", "Invalid spatial filter type.");
                return paddedImage; // 返回填充後的影像以表示錯誤
            }

            // 設置濾波後的像素值到結果圖像中
            QRgb newPixel = qRgb(redValue, greenValue, blueValue);
            spatialFilterImage->setPixel(x, y, newPixel);
        }
    }

    // 返回濾波後的圖像
    return spatialFilterImage;
}

// 填充圖像(padding)
std::unique_ptr<QImage> SpecificProcess::paddingImage(std::unique_ptr<QImage> &image, int kernelSize, QString type)
{
    if (!image)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid image pointer.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    // 計算 padding 大小，kernelSize 必須為奇數，所以 (kernelSize - 1) / 2 可以得到正確的邊界填充數量
    int padding = (kernelSize - 1) / 2;

    // 獲取原圖像的寬度和高度
    int width = image->width();
    int height = image->height();

    // 創建一個新的 QImage 來存放填充後的結果，寬度和高度分別加上 2 倍的 padding
    auto paddedImage = std::make_unique<QImage>(width + 2 * padding, height + 2 * padding, QImage::Format_RGB32);

    // 判斷填充類型，這裡可以擴展為多種不同的填充策略
    if (type == "zero")
    {
        // 將邊界部分填充為全黑，即 RGB 值為 (0, 0, 0)
        paddedImage->fill(qRgb(0, 0, 0));

        // 填充圖像的中心部分
        for (int y = 0; y < height; ++y)
        {
            // 計算 padding 後的 y 座標，避免多次計算
            int paddedY = y + padding;

            for (int x = 0; x < width; ++x)
            {
                // 計算 padding 後的 x 座標，避免多次計算
                int paddedX = x + padding;

                // 設置新圖像中對應位置的像素值
                paddedImage->setPixel(paddedX, paddedY, image->pixel(x, y));
            }
        }
    }
    else if (type == "replicate")
    {
        // 填充邊界為複製邊緣像素值
        for (int y = 0; y < height + 2 * padding; ++y)
        {
            for (int x = 0; x < width + 2 * padding; ++x)
            {
                int clampedX = std::clamp(x - padding, 0, width - 1);  // 將 x 座標限制在圖像邊界內
                int clampedY = std::clamp(y - padding, 0, height - 1); // 將 y 座標限制在圖像邊界內

                // 使用原圖像邊緣的像素值進行填充
                paddedImage->setPixel(x, y, image->pixel(clampedX, clampedY));
            }
        }
    }
    else
    {
        QMessageBox::critical(nullptr, "Error", "Invalid padding type.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    return paddedImage; // 返回填充後的圖像
}
