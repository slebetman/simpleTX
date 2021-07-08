PROJECT = simpleTX

CPU    = 18F2520

SOURCES = $(shell ls *.c */*.c)
HEADERS = $(shell ls *.h */*.h)

####### modifications should not be necessary below this line #######

CC = xc8
HEXFILE = $(PROJECT).hex
CFLAGS = --chip=$(CPU) -O$(HEXFILE) --output=intel
PROGRAMMER = usbpicprog

$(HEXFILE): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES)

install: $(HEXFILE)
	$(PROGRAMMER) -p$(CPU) -e
	$(PROGRAMMER) -p$(CPU) -w -f=$(HEXFILE) --silent
	$(PROGRAMMER) -p$(CPU) -v -f=$(HEXFILE) --silent

verify:
	$(PROGRAMMER) -p$(CPU) -v -f=$(HEXFILE) --silent

run:
	$(PROGRAMMER) --run

stop:
	$(PROGRAMMER) --stop

backup:
	$(PROGRAMMER) --stop
	$(PROGRAMMER) -p$(CPU) --read -f=backup_hex --silent

restore:
	$(PROGRAMMER) -p$(CPU) -e
	$(PROGRAMMER) -p$(CPU) -w -f=backup_hex --silent
	$(PROGRAMMER) -p$(CPU) -v -f=backup_hex --silent

clean: tidy
	-rm -f *.hex

tidy:
	-rm -f *.o *.asm *.p *.cod *.lst *.adb *.as *.sym *.p1
	-rm -f *.hxl *.pre *.obj *.rlf *.sdb funclist *.cmf *.d
