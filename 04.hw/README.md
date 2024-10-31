
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

## 【結果圖片】
<div style="text-align: center;">
  <img src="readme_figure/image.png" alt="alt text" style="max-width: 100%;">
  <img src="readme_figure/image-1.png" alt="alt text" style="max-width: 100%;">
</div>

## 【結果討論】
經過FFT與IFFT變換中可能由於一些精度的誤差而產生一些雜訊，但是基本上能夠做到完全還原影像。  
FFT轉換時間約與圖像尺寸成正比，也就是多圖片越大，轉換時間需要越久。  

<br/>

# Part 2. 
Design a program for highpass and lowpass filtering of images using (1) Ideal filter; (2) Butterworth filter; (3) Gaussian filter. Test your program with the following image and discuss the effect of cut-off frequency on the processed image.

使用（1）理想濾波器設計影像高通和低通濾波程式； (2)巴特沃斯濾波器； (3)高斯濾波器。使用下圖測試您的程式並討論截止頻率對處理影像的影響。

## 【結果圖片】
<div style="text-align: center;">
  <img src="readme_figure/image-2.png" alt="D20" style="max-width: 100%;">
  <img src="readme_figure/image-3.png" alt="D40" style="max-width: 100%;">
</div>

## 【結果討論】
當截止頻率從20調整為40，代表保留了更多低頻的資訊，因此可以觀察到低通後的結果品質都有明顯提升。  
而高通因為相當於1-低通，所以相當於當截止頻率提升，會過濾掉更多高頻資訊，導致影像愈發模糊。  

<br/>

# Part 3. 
Design an image processing program for homomorphic filtering as described in Section 4.9 in our textbook. Your program should have a user-friendly interface allowing flexible adjustment of three parameters $\gamma_H$, $\gamma_L$, and $D_0$ defined in equation (4-147). Discuss the effect of these parameters on the processed image in your report.

設計一個用於同態濾波的影像處理程序，如我們教科書第 4.9 節所述。您的程式應該有一個使用者友善的介面，允許靈活調整方程式（4-147）中定義的三個參數$\gamma_H$, $\gamma_L$, 和 $D_0$。討論這些參數對報告中處理後的影像的影響。

<!-- <br/> -->

## 【結果圖片】
<div style="text-align: center;">
  <img src="readme_figure/image-4.png" alt="alt text" style="max-width: 100%;">
  <img src="readme_figure/image-5.png" alt="H" style="max-width: 100%;">
  <img src="readme_figure/image-6.png" alt="L" style="max-width: 100%;">
  <img src="readme_figure/image-7.png" alt="C" style="max-width: 100%;">
</div>

## 【結果討論】
- $\gamma_H$: 可以理解為高頻增益。增大 $\gamma_H$ 的值會強化影像的高頻成分，使邊緣和紋理更加銳利，帶來更清晰的效果；減少 $\gamma_H$ 則會使高頻訊號受到壓制，邊緣變模糊。

- $\gamma_L$: 可以理解為低頻增益。增大 $\gamma_L$ 會增強影像的低頻成分，使背景變亮；減少 $\gamma_L$ 則會壓制低頻，使背景變暗，從而達到對比增強的效果。

- $D_0$: 控制高頻和低頻成分的分界點，即濾波器作用的範圍。較大的 $D_0$ 會使更多中頻和高頻通過濾波器，增加影像的清晰度和細節；較小的 $D_0$ 會保留更多低頻分量，使影像較平滑。

- $c$: c 決定了濾波器的過渡速率，即從低頻到高頻的增益轉換幅度。它影響了濾波器響應曲線的「平滑度」或「銳利度」。較大的 𝑐值適合於增強高頻細節和銳利度，強調細微紋理和邊緣；而較小的𝑐值則適合於平滑過渡，減少過度增強帶來的噪聲，適合於低對比度的影像。

# Part 4. 
Design an image processing program to create a motion blurred image as shown in Figure 5.26b. Then apply a 2-D frequency domain inverse filter and Wiener filter to this blurred image, respectively. Comment on the performance of the two filters for removing motion blur. To compare the performance of the two filters, you may compare the processed images with the original unblurred image by image subtraction.

Add a zero-mean white Gaussian noise to the motion blurred image with variance σ = 20. Restore the image with inverse filter and Wiener filter, respectively. Comment on the simultaneous noise removal and de-blurring abilities of the two filters. Also discuss the effect of noise level on the result of image restoration in your report.

設計一個影像處理程序來創建運動模糊影像，如圖 5.26b 所示。然後分別對此模糊影像應用二維頻域逆濾波器和維納濾波器。評論兩個濾波器消除運動模糊的性能。要比較兩個濾波器的效能，您可以透過影像減法將處理後的影像與原始未模糊影像進行比較。

將零均值高斯白噪聲加到方差 σ = 20 的運動模糊影像中。評論兩個濾波器同時去除雜訊和去模糊的能力。在報告中也可以討論雜訊程度對影像恢復結果的影響。

## 【結果圖片】
<div style="text-align: center;">
  <img src="readme_figure/image-10.png" alt="alt text" style="max-width: 100%;">
  <img src="readme_figure/image-8.png" alt="alt text" style="max-width: 100%;">
  <img src="readme_figure/image-9.png" alt="alt text" style="max-width: 100%;">
</div>

## 【結果討論】
1. **逆濾波公式**
    假設一個模糊影像模型為：
    $$
    G(u, v) = H(u, v) \cdot F(u, v) + N(u, v)
    $$
    直接的逆濾波不考慮噪聲，因此公式為：
    $$
    \hat{F}(u, v) = \frac{G(u, v)}{H(u, v)}
    $$
    然而，當 $H(u, v)$ 在某些頻率上接近零時，分母會趨近於零，使得結果放大噪聲，導致還原影像中出現大量的噪聲放大。需要手動將$H(u, v)$加上一個實數常數(inverse_k)，避免噪聲被無限放大，導致無法還原影像。  

<br/>

2. **Wiener 濾波公式**
    Wiener 濾波器則根據 **最小均方誤差**（MMSE）的原理，對頻域進行調整。其公式為：
    $$
    \hat{F}(u, v) = \frac{H^*(u, v)}{|H(u, v)|^2 + \frac{S_N(u, v)}{S_F(u, v)}} G(u, v)
    $$
    這個公式中的項目 $\frac{S_N(u, v)}{S_F(u, v)}$ 是 **信噪比（SNR）的倒數**(wiener_k)。  
    Wiener 濾波器會根據頻率成分的信噪比動態調整濾波強度，高信噪比頻率區域更接近逆濾波，低信噪比區域則減少增益，這樣的自適應特性讓濾波效果更加穩定。

3. **調整參數的影響** 
   - **a, b**: 當 a 或 b 增大時，模糊的方向與範圍會相應增加，模糊效果更為明顯且拖尾變長。當 a 和 b 設為 0 時，表示無運動模糊，濾波器將不進行任何模糊的平滑運算。
   - **T**: 當 T 增大時，模糊拖尾的強度也會增強，頻域中會出現更明顯的模糊濾波效果。當 T 等於 1 時，影像的頻譜特徵將被完全保留，而當 T 小於 1 時，模糊效果會減弱，頻譜細節可能會顯得模糊或失真。若 T 為非常小的值（接近於 0），頻譜的變化將不明顯，模糊的效果也會相應減弱。

4. **總結**: 從數學角度來看，Wiener 濾波器在逆濾波的基礎上，加入了對噪聲的考慮，使其在低信噪比的區域抑制增益，從而達到減少噪聲放大和避免不穩定性的效果。因此，Wiener 濾波器通常比直接逆濾波更能還原影像且更具穩定性。