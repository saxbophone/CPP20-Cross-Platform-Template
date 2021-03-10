/**
 * This is a sample source file corresponding to a public header file.
 *
 * <Copyright information goes here>
 */

#include <project/Public.hpp>

#include "Private.hpp"

namespace com::saxbophone::project {
    bool library_works() {
        return PRIVATE::library_works();
    }
}
