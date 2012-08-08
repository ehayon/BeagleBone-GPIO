// Licensed under The MIT License (MIT)
// See MIT-LICENSE file for more

#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* gpio_dir(); // get the gpio class directory
int gpio_export(int);    // export a pin
int gpio_unexport(int);  // unexport a pin
int gpio_analog_read(unsigned int);  // analog read

/* To implement
int digital_write(unsigned int port, int value);
*/

#endif
