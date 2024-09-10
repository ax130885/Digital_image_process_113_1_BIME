#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QFileDialog>
#include "ImageProcessor.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    // 解構函數 釋放資源用 解構函數不會被繼承
    // 父類的解構函數會先被調用但是不會先被釋放, 會等到子類的解構函數被調用完畢後才會釋放
    ~MainWindow();

private slots:
    void loadSelectedFile();
    void cleanHistogram();
    void uploadFile();

private:
    Ui::MainWindow *ui;
    QComboBox *fileSelector;
    QPushButton *loadButton;
    QPushButton *cleanButton;
    QPushButton *uploadButton;
    ImageProcessor *processor;
    QString currentFilePath;
};
#endif // MAINWINDOW_H