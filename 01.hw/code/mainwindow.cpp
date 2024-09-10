#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include "QDebug"
#include <Qdir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 修改窗口標題
    setWindowTitle("Image Processor");
    // 修改窗口大小(W, H) (後續可拖拉縮放)
    resize(1200, 800);

    // 創建中央小部件和佈局
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 創建水平佈局用於放置控制元件
    QHBoxLayout *controlLayout = new QHBoxLayout();

    // 將控制佈局添加到主佈局
    mainLayout->addLayout(controlLayout);

    // 創建並填充文件選擇器下拉框
    fileSelector = new QComboBox(this);
    fileSelector->addItem("LISA.64");
    fileSelector->addItem("LINCOLN.64");
    fileSelector->addItem("LIBERTY.64");
    fileSelector->addItem("JET.64");
    controlLayout->addWidget(fileSelector);

    // 創建加載按鈕
    loadButton = new QPushButton("Load Image", this);
    controlLayout->addWidget(loadButton);

    // 創建清除按鈕
    cleanButton = new QPushButton("Clean Histogram", this);
    controlLayout->addWidget(cleanButton);

    // 創建上傳按鈕
    uploadButton = new QPushButton("Upload File", this);
    controlLayout->addWidget(uploadButton);

    // 創建 ImageProcessor
    processor = new ImageProcessor(this);
    mainLayout->addWidget(processor);

    // 設置中央小部件
    setCentralWidget(centralWidget);

    // 連接按鈕點擊到相應的槽
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadSelectedFile);
    connect(cleanButton, &QPushButton::clicked, this, &MainWindow::cleanHistogram);
    connect(uploadButton, &QPushButton::clicked, this, &MainWindow::uploadFile);

    // 初始化時隱藏直方圖
    processor->hide();

    // 輸出訊息到控制台和日誌 類似cout, printf
    qDebug() << "MainWindow initialized";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadSelectedFile()
{
    QString selectedFile = fileSelector->currentText();
    currentFilePath = QDir::currentPath() + "/" + selectedFile;

    if (processor->loadImage(currentFilePath))
    {
        processor->show();
        processor->update(); // 強制重繪 ImageProcessor 小部件
        // QMessageBox::information(this, "File Loaded", "Loaded file: " + currentFilePath);
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to load file: " + currentFilePath);
        processor->hide();
    }
}

void MainWindow::cleanHistogram()
{
    processor->hide();
    processor->clearHistogram();
}

void MainWindow::uploadFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open .64 File", "", "64 Files (*.64)");
    if (!filePath.isEmpty())
    {
        currentFilePath = filePath;
        if (processor->loadImage(currentFilePath))
        {
            processor->show();
            processor->update();
            // QMessageBox::information(this, "File Uploaded", "Loaded file: " + QFileInfo(filePath).fileName());
        }
        else
        {
            QMessageBox::critical(this, "Error", "Failed to load file: " + QFileInfo(filePath).fileName());
            processor->hide();
        }
    }
}
