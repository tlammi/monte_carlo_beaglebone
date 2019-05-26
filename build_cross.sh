
BASE_DIR=$(realpath $(dirname "$0"))

TARGET="xenomai_armhf"

source /opt/poky/2.6.1/environment-setup-armv7at2hf-neon-poky-linux-gnueabi

cd ${BASE_DIR}
mkdir -p build/${TARGET}
cmake -H. -Bbuild/${TARGET} -DTARGET_DEV=${TARGET^^}
cd build/${TARGET}
make $1