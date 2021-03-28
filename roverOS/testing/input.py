import RPi.GPIO as GPIO
import time

# Pin Definitions
input_pinA = 'DAP1_FS'  # BCM pin 18, BOARD pin 12
input_pinB = 'GPIO_PQ4'

def main():
    prev_value = None

    # Pin Setup:
    GPIO.setmode(GPIO.TEGRA_SOC)  # BCM pin-numbering scheme from Raspberry Pi
    GPIO.setup(input_pinA, GPIO.IN)  # set pin as an input pin
    GPIO.setup(input_pinB, GPIO.IN)  # set pin as an input pin
    
    print("Starting demo now! Press CTRL+C to exit")
    try:
        while True:
            print(GPIO.input(input_pinA), end='')
            print(GPIO.input(input_pinB))
            time.sleep(.01)
    finally:
        GPIO.cleanup()
        

if __name__ == '__main__':
    main()