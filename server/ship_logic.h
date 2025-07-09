#pragma once

#include "server_state.h"
#include "../shared/ship_net.h"

#define DASH_COOLDOWN 0.5f
#define DASH_BOOST 666.66f

void update_ship(server_state_t* state, ship_t* ship, const float dt);