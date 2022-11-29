import cv2
import mediapipe as mp
import time
import math
import numpy as np



mode=False
upBody=False
smooth=True
detectionCon=0.5
trackCon=0.5
lmList = []

mpDraw = mp.solutions.drawing_utils
mpPose = mp.solutions.pose
# pose = mpPose.Pose(static_image_mode = mode,model_complexity = 1 ,upBody, smooth, detectionCon, trackCon)
pose = mpPose.Pose(static_image_mode = mode,model_complexity = 1 , smooth_landmarks = smooth,enable_segmentation = False,smooth_segmentation = False,min_detection_confidence = detectionCon, min_tracking_confidence = trackCon)
def findPose(img, draw=True):
        mpDraw = mp.solutions.drawing_utils
        mpPose = mp.solutions.pose
        imgRGB = cv2.cvtColor(src=img, code=cv2.COLOR_BGR2RGB)
        results = pose.process(imgRGB)
        if results.pose_landmarks:
            if draw:
                mpDraw.draw_landmarks(img, results.pose_landmarks,
                                           mpPose.POSE_CONNECTIONS)
        return img

def findPosition(img, draw=True):
        #lmList = []
        imgRGB = cv2.cvtColor(src=img,code=cv2.COLOR_BGR2RGB)
        results = pose.process(imgRGB)
        if results.pose_landmarks:
            for id, lm in enumerate(results.pose_landmarks.landmark):
                h, w, c = img.shape
                # print(id, lm)
                cx, cy = int(lm.x * w), int(lm.y * h)
                lmList.append([id, cx, cy])
                if draw:
                    cv2.circle(img, (cx, cy), 5, (255, 0, 0), cv2.FILLED)
        return lmList

def findAngle(img, p1, p2, p3, draw=True):

        # Get the landmarks
        x1, y1 = lmList[p1][1:]
        x2, y2 = lmList[p2][1:]
        x3, y3 = lmList[p3][1:]

        # Calculate the Angle
        angle = math.degrees(math.atan2(y3 - y2, x3 - x2) -
                             math.atan2(y1 - y2, x1 - x2))
        if angle < 0:
            angle += 360

        # print(angle)

        # Draw
        if draw:
            cv2.line(img, (x1, y1), (x2, y2), (255, 255, 255), 3)
            cv2.line(img, (x3, y3), (x2, y2), (255, 255, 255), 3)
            cv2.circle(img, (x1, y1), 10, (0, 0, 255), cv2.FILLED)
            cv2.circle(img, (x1, y1), 15, (0, 0, 255), 2)
            cv2.circle(img, (x2, y2), 10, (0, 0, 255), cv2.FILLED)
            cv2.circle(img, (x2, y2), 15, (0, 0, 255), 2)
            cv2.circle(img, (x3, y3), 10, (0, 0, 255), cv2.FILLED)
            cv2.circle(img, (x3, y3), 15, (0, 0, 255), 2)
            cv2.putText(img, str(int(angle)), (x2 - 50, y2 + 50),
                        cv2.FONT_HERSHEY_PLAIN, 2, (0, 0, 255), 2)
        return angle

def main():
    print("inside main")
    cap = cv2.VideoCapture('a_t.mp4')
    pTime = 0
    dir = 0
    count = 0



    #detector = mp.poseDetector()
    while True:
    #     success, img = cap.read()
    #     img = detector.findPose(img)
    #     lmList = detector.findPosition(img, draw=False)
    #     if len(lmList) != 0:
    #         print(lmList[14])
    #         cv2.circle(img, (lmList[14][1], lmList[14][2]), 15, (0, 0, 255), cv2.FILLED)

    #     cTime = time.time()
    #     fps = 1 / (cTime - pTime)
    #     pTime = cTime

    #     cv2.putText(img, str(int(fps)), (70, 50), cv2.FONT_HERSHEY_PLAIN, 3,
    #                 (255, 0, 0), 3)
        #print("hii")
        print("inside while")
        success, img = cap.read()
        img = cv2.resize(img, (1280, 720))
        # img = cv2.imread("AiTrainer/test.jpg")
        img = findPose(img, False)
        lmList = findPosition(img)
        # print(lmList)
        if len(lmList) != 0:
            # Right Arm
            angle = findAngle(img, 12, 14, 16,False)
            # # Left Arm
            #angle = detector.findAngle(img, 11, 13, 15,False)
            
            per = np.interp(angle, (210, 310), (0, 100))
            bar = np.interp(angle, (220, 310), (650, 100))
            
            print(angle, per)
            per+=1
            bar+=1
            print(angle, per)
                
            # Check for the dumbbell curls
            color = (255, 0, 255)
            if per == 100:
                color = (0, 255, 0)
                if dir == 0:
                    count += 0.5
                    dir = 1
            if per == 0:
                color = (0, 255, 0)
                if dir == 1:
                    count += 0.5
                    dir = 0
            print(count)

        # Draw Bar
            cv2.rectangle(img, (1100, 100), (1175, 650), color, 3)
            cv2.rectangle(img, (1100, int(bar)), (1175, 650), color, cv2.FILLED)
            
            cv2.putText(img, f'{int(per)} %', (1100, 75), cv2.FONT_HERSHEY_PLAIN, 4,
                        color, 4)
            

            # Draw Curl Count
        
            cv2.rectangle(img, (0, 450), (250, 720), (0, 255, 0), cv2.FILLED)    
            cv2.putText(img, str(int(count)), (45, 670), cv2.FONT_HERSHEY_PLAIN, 15,
                        (255, 0, 0), 25)

        cTime = time.time()
        fps = 1 / (cTime - pTime)
        pTime = cTime
        cv2.putText(img, str(int(fps)), (50, 100), cv2.FONT_HERSHEY_PLAIN, 5,
                    (255, 0, 0), 5)

        cv2.imshow("Image", img)
        cv2.waitKey(1)

main()
