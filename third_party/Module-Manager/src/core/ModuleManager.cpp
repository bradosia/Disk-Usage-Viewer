/*
 * @name Module Manager
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Manages shared library plugins
 */

#include "ModuleManager.hpp"

// c++17
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

/* boost 1.72.0
 * License: Boost Software License (similar to BSD and MIT)
 */
#include <boost/dll/import.hpp> // for import_alias
#include <boost/shared_ptr.hpp>

namespace bradosia {

  

} // namespace bradosia