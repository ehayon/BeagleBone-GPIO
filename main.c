#include "beaglebone.h"
#include "gpio.h"

int main(int args, char **argv) {
    printf("Export result = %d\n", gpio_export(34));
	return 0;
}
