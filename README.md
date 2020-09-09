@mainpage
# Mars Tractor

# Description
This repository aims to autonomously control a mars tractor for terraforming.

# INSTALLATION

### INSTALL C++ COMPILER
#### Windows:
- Install Visual Studio Community Edition from this link
- [Visual Studio](https://visualstudio.microsoft.com/)

- During installation, click on Desktop development with C++ workload and install.

#### Linux:
 - Type this command in your terminal
 - > sudo apt-get install gcc g++

### INSTALL CMAKE
Windows:
- Install CMake from this link
- [CMake](https://cmake.org/download/)
- Make sure to get the msi installer instead of the source files.

Linux:
- Type this command in your terminal
- > sudo apt-get install cmake

### INSTALL GIT
Windows:
- Install git from this link
- [Git](https://git-scm.com/downloads)
- During installation, leave default/recommended options.


Linux:
- Type this command in your terminal
- > sudo apt-get install git

Both:
- Enter these commands into your terminal with your github username and email
- > git config --global user.name "John Doe"
- > git config --global user.email johndoe@example.com

### INSTALL VCPKG MANAGER
Windows;
1. Clone vcpkg anywhere using command
- > git clone https://github.com/microsoft/vcpkg
1. Type this command in your administrative terminal inside of your vcpkg folder
- > .\bootstrap-vcpkg.bat

Linux:
1. Clone vcpkg anywhere using command
- > git clone https://github.com/microsoft/vcpkg
1. Type this command in your terminal inside of your vcpkg folder
- > ./bootstrap-vcpkg.sh

Both:
1. Type this command to list all available triplets. Determine what triplet your computer is from this list
- > vcpkg help triplet
1. Open a terminal in your vcpkg directory and type these commands to install the dependencies of this repository ( replace the word triplet with your computer's triplet ex. vcpkg install opencv4:x64-windows)
    1. > vcpkg install opencv4:triplet
    1. > vcpkg install opencv4[contrib]:triplet --recurse
    1. > vcpkg install gtest:triplet
    1. > vcpkg install jsoncpp:triplet
    1. > vcpkg install boost-signals2:triplet
    1. > vcpkg install boost-asio:triplet
    1. > vcpkg install qt5-base:triplet

1. Type this command in your terminal inside of the vcpkg directory and copy the path to vcpkg.cmake
    - > vcpkg integrate install
1. Set this path as an environmental variable named VCPKG

### INSTALL DOXYGEN (OPTIONAL)
- Download Doxygen binary installer at [Doxygen](https://www.doxygen.nl/download.html)
- Install doxygen inside your vcpkg directory at vcpkg/downloads/tools/

### INSTALL VISUAL STUDIO CODE
- Download vs code at [VSCode](https://code.visualstudio.com/)
- Inside vs code go to extensions and install the C/C++ extension and the CMake Tools extension

### CONFIGURE PROJECT
1. Clone the project by typing this command in your terminal
    - > git clone https://github.com/stanford-ssi/Mars-Tractor
1. Open the folder in vs code and build the project
