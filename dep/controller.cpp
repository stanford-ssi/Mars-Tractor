#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include "Motor.h"
#include <cstdlib>

//Pin Initializations
const int HARDWARE_PIN = 1;

const int BACK_IN1 = 0;
const int BACK_IN2 = 2;
const int BACK_IN3 = 21;
const int BACK_IN4 = 22;
const int BACK_LEFT_PWM = 3;
const int BACK_RIGHT_PWM = 25;

int read_event(int fd, struct js_event *event)
{
    ssize_t bytes;

    bytes = read(fd, event, sizeof(*event));

    if (bytes == sizeof(*event)) {
        return 0;
    }
    /* Error, could not read full event. */
    return -1;
}

/**
 * Returns the number of axes on the controller or 0 if an error occurs.
 */
size_t get_axis_count(int fd)
{
    __u8 axes;

    if (ioctl(fd, JSIOCGAXES, &axes) == -1) {
        return 0;
    }
    return axes;
}

/**
 * Returns the number of buttons on the controller or 0 if an error occurs.
 */
size_t get_button_count(int fd)
{
    __u8 buttons;
    if (ioctl(fd, JSIOCGBUTTONS, &buttons) == -1) {
        return 0;
    }
    return buttons;
}

/**
 * Current state of an axis.
 */
struct axis_state {
    short x, y;
};

/**
 * Keeps track of the current axis state.
 *
 * NOTE: This function assumes that axes are numbered starting from 0, and that
 * the X axis is an even number, and the Y axis is an odd number. However, this
 * is usually a safe assumption.
 *
 * Returns the axis that the event indicated.
 */
size_t get_axis_state(struct js_event *event, struct axis_state axes[3])
{
    size_t axis = event->number / 2;

    if (axis < 3)
    {
        if (event->number % 2 == 0) {
            axes[axis].x = event->value;
        }
        else {
            axes[axis].y = event->value;
        }
    }

    return axis;
}

int main(int argc, char *argv[])
{
    if (wiringPiSetup() == -1) {
        std::cout << "The wiringPi library has failed to initialize." << std::endl;     
    }

    Motor leftMotor(BACK_IN1, BACK_IN2, BACK_LEFT_PWM);
    Motor rightMotor(BACK_IN3, BACK_IN4, BACK_RIGHT_PWM);

    const char *device;
    int js;
    struct js_event event;
    struct axis_state axes[3] = {0};
    size_t axis;

    if (argc > 1) {
        device = argv[1];
    }
    else {
        device = "/dev/input/js0";
    }
    js = open(device, O_RDONLY);

    if (js == -1) {
        perror("Could not open joystick");
    }

    /* This loop will exit if the controller is unplugged. */
    while (read_event(js, &event) == 0)
    {
        switch (event.type)
        {
            /*
            case JS_EVENT_BUTTON:
                printf("Button %u %s\n", event.number, event.value ? "pressed" : "released");
                break;
            */
            case JS_EVENT_AXIS:
                axis = get_axis_state(&event, axes);
                if (axis < 3)
                    printf("Axis %zu at (%6d, %6d)\n", axis, axes[axis].x, axes[axis].y);
                if (axes[0].y < -20) {
                    leftMotor.setForward(axes[0].y);
                    rightMotor.setForward(axes[0].y);
                }
                else if (axes[0].y > 20) {
                    leftMotor.setReverse(abs(axes[0].y));
                    rightMotor.setReverse(abs(axes[0].y));
                }
                else {
                    leftMotor.stop();
                    rightMotor.stop();
                }
                break;
            default:
                /* Ignore init events. */
                break;
        }
        
        fflush(stdout);
    }

    close(js);
    return 0;
}

//for when libevdev works
/*
#include <linux/input.h>
#include "libevdev/libevdev.h"

struct libevdev *dev = NULL;
 int fd;
 int rc = 1;

 fd = open("/dev/input/event0", O_RDONLY|O_NONBLOCK);
 rc = libevdev_new_from_fd(fd, &dev);
 if (rc < 0) {
         fprintf(stderr, "Failed to init libevdev (%s)\n", strerror(-rc));
         exit(1);
 }
 printf("Input device name: \"%s\"\n", libevdev_get_name(dev));
 printf("Input device ID: bus %#x vendor %#x product %#x\n",
        libevdev_get_id_bustype(dev),
        libevdev_get_id_vendor(dev),
        libevdev_get_id_product(dev));
 if (!libevdev_has_event_type(dev, EV_REL) ||
     !libevdev_has_event_code(dev, EV_KEY, BTN_LEFT)) {
         printf("This device does not look like a mouse\n");
         exit(1);
 }

 do {
         struct input_event ev;
         rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
         if (rc == 0)
                 printf("Event: %s %s %d\n",
                        libevdev_event_type_get_name(ev.type),
                        libevdev_event_code_get_name(ev.type, ev.code),
                        ev.value);
 } while (rc == 1 || rc == 0 || rc == -EAGAIN);

#include "config.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <linux/input.h>

#include "libevdev/libevdev.h"

static void
print_abs_bits(struct libevdev *dev, int axis)
{
	const struct input_absinfo *abs;

	if (!libevdev_has_event_code(dev, EV_ABS, axis))
		return;

	abs = libevdev_get_abs_info(dev, axis);

	printf("	Value	%6d\n", abs->value);
	printf("	Min	%6d\n", abs->minimum);
	printf("	Max	%6d\n", abs->maximum);
	if (abs->fuzz)
		printf("	Fuzz	%6d\n", abs->fuzz);
	if (abs->flat)
		printf("	Flat	%6d\n", abs->flat);
	if (abs->resolution)
		printf("	Resolution	%6d\n", abs->resolution);
}

static void
print_code_bits(struct libevdev *dev, unsigned int type, unsigned int max)
{
	unsigned int i;
	for (i = 0; i <= max; i++) {
		if (!libevdev_has_event_code(dev, type, i))
			continue;

		printf("    Event code %i (%s)\n", i, libevdev_event_code_get_name(type, i));
		if (type == EV_ABS)
			print_abs_bits(dev, i);
	}
}

static void
print_bits(struct libevdev *dev)
{
	unsigned int i;
	printf("Supported events:\n");

	for (i = 0; i <= EV_MAX; i++) {
		if (libevdev_has_event_type(dev, i))
			printf("  Event type %d (%s)\n", i, libevdev_event_type_get_name(i));
		switch(i) {
			case EV_KEY:
				print_code_bits(dev, EV_KEY, KEY_MAX);
				break;
			case EV_REL:
				print_code_bits(dev, EV_REL, REL_MAX);
				break;
			case EV_ABS:
				print_code_bits(dev, EV_ABS, ABS_MAX);
				break;
			case EV_LED:
				print_code_bits(dev, EV_LED, LED_MAX);
				break;
		}
	}
}

static void
print_props(struct libevdev *dev)
{
	unsigned int i;
	printf("Properties:\n");

	for (i = 0; i <= INPUT_PROP_MAX; i++) {
		if (libevdev_has_property(dev, i))
			printf("  Property type %d (%s)\n", i,
					libevdev_property_get_name(i));
	}
}

static int
print_event(struct input_event *ev)
{
	if (ev->type == EV_SYN)
		printf("Event: time %ld.%06ld, ++++++++++++++++++++ %s +++++++++++++++\n",
				ev->input_event_sec,
				ev->input_event_usec,
				libevdev_event_type_get_name(ev->type));
	else
		printf("Event: time %ld.%06ld, type %d (%s), code %d (%s), value %d\n",
			ev->input_event_sec,
			ev->input_event_usec,
			ev->type,
			libevdev_event_type_get_name(ev->type),
			ev->code,
			libevdev_event_code_get_name(ev->type, ev->code),
			ev->value);
	return 0;
}

static int
print_sync_event(struct input_event *ev)
{
	printf("SYNC: ");
	print_event(ev);
	return 0;
}

int 
main(int argc, char **argv)
{
	struct libevdev *dev = NULL;
	const char *file;
	int fd;
	int rc = 1;

	if (argc < 2)
		goto out;

	file = argv[1];
	fd = open(file, O_RDONLY);
	if (fd < 0) {
		perror("Failed to open device");
		goto out;
	}

	rc = libevdev_new_from_fd(fd, &dev);
	if (rc < 0) {
		fprintf(stderr, "Failed to init libevdev (%s)\n", strerror(-rc));
		goto out;
	}

	printf("Input device ID: bus %#x vendor %#x product %#x\n",
			libevdev_get_id_bustype(dev),
			libevdev_get_id_vendor(dev),
			libevdev_get_id_product(dev));
	printf("Evdev version: %x\n", libevdev_get_driver_version(dev));
	printf("Input device name: \"%s\"\n", libevdev_get_name(dev));
	printf("Phys location: %s\n", libevdev_get_phys(dev));
	printf("Uniq identifier: %s\n", libevdev_get_uniq(dev));
	print_bits(dev);
	print_props(dev);

	do {
		struct input_event ev;
		rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL|LIBEVDEV_READ_FLAG_BLOCKING, &ev);
		if (rc == LIBEVDEV_READ_STATUS_SYNC) {
			printf("::::::::::::::::::::: dropped ::::::::::::::::::::::\n");
			while (rc == LIBEVDEV_READ_STATUS_SYNC) {
				print_sync_event(&ev);
				rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_SYNC, &ev);
			}
			printf("::::::::::::::::::::: re-synced ::::::::::::::::::::::\n");
		} else if (rc == LIBEVDEV_READ_STATUS_SUCCESS)
			print_event(&ev);
	} while (rc == LIBEVDEV_READ_STATUS_SYNC || rc == LIBEVDEV_READ_STATUS_SUCCESS || rc == -EAGAIN);

	if (rc != LIBEVDEV_READ_STATUS_SUCCESS && rc != -EAGAIN)
		fprintf(stderr, "Failed to handle events: %s\n", strerror(-rc));

	rc = 0;
out:
	libevdev_free(dev);

	return rc;
}
*/