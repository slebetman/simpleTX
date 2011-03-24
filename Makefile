PROJECT = txmod

CPU    = 16F690

SOURCES = $(shell ls *.c)
HEADERS = $(shell ls *.h)

####### modifications should not be necessary below this line #######

CC = /usr/hitech/picc/9.80/bin/picc
HEXFILE = $(PROJECT).hex
CFLAGS = --CHIP=$(CPU) -O$(HEXFILE) --OUTPUT=intel
PROGRAMMER = usbpicprog

$(HEXFILE): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES)

install: $(HEXFILE)
	$(PROGRAMMER) -p$(CPU) -e
	$(PROGRAMMER) -p$(CPU) -w -f=$(HEXFILE) --silent
	$(PROGRAMMER) -p$(CPU) -v -f=$(HEXFILE) --silent

verify:
	$(PROGRAMMER) -p$(CPU) -v -f=$(HEXFILE) --silent

run: $(HEXFILE)
	$(PROGRAMMER) --run

stop:
	$(PROGRAMMER) --stop

clean: tidy
	-rm -f *.hex

tidy:
	-rm -f *.o *.asm *.p *.cod *.lst *.adb *.as *.sym *.p1
	-rm -f *.hxl *.pre *.obj *.rlf *.sdb funclist
