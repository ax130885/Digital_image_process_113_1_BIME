#include "secondprocess.h"
#include <Qdir>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <cmath> // 包含 std::round 函數

SecondProcess::SecondProcess(QWidget *parent)
    : QWidget{parent}
{
    // 初始化 imageArrayAns
    imageArrayAns.resize(64);
    for (int i = 0; i < imageArrayAns.size(); i++)
    {
        imageArrayAns[i].resize(64);
        std::fill(imageArrayAns[i].begin(), imageArrayAns[i].end(), 0);
    }
}

int SecondProcess::p_loadImage(QString image1FileName, QString image2FileName)
{
    int imageNum = 0;

    // 初始化 imageArray1 和 imageArray2
    imageArray1.clear();
    imageArray2.clear();

    // this是一個指向當前對象的指針 所以用-> 而不是.
    this->image1Path = QDir::currentPath() + "/" + image1FileName;
    this->image2Path = QDir::currentPath() + "/" + image2FileName;

    // image何imagePath都在.h檔案中有定義過為成員變數(屬性) 因此可以不用this-> 直接使用 但使用this->可以增加可讀性
    // 載入影像1
    image1.setFileName(image1Path);
    if (!image1.exists())
    {
        QMessageBox::critical(this, "Load Image1 ERROR", "File does not exist:\n" + image1Path);
        return -1;
    }
    else if (!image1.open(QIODevice::ReadOnly)) // 一定要open才有載入影像
    {
        qDebug() << "Failed to open file:" << image1.errorString();
    }
    else
    {
        imageArray1 = QFileTo2dQVector64(image1);
        if (imageArray1.isEmpty())
        {
            QMessageBox::critical(this, "Load Image1 ERROR!", "\nFailed to load image1");
            return -1;
        };
        imageNum++;
        // qDebug() << "image1 to 2d QVector successfully";
    };

    // 載入影像2
    image2.setFileName(image2Path);
    if (image2FileName == "None")
    {
        qDebug() << "image2 is None";
        imageArray2.resize(64);
        for (int i = 0; i < imageArray2.size(); i++)
        {
            imageArray2[i].resize(64);                                  // 將每行都有64列
            std::fill(imageArray2[i].begin(), imageArray2[i].end(), 0); // 初始化整行所有元素為 0
        }
        imageNum++;
    }
    else if (!image2.exists())
    {
        QMessageBox::critical(this, "Load Image2 ERROR", "File does not exist:\n" + image2Path);
        return -1;
    }
    else if (!image2.open(QIODevice::ReadOnly)) // 一定要open才有載入影像
    {
        qDebug() << "Failed to open file:" << image2.errorString();
    }
    else
    {
        imageArray2 = QFileTo2dQVector64(image2);
        if (imageArray2.isEmpty())
        {
            QMessageBox::critical(this, "Load Image2 ERROR!", "\nFailed to load image2");
            return -1;
        };
        imageNum++;
        // qDebug() << "image2 to 2d QVector successfully";
    };

    // 初始化 imageArrayAns
    imageArrayAns.resize(64);
    for (int i = 0; i < imageArrayAns.size(); i++)
    {
        imageArrayAns[i].resize(64);
        std::fill(imageArrayAns[i].begin(), imageArrayAns[i].end(), 0);
    }

    if (imageNum == 0)
        QMessageBox::information(this, "Load Image", "No image selected");

    else if (imageNum == 1)
        QMessageBox::information(this, "Load Image", "\nLoad image1:" + image1Path + "\nsuccessfully");

    else
        QMessageBox::information(this, "Load Image success!", "\nLoad image1:" + image1Path + "\nimage2:" + image2Path + "\nsuccessfully");

    // 繪製灰階圖 千萬不能放到paintEvent裡面 不然會一直重繪 然後crash
    displayGrayImage();

    return imageNum;
}

void SecondProcess::p_calculateImage(int addend, double multiplier)
{
    // 計算影像的加法和乘法
    // 最後記得檢查數值會不會超過 255 或是小於 0
    for (int i = 0; i < imageArray1.size(); i++)
    {
        for (int j = 0; j < imageArray1[i].size(); j++)
        {
            // 先乘後加
            imageArrayAns[i][j] = static_cast<int>(std::round(imageArray1[i][j] * multiplier));
            imageArrayAns[i][j] = imageArrayAns[i][j] + addend;

            // 將結果限制在 [0, 255] 範圍內
            if (imageArrayAns[i][j] < 0)
                imageArrayAns[i][j] = 0;
            if (imageArrayAns[i][j] > 255)
                imageArrayAns[i][j] = 255;
        }
    }
    displayGrayImage();
    update(); // 強制重繪
}

void SecondProcess::p_averageImage()
{
    // 檢查一定要載入兩個影像
    if (image2Path == "None")
    {
        QMessageBox::critical(this, "Error", "Please load image2 first");
        return;
    }

    // 計算兩個影像的平均值
    // 這裡只是一個示例，實際上需要根據您的需求來實現
    for (int i = 0; i < imageArray1.size(); i++)
    {
        for (int j = 0; j < imageArray1[i].size(); j++)
        {
            imageArrayAns[i][j] = (imageArray1[i][j] + imageArray2[i][j]) / 2;
        }
    }

    displayGrayImage();
    update(); // 強制重繪
}

void SecondProcess::p_gxImage()
{
    // 檢查一定要載入兩個影像
    if (image2Path == "None")
    {
        QMessageBox::critical(this, "Error", "Please load image2 first");
        return;
    }

    // 計算兩個影像的 g(x,y)=f1(x,y)-f2(x-1,y)
    for (int i = 0; i < imageArray1.size(); i++)
    {
        for (int j = 0; j < imageArray1[i].size(); j++)
        {
            if (i > 0) // 避免 i - 1 為負數
            {
                imageArrayAns[i][j] = imageArray1[i][j] - imageArray2[i - 1][j];
            }
            else
            {
                imageArrayAns[i][j] = imageArray1[i][j]; // i == 0 時，僅使用 imageArray1
            }

            // 將結果限制在 [0, 255] 範圍內
            if (imageArrayAns[i][j] < 0)
                imageArrayAns[i][j] = 0;
            if (imageArrayAns[i][j] > 255)
                imageArrayAns[i][j] = 255;
        }
    }

    displayGrayImage();
    update(); // 強制重繪
}

QVector<QVector<int>> SecondProcess::QFileTo2dQVector64(QFile &file)
{
    QVector<QVector<int>> imageArray;
    imageArray.resize(64); // 將行數設為 64
    for (int i = 0; i < imageArray.size(); i++)
    {
        imageArray[i].resize(64);                                 // 將每行都有64列
        std::fill(imageArray[i].begin(), imageArray[i].end(), 0); // 初始化整行所有元素為 0
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
                return QVector<QVector<int>>();
            }

            imageArray[row][col] = value;
            col++; // 僅在有效字符時增加 col
        }
    }

    return imageArray;
}

void SecondProcess::displayGrayImage()
{
    QImage displayImage(64, 64, QImage::Format_Grayscale8);

    // 創建QImage以儲存灰階影像
    if (imageArray1.isEmpty())
    {
        qDebug() << "No image1 to display";
    }
    else if (imageArray1.size() != 64 || imageArray1[0].size() != 64)
    {
        QMessageBox::critical(this, "Display Gray Image", "Invalid image size");
    }
    else
    {
        for (int row = 0; row < 64; row++)
        {
            for (int col = 0; col < 64; col++)
            {
                int value = imageArray1[row][col];                          // 從 imageArray 取得值
                displayImage.setPixel(col, row, qRgb(value, value, value)); // 設置為灰階顏色
            }
        }

        // 更新窗口以顯示影像
        QPixmap pixmap = QPixmap::fromImage(displayImage);
        // 創建 QLabel 用於顯示影像
        QLabel *imageLabel1(new QLabel(this));
        imageLabel1->setPixmap(pixmap.scaled(200, 200)); // 顯示 200x200 大小的影像
        imageLabel1->setGeometry(50, 25, 200, 200);      // 設置影像位置(左上角x,y)和大小(w,h) 須符合圖片大小
        imageLabel1->show();
    }

    if (imageArray2.isEmpty())
    {
        qDebug() << "No image2 to display";
    }
    else if (imageArray2.size() != 64 || imageArray2[0].size() != 64)
    {
        QMessageBox::critical(this, "Display Gray Image", "Invalid image size");
    }
    else
    {
        for (int row = 0; row < 64; row++)
        {
            for (int col = 0; col < 64; col++)
            {
                int value = imageArray2[row][col];                          // 從 imageArray 取得值
                displayImage.setPixel(col, row, qRgb(value, value, value)); // 設置為灰階顏色
            }
        }

        // 更新窗口以顯示影像
        QPixmap pixmap = QPixmap::fromImage(displayImage);
        // 創建 QLabel 用於顯示影像
        QLabel *imageLabel2(new QLabel(this));
        imageLabel2->setPixmap(pixmap.scaled(200, 200)); // 顯示 200x200 大小的影像
        imageLabel2->setGeometry(50, 250, 200, 200);     // 設置影像位置(左上角x,y)和大小(w,h) 須符合圖片大小
        imageLabel2->show();
    }

    if (imageArrayAns.isEmpty())
    {
        qDebug() << "No imageAns to display";
    }
    else if (imageArrayAns.size() != 64 || imageArrayAns[0].size() != 64)
    {
        QMessageBox::critical(this, "Display Gray Image", "Invalid image size");
    }
    else
    {
        for (int row = 0; row < 64; row++)
        {
            for (int col = 0; col < 64; col++)
            {
                int value = imageArrayAns[row][col];                        // 從 imageArray 取得值
                displayImage.setPixel(col, row, qRgb(value, value, value)); // 設置為灰階顏色
            }
        }

        // 更新窗口以顯示影像
        QPixmap pixmap = QPixmap::fromImage(displayImage);
        // 創建 QLabel 用於顯示影像
        QLabel *imageLabelAns(new QLabel(this));
        imageLabelAns->setPixmap(pixmap.scaled(200, 200)); // 顯示 200x200 大小的影像
        imageLabelAns->setGeometry(50, 475, 200, 200);     // 設置影像位置(左上角x,y)和大小(w,h) 須符合圖片大小
        imageLabelAns->show();
    }

    // // 將影像儲存到檔案
    // image.save("gray_image.png");
}

void SecondProcess::displayHistogram()
{
    QPainter painter(this);

    QVector<int> histogram(255, 0);

    for (int row = 0; row < 64; row++)
    {
        for (int col = 0; col < 64; col++)
        {
            int value = imageArrayAns[row][col];
            histogram[value]++;
        }
    }

    int barWidth = 3;       // 條形寬度
    int xOffset = 400;      // x 軸起始位置
    int yOffset = 550;      // y 軸起始位置
    int maxHeight = 500;    // 最大高度
    int labelInterval = 20; // 標籤間隔，交錯顯示

    // 計算最大數值
    int maxCount = *std::max_element(histogram.begin(), histogram.end());

    // 繪製 x 軸
    painter.drawLine(xOffset, yOffset, xOffset + 255 * barWidth, yOffset);

    // 繪製 y 軸
    painter.drawLine(xOffset, yOffset, xOffset, yOffset - maxHeight);

    // 繪製直方圖條形
    for (int i = 0; i < 255; i++) // 只顯示到 255
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

void SecondProcess::paintEvent(QPaintEvent *event) // 繪製事件 使用update()函數時自動觸發
{
    QPainter painter(this);

    // 繪製直方圖
    displayHistogram();
}