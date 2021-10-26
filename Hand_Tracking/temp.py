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
        self.mpDraw = mp.solutions.drawing_utils

        self.points = [[0 for x in range(21)] for y in range(self.maxHands)] 
    
    def __getitem__(self, c):
        x, y = c
        return self.points[x][y]

    def __setitem__(self, c, v):
        x, y = c
        self.data[x][y] = v

    def findHands(self, img, draw = True):
        imgRBG = cv.cvtColor(img, cv.COLOR_BGR2RGB)
        results = self.hands.process(imgRBG)
        # print(results.multi_hand_landmarks)

        if results.multi_hand_landmarks:
            for handLms in results.multi_hand_landmarks:
                if(draw):
                    self.mpDraw.draw_landmarks(img, handLms, self.mpHands.HAND_CONNECTIONS)
        return img

    def findPosition(self, img, handNo=0, draw = True):
        lmList = []
        if results.multi_hand_landmarks:
            for id, lm in enumerate(handLms.landmark):
                h, w, c = img.shape
                cx, cy = int(lm.x * w), int(lm.y * h)
                print(id, cx, cy)
