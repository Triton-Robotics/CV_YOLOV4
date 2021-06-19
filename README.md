# CV_YOLOV4

To get the config, weight and name file: https://drive.google.com/drive/u/1/folders/15x5wlLDIp8QlzBW67mvsaWEV7Er87uz4

Setup tutorial: https://www.ccoderun.ca/DarkHelp/api/Building.html#Linux -->  0:00 - 3:40

## CUDA >= 10.2 
Download CUDA: https://developer.nvidia.com/cuda-toolkit-archive
Tutorial: https://docs.nvidia.com/cuda/cuda-installation-guide-linux/index.html#post-installation-actions

## cuDNN >= 8.0.2
Download cuDNN: https://developer.nvidia.com/rdp/cudnn-archive
Tutorial: https://docs.nvidia.com/deeplearning/cudnn/install-guide/index.html#installlinux-tar

## Building Darknet

1) (make a directory) 
2) get openCV installed in the same directory (skip if installed)
sudo apt-get install build-essential git libopencv-dev
3) git clone https://github.com/AlexeyAB/darknet.git
4) cd darknet
5) (Go to Makefile) - set GPU, CUDNN, AVX, OPENMP, LIBSO to 1 (if you have GPU, if not, see the Makefile explaination)
6) (In the Makefile) - uncomment the line (ARCH = ...) for whichever GPU you use (if you have one)
7) make
8) sudo cp libdarknet.so /usr/local/lib/
9) sudo cp include/darknet.h /usr/local/include/
10) sudo ldconfig

## Building Darkhelp (previous directory of darknet)
1) sudo apt-get install cmake build-essential libtclap-dev libmagic-dev libopencv-dev
2) git clone https://github.com/stephanecharette/DarkHelp.git
3) cd DarkHelp
4) mkdir build
5) cd build
6) cmake -DCMAKE_BUILD_TYPE=Release ..
7) make
8) make package 
9) sudo dpkg -i darkhelp-*.deb

## Use in the application
1) #include <DarkHelp.hpp>
2) link these libraries: libdarkhelp.a, libdarknet.so, OpenCV with the Make file provided


## To use the Cmake
1) cd into the build directory (make sure all the previous steps are finish)
2) cmake ..

## To use the make in the build directory
1) make

## To use the detector in the build directory
input format: ./detector "config file" "weights file" "name file" "input name"
