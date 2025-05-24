import cv2
import numpy

name = "Vagner"

fore = cv2.imread("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\{}.png".format(name))[ : , : , 2 : : -1]
img = numpy.ones(fore.shape[ : 2] + (4,), numpy.uint8) * 255
img[ : , : , : 3] = fore

for i in range(img.shape[0]):
    for j in range(img.shape[1]):
        if all(img[i, j] == 255):
            img[i, j] = 0

cv2.imshow("img", cv2.cvtColor(img, cv2.COLOR_RGBA2BGRA))
cv2.waitKey(0)

cv2.imwrite("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\{}.bmp".format(name), cv2.cvtColor(img, cv2.COLOR_RGBA2BGRA))
with open("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\src\\{}.mem".format(name), "wb") as mem:
    height, width, *_ = img.shape
    mem.write(width.to_bytes(4, "little") + height.to_bytes(4, "little"))
    mem.write(img.tobytes())
