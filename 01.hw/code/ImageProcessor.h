#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QWidget>
#include <QImage>
#include <QVector>

class ImageProcessor : public QWidget
{
    Q_OBJECT

public:
    ImageProcessor(QWidget *parent = nullptr);
    bool loadImage(const QString &fileName);
    void clearHistogram();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QVector<int>> imageArray; // 存儲64x64圖像數據
    QImage image;                     // 用於顯示的圖像
    QVector<int> histogram;           // 灰度直方圖

    void generateHistogram();              // 計算直方圖
    void drawHistogram(QPainter &painter); // 繪製直方圖
    void displayGrayImage();               // 顯示灰階影像
};

#endif // IMAGEPROCESSOR_H
