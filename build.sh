
TARGET_LIST=(

)


print_usage() {
    echo "asdfasdfasdf"
}


if [ $# -gt 1 ] ; then
    print_usage
    exit 1
fi

if [ $# -eq 0 ]; then
    TARGET="all"
else
    TARGET="$1"
fi

cmake -Bbuild -H.
cd build
make


if [ "$#" -ge 1 ] && [ "$1" == "test" ]; then
    test/test

fi
