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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QPushButton *uploadfile;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QGraphicsView *originalimage;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spatialFilter_kernelSize_spinbox;
    QComboBox *spatialFilter_comboBox;
    QPushButton *ApplySpatialFilter;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_11;
    QGraphicsView *spatialFilterImage;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QLabel *label_5;
    QSpinBox *log_kernelSize_spinbox;
    QLabel *label_4;
    QDoubleSpinBox *log_sigma_spinbox;
    QPushButton *ApplySobelandLoG;
    QDoubleSpinBox *log_threshold_spinbox;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_7;
    QGraphicsView *sobelImage;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_8;
    QGraphicsView *marrHildrethImage;
    QFormLayout *formLayout_2;
    QLabel *label_9;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_16;
    QLabel *label_15;
    QSpinBox *localStatisticalEnhancement_kernelSize_spinbox;
    QDoubleSpinBox *localStatisticalEnhancement_k0_spinbox;
    QDoubleSpinBox *localStatisticalEnhancement_k1_spinbox;
    QDoubleSpinBox *localStatisticalEnhancement_k2_spinbox;
    QDoubleSpinBox *localStatisticalEnhancement_k3_spinbox;
    QDoubleSpinBox *localStatisticalEnhancement_C_spinbox;
    QPushButton *ApplylocalMeanConstrastEnhancement;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_10;
    QGraphicsView *equalizeHistogramRGBImage;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_18;
    QGraphicsView *localMeanContrastEnhancementImage;
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
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        uploadfile = new QPushButton(centralwidget);
        uploadfile->setObjectName("uploadfile");

        gridLayout_2->addWidget(uploadfile, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        originalimage = new QGraphicsView(centralwidget);
        originalimage->setObjectName("originalimage");

        verticalLayout->addWidget(originalimage);


        gridLayout_2->addLayout(verticalLayout, 1, 0, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        spatialFilter_kernelSize_spinbox = new QSpinBox(centralwidget);
        spatialFilter_kernelSize_spinbox->setObjectName("spatialFilter_kernelSize_spinbox");
        spatialFilter_kernelSize_spinbox->setMinimum(1);
        spatialFilter_kernelSize_spinbox->setMaximum(99);
        spatialFilter_kernelSize_spinbox->setSingleStep(2);
        spatialFilter_kernelSize_spinbox->setValue(3);

        formLayout->setWidget(0, QFormLayout::FieldRole, spatialFilter_kernelSize_spinbox);

        spatialFilter_comboBox = new QComboBox(centralwidget);
        spatialFilter_comboBox->addItem(QString());
        spatialFilter_comboBox->addItem(QString());
        spatialFilter_comboBox->addItem(QString());
        spatialFilter_comboBox->addItem(QString());
        spatialFilter_comboBox->setObjectName("spatialFilter_comboBox");

        formLayout->setWidget(1, QFormLayout::FieldRole, spatialFilter_comboBox);

        ApplySpatialFilter = new QPushButton(centralwidget);
        ApplySpatialFilter->setObjectName("ApplySpatialFilter");

        formLayout->setWidget(2, QFormLayout::FieldRole, ApplySpatialFilter);


        gridLayout_2->addLayout(formLayout, 1, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName("label_11");

        verticalLayout_2->addWidget(label_11);

        spatialFilterImage = new QGraphicsView(centralwidget);
        spatialFilterImage->setObjectName("spatialFilterImage");

        verticalLayout_2->addWidget(spatialFilterImage);


        gridLayout_2->addLayout(verticalLayout_2, 1, 2, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        log_kernelSize_spinbox = new QSpinBox(centralwidget);
        log_kernelSize_spinbox->setObjectName("log_kernelSize_spinbox");
        log_kernelSize_spinbox->setMaximum(99);
        log_kernelSize_spinbox->setSingleStep(2);
        log_kernelSize_spinbox->setValue(21);

        gridLayout->addWidget(log_kernelSize_spinbox, 0, 1, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        log_sigma_spinbox = new QDoubleSpinBox(centralwidget);
        log_sigma_spinbox->setObjectName("log_sigma_spinbox");
        log_sigma_spinbox->setMinimum(0.010000000000000);
        log_sigma_spinbox->setMaximum(5.000000000000000);
        log_sigma_spinbox->setSingleStep(0.050000000000000);
        log_sigma_spinbox->setValue(2.000000000000000);

        gridLayout->addWidget(log_sigma_spinbox, 1, 1, 1, 1);

        ApplySobelandLoG = new QPushButton(centralwidget);
        ApplySobelandLoG->setObjectName("ApplySobelandLoG");

        gridLayout->addWidget(ApplySobelandLoG, 3, 1, 1, 1);

        log_threshold_spinbox = new QDoubleSpinBox(centralwidget);
        log_threshold_spinbox->setObjectName("log_threshold_spinbox");

        gridLayout->addWidget(log_threshold_spinbox, 2, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 2, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");

        verticalLayout_4->addWidget(label_7);

        sobelImage = new QGraphicsView(centralwidget);
        sobelImage->setObjectName("sobelImage");

        verticalLayout_4->addWidget(sobelImage);


        gridLayout_2->addLayout(verticalLayout_4, 2, 1, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");

        verticalLayout_5->addWidget(label_8);

        marrHildrethImage = new QGraphicsView(centralwidget);
        marrHildrethImage->setObjectName("marrHildrethImage");

        verticalLayout_5->addWidget(marrHildrethImage);


        gridLayout_2->addLayout(verticalLayout_5, 2, 2, 1, 1);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName("formLayout_2");
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_9);

        label_12 = new QLabel(centralwidget);
        label_12->setObjectName("label_12");

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_12);

        label_13 = new QLabel(centralwidget);
        label_13->setObjectName("label_13");

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_13);

        label_14 = new QLabel(centralwidget);
        label_14->setObjectName("label_14");

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_14);

        label_16 = new QLabel(centralwidget);
        label_16->setObjectName("label_16");

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_16);

        label_15 = new QLabel(centralwidget);
        label_15->setObjectName("label_15");

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_15);

        localStatisticalEnhancement_kernelSize_spinbox = new QSpinBox(centralwidget);
        localStatisticalEnhancement_kernelSize_spinbox->setObjectName("localStatisticalEnhancement_kernelSize_spinbox");
        localStatisticalEnhancement_kernelSize_spinbox->setMinimum(1);
        localStatisticalEnhancement_kernelSize_spinbox->setMaximum(99);
        localStatisticalEnhancement_kernelSize_spinbox->setSingleStep(2);
        localStatisticalEnhancement_kernelSize_spinbox->setValue(3);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, localStatisticalEnhancement_kernelSize_spinbox);

        localStatisticalEnhancement_k0_spinbox = new QDoubleSpinBox(centralwidget);
        localStatisticalEnhancement_k0_spinbox->setObjectName("localStatisticalEnhancement_k0_spinbox");
        localStatisticalEnhancement_k0_spinbox->setMinimum(0.000000000000000);
        localStatisticalEnhancement_k0_spinbox->setMaximum(5.000000000000000);
        localStatisticalEnhancement_k0_spinbox->setSingleStep(0.050000000000000);
        localStatisticalEnhancement_k0_spinbox->setValue(0.000000000000000);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, localStatisticalEnhancement_k0_spinbox);

        localStatisticalEnhancement_k1_spinbox = new QDoubleSpinBox(centralwidget);
        localStatisticalEnhancement_k1_spinbox->setObjectName("localStatisticalEnhancement_k1_spinbox");
        localStatisticalEnhancement_k1_spinbox->setMinimum(0.000000000000000);
        localStatisticalEnhancement_k1_spinbox->setMaximum(5.000000000000000);
        localStatisticalEnhancement_k1_spinbox->setSingleStep(0.050000000000000);
        localStatisticalEnhancement_k1_spinbox->setValue(0.250000000000000);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, localStatisticalEnhancement_k1_spinbox);

        localStatisticalEnhancement_k2_spinbox = new QDoubleSpinBox(centralwidget);
        localStatisticalEnhancement_k2_spinbox->setObjectName("localStatisticalEnhancement_k2_spinbox");
        localStatisticalEnhancement_k2_spinbox->setMinimum(0.000000000000000);
        localStatisticalEnhancement_k2_spinbox->setMaximum(5.000000000000000);
        localStatisticalEnhancement_k2_spinbox->setSingleStep(0.050000000000000);
        localStatisticalEnhancement_k2_spinbox->setValue(0.000000000000000);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, localStatisticalEnhancement_k2_spinbox);

        localStatisticalEnhancement_k3_spinbox = new QDoubleSpinBox(centralwidget);
        localStatisticalEnhancement_k3_spinbox->setObjectName("localStatisticalEnhancement_k3_spinbox");
        localStatisticalEnhancement_k3_spinbox->setMinimum(0.000000000000000);
        localStatisticalEnhancement_k3_spinbox->setMaximum(5.000000000000000);
        localStatisticalEnhancement_k3_spinbox->setSingleStep(0.050000000000000);
        localStatisticalEnhancement_k3_spinbox->setValue(0.100000000000000);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, localStatisticalEnhancement_k3_spinbox);

        localStatisticalEnhancement_C_spinbox = new QDoubleSpinBox(centralwidget);
        localStatisticalEnhancement_C_spinbox->setObjectName("localStatisticalEnhancement_C_spinbox");
        localStatisticalEnhancement_C_spinbox->setMinimum(0.000000000000000);
        localStatisticalEnhancement_C_spinbox->setMaximum(999.000000000000000);
        localStatisticalEnhancement_C_spinbox->setSingleStep(0.050000000000000);
        localStatisticalEnhancement_C_spinbox->setValue(22.800000000000001);

        formLayout_2->setWidget(5, QFormLayout::FieldRole, localStatisticalEnhancement_C_spinbox);

        ApplylocalMeanConstrastEnhancement = new QPushButton(centralwidget);
        ApplylocalMeanConstrastEnhancement->setObjectName("ApplylocalMeanConstrastEnhancement");

        formLayout_2->setWidget(6, QFormLayout::FieldRole, ApplylocalMeanConstrastEnhancement);


        gridLayout_2->addLayout(formLayout_2, 3, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");

        verticalLayout_3->addWidget(label_10);

        equalizeHistogramRGBImage = new QGraphicsView(centralwidget);
        equalizeHistogramRGBImage->setObjectName("equalizeHistogramRGBImage");

        verticalLayout_3->addWidget(equalizeHistogramRGBImage);


        gridLayout_2->addLayout(verticalLayout_3, 3, 1, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_18 = new QLabel(centralwidget);
        label_18->setObjectName("label_18");

        verticalLayout_6->addWidget(label_18);

        localMeanContrastEnhancementImage = new QGraphicsView(centralwidget);
        localMeanContrastEnhancementImage->setObjectName("localMeanContrastEnhancementImage");

        verticalLayout_6->addWidget(localMeanContrastEnhancementImage);


        gridLayout_2->addLayout(verticalLayout_6, 3, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1080, 20));
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

        ApplySpatialFilter->setText(QCoreApplication::translate("MainWindow", "ApplySpatialFilter", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Spatial Filter", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "gauss kernel size \n"
"(1~99)", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "zero cross \n"
"threshold (0.0~99.0)", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "gauss sigma \n"
"(0.01~5.0)", nullptr));
        ApplySobelandLoG->setText(QCoreApplication::translate("MainWindow", "Apply sobel and LoG", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "sobel", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "LoG", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "local kernel size \n"
"(1~99)", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "k0 (0.0~5.0)", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "k1 (0.0~5.0)", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "k2 (0.0~5.0)", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "k3 (0.0~5.0)", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "C (0.0~999.0)", nullptr));
        ApplylocalMeanConstrastEnhancement->setText(QCoreApplication::translate("MainWindow", "Apply Local Mean Contrast Enhancement", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "equalize Histogram ", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "localMeanContrastEnhancement", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
