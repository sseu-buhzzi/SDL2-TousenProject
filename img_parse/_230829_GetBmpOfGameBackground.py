import cv2
import numpy

mask = cv2.imread("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\Sakura_2.bmp")[ : , : 1024]
img = numpy.zeros((768, 1024, 3), numpy.uint8)

div = 64
for i in range(img.shape[0]):
    for j in range(img.shape[1]):
        i_pix = (i % div) * (256 / div)
        j_pix = (j % div) * (256 / div)
        i_pix, j_pix = i, j
        img[i, j] = [i_pix - j_pix * 0.25, i_pix * 0.25 - j_pix, i_pix + j_pix]
        img[i, j] = (img[i, j] * (mask[int(i / img.shape[0] * mask.shape[0]), int(j / img.shape[1] * mask.shape[1])] / 256)).astype(numpy.uint8)

img[img == 0] = 1

cv2.namedWindow("img", cv2.WINDOW_FREERATIO)
cv2.imshow("img", img)
cv2.waitKey(0)
cv2.imwrite("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\GameBackground.bmp", img)
