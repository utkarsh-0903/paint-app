@echo off
echo ==============================
echo Saving and pushing changes
echo ==============================

echo.
set /p msg="Enter commit message: "

echo.
git add .

git commit -m "%msg%"

git push

echo.
echo Done. Press any key to exit.
pause >nul


