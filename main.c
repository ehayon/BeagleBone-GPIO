#include "beaglebone.h"
#include "gpio.h"

int main(int args, char **argv) {
	printf("Export result = %d\n", gpio_export(34));
	printf("Analog read = %d\n", gpio_analog_read(34));
	printf("Unexport result = %d\n", gpio_unexport(34));
	printf("--- Program execution complete --- ");

	return 0;

}
