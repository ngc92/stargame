#ifndef CONSTS_H_INCLUDED
#define CONSTS_H_INCLUDED

const float STEPS_PER_SECOND = 50;
const float STEP_TIME = 1.f / STEPS_PER_SECOND;

// max movement per step in box is 2, so default units give 100 m/s max speed

const float BOX_TO_METERS = 2;
const float BOX_TO_KILOGRAM = 1;
const float METERS_TO_BOX = 1.f / BOX_TO_METERS;
const float KILOGRAM_TO_BOX = 1.f / BOX_TO_KILOGRAM;

#endif // CONSTS_H_INCLUDED
