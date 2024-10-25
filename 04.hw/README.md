
<!-- title: 影處HW4 -->
---
Title: 影處HW4  
Student ID: R12631070  
Name: 林育新  
---

<!-- ---
Header:
  Left: 影處HW4
  Right: R12631070 林育新
Footer:
  Center: 
--- -->

# Part 1. 
Design a computer program to perform Fourier transform of an image using FFT. You may use FFT function source code available on the NTU COOL course website or FFT function of OpenCV library. The image spectrum obtained after Fourier transform could be further processed using the following method to achieve better display. Beside image spectrum, also display the image phase angle with your program. 

FMIN = LOG(1+ABS(Fmin)) Fmin is the minimum value of the F(u,v) spectrum
FMAX = LOG(1+ABS(Fmax)) Fmax is the maximum value of the F(u,v) spectrum
YNEW(u,v) = G*[ LOG(1+ABS(F(u,v))) - FMIN ]/[ FMAX - FMIN ]

where G is the highest gray level in an image. (G = 255 for most cases)

Is there any difference between the original image and the processed image after forward Fourier transform and inverse Fourier transform using your program? Examine and discuss your result.

Make an analysis of the effect of image size on the processing time of your Fourier transform program.

設計一個電腦程式以使用 FFT 執行影像的傅立葉變換。您可以使用 NTU COOL 課程網站上提供的 FFT 函數原始碼或 OpenCV 函式庫的 FFT 函數。傅立葉變換後所得到的影像頻譜可以採用以下方法進一步處理，以達到更好的顯示效果。除了影像光譜之外，還可以使用程式顯示影像相位角。
 
FMIN = LOG(1+ABS(Fmin)) Fmin 是 F(u,v) 譜的最小值
FMAX = LOG(1+ABS(Fmax)) Fmax 是 F(u,v) 譜的最大值
YNEW(u,v) = G*[ LOG(1+ABS(F(u,v))) - FMIN ]/[ FMAX - FMIN ]

其中 G 是影像中的最高灰階。 （大多數情況下 G = 255）

使用你們的程式進行正傅立葉變換和逆傅立葉變換後，原始影像和處理後的影像有什麼不同嗎？檢查並討論你的結果。

分析影像尺寸對傅立葉變換程序處理時間的影響。

## 【算法實現與解釋】


## 【結果圖片】


## 【結果討論】


<br/>

# Part 2. 
Design a program for highpass and lowpass filtering of images using (1) Ideal filter; (2) Butterworth filter; (3) Gaussian filter. Test your program with the following image and discuss the effect of cut-off frequency on the processed image.

使用（1）理想濾波器設計影像高通和低通濾波程式； (2)巴特沃斯濾波器； (3)高斯濾波器。使用下圖測試您的程式並討論截止頻率對處理影像的影響。

## 【算法實現與解釋】


## 【結果圖片】
<table>
  <tr>
    <th></th> <!-- 空白單元格，對應表頭 -->
    <th>kernel size 3</th>
    <th>kernel size 21</th>
  </tr>
  <tr>
    <td>median</td> <!-- 新增row name -->
    <td><img src="readme_figure/image-2.png" alt="k3 median"></td>
    <td><img src="readme_figure/image-6.png" alt="k21 median"></td>
  </tr>
  <tr>
    <td>mean</td> <!-- 新增row name -->
    <td><img src="readme_figure/image-3.png" alt="k3 mean"></td>
    <td><img src="readme_figure/image-7.png" alt="k21 mean"></td>
  </tr>
  <tr>
    <td>max</td> <!-- 新增row name -->
    <td><img src="readme_figure/image-4.png" alt="k3 max"></td>
    <td><img src="readme_figure/image-8.png" alt="k21 max"></td>
  </tr>
  <tr>
    <td>min</td> <!-- 新增row name -->
    <td><img src="readme_figure/image-5.png" alt="k3 min"></td>
    <td><img src="readme_figure/image-9.png" alt="k21 min"></td>
  </tr>
</table>

## 【結果討論】


<br/>

# Part 3. 
Design an image processing program for homomorphic filtering as described in Section 4.9 in our textbook. Your program should have a user-friendly interface allowing flexible adjustment of three parameters $\gamma_H$, $\gamma_L$, and $D_0$ defined in equation (4-147). Discuss the effect of these parameters on the processed image in your report.

設計一個用於同態濾波的影像處理程序，如我們教科書第 4.9 節所述。您的程式應該有一個使用者友善的介面，允許靈活調整方程式（4-147）中定義的三個參數$\gamma_H$, $\gamma_L$, 和 $D_0$。討論這些參數對報告中處理後的影像的影響。

<!-- <br/> -->

## 【算法實現與解釋】
- 
- 


## 【結果圖片】


## 【結果討論】


# Part 4. 
Design an image processing program to create a motion blurred image as shown in Figure 5.26b. Then apply a 2-D frequency domain inverse filter and Wiener filter to this blurred image, respectively. Comment on the performance of the two filters for removing motion blur. To compare the performance of the two filters, you may compare the processed images with the original unblurred image by image subtraction.

Add a zero-mean white Gaussian noise to the motion blurred image with variance σ = 20. Restore the image with inverse filter and Wiener filter, respectively. Comment on the simultaneous noise removal and de-blurring abilities of the two filters. Also discuss the effect of noise level on the result of image restoration in your report.

設計一個影像處理程序來創建運動模糊影像，如圖 5.26b 所示。然後分別對此模糊影像應用二維頻域逆濾波器和維納濾波器。評論兩個濾波器消除運動模糊的性能。要比較兩個濾波器的效能，您可以透過影像減法將處理後的影像與原始未模糊影像進行比較。

將零均值高斯白噪聲加到方差 σ = 20 的運動模糊影像中。評論兩個濾波器同時去除雜訊和去模糊的能力。在報告中也可以討論雜訊程度對影像恢復結果的影響。

## 【算法實現與解釋】



## 【結果圖片】


## 【結果討論】

- 