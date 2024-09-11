// ImageProceesor.cpp
#include "ImageProcessor.h"
#include <QPainter>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <QImage>  // 用於處理影像顯示
#include <QPixmap> // 用於處理影像顯示
#include <QBuffer> // 用於儲存影像
#include <QLabel>  // 用於顯示影像

ImageProcessor::ImageProcessor(QWidget *parent) : QWidget(parent)
{
    // imageArray 在.h檔案中有定義為 QVector<QVector<int>> ; QVector<QVector<int>> 代表一個二維矩陣
    // 創造一個64x64的矩陣 並且所有元素初始化為0
    imageArray.resize(64); // 將行數設為 64
    for (int i = 0; i < imageArray.size(); i++)
    {
        imageArray[i].resize(64);                                 // 將每行都有64列
        std::fill(imageArray[i].begin(), imageArray[i].end(), 0); // 初始化整行所有元素為 0
    }

    // histogram 在.h檔案中有定義為 QVector<int> ; QVector<int> 代表一個一維矩陣
    // 創建一個大小為64的向量 並且所有元素初始化為0
    histogram.resize(32);                             // 將大小設為 32
    std::fill(histogram.begin(), histogram.end(), 0); // 初始化向量所有元素為 0

    setFixedSize(1200, 800); // 設定窗口大小
}

// 讀取 .64 文件 並且將其存儲到 imageArray 中
bool ImageProcessor::loadImage(const QString &fileName)
{
    QFile file(fileName);
    if (!file.exists())
    {
        qDebug() << "File does not exist:" << fileName;
        return false;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file. Error:" << file.errorString();
        return false;
    }

    // 清空之前的數據
    for (auto &row : imageArray) // imageArray 是一個二維矩陣 auto 代表自動推斷類型 一次取出一行 然後儲存地址到 &row 中
    {
        std::fill(row.begin(), row.end(), 0);
    }

    QTextStream in(&file); // 創建一個 QTextStream 物件 in 並且輸入(&file)來讀取文件
    for (int row = 0; row < 64; row++)
    {
        int col = 0;
        while (col < 64)
        {
            QString character = in.read(1); // 讀取一個字符
            if (character.isEmpty())
            {
                qDebug() << "Unexpected end of file.";
                return false;
            }

            // 忽略換行符和空格
            if (character == "\n" || character == " " || character == "\r")
            {
                continue;
            }

            bool ok;
            int value = character.toInt(&ok, 32); // 32進制轉換為數字

            if (!ok)
            {
                qDebug() << "Failed to convert character:" << character;
                return false;
            }

            imageArray[row][col] = value;
            col++; // 僅在有效字符時增加 col
        }
    }

    // 生成直方圖
    generateHistogram();

    // 顯示灰階影像
    displayGrayImage();

    return true;
}

void ImageProcessor::generateHistogram()
{
    // 確認直方圖是淨空的
    std::fill(histogram.begin(), histogram.end(), 0);
    int count = 0;
    // 計算每個灰度級別的出現次數
    for (const auto &row : imageArray)
    {
        for (const int value : row)
        {
            histogram[value]++;
            count++;
        }
    }

    // printf("total count = %d\n", count);
    // int sum = 0;
    // for (int i = 0; i < 32; i++)
    // {
    //     qDebug() << "value: " << i << ", count: " << histogram[i];
    //     sum += histogram[i];
    // }
    // printf("sum = %d\n", sum);
}

void ImageProcessor::paintEvent(QPaintEvent *event) // 繪製事件 使用update()函數時自動觸發
{
    QPainter painter(this);

    // 繪製直方圖
    drawHistogram(painter);
}

void ImageProcessor::drawHistogram(QPainter &painter)
{
    int barWidth = 22;     // 條形寬度
    int xOffset = 50;      // x 軸起始位置
    int yOffset = 550;     // y 軸起始位置
    int maxHeight = 500;   // 最大高度
    int labelInterval = 1; // 標籤間隔，交錯顯示

    // 計算最大數值
    int maxCount = *std::max_element(histogram.begin(), histogram.end());

    // 繪製 x 軸
    painter.drawLine(xOffset, yOffset, xOffset + 32 * barWidth, yOffset);

    // 繪製 y 軸
    painter.drawLine(xOffset, yOffset, xOffset, yOffset - maxHeight);

    // 繪製直方圖條形
    for (int i = 0; i < 32; i++) // 只顯示到 32
    {
        int barHeight = static_cast<int>((static_cast<double>(histogram[i]) / maxCount) * maxHeight);
        int x = xOffset + i * barWidth;
        int y = yOffset - barHeight;

        painter.drawRect(x, y, barWidth - 1, barHeight);

        // 繪製條形的數值
        painter.drawText(x + (barWidth - 1) / 2, y - 15, QString::number(histogram[i]));

        // 繪製 x 軸刻度
        if (i % labelInterval == 0)
        {
            // 繪製 x 軸標籤
            painter.drawText(x + (barWidth - 1) / 2 - 5, yOffset + 25, QString::number(i));
            // 繪製 x 軸外刻度
            painter.drawLine(x + (barWidth - 1) / 2, yOffset, x + (barWidth - 1) / 2, yOffset + 5);
        }
    }

    // 繪製 y 軸刻度 共有numTicks個刻度
    int numTicks = 10;
    int tickInterval = maxHeight / numTicks;

    for (int i = 0; i < numTicks; i++)
    {
        int y = yOffset - i * tickInterval;
        painter.drawLine(xOffset - 5, y, xOffset, y); // 繪製刻度線
        painter.drawText(xOffset - 30, y + 5, QString::number(static_cast<int>(i * maxCount / numTicks)));
    }
}

// 顯示灰階影像
void ImageProcessor::displayGrayImage()
{
    // 創建QImage以儲存灰階影像
    QImage image(64, 64, QImage::Format_Grayscale8);

    for (int row = 0; row < 64; row++)
    {
        for (int col = 0; col < 64; col++)
        {
            int value = imageArray[row][col] * 4;                // 從 imageArray 取得值
            image.setPixel(col, row, qRgb(value, value, value)); // 設置為灰階顏色
        }
    }

    // 將影像儲存到檔案
    // image.save("gray_image.png");

    // 更新窗口以顯示影像
    QPixmap pixmap = QPixmap::fromImage(image);
    QLabel *imageLabel = new QLabel(this);
    imageLabel->setPixmap(pixmap.scaled(256, 256)); // 顯示 256x256 大小的影像
    imageLabel->setGeometry(850, 250, 256, 256);    // 設置影像位置(左上角x,y)和大小(w,h) 須符合圖片大小
    imageLabel->show();
}

void ImageProcessor::clearHistogram()
{
    // 清空直方圖數據
    std::fill(histogram.begin(), histogram.end(), 0);
    update(); // 強制重繪
}
