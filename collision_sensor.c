﻿#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "/usr/include/linux/i2c-dev.h"
#include "signal.h"
#include "move_api.h"


void quit_func();

int quit_flg = 0;

int main(void)
{
    int  fd1, fd2;
    char filename[ 20 ];
    char buf[ 10 ];
    int  res;
    int  range = 0;

    // set signal handler
    signal(SIGINT, quit_func);

    // I2Cデータバスをオープン
    sprintf(filename, "/dev/i2c-1");

    // 一つ目
    fd1 = open(filename, O_RDWR);
    if (fd1 < 0) {
        printf("Error on open\n");
        exit(1);
    }
    if (ioctl(fd1, I2C_SLAVE, (0xE2 >> 1) ) < 0) {  // 0xE0(0x11100000) >> 1 = 0x70(0x01110000)
        printf("Error on slave address 0xE2\n");
        exit(1);
    }

    // 二つ目
    fd2 = open(filename, O_RDWR);
    if (fd2 < 0) {
        printf("Error on open\n");
        exit(1);
    }

    if (ioctl(fd2, I2C_SLAVE, (0xE2 >> 1) ) < 0) {  // 0xE0(0x11100000) >> 1 = 0x70(0x01110000)
        printf("Error on slave address 0xE2\n");
        exit(1);
    }

    while (!quit_flg)
    {     // read from 0xE2
        buf[ 0 ] = 0x00;
        buf[ 1 ] = 0x51;

        if ( (write(fd1, buf, 2) ) != 2) {
            printf("0xE2 Error send the read command\n");
            exit(1);
        }
        // Wait for the measurement
        usleep(66000);

        buf[ 0 ] = 0x02;
        if ( (write(fd1, buf, 1) ) != 1) {
            printf("0xE2 Error on select the Range High Byte\n");
            exit(1);
        }

        if ( (read(fd1, buf, 1) ) != 1) {
            printf("0xE2 Error on read the Range High Byte\n");
            exit(1);
        }
        range = buf[ 0 ] << 8;

        buf[ 0 ] = 0x03;
        if ( (write(fd1, buf, 1) ) != 1) {
            printf("0xE2 Error on select the Range Low Byte\n");
            exit(1);
        }

        if ( (read(fd1, buf, 1) ) != 1) {
            printf("0xE2 Error on read the Range Low Byte\n");
            exit(1);
        }
        range |= buf[ 0 ];

        printf("0xE2 Range=%d cm\n", range);
        if (range <= 10) {
            g_stop();
        } else {
            g_go_straight(1, range);
        }
    }

    close(fd1);
    close(fd2);

    return 0;
}

void quit_func()
{
    printf("quit\n");
    quit_flg = 1;
}
