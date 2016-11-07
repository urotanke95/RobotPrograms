CC = gcc
CFLAGS = -o -Wall

urobotm: urobotm.c
	$(CC) $(CFLAGS) -o $@ $< -lm

urobot_1ch_enc_pos: urobot_1ch_enc_pos.c
	$(CC) $(CFLAGS) -o $@ $< -lm

urobot_enc_pos: urobot_enc_pos.c
	$(CC) $(CFLAGS) -o $@ $< -lm

urobot_enc_pos_mod: urobot_enc_pos_mod.c
	$(CC) $(CFLAGS) -o $@ $< -lm

urobot_enc_pos_mod2: urobot_enc_pos_mod2.c
	$(CC) $(CFLAGS) -o $@ $< -lm

urobotc_ad: urobotc_ad.c
	$(CC) $(CFLAGS) -o $@ $< -lm

urobotc_open_loop: urobotc_open_loop.c
	$(CC) $(CFLAGS) -o $@ $< -lm

urobotc_open_loop_r: urobotc_open_loop_r.c
	$(CC) $(CFLAGS) -o $@ $< -lm
