import numpy as np

def bilinear_interpolation(input_matrix, out_height, out_width):
    """
    對輸入矩陣進行雙線性插值，調整到指定大小
    
    參數:
    input_matrix: numpy陣列，輸入矩陣
    out_height: 輸出矩陣的高度
    out_width: 輸出矩陣的寬度
    
    返回:
    numpy陣列，插值後的矩陣
    """
    # 獲取輸入矩陣的尺寸
    in_height, in_width = input_matrix.shape
    
    # 創建輸出矩陣的座標網格
    x = np.linspace(0, in_width - 1, out_width)
    y = np.linspace(0, in_height - 1, out_height)
    
    # 創建網格點
    x_coords, y_coords = np.meshgrid(x, y)
    
    # 計算相鄰的整數座標
    x0 = np.floor(x_coords).astype(int)
    x1 = np.minimum(x0 + 1, in_width - 1)
    y0 = np.floor(y_coords).astype(int)
    y1 = np.minimum(y0 + 1, in_height - 1)
    
    # 計算權重
    x_weight = x_coords - x0
    y_weight = y_coords - y0
    
    # 獲取四個角點的值
    q11 = input_matrix[y0, x0]
    q21 = input_matrix[y0, x1]
    q12 = input_matrix[y1, x0]
    q22 = input_matrix[y1, x1]
    
    # 在x方向進行插值
    r1 = q11 * (1 - x_weight) + q21 * x_weight
    r2 = q12 * (1 - x_weight) + q22 * x_weight
    
    # 在y方向進行插值
    result = r1 * (1 - y_weight) + r2 * y_weight
    
    return result

def main():
    # 例子 1: 3x3 矩陣插值到 4x4
    matrix_3x3 = np.array([[1, 2, 3],
                          [4, 5, 6],
                          [7, 8, 9]])
    result_4x4 = bilinear_interpolation(matrix_3x3, 4, 4)
    result_5x5 = bilinear_interpolation(matrix_3x3, 5, 5)
    print("Example 1:")
    print("Input 3x3 Matrix:")
    print(matrix_3x3)
    print("\nOutput 4x4 Matrix:")
    print(result_4x4)
    print("\nOutput 5x5 Matrix:")
    print(result_5x5)

    # 例子 2: 2x2 矩陣插值到 5x5
    matrix_2x2 = np.array([[10, 20],
                          [30, 40]])
    result_5x5 = bilinear_interpolation(matrix_2x2, 5, 5)
    print("\nExample 2:")
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
    print("\nExample 3:")
    print("\nInput 4x4 Matrix:")
    print(matrix_4x4)
    print("\nOutput 3x3 Matrix:")
    print(result_3x3)

    # 例子 4: 2x2 矩陣插值到 3x3
    matrix_2x2 = np.array([[10, 20],
                          [40, 80]])
    result_3x3 = bilinear_interpolation(matrix_2x2, 3, 3)
    print("\nExample 4:")
    print("\nInput 2x2 Matrix:")
    print(matrix_2x2)
    print("\nOutput 3x3 Matrix:")
    print(result_3x3)

if __name__ == "__main__":
    main()