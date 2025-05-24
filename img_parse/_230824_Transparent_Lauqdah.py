import cv2
import numpy

img = cv2.imread("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\Prigozin_0.bmp")[ : 160, : 128]
back = numpy.ones(img.shape[ : 2] + (4,), numpy.uint8) * 255
back[ : , : , : 3] = img
img = back
for i in range(img.shape[0]):
    for j in range(img.shape[1]):
        if not any(img[i, j, : 3]):
            img[i, j] = 0
cv2.imshow("img", img)
cv2.waitKey(0)
cv2.imwrite("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\Prigozin.png", img)
