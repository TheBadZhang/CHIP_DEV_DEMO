import cv2
import matplotlib.pyplot as plt
import numpy as np
import Dither
import serial

ser = serial.Serial("COM6", 1152000, timeout=1)
# capture = cv2.VideoCapture(0)
# capture = cv2.VideoCapture("./video2.mp4")
capture = cv2.VideoCapture("./bad_apple.mp4")
while True:
	ret, frame = capture.read()
	frame = cv2.resize(frame,(128,64))
	frame = cv2.flip(frame,1)   #镜像操作height,width = img.shape
	gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	# img = cv2.
	# print(frame.shape)
	dst = Dither.dither(gray, 'simple2D', resize=False)
	cv2.imshow('frame', dst)

	data = []
	for i in range(0,8):
		for j in range(0,128):
			str1 = ""
			for k in range(0,8):
				str1 = str(1-int(dst[i*8+k][j])) + str1
			nn = int(str1,2)
			data.append(nn)
	ser.write(data)

	key = cv2.waitKey(16)
	if key  == ord('q'):  #判断是哪一个键按下
		break
cv2.destroyAllWindows()