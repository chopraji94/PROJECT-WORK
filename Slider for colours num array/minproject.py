# -*- coding: utf-8 -*-
"""
Created on Wed Aug  1 22:31:55 2018

@author: HP
"""

import cv2
import numpy as np

def emptyFunction():
    pass

def main():
    
    img = np.zeros((512, 512, 3), np.uint8)
    windowName = 'OPENCV0'
    cv2.namedWindow(windowName)
    
    cv2.createTrackbar('B' ,windowName, 0, 255, emptyFunction)
    cv2.createTrackbar('G' ,windowName, 0, 255, emptyFunction)
    cv2.createTrackbar('R' ,windowName, 0, 255, emptyFunction)
    
    while(True):
        cv2.imshow(windowName, img)
        
        if cv2.waitKey(1) == 27:
            break
        
        blue = cv2.getTrackbarPos('B', windowName)
        green = cv2.getTrackbarPos('G', windowName)
        red = cv2.getTrackbarPos('R', windowName)
        
        img[:] = [blue, green, red]
        print (blue, green, red)
        
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()