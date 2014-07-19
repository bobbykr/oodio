/**▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
 * Reverb model tuning values
 *
 * Written by Jezar at Dreampoint, June 2000
 * http://www.dreampoint.co.uk
 * This code is public domain
 */

#ifndef TUNING_H
#define TUNING_H

const int    numCombs       = 8;
const int    numAllpasses   = 4;
const int    stereoSpread   = 23;

const double muted          = 0.0;
const double fixedGain      = 0.015;

const double scaleWet       = 3.0;
const double scaleDry       = 2.0;
const double scaleDamp      = 0.4;
const double scaleRoom      = 0.28;
const double offsetRoom     = 0.7;

const double initialRoom    = 0.5;
const double initialDamp    = 0.5;
const double initialWet     = 0.1 / scaleWet;
const double initialDry     = 0.0;
const double initialWidth   = 1.0;
const double initialMode    = 0.0;

const double freezeMode     = 0.5;


// These values assume 44.1KHz sample rate
// they will probably be OK for 48KHz sample rate
// but would need scaling for 96KHz (or other) sample rates.
// The values were obtained by listening tests.
const int combTuningL1      = 1116;
const int combTuningR1      = 1116 + stereoSpread;
const int combTuningL2      = 1188;
const int combTuningR2      = 1188 + stereoSpread;
const int combTuningL3      = 1277;
const int combTuningR3      = 1277 + stereoSpread;
const int combTuningL4      = 1356;
const int combTuningR4      = 1356 + stereoSpread;
const int combTuningL5      = 1422;
const int combTuningR5      = 1422 + stereoSpread;
const int combTuningL6      = 1491;
const int combTuningR6      = 1491 + stereoSpread;
const int combTuningL7      = 1557;
const int combTuningR7      = 1557 + stereoSpread;
const int combTuningL8      = 1617;
const int combTuningR8      = 1617 + stereoSpread;

const int allpassTuningL1   = 556;
const int allpassTuningR1   = 556 + stereoSpread;
const int allpassTuningL2   = 441;
const int allpassTuningR2   = 441 + stereoSpread;
const int allpassTuningL3   = 341;
const int allpassTuningR3   = 341 + stereoSpread;
const int allpassTuningL4   = 225;
const int allpassTuningR4   = 225 + stereoSpread;

#endif

