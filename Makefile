QMAKE_TARGET  = tibb
QMAKE         = $(QNX_HOST)/usr/bin/qmake
TARGET        = $(QMAKE_TARGET)

.PHONY: all
all: Makefile device simulator

.PHONY: clean
clean:
	$(MAKE) -C ./arm -f Makefile distclean
	$(MAKE) -C ./x86 -f Makefile distclean

.PHONY: Makefile
Makefile: FORCE
	$(QMAKE) -spec unsupported/blackberry-armv7le-g++ -o arm/Makefile $(QMAKE_TARGET).pro CONFIG+=device
	$(QMAKE) -spec unsupported/blackberry-x86-g++ -o x86/Makefile $(QMAKE_TARGET).pro CONFIG+=simulator

.PHONY: FORCE
FORCE:

.PHONY: device
device:
	$(MAKE) -C ./arm -f Makefile all

.PHONY: Device-Debug
Device-Debug: Makefile
	$(MAKE) -C ./arm -f Makefile debug

.PHONY: Device-Release
Device-Release: Makefile
	$(MAKE) -C ./arm -f Makefile release

.PHONY: simulator
simulator:
	$(MAKE) -C ./x86 -f Makefile all

.PHONY: Simulator-Debug
Simulator-Debug: Makefile
	$(MAKE) -C ./x86 -f Makefile debug
