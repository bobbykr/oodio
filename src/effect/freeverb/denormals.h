/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Macro for killing denormalled numbers
 *
 * Written by Jezar at Dreampoint, June 2000
 * http://www.dreampoint.co.uk
 * Based on IS_DENORMAL macro by Jon Watte
 * This code is public domain
 */

#ifndef DENORMALS_H
#define DENORMALS_H

#include <stdint.h>  // integer type aliases


#define UNDENORMALISE(sample) if (((*(uint32_t*)&sample) & 0x7f800000) == 0) sample = 0.0f
#define DOUBLE_DENORM(sample) if (((*(uint64_t*)&sample) & 0x7ff0000000000000) == 0) sample = 0.0

#endif

