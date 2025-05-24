import cv2
import math
import numpy

name = "JudgePoint"

# fore = cv2.imread("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\{}.bmp".format(name))[ : , : , 2 : : -1]
# img = numpy.ones(fore.shape[ : 2] + (4,), numpy.uint8) * 255
# img[ : , : , : 3] = fore
img = numpy.zeros((256, 256, 4), numpy.uint8)

for i in range(img.shape[0]):
    for j in range(img.shape[1]):
        dist = math.sqrt((i - 127.5) ** 2 + (j - 127.5) ** 2)
        if dist < 96:
            img[i, j] = [255, 255, 255, 255 - dist * 2]
        elif dist < 128:
            img[i, j] = [128, 0, 0, 255]

cv2.imshow("img", cv2.cvtColor(img, cv2.COLOR_RGBA2BGRA))
cv2.waitKey(0)

with open("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\src\\{}.mem".format(name), "wb") as mem:
    height, width, *_ = img.shape
    mem.write(width.to_bytes(4, "little") + height.to_bytes(4, "little"))
    mem.write(img.tobytes())
