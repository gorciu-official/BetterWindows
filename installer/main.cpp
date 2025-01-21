/**
 * ======================================= BW =======================================
 *   BetterWindows - a solution to make Windows better
 * 
 * (c) 2024 Gorciu
 */

// ACT 1: PREPROCESSOR

#ifdef __linux__
#error Building BetterWindows on Linux is kind of useless
#endif 

#ifndef _WIN32
#error Building BetterWindows on AurorOS/Linux/MacOS is kind of useless
#endif 

#include <iostream>
#include <fstream>
#include <windows.h>

// ACT 2: INTERNALS

void print(std::string something) {
    std::cout << something;
}

void println(std::string something) {
    std::cout << something << std::endl;
}

void printnl() {
    println("\n");
}

void setConsoleColor(int fg = 0x0F, int bg = 0) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)((bg << 4) | fg)); 
}

void restartTerminal() {
    setConsoleColor();
    system("cls");
}

std::string read(std::string prefix) {
    std::cout << prefix;
    std::string result;
    std::getline(std::cin, result);
    return result;
}

// ACT 3: INSTALLER

int main() {
    while (true) {
        restartTerminal();
        setConsoleColor(0x0f, 1);
        println("BetterWindows - a solution to make Windows better, without need for reinstall");
        setConsoleColor();
        printnl();
        println("Windows sucks these days... There are actually people who will use it.");
        println("You probably don't want to switch to a different operating system, but you want");
        println("to make it a little better. If that describes you - go and use my project.");
        printnl();
        setConsoleColor(8);
        print("1) ");
        setConsoleColor();
        println("Install BetterWindows");
        setConsoleColor(8);
        print("2) ");
        setConsoleColor();
        println("Quit from this installer");

        std::string sel = read("# ");
        if (sel == "1") {
            system("md C:\\BetterWindows\\temp\\installer");
            system("curl -s -L https://raw.githubusercontent.com/gorciu-official/BetterWindows/refs/heads/main/online-content/RemoveBloatware.ps1 -o C:\\BetterWindows\\temp\\installer\\bloatwareremover.ps1");
            system("C:\\BetterWindows\\temp\\installer\\bloatwareremover.ps1");
            break;
        } else if (sel == "2") {
            break;
        } else {
            MessageBoxExA(NULL, "The option that you selected is invalid.", "Invalid option", MB_OK | MB_ICONINFORMATION, 0);
        }
    }
    return 0;
}