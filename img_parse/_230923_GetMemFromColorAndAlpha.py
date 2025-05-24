import cv2
import numpy
import sys

name = "HealBar" if len(sys.argv) < 2 else sys.argv[1]

color = cv2.imread("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\{}_color.bmp".format(name))[ : , : , : 3]
alpha = cv2.imread("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\{}_alpha.bmp".format(name))[ : , : , 0]

img = numpy.zeros(color.shape[ : 2] + (4,), numpy.uint8)
img[ : , : , : 3] = color
img[ : , : , 3] = alpha

cv2.imshow("img", img)
cv2.waitKey(0)

cv2.imwrite("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\{}.png".format(name), img)
with open("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\src\\{}.mem".format(name), "wb") as mem:
    height, width, *_ = img.shape
    data = cv2.cvtColor(img, cv2.COLOR_BGRA2RGBA).tobytes()
    mem.write(width.to_bytes(4, "little") + height.to_bytes(4, "little") + data)
