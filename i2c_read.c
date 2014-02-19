// Frontend for i2c ethersex

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define Buffer 20

void print_usage(int exval) {
	printf("\nUsage: i2c_ecmd options\n");
	printf("\n-v Verbose");
	printf("\n-h Print this help");
	printf("\n-d DEVICE i.e /dev/i2c-2");
	printf("\n-c esex cmd i.e hostname\n\n");
	exit(exval);
}

int main(int argc, char *argv[]) {
	int File;
	char Device[] = "/dev/i2c-1";
	char Ethersex = 0x08;
	char CMD[50] = "";
	int len;
	char Data[Buffer];
	int i;
	int Debug = 1;
	int opt;
	unsigned int zaehler;

	if (argc == 1) {
		print_usage(1);
	}
	while ((opt = getopt(argc, argv, "?hvd:c:")) != -1) {
		switch (opt) {
		case '?':
		case 'h':
			print_usage(0);
			break;
		case 'v':
			Debug = 1;
			break;
		case 'd':
			strcpy(Device, optarg);
			break;
		case 'c':
			strcpy(CMD, optarg);
			break;
		case ':':
			fprintf(stderr, "i2c_read: Error - Option `%c' needs a value\n\n",
					optopt);
			print_usage(1);
			break;
		}
	}
	if (Debug) {
		printf("\nDevice: %s,Command: %s\n", Device, CMD);
	}
	// Start of Program
	len = strlen(CMD);

	if ((File = open(Device, O_RDWR)) < 0) 					// I²C aktivieren
			{
		printf("I²C Modul kann nicht geladen werden!\n");
		return -1;
	}

	if (ioctl(File, I2C_SLAVE, Ethersex) < 0) {
		printf("Deviceadresse wurde nicht gefunden!\n");
		exit(1);
	}

	/*if (write(File, CMD, len + 1) != len + 1) {
	 printf("Fehler beim Schreiben der Daten!\n");
	 return -1;
	 }
	 //sleep(1);
	 Data[0]=0;
	 if (read(File, Data, Buffer) != Buffer) {
	 printf("Fehler beim Lesen der Daten!\n");
	 return -1;
	 } else {
	 if (Debug) {
	 printf("Buffer:\n");
	 // Werte vom Buffer lesen
	 for (i = 0; i < 4; i++) {
	 printf("%2d: 0x%0x ", i, (Data[i] & 0xff));

	 }
	 printf("\n");
	 }

	 }*/
	for (i = 0; i < 4; i++) {
		Data[i] = i2c_smbus_read_word_data(File, i);
		if (Data[i] < 0) {
			printf("Error\n");
		} else {
			printf("%d: 0x%0x ",i, Data[i]);
		}
		
	}
	printf("\n");
	close(File);
	return 0;
}
