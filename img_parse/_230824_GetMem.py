import cv2
import numpy

img = cv2.imread("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\src\\Prigozin.png", cv2.IMREAD_UNCHANGED)[ : , : , : : 1]
img = cv2.cvtColor(img, cv2.COLOR_BGRA2RGBA)
with open("D:\\Sseu\\Tryingssiuh\\Ssianxmuh\\_230515_STGs\\_230824_STG\\Prigozin.mem", "wb") as mem:
    height, width, *_ = img.shape
    mem.write(width.to_bytes(4, "little") + height.to_bytes(4, "little"))
    mem.write(img.tobytes())
