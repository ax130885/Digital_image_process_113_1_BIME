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
#include <QtWidgets/QHBoxLayout>
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
    QPushButton *uploadfile;
    QTabWidget *answer_widget;
    QWidget *prob1_FFT;
    QPushButton *ApplyFFT;
    QWidget *horizontalLayoutWidget;
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_7;
    QGraphicsView *ifftImage;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_9;
    QGraphicsView *diff;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_11;
    QGraphicsView *fftImage_magnitude;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_8;
    QGraphicsView *fftImage_phase;
    QWidget *prob2_HLPF;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_14;
    QLabel *label_19;
    QGraphicsView *butterworthLowPassImage;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_18;
    QGraphicsView *gaussianLowPassImage;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_16;
    QGraphicsView *idealLowPassImage;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_12;
    QGraphicsView *gaussianHighPassImage;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_10;
    QGraphicsView *idealHighPassImage;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_14;
    QGraphicsView *butterworthHighPassImage;
    QGridLayout *gridLayout_3;
    QDoubleSpinBox *prob2_D0_spinbox;
    QPushButton *ApplyHLPF;
    QLabel *label_13;
    QSpinBox *prob2_n_spinbox;
    QLabel *label_17;
    QWidget *prob3_homomorphic;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout_4;
    QDoubleSpinBox *prob3_gamma_L_spinbox;
    QPushButton *ApplyHomomorphic;
    QLabel *label_22;
    QDoubleSpinBox *prob3_gamma_H_spinbox;
    QLabel *label_21;
    QDoubleSpinBox *prob3_D0_spinbox;
    QLabel *label_20;
    QDoubleSpinBox *prob3_c_spinbox;
    QLabel *label_37;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_23;
    QGraphicsView *homomorphicImage;
    QWidget *prob4_MotionBlurred;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout_22;
    QLabel *label_33;
    QGraphicsView *diffImage_wiener;
    QVBoxLayout *verticalLayout_18;
    QLabel *label_29;
    QGraphicsView *inverseFilterImage2;
    QVBoxLayout *verticalLayout_24;
    QLabel *label_35;
    QGraphicsView *GaussianNoiseImage;
    QVBoxLayout *verticalLayout_20;
    QLabel *label_31;
    QGraphicsView *wienerFilterImage;
    QVBoxLayout *verticalLayout_21;
    QLabel *label_32;
    QGraphicsView *diffImage_inv;
    QGridLayout *gridLayout;
    QDoubleSpinBox *prob4_T_spinbox;
    QDoubleSpinBox *prob4_wiener_k_spinbox;
    QLabel *label_5;
    QPushButton *ApplyMotionBlurred;
    QDoubleSpinBox *prob4_b_spinbox;
    QLabel *label_6;
    QDoubleSpinBox *prob4_a_spinbox;
    QLabel *label_15;
    QLabel *label_4;
    QDoubleSpinBox *prob4_inverse_k_spinbox;
    QLabel *label_30;
    QVBoxLayout *verticalLayout_23;
    QLabel *label_34;
    QGraphicsView *motionBlurredImage;
    QVBoxLayout *verticalLayout_19;
    QLabel *label_36;
    QGraphicsView *inverseFilterImage1;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QGraphicsView *originalimage;
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
        uploadfile->setGeometry(QRect(250, 90, 161, 121));
        answer_widget = new QTabWidget(centralwidget);
        answer_widget->setObjectName("answer_widget");
        answer_widget->setGeometry(QRect(10, 280, 1051, 421));
        prob1_FFT = new QWidget();
        prob1_FFT->setObjectName("prob1_FFT");
        ApplyFFT = new QPushButton(prob1_FFT);
        ApplyFFT->setObjectName("ApplyFFT");
        ApplyFFT->setGeometry(QRect(80, 140, 181, 111));
        horizontalLayoutWidget = new QWidget(prob1_FFT);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(340, 10, 571, 381));
        gridLayout_6 = new QGridLayout(horizontalLayoutWidget);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_7 = new QLabel(horizontalLayoutWidget);
        label_7->setObjectName("label_7");

        verticalLayout_4->addWidget(label_7);

        ifftImage = new QGraphicsView(horizontalLayoutWidget);
        ifftImage->setObjectName("ifftImage");

        verticalLayout_4->addWidget(ifftImage);


        gridLayout_6->addLayout(verticalLayout_4, 1, 2, 1, 1);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName("verticalLayout_10");
        label_9 = new QLabel(horizontalLayoutWidget);
        label_9->setObjectName("label_9");

        verticalLayout_10->addWidget(label_9);

        diff = new QGraphicsView(horizontalLayoutWidget);
        diff->setObjectName("diff");

        verticalLayout_10->addWidget(diff);


        gridLayout_6->addLayout(verticalLayout_10, 1, 3, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_11 = new QLabel(horizontalLayoutWidget);
        label_11->setObjectName("label_11");

        verticalLayout_2->addWidget(label_11);

        fftImage_magnitude = new QGraphicsView(horizontalLayoutWidget);
        fftImage_magnitude->setObjectName("fftImage_magnitude");

        verticalLayout_2->addWidget(fftImage_magnitude);


        gridLayout_6->addLayout(verticalLayout_2, 0, 2, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_8 = new QLabel(horizontalLayoutWidget);
        label_8->setObjectName("label_8");

        verticalLayout_5->addWidget(label_8);

        fftImage_phase = new QGraphicsView(horizontalLayoutWidget);
        fftImage_phase->setObjectName("fftImage_phase");

        verticalLayout_5->addWidget(fftImage_phase);


        gridLayout_6->addLayout(verticalLayout_5, 0, 3, 1, 1);

        answer_widget->addTab(prob1_FFT, QString());
        prob2_HLPF = new QWidget();
        prob2_HLPF->setObjectName("prob2_HLPF");
        gridLayoutWidget = new QWidget(prob2_HLPF);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(10, 10, 1031, 371));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName("verticalLayout_14");
        label_19 = new QLabel(gridLayoutWidget);
        label_19->setObjectName("label_19");

        verticalLayout_14->addWidget(label_19);

        butterworthLowPassImage = new QGraphicsView(gridLayoutWidget);
        butterworthLowPassImage->setObjectName("butterworthLowPassImage");

        verticalLayout_14->addWidget(butterworthLowPassImage);


        gridLayout_2->addLayout(verticalLayout_14, 1, 3, 1, 1);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName("verticalLayout_13");
        label_18 = new QLabel(gridLayoutWidget);
        label_18->setObjectName("label_18");

        verticalLayout_13->addWidget(label_18);

        gaussianLowPassImage = new QGraphicsView(gridLayoutWidget);
        gaussianLowPassImage->setObjectName("gaussianLowPassImage");

        verticalLayout_13->addWidget(gaussianLowPassImage);


        gridLayout_2->addLayout(verticalLayout_13, 1, 2, 1, 1);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName("verticalLayout_11");
        label_16 = new QLabel(gridLayoutWidget);
        label_16->setObjectName("label_16");

        verticalLayout_11->addWidget(label_16);

        idealLowPassImage = new QGraphicsView(gridLayoutWidget);
        idealLowPassImage->setObjectName("idealLowPassImage");

        verticalLayout_11->addWidget(idealLowPassImage);


        gridLayout_2->addLayout(verticalLayout_11, 1, 1, 1, 1);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        label_12 = new QLabel(gridLayoutWidget);
        label_12->setObjectName("label_12");

        verticalLayout_7->addWidget(label_12);

        gaussianHighPassImage = new QGraphicsView(gridLayoutWidget);
        gaussianHighPassImage->setObjectName("gaussianHighPassImage");

        verticalLayout_7->addWidget(gaussianHighPassImage);


        gridLayout_2->addLayout(verticalLayout_7, 0, 2, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName("label_10");

        verticalLayout_6->addWidget(label_10);

        idealHighPassImage = new QGraphicsView(gridLayoutWidget);
        idealHighPassImage->setObjectName("idealHighPassImage");

        verticalLayout_6->addWidget(idealHighPassImage);


        gridLayout_2->addLayout(verticalLayout_6, 0, 1, 1, 1);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        label_14 = new QLabel(gridLayoutWidget);
        label_14->setObjectName("label_14");

        verticalLayout_9->addWidget(label_14);

        butterworthHighPassImage = new QGraphicsView(gridLayoutWidget);
        butterworthHighPassImage->setObjectName("butterworthHighPassImage");

        verticalLayout_9->addWidget(butterworthHighPassImage);


        gridLayout_2->addLayout(verticalLayout_9, 0, 3, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        prob2_D0_spinbox = new QDoubleSpinBox(gridLayoutWidget);
        prob2_D0_spinbox->setObjectName("prob2_D0_spinbox");
        prob2_D0_spinbox->setValue(30.000000000000000);

        gridLayout_3->addWidget(prob2_D0_spinbox, 0, 1, 1, 1);

        ApplyHLPF = new QPushButton(gridLayoutWidget);
        ApplyHLPF->setObjectName("ApplyHLPF");

        gridLayout_3->addWidget(ApplyHLPF, 2, 1, 1, 1);

        label_13 = new QLabel(gridLayoutWidget);
        label_13->setObjectName("label_13");

        gridLayout_3->addWidget(label_13, 0, 0, 1, 1);

        prob2_n_spinbox = new QSpinBox(gridLayoutWidget);
        prob2_n_spinbox->setObjectName("prob2_n_spinbox");
        prob2_n_spinbox->setValue(1);

        gridLayout_3->addWidget(prob2_n_spinbox, 1, 1, 1, 1);

        label_17 = new QLabel(gridLayoutWidget);
        label_17->setObjectName("label_17");

        gridLayout_3->addWidget(label_17, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_3, 0, 0, 1, 1);

        answer_widget->addTab(prob2_HLPF, QString());
        prob3_homomorphic = new QWidget();
        prob3_homomorphic->setObjectName("prob3_homomorphic");
        horizontalLayoutWidget_2 = new QWidget(prob3_homomorphic);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(10, 10, 1031, 371));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        prob3_gamma_L_spinbox = new QDoubleSpinBox(horizontalLayoutWidget_2);
        prob3_gamma_L_spinbox->setObjectName("prob3_gamma_L_spinbox");
        prob3_gamma_L_spinbox->setValue(0.500000000000000);

        gridLayout_4->addWidget(prob3_gamma_L_spinbox, 1, 1, 1, 1);

        ApplyHomomorphic = new QPushButton(horizontalLayoutWidget_2);
        ApplyHomomorphic->setObjectName("ApplyHomomorphic");

        gridLayout_4->addWidget(ApplyHomomorphic, 4, 1, 1, 1);

        label_22 = new QLabel(horizontalLayoutWidget_2);
        label_22->setObjectName("label_22");

        gridLayout_4->addWidget(label_22, 1, 0, 1, 1);

        prob3_gamma_H_spinbox = new QDoubleSpinBox(horizontalLayoutWidget_2);
        prob3_gamma_H_spinbox->setObjectName("prob3_gamma_H_spinbox");
        prob3_gamma_H_spinbox->setValue(2.000000000000000);

        gridLayout_4->addWidget(prob3_gamma_H_spinbox, 0, 1, 1, 1);

        label_21 = new QLabel(horizontalLayoutWidget_2);
        label_21->setObjectName("label_21");

        gridLayout_4->addWidget(label_21, 2, 0, 1, 1);

        prob3_D0_spinbox = new QDoubleSpinBox(horizontalLayoutWidget_2);
        prob3_D0_spinbox->setObjectName("prob3_D0_spinbox");
        prob3_D0_spinbox->setValue(30.000000000000000);

        gridLayout_4->addWidget(prob3_D0_spinbox, 2, 1, 1, 1);

        label_20 = new QLabel(horizontalLayoutWidget_2);
        label_20->setObjectName("label_20");

        gridLayout_4->addWidget(label_20, 0, 0, 1, 1);

        prob3_c_spinbox = new QDoubleSpinBox(horizontalLayoutWidget_2);
        prob3_c_spinbox->setObjectName("prob3_c_spinbox");
        prob3_c_spinbox->setValue(1.000000000000000);

        gridLayout_4->addWidget(prob3_c_spinbox, 3, 1, 1, 1);

        label_37 = new QLabel(horizontalLayoutWidget_2);
        label_37->setObjectName("label_37");

        gridLayout_4->addWidget(label_37, 3, 0, 1, 1);


        horizontalLayout_2->addLayout(gridLayout_4);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        label_23 = new QLabel(horizontalLayoutWidget_2);
        label_23->setObjectName("label_23");

        verticalLayout_8->addWidget(label_23);

        homomorphicImage = new QGraphicsView(horizontalLayoutWidget_2);
        homomorphicImage->setObjectName("homomorphicImage");

        verticalLayout_8->addWidget(homomorphicImage);


        horizontalLayout_2->addLayout(verticalLayout_8);

        answer_widget->addTab(prob3_homomorphic, QString());
        prob4_MotionBlurred = new QWidget();
        prob4_MotionBlurred->setObjectName("prob4_MotionBlurred");
        gridLayoutWidget_2 = new QWidget(prob4_MotionBlurred);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(20, 10, 1021, 371));
        gridLayout_5 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_22 = new QVBoxLayout();
        verticalLayout_22->setObjectName("verticalLayout_22");
        label_33 = new QLabel(gridLayoutWidget_2);
        label_33->setObjectName("label_33");

        verticalLayout_22->addWidget(label_33);

        diffImage_wiener = new QGraphicsView(gridLayoutWidget_2);
        diffImage_wiener->setObjectName("diffImage_wiener");

        verticalLayout_22->addWidget(diffImage_wiener);


        gridLayout_5->addLayout(verticalLayout_22, 1, 3, 1, 1);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setObjectName("verticalLayout_18");
        label_29 = new QLabel(gridLayoutWidget_2);
        label_29->setObjectName("label_29");

        verticalLayout_18->addWidget(label_29);

        inverseFilterImage2 = new QGraphicsView(gridLayoutWidget_2);
        inverseFilterImage2->setObjectName("inverseFilterImage2");

        verticalLayout_18->addWidget(inverseFilterImage2);


        gridLayout_5->addLayout(verticalLayout_18, 1, 0, 1, 1);

        verticalLayout_24 = new QVBoxLayout();
        verticalLayout_24->setObjectName("verticalLayout_24");
        label_35 = new QLabel(gridLayoutWidget_2);
        label_35->setObjectName("label_35");

        verticalLayout_24->addWidget(label_35);

        GaussianNoiseImage = new QGraphicsView(gridLayoutWidget_2);
        GaussianNoiseImage->setObjectName("GaussianNoiseImage");

        verticalLayout_24->addWidget(GaussianNoiseImage);


        gridLayout_5->addLayout(verticalLayout_24, 0, 2, 1, 1);

        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setObjectName("verticalLayout_20");
        label_31 = new QLabel(gridLayoutWidget_2);
        label_31->setObjectName("label_31");

        verticalLayout_20->addWidget(label_31);

        wienerFilterImage = new QGraphicsView(gridLayoutWidget_2);
        wienerFilterImage->setObjectName("wienerFilterImage");

        verticalLayout_20->addWidget(wienerFilterImage);


        gridLayout_5->addLayout(verticalLayout_20, 1, 1, 1, 1);

        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setObjectName("verticalLayout_21");
        label_32 = new QLabel(gridLayoutWidget_2);
        label_32->setObjectName("label_32");

        verticalLayout_21->addWidget(label_32);

        diffImage_inv = new QGraphicsView(gridLayoutWidget_2);
        diffImage_inv->setObjectName("diffImage_inv");

        verticalLayout_21->addWidget(diffImage_inv);


        gridLayout_5->addLayout(verticalLayout_21, 1, 2, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        prob4_T_spinbox = new QDoubleSpinBox(gridLayoutWidget_2);
        prob4_T_spinbox->setObjectName("prob4_T_spinbox");
        prob4_T_spinbox->setSingleStep(0.100000000000000);
        prob4_T_spinbox->setValue(1.000000000000000);

        gridLayout->addWidget(prob4_T_spinbox, 0, 1, 1, 1);

        prob4_wiener_k_spinbox = new QDoubleSpinBox(gridLayoutWidget_2);
        prob4_wiener_k_spinbox->setObjectName("prob4_wiener_k_spinbox");
        prob4_wiener_k_spinbox->setSingleStep(0.010000000000000);
        prob4_wiener_k_spinbox->setValue(0.010000000000000);

        gridLayout->addWidget(prob4_wiener_k_spinbox, 4, 1, 1, 1);

        label_5 = new QLabel(gridLayoutWidget_2);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        ApplyMotionBlurred = new QPushButton(gridLayoutWidget_2);
        ApplyMotionBlurred->setObjectName("ApplyMotionBlurred");

        gridLayout->addWidget(ApplyMotionBlurred, 5, 1, 1, 1);

        prob4_b_spinbox = new QDoubleSpinBox(gridLayoutWidget_2);
        prob4_b_spinbox->setObjectName("prob4_b_spinbox");
        prob4_b_spinbox->setSingleStep(0.050000000000000);
        prob4_b_spinbox->setValue(0.100000000000000);

        gridLayout->addWidget(prob4_b_spinbox, 2, 1, 1, 1);

        label_6 = new QLabel(gridLayoutWidget_2);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        prob4_a_spinbox = new QDoubleSpinBox(gridLayoutWidget_2);
        prob4_a_spinbox->setObjectName("prob4_a_spinbox");
        prob4_a_spinbox->setSingleStep(0.050000000000000);
        prob4_a_spinbox->setValue(0.100000000000000);

        gridLayout->addWidget(prob4_a_spinbox, 1, 1, 1, 1);

        label_15 = new QLabel(gridLayoutWidget_2);
        label_15->setObjectName("label_15");

        gridLayout->addWidget(label_15, 4, 0, 1, 1);

        label_4 = new QLabel(gridLayoutWidget_2);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        prob4_inverse_k_spinbox = new QDoubleSpinBox(gridLayoutWidget_2);
        prob4_inverse_k_spinbox->setObjectName("prob4_inverse_k_spinbox");
        prob4_inverse_k_spinbox->setSingleStep(0.100000000000000);
        prob4_inverse_k_spinbox->setValue(0.500000000000000);

        gridLayout->addWidget(prob4_inverse_k_spinbox, 3, 1, 1, 1);

        label_30 = new QLabel(gridLayoutWidget_2);
        label_30->setObjectName("label_30");

        gridLayout->addWidget(label_30, 3, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout, 0, 0, 1, 1);

        verticalLayout_23 = new QVBoxLayout();
        verticalLayout_23->setObjectName("verticalLayout_23");
        label_34 = new QLabel(gridLayoutWidget_2);
        label_34->setObjectName("label_34");

        verticalLayout_23->addWidget(label_34);

        motionBlurredImage = new QGraphicsView(gridLayoutWidget_2);
        motionBlurredImage->setObjectName("motionBlurredImage");

        verticalLayout_23->addWidget(motionBlurredImage);


        gridLayout_5->addLayout(verticalLayout_23, 0, 1, 1, 1);

        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setObjectName("verticalLayout_19");
        label_36 = new QLabel(gridLayoutWidget_2);
        label_36->setObjectName("label_36");

        verticalLayout_19->addWidget(label_36);

        inverseFilterImage1 = new QGraphicsView(gridLayoutWidget_2);
        inverseFilterImage1->setObjectName("inverseFilterImage1");

        verticalLayout_19->addWidget(inverseFilterImage1);


        gridLayout_5->addLayout(verticalLayout_19, 0, 3, 1, 1);

        answer_widget->addTab(prob4_MotionBlurred, QString());
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(570, 10, 391, 291));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        originalimage = new QGraphicsView(layoutWidget);
        originalimage->setObjectName("originalimage");

        verticalLayout->addWidget(originalimage);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1080, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        answer_widget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        uploadfile->setText(QCoreApplication::translate("MainWindow", "upload file", nullptr));
        ApplyFFT->setText(QCoreApplication::translate("MainWindow", "ApplyFFT", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "ifftImage", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "origin - ifftImage", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "fftImage_magnitude", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "fftImage_phase", nullptr));
        answer_widget->setTabText(answer_widget->indexOf(prob1_FFT), QCoreApplication::translate("MainWindow", "prob1_FFT", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "butterworthLowPassImage", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "gaussianLowPassImage", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "idealLowPassImage", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "gaussianHighPassImage", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "idealHighPassImage", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "butterworthHighPassImage", nullptr));
        ApplyHLPF->setText(QCoreApplication::translate("MainWindow", "ApplyHLPF", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "D0", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "n", nullptr));
        answer_widget->setTabText(answer_widget->indexOf(prob2_HLPF), QCoreApplication::translate("MainWindow", "prob2_HLPF", nullptr));
        ApplyHomomorphic->setText(QCoreApplication::translate("MainWindow", "ApplyHomomorphic", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "gamma_L", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "D_0", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "gamma_H", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "homomorphicImage", nullptr));
        answer_widget->setTabText(answer_widget->indexOf(prob3_homomorphic), QCoreApplication::translate("MainWindow", "prob3_homomorphic", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "\345\216\237\345\234\226 - winer filter  (\347\247\273\345\213\225\346\250\241\347\263\212+\347\231\275\351\253\230\346\226\257\351\233\234\350\250\212(sigma=20))", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", "inverse filter (\347\247\273\345\213\225\346\250\241\347\263\212+\347\231\275\351\253\230\346\226\257\351\233\234\350\250\212(sigma=20))", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", "\347\247\273\345\213\225\346\250\241\347\263\212+\347\231\275\351\253\230\346\226\257\351\233\234\350\250\212(sigma=20)", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "winer filter (\347\247\273\345\213\225\346\250\241\347\263\212+\347\231\275\351\253\230\346\226\257\351\233\234\350\250\212(sigma=20))", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "\345\216\237\345\234\226 - inverse filter  (\347\247\273\345\213\225\346\250\241\347\263\212+\347\231\275\351\253\230\346\226\257\351\233\234\350\250\212(sigma=20))", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "b(Y\351\200\237\345\272\246)", nullptr));
        ApplyMotionBlurred->setText(QCoreApplication::translate("MainWindow", "ApplyMotionBlurred", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\345\277\253\351\226\200\346\231\202\351\226\223", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "wiener_K", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "a(X\351\200\237\345\272\246)", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "inverse_K", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "\347\247\273\345\213\225\346\250\241\347\263\212", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "inverse filter (\347\247\273\345\213\225\346\250\241\347\263\212)", nullptr));
        answer_widget->setTabText(answer_widget->indexOf(prob4_MotionBlurred), QCoreApplication::translate("MainWindow", "prob4_MotionBlurred", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Original imamge", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
