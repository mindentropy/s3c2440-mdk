#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <stdint.h>
#include "sunflower.h"

//#define OS_UPLOAD_DBG 


#undef TEST_LCD

#define TERM_SPEED 115200

const char *serial_dev = "/dev/ttyUSB0";


int read_str_response(int serial_fd)
{
	char ch = 0;
	unsigned int count = 0;

	while(ch != '\n') {
		if(read(serial_fd,&ch,1) < 0) {
			perror("read");
			return -1;
		}
		count++;
		printf("%c",ch);
	}
	return count;
}

void print_progress(const char legend[],
						uint32_t progress,
						uint32_t final_progress)
{
	uint32_t progress_percent = ((float)(progress)/(float)(final_progress))*100;

	printf("\r");
	fflush(stdout);

	printf("%s: %d%%\r",legend,progress_percent);
	fflush(stdout);
}

int main(int argc, char **argv)
{
	struct termios attrib;
	char ch,val_ch;
	int serial_fd = 0,binary_fd,retval;
	unsigned int size = 0,serial_index = 0;
	unsigned progress = 0;

#ifdef TEST_LCD
	unsigned pic_size = sizeof(image)/sizeof(char);
	unsigned pic_idx = 0;
#endif

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

	//read_str_response(serial_fd);

	while(read(binary_fd,&ch,1)) {

		write(serial_fd,&ch,1);
		read(serial_fd,&val_ch,1);

		if(ch != val_ch) {
			printf("Match failed\n");
			break;
		} else {

#ifdef OS_UPLOAD_DBG
			if((serial_index & 0x1F) == 0) 
				printf("\n");

			printf("%02x ",(unsigned char)ch);
#endif

			serial_index++;
			progress++;
			
			print_progress("Upload progress",
							progress,
							size);

		}
	}
	
	printf("\nOS uploaded\n");
	printf("\n");

#ifdef TEST_LCD
	printf("Uploading picture of size :%u\n",pic_size);
	sleep(2);
	for(pic_idx = 0; pic_idx<pic_size; pic_idx++)
	{
		write(serial_fd,image+pic_idx,1);
		read(serial_fd,&val_ch,1);

		if(image[pic_idx] != (unsigned char)val_ch) {
			printf("0x%02x 0x%02x\n",image[pic_idx],(unsigned char)(val_ch));
			printf("Match failed\n");
			break;
		}

		print_progress("Upload progress",pic_idx,pic_size);
	//	printf("Index : %u\n",pic_idx);
	}
	printf("Done uploading picture\n");
#endif

	serial_index = 0;
	while(1) {
		read_str_response(serial_fd);
	/*	read(serial_fd,&val_ch,1);

		if((serial_index & 0x1F) == 0)
			printf("\n");

		printf("%02x ",(unsigned char) val_ch);
		
		serial_index++;*/
		fflush(stdout);
	}
	
	
	close(binary_fd);
	close(serial_fd);

	return 0;
}
