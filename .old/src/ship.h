#pragma once

#include <math.h>
#include <stdbool.h>

#include "../client/window.h"

void ai_control(const ship_t* ship, const float x, const float y, int* thrust, bool* left, bool* right);

static void boid_control(const ship_t* self, const ship_t* flock, size_t flock_count, int* thrust, bool* left, bool* right) {
    float avg_dx = 0, avg_dy = 0;
    float avg_vx = 0, avg_vy = 0;
    float sep_dx = 0, sep_dy = 0;
    int count = 0;

    const float neighbor_radius = 100.0f;
    const float separation_distance = 20.0f;

    for (int i = 0; i < flock_count; ++i) {
        const ship_t* other = &flock[i];
        if (other == self) continue;

        float dx = other->x - self->x;
        float dy = other->y - self->y;

        if (dx > REAL_WIDTH / 2)  dx -= REAL_WIDTH;
        if (dx < -REAL_WIDTH / 2) dx += REAL_WIDTH;
        if (dy > REAL_HEIGHT / 2) dy -= REAL_HEIGHT;
        if (dy < -REAL_HEIGHT / 2) dy += REAL_HEIGHT;

        float dist2 = dx * dx + dy * dy;
        if (dist2 < neighbor_radius * neighbor_radius) {
            avg_dx += dx;
            avg_dy += dy;
            avg_vx += other->vx;
            avg_vy += other->vy;
            ++count;

            if (dist2 < separation_distance * separation_distance) {
                sep_dx -= dx;
                sep_dy -= dy;
            }
        }
    }

    if (count == 0) {
        *thrust = 0;
        *left = *right = false;
        return;
    }

    avg_dx /= count;
    avg_dy /= count;
    avg_vx /= count;
    avg_vy /= count;

    float cohesion_angle = atan2f(avg_dy, avg_dx);
    float alignment_angle = atan2f(avg_vy, avg_vx);
    float separation_angle = atan2(sep_dy, sep_dx);

    float desired_angle = cohesion_angle * 0.4f + alignment_angle * 0.4f + separation_angle * 0.2f;

    float diff = desired_angle - self->angle;
    while (diff > SDL_PI_F)  diff -= 2 * SDL_PI_F;
    while (diff < -SDL_PI_F) diff += 2 * SDL_PI_F;

    const float angle_threshold = 0.05f;
    *left  = diff < -angle_threshold;
    *right = diff >  angle_threshold;

    *thrust = (fabsf(diff) < 0.3f) ? 1 : 0;
}
