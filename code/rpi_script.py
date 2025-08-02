import serial
import sys
import time

PORT = "/dev/ttyACM0"  # Adjust as needed
BAUD = 9600
tools = {
    "screwdriver M3" : "(1,3)"
}
def main():
    if len(sys.argv) < 2:
        print("Your forgot to specify the tool or the coordinates")
        return

    message = sys.argv[1]
    if message in tools:
        message = tools[message]
    try:
        arduino = serial.Serial(PORT, BAUD, timeout=1)
        time.sleep(2) 

        arduino.write((message + "\n").encode())
        print("Request sent successfully")

    except serial.SerialException as e:
        print("Serial error:", e)

    finally:
        if 'arduino' in locals():
            arduino.close()

if __name__ == "__main__":
    main()
