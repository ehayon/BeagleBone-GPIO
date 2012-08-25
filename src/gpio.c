/**
 * @file gpio.c
 * @author Ethan Hayon
 *
 * This file contains GPIO functions using high
 * performance mmap of /dev/mem
 *
 * Licensed under the MIT License (MIT)
 * See MIT-LICENSE file for more information
 */

#include "gpio.h"

static volatile uint32_t *map;
static char mapped = FALSE;

/**
 * map /dev/mem to memory
 *
 * @returns whether or not the mapping of /dev/mem into memory was successful
 */
int init() {
	if(!mapped) {
		puts("Initializing...");
		int fd;
		fd = open("/dev/mem", O_RDWR);
		if(fd == -1) {
			perror("Unable to open /dev/mem");
			exit(EXIT_FAILURE);
		}
		map = (uint32_t*)mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, MMAP_OFFSET);
		if(map == MAP_FAILED) {
			close(fd);
			perror("Unable to map /dev/mem");
			exit(EXIT_FAILURE);
		}
		mapped = TRUE;
	}
	return mapped;
}

/**
 * Set up a pin for future use
 *
 * @param pin The pin to set up
 * @param direction Configure the pin as INPUT or OUTPUT
 * @param mux Mux mode to use for this pin 0-7
 * @param pull PULLUP, PULLDOWN, or DISABLED
 * @returns the pin was successfully configured
 */
int pinMode(PIN pin, unsigned char direction, unsigned char mux, unsigned char pull) {
	// map over the values of pull, 0=pulldown, 1=pullup, 2=disabled
	int pin_data = 0;
	pin_data |=  mux; // set the mux mode
	// set up the pull up/down resistors
	if(pull == DISABLED) pin_data |= 1 << 3;
	if(pull == PULLUP)   pin_data |= 1 << 4;
	pin_data |= direction << 5; // set up the pin direction
	// write the pin_data
	FILE *fp = NULL;
	char muxfile[64];
	sprintf(muxfile, "%s/%s", CONFIG_MUX_PATH, pin.mux);
	// open the file
	if((fp = fopen(muxfile, "w")) == NULL) {
		perror("Cannot set pin mode");
		exit(1);
	}
	fprintf(fp, "%x", pin_data);
	fclose(fp);
	
	return 1;
}


/**
 * Set a GPIO digital output * @param p Pin to write to
 *
 * @param mode Position to set the pin, HIGH or LOW
 * @returns output was successfully written
 */
int digitalWrite(PIN p, uint8_t mode) {
	init();
	if(mode == HIGH) map[(p.gpio_bank-MMAP_OFFSET+GPIO_DATAOUT)/4] |= 1<<p.bank_id;
	else map[(p.gpio_bank-MMAP_OFFSET+GPIO_DATAOUT)/4] &= ~(1<<p.bank_id);
	return 1;
}

/**
 * Read the input from a digital input. You must set 
 * the pin as an INPUT using the pinMode function
 *
 * @param p Pin to read from
 * @returns the value of the pin
 */
int digitalRead(PIN p) {
	init();
	return (map[(p.gpio_bank-MMAP_OFFSET+GPIO_DATAIN)/4] & (1<<p.bank_id))>>p.bank_id;
}
