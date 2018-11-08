PROJECT = toy-car

CPU    = 18F2520

SOURCES = $(shell ls *.c)
HEADERS = $(shell ls *.h)

####### modifications should not be necessary below this line #######

CC = xc8
HEXFILE = $(PROJECT).hex
CFLAGS = --chip=$(CPU) -O$(HEXFILE) --output=intel
PROGRAMMER = usbpicprog

$(HEXFILE): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES)

install: $(HEXFILE)
	./splice_trim_data.tcl
	$(PROGRAMMER) -p$(CPU) -e
	$(PROGRAMMER) -p$(CPU) -w -f=$(HEXFILE) --silent
	$(PROGRAMMER) -p$(CPU) -v -f=$(HEXFILE) --silent

verify:
	$(PROGRAMMER) -p$(CPU) -v -f=$(HEXFILE) --silent

run: $(HEXFILE)
	$(PROGRAMMER) --run

stop:
	$(PROGRAMMER) --stop

backup:
	$(PROGRAMMER) -p$(CPU) --read -f=backup_hex --silent

clean: tidy
	-rm -f *.hex

tidy:
	-rm -f *.o *.asm *.p *.cod *.lst *.adb *.as *.sym *.p1
	-rm -f *.hxl *.pre *.obj *.rlf *.sdb funclist *.cmf *.d
