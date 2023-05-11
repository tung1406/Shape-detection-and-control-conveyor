import cv2
import serial
scale = 2
cap = cv2.VideoCapture(0)
print("press q to exit")

ser = serial.Serial('/dev/ttyUSB1', 9600, timeout=1)
ser.reset_input_buffer()

while(cap.isOpened()):

    ret, frame = cap.read()
    if ret==True:
        canny = cv2.Canny(frame,80,240,3)
        contours, hierarchy = cv2.findContours(canny,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
        for i in range(0,len(contours)):
            approx = cv2.approxPolyDP(contours[i],cv2.arcLength(contours[i],True)*0.02,True)

            if(abs(cv2.contourArea(contours[i]))<100 or not(cv2.isContourConvex(approx))):
                continue
            if(len(approx) == 3):
                x,y,w,h = cv2.boundingRect(contours[i])
                cv2.putText(frame,'Triangle',(x,y),cv2.FONT_HERSHEY_SIMPLEX,scale,(255, 0, 0),2,cv2.LINE_AA)
                print("Sending triangle")
                ser.write(b"triangle\n")

            elif(len(approx)==4):
                x, y, w, h = cv2.boundingRect(contours[i])
                cv2.putText(frame,'Rectangle',(x,y),cv2.FONT_HERSHEY_SIMPLEX,scale,(255, 0, 0),2,cv2.LINE_AA)
                print("Sending rectangle")
                ser.write(b"rectangle\n")
        cv2.imshow('frame',frame)
        cv2.imshow('canny',canny)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

cap.release()
cv2.destroyAllWindows()