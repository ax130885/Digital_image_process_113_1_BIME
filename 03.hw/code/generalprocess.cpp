#include "generalprocess.h"
#include <QFileDialog>
#include <QImage>
#include <QMessageBox>
#include <QPainter>

GeneralProcess::GeneralProcess(QObject *parent)
    : QObject{parent}
{
}

std::unique_ptr<QImage> GeneralProcess::UploadFile()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    "Open Image File",
                                                    "",
                                                    "Images (*.jpg *.jpeg *.png *.bmp)");
    if (fileName.isEmpty())
    {
        return nullptr; // 用戶取消選擇
    }

    auto image = std::make_unique<QImage>(); // 使用智能指標管理 QImage
    if (!image->load(fileName))
    {
        QMessageBox::critical(nullptr, "Error", "Could not load the image file.");
        return nullptr; // 載入失敗時返回 nullptr
    }

    return image; // 返回成功載入的 QImage 智能指標
}

std::unique_ptr<QImage> GeneralProcess::calculateGrayHistogram(std::unique_ptr<QImage> &image)
{
    if (!image)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid image pointer.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    // 初始化直方圖為 0
    std::vector<int> histogram(256, 0);

    // 獲取圖片的寬度和高度
    int width = image->width();
    int height = image->height();

    // 遍歷每個像素，計算灰階直方圖
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // 獲取像素的灰階值
            int gray = qGray(image->pixel(x, y));
            // 更新直方圖
            ++histogram[gray];
        }
    }

    // 創建一個新圖像來顯示直方圖
    int histogramHeight = 200; // 設定直方圖高度
    std::unique_ptr<QImage> histogramImage = std::make_unique<QImage>(256, histogramHeight, QImage::Format_RGB32);
    histogramImage->fill(Qt::white); // 填充背景為白色

    // 繪製直方圖
    QPainter painter(histogramImage.get());
    painter.setPen(Qt::black);
    int maxCount = *std::max_element(histogram.begin(), histogram.end());

    for (int i = 0; i < 256; ++i)
    {
        int height = static_cast<int>(histogram[i] * histogramHeight / maxCount); // 正規化高度
        painter.drawLine(i, histogramHeight, i, histogramHeight - height);        // 繪製直方圖條
    }

    return histogramImage; // 返回直方圖圖像
}

std::unique_ptr<QImage> GeneralProcess::calculateRGBHistogram(std::unique_ptr<QImage> &image)
{
    if (!image)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid image pointer.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    // 初始化直方圖為 0
    std::vector<int> redHistogram(256, 0);
    std::vector<int> greenHistogram(256, 0);
    std::vector<int> blueHistogram(256, 0);

    // 獲取圖片的寬度和高度
    int width = image->width();
    int height = image->height();

    // 遍歷每個像素，計算 RGB 直方圖
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            QRgb pixel = image->pixel(x, y);
            ++redHistogram[qRed(pixel)];
            ++greenHistogram[qGreen(pixel)];
            ++blueHistogram[qBlue(pixel)];
        }
    }

    // 創建一個新圖像來顯示直方圖
    int histogramHeight = 200; // 設定直方圖高度
    std::unique_ptr<QImage> histogramImage = std::make_unique<QImage>(256, histogramHeight, QImage::Format_RGB32);
    histogramImage->fill(Qt::white); // 填充背景為白色

    // 繪製直方圖
    QPainter painter(histogramImage.get());
    int maxRedCount = *std::max_element(redHistogram.begin(), redHistogram.end());
    int maxGreenCount = *std::max_element(greenHistogram.begin(), greenHistogram.end());
    int maxBlueCount = *std::max_element(blueHistogram.begin(), blueHistogram.end());

    painter.setPen(Qt::red);
    for (int i = 0; i < 256; ++i)
    {
        int height = static_cast<int>(redHistogram[i] * histogramHeight / maxRedCount); // 正規化高度
        painter.drawLine(i, histogramHeight, i, histogramHeight - height);              // 繪製直方圖條
    }

    painter.setPen(Qt::green);
    for (int i = 0; i < 256; ++i)
    {
        int height = static_cast<int>(greenHistogram[i] * histogramHeight / maxGreenCount); // 正規化高度
        painter.drawLine(i, histogramHeight, i, histogramHeight - height);                  // 繪製直方圖條
    }

    painter.setPen(Qt::blue);
    for (int i = 0; i < 256; ++i)
    {
        int height = static_cast<int>(blueHistogram[i] * histogramHeight / maxBlueCount); // 正規化高度
        painter.drawLine(i, histogramHeight, i, histogramHeight - height);                // 繪製直方圖條
    }

    return histogramImage; // 返回直方圖圖像
}

// 二值化
std::unique_ptr<QImage> GeneralProcess::binaryzation(std::unique_ptr<QImage> &image, int *threshold_rgb)
{
    // 獲取圖片的寬度和高度
    int width = image->width();
    int height = image->height();

    // 創建一個新的 QImage 對象，並設置其大小和格式
    auto binaryImage = std::make_unique<QImage>(width, height, QImage::Format_Grayscale8);

    // 遍歷每個像素
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // 獲取像素的灰階值
            int gray = qGray(image->pixel(x, y));

            // 二值化處理
            int binary = (gray > *threshold_rgb) ? 255 : 0;

            // 將二值化結果設置為新像素的灰階值
            binaryImage->setPixel(x, y, qRgb(binary, binary, binary));
        }
    }

    return binaryImage; // 返回二值化圖像
}

// 雙線性插值法
std::unique_ptr<QImage> GeneralProcess::scaleImageBilinear(std::unique_ptr<QImage> &image, const int *newWidth, const int *newHeight)
{
    // 創建一個新的 QImage 來存儲縮放後的圖像
    std::unique_ptr<QImage> scaledImage = std::make_unique<QImage>(*newWidth, *newHeight, QImage::Format_RGB32);

    int oldWidth = image->width();
    int oldHeight = image->height();

    // 計算縮放比例 (原圖寬高除以新圖寬高)
    // 例如 3x3原圖縮放到4x4矩陣中 Scale = 3/4 = 0.75
    float xScale = static_cast<float>(oldWidth) / *newWidth;
    float yScale = static_cast<float>(oldHeight) / *newHeight;

    // 雙線性插值 Bilinear Interpolation
    for (int y = 0; y < *newHeight; ++y)
    {
        for (int x = 0; x < *newWidth; ++x)
        {
            // 在原圖中對應的座標 (浮點數) 例如4x4矩陣中的(2,3)座標 相當於3x3原圖中的(1.5,2.25)座標
            float oldX = x * xScale;
            float oldY = y * yScale;

            // 由oldXY 找到原圖中對應的四個相鄰像素
            // 計算左上角像素座標 (x1, y1)
            // 例如4x4矩陣中的(2,3)座標 對應到3x3原圖中的(1,2)座標
            int x1 = static_cast<int>(std::floor(oldX)); // static_cast<int> 將資料型態轉為int
            int y1 = static_cast<int>(std::floor(oldY)); // std::floor 取小於等於x的最大整數值
            // 計算右下角像素座標 (x2, y2)
            // 例如4x4矩陣中的(2,3)座標 對應到3x3原圖中的(2,3)座標
            int x2 = std::min(x1 + 1, oldWidth - 1);  // 在 x1+1 和 oldWidth-1 之間取最小值 確保不超出原圖範圍
            int y2 = std::min(y1 + 1, oldHeight - 1); // 因為圖片座標從0開始 所以要減1

            // 計算相對位置
            float xLerp = oldX - x1; // oldX - x1 = 1.5 - 1 = 0.5
            float yLerp = oldY - y1; // oldY - y1 = 2.25 - 2 = 0.25

            // 獲取這四個像素的顏色值 (假設是RGB格式)
            QRgb p11 = image->pixel(x1, y1); // 左上
            QRgb p12 = image->pixel(x1, y2); // 左下
            QRgb p21 = image->pixel(x2, y1); // 右上
            QRgb p22 = image->pixel(x2, y2); // 右下

            // 分別對 R、G、B 三個通道進行雙線性插值
            // 插值公式: f(x,y) = (1-x)(1-y)f(0,0) + x(1-y)f(1,0) + (1-x)yf(0,1) + xyf(1,1)
            // 例如: f(1.5,2.25) = (1-0.5)(1-0.25)f(1,2) + 0.5(1-0.25)f(2,2) + (1-0.5)0.25f(1,3) + 0.5*0.25f(2,3)
            //                  = (1-到x1的距離)(1-到y1的距離)f(x1,y1) + 到x1的距離(1-到y1的距離)f(x2,y1) + (1-到x1的距離)到y1的距離f(x1,y2) + 到x1的距離到y1的距離f(x2,y2)
            // 背法: f(x,y)與前面係數相加等於1; f(x,y)順序為左上, 左下, 右上, 右下; 四個角落固定不變; 邊界相當內插法
            int red = static_cast<int>((1 - xLerp) * ((1 - yLerp) * qRed(p11) + yLerp * qRed(p12)) +
                                       xLerp * ((1 - yLerp) * qRed(p21) + yLerp * qRed(p22)));

            int green = static_cast<int>((1 - xLerp) * ((1 - yLerp) * qGreen(p11) + yLerp * qGreen(p12)) +
                                         xLerp * ((1 - yLerp) * qGreen(p21) + yLerp * qGreen(p22)));

            int blue = static_cast<int>((1 - xLerp) * ((1 - yLerp) * qBlue(p11) + yLerp * qBlue(p12)) +
                                        xLerp * ((1 - yLerp) * qBlue(p21) + yLerp * qBlue(p22)));

            // 將插值後的 RGB 值寫入新的圖像中
            scaledImage->setPixel(x, y, qRgb(red, green, blue));
        }
    }

    return scaledImage;
}

// 最近鄰插值法
std::unique_ptr<QImage> GeneralProcess::scaleImageNearestNeighbor(std::unique_ptr<QImage> &image, const int *newWidth, const int *newHeight)
{
    // 創建一個新的 QImage 來存儲縮放後的圖像
    std::unique_ptr<QImage> scaledImage = std::make_unique<QImage>(*newWidth, *newHeight, QImage::Format_RGB32);

    int oldWidth = image->width();
    int oldHeight = image->height();

    // 計算縮放比例
    float xScale = static_cast<float>(oldWidth) / *newWidth;
    float yScale = static_cast<float>(oldHeight) / *newHeight;

    for (int y = 0; y < *newHeight; ++y)
    {
        for (int x = 0; x < *newWidth; ++x)
        {
            // 在原圖中對應的浮點座標
            float oldX = x * xScale;
            float oldY = y * yScale;

            // 使用 std::round 來進行最近鄰計算
            int nearestX = static_cast<int>(std::round(oldX));
            int nearestY = static_cast<int>(std::round(oldY));

            // 確保不越界
            nearestX = std::min(std::max(nearestX, 0), oldWidth - 1);
            nearestY = std::min(std::max(nearestY, 0), oldHeight - 1);

            // 獲取最近鄰像素的顏色
            QRgb pixel = image->pixel(nearestX, nearestY);

            // 將像素值設置到縮放後的圖像中
            scaledImage->setPixel(x, y, pixel);
        }
    }

    return scaledImage;
}

// 量化
std::unique_ptr<QImage> GeneralProcess::quantization(std::unique_ptr<QImage> &image, int *bits)
{
    // 獲取圖片的寬度和高度
    int width = image->width();
    int height = image->height();

    // 創建一個新的 QImage 對象，並設置其大小和格式
    auto quantizedImage = std::make_unique<QImage>(width, height, QImage::Format_RGB32);

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

            // 量化處理
            int redQuantized = (red >> (8 - *bits)) << (8 - *bits);     // 右移>> 相當於捨去低位數, 也就是量化本身
            int greenQuantized = (green >> (8 - *bits)) << (8 - *bits); // 左移<< 相當於補0, 還原回0~255的範圍
            int blueQuantized = (blue >> (8 - *bits)) << (8 - *bits);

            // 將量化結果設置為新像素的 RGB 值
            quantizedImage->setPixel(x, y, qRgb(redQuantized, greenQuantized, blueQuantized));
        }
    }

    return quantizedImage; // 返回量化圖像
}

// 調整亮度
std::unique_ptr<QImage> GeneralProcess::adjustBrightness(std::unique_ptr<QImage> &image, int *brightness)
{
    // 獲取圖片的寬度和高度
    int width = image->width();
    int height = image->height();

    // 創建一個新的 QImage 對象，並設置其大小和格式
    auto adjustedImage = std::make_unique<QImage>(width, height, QImage::Format_RGB32);

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

            // 調整亮度
            red = qBound(0, red + *brightness, 255);     // qBound 限制在0~255之間
            green = qBound(0, green + *brightness, 255); // 亮度調整
            blue = qBound(0, blue + *brightness, 255);

            // 將調整後的 RGB 值設置為新像素的 RGB 值
            adjustedImage->setPixel(x, y, qRgb(red, green, blue));
        }
    }

    return adjustedImage; // 返回調整亮度後的圖像
}

// 調整對比度
std::unique_ptr<QImage> GeneralProcess::adjustContrast(std::unique_ptr<QImage> &image, float *contrast)
{
    // 獲取圖片的寬度和高度
    int width = image->width();
    int height = image->height();

    // 創建一個新的 QImage 對象，並設置其大小和格式
    auto adjustedImage = std::make_unique<QImage>(width, height, QImage::Format_RGB32);

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

            // 調整對比度
            red = qBound(0.0, *contrast * (red - 128) + 128, 255.0);     // qBound 限制在0~255之間
            green = qBound(0.0, *contrast * (green - 128) + 128, 255.0); // 對比度調整 以128為中心 乘上對比度係數
            blue = qBound(0.0, *contrast * (blue - 128) + 128, 255.0);

            // 將調整後的 RGB 值設置為新像素的 RGB 值
            adjustedImage->setPixel(x, y, qRgb(red, green, blue));
        }
    }

    return adjustedImage; // 返回調整對比度後的圖像
}

// 灰階直方圖均衡化
std::unique_ptr<QImage> GeneralProcess::equalizeHistogramGrayImage(std::unique_ptr<QImage> &image)
{
    if (!image)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid image pointer.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    // 獲取圖片的寬度和高度
    int width = image->width();
    int height = image->height();

    // 初始化直方圖為 0
    std::vector<int> histogram(256, 0);

    // 計算灰階直方圖
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int gray = qGray(image->pixel(x, y));
            ++histogram[gray];
        }
    }

    // 計算累積直方圖(CDF)
    std::vector<int> cumulativeHistogram(256, 0);
    cumulativeHistogram[0] = histogram[0];
    for (int i = 1; i < 256; ++i)
    {
        cumulativeHistogram[i] = cumulativeHistogram[i - 1] + histogram[i];
    }

    // 計算均衡化後的灰階值
    int totalPixels = width * height;
    std::vector<int> equalizedGray(256, 0);
    for (int i = 0; i < 256; ++i)
    {
        equalizedGray[i] = static_cast<int>(255.0 * cumulativeHistogram[i] / totalPixels + 0.5);
    }

    // 創建一個新的 QImage 對象，並設置其大小和格式
    auto equalizedImage = std::make_unique<QImage>(width, height, QImage::Format_RGB32);

    // 應用均衡化後的灰階值到新圖像
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int gray = qGray(image->pixel(x, y));
            int newGray = equalizedGray[gray];
            equalizedImage->setPixel(x, y, qRgb(newGray, newGray, newGray));
        }
    }

    return equalizedImage; // 返回均衡化後的圖像
}

// RGB直方圖均衡化
std::unique_ptr<QImage> GeneralProcess::equalizeHistogramRGBImage(std::unique_ptr<QImage> &image)
{
    if (!image)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid image pointer.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    // 獲取圖片的寬度和高度
    int width = image->width();
    int height = image->height();

    // 初始化直方圖為 0
    std::vector<int> redHistogram(256, 0);
    std::vector<int> greenHistogram(256, 0);
    std::vector<int> blueHistogram(256, 0);

    // 計算 RGB 直方圖
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            QRgb pixel = image->pixel(x, y);
            ++redHistogram[qRed(pixel)];
            ++greenHistogram[qGreen(pixel)];
            ++blueHistogram[qBlue(pixel)];
        }
    }

    // 計算累積直方圖 (CDF)
    std::vector<int> redCumulativeHistogram(256, 0);
    std::vector<int> greenCumulativeHistogram(256, 0);
    std::vector<int> blueCumulativeHistogram(256, 0);

    redCumulativeHistogram[0] = redHistogram[0];
    greenCumulativeHistogram[0] = greenHistogram[0];
    blueCumulativeHistogram[0] = blueHistogram[0];

    for (int i = 1; i < 256; ++i)
    {
        redCumulativeHistogram[i] = redCumulativeHistogram[i - 1] + redHistogram[i];
        greenCumulativeHistogram[i] = greenCumulativeHistogram[i - 1] + greenHistogram[i];
        blueCumulativeHistogram[i] = blueCumulativeHistogram[i - 1] + blueHistogram[i];
    }

    // 計算均衡化後的 RGB 值 (把CDF乘上強度最大值255)
    int totalPixels = width * height;
    std::vector<int> equalizedRed(256, 0);
    std::vector<int> equalizedGreen(256, 0);
    std::vector<int> equalizedBlue(256, 0);

    // 四捨五入後新的強度值
    for (int i = 0; i < 256; ++i)
    {
        equalizedRed[i] = static_cast<int>(255.0 * redCumulativeHistogram[i] / totalPixels + 0.5);
        equalizedGreen[i] = static_cast<int>(255.0 * greenCumulativeHistogram[i] / totalPixels + 0.5);
        equalizedBlue[i] = static_cast<int>(255.0 * blueCumulativeHistogram[i] / totalPixels + 0.5);
    }

    // 創建一個新的 QImage 對象，並設置其大小和格式
    auto equalizedImage = std::make_unique<QImage>(width, height, QImage::Format_RGB32);

    // 應用均衡化後的 RGB 值到新圖像
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            QRgb pixel = image->pixel(x, y);
            int red = equalizedRed[qRed(pixel)];
            int green = equalizedGreen[qGreen(pixel)];
            int blue = equalizedBlue[qBlue(pixel)];
            equalizedImage->setPixel(x, y, qRgb(red, green, blue));
        }
    }

    return equalizedImage; // 返回均衡化後的圖像
}

// 空間濾波器(自訂kernel size做最大, 最小, 平均, 中位濾波)
std::unique_ptr<QImage> GeneralProcess::spatialFilter(std::unique_ptr<QImage> &image, int kernelSize, QString spatialFilterType)
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
    int paddedWidth = static_cast<int>(paddedImage->bytesPerLine() / sizeof(QRgb));

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
std::unique_ptr<QImage> GeneralProcess::paddingImage(std::unique_ptr<QImage> &image, int kernelSize, QString type)
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

// Sobel邊緣檢測
std::unique_ptr<QImage> GeneralProcess::sobelEdgeDetect(std::unique_ptr<QImage> &image)
{
    if (!image)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid image pointer.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    // 獲取圖片的寬度和高度
    int width = image->width();
    int height = image->height();

    // 創建一個新的 QImage 對象，並設置其大小和格式
    auto edgeImage = std::make_unique<QImage>(width, height, QImage::Format_Grayscale8);

    // Sobel 算子
    int gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}};
    int gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}};

    // 遍歷每個像素
    for (int y = 1; y < height - 1; ++y)
    {
        for (int x = 1; x < width - 1; ++x)
        {
            int sumX = 0;
            int sumY = 0;

            // 計算 Gx 和 Gy
            for (int i = -1; i <= 1; ++i)
            {
                for (int j = -1; j <= 1; ++j)
                {
                    int gray = qGray(image->pixel(x + j, y + i));
                    sumX += gx[i + 1][j + 1] * gray;
                    sumY += gy[i + 1][j + 1] * gray;
                }
            }

            // 計算梯度幅值
            int magnitude = static_cast<int>(std::sqrt(sumX * sumX + sumY * sumY));
            magnitude = qBound(0, magnitude, 255);

            // 設置邊緣圖像的像素值
            edgeImage->setPixel(x, y, qRgb(magnitude, magnitude, magnitude));
        }
    }

    return edgeImage; // 返回邊緣檢測後的圖像
}

// Marr-Hildreth邊緣檢測（使用LoG核）
std::unique_ptr<QImage> GeneralProcess::MarrHildrethEdgeDetection(const QImage &image, int kernelSize, double sigma, double threshold)
{

    // 1. 創建LoG核
    auto logKernel = createLoGKernel(sigma, kernelSize);

    // 2. 直接應用LoG濾波器，得到邊緣響應
    auto logResponse = applyLoGFilter(image, logKernel);

    // 3. 應用零交叉檢測
    auto edgeImage = applyZeroCrossing(logResponse, threshold);

    return edgeImage;
}

// 創建LoG（Laplacian of Gaussian）核
std::vector<std::vector<double>> GeneralProcess::createLoGKernel(double sigma, int kernelSize)
{
    std::vector<std::vector<double>> kernel(kernelSize, std::vector<double>(kernelSize));
    int halfSize = kernelSize / 2;
    double sigma2 = sigma * sigma;
    double sigma4 = sigma2 * sigma2;

    // 計算LoG核的係數
    double sum = 0.0;
    for (int y = -halfSize; y <= halfSize; ++y)
    {
        for (int x = -halfSize; x <= halfSize; ++x)
        {
            double r2 = x * x + y * y;
            // LoG方程：(r² - 2σ²)/(2πσ⁶) * exp(-r²/(2σ²))
            double value = (r2 - 2 * sigma2) * std::exp(-r2 / (2 * sigma2)) / (2 * M_PI * sigma4 * sigma2);
            kernel[y + halfSize][x + halfSize] = value;
            sum += value;
        }
    }

    // 確保核的和為0（這是LoG的重要特性）
    for (int y = 0; y < kernelSize; ++y)
    {
        for (int x = 0; x < kernelSize; ++x)
        {
            kernel[y][x] -= sum / (kernelSize * kernelSize);
        }
    }

    return kernel;
}

// 應用LoG濾波器
std::vector<std::vector<double>> GeneralProcess::applyLoGFilter(const QImage &image, const std::vector<std::vector<double>> &kernel)
{
    int width = image.width();
    int height = image.height();
    int kernelSize = kernel.size();
    int halfSize = kernelSize / 2;

    std::vector<std::vector<double>> response(height, std::vector<double>(width, 0.0));

    // 對每個像素應用LoG核
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            double sum = 0.0;

            for (int ky = -halfSize; ky <= halfSize; ++ky)
            {
                for (int kx = -halfSize; kx <= halfSize; ++kx)
                {
                    int px = std::clamp(x + kx, 0, width - 1);
                    int py = std::clamp(y + ky, 0, height - 1);

                    QColor color = image.pixelColor(px, py);
                    int gray = qGray(color.rgb()); // 轉換為灰度值

                    sum += gray * kernel[ky + halfSize][kx + halfSize];
                }
            }

            response[y][x] = sum;
        }
    }

    return response;
}

// 零交叉檢測
std::unique_ptr<QImage> GeneralProcess::applyZeroCrossing(const std::vector<std::vector<double>> &logResponse, double threshold)
{
    int height = logResponse.size();
    int width = logResponse[0].size();
    auto edgeImage = std::make_unique<QImage>(width, height, QImage::Format_RGB32);

    for (int y = 1; y < height - 1; ++y)
    {
        for (int x = 1; x < width - 1; ++x)
        {
            double current = logResponse[y][x];
            bool isEdge = false;

            // 檢查8個方向的零交叉
            for (int ky = -1; ky <= 1 && !isEdge; ++ky)
            {
                for (int kx = -1; kx <= 1; ++kx)
                {
                    if (kx == 0 && ky == 0)
                        continue;

                    double neighbor = logResponse[y + ky][x + kx];

                    // 檢查零交叉點
                    if ((current > 0 && neighbor < 0) || (current < 0 && neighbor > 0))
                    {
                        if (std::abs(current - neighbor) >= threshold)
                        {
                            isEdge = true;
                            break;
                        }
                    }
                }
            }

            edgeImage->setPixelColor(x, y, isEdge ? QColor(255, 255, 255) : QColor(0, 0, 0));
        }
    }

    return edgeImage;
}

// 局部統計的影像增強 Local Statistical Image Enhancement (增強影像的低強度且低對比區域)
std::unique_ptr<QImage> GeneralProcess::localMeanContrastEnhancement(std::unique_ptr<QImage> &image, int kernelSize, double k0, double k1, double k2, double k3, double C)
{
    // 檢查圖像指標是否為空
    if (!image)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid image pointer.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    // 獲取圖像的寬度和高度
    int width = image->width();
    int height = image->height();

    // 創建一個新的 QImage 來存儲增強後的圖像
    auto enhancedImage = std::make_unique<QImage>(width, height, QImage::Format_RGB32);

    // 初始化 global intensity 的 mean 和 standard deviation
    double globalMean = 0.0;
    double globalStdDev = 0.0;
    int totalPixels = width * height;

    // 計算全局強度的平均值
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            double gray = qGray(image->pixel(x, y));
            globalMean += gray; // 總和
        }
    }
    globalMean = globalMean / totalPixels; // 平均值

    // 計算全局強度的標準差 (要先算完平均值才能算標準差 不能一起做 否則會造成每次算的平均值不一樣)
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            double gray = qGray(image->pixel(x, y));
            globalStdDev += (gray - globalMean) * (gray - globalMean); // 方差和
        }
    }
    globalStdDev = std::sqrt(globalStdDev / totalPixels); // 標準差

    // 遍歷每個像素
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // 計算局部區域的均值和標準差
            double localMean = 0.0;
            double localStdDev = 0.0;
            int count = 0;

            for (int ky = -kernelSize / 2; ky <= kernelSize / 2; ++ky)
            {
                for (int kx = -kernelSize / 2; kx <= kernelSize / 2; ++kx)
                {
                    int nx = std::clamp(x + kx, 0, width - 1);
                    int ny = std::clamp(y + ky, 0, height - 1);
                    double gray = qGray(image->pixel(nx, ny));
                    localMean += gray; // 總和
                    ++count;
                }
            }
            localMean = localMean / count; // 平均值

            for (int ky = -kernelSize / 2; ky <= kernelSize / 2; ++ky)
            {
                for (int kx = -kernelSize / 2; kx <= kernelSize / 2; ++kx)
                {
                    int nx = std::clamp(x + kx, 0, width - 1);
                    int ny = std::clamp(y + ky, 0, height - 1);
                    double gray = qGray(image->pixel(nx, ny));
                    localStdDev += (gray - localMean) * (gray - localMean); // 方差和
                }
            }
            localStdDev = std::sqrt(localStdDev / count); // 標準差

            // 獲取當前像素的灰階值
            QRgb currentPixel = image->pixel(x, y);
            double currentGray = qGray(currentPixel);

            // 如果影像是低強度區且低對比區才要增強
            double enhancedGray = currentGray;
            if ((k0 * globalMean <= localMean && localMean <= k1 * globalMean) &&
                (k2 * globalStdDev <= localStdDev && localStdDev <= k3 * globalStdDev))
            {
                enhancedGray = C * currentGray;
            }

            // 確保增強後的灰階值在有效範圍內
            enhancedGray = std::clamp(enhancedGray, 0.0, 255.0);

            // 將增強後的灰階值設置為新像素的 RGB 值
            int finalGray = qBound(0, static_cast<int>(enhancedGray), 255);
            enhancedImage->setPixel(x, y, qRgb(finalGray, finalGray, finalGray));
        }
    }

    return enhancedImage; // 返回增強後的圖像
}