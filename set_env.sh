# Make venv
python3 -m venv .venv
source .venv/bin/activate

# Use gcc suite of compilers
export FC=gfortran
export CC=gcc-15
export CXX=g++-15

# Meson
pip install meson cmake ninja
brew install pkg-config