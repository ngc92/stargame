#ifndef CONSTS_H_INCLUDED
#define CONSTS_H_INCLUDED

constexpr const float STEPS_PER_SECOND = 50;
constexpr const float STEP_TIME = 1.f / STEPS_PER_SECOND;

// max movement per step in box is 2, so default units give 100 m/s max speed

constexpr const float BOX_TO_METERS = 2;
constexpr const float BOX_TO_KILOGRAM = 1;
constexpr const float METERS_TO_BOX = 1.f / BOX_TO_METERS;
constexpr const float KILOGRAM_TO_BOX = 1.f / BOX_TO_KILOGRAM;
constexpr const float NEWTON_TO_BOX = KILOGRAM_TO_BOX * METERS_TO_BOX;

#endif // CONSTS_H_INCLUDED
