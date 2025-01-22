# ======================================= BW =======================================
#   BetterWindows - a solution to make Windows better
# 
# (c) 2024 Gorciu

Write-Host "This is an BetterWindows internal script. If you ran this script manually - close this window." -ForegroundColor Yellow
cmd.exe /c "timeout 5 > nul"

Write-Host "Adding BetterWindows to the PATH variable..." -ForegroundColor Yellow
$env:Path = $env:Path + ";C:\BetterWindows"
