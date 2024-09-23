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

    // 遍歷每個像素，計算灰度直方圖
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // 獲取像素的灰度值
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
            // 獲取像素的灰度值
            int gray = qGray(image->pixel(x, y));

            // 二值化處理
            int binary = (gray > *threshold_rgb) ? 255 : 0;

            // 將二值化結果設置為新像素的灰度值
            binaryImage->setPixel(x, y, qRgb(binary, binary, binary));
        }
    }

    return binaryImage; // 返回二值化圖像
}

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

// 最近鄰插值法實現
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

    // 計算灰度直方圖
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int gray = qGray(image->pixel(x, y));
            ++histogram[gray];
        }
    }

    // 計算累積直方圖
    std::vector<int> cumulativeHistogram(256, 0);
    cumulativeHistogram[0] = histogram[0];
    for (int i = 1; i < 256; ++i)
    {
        cumulativeHistogram[i] = cumulativeHistogram[i - 1] + histogram[i];
    }

    // 計算均衡化後的灰度值
    int totalPixels = width * height;
    std::vector<int> equalizedGray(256, 0);
    for (int i = 0; i < 256; ++i)
    {
        equalizedGray[i] = static_cast<int>(255.0 * cumulativeHistogram[i] / totalPixels + 0.5);
    }

    // 創建一個新的 QImage 對象，並設置其大小和格式
    auto equalizedImage = std::make_unique<QImage>(width, height, QImage::Format_RGB32);

    // 應用均衡化後的灰度值到新圖像
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

    // 計算累積直方圖
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

    // 計算均衡化後的 RGB 值
    int totalPixels = width * height;
    std::vector<int> equalizedRed(256, 0);
    std::vector<int> equalizedGreen(256, 0);
    std::vector<int> equalizedBlue(256, 0);

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
