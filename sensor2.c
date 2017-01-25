#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <wiringPi.h>

#define    TRIG_PIN    17
#define    ECHO_PIN    27
#define    MEASURE_INTERVAL    1

int
pulseIn(
    int pin,
    int level,
    int timeout
) {
    struct timeval tn, t0, t1;
    long micros;

    memset(&tn, 0, sizeof(struct timeval));
    memset(&t1, 0, sizeof(struct timeval));

    gettimeofday(&t0, NULL);
    micros = 0;
    while (digitalRead(pin) != level)
    {
        gettimeofday(&tn, NULL);
        if (tn.tv_sec > t0.tv_sec) {
            micros = 1000000L;
        } else {
            micros = 0;
        }
        micros += (tn.tv_usec - t0.tv_usec);
        if (micros > timeout) {
            return 0;
        }
    }

    gettimeofday(&t1, NULL);
    while (digitalRead(pin) == level)
    {
        gettimeofday(&tn, NULL);
        if (tn.tv_sec > t0.tv_sec) {
            micros = 1000000L;
        } else {
            micros = 0;
        }
        micros = micros + (tn.tv_usec - t0.tv_usec);
        if (micros > timeout) {
            return 0;
        }
    }

    if (tn.tv_sec > t1.tv_sec) {
        micros = 1000000L;
    } else {
        micros = 0;
    }
    micros = micros + (tn.tv_usec - t1.tv_usec);
    return (int)micros;
}

void
measure_distance()
{
    int duration, distance;

		/* init sensor*/
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    /* measure distance */
    duration = pulseIn(ECHO_PIN, HIGH, 1000000);
//    printf("duration=%d\n",duration);
    distance = (duration/2) / 29.1;
    printf("distance=%d cm\n",distance);
}

int
main (
    int argc,
    char **argv
) {
    int i;

    if(wiringPiSetupGpio() == -1) {
        return 1;
    }
    pinMode(TRIG_PIN,OUTPUT);
    pinMode(ECHO_PIN,INPUT);

    for(i=0; i<10; i++) {
        measure_distance();
        sleep(MEASURE_INTERVAL);
    }
    return(EXIT_SUCCESS);
}
