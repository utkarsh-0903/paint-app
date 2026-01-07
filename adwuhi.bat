@echo off
echo ==============================
echo Git daily sync started
echo ==============================

echo.
echo Pulling latest changes...
git pull

echo.
set /p msg="Enter commit message: "

echo.
echo Adding files...
git add .

echo.
echo Committing...
git commit -m "%msg%"

echo.
echo Pushing to GitHub...
git push

echo.
echo ==============================
echo Done. Press any key to exit.
echo ==============================
pause >nul
