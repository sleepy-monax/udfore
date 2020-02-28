#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define __create(__type) (__type *)calloc(1, sizeof(__type));

bool utils_is_white_space(char chr);

bool utils_is_letter(char chr);

bool utils_is_number(char chr);
