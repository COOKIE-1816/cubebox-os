PROJDIRS := src

AUXFILES := Makefile README.md CONTRIBUTING.md LICENSE

SRCFILES := $(shell find $(PROJDIRS) -type f -name "\*.c") $(shell find $(PROJDIRS) -type f -name "\*.cpp")
ASMFILES := $(shell find $(PROJDIRS) -type f -name "\*.s")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "\*.h")
LNKFILES := $(shell find $(PROJDIRS) -type f -name "\*.ld")

OBJFILES := $(patsubst %.c,%.o,$(SRCFILES)) $(patsubst %.cpp,%.o,$(SRCFILES)) $(patsubst %.s,%.o,$(SRCFILES))
TSTFILES := $(patsubst %.c,%_t,$(SRCFILES))

DEPFILES    := $(patsubst %.c,%.d,$(SRCFILES)) $(patsubst %.cpp,%.d,$(SRCFILES)) $(patsubst %.s,%.d,$(SRCFILES))
TSTDEPFILES := $(patsubst %,%.d,$(TSTFILES))

ALLFILES := $(SRCFILES) $(HDRFILES) $(ASMFILES) $(AUXFILES)

CC := i686-elf-g++
AS := i686-elf-as
LD := $(CC) -T $(LNKFILES) -o build/bin/ -ffreestanding -O2 -nostdlib $(OBJFILES) -lgcc

.PHONY: all clean dist check testdrivers todolist

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wconversion -Wstrict-prototypes
CFLAGS := -g -std=gnu99 --ffreestanding -O2 -fno-exceptions -fno-rtti $(WARNINGS)

all: pdclib.a

pdclib.a: $(OBJFILES)
	@ar r pdclib.a $?

clean:
	-@$(RM) $(wildcard $(OBJFILES) $(DEPFILES) $(TSTFILES) pdclib.a pdclib.tgz)

dist:
	@tar czf pdclib.tgz $(ALLFILES)

check: testdrivers
	-@rc=0; count=0; \
        for file in $(TSTFILES); do \
            echo " TST     $$file"; ./$$file; \
            rc=`expr $$rc + $$?`; count=`expr $$count + 1`; \
        done; \
	echo; echo "Tests executed: $$count  Tests failed: $$rc"

testdrivers: $(TSTFILES)

-include $(DEPFILES) $(TSTDEPFILES)

todolist:
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -e TODO -e FIXME $$file; done; true

%.o: %.c %.cpp Makefile
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

%.o: %.s Makefile
	@$(AS) $< -o $@

%_t: %.c %.cpp Makefile pdclib.a
	@$(CC) $(CFLAGS) -MMD -MP -DTEST $< pdclib.a -o $@

THISDIR := $(shell basename `pwd`)
TODAY := $(shell date +%Y-%m-%d)
BACKUPDIR := backups/$(TODAY)

backup: clean
	@tar cf - ../$(THISDIR) | 7za a -si ../$(BACKUPDIR)/$(THISDIR).$(TODAY)_`date +%H%M`.tar.7z

