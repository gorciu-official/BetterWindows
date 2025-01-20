/**
 * ======================================= BW =======================================
 *   BetterWindows - a solution to make Windows better, without need for reinstall
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

std::string readlog() {
    std::ifstream file("bw.installer.temp/log.log");

    if (!file.is_open()) {
        return "";
    }

    std::string str;
    std::string file_contents;

    while (std::getline(file, str)) {
        file_contents += str;
        file_contents.push_back('\n');
    }

    file.close();

    return str;
}

void printlog(std::string something) {
    std::ofstream file("bw.installer.temp/log.log");
    if (!file.is_open()) {
        println("Error while trying to use logging.");
        while (true) continue;
        return;
    }

    file << readlog() << something << std::endl;
    file.close();
}

void setConsoleColor(int fg = 0x0F, int bg = 0) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)((bg << 4) | fg)); 
    printlog("[RANDOM] Color changed to " + std::to_string(fg) + " (foreground) and " + std::to_string(bg) + " (background)");
}

void restartTerminal() {
    setConsoleColor();
    system("cls");
    printlog("[RANDOM] Terminal restarted (cleaned)");
}

std::string read(std::string prefix) {
    std::cout << prefix;
    std::string result;
    std::getline(std::cin, result);
    return result;
}

// ACT 3: INSTALLER

int main() {
    system("if not exist bw.installer.temp md bw.installer.temp");
    printlog("[IMPORTANT] New startup of BetterWindows installer");
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
        println("Check \"non-corrupted Windows\" BetterWindows's requirement");
        setConsoleColor(8);
        print("3) ");
        setConsoleColor();
        println("Quit from this installer");

        std::string sel = read("# ");
        if (sel == "3") {
            break;
        } else {
            MessageBoxA(NULL, "Invalid option", "The option that you selected is invalid.", MB_OK | MB_ICONINFORMATION);
        }
    }
    return 0;
}