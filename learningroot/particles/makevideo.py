import cv2 as cv
out = cv.VideoWriter("./frames/video.mkv", cv.VideoWriter_fourcc("M","P","E","G"), 10, (698,474))   
for t in range(1, 200):
    frame = cv.imread("./frames/frame" + str(t) + ".png")
    print("./frames/frame" + str(t) + ".png")
    out.write(frame)