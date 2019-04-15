
from skimage.io import imread
from skimage.filters import threshold_otsu
import matplotlib.pyplot as plt
import cv2
from skimage import measure
from skimage.measure import regionprops
import matplotlib.patches as patches
import numpy as np
from skimage.transform import resize
import os
from sklearn.externals import joblib


class Preprocessing:

	def __init__(self) :
		self.greyscale = cv2.imread("6.jpg", 0)
		

		print(self.greyscale.shape)
		cv2.imshow("Grayscale", self.greyscale)
		cv2.waitKey(0)
		self.greyscale = cv2.medianBlur(self.greyscale,1)
		#(thresh, binary_img) = cv2.threshold(greyscale, 128, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)
		binary_img1 = cv2.adaptiveThreshold(self.greyscale, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY,11,2)
		kernel = np.ones((1,1),np.uint8)
		self.binary_img = cv2.erode(binary_img1,kernel,iterations = 1)
		#self.binary_img = cv2.bilateralFilter(binary_img1,9,75,75)
		#binary_img = cv2.adaptiveThreshold(greyscale, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY,11,2)
		cv2.imshow("Binary", self.binary_img)
		cv2.waitKey(0)
		plt.show()

	def getGreyScale(self):
		return self.greyscale

	def getBinaryImage(self):
		return self.binary_img


class Connected:

	def __init__(self, greyscale, binary_img):
		connected = measure.label(binary_img)
		fig, (ax1) = plt.subplots(1)
		ax1.imshow(greyscale, cmap="gray")

		for region in regionprops(connected):
		    if region.area < 100:
			continue
    
		    min_row, min_col, max_row, max_col = region.bbox
		    rectBorder = patches.Rectangle((min_col, min_row), max_col-min_col, max_row-min_row, edgecolor="green", linewidth=2, fill=False)
		    ax1.add_patch(rectBorder)
 
		plt.show()

class ContinueConnected:

	def __init__(self, binary_img, greyscale):
		connected = measure.label(binary_img)
		percentage_plate = (0.1*connected.shape[0], 0.25*connected.shape[0], 0.10*connected.shape[1], 0.50*connected.shape[1])
		h_max, h_min, w_min, w_max = percentage_plate
		coord = []
		self.obj_like_plate = []
		fig, (ax1) = plt.subplots(1)
		ax1.imshow(greyscale, cmap="gray")
		for region in regionprops(connected):
		    if region.area < 50:
			continue
		    min_row, min_col, max_row, max_col = region.bbox
		    region_height = max_row - min_row
		    region_width = max_col - min_col
		    if region_height >= h_max and region_height <= h_min and region_width >= w_min and region_width <= w_max and region_width > region_height:
			self.obj_like_plate.append(binary_img[min_row:max_row, min_col:max_col])
			coord.append((min_row, min_col, max_row, max_col))
			rectBorder = patches.Rectangle((min_col, min_row), max_col-min_col, max_row-min_row, edgecolor="blue", linewidth=2, fill=False)
			ax1.add_patch(rectBorder)
		plt.show()
	
	def plates(self):
		return self.obj_like_plate
	

class Segmentation:

	def __init__(self, obj_like_plate):
		self.licensePlates = []
		self.characters = []
		for i in obj_like_plate:
			self.licensePlates.append(np.invert(i))
		#licensePlates = np.invert(obj_like_plate[1])

	def license(self):
		return self.licensePlates


	def continues(self,licensePlates):
		connected_plate = measure.label(licensePlates)
		fig, ax1 = plt.subplots(1)
		ax1.imshow(licensePlates, cmap="gray")
		percent_char = (0.35*licensePlates.shape[0], 0.60*licensePlates.shape[0], 0.05*licensePlates.shape[1], 0.15*licensePlates.shape[1])
		h_max, h_min, w_min, w_max = percent_char
		counter=0
		self.column_list = []
		for region in regionprops(connected_plate):
		    y0, x0, y1, x1 = region.bbox
		    region_height = y1 - y0
		    region_width = x1 - x0
		    if region_height > h_max and region_height < h_min and region_width > w_min and region_width < w_max:
			bordr = licensePlates[y0:y1, x0:x1]
			rect_border = patches.Rectangle((x0, y0), x1 - x0, y1 - y0, edgecolor="red",
				                        linewidth=2, fill=False)
			ax1.add_patch(rect_border)
			resized_char = resize(bordr, (20, 20))
			self.characters.append(resized_char)     
			self.column_list.append(x0)
		plt.show()

	def segmentation(self):
		return self.characters

	def column(self):
		return self.column_list

class Recognition:

	def __init__(self, characters, column_list):
		directory = os.path.dirname(os.path.realpath(__file__))
		dir_mdls = os.path.join(directory, 'models/svc/svc.pkl')
		model = joblib.load(dir_mdls)
		my_result = []
		for character in characters:
		    character = character.reshape(1, -1);
		    result = model.predict(character)
		    my_result.append(result)
		plate_string = ''
		for eachPredict in my_result:
		    plate_string += eachPredict[0]
		print(plate_string)
		col_list2 = column_list[:]
		column_list.sort()
		myPlate = ''
		for i in column_list:
		    myPlate += plate_string[col_list2.index(i)]
		print(myPlate)

def main():

	pre = Preprocessing()
	greyscale = pre.getGreyScale()
	binary_img = pre.getBinaryImage()
	c1 = Connected(greyscale, binary_img)
	c2 = ContinueConnected(binary_img, greyscale)
	plate = c2.plates()
	seg = Segmentation(plate)
	seg1 = seg.segmentation()
	lic = seg.license()
	for i in lic:
		seg.continues(i)
		col1 = seg.column()
		reg = Recognition(seg1, col1)

main()
