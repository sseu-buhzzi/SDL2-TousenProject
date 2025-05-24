import cv2
import numpy

img = cv2.imread("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\Logo_1.bmp")

for i in range(img.shape[0]):
    for j in range(img.shape[1]):
        if all(img[i, j, : 3] == 64):
            img[i, j, : 3] = int(128 - (abs(i - 511.5) / 512) * 64)

cv2.namedWindow("img", cv2.WINDOW_FREERATIO)
cv2.imshow("img", img)
cv2.waitKey(0)
cv2.imwrite("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\Logo.bmp", img)