#include "buildcntrl.hpp"
#include "fal/sys.hpp"


#if defined(TARGET_DEV_LINUX_AMD64)

namespace fal{
namespace sys{

int init(){
    return 0;
}

int deinit(){
    return 0;
}
}
}

#elif defined(TARGET_DEV_XENOMAI_ARMHF)


#else
#pragma error "Invalid target system"
#endif