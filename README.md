# CV_YOLOV4

To get the config, weight and name file: https://drive.google.com/drive/u/1/folders/15x5wlLDIp8QlzBW67mvsaWEV7Er87uz4

Setup tutorial: https://www.ccoderun.ca/DarkHelp/api/Building.html#Linux -->  0:00 - 3:40

Building Darknet

1) (make a directory) 
2) get openCV installed in the same directory (skip if installed)
sudo apt-get install build-essential git libopencv-dev
3) git clone https://github.com/AlexeyAB/darknet.git
4) cd darknet
5) (Go to Makefile) - set GPU, CUDNN, AVX, OPENMP, LIBSO to 1
6) (In the Makefile) - uncomment the line (ARCH = ...) for whichever GPU you use (if you have one)
7) make
8) sudo cp libdarknet.so /usr/local/lib/
9) sudo cp include/darknet.h /usr/local/include/
10) sudo ldconfig

Building Darkhelp (previous directory of darknet)
1) sudo apt-get install cmake build-essential libtclap-dev libmagic-dev libopencv-dev
2) git clone https://github.com/stephanecharette/DarkHelp.git
3) cd DarkHelp
4) mkdir build
5) cd build
6) cmake -DCMAKE_BUILD_TYPE=Release ..
7) make
8) make package 
9) sudo dpkg -i darkhelp-*.deb

Use in the application
1) #include <DarkHelp.hpp>
2) link these libraries: libdarkhelp.a, libdarknet.so, OpenCV with the Make file provided
