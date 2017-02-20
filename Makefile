# Makefile for f9dasm
# Copyright (C) 2014 Gordon JC Pearce <gordon@gjcp.net>

CC=gcc
CFLAGS=


OBJS =	opcode.o mc68hc11.o mc6809.o mc6309.o f9dasm.o

f9dasm:$(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

opcode.o: opcode.c opcode.h
mc6809.o: mc6809.c mc6809.h
mc6309.o: mc6309.c mc6309.h
mc68hc11.o: mc68hc11.c mc68hc11.h


hex2bin: hex2bin.c
	 $(CC) hex2bin.c -o $@
mot2bin: mot2bin.c
	 $(CC) mot2bin.c -o $@

clean:
	rm mot2bin hex2bin f9dasm

all: f9dasm hex2bin mot2bin
