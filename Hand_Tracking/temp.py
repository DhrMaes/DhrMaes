import cv2 as cv
import mediapipe as mp
import time

class HandTracker():
    def __init__(self, static_image_mode = False, max_num_hands = 2, min_detection_confidence = 0.8, min_tracking_confidence = 0.8):
        self.mode = static_image_mode
        self.maxHands = max_num_hands
        self.detectionLvl = min_detection_confidence
        self.trackingLvl = min_tracking_confidence

        self.mpHands = mp.solutions.hands
        self.hands = self.mpHands.Hands(self.mode, self.maxHands, self.detectionLvl, self.trackingLvl)
        self.mpDrawing = mp.solutions.drawing_utils

        self.points = [[0 for x in range(21)] for y in range(self.maxHands)] 
    
    def __getitem__(self, c):
        x, y = c
        return self.points[x][y]

    def findHands(self, img, draw = True):
        image = cv.cvtColor(img, cv.COLOR_BGR2RGB)
        results = self.hands.process(image)
        if results.multi_hand_landmarks:
            for handLms in results.multi_hand_landmarks:
                if(draw):
                    self.mpDrawing.draw_landmarks(img, handLms, self.mpHands.HAND_CONNECTIONS)
                for id, lm in enumerate(handLms.landmark):
                    h, w, c = img.shape
                    cx, cy = int(lm.x * w), int(lm.y * h)
        return img

    def findPosition(self, img, handNo=0, draw = True):
        lmList = []
        if self.results.multi_hand_landmarks:
            myHand = self.results.multi_hand_landmarks[handNo]
            for id, lm in enumerate(myHand.landmark):
                h, w, c = img.shape
                cx, cy = int(lm.x * w), int(lm.y * h)
                # print(id, cx, cy)
                lmList.append([id, cx, cy])
                if draw:
                    cv.circle(img, (cx, cy), 15, (36, 139, 251), cv.FILLED)
        return lmList
