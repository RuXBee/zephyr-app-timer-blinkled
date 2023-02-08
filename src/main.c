#include <zephyr/kernel.h>
#include "user_button.h"
#include "user_led.h"

static int pwm_frequency = 0;


static void button_event_handler(enum button_evt evt)
{
	switch (evt) {
	case BUTTON_EVT_PRESSED:

		return "Pressed";
	case BUTTON_EVT_RELEASED:
		return "Released";
	default:
		return "Unknown";
	}
}

void main(void)
{
	int err = -1;

	printk("Button Debouncing Sample!\n");

	err = button_init(button_event_handler);
	if (err) {
		printk("Button Init failed: %d\n", err);
		return;
	}
	
	err = init_pwm_led();
	if (err) {
		printk("LED Init failed: %d\n", err);
		return;
	}

	printk("Init succeeded. Waiting for event...\n");
}