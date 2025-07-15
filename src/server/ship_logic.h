#pragma once

#include "../structs.h"
#define DASH_COOLDOWN 0.5f
#define DASH_BOOST 666.66f

static void update_ship(const server_state_t* state, ship_t* ship, const float dt) {
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
    for (size_t i = 0; i < state->clients_size; i++) {
        ship_t* s = &state->clients[i].ship;
        if (s == ship) continue;

        const float dx = s->x - ship->x;
        const float dy = s->y - ship->y;

        const float dist = sqrtf(dx*dx + dy*dy);
        const float collision_distance = ship->size/2 + s->size/2;

        if (dist <= collision_distance) {
            if (dist <= collision_distance/2) {
                ship->x -= collision_distance/2;
                s->x += collision_distance/2;
                continue;
            }

            const float tvx = s->vx;
            s->vx = ship->vx;
            ship->vx = tvx;

            const float tvy = s->vy;
            s->vy = ship->vy;
            ship->vy = tvy;
        }
    }

    if (ship->dash_timer > 0.0f) {
        ship->vx -= cosf(ship->angle) * DASH_BOOST;
        ship->vy -= sinf(ship->angle) * DASH_BOOST;
    }

    ship->x = fmodf(ship->x + state->map.width, state->map.width);
    ship->y = fmodf(ship->y + state->map.height, state->map.height);

    ship->dash_timer -= dt;
    ship->dash_cooldown -= dt;
}
