// SecondWindow.cpp
#include "secondwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QDir>
#include <QDebug>
#include <QComboBox>
#include <QLineEdit>
#include <QIntValidator> // 用來限制輸入為整數
#include <QPushButton>
#include <QLabel>
#include <QPainter>

SecondWindow::SecondWindow(QWidget *parent) : QMainWindow(parent)
{
    // 設置窗口標題
    setWindowTitle("Second Window");
    resize(1200, 900); // 調整窗口大小

    // 創建中央小部件和佈局
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 將控制佈局添加到主佈局
    QHBoxLayout *controlLayout = new QHBoxLayout();

    // 將控制佈局添加到主佈局
    mainLayout->addLayout(controlLayout);

    // 設置中央小部件
    setCentralWidget(centralWidget);

    // 創建一個不可互動的文字框
    QLabel *infoLabel1 = new QLabel("每次更改圖片選單後，需要重新點擊load，三種運算才會生效。", this);
    mainLayout->addWidget(infoLabel1);
    infoLabel1->setFixedHeight(20);
    infoLabel1->setFixedWidth(500);

    // 創建一個不可互動的文字框
    QLabel *infoLabel2 = new QLabel("cal根據第一張(左選單)圖片運算。", this);
    mainLayout->addWidget(infoLabel2);
    infoLabel2->setFixedHeight(20);
    infoLabel2->setFixedWidth(500);

    // 創造兩個影像選單 // 取得選單的值 image1List->currentText();
    QComboBox *image1List = new QComboBox(this);
    image1List->addItem("LISA.64");
    image1List->addItem("LINCOLN.64");
    image1List->addItem("LIBERTY.64");
    image1List->addItem("JET.64");
    image1List->setFixedWidth(100);
    controlLayout->addWidget(image1List);
    image1List->currentText();

    QComboBox *image2List = new QComboBox(this);
    image2List->addItem("LISA.64");
    image2List->addItem("LINCOLN.64");
    image2List->addItem("LIBERTY.64");
    image2List->addItem("JET.64");
    image2List->addItem("None");
    image2List->setFixedWidth(100);
    controlLayout->addWidget(image2List);

    // 創建載入影像按鈕
    QPushButton *loadButton = new QPushButton("Load Image", this);
    controlLayout->addWidget(loadButton);

    // 創建加數輸入框 // 取得輸入的值 int addend = addend->text().toInt();
    QLineEdit *addend = new QLineEdit(this);
    addend->setValidator(new QIntValidator(-31, 31, this));
    addend->setPlaceholderText("輸入加數 (限+-31之間的整數)");
    addend->setFixedWidth(200);
    controlLayout->addWidget(addend);

    // 連接 editingFinished 信號到槽函數 (如果輸入值超過上下限 自動修正為上下限)
    connect(addend, &QLineEdit::textEdited, this, [addend]()
            {
        bool ok;
        int value = addend->text().toInt(&ok);
        if (ok) {
            if (value < -31) {
                addend->setText(QString::number(-31));
            } else if (value > 31) {
                addend->setText(QString::number(31));
            }
        } });

    // 創建乘數輸入框 // 取得輸入的值 int multiplierValue = multiplier->text().toInt();
    QLineEdit *multiplier = new QLineEdit(this);
    multiplier->setValidator(new QDoubleValidator(0.0, 31.0, 2, this));
    multiplier->setPlaceholderText("輸入乘數 (限0.0~31.0之間.2f浮點數)");
    multiplier->setFixedWidth(200);
    controlLayout->addWidget(multiplier);

    // 連接 editingFinished 信號到槽函數 (如果輸入值超過上下限 自動修正為上下限)
    connect(multiplier, &QLineEdit::textEdited, this, [multiplier]()
            {
        bool ok;
        double value = multiplier->text().toDouble(&ok);
        if (ok) {
            if (value < -31.0) {
                multiplier->setText(QString::number(0.0, 'f', 2));
            } else if (value > 31.0) {
                multiplier->setText(QString::number(31.0, 'f', 2));
            }
        } });

    // 創建計算按鈕 (需產生一個新的影像)
    QPushButton *calculateButton = new QPushButton("Calculate for image1 (先乘後加)", this);
    controlLayout->addWidget(calculateButton);

    // 創建計算兩影像平均按鈕 (需產生一個新的影像)
    QPushButton *averageButton = new QPushButton("Average image1 & 2", this);
    controlLayout->addWidget(averageButton);

    // 創建 g(x,y)=f(x,y)-f(x-1,y) 按鈕 (需產生一個新的影像)
    QPushButton *gxButton = new QPushButton("g(x,y)=f1(x,y)-f2(x-1,y)", this);
    controlLayout->addWidget(gxButton);

    // 創建 SecondProcess 用來放置 結果影像與直方圖
    secondProcess = new SecondProcess(this);
    mainLayout->addWidget(secondProcess);

    // 創建連結訊號與槽函數
    connect(loadButton, &QPushButton::clicked, [this, image1List, image2List]()
            { loadImage(image1List->currentText(), image2List->currentText()); }); // [捕捉列表(等會主函式要用到的物件)](外部輸入參數(來自其他成員或是常數)) {lambda函式主體} 是一個 lambda 函數 並且lambda函數可以隱式轉換為函數指針
    // 下面用法會報錯 因為槽函數接受的格式為指標 如果使用&func(args)會變成返回值 而非指標
    // 相當於image1List->currentText()是保存connect建立時捕捉到的list值 而非訊號觸發時的list值
    // connect(loadButton, &QPushButton::clicked, &SecondWindow::loadImage(image1List->currentText(), image2List->currentText()));
    connect(calculateButton, &QPushButton::clicked, this, [this, addend, multiplier]()
            { calculateImage(addend->text().toInt(), multiplier->text().toDouble()); });
    connect(averageButton, &QPushButton::clicked, this, &SecondWindow::averageImage);
    connect(gxButton, &QPushButton::clicked, this, &SecondWindow::gxImage);
}

void SecondWindow::loadImage(QString image1FileName, QString image2FileName)
{

    secondProcess->p_loadImage(image1FileName, image2FileName);
}

void SecondWindow::calculateImage(int addend, double multiplier)
{
    secondProcess->p_calculateImage(addend, multiplier);
}

void SecondWindow::averageImage()
{
    secondProcess->p_averageImage();
}

void SecondWindow::gxImage()
{
    secondProcess->p_gxImage();
}
