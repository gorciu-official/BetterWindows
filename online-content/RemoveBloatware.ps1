# ======================================= BW =======================================
#   BetterWindows - a solution to make Windows better
# 
# (c) 2024 Gorciu

Write-Host "This is an BetterWindows internal script. If you ran this script manually - close this window." -ForegroundColor Yellow
Write-Host "This script will remove potentially unwanted programs from your Windows installation. If you need some from the"
Write-Host "Microsoft useless apps, please abort BetterWindows installation by X. If you agree, click any key to continue."
cmd.exe /c "pause > nul"

Write-Host "Removing package: Microsoft.GetHelp" -ForegroundColor Magenta
Get-AppxPackage -Name "Microsoft.GetHelp" | Remove-AppxPackage
Write-Host "Removing package: Microsoft.Office.OneNote" -ForegroundColor Magenta
Get-AppxPackage -Name "Microsoft.Office.OneNote" | Remove-AppxPackage
Write-Host "Removing package: Microsoft.OfficeHub" -ForegroundColor Magenta
Get-AppxPackage -Name "Microsoft.OfficeHub" | Remove-AppxPackage
Write-Host "Removing package: Microsoft.ZuneMusic" -ForegroundColor Magenta
Get-AppxPackage -Name "Microsoft.ZuneMusic" | Remove-AppxPackage
Write-Host "Removing package: Microsoft.ZuneVideo" -ForegroundColor Magenta
Get-AppxPackage -Name "Microsoft.ZuneVideo" | Remove-AppxPackage
Write-Host "Removing package: Microsoft.WindowsMaps" -ForegroundColor Magenta
Get-AppxPackage -Name "Microsoft.WindowsMaps" | Remove-AppxPackage
Write-Host "Removing package: Microsoft.MicrosoftSolitaireCollection" -ForegroundColor Magenta
Get-AppxPackage -Name "Microsoft.MicrosoftSolitaireCollection" | Remove-AppxPackage
Write-Host "Removing package: Microsoft.FeedbackHub" -ForegroundColor Magenta
Get-AppxPackage -Name "Microsoft.FeedbackHub" | Remove-AppxPackage

$removeMicrosoftStore = Read-Host "Do you want to remove Microsoft Store? (y/n)"
if ($removeMicrosoftStore -eq 'y') {
    Write-Host "Removing package: Microsoft.WindowsStore" -ForegroundColor Magenta
    Get-AppxPackage -Name "Microsoft.WindowsStore" | Remove-AppxPackage
} else {
    Write-Host "Skipped package: Microsoft.WindowsStore" -ForegroundColor Green
}