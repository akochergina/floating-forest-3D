#pragma once

#include "cgp/cgp.hpp"


// Terrain data (positions, heights, and sigmas)
static std::vector<cgp::vec2> vertices_terrain_position;
static std::vector<float> heights_terrain;
static std::vector<int> sigmas_terrain;
static constexpr int N_VERTICES_TERRAIN = 200;

// Evaluates the height of the terrain at the given (x, y) coordinates using Gaussian function.
float evaluate_terrain_height(float x, float y);

// Creates a mesh object representing the terrain.
cgp::mesh create_terrain_mesh(int quantity, float length);

// Generates a vector of 3D positions (vec3)
std::vector<cgp::vec3> generate_positions_on_terrain(int quantity, float terrain_length, bool is_flying, bool distance_check);

// Generates a vector of 2D positions (vec2).
std::vector<cgp::vec2> generate_positions_on_terrain_x_y(int quantity, float terrain_length);

// Generates a vector of random floats in the range [-max, max]
std::vector<float> generate_float(int quantity, float max);

// Generates a vector of random integers in the range [min, max].
std::vector<int> generate_int(int quantity, int min, int max);

// Generates the constants for Gaussian function.
void generate_const_gaussian_function(float terrain_length);
