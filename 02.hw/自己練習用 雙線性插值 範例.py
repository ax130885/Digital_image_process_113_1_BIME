import numpy as np

# 雙線性插值公式: f(x,y) = (1-x)(1-y)f(0,0) + x(1-y)f(1,0) + (1-x)yf(0,1) + xyf(1,1)
# 其中f(0,0), f(1,0), f(0,1), f(1,1)為對應原圖中四個相鄰像素的值
# 背法: f(x,y)與前面係數相加等於1; f(x,y)順序為左上, 左下, 右上, 右下; 四個角落固定不變; 邊界相當內插法

def bilinear_interpolation(image, new_height, new_width):
    old_height, old_width = image.shape
    # 計算縮放比例
    x_scale = old_width / new_width
    y_scale = old_height / new_height

    # 創建新的插值矩陣
    scaled_image = np.zeros((new_height, new_width))

    for y in range(new_height):
        for x in range(new_width):
            # 在原圖中對應的座標 (浮點數)
            old_x = x * x_scale
            old_y = y * y_scale

            # 找到對應的四個相鄰像素
            x1 = int(np.floor(old_x))
            y1 = int(np.floor(old_y))
            x2 = min(x1 + 1, old_width - 1)
            y2 = min(y1 + 1, old_height - 1)

            # 計算相對位置
            x_lerp = old_x - x1
            y_lerp = old_y - y1

            # 獲取四個像素的值
            p11 = image[y1, x1]
            p12 = image[y2, x1]
            p21 = image[y1, x2]
            p22 = image[y2, x2]

            # 進行雙線性插值
            scaled_image[y, x] = (1 - x_lerp) * ((1 - y_lerp) * p11 + y_lerp * p12) + \
                                  x_lerp * ((1 - y_lerp) * p21 + y_lerp * p22)

    return scaled_image

# 例子 1: 3x3 矩陣插值到 4x4
matrix_3x3 = np.array([[1, 2, 3],
                        [4, 5, 6],
                        [7, 8, 9]])
result_4x4 = bilinear_interpolation(matrix_3x3, 4, 4)
print("Input 3x3 Matrix:")
print(matrix_3x3)
print("\nOutput 4x4 Matrix:")
print(result_4x4)

# 例子 2: 2x2 矩陣插值到 5x5
matrix_2x2 = np.array([[10, 20],
                       [30, 40]])
result_5x5 = bilinear_interpolation(matrix_2x2, 5, 5)
print("\nInput 2x2 Matrix:")
print(matrix_2x2)
print("\nOutput 5x5 Matrix:")
print(result_5x5)

# 例子 3: 4x4 矩陣插值到 3x3
matrix_4x4 = np.array([[1, 2, 3, 4],
                       [5, 6, 7, 8],
                       [9, 10, 11, 12],
                       [13, 14, 15, 16]])
result_3x3 = bilinear_interpolation(matrix_4x4, 3, 3)
print("\nInput 4x4 Matrix:")
print(matrix_4x4)
print("\nOutput 3x3 Matrix:")
print(result_3x3)
