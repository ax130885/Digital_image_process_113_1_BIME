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

std::unique_ptr<QImage> GeneralProcess::calculateHistogram(std::unique_ptr<QImage> &image)
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
