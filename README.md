# OpenGL CarGUI C++ with Qt
![alt text](img/figure/demo.gif)
## Deployable on these OS
- Ubuntu 22.04
- Raspberry Pi OS
- l4t Ubuntu 22.04 (from Jetpack 6.2)
## Install requirements
### Qt 
```
sudo apt install qt6-base-dev qt6-tools-dev cmake g++ ninja-build
```   
### OpenCV
```
sudo apt install libopencv-dev
```

## Usage
Use cmake to generate Makefile
```
mkdir build
cd build
cmake .
```
Build the program
```
make
```
Start up the program
```
./build/SmartDash
boardSystem
```
For generating dummy data to this program, please clone [this](https://github.com/eddy0117/OpenGL_CarGUI_Qt_Cpp) repository and refer the [tutorial](https://github.com/eddy0117/OpenGL_CarGUI_Cpp/blob/main/docs/datasender.md).
