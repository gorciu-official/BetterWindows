# ======================================= BW =======================================
#   BetterWindows - a solution to make Windows better
# 
# (c) 2024 Gorciu

Write-Host "This is an BetterWindows internal script. If you ran this script manually - close this window." -ForegroundColor Yellow
cmd.exe /c "timeout 5 > nul"

Write-Host "Adding BetterWindows to the PATH variable..." -ForegroundColor Yellow
[System.Environment]::SetEnvironmentVariable("Path", $env:Path + ";C:\BetterWindows", [System.EnvironmentVariableTarget]::Machine)
Write-Host "Downloading `winman` executable..." -ForegroundColor Yellow
Invoke-WebRequest -Uri "https://raw.githubusercontent.com/TheBetterWindows/BetterWindows/refs/heads/main/online-content/winman.binary.exe" -OutFile "C:\BetterWindows\temp\winman.exe"
Write-Host "Checking checksum..." -ForegroundColor Yellow
$checksum = Get-FileHash "C:\BetterWindows\temp\winman.exe" -Algorithm SHA256
$expectedChecksum = (Invoke-WebRequest -Uri "https://raw.githubusercontent.com/TheBetterWindows/BetterWindows/refs/heads/main/online-content/winman.checksum-sha256.txt").Content.Trim()
if ($checksum.Hash -eq $expectedChecksum) {
    Write-Host "Checksum is valid. Continuing installation..." -ForegroundColor Green
} else {
    Write-Host "Checksum is invalid. Please close BetterWindows installation." -ForegroundColor Red
    while ($true) {
        Start-Sleep -Seconds 5
    }
}
Write-Host "Copying `winman` to the correct location..." -ForegroundColor Yellow
Copy-Item "C:\BetterWindows\temp\winman.exe" "C:\BetterWindows\winman.exe"
Write-Host "Installing required packages..." -ForegroundColor Yellow
cmd.exe /c "C:\BetterWindows\winman.exe -I base"

Write-Host "Adding userinit binary..." -ForegroundColor Yellow
Invoke-WebRequest -Uri "https://raw.githubusercontent.com/TheBetterWindows/BetterWindows/refs/heads/main/online-content/userinit.binary.exe" -OutFile "C:\BetterWindows\userinit.exe"
Write-Host "Registering userinit binary..." -ForegroundColor Yellow
Set-ItemProperty -Path "HKLM:\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon" -Name "Userinit" -Value "C:\BetterWindows\userinit.exe,C:\Windows\system32\userinit.exe," -Force

$restart = Read-Host "Do you want to restart to apply the changes? (y - restart now / n - restart later)"
if ($restart -eq 'y') {
    Reset-Computer -Force
} else {
    Write-Host "BetterWindows needs to restart later to apply changes." -ForegroundColor Green
    Start-Sleep -Seconds 120
}