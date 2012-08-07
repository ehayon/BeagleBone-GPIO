// Licensed under The MIT License (MIT)
// See MIT-LICENSE file for more
#include "src/beaglebone.h"

int main(int args, char **argv) {

    char *custom_dir = getenv("GPIO");
    if(custom_dir != NULL) {
        printf("Default GPIO override: %s\n\n", custom_dir);
    }
    else {
        printf("Using default GPIO class: /sys/class/gpio\n");
    }

    printf("--- Begin program execution ---\n");
	printf("Export result = %d\n", gpio_export(34));
	printf("Analog read = %d\n", gpio_analog_read(34));
	printf("Unexport result = %d\n", gpio_unexport(34));
	printf("--- Program execution complete --- \n");

	return 0;

}
