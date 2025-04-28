# OpenGL CarGUI C++ with Qt
![alt text](img/figure/demo.gif)
## OS requirement
- Ubuntu 22.04
- Raspberry Pi OS
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