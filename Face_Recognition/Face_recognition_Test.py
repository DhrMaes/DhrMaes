import cv2
import numpy as np
import face_recognition
import os

imgArne = face_recognition.load_image_file('Arne (1).jpg')
imgArne = cv2.cvtColor(imgArne, cv2.COLOR_BGR2RGB)
imgTest = face_recognition.load_image_file('Arne (2).jpg')
imgTest = cv2.cvtColor(imgTest, cv2.COLOR_BGR2RGB)

faceLoc = face_recognition.face_locations(imgArne)[0]
encodeArne = face_recognition.face_encodings(imgArne)[0]
cv2.rectangle(imgArne, (faceLoc[3], faceLoc[0]), (faceLoc[1], faceLoc[2]), (0, 255, 0), 2)

faceLocTest = face_recognition.face_locations(imgTest)[0]
encodeArneTest = face_recognition.face_encodings(imgTest)[0]
cv2.rectangle(imgTest, (faceLocTest[3], faceLocTest[0]), (faceLocTest[1], faceLocTest[2]), (0, 255, 0), 2)

result = face_recognition.compare_faces([encodeArne], encodeArneTest)
faceDis = face_recognition.face_distance([encodeArne], encodeArneTest)

cv2.imshow('Original', imgArne)
cv2.imshow('Test', imgTest)
cv2.waitKey(0)