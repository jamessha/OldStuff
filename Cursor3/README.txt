Utilizes OpenCV and Emgu CV for contour detection and convex hull detection.

Finger Detection: 
- Find convexity defects 
- Find angle between defects
- Find distance between defect corner and depth
- Filter based off of angle and distance

UI:
- Looks at number of fingers over several frames to smooth out jumps
- Cursor is moved by "pushing" it around on a virtual touchscreen a set distacne from the kinect
- One finger click, two finger scroll, three finger zoom, grab hold