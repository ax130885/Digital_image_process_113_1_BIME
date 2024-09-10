#ifndef SECONDPROCESS_H
#define SECONDPROCESS_H

#include <QWidget>
#include <QFile>
#include <QVector>
#include <QPainter>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>

class SecondProcess : public QWidget
{
    Q_OBJECT
public:
    explicit SecondProcess(QWidget *parent = nullptr);
    QVector<QVector<int>> imageArray1;
    QVector<QVector<int>> imageArray2;
    QVector<QVector<int>> imageArrayAns;
    QVector<QVector<int>> QFileTo2dQVector64(QFile &file);

    int p_loadImage(QString image1FileName, QString image2FileName);
    void p_calculateImage(int addend, double multiplier);
    void p_averageImage();
    void p_gxImage();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void displayGrayImage();
    void displayHistogram();

    QComboBox *image1List;
    QComboBox *image2List;
    QPushButton *loadButton;
    QLineEdit *addend;
    QLineEdit *multiplier;
    QPushButton *calculateButton;
    QPushButton *averageButton;
    QPushButton *gxButton;

    QString image1Path;
    QString image2Path;
    QFile image1;
    QFile image2;
    QLabel *imageLabel1;
    QLabel *imageLabel2;
    QLabel *imageLabelAns;
};

#endif // SECONDPROCESS_H
