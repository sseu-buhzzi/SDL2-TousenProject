import cv2

img = cv2.imread("D:\Sseu\Tryingssiuh\Ssianxmuh\_230515_STGs\_230824_STG\TEST\Logo.bmp")
img[img < 128] = 0
img[img >= 128] = 255
cv2.namedWindow("img", cv2.WINDOW_FREERATIO)
cv2.imshow("img", img)
cv2.waitKey(0)
cv2.imwrite("D:\Sseu\Tryingssiuh\Ssianxmuh\_230515_STGs\_230824_STG\TEST\Logo.bmp", img[ : , : , 0])
