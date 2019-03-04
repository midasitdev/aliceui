curl -L -o temp\glfw.zip https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.bin.WIN64.zip
Powershell -ExecutionPolicy Bypass -Command "& '.\unzip.ps1' 'temp\glfw' 'temp\glfw.zip'"
robocopy /e "temp\glfw\glfw-3.2.1.bin.WIN64" "glfw"
rmdir /s /q "temp\glfw"
del "temp\glfw.zip"
robocopy "glfw\lib-vc2015" "..\..\bin\vc140\Debug\x64" "glfw3.dll"
robocopy "glfw\lib-vc2015" "..\..\bin\vc140\Release\x64" "glfw3.dll"
