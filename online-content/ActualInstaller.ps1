# ======================================= BW =======================================
#   BetterWindows - a solution to make Windows better
# 
# (c) 2024 Gorciu

Write-Host "This is an BetterWindows internal script. If you ran this script manually - close this window." -ForegroundColor Yellow
cmd.exe /c "timeout 5 > nul"

Write-Host "Adding BetterWindows to the PATH variable..." -ForegroundColor Yellow
$env:Path = $env:Path + ";C:\BetterWindows"
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

Write-Host "BetterWindows has been successfully installed!" -ForegroundColor Green