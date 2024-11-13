
<!-- title: 影處HW5 -->
---
Title: 影處HW5  
Student ID: R12631070  
Name: 林育新  
---

# Part 1. 
Design a computer program for color model conversion. Your program should be able to display an image in RGB, CMY, HSI, XYZ, L*a*b*, YUV color planes. Check the following web link for more information about color model conversion.

設計用於顏色模型轉換的電腦程式。您的程式應該能夠以 RGB、CMY、HSI、XYZ、L*a*b*、YUV 色彩平面顯示影像。有關顏色模型轉換的更多信息，請檢查以下 Web 連結。
http://www.cs.rit.edu/~ncs/color/t_convert.html

## 【結果圖片】

| ![alt text](readme_figure/image.png) | ![alt text](readme_figure/image-1.png) |
| :----------------------------------: | :------------------------------------: |

| ![alt text](readme_figure/image-2.png) | ![alt text](readme_figure/image-3.png) |
| :------------------------------------: | :------------------------------------: |

| ![alt text](readme_figure/image-4.png) | ![alt text](readme_figure/image-15.png) |
| :------------------------------------: | :-------------------------------------: |
 

<br/>

# Part 2. 
Develop a program to display a grayscale image in pseudo-color. In your program, you need to design an interface to both display the grayscale and pseudo-color images for comparison. You also need to show the color table (color bar) with its corresponding grayscale.
Design a user-friendly interface for flexible color table creation and multiple color tables should be provided for user selection. You may learn from popular softwares such as Photoshop or ImageJ for their interface to create a color table.

開發一個程式以偽彩色顯示灰階影像。在你的程式中，你需要設計一個介面來同時顯示灰階和偽彩色圖像以進行比較。您還需要顯示色表（色條）及其對應的灰階。
設計一個使用者友善的介面，靈活創建色表，並提供多種色表供使用者選擇。您可以藉由 Photoshop 或 ImageJ 等流行軟體的介面來建立色表。

## 【結果圖片】
| ![alt text](readme_figure/image-5.png) | ![alt text](readme_figure/image-6.png) |
| :------------------------------------: | :------------------------------------: |

| ![alt text](readme_figure/image-7.png) | ![alt text](readme_figure/image-8.png) |
| :------------------------------------: | :------------------------------------: |

<br/>

# Part 3. 
In this assignment, you will practice image segmentation by color clustering, using the k-means algorithm. Your tasks are as follows:
1. Search the internet to study the k-means algorithm.
2. Implement a program for image segmentation based on color clustering approach. You may use OpenCV or MATLAB functions for k-means algorithm or you may develop your own function.
3. Test your program with the accompanied images with various levels of complexity. Compare and discuss color segmentation results using different k values of the k-means algorithm.
4. Compare the color segmentation results using RGB, HSI, and L*a*b* color planes (using k = 2).


在本作業中，您將使用 k 均值演算法透過色彩聚類練習影像分割。你的任務如下： 
1. 上網搜尋k-means演算法。
2. 實作基於顏色聚類方法的影像分割程序。您可以使用 OpenCV 或 MATLAB 函數來實作 k-means 演算法，也可以發展自己的函數。
3. 使用具有不同複雜程度的隨附影像來測試您的程式。比較並討論使用 k-means 演算法的不同 k 值的顏色分割結果。
4. 比較使用 RGB、HSI 和 L*a*b* 色彩平面（使用 k = 2）的顏色分割結果。



<!-- <br/> -->

## 【結果圖片】
| ![alt text](readme_figure/image-9.png) | ![alt text](readme_figure/image-10.png) | ![alt text](readme_figure/image-11.png) |
| :------------------------------------: | :-------------------------------------: | :-------------------------------------: |
|                  K=2                   |                   K=4                   |                   K=8                   |

| ![alt text](readme_figure/image-12.png) | ![alt text](readme_figure/image-13.png) | ![alt text](readme_figure/image-14.png) |
| :-------------------------------------: | :-------------------------------------: | :-------------------------------------: |
|                   K=2                   |                   K=4                   |                   K=8                   |

| ![alt text](readme_figure/image-16.png) | ![alt text](readme_figure/image-17.png) | ![alt text](readme_figure/image-18.png) |
| :-------------------------------------: | :-------------------------------------: | :-------------------------------------: |
|                   K=2                   |                   K=4                   |                   K=8                   |

| ![alt text](readme_figure/image-19.png) | ![alt text](readme_figure/image-20.png) | ![alt text](readme_figure/image-21.png) |
| :-------------------------------------: | :-------------------------------------: | :-------------------------------------: |
|                   K=2                   |                   K=4                   |                   K=8                   |

## 【結果討論】
- 當 K 值較小時，影像會被分割成較大的區塊，能夠清楚地分辨出主要的輪廓和結構。然而，細節部分可能會被忽略。
- 當 K 值較大時，影像會被分割成更多的區塊，能夠捕捉到更多的細節，影像的還原度更高，但可能會導致過度分割。
- 使用 RGB 色彩平面進行分割的結果：保留最多細節，但這也代表分割的效果不佳。
- 使用 HSI 色彩平面進行分割的結果：在K值=2時有最好的分割結果，能夠分割出圖形的輪廓，但無法適當的反應顏色的差異。**產生的結果近似於語意分割 (Semantic Segmentation)**。
- 使用 L*a*b* 色彩平面進行分割的結果：在K值設定較大時有最好的分割結果，能夠較佳的反應出顏色間的差異。**產生的結果近似於實例分割 (Instance Segmentation)**。但在醫學影像這種灰階影像當中，因為顏色變化不明顯，因此很難觀察L*a*b* 後分割的差異。


