#pragma once
#include "ErrorHandling\ErrorContext.h"
#include "Timing\Timing.h"

extern Blz::Err::ErrContext ec;
extern Blz::Timing::EngineClock engineClock;

const sfloat c_levelBorderMaxX = 1920.0f;
const sfloat c_levelBorderMaxY = 1080.0f;

const sfloat c_levelBorderMinX = 0.0f;
const sfloat c_groundLevel = 100.0f;