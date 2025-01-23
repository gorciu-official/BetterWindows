ifeq ($(OS),Windows_NT)
    SUFFIX = .exe
else
    $(error Building BetterWindows on AurorOS/Linux/MacOS is kind of useless)
endif

.PHONY: all installer winman installout winman-nonce

all: installer installout

installer:
	windres installer/app.rc -o installer/app_res.o
	g++ -m64 installer/main.cpp installer/app_res.o -o installer/out$(SUFFIX)

winman:
	g++ winman/main.cpp -o winman/out$(SUFFIX)

installout:
	installer/out$(SUFFIX)

winman-nonce:
	@certutil -hashfile online-content\winman.binary.exe SHA256