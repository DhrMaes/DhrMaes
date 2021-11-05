import cv2
import mediapipe as mp
import time

cap = cv2.VideoCapture(0)
mpHands = mp.solutions.hands
hands = mpHands.Hands(
    static_image_mode = False, 
    max_num_hands = 2, 
    min_detection_confidence = 0.8,
    min_tracking_confidence = 0.8
    )
mpDraw = mp.solutions.drawing_utils

pTime = 0
cTime = 0

while True:
    success, img = cap.read()
    imgRBG = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    results = hands.process(imgRBG)
    # print(results.multi_hand_landmarks)

    if results.multi_hand_landmarks:
        for handLms in results.multi_hand_landmarks:
            for id, lm in enumerate(handLms.landmark):
                h, w, c = img.shape
                cx, cy = int(lm.x * w), int(lm.y * h)
                print(id, cx, cy)
            mpDraw.draw_landmarks(img, handLms, mpHands.HAND_CONNECTIONS)

    cTime = time.time()
    fps = 1 / (cTime - pTime)
    pTime = cTime

    cv2.putText(img, str(int(fps)), (15, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (36, 139, 251), 3)

    cv2.imshow("Image", img)
    cv2.waitKey(1)