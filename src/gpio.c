/*
 * Author: Ethan Hayon
 * Date: July 1, 2012
 * gpio.h
 *
 * Licensed under the MIT License (MIT)
 * See MIT-LICENSE file for more
 */

#include "gpio.h"

/* 
 * Get GPIO dir
 * Get the directory to the GPIO class, wheter it's custom or not
 */

char* gpio_dir() {
    
    // temp dir
    static char temp[128];

	// try to get the environment var
    char *env = getenv("GPIO");
    if(env != NULL) {
        
        // let's be smart, check for trailing slash
    	int pos = strrchr(env, '/') - env + 1;
        int len = (unsigned)strlen(env);

        // is it the last char?
    	if(pos == len) {
    		return env;
    	}
    	else {
    		sprintf(temp, "%s/", env);
    		return temp;
    	}
    }
   	else {
   		return "/sys/class/gpio";
	}
}

/*
 * Export a pin
 * Read and write to this pin once it is exported
 */
int gpio_export(int p) {

    FILE *fp = NULL;
    
    // get the export dir
    char export_dir[128];
    sprintf(export_dir, "%sexport", gpio_dir());
    
    // open the file
    if((fp = fopen(export_dir, "w")) == NULL) {
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
    
    // get the unexport dir
    char unexport_dir[128];
    sprintf(unexport_dir, "%sunexport", gpio_dir()); 

	// open the file to unexport
	if((fp = fopen(unexport_dir, "w")) == NULL) {
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
	int val;
    
	 // get the unexport dir
    char analog_read_dir[128];
    sprintf(analog_read_dir, "%sgpio%d/value", gpio_dir(), p);

	// open the file to read
    if((fp = fopen(analog_read_dir, "r")) == NULL) {
		perror("Analog read failed. Is the pin exported?");
		exit(1);
	}
	fscanf(fp, "%d", &val);
	return val;
}
