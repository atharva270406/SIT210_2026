import tkinter as tk
import RPi.GPIO as GPIO

# GPIO Setup
GPIO.setmode(GPIO.BCM)

LED_LIVING = 17
LED_BATHROOM = 27
LED_CLOSET = 22

GPIO.setup(LED_LIVING, GPIO.OUT)
GPIO.setup(LED_BATHROOM, GPIO.OUT)
GPIO.setup(LED_CLOSET, GPIO.OUT)

# Turn OFF all initially
GPIO.output(LED_LIVING, GPIO.LOW)
GPIO.output(LED_BATHROOM, GPIO.LOW)
GPIO.output(LED_CLOSET, GPIO.LOW)

# Function to control LEDs
def update_led():
    choice = selected.get()

    GPIO.output(LED_LIVING, GPIO.LOW)
    GPIO.output(LED_BATHROOM, GPIO.LOW)
    GPIO.output(LED_CLOSET, GPIO.LOW)

    if choice == 1:
        GPIO.output(LED_LIVING, GPIO.HIGH)
    elif choice == 2:
        GPIO.output(LED_BATHROOM, GPIO.HIGH)
    elif choice == 3:
        GPIO.output(LED_CLOSET, GPIO.HIGH)

# GUI Window
root = tk.Tk()
root.title("Home Light Controller")
root.geometry("300x200")

selected = tk.IntVar()

tk.Label(root, text="Select Room", font=("Arial", 14)).pack(pady=10)

# Radio Buttons
tk.Radiobutton(root, text="Living Room", variable=selected, value=1, command=update_led).pack()
tk.Radiobutton(root, text="Bathroom", variable=selected, value=2, command=update_led).pack()
tk.Radiobutton(root, text="Closet", variable=selected, value=3, command=update_led).pack()

# Exit Button
def exit_app():
    GPIO.cleanup()
    root.destroy()

tk.Button(root, text="Exit", command=exit_app, bg="red", fg="white").pack(pady=20)

root.mainloop()
