ifeq ($(OS),Windows_NT)
    SUFFIX = .exe
else
    $(error Building BetterWindows on AurorOS/Linux/MacOS is kind of useless)
endif

.PHONY: all installer winman installout

all: installer installout

installer:
	g++ installer/main.cpp -o installer/out$(SUFFIX)

winman:
	$(error Actually pretty useless right now)

installout:
	installer/out$(SUFFIX)