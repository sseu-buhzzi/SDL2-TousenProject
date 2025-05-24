import cv2
import numpy

img = cv2.imread("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\DeanPoint.bmp")
for i in range(img.shape[0]):
    for j in range(img.shape[1]):
        img[i, j, 0] = 255

cv2.imshow("img", img)
cv2.waitKey(0)
cv2.imwrite("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\DeanPoint.bmp", img)
