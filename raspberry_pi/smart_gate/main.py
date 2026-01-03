from keypad import get_user_code
from uart_comm import send_command
from camera import capture_image, record_video_if_tailgating
from database import init_db, log_access

AUTHORIZED_CODES = ["1234", "5678"]

def main():
    init_db()
    print("Smart Gate System Started")

    while True:
        user_code = get_user_code()

        if user_code in AUTHORIZED_CODES:
            print("Access Granted")
            send_command("OPEN")

            image = capture_image()
            if image:
                log_access(user_code, image)

            video = record_video_if_tailgating()
            if video:
                print("Tailgating detected! Video saved.")

            send_command("CLOSE")

        else:
            print("Access Denied")

if __name__ == "__main__":
    main()
