﻿#include <stdio.h>
#include <stdlib.h>  // chg akihito
#include <unistd.h>         /* for read, write, close */
#include <sys/ioctl.h>      /* for ioctl */
#include <sys/types.h>      /* for open */
#include <sys/stat.h>       /* for open */
#include <fcntl.h>          /* for open */

#include <signal.h>

#include "driver/urbtc.h"          /* Linux specific part */
#include "driver/urobotc.h"        /* OS independent part */

#define SPEED      500
#define WHEEL_ZERO 1024


void setup_motor(struct uin *ibuf, struct uout *obuf, struct ccmd *cmd);

void go_straight(struct ccmd *cmd, unsigned short speed, int front);
void left_wheel(struct ccmd *cmd, unsigned short speed);
void right_wheel(struct ccmd *cmd, unsigned short speed);

void turn(struct ccmd *cmd, unsigned short speed, int left);

void stop(struct ccmd *cmd);


int         quit_flag = 1;
int         fd;
struct uin  ibuf;
struct uout obuf;
struct ccmd cmd;


void g_init()
{
    setup_motor(&ibuf, &obuf, &cmd);
    stop(&cmd);
}

void g_go_straight(int front, unsigned short speed)
{
    go_straight(&cmd, speed, front);
}

void g_left_wheel(unsigned short speed)
{
    left_wheel(&cmd, speed);
}

void g_right_wheel(unsigned short speed)
{
    right_wheel(&cmd, speed);
}

void g_turn(int left, unsigned short speed)
{
    turn(&cmd, speed, left);
}

void g_stop()
{
    stop(&cmd);
}

void g_quit()
{
    stop(&cmd);
    close(fd);
}

void setup_motor(struct uin *ibuf, struct uout *obuf, struct ccmd *cmd)
{
    int   i   = 0;
    char *dev = "/dev/urbtc0";

    if ((fd = open(dev, O_RDWR)) == -1) {
        fprintf(stderr, "%s: Open error\n", dev);
        exit(1);
    }
    cmd->retval     = 0 /* RETURN_VAL */;
    cmd->setoffset  = CH0 | CH1 | CH2 | CH3;
    cmd->setcounter = CH0 | CH1 | CH2 | CH3;
    cmd->resetint   = CH0 | CH1 | CH2 | CH3;

    cmd->selin = CH0 | CH1 | CH2 | CH3 | SET_SELECT;

    #if 0
        cmd->dout = DOUT0 | DOUT1 | DOUT2 | DOUT3; /*digital out (ON/OFF out)*/
    #endif
    cmd->dout = 0;

    cmd->selout = SET_SELECT | CH0 | CH1 | CH2 | CH3; /* EEPROM $B%G!<%?$,@5$7$1$l$PITMW(B */

    /*---$B3F%A%c%s%M%k$N%*%U%;%C%HCM$N@_Dj(B---*/
    #if __BYTE_ORDER ==  __LITTLE_ENDIAN
        cmd->offset[0]  = cmd->offset[1] = cmd->offset[2] = cmd->offset[3] = 0x7fff;
        cmd->counter[0] = cmd->counter[1] = cmd->counter[2] = cmd->counter[3] = 0;
        cmd->magicno    = 0x00;
    #else
        cmd->offset[0]  = cmd->offset[1] = cmd->offset[2] = cmd->offset[3] = 0xff7f;
        cmd->counter[0] = cmd->counter[1] = cmd->counter[2] = cmd->counter[3] = 0;
        cmd->magicno    = 0x00;
    #endif

    cmd->posneg = SET_POSNEG | CH0 | CH1 | CH2 | CH3;
    cmd->breaks = SET_BREAKS | CH0 | CH1 | CH2 | CH3;

    cmd->wrrom = 0; /* WR_MAGIC | WR_OFFSET | WR_SELOUT;*/

    /*---ccmd$B$N%b!<%I$K@Z$jBX$($k(B---*/
    /*---$B0J8e!$(Bccmd$B%b!<%I$K@Z$jBX$($i$l$k$^$G!$%b!<%I$O0];}$5$l$k(B---*/
    if (ioctl(fd, URBTC_COUNTER_SET) < 0) {
        fprintf(stderr, "ioctl: URBTC_COUNTER_SET error\n");
        exit(1);
    }
    // printf("sizeof(cmd) %d\n", sizeof(cmd));

    /*---ccmd$B$NCM$r(BH8$B$K=q$-9~$`(B---*/
    if (write(fd, cmd, sizeof(cmd)) < 0) {
        fprintf(stderr, "write error\n");
        exit(1);
    }

    #if 0
        /*set scmd mode*/
        if (ioctl(fd, URBTC_DESIRE_SET) < 0) {
            fprintf(stderr, "ioctl: URBTC_DESIRE_SET error\n");
            exit(1);
        }
    #endif

    for (i = 0; i < 4; i++) {
        #if __BYTE_ORDER ==  __LITTLE_ENDIAN
            obuf->ch[i].x   = 0;
            obuf->ch[i].d   = 0;
            obuf->ch[i].kp  = 0;
            obuf->ch[i].kpx = 1;
            obuf->ch[i].kd  = 0;
            obuf->ch[i].kdx = 1;
            obuf->ch[i].ki  = 0;
            obuf->ch[i].kix = 1;
        #else
            obuf->ch[i].x   = 0;
            obuf->ch[i].d   = 0;
            obuf->ch[i].kp  = 0;
            obuf->ch[i].kpx = 0x0100;
            obuf->ch[i].kd  = 0;
            obuf->ch[i].kdx = 0x0100;
            obuf->ch[i].ki  = 0;
            obuf->ch[i].kix = 0x0100;
        #endif
    }
}

void go_straight(struct ccmd *cmd, unsigned short speed, int front)
{
    unsigned short a = WHEEL_ZERO;
    unsigned short b = WHEEL_ZERO;

    if (front) {
        a += speed;
        b -= speed;
    } else {
        a -= speed;
        b += speed;
    }
    a <<= 5;
    b <<= 5;

    cmd->offset[1] = a;
    cmd->offset[2] = b;

    if (ioctl(fd, URBTC_COUNTER_SET) < 0) {
        fprintf(stderr, "ioctl: URBTC_COUNTER_SET error\n");
        exit(1);
    }

    if (write(fd, cmd, sizeof(*cmd)) <= 0) {
        fprintf(stderr, "write cmd error\n");
        exit(1);
    }
}

void left_wheel(struct ccmd *cmd, unsigned short speed)
{
    unsigned short a = WHEEL_ZERO;
    a             += speed;
    a            <<= 5;
    cmd->offset[1] = a;

    if (ioctl(fd, URBTC_COUNTER_SET) < 0) {
        fprintf(stderr, "ioctl: URBTC_COUNTER_SET error\n");
        exit(1);
    }

    if (write(fd, cmd, sizeof(*cmd)) <= 0) {
        fprintf(stderr, "write cmd error\n");
        exit(1);
    }
}

void right_wheel(struct ccmd *cmd, unsigned short speed)
{
    unsigned short a = WHEEL_ZERO;

    a  += speed;
    a <<= 5;

    cmd->offset[2] = a;

    if (ioctl(fd, URBTC_COUNTER_SET) < 0) {
        fprintf(stderr, "ioctl: URBTC_COUNTER_SET error\n");
        exit(1);
    }

    if (write(fd, cmd, sizeof(*cmd)) <= 0) {
        fprintf(stderr, "write cmd error\n");
        exit(1);
    }
}

void turn(struct ccmd *cmd, unsigned short speed, int left)
{
    unsigned short a = WHEEL_ZERO;
    unsigned short b = WHEEL_ZERO;

    if (left) {
        a -= speed;
        b -= speed;
    } else {
        a += speed;
        b += speed;
    }
    a <<= 5;
    b <<= 5;

    cmd->offset[1] = a;
    cmd->offset[2] = b;

    if (ioctl(fd, URBTC_COUNTER_SET) < 0) {
        fprintf(stderr, "ioctl: URBTC_COUNTER_SET error\n");
        exit(1);
    }

    if (write(fd, cmd, sizeof(*cmd)) <= 0) {
        fprintf(stderr, "write cmd error\n");
        exit(1);
    }
}

void stop(struct ccmd *cmd)
{
    unsigned short zero = WHEEL_ZERO;
    zero         <<= 5;
    cmd->offset[1] = zero;
    cmd->offset[2] = zero;
    write(fd, cmd, sizeof(*cmd));
}
