import cv2
import numpy as np
import face_recognition
import os

path = 'Z:/Documents/Mediapipe/img/'
faceLocations = []
encodings = []

imgArne = face_recognition.load_image_file(path + 'Start.png')
imgArne = cv2.cvtColor(imgArne, cv2.COLOR_BGR2RGB)
faceLocArne = face_recognition.face_locations(imgArne)[0]
encodeArne = face_recognition.face_encodings(imgArne)[0]
encodings.append(encodeArne)

# for img in os.listdir(path):
#     print(path + img)
#     image = cv2.imread(path + img)
#     image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
#     faceLocation = face_recognition.face_locations(image)
#     faceLocations.append(faceLocation)
#     encodings.append(face_recognition.face_encodings(image))
#     cv2.rectangle(image, (faceLocation[3], faceLocation[0]), (faceLocation[1], faceLocation[2]), (0,255,0), 2)
#     cv2.imshow('Image: ' + img, image)
#     cv2.waitKey(0)

print("Encodings complete")

cap = cv2.VideoCapture(0)

while True:
    success, img = cap.read()
    if not success:
        print("Ignoring empty camera frame.")
        # If loading a video, use 'break' instead of 'continue'.
        continue
    imgS = cv2.resize(img, (0, 0), None, 0.25, 0.25)
    imgS = cv2.cvtColor(imgS, cv2.COLOR_BGR2RGB)

    location = face_recognition.face_locations(imgS)
    if len(location) != 0:
        location = location[0]
    encode = face_recognition.face_encodings(imgS)
    if len(encode) != 0:
        encode = encode[0]
        match = face_recognition.compare_faces(encodings, encode)
        distance = face_recognition.face_distance(encodings, encode)
        print(match, distance)
    else:
        match = False

    if match:
        y1, x2, y2, x1 = location
        y1, x2, y2, x1 = y1 * 4, x2 * 4, y2 * 4, x1 * 4
        cv2.rectangle(img, (x1, y1), (x2, y2), (0, 255, 0), 2)
        cv2.rectangle(img, (x1, y2 - 35), (x2, y2), (0, 255, 0), cv2.FILLED)
        cv2.putText(img, 'Arne Maes', (x1 + 6, y2 - 6), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)
    # for encodeFace, faecLoc in zip(encode, location):
    #     matches = face_recognition.compare_faces(encodings, encodeFace)
    #     print(matches)
    #     face_distance = face_recognition.face_distance(encodings, encodeFace)
    #     index = np.argmin(face_distance)
    
    cv2.imshow('Webcam', img)
    cv2.waitKey(1)