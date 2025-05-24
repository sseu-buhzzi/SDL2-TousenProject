import cv2
import numpy

img = cv2.imread("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\Sakura_0.png")

for i in range(img.shape[0]):
    for j in range(img.shape[1]):
        if any(img[i, j] < 128) and img[i, j, 0] > img[i, j, 2]:
            img[i, j] = 0

img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

cv2.namedWindow("img", cv2.WINDOW_FREERATIO)
cv2.imshow("img", img)
cv2.waitKey(0)
cv2.imwrite("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\Sakura_2.bmp", img)
