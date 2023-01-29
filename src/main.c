#include <zephyr/kernel.h>

void main(void) {

	while (1) {
		printk("The board is %s\n", CONFIG_BOARD);
		k_msleep(1000);
	}
}

