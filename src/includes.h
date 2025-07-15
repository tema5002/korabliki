#pragma once

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pwd.h>
#include <arpa/inet.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MAX3(a, b, c) MAX(MAX(a, b), c)

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define DIST(x1, y1, x2, y2) (sqrtf((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)))