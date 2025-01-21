# BetterWindows - a solution to make Windows better

Windows sucks these days... There are actually people who will use it. You probably don't want to switch to a different operating system, but you want to make it a little better. If that describes you - go and download the project.

## Where it works?

The confirmed to work OSes are:

- Windows 10 22H2 
- Windows 10 22H2 (Insider Preview compilation: **19045.5247**) - causes problems, probably untested and unstable Windows compilation
- Any build of Windows 11

To exit Windows 10's Insider Preview you probably need to reinstall Windows.

To exit Windows 11's Insider Preview you need to wait to a next big update of Windows 11 with option to quit enabled.

## Installing

> [!WARNING]
> If `DISM /Online /Cleanup-Image /ScanHealth` prints something with `The component store`, it means that BetterWindows won't work as good as on a clean device. Please apply cleanup image from Windows installer (eg. `DISM /Online /Cleanup-Image /RestoreHealth /source:WIM:E:\sources\install.wim:1`, change index to your Windows edition and letter to Windows installer) and then check again.

Go to GitHub releases on this project (Releases tab) and download the latest executable.