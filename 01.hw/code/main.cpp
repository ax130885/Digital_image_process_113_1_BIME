// main.cpp
#include "mainwindow.h"
#include "secondwindow.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 創建一個初始窗口
    QWidget initialWindow;
    initialWindow.setWindowTitle("Select a question");
    initialWindow.resize(300, 200);

    // 創建兩個按鈕
    QPushButton *button1 = new QPushButton("顯示第一題", &initialWindow);
    QPushButton *button2 = new QPushButton("顯示第二題", &initialWindow);

    // 使用 QVBoxLayout 來排放按鈕
    QVBoxLayout *layout = new QVBoxLayout(&initialWindow);
    layout->addWidget(button1);
    layout->addWidget(button2);

    // 創建 MainWindow 和 SecondWindow 物件
    MainWindow mainWindow;
    SecondWindow secondWindow;

    // 點擊按鈕1顯示 MainWindow
    QObject::connect(button1, &QPushButton::clicked, [&]()
                     {
                         mainWindow.show();
                         initialWindow.hide(); // 隱藏初始窗口
                     });

    // 點擊按鈕2顯示 SecondWindow
    QObject::connect(button2, &QPushButton::clicked, [&]()
                     {
                         secondWindow.show();
                         initialWindow.hide(); // 隱藏初始窗口
                     });

    // 顯示初始窗口
    initialWindow.show();

    return a.exec();
}
