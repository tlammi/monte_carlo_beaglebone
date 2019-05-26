/**
 * @file sys.hpp
 * @author tlammi (tlammi@github.com)
 * @brief Firmware access for system management
 * @version 0.1
 * @date 2019-05-26
 *
 * @copyright Copyright (c) 2019
 *
*/

#ifndef FAL_SYS_HPP_
#define FAL_SYS_HPP_

namespace fal{
/**
 * @brief Firmware Access Layer management
 *
 * Namespace providing utilities for configuring FAL
 *
 */
namespace sys{

    /**
     * @brief Init FAL
     *
     * @return 0 on successs, positive on warning, negative on error
     */
    int init();
    /**
     * @brief Frees the resources of FAL
     *
     * @return 0 on success, positive on warning, negative on error
     */
    int deinit();
}
}

#endif  // FAL_SYS_HPP_