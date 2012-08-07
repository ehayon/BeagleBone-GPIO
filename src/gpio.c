/*
 * Author: Ethan Hayon
 * Date: July 1, 2012
 * gpio.h
 *
 * Licensed under the MIT License (MIT)
 * See MIT-LICENSE file for more
 */

#include "gpio.h"

#define EXPORT fopen("/sys/class/gpio/export", "w")
#define UNEXPORT fopen("/sys/class/gpio/unexport", "w")

/*
 * Export a pin
 * Read and write to this pin once it is exported
 */
int gpio_export(int p) {
    FILE *fp = NULL;
    if((fp = EXPORT) == NULL) {
        perror("Cannot export pin");
        exit(1);
    }
    fprintf(fp, "%d", p);
    fclose(fp);
    return 1;
}

/*
 * Unexport a GPIO Pin
 * Don't try reading or writing to a pin until it is re-exported
 */
int gpio_unexport(int p) {
	FILE *fp = NULL;
	if((fp = UNEXPORT) == NULL) {
		perror("Cannot unexport pin");
		exit(1);
	}
	fprintf(fp, "%d", p);
	fclose(fp);
	return 1;
}

/*
 * Analog read from a GPIO pin
 */
int gpio_analog_read(unsigned int p) {
	FILE *fp = NULL;
	char buf[50];
	int val;
	sprintf(buf, "/sys/class/gpio/gpio%d/value", p);
	if((fp = fopen(buf, "r")) == NULL) {
		perror("Is the pin exported?");
		exit(1);
	}
	fscanf(fp, "%d", &val);
	return val;
}
