#include "ship.h"

#include <math.h>
#include "../client/window.h"

void ai_control(const ship_t* ship, const float x, const float y, int* thrust, bool* left, bool* right) {
    float dx = x - ship->x;
    float dy = y - ship->y;

    if (dx > REAL_WIDTH / 2) dx -= REAL_WIDTH;
    if (dx < -REAL_WIDTH / 2) dx += REAL_WIDTH;
    if (dy > REAL_HEIGHT / 2) dy -= REAL_HEIGHT;
    if (dy < -REAL_HEIGHT / 2) dy += REAL_HEIGHT;

    const float distance = sqrtf(dx * dx + dy * dy);

    const float desired_angle = atan2f(dy, dx);

    float diff = desired_angle - ship->angle;
    while (diff > SDL_PI_F) diff -= 2 * SDL_PI_F;
    while (diff < -SDL_PI_F) diff += 2 * SDL_PI_F;

    const float angle_threshold = 0.05f;
    *left = diff < -angle_threshold;
    *right = diff > angle_threshold;

    *thrust = 0;

    if (fabsf(diff) < 0.3f && distance > 40.0f) {
        *thrust = 1;
    }
    else if (fabsf(diff) > 2.0f && distance < 80.0f) {
        *thrust = -1;
    }
}