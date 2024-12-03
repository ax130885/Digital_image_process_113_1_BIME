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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *GeometricTransformation;
    QPushButton *uploadfile;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_7;
    QGraphicsView *trapezoidalGeometricTransformationImage;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_8;
    QGraphicsView *wavyGeometricTransformationImage;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_9;
    QGraphicsView *circularGeometricTransformationImage;
    QGridLayout *gridLayout_7;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QGraphicsView *originalImage;
    QGridLayout *gridLayout_6;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QDoubleSpinBox *amplitudeSpinBox;
    QDoubleSpinBox *frequencySpinBox;
    QDoubleSpinBox *phaseSpinBox;
    QGridLayout *gridLayout_5;
    QLabel *label_19;
    QDoubleSpinBox *scaleXSpinBox;
    QDoubleSpinBox *scaleYSpinBox;
    QLabel *label_17;
    QWidget *DWTfusion;
    QPushButton *uploadfile_2;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_14;
    QGraphicsView *imageFusionImage;
    QGridLayout *gridLayout_8;
    QDoubleSpinBox *levelSpinBox;
    QLabel *label_25;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QGraphicsView *originalImage_2;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_11;
    QGraphicsView *originalImage_4;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_10;
    QGraphicsView *originalImage_3;
    QVBoxLayout *verticalLayout_6;
    QPushButton *uploadfile_4;
    QPushButton *uploadfile_5;
    QPushButton *uploadfile_6;
    QWidget *SLICseg;
    QPushButton *uploadfile_3;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_14;
    QLabel *label_18;
    QGraphicsView *segmentedImage;
    QVBoxLayout *verticalLayout_12;
    QGridLayout *gridLayout_9;
    QSpinBox *KspinBox;
    QDoubleSpinBox *MdoubleSpinBox;
    QLabel *label_27;
    QLabel *label_26;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QGraphicsView *boundaryImage;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_4;
    QGraphicsView *originalimage_4;
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
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(20, 10, 1041, 691));
        GeometricTransformation = new QWidget();
        GeometricTransformation->setObjectName("GeometricTransformation");
        uploadfile = new QPushButton(GeometricTransformation);
        uploadfile->setObjectName("uploadfile");
        uploadfile->setGeometry(QRect(10, 20, 161, 51));
        gridLayoutWidget = new QWidget(GeometricTransformation);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(10, 90, 1011, 551));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName("label_7");

        verticalLayout_7->addWidget(label_7);

        trapezoidalGeometricTransformationImage = new QGraphicsView(gridLayoutWidget);
        trapezoidalGeometricTransformationImage->setObjectName("trapezoidalGeometricTransformationImage");

        verticalLayout_7->addWidget(trapezoidalGeometricTransformationImage);


        gridLayout->addLayout(verticalLayout_7, 1, 0, 1, 1);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName("label_8");

        verticalLayout_8->addWidget(label_8);

        wavyGeometricTransformationImage = new QGraphicsView(gridLayoutWidget);
        wavyGeometricTransformationImage->setObjectName("wavyGeometricTransformationImage");

        verticalLayout_8->addWidget(wavyGeometricTransformationImage);


        gridLayout->addLayout(verticalLayout_8, 1, 1, 1, 1);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName("label_9");

        verticalLayout_9->addWidget(label_9);

        circularGeometricTransformationImage = new QGraphicsView(gridLayoutWidget);
        circularGeometricTransformationImage->setObjectName("circularGeometricTransformationImage");

        verticalLayout_9->addWidget(circularGeometricTransformationImage);


        gridLayout->addLayout(verticalLayout_9, 1, 2, 1, 1);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName("gridLayout_7");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(gridLayoutWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        originalImage = new QGraphicsView(gridLayoutWidget);
        originalImage->setObjectName("originalImage");

        verticalLayout->addWidget(originalImage);


        gridLayout_7->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_7, 0, 2, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName("gridLayout_6");
        label_21 = new QLabel(gridLayoutWidget);
        label_21->setObjectName("label_21");
        label_21->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_6->addWidget(label_21, 0, 0, 1, 1);

        label_22 = new QLabel(gridLayoutWidget);
        label_22->setObjectName("label_22");
        label_22->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_6->addWidget(label_22, 1, 0, 1, 1);

        label_23 = new QLabel(gridLayoutWidget);
        label_23->setObjectName("label_23");
        label_23->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_6->addWidget(label_23, 2, 0, 1, 1);

        amplitudeSpinBox = new QDoubleSpinBox(gridLayoutWidget);
        amplitudeSpinBox->setObjectName("amplitudeSpinBox");
        amplitudeSpinBox->setValue(30.000000000000000);

        gridLayout_6->addWidget(amplitudeSpinBox, 0, 1, 1, 1);

        frequencySpinBox = new QDoubleSpinBox(gridLayoutWidget);
        frequencySpinBox->setObjectName("frequencySpinBox");
        frequencySpinBox->setDecimals(4);
        frequencySpinBox->setMinimum(0.000000000000000);
        frequencySpinBox->setMaximum(99.989999999999995);
        frequencySpinBox->setSingleStep(0.001000000000000);
        frequencySpinBox->setValue(0.005000000000000);

        gridLayout_6->addWidget(frequencySpinBox, 1, 1, 1, 1);

        phaseSpinBox = new QDoubleSpinBox(gridLayoutWidget);
        phaseSpinBox->setObjectName("phaseSpinBox");
        phaseSpinBox->setMaximum(6.280000000000000);
        phaseSpinBox->setSingleStep(0.314000000000000);
        phaseSpinBox->setValue(0.000000000000000);

        gridLayout_6->addWidget(phaseSpinBox, 2, 1, 1, 1);


        gridLayout->addLayout(gridLayout_6, 0, 1, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName("gridLayout_5");
        label_19 = new QLabel(gridLayoutWidget);
        label_19->setObjectName("label_19");
        label_19->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_5->addWidget(label_19, 1, 0, 1, 1);

        scaleXSpinBox = new QDoubleSpinBox(gridLayoutWidget);
        scaleXSpinBox->setObjectName("scaleXSpinBox");
        scaleXSpinBox->setMinimum(0.100000000000000);
        scaleXSpinBox->setMaximum(1.000000000000000);
        scaleXSpinBox->setSingleStep(0.100000000000000);
        scaleXSpinBox->setValue(0.800000000000000);

        gridLayout_5->addWidget(scaleXSpinBox, 0, 1, 1, 1);

        scaleYSpinBox = new QDoubleSpinBox(gridLayoutWidget);
        scaleYSpinBox->setObjectName("scaleYSpinBox");
        scaleYSpinBox->setMinimum(0.100000000000000);
        scaleYSpinBox->setMaximum(1.000000000000000);
        scaleYSpinBox->setSingleStep(0.100000000000000);
        scaleYSpinBox->setValue(0.700000000000000);

        gridLayout_5->addWidget(scaleYSpinBox, 1, 1, 1, 1);

        label_17 = new QLabel(gridLayoutWidget);
        label_17->setObjectName("label_17");
        label_17->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_5->addWidget(label_17, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_5, 0, 0, 1, 1);

        tabWidget->addTab(GeometricTransformation, QString());
        DWTfusion = new QWidget();
        DWTfusion->setObjectName("DWTfusion");
        uploadfile_2 = new QPushButton(DWTfusion);
        uploadfile_2->setObjectName("uploadfile_2");
        uploadfile_2->setGeometry(QRect(10, 20, 191, 51));
        gridLayoutWidget_2 = new QWidget(DWTfusion);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(10, 80, 1021, 541));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_14 = new QLabel(gridLayoutWidget_2);
        label_14->setObjectName("label_14");

        verticalLayout_4->addWidget(label_14);

        imageFusionImage = new QGraphicsView(gridLayoutWidget_2);
        imageFusionImage->setObjectName("imageFusionImage");

        verticalLayout_4->addWidget(imageFusionImage);


        gridLayout_2->addLayout(verticalLayout_4, 0, 2, 1, 1);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName("gridLayout_8");
        levelSpinBox = new QDoubleSpinBox(gridLayoutWidget_2);
        levelSpinBox->setObjectName("levelSpinBox");
        levelSpinBox->setDecimals(0);
        levelSpinBox->setMinimum(1.000000000000000);
        levelSpinBox->setMaximum(5.000000000000000);
        levelSpinBox->setSingleStep(1.000000000000000);
        levelSpinBox->setValue(1.000000000000000);

        gridLayout_8->addWidget(levelSpinBox, 0, 1, 1, 1);

        label_25 = new QLabel(gridLayoutWidget_2);
        label_25->setObjectName("label_25");
        label_25->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_8->addWidget(label_25, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_8, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_2 = new QLabel(gridLayoutWidget_2);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        originalImage_2 = new QGraphicsView(gridLayoutWidget_2);
        originalImage_2->setObjectName("originalImage_2");

        verticalLayout_2->addWidget(originalImage_2);


        gridLayout_2->addLayout(verticalLayout_2, 1, 0, 1, 1);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName("verticalLayout_11");
        label_11 = new QLabel(gridLayoutWidget_2);
        label_11->setObjectName("label_11");

        verticalLayout_11->addWidget(label_11);

        originalImage_4 = new QGraphicsView(gridLayoutWidget_2);
        originalImage_4->setObjectName("originalImage_4");

        verticalLayout_11->addWidget(originalImage_4);


        gridLayout_2->addLayout(verticalLayout_11, 1, 2, 1, 1);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName("verticalLayout_10");
        label_10 = new QLabel(gridLayoutWidget_2);
        label_10->setObjectName("label_10");

        verticalLayout_10->addWidget(label_10);

        originalImage_3 = new QGraphicsView(gridLayoutWidget_2);
        originalImage_3->setObjectName("originalImage_3");

        verticalLayout_10->addWidget(originalImage_3);


        gridLayout_2->addLayout(verticalLayout_10, 1, 1, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        uploadfile_4 = new QPushButton(gridLayoutWidget_2);
        uploadfile_4->setObjectName("uploadfile_4");

        verticalLayout_6->addWidget(uploadfile_4);

        uploadfile_5 = new QPushButton(gridLayoutWidget_2);
        uploadfile_5->setObjectName("uploadfile_5");

        verticalLayout_6->addWidget(uploadfile_5);

        uploadfile_6 = new QPushButton(gridLayoutWidget_2);
        uploadfile_6->setObjectName("uploadfile_6");

        verticalLayout_6->addWidget(uploadfile_6);


        gridLayout_2->addLayout(verticalLayout_6, 0, 1, 1, 1);

        tabWidget->addTab(DWTfusion, QString());
        SLICseg = new QWidget();
        SLICseg->setObjectName("SLICseg");
        uploadfile_3 = new QPushButton(SLICseg);
        uploadfile_3->setObjectName("uploadfile_3");
        uploadfile_3->setGeometry(QRect(10, 20, 161, 51));
        gridLayoutWidget_3 = new QWidget(SLICseg);
        gridLayoutWidget_3->setObjectName("gridLayoutWidget_3");
        gridLayoutWidget_3->setGeometry(QRect(10, 80, 1021, 561));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName("verticalLayout_14");
        label_18 = new QLabel(gridLayoutWidget_3);
        label_18->setObjectName("label_18");

        verticalLayout_14->addWidget(label_18);

        segmentedImage = new QGraphicsView(gridLayoutWidget_3);
        segmentedImage->setObjectName("segmentedImage");

        verticalLayout_14->addWidget(segmentedImage);


        gridLayout_3->addLayout(verticalLayout_14, 1, 2, 1, 1);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName("verticalLayout_12");

        gridLayout_3->addLayout(verticalLayout_12, 1, 0, 1, 1);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName("gridLayout_9");
        KspinBox = new QSpinBox(gridLayoutWidget_3);
        KspinBox->setObjectName("KspinBox");
        KspinBox->setMinimum(1);
        KspinBox->setMaximum(999);
        KspinBox->setSingleStep(100);
        KspinBox->setValue(99);
        KspinBox->setDisplayIntegerBase(10);

        gridLayout_9->addWidget(KspinBox, 0, 1, 1, 1);

        MdoubleSpinBox = new QDoubleSpinBox(gridLayoutWidget_3);
        MdoubleSpinBox->setObjectName("MdoubleSpinBox");
        MdoubleSpinBox->setSingleStep(0.100000000000000);
        MdoubleSpinBox->setValue(0.200000000000000);

        gridLayout_9->addWidget(MdoubleSpinBox, 1, 1, 1, 1);

        label_27 = new QLabel(gridLayoutWidget_3);
        label_27->setObjectName("label_27");
        label_27->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_9->addWidget(label_27, 1, 0, 1, 1);

        label_26 = new QLabel(gridLayoutWidget_3);
        label_26->setObjectName("label_26");
        label_26->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_9->addWidget(label_26, 0, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_9, 0, 2, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_3 = new QLabel(gridLayoutWidget_3);
        label_3->setObjectName("label_3");

        verticalLayout_3->addWidget(label_3);

        boundaryImage = new QGraphicsView(gridLayoutWidget_3);
        boundaryImage->setObjectName("boundaryImage");

        verticalLayout_3->addWidget(boundaryImage);


        gridLayout_3->addLayout(verticalLayout_3, 1, 1, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_4 = new QLabel(gridLayoutWidget_3);
        label_4->setObjectName("label_4");

        verticalLayout_5->addWidget(label_4);

        originalimage_4 = new QGraphicsView(gridLayoutWidget_3);
        originalimage_4->setObjectName("originalimage_4");

        verticalLayout_5->addWidget(originalimage_4);


        gridLayout_3->addLayout(verticalLayout_5, 0, 1, 1, 1);

        tabWidget->addTab(SLICseg, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1080, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        uploadfile->setText(QCoreApplication::translate("MainWindow", "upload file", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\346\242\257\345\275\242", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\346\263\242\346\265\252", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\345\234\223\345\275\242", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Original", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "\351\234\207\345\271\205 (pixel)", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "\351\240\273\347\216\207 (rad/pixel)", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "\347\233\270\344\275\215 (rad) (0~6.28(2pi))", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "y \350\273\270\347\270\256\346\224\276\346\257\224\344\276\213", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "x \350\273\270\347\270\256\346\224\276\346\257\224\344\276\213", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(GeometricTransformation), QCoreApplication::translate("MainWindow", "GeometricTransformation", nullptr));
        uploadfile_2->setText(QCoreApplication::translate("MainWindow", "apply fusion", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "\350\236\215\345\220\210\347\265\220\346\236\234", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "level ", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "image1", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "image3", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "image2", nullptr));
        uploadfile_4->setText(QCoreApplication::translate("MainWindow", "upload image 1", nullptr));
        uploadfile_5->setText(QCoreApplication::translate("MainWindow", "upload image 2", nullptr));
        uploadfile_6->setText(QCoreApplication::translate("MainWindow", "(optional) upload image 3", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(DWTfusion), QCoreApplication::translate("MainWindow", "DWTfusion", nullptr));
        uploadfile_3->setText(QCoreApplication::translate("MainWindow", "upload file", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "SegResult", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "m", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "K", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "SLIC\351\202\212\347\225\214", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Original imamge", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(SLICseg), QCoreApplication::translate("MainWindow", "SLICseg", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
