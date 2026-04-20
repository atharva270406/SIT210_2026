import tkinter as tk
import RPi.GPIO as GPIO

# GPIO setup
GPIO.setmode(GPIO.BCM)

LED_LIVING = 18   # PWM pin
LED_BATHROOM = 27
LED_CLOSET = 22

GPIO.setup(LED_LIVING, GPIO.OUT)
GPIO.setup(LED_BATHROOM, GPIO.OUT)
GPIO.setup(LED_CLOSET, GPIO.OUT)

# PWM setup for living room
pwm = GPIO.PWM(LED_LIVING, 100)
pwm.start(0)

# Function to turn OFF all lights
def turn_off_all():
    pwm.ChangeDutyCycle(0)
    GPIO.output(LED_BATHROOM, GPIO.LOW)
    GPIO.output(LED_CLOSET, GPIO.LOW)

# Slider function (brightness control)
def change_brightness(val):
    turn_off_all()
    pwm.ChangeDutyCycle(int(val))

# Bathroom ON
def bathroom_on():
    turn_off_all()
    GPIO.output(LED_BATHROOM, GPIO.HIGH)

# Closet ON
def closet_on():
    turn_off_all()
    GPIO.output(LED_CLOSET, GPIO.HIGH)

# GUI setup
root = tk.Tk()
root.title("Smart Light Control")
root.geometry("300x300")

# Title
tk.Label(root, text="Living Room Brightness", font=("Arial", 12)).pack(pady=10)

# Slider (0–100)
slider = tk.Scale(root, from_=0, to=100, orient=tk.HORIZONTAL, command=change_brightness)
slider.pack()

# Other lights
tk.Label(root, text="Other Lights", font=("Arial", 12)).pack(pady=10)

tk.Button(root, text="Bathroom ON", command=bathroom_on).pack(pady=5)
tk.Button(root, text="Closet ON", command=closet_on).pack(pady=5)

# Exit button
def exit_app():
    pwm.stop()
    GPIO.cleanup()
    root.destroy()

tk.Button(root, text="Exit", command=exit_app, bg="red", fg="white").pack(pady=20)

root.mainloop()
