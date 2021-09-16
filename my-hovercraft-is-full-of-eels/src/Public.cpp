/*
 * This is a sample source file corresponding to a public header file.
 *
 * <Copyright information goes here>
 */

#include <my-hovercraft-is-full-of-eels/Public.hpp>

#include "Private.hpp"

namespace com::saxbophone::my_hovercraft_is_full_of_eels {
    bool library_works() {
        return PRIVATE::library_works();
    }
}
