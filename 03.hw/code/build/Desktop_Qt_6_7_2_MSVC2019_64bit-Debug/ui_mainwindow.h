/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *uploadfile;
    QGraphicsView *originalimage;
    QLabel *label;
    QSpinBox *spatialFilter_kernelSize_spinbox;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *spatialFilter_comboBox;
    QDoubleSpinBox *contrast_spinbox_2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QSpinBox *threshold_rgb_spinbox_3;
    QSpinBox *threshold_rgb_spinbox_5;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QSpinBox *threshold_rgb_spinbox_6;
    QGraphicsView *graphicsView_2;
    QGraphicsView *spatialFilterImage;
    QGraphicsView *graphicsView_4;
    QGraphicsView *graphicsView_5;
    QLabel *label_10;
    QLabel *label_11;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1080, 750);
        MainWindow->setAutoFillBackground(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        uploadfile = new QPushButton(centralwidget);
        uploadfile->setObjectName("uploadfile");
        uploadfile->setGeometry(QRect(30, 20, 80, 23));
        originalimage = new QGraphicsView(centralwidget);
        originalimage->setObjectName("originalimage");
        originalimage->setGeometry(QRect(150, 50, 256, 192));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(160, 20, 101, 16));
        spatialFilter_kernelSize_spinbox = new QSpinBox(centralwidget);
        spatialFilter_kernelSize_spinbox->setObjectName("spatialFilter_kernelSize_spinbox");
        spatialFilter_kernelSize_spinbox->setGeometry(QRect(630, 20, 124, 24));
        spatialFilter_kernelSize_spinbox->setMinimum(1);
        spatialFilter_kernelSize_spinbox->setMaximum(99);
        spatialFilter_kernelSize_spinbox->setSingleStep(2);
        spatialFilter_kernelSize_spinbox->setValue(3);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(450, 30, 151, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(450, 80, 161, 16));
        spatialFilter_comboBox = new QComboBox(centralwidget);
        spatialFilter_comboBox->addItem(QString());
        spatialFilter_comboBox->addItem(QString());
        spatialFilter_comboBox->addItem(QString());
        spatialFilter_comboBox->addItem(QString());
        spatialFilter_comboBox->setObjectName("spatialFilter_comboBox");
        spatialFilter_comboBox->setGeometry(QRect(630, 80, 121, 23));
        contrast_spinbox_2 = new QDoubleSpinBox(centralwidget);
        contrast_spinbox_2->setObjectName("contrast_spinbox_2");
        contrast_spinbox_2->setGeometry(QRect(150, 400, 124, 24));
        contrast_spinbox_2->setMaximum(3.000000000000000);
        contrast_spinbox_2->setSingleStep(0.100000000000000);
        contrast_spinbox_2->setValue(1.000000000000000);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 400, 121, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 440, 121, 16));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 370, 101, 16));
        threshold_rgb_spinbox_3 = new QSpinBox(centralwidget);
        threshold_rgb_spinbox_3->setObjectName("threshold_rgb_spinbox_3");
        threshold_rgb_spinbox_3->setGeometry(QRect(150, 370, 124, 24));
        threshold_rgb_spinbox_3->setMaximum(256);
        threshold_rgb_spinbox_3->setValue(128);
        threshold_rgb_spinbox_5 = new QSpinBox(centralwidget);
        threshold_rgb_spinbox_5->setObjectName("threshold_rgb_spinbox_5");
        threshold_rgb_spinbox_5->setGeometry(QRect(150, 430, 124, 24));
        threshold_rgb_spinbox_5->setMaximum(256);
        threshold_rgb_spinbox_5->setValue(128);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(290, 260, 101, 16));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(610, 260, 101, 16));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(30, 560, 101, 16));
        threshold_rgb_spinbox_6 = new QSpinBox(centralwidget);
        threshold_rgb_spinbox_6->setObjectName("threshold_rgb_spinbox_6");
        threshold_rgb_spinbox_6->setGeometry(QRect(140, 560, 124, 24));
        threshold_rgb_spinbox_6->setMaximum(256);
        threshold_rgb_spinbox_6->setValue(128);
        graphicsView_2 = new QGraphicsView(centralwidget);
        graphicsView_2->setObjectName("graphicsView_2");
        graphicsView_2->setGeometry(QRect(290, 280, 256, 192));
        spatialFilterImage = new QGraphicsView(centralwidget);
        spatialFilterImage->setObjectName("spatialFilterImage");
        spatialFilterImage->setGeometry(QRect(780, 40, 256, 192));
        graphicsView_4 = new QGraphicsView(centralwidget);
        graphicsView_4->setObjectName("graphicsView_4");
        graphicsView_4->setGeometry(QRect(600, 280, 256, 192));
        graphicsView_5 = new QGraphicsView(centralwidget);
        graphicsView_5->setObjectName("graphicsView_5");
        graphicsView_5->setGeometry(QRect(290, 510, 256, 192));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(290, 490, 101, 16));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(780, 20, 101, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1080, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        uploadfile->setText(QCoreApplication::translate("MainWindow", "upload file", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Original imamge", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "kernel size (1~99)", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "spatial filtering type", nullptr));
        spatialFilter_comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "median \344\270\255\344\275\215", nullptr));
        spatialFilter_comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "mean \345\271\263\345\235\207", nullptr));
        spatialFilter_comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "max \346\234\200\345\244\247", nullptr));
        spatialFilter_comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "min \346\234\200\345\260\217", nullptr));

        label_4->setText(QCoreApplication::translate("MainWindow", "sigma", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "threshold", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "kernel size", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "sobel", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "LoG", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "neighbor size", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "TT", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Spatial Filter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
