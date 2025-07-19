#pragma once

#include "structs.h"
#define DASH_COOLDOWN 0.5f
#define DASH_BOOST 666.66f
/*
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

    ship->dash_timer -= dt;
    ship->dash_cooldown -= dt;
}*/
static void update_ship(ship_t* ship, const float dt, const vector2d max) {
    ship_state_t* state = &ship->state;
    // rotation with inertia
    const float inertia = state->size * 0.5f;
    if (ship->input_buffer.rotate_left) state->angular_velocity -= 300.0f * dt / inertia;
    if (ship->input_buffer.rotate_right) state->angular_velocity += 300.0f * dt / inertia;

    // rotation stuff
    state->angular_velocity *= 0.9f;
    state->angle += state->angular_velocity * dt;

    // traction force
    float acceleration = 10000.0f / state->size;
    float ax = 0.0f, ay = 0.0f;

    // dashing
    if (state->dash_timer < 0.0f && state->dash_cooldown < 0.0f && ship->input_buffer.dash) {
        state->dash_timer = 0.15f;
        state->dash_cooldown = DASH_COOLDOWN;
    }

    if (ship->input_buffer.thrust == 1) {
        ax = cosf(state->angle) * acceleration;
        ay = sinf(state->angle) * acceleration;
    }
    else if (ship->input_buffer.thrust == -1) {
        ax = -cosf(state->angle) * acceleration/3;
        ay = -sinf(state->angle) * acceleration/3;
    }

    // windage
    const float resistance = 0.8f;
    ax -= state->vx * resistance;
    ay -= state->vy * resistance;

    // coords update
    state->vx += ax * dt;
    state->vy += ay * dt;

    if (state->dash_timer > 0.0f) {
        state->vx += cosf(state->angle) * DASH_BOOST;
        state->vy += sinf(state->angle) * DASH_BOOST;
    }

    state->x += state->vx * dt;
    state->y += state->vy * dt;

    if (state->dash_timer > 0.0f) {
        state->vx -= cosf(state->angle) * DASH_BOOST;
        state->vy -= sinf(state->angle) * DASH_BOOST;
    }

    state->dash_timer -= dt;
    state->dash_cooldown -= dt;

    state->x = fmodf(state->x + max.x, max.x);
    state->y = fmodf(state->y + max.y, max.y);
}
/*
static void cpu_control(const server_state_t* state, ship_t* ship, const float x, const float y) {
    float dx = x - ship->x;
    float dy = y - ship->y;

    if (dx > state->map.width / 2) dx -= state->map.width;
    if (dx < -state->map.width / 2) dx += state->map.width;
    if (dy > state->map.height / 2) dy -= state->map.height;
    if (dy < -state->map.height / 2) dy += state->map.height;

    const float distance = sqrtf(dx * dx + dy * dy);

    const float desired_angle = atan2f(dy, dx);

    float diff = desired_angle - ship->angle;
    while (diff > M_PI) diff -= 2 * M_PI;
    while (diff < -M_PI) diff += 2 * M_PI;

    const float angle_threshold = 0.05f;
    ship->input_buffer.rotate_left = diff < -angle_threshold;
    ship->input_buffer.rotate_right = diff > angle_threshold;

    ship->input_buffer.thrust = 0;

    if (fabsf(diff) < 0.3f && distance > 40.0f) {
        ship->input_buffer.thrust = 1;
    }
    else if (fabsf(diff) > 2.0f && distance < 80.0f) {
        ship->input_buffer.thrust = -1;
    }
}*/
static void cpu_control(ship_t* ship, const float x, const float y) {
    ship_state_t* state = &ship->state;
    float dx = x - state->x;
    float dy = y - state->y;

    const float desired_angle = atan2f(dy, dx);

    float diff = desired_angle - state->angle;
    while (diff > M_PI) diff -= 2 * M_PI;
    while (diff < -M_PI) diff += 2 * M_PI;

    const float angle_threshold = 0.05f;
    ship->input_buffer.rotate_left = diff < -angle_threshold;
    ship->input_buffer.rotate_right = diff > angle_threshold;

    ship->input_buffer.thrust = 1;
}