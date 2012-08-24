#include "src/gpio.h"

int main() {
	while(1) {
		digitalWrite(USR3, HIGH);
		usleep(50000);
		digitalWrite(USR2, HIGH);
		usleep(50000);
		digitalWrite(USR1, HIGH);
		usleep(50000);
		digitalWrite(USR0, HIGH);
		usleep(50000);
		digitalWrite(USR3, LOW);
		usleep(50000);
		digitalWrite(USR2, LOW);
		usleep(50000);
		digitalWrite(USR1, LOW);
		usleep(50000);
		digitalWrite(USR0, LOW);
		usleep(50000);
	}	
	//munmap(map, fd);	
	return 0;
}
