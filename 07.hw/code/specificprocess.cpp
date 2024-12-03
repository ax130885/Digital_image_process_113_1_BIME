#include "specificprocess.h"
#include <QImage>
#include <QMessageBox>
#include <QDebug>

#include <complex> // 引入複數標頭
#include <random>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

SpecificProcess::SpecificProcess(QObject *parent)
    : QObject{parent}
{
}

// 空間濾波器(自訂kernel size做最大, 最小, 平均, 中位濾波)
std::unique_ptr<QImage> SpecificProcess::spatialFilter(std::unique_ptr<QImage> &image, int kernelSize, QString spatialFilterType)
{
    // 檢查圖像指標是否為空
    if (!image)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid image pointer.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    // 檢查 kernelSize 是否為奇數，必須是奇數才能進行濾波操作
    if (kernelSize % 2 == 0)
    {
        QMessageBox::critical(nullptr, "Error", "Kernel size must be an odd number.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    // 獲取原圖像的寬度和高度
    int origin_width = image->width();
    int origin_height = image->height();

    // 創建一個與原圖像大小相同的 QImage 來存放濾波後的結果
    auto spatialFilterImage = std::make_unique<QImage>(origin_width, origin_height, QImage::Format_RGB32);

    // 對原圖像進行 padding 操作，以便處理邊界
    auto paddedImage = paddingImage(image, kernelSize);

    // 獲取填充後的圖像寬度和高度
    int paddedWidth = static_cast<int>(paddedImage->bytesPerLine() / sizeof(QRgb));

    // 取得圖像的像素數據
    const QRgb *paddedData = reinterpret_cast<const QRgb *>(paddedImage->constBits());

    // 初始化存放 kernel 區域像素值的陣列
    std::vector<int> redValues(kernelSize * kernelSize);
    std::vector<int> greenValues(kernelSize * kernelSize);
    std::vector<int> blueValues(kernelSize * kernelSize);

// 使用 OpenMP 平行化來加速像素遍歷
#pragma omp parallel for collapse(2) schedule(dynamic)
    for (int y = 0; y < origin_height; ++y)
    {
        for (int x = 0; x < origin_width; ++x)
        {
            int index = 0; // 初始化索引，用來存取 kernel 中的每個像素值

            // 將 kernel 區域內的每個像素值存入相應的陣列
            for (int j = 0; j < kernelSize; ++j)
            {
                for (int i = 0; i < kernelSize; ++i)
                {
                    QRgb pixel = paddedData[(y + j) * paddedWidth + (x + i)];
                    redValues[index] = qRed(pixel);
                    greenValues[index] = qGreen(pixel);
                    blueValues[index] = qBlue(pixel);
                    ++index;
                }
            }

            // 初始化新的像素值
            int redValue = 0, greenValue = 0, blueValue = 0;

            // 根據不同的濾波器類型計算新的像素值
            if (spatialFilterType == "mean 平均")
            {
                int redSum = 0, greenSum = 0, blueSum = 0;
#pragma omp simd reduction(+ : redSum, greenSum, blueSum)
                for (int i = 0; i < kernelSize * kernelSize; ++i)
                {
                    redSum += redValues[i];
                    greenSum += greenValues[i];
                    blueSum += blueValues[i];
                }
                redValue = redSum / (kernelSize * kernelSize);
                greenValue = greenSum / (kernelSize * kernelSize);
                blueValue = blueSum / (kernelSize * kernelSize);
            }
            else if (spatialFilterType == "median 中位")
            {
                // 使用 std::nth_element 用途是找到第 n 大的元素 (每個參數的意思為: 起始位置, 第 n 大的元素位置, 結束位置)
                std::nth_element(redValues.begin(), redValues.begin() + redValues.size() / 2, redValues.end());
                std::nth_element(greenValues.begin(), greenValues.begin() + greenValues.size() / 2, greenValues.end());
                std::nth_element(blueValues.begin(), blueValues.begin() + blueValues.size() / 2, blueValues.end());
                redValue = redValues[redValues.size() / 2];
                greenValue = greenValues[greenValues.size() / 2];
                blueValue = blueValues[blueValues.size() / 2];
            }
            else if (spatialFilterType == "max 最大")
            {
                redValue = *std::max_element(redValues.begin(), redValues.end());
                greenValue = *std::max_element(greenValues.begin(), greenValues.end());
                blueValue = *std::max_element(blueValues.begin(), blueValues.end());
            }
            else if (spatialFilterType == "min 最小")
            {
                redValue = *std::min_element(redValues.begin(), redValues.end());
                greenValue = *std::min_element(greenValues.begin(), greenValues.end());
                blueValue = *std::min_element(blueValues.begin(), blueValues.end());
            }
            else // 無效的濾波器類型
            {
                QMessageBox::critical(nullptr, "Error", "Invalid spatial filter type.");
                return paddedImage; // 返回填充後的影像以表示錯誤
            }

            // 設置濾波後的像素值到結果圖像中
            QRgb newPixel = qRgb(redValue, greenValue, blueValue);
            spatialFilterImage->setPixel(x, y, newPixel);
        }
    }

    // 返回濾波後的圖像
    return spatialFilterImage;
}

// 填充圖像(padding)
std::unique_ptr<QImage> SpecificProcess::paddingImage(std::unique_ptr<QImage> &image, int kernelSize, QString type)
{
    if (!image)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid image pointer.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    // 計算 padding 大小，kernelSize 必須為奇數，所以 (kernelSize - 1) / 2 可以得到正確的邊界填充數量
    int padding = (kernelSize - 1) / 2;

    // 獲取原圖像的寬度和高度
    int width = image->width();
    int height = image->height();

    // 創建一個新的 QImage 來存放填充後的結果，寬度和高度分別加上 2 倍的 padding
    auto paddedImage = std::make_unique<QImage>(width + 2 * padding, height + 2 * padding, QImage::Format_RGB32);

    // 判斷填充類型，這裡可以擴展為多種不同的填充策略
    if (type == "zero")
    {
        // 將邊界部分填充為全黑，即 RGB 值為 (0, 0, 0)
        paddedImage->fill(qRgb(0, 0, 0));

        // 填充圖像的中心部分
        for (int y = 0; y < height; ++y)
        {
            // 計算 padding 後的 y 座標，避免多次計算
            int paddedY = y + padding;

            for (int x = 0; x < width; ++x)
            {
                // 計算 padding 後的 x 座標，避免多次計算
                int paddedX = x + padding;

                // 設置新圖像中對應位置的像素值
                paddedImage->setPixel(paddedX, paddedY, image->pixel(x, y));
            }
        }
    }
    else if (type == "replicate")
    {
        // 填充邊界為複製邊緣像素值
        for (int y = 0; y < height + 2 * padding; ++y)
        {
            for (int x = 0; x < width + 2 * padding; ++x)
            {
                int clampedX = std::clamp(x - padding, 0, width - 1);  // 將 x 座標限制在圖像邊界內
                int clampedY = std::clamp(y - padding, 0, height - 1); // 將 y 座標限制在圖像邊界內

                // 使用原圖像邊緣的像素值進行填充
                paddedImage->setPixel(x, y, image->pixel(clampedX, clampedY));
            }
        }
    }
    else
    {
        QMessageBox::critical(nullptr, "Error", "Invalid padding type.");
        return nullptr; // 返回 nullptr 表示錯誤
    }

    return paddedImage; // 返回填充後的圖像
}

// 計算理想低通濾波器圖像
cv::Mat SpecificProcess::idealLowPassFilter(const cv::Mat &shift_dft, double D0)
{
    // 檢查 shift_dft 是否為複數頻譜且不為空
    if (shift_dft.empty() || shift_dft.channels() != 2)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid FFT shift image.");
        return cv::Mat(); // 返回空的 Mat 表示錯誤
    }

    // 獲取頻譜圖尺寸
    int rows = shift_dft.rows;
    int cols = shift_dft.cols;

    // 建立理想低通遮罩
    cv::Mat idealLowPass(rows, cols, CV_32F);
    cv::Point center(cols / 2, rows / 2); // 頻譜中心

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // 計算每個點到中心的距離
            double distance = cv::norm(cv::Point(j, i) - center);
            idealLowPass.at<float>(i, j) = (distance <= D0) ? 1.0f : 0.0f;
        }
    }

    // 將理想低通遮罩轉換為複數格式（頻譜格式需一致）
    cv::Mat complexIdealLowPass;
    cv::Mat planes[] = {idealLowPass, cv::Mat::zeros(rows, cols, CV_32F)};
    cv::merge(planes, 2, complexIdealLowPass);

    // // 顯示 complexIdealLowPass 的非零元素
    // qDebug() << "complexIdealLowPass (non-zero elements):";
    // for (int i = 0; i < rows; ++i)
    // {
    //     for (int j = 0; j < cols; ++j)
    //     {
    //         cv::Vec2f value = complexIdealLowPass.at<cv::Vec2f>(i, j);
    //         if (value[0] != 0.0f || value[1] != 0.0f)
    //         {
    //             qDebug() << "Position (" << i << "," << j << "): Real =" << value[0] << ", Imag =" << value[1];
    //         }
    //     }
    // }

    // 應用遮罩於頻譜
    cv::Mat filteredDFT;
    cv::mulSpectrums(shift_dft, complexIdealLowPass, filteredDFT, 0); // 0 表示不進行共軛

    return filteredDFT;
}

// 計算高斯低通濾波器圖像
cv::Mat SpecificProcess::gaussianLowPassFilter(const cv::Mat &shift_dft, double D0)
{
    // 檢查 shift_dft 是否為複數頻譜且不為空
    if (shift_dft.empty() || shift_dft.channels() != 2)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid FFT shift image.");
        return cv::Mat(); // 返回空的 Mat 表示錯誤
    }

    // 獲取頻譜圖尺寸
    int rows = shift_dft.rows;
    int cols = shift_dft.cols;

    // 建立高斯低通遮罩
    cv::Mat gaussianLowPass(rows, cols, CV_32F);
    cv::Point center(cols / 2, rows / 2); // 頻譜中心

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // 計算每個點到中心的距離
            double distance = cv::norm(cv::Point(j, i) - center);
            gaussianLowPass.at<float>(i, j) = std::exp(-(distance * distance) / (2 * D0 * D0));
        }
    }

    // 將高斯低通遮罩轉換為複數格式（頻譜格式需一致）
    cv::Mat complexGaussianLowPass;
    cv::Mat planes[] = {gaussianLowPass, cv::Mat::zeros(rows, cols, CV_32F)};
    cv::merge(planes, 2, complexGaussianLowPass);

    // 應用遮罩於頻譜
    cv::Mat filteredDFT;
    cv::mulSpectrums(shift_dft, complexGaussianLowPass, filteredDFT, 0); // 0 表示不進行共軛

    return filteredDFT;
}

// 計算巴特沃斯低通濾波器圖像
cv::Mat SpecificProcess::butterworthLowPassFilter(const cv::Mat &shift_dft, double D0, int n)
{
    // 檢查 shift_dft 是否為複數頻譜且不為空
    if (shift_dft.empty() || shift_dft.channels() != 2)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid FFT shift image.");
        return cv::Mat(); // 返回空的 Mat 表示錯誤
    }

    // 獲取頻譜圖尺寸
    int rows = shift_dft.rows;
    int cols = shift_dft.cols;

    // 建立巴特沃斯低通遮罩
    cv::Mat butterworthLowPass(rows, cols, CV_32F);
    cv::Point center(cols / 2, rows / 2); // 頻譜中心

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // 計算每個點到中心的距離
            double distance = cv::norm(cv::Point(j, i) - center);
            butterworthLowPass.at<float>(i, j) = 1.0 / (1.0 + std::pow(distance / D0, 2 * n));
        }
    }

    // 將巴特沃斯低通遮罩轉換為複數格式（頻譜格式需一致）
    cv::Mat complexButterworthLowPass;
    cv::Mat planes[] = {butterworthLowPass, cv::Mat::zeros(rows, cols, CV_32F)};
    cv::merge(planes, 2, complexButterworthLowPass);

    // 應用遮罩於頻譜
    cv::Mat filteredDFT;
    cv::mulSpectrums(shift_dft, complexButterworthLowPass, filteredDFT, 0); // 0 表示不進行共軛

    return filteredDFT;
}

// 計算理想高通濾波器圖像
cv::Mat SpecificProcess::idealHighPassFilter(const cv::Mat &shift_dft, double D0)
{
    // 檢查 shift_dft 是否為複數頻譜且不為空
    if (shift_dft.empty() || shift_dft.channels() != 2)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid FFT shift image.");
        return cv::Mat(); // 返回空的 Mat 表示錯誤
    }

    // 獲取頻譜圖尺寸
    int rows = shift_dft.rows;
    int cols = shift_dft.cols;

    // 建立理想高通遮罩
    cv::Mat idealHighPass(rows, cols, CV_32F);
    cv::Point center(cols / 2, rows / 2); // 頻譜中心

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // 計算每個點到中心的距離
            double distance = cv::norm(cv::Point(j, i) - center);
            idealHighPass.at<float>(i, j) = (distance > D0) ? 1.0f : 0.0f;
        }
    }

    // 將理想高通遮罩轉換為複數格式（頻譜格式需一致）
    cv::Mat complexIdealHighPass;
    cv::Mat planes[] = {idealHighPass, cv::Mat::zeros(rows, cols, CV_32F)};
    cv::merge(planes, 2, complexIdealHighPass);

    // 應用遮罩於頻譜
    cv::Mat filteredDFT;
    cv::mulSpectrums(shift_dft, complexIdealHighPass, filteredDFT, 0); // 0 表示不進行共軛

    return filteredDFT;
}

// 計算高斯高通濾波器圖像
cv::Mat SpecificProcess::gaussianHighPassFilter(const cv::Mat &shift_dft, double D0)
{
    // 檢查 shift_dft 是否為複數頻譜且不為空
    if (shift_dft.empty() || shift_dft.channels() != 2)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid FFT shift image.");
        return cv::Mat(); // 返回空的 Mat 表示錯誤
    }

    // 獲取頻譜圖尺寸
    int rows = shift_dft.rows;
    int cols = shift_dft.cols;

    // 建立高斯高通遮罩
    cv::Mat gaussianHighPass(rows, cols, CV_32F);
    cv::Point center(cols / 2, rows / 2); // 頻譜中心

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // 計算每個點到中心的距離
            double distance = cv::norm(cv::Point(j, i) - center);
            gaussianHighPass.at<float>(i, j) = 1.0 - std::exp(-(distance * distance) / (2 * D0 * D0));
        }
    }

    // 將高斯高通遮罩轉換為複數格式（頻譜格式需一致）
    cv::Mat complexGaussianHighPass;
    cv::Mat planes[] = {gaussianHighPass, cv::Mat::zeros(rows, cols, CV_32F)};
    cv::merge(planes, 2, complexGaussianHighPass);

    // 應用遮罩於頻譜
    cv::Mat filteredDFT;
    cv::mulSpectrums(shift_dft, complexGaussianHighPass, filteredDFT, 0); // 0 表示不進行共軛

    return filteredDFT;
}

// 計算巴特沃斯高通濾波器圖像
cv::Mat SpecificProcess::butterworthHighPassFilter(const cv::Mat &shift_dft, double D0, int n)
{
    // 檢查 shift_dft 是否為複數頻譜且不為空
    if (shift_dft.empty() || shift_dft.channels() != 2)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid FFT shift image.");
        return cv::Mat(); // 返回空的 Mat 表示錯誤
    }

    // 獲取頻譜圖尺寸
    int rows = shift_dft.rows;
    int cols = shift_dft.cols;

    // 建立巴特沃斯高通遮罩
    cv::Mat butterworthHighPass(rows, cols, CV_32F);
    cv::Point center(cols / 2, rows / 2); // 頻譜中心

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // 計算每個點到中心的距離
            double distance = cv::norm(cv::Point(j, i) - center);
            butterworthHighPass.at<float>(i, j) = 1.0 / (1.0 + std::pow(D0 / distance, 2 * n));
        }
    }

    // 將巴特沃斯高通遮罩轉換為複數格式（頻譜格式需一致）
    cv::Mat complexButterworthHighPass;
    cv::Mat planes[] = {butterworthHighPass, cv::Mat::zeros(rows, cols, CV_32F)};
    cv::merge(planes, 2, complexButterworthHighPass);

    // 應用遮罩於頻譜
    cv::Mat filteredDFT;
    cv::mulSpectrums(shift_dft, complexButterworthHighPass, filteredDFT, 0); // 0 表示不進行共軛

    return filteredDFT;
}

// 同態濾波器
std::unique_ptr<QImage> SpecificProcess::homomorphicFilter(std::unique_ptr<QImage> &image, double gamma_H, double gamma_L, double D0, double c)
{
    if (!image)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid image pointer.");
        return nullptr;
    }

    // 獲取圖像的寬度和高度
    int width = image->width();
    int height = image->height();

    // 將 QImage 轉換為灰度圖像
    auto grayImage = image->convertToFormat(QImage::Format_Grayscale8);

    // 將灰度圖像轉換為 OpenCV 的 Mat 對象
    cv::Mat grayMat(height, width, CV_8UC1, grayImage.bits(), grayImage.bytesPerLine());

    // 將圖像轉換為浮點型
    cv::Mat floatMat;
    grayMat.convertTo(floatMat, CV_32F);

    // 對數變換
    cv::Mat logImage;
    cv::log(floatMat + 1, logImage); // 加1以避免 log(0)

    // 執行傅立葉變換
    cv::Mat complexMat;
    cv::dft(logImage, complexMat, cv::DFT_COMPLEX_OUTPUT);

    // 將頻譜圖中心化
    int cx = complexMat.cols / 2;
    int cy = complexMat.rows / 2;

    cv::Mat q0(complexMat, cv::Rect(0, 0, cx, cy));   // 左上
    cv::Mat q1(complexMat, cv::Rect(cx, 0, cx, cy));  // 右上
    cv::Mat q2(complexMat, cv::Rect(0, cy, cx, cy));  // 左下
    cv::Mat q3(complexMat, cv::Rect(cx, cy, cx, cy)); // 右下

    cv::Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    // 構建高通濾波器
    cv::Mat filter = cv::Mat(complexMat.size(), CV_32F);

    for (int i = 0; i < complexMat.rows; ++i)
    {
        for (int j = 0; j < complexMat.cols; ++j)
        {
            double distance = std::sqrt(std::pow(i - cy, 2) + std::pow(j - cx, 2));
            filter.at<float>(i, j) = (gamma_H - gamma_L) * (1 - std::exp(-c * ((distance * distance) / (2 * D0 * D0)))) + gamma_L;
        }
    }

    // 應用高通濾波器
    cv::Mat planes[2];
    cv::split(complexMat, planes);

    planes[0] = planes[0].mul(filter);
    planes[1] = planes[1].mul(filter);

    cv::merge(planes, 2, complexMat);

    // 將頻譜圖反中心化 (inverse shift)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    // 執行逆傅立葉變換
    cv::Mat idftImage;
    cv::idft(complexMat, idftImage, cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);

    // 指數變換以恢復亮度
    cv::Mat expImage;
    cv::exp(idftImage, expImage);

    // 將結果轉換回 8 位無符號整數型
    expImage.convertTo(expImage, CV_8U);

    // 將結果轉換為 QImage
    auto resultImage = std::make_unique<QImage>(width, height, QImage::Format_RGB32);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int gray = expImage.at<uchar>(y, x);
            resultImage->setPixel(x, y, qRgb(gray, gray, gray));
        }
    }

    return resultImage;
}

// 頻域不變濾波器(測試用)
cv::Mat SpecificProcess::unitImpulseResponse(const cv::Mat &shift_dft, double T)
{
    // 創建一個與 shift_dft 相同大小的矩陣，類型為 CV_32FC2
    cv::Mat impulseResponse(shift_dft.size(), CV_32FC2);

    // 獲取圖像的尺寸
    int rows = impulseResponse.rows;
    int cols = impulseResponse.cols;

    // 遍歷每個頻域點，設置為 (T, 0)
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            impulseResponse.at<cv::Vec2f>(i, j) = cv::Vec2f(T, 0);
        }
    }

    // 確保合併後的類型一致
    cv::Mat filteredDFT;
    cv::mulSpectrums(shift_dft, impulseResponse, filteredDFT, 0); // 0 表示不進行共軛

    return filteredDFT;
}

// 直線動態模糊
cv::Mat SpecificProcess::motionBlurred(const cv::Mat &shift_dft, double a, double b, double T)
{
    // 檢查 shift_dft 是否為複數頻譜且不為空
    if (shift_dft.empty() || shift_dft.channels() != 2 || shift_dft.type() != CV_32FC2)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid FFT shift image.");
        return cv::Mat(); // 返回空的 Mat 表示錯誤
    }

    int rows = shift_dft.rows;
    int cols = shift_dft.cols;

    // 使用 CV_32FC2 初始化複數矩陣
    cv::Mat motionBlur(rows, cols, CV_32FC2);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // 將 u 和 v 移到頻譜的中心
            double u = j - cols / 2; // 頻率 u
            double v = i - rows / 2; // 頻率 v
            double pi = CV_PI;

            double denominator = pi * (u * a + v * b);
            std::complex<float> value;

            // 運動模糊衰退運算
            if (denominator != 0)
            {
                value = std::complex<float>(T * sin(denominator) / denominator, 0) * std::exp(std::complex<float>(0, -pi * (u * a + v * b)));
            }
            else
            {
                value = std::complex<float>(T, 0);
            }
            // qDebug() << "T:" << T << ",  a:" << a << ",  b:" << b << ", denominator:" << denominator;

            motionBlur.at<std::complex<float>>(i, j) = value;
        }
    }

    // 確保合併後的類型一致
    cv::Mat filteredDFT;
    cv::mulSpectrums(shift_dft, motionBlur, filteredDFT, 0); // 0 表示不進行共軛

    return filteredDFT;
}

// 空間域中加入高斯雜訊
std::unique_ptr<QImage> SpecificProcess::GaussianNoise(std::unique_ptr<QImage> &image, double sigma)

{
    if (!image || image->isNull())
    {
        throw std::runtime_error("Invalid input image");
    }

    // 獲取圖像的寬度和高度
    int width = image->width();
    int height = image->height();

    // 創建一個新的 QImage 來存放加噪後的結果
    auto noisyImage = std::make_unique<QImage>(width, height, QImage::Format_RGB32);

    // 初始化隨機數生成器
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, sigma);

    // 遍歷每個像素並加入高斯雜訊
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            QRgb pixel = image->pixel(x, y);

            int red = qRed(pixel) + static_cast<int>(distribution(generator));
            int green = qGreen(pixel) + static_cast<int>(distribution(generator));
            int blue = qBlue(pixel) + static_cast<int>(distribution(generator));

            // 確保像素值在有效範圍內
            red = std::clamp(red, 0, 255);
            green = std::clamp(green, 0, 255);
            blue = std::clamp(blue, 0, 255);

            noisyImage->setPixel(x, y, qRgb(red, green, blue));
        }
    }

    return noisyImage;
}

// 運動模糊衰退逆濾波器
cv::Mat SpecificProcess::inverseFilter(const cv::Mat &shift_dft_noise, double a, double b, double T, double k)
{
    // 檢查 shift_dft_noise 是否為複數頻譜且不為空
    if (shift_dft_noise.empty() || shift_dft_noise.channels() != 2 || shift_dft_noise.type() != CV_32FC2)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid FFT shift image.");
        return cv::Mat(); // 返回空的 Mat 表示錯誤
    }

    int rows = shift_dft_noise.rows;
    int cols = shift_dft_noise.cols;

    // 使用 CV_32FC2 初始化複數矩陣
    cv::Mat restoredDFT(rows, cols, CV_32FC2);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // 將 u 和 v 移到頻譜的中心
            double u = j - cols / 2; // 頻率 u
            double v = i - rows / 2; // 頻率 v
            double pi = CV_PI;

            // 計算 denominator
            double denominator = pi * (u * a + v * b);
            std::complex<float> H, inverseValue;

            // 運動模糊衰退運算
            if (denominator != 0)
            {
                H = std::complex<float>(T * sin(denominator) / denominator, 0) * std::exp(std::complex<float>(0, -pi * (u * a + v * b)));
                H += std::complex<float>(k, 0);
            }
            else
            {
                H = std::complex<float>(T, 0);
            }
            // qDebug() << "T:" << T << ",  a:" << a << ",  b:" << b << ", denominator:" << denominator;
            inverseValue = std::complex<float>(1, 0) / H;
            restoredDFT.at<std::complex<float>>(i, j) = inverseValue;
        }
    }

    // 確保合併後的類型一致
    cv::Mat filteredDFT;
    cv::mulSpectrums(shift_dft_noise, restoredDFT, filteredDFT, 0); // 0 表示不進行共軛

    return filteredDFT;
}

// 運動模糊衰退 Wiener 濾波器
cv::Mat SpecificProcess::wienerFilter(const cv::Mat &shift_dft_noise, double a, double b, double T, double k)

{
    // 檢查 shift_dft_noise 是否為複數頻譜且不為空
    if (shift_dft_noise.empty() || shift_dft_noise.channels() != 2 || shift_dft_noise.type() != CV_32FC2)
    {
        QMessageBox::critical(nullptr, "Error", "Invalid FFT shift image.");
        return cv::Mat(); // 返回空的 Mat 表示錯誤
    }

    int rows = shift_dft_noise.rows;
    int cols = shift_dft_noise.cols;

    // 使用 CV_32FC2 初始化複數矩陣
    cv::Mat restoredDFT(rows, cols, CV_32FC2);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // 將 u 和 v 移到頻譜的中心
            double u = j - cols / 2; // 頻率 u
            double v = i - rows / 2; // 頻率 v
            double pi = CV_PI;

            // 計算 denominator
            double denominator = pi * (u * a + v * b);
            std::complex<float> H, inverseValue;

            // 運動模糊衰退運算
            if (denominator != 0)
            {
                H = std::complex<float>(T * sin(denominator) / denominator, 0) * std::exp(std::complex<float>(0, -pi * (u * a + v * b)));
            }
            else
            {
                H = std::complex<float>(T, 0);
            }
            // qDebug() << "T:" << T << ",  a:" << a << ",  b:" << b << ", denominator:" << denominator;

            // 計算 Wiener 濾波器
            inverseValue = std::complex<float>(std::norm(H) / (std::norm(H) + k), 0) / H;
            restoredDFT.at<std::complex<float>>(i, j) = inverseValue;
        }
    }

    // 確保合併後的類型一致
    cv::Mat filteredDFT;
    cv::mulSpectrums(shift_dft_noise, restoredDFT, filteredDFT, 0); // 0 表示不進行共軛

    return filteredDFT;
}

// 計算空間域圖像差異
std::unique_ptr<QImage> SpecificProcess::diffImage(const QImage &image1, const QImage &image2)
{
    if (image1.isNull() || image2.isNull() || image1.size() != image2.size())
    {
        throw std::runtime_error("Invalid input images");
    }

    // 獲取圖像的寬度和高度
    int width = image1.width();
    int height = image1.height();

    // 創建一個新的 QImage 來存放差異圖像
    auto diffImage = std::make_unique<QImage>(width, height, QImage::Format_RGB32);

    // 遍歷每個像素並計算差異
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            QRgb pixel1 = image1.pixel(x, y);
            QRgb pixel2 = image2.pixel(x, y);

            int red = std::abs(qRed(pixel1) - qRed(pixel2));
            int green = std::abs(qGreen(pixel1) - qGreen(pixel2));
            int blue = std::abs(qBlue(pixel1) - qBlue(pixel2));

            diffImage->setPixel(x, y, qRgb(red, green, blue));
        }
    }

    return diffImage;
}
