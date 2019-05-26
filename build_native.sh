

BASE_DIR=$(realpath $(dirname "$0"))

TARGET="linux_amd64"

cd ${BASE_DIR}
mkdir -p build/${TARGET}
cmake -H. -Bbuild/${TARGET} -DTARGET_DEV=${TARGET^^}
cd build/${TARGET}
make $1