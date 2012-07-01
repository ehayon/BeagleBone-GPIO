#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdlib.h>
#include <stdio.h>

int gpio_export(int);    // export a pin
int gpio_unexport(int);  // unexport a pin

/*int digital_write(int, char*);
int gpio_read(int);
*/
#endif