import serial
import time

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)

last_data_time = time.time()
current_state = "SAFE"

print("====================================")
print(" Smart Blind Assistance Supervisor ")
print("====================================")

while True:

    line = ser.readline().decode().strip()

    # Communication Watchdog
    if not line:

        if time.time() - last_data_time > 3:

            if current_state != "COMM_FAULT":

                current_state = "COMM_FAULT"

                print("\n====================================")
                print("FAULT: COMMUNICATION LOST")
                print("====================================\n")

        continue

    last_data_time = time.time()

    # Log all sensor data
    with open("sensor_log.txt", "a") as f:

        f.write(
            time.strftime("%Y-%m-%d %H:%M:%S")
            + " | "
            + line
            + "\n"
        )

    print(line)

    try:

        parts = line.split(',')

        distance = float(parts[0].split('=')[1])
        light = float(parts[1].split('=')[1])

        new_state = "SAFE"

        # Sensor fault detection
        if distance == 999:
            new_state = "SENSOR_FAULT"

        elif distance < 15:
            new_state = "CRITICAL"

        elif distance < 30:
            new_state = "WARNING"

        # State change detection
        if new_state != current_state:

            current_state = new_state

            print("\n====================================")
            print("STATE:", current_state)
            print("====================================\n")

        # Low light detection
        if light < 20:
            print("Environment: DARK")

    except Exception as e:

        print("PARSE ERROR:", e)
