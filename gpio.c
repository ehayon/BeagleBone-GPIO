#include "gpio.h"

#define EXPORT fopen("/sys/class/gpio/export", "w")

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