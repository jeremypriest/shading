# FSL modules
module load intel-oneapi/2023.2.4
module load python/3.12

# Make venv
python3 -m venv .venv
source .venv/bin/activate
pip install --upgrade pip

# Meson
pip install meson cmake ninja
# brew install pkg-config

# Use Intel suite of compilers
module load intel-oneapi/2023.2.4
export FC=ifort
export CC=icx
export CXX=icpx

# module load gcc/14.2.0
# export FC=gfortran
# export CC=gcc
# export CXX=g++

# Build PCL
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg && ./bootstrap-vcpkg.sh
export VCPKG_ROOT=`pwd`
export PATH=$VCPKG_ROOT:$PATH
cd ..
vcpkg install pcl --x-install-root=pcl # --binarysource=clear
export PKG_CONFIG_PATH=`pwd`/pcl/x64-linux/lib/pkgconfig:$PKG_CONFIG_PATH
# export PKG_CONFIG_PATH=`pwd`/pcl/x64-linux/debug/lib/pkgconfig:$PKG_CONFIG_PATH