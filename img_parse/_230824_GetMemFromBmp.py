import cv2
import numpy

name = "LogoSseu"

fore = cv2.imread("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\TEST\\{}.bmp".format(name))[ : , : , 2 : : -1]
img = numpy.ones(fore.shape[ : 2] + (4,), numpy.uint8) * 255
img[ : , : , : 3] = fore
img = img.astype(numpy.uint8)

for i in range(img.shape[0]):
    for j in range(img.shape[1]):
        if not any(img[i, j, : 3]):
            img[i, j] = 0

cv2.imshow("img", cv2.cvtColor(img, cv2.COLOR_RGBA2BGRA))
cv2.waitKey(0)

with open("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\src\\{}.mem".format(name), "wb") as mem:
    height, width, *_ = img.shape
    data = img.tobytes()
    mem.write(width.to_bytes(4, "little") + height.to_bytes(4, "little"))
    mem.write(data)

if False:
    with open("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\src\\{}.mem".format(name), "rb") as mem:
        width = int.from_bytes(mem.read(4), "little")
        height = int.from_bytes(mem.read(4), "little")
        data = mem.read()
        cv2.imshow("img", cv2.cvtColor(numpy.frombuffer(data, numpy.uint8).reshape((height, width, 4)), cv2.COLOR_RGBA2BGRA))
        cv2.waitKey(0)
