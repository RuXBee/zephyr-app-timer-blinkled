#include <zephyr/drivers/pwm.h>
#include <zephyr/drivers/led.h>
#include "user_led.h"

#define LED_NODE	DT_ALIAS(pwm_led0)
#if !DT_NODE_HAS_STATUS(LED_NODE, okay)
#error "Unsupported board: pwm_led0 devicetree alias is not defined"
#endif

#define MIN_PERIOD PWM_SEC(1U) / 128U
#define MAX_PERIOD PWM_SEC(1U)

const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(LED_NODE);


int init_pwm_led(void) {
	uint32_t max_period;
	uint32_t period;
	uint8_t dir = 0U;
	int ret;

    printk("Initializing LED pwm...\n");

	if (!device_is_ready(pwm_led0.dev)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_led0.dev->name);
		return;
	}

	/*
	 * In case the default MAX_PERIOD value cannot be set for
	 * some PWM hardware, decrease its value until it can.
	 *
	 * Keep its value at least MIN_PERIOD * 4 to make sure
	 * the sample changes frequency at least once.
	 */
	printk("Calibrating for channel %d...\n", pwm_led0.channel);
	max_period = MAX_PERIOD;
	while (pwm_set_dt(&pwm_led0, max_period, max_period / 2U)) {
		max_period /= 2U;
		if (max_period < (4U * MIN_PERIOD)) {
			printk("Error: PWM device "
			       "does not support a period at least %lu\n",
			       4U * MIN_PERIOD);
			return;
		}
	}
	pwm_set_dt(&pwm_led0, 1000000000, 1000000000/2);
}

const struct pwm_dt_spec get_pwm_led_dt(void) {
	return pwm_led0;
}