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
export FC=ifort
export CC=icx
export CXX=icpx

# Build PCL
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg && ./bootstrap-vcpkg.sh
export VCPKG_ROOT=`pwd`
export PATH=$VCPKG_ROOT:$PATH
cd ..
vcpkg install pcl --x-install-root=pcl
export PKG_CONFIG_PATH=`pwd`/vcpkg/pcl/x64-linux/lib/pkgconfig:$PKG_CONFIG_PATH