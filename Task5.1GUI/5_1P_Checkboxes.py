import tkinter as tk
import RPi.GPIO as GPIO

# setting GPIO mode
GPIO.setmode(GPIO.BCM)

# LED pins (rooms)
living_led = 17
bath_led = 27
closet_led = 22

# setup pins as output
GPIO.setup(living_led, GPIO.OUT)
GPIO.setup(bath_led, GPIO.OUT)
GPIO.setup(closet_led, GPIO.OUT)

# initially all OFF
GPIO.output(living_led, GPIO.LOW)
GPIO.output(bath_led, GPIO.LOW)
GPIO.output(closet_led, GPIO.LOW)

# function to control LEDs
def control_leds():
    # living room
    if living.get() == 1:
        GPIO.output(living_led, GPIO.HIGH)
    else:
        GPIO.output(living_led, GPIO.LOW)

    # bathroom
    if bathroom.get() == 1:
        GPIO.output(bath_led, GPIO.HIGH)
    else:
        GPIO.output(bath_led, GPIO.LOW)

    # closet
    if closet.get() == 1:
        GPIO.output(closet_led, GPIO.HIGH)
    else:
        GPIO.output(closet_led, GPIO.LOW)

# GUI window
root = tk.Tk()
root.title("Light Control")
root.geometry("280x230")

# heading
label = tk.Label(root, text="Room Lights", font=("Arial", 13))
label.pack(pady=10)

# variables for checkboxes
living = tk.IntVar()
bathroom = tk.IntVar()
closet = tk.IntVar()

# checkboxes
cb1 = tk.Checkbutton(root, text="Living Room", variable=living, command=control_leds)
cb1.pack()

cb2 = tk.Checkbutton(root, text="Bathroom", variable=bathroom, command=control_leds)
cb2.pack()

cb3 = tk.Checkbutton(root, text="Closet", variable=closet, command=control_leds)
cb3.pack()

# exit function
def close_app():
    GPIO.cleanup()
    root.destroy()

# exit button
btn = tk.Button(root, text="Exit", command=close_app)
btn.pack(pady=20)

# run GUI
root.mainloop()
