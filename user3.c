#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE "/dev/BSP"

int main() {
	int _open, _ioctl;
	int cmd, flag;
	
	_open = open(DEVICE, O_RDWR);
	if(_open < 0) {
		printf("Fail to open %s!\n", DEVICE);
		return 0;
	}
	
	printf("OK to open %s!\n\n", DEVICE);
	
	printf("0: Quit\n");
	printf("10: Stop thread1\n");
	printf("11: Start thread1\n");
	printf("12: Reset thread1\n");
	printf("20: Stop thread2\n");
	printf("21: Start thread2\n");
	printf("22: Reset thread2\n");
	printf("30: Stop thread1 and thread2\n");
	printf("31: Start thread1 and thread2\n");
	printf("32: Reset thread1 and thread2\n\n");
	
	flag = 1;
	while(1) {
		if(flag == 0) break;
		printf("Input cmd: ");
		scanf("%d", &cmd);
		switch(cmd) {
			case 0:
				flag = 0;
				break;
			case 10:
				_ioctl = ioctl(_open, 10, 0);
				printf("OK to stop thread1!\n");
				break;
			case 11:
				_ioctl = ioctl(_open, 11, 0);
				if(_ioctl == -1) printf("Has already started thread1!\n");
				if(_ioctl == 0) printf("OK to start thread1!\n");
				break;
			case 12:
				_ioctl = ioctl(_open, 12, 0);
				printf("OK to reset thread1!\n");
				break;
			case 20:
				_ioctl = ioctl(_open, 20, 0);
				printf("OK to stop thread2!\n");
				break;
			case 21:
				_ioctl = ioctl(_open, 21, 0);
				if(_ioctl == -1) printf("Has already started thread2!\n");
				if(_ioctl == 0) printf("OK to start thread2!\n");
				break;
			case 22:
				_ioctl = ioctl(_open, 22, 0);
				printf("OK to reset thread2 !\n");
				break;
			case 30:
				_ioctl = ioctl(_open, 30, 0);
				printf("OK to stop thread1 and thread2!\n");
				break;
			case 31:
				_ioctl = ioctl(_open, 31, 0);
				if(_ioctl == -1) printf("Has already started thread1 and thread2!\n");
				if(_ioctl == 1) printf("OK to start thread1, has already started thread2!\n");
				if(_ioctl == 2) printf("OK to start thread2, has already started thread2!\n");
				if(_ioctl == 0) printf("OK to start thread1 and thread2!\n");
				break;
			case 32:
				_ioctl = ioctl(_open, 32, 0);
				printf("OK to reset thread1 and thread2!\n");
				break;
			default:
				printf("ERROR cmd!\n");
				break;
		}
	}
	
	close(_open);
	return 0;
}
