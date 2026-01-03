import cv2
import time
from config import CAMERA_URL, VIDEO_DURATION

hog = cv2.HOGDescriptor()
hog.setSVMDetector(cv2.HOGDescriptor_getDefaultPeopleDetector())

def capture_image():
    cap = cv2.VideoCapture(CAMERA_URL)
    ret, frame = cap.read()
    cap.release()
    if ret:
        filename = f"images/{int(time.time())}.jpg"
        cv2.imwrite(filename, frame)
        return filename
    return None

def detect_people(frame):
    boxes, _ = hog.detectMultiScale(frame, winStride=(8,8))
    return len(boxes)

def record_video_if_tailgating():
    cap = cv2.VideoCapture(CAMERA_URL)
    fourcc = cv2.VideoWriter_fourcc(*"XVID")
    filename = f"videos/{int(time.time())}.avi"
    out = cv2.VideoWriter(filename, fourcc, 20.0, (640,480))

    start = time.time()
    while time.time() - start < VIDEO_DURATION:
        ret, frame = cap.read()
        if not ret:
            break
        if detect_people(frame) > 1:
            out.write(frame)
        cv2.imshow("Monitor", frame)
        if cv2.waitKey(1) == 27:
            break

    cap.release()
    out.release()
    cv2.destroyAllWindows()
    return filename
