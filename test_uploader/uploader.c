#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>


#define TERM_SPEED 115200

const char *serial_dev = "/dev/ttyUSB0";

int main(int argc, char **argv)
{
	struct termios attrib;
	char ch,val_ch;
	int serial_fd = 0,binary_fd,retval;
	unsigned int size = 0;

	struct stat stat_buff;

	if(argc != 2) {
		printf("Usage: uploader <filename>\n");
		return 0;
	}

	binary_fd = open(argv[1],O_RDONLY);
	
	if(binary_fd == -1) {
		perror("uploader_open");
		return -1;
	}

	stat(argv[1],&stat_buff);
	printf("Uploading size : %lu\n",stat_buff.st_size);

	serial_fd = open(serial_dev,O_RDWR);

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
	attrib.c_cc[VTIME] = 0;

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
	

	size = stat_buff.st_size;

		
	if(write(serial_fd,&size,sizeof(size)) < 0) {
		perror("write");
		return -1;
	}

	ch = 0;
	while(ch != '\n') {
		if(read(serial_fd,&ch,1) < 0) {
			perror("read");
			return -1;
		}
		printf("%c",ch);
	}

	while(read(binary_fd,&ch,1)) {
		write(serial_fd,&ch,1);
		read(serial_fd,&val_ch,1);

		if(ch != val_ch) {
			printf("Match failed\n");
			break;
		} else {
			printf("%02x ",(unsigned char)ch);
		}
	}
	
	printf("\n");
	close(binary_fd);
	close(serial_fd);
}
