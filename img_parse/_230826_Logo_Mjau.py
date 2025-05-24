import cv2

img = cv2.imread("D:\Sseu\Tryingssiuh\Ssianxmuh\_230515_STGs\_230824_STG\TEST\Logo.bmp")
for i in range(img.shape[0]):
    for j in range(img.shape[1]):
        try:
            # if any(img[i, j]) and (not any(img[i - 1, j]) or not any(img[i + 1, j]) or not any(img[i, j - 1]) or not any(img[i, j + 1])):
            if any(img[i, j]) and not all(img[i, j] == 255):
                img[i, j] = 0, 0, 255
        except IndexError:
            pass
cv2.imshow("img", img)
cv2.waitKey(0)
cv2.imwrite("D:\Sseu\Tryingssiuh\Ssianxmuh\_230515_STGs\_230824_STG\TEST\Logo.bmp", img)
