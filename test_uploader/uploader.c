#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>


#define TERM_SPEED 115200

const char *serial_dev = "/dev/ttyUSB0";

int main(int argc, char **argv)
{
	struct termios attrib;
	char ch;

	int serial_fd = 0,retval;

	serial_fd = open(serial_dev,O_RDWR|O_NOCTTY|O_NDELAY);

	if(serial_fd == -1) {
		perror("test_uploader");
		return serial_fd;
	}

/*	if((retval = tcgetattr(serial_fd,&attrib)) < 0) {
		perror("serial_fd");
		return retval;
	}*/


	memset(&attrib,0,sizeof(attrib));
	attrib.c_iflag = 0;
	attrib.c_oflag = 0;
	attrib.c_cflag = CS8|CREAD|CLOCAL;
	attrib.c_lflag = 0;
	attrib.c_cc[VMIN] = 1;
	attrib.c_cc[VTIME] = 5;

	if((retval = cfsetispeed(&attrib,B115200)) < 0) {
		perror("input baud rate");
		return retval;
	}

	if((retval = cfsetospeed(&attrib,B115200)) < 0) {
		perror("output baud rate");
		return retval;
	}

	/* Apply settings */

	if((retval = tcsetattr(serial_fd,TCSANOW,&attrib)) < 0) {
		perror("tcsetattr");
		return retval;
	}
	
	while(1) {

		ch = 'A';
		if(write(serial_fd,&ch,1) < 0) {
			perror("write");
			return -1;
		}

		ch = 0;
		while(ch == '\n') {
			if(read(serial_fd,&ch,1) < 0) {
				perror("read");
				return -1;
			}
		}
	}
	close(serial_fd);
}
