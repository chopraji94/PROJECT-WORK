# -*- coding: utf-8 -*-
"""
Created on Tue Sep 18 12:17:50 2018

@author: HP
"""


import cv2
import glob

images=glob.glob("*.jpg")

for image in images:
    img=cv2.imread(image,1)
    re=cv2.resize(img,(100,100))
    cv2.imshow("Hey",re)
    cv2.waitKey(500)
    cv2.destroyAllWindows()
    cv2.imwrite("resized_"+image,re)
