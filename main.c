#include "beaglebone.h"
#include "gpio.h"

// Licensed under The MIT License (MIT)
// See MIT-LICENSE file for more

int main(int args, char **argv) {
	printf("--- Begin program execution ---\n");
	printf("Export result = %d\n", gpio_export(34));
	printf("Analog read = %d\n", gpio_analog_read(34));
	printf("Unexport result = %d\n", gpio_unexport(34));
	printf("--- Program execution complete --- \n");

	return 0;

}
