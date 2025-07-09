#include "ship_logic.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

void update_ship(server_state_t* state, ship_t* ship, const float dt) {
    // rotation with inertia
    const float inertia = ship->size * 0.5f;
    if (ship->input_buffer.rotate_left) ship->angular_velocity -= 300.0f * dt / inertia;
    if (ship->input_buffer.rotate_right) ship->angular_velocity += 300.0f * dt / inertia;

    // rotation stuff
    ship->angular_velocity *= 0.9f;
    ship->angle += ship->angular_velocity * dt;

    // traction force
    float acceleration = 10000.0f / ship->size;
    float ax = 0.0f, ay = 0.0f;

    // dashing
    if (ship->dash_timer < 0.0f && ship->dash_cooldown < 0.0f && ship->input_buffer.dash) {
        ship->dash_timer = 0.15f;
        ship->dash_cooldown = DASH_COOLDOWN;
    }

    if (ship->input_buffer.thrust == 1) {
        ax = cosf(ship->angle) * acceleration;
        ay = sinf(ship->angle) * acceleration;
    }
    else if (ship->input_buffer.thrust == -1) {
        ax = -cosf(ship->angle) * acceleration/3;
        ay = -sinf(ship->angle) * acceleration/3;
    }

    // windage
    const float resistance = 0.8f;
    ax -= ship->vx * resistance;
    ay -= ship->vy * resistance;

    // coords update
    ship->vx += ax * dt;
    ship->vy += ay * dt;

    if (ship->dash_timer > 0.0f) {
        ship->vx += cosf(ship->angle) * DASH_BOOST;
        ship->vy += sinf(ship->angle) * DASH_BOOST;
    }

    ship->x += ship->vx * dt;
    ship->y += ship->vy * dt;

    // collision and impulse

    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (!state->ships[i].connected) continue;
        if (memcmp(ship, &state->ships[i], sizeof(ship_t)) == 0) continue;

        float dx = state->ships[i].x - ship->x;
        float dy = state->ships[i].y - ship->y;

        float dist = sqrt(dx*dx + dy*dy);

        if (dist <= ship->size) {
            float fvx = state->ships[i].vx;
            float fvy = state->ships[i].vy;
            float svx = ship->vx;
            float svy = ship->vy;

            state->ships[i].vx = svx;
            state->ships[i].vy = svy;

            ship->vx = fvx;
            ship->vy = fvy;
        }
    }

    if (ship->dash_timer > 0.0f) {
        ship->vx -= cosf(ship->angle) * DASH_BOOST;
        ship->vy -= sinf(ship->angle) * DASH_BOOST;
    }

    ship->x = fmodf(ship->x + state->width, state->width);
    ship->y = fmodf(ship->y + state->height, state->height);

    ship->dash_timer -= dt;
    ship->dash_cooldown -= dt;
}
