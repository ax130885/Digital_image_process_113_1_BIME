// SecondWindow.h
#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <qstring.h>
#include <QFile>
#include <QLabel>
#include "secondprocess.h"
class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);

private slots:
    void loadImage(QString image1FileName, QString image2FileName);
    void calculateImage(int addend, double multiplier);
    void averageImage();
    void gxImage();

private:
    SecondProcess *secondProcess;
};

#endif // SECONDWINDOW_H
