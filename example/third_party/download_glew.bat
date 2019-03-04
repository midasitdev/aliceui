curl -L -o temp\glew.zip https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip/download
Powershell -ExecutionPolicy Bypass -Command "& '.\unzip.ps1' 'temp\glew' 'temp\glew.zip'"
robocopy /e "temp\glew\glew-2.1.0" "glew"
rmdir /s /q "temp\glew"
del "temp\glew.zip"
robocopy "glew\bin\Release\x64" "..\..\bin\vc140\Debug\x64" "glew32.dll"
robocopy "glew\bin\Release\x64" "..\..\bin\vc140\Release\x64" "glew32.dll"
