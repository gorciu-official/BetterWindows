ifeq ($(OS),Windows_NT)
    SUFFIX = .exe
else
    $(error Building BetterWindows on AurorOS/Linux/MacOS is kind of useless)
endif

.PHONY: all installer winman installout

all: installer installout

installer:
	windres installer/app.rc -o installer/app_res.o
	g++ installer/main.cpp installer/app_res.o -o installer/out$(SUFFIX)

winman:
	$(error Actually pretty useless right now)

installout:
	installer/out$(SUFFIX)