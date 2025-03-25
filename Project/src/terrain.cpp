#include "terrain.hpp"

using namespace cgp;

#include <vector>
#include <cmath>
#include <cgp/cgp.hpp>


std::vector<float> generate_float(int quantity, float max) {
    std::vector<float> floats;
    floats.reserve(quantity); // Reserve space to improve performance
    for (int i = 0; i < quantity; ++i) {
        float h = rand_uniform(-max, max);
        floats.push_back(h);
    }
    return floats;
}


std::vector<int> generate_int(int quantity, int min, int max) {
    std::vector<int> ints;
    ints.reserve(quantity); // Reserve space to improve performance
    for (int i = 0; i < quantity; ++i) {
        int h = static_cast<int>(rand_uniform(min, max));
        ints.push_back(h);
    }
    return ints;
}


void generate_const_gaussian_function(float terrain_length) {
    constexpr float HEIGHT_MAX = 6.0f;
    constexpr int SIGMA_MIN = 4;
    constexpr int SIGMA_MAX = 10;

    vertices_terrain_position = generate_positions_on_terrain_x_y(N_VERTICES_TERRAIN, terrain_length * 0.8f);
    heights_terrain = generate_float(N_VERTICES_TERRAIN, HEIGHT_MAX);
    sigmas_terrain = generate_int(N_VERTICES_TERRAIN, SIGMA_MIN, SIGMA_MAX);
}


float evaluate_terrain_height(float x, float y) {
    float z = 0.0f;
    for (int i = 0; i < N_VERTICES_TERRAIN; ++i) {
        float d_i = norm(cgp::vec2(x, y) - vertices_terrain_position[i]) / sigmas_terrain[i];
        z += heights_terrain[i] * std::exp(-d_i * d_i);
    }
    return z;
}

cgp::mesh create_terrain_mesh(int quantity, float terrain_length) {
    generate_const_gaussian_function(terrain_length);

    cgp::mesh terrain;
    terrain.position.resize(quantity * quantity);
    terrain.uv.resize(quantity * quantity);

    // Fill terrain geometry
    for (int ku = 0; ku < quantity; ++ku) {
        for (int kv = 0; kv < quantity; ++kv) {
            // Compute local parametric coordinates (u, v) \in [0,1]
            float u = ku / (quantity - 1.0f);
            float v = kv / (quantity - 1.0f);

            // Compute the real coordinates (x, y) of the terrain in [-TERRAIN_LENGTH/2, +TERRAIN_LENGTH/2]
            float x = (u - 0.5f) * terrain_length;
            float y = (v - 0.5f) * terrain_length;

            // Compute the surface height function at the given sampled coordinate
            float z = evaluate_terrain_height(x, y);

            // Store vertex coordinates
            terrain.position[kv + quantity * ku] = {x, y, z};
            terrain.uv[kv + quantity * ku] = {u * 50, v * 50};
        }
    }

    // Generate triangle organization
    // Parametric surface with uniform grid sampling: generate 2 triangles for each grid cell
    for (int ku = 0; ku < quantity - 1; ++ku) {
        for (int kv = 0; kv < quantity - 1; ++kv) {
            unsigned int idx = kv + quantity * ku; // current vertex offset

            cgp::uint3 triangle_1 = {idx, idx + 1 + quantity, idx + 1};
            cgp::uint3 triangle_2 = {idx, idx + quantity, idx + 1 + quantity};

            terrain.connectivity.push_back(triangle_1);
            terrain.connectivity.push_back(triangle_2);
        }
    }

    // Fill the other buffers with default values (normal, color, etc.)
    terrain.fill_empty_field();

    return terrain;
}

std::vector<cgp::vec3> generate_positions_on_terrain(int quantity, float terrain_length, bool is_flying, bool distance_check) {
    std::vector<cgp::vec3> positions;
    positions.reserve(quantity); // Reserve space to improve performance
    constexpr float MIN_DISTANCE = 6.0f;
    constexpr float MIN_DIFF = 0.2f;

    while (positions.size() < quantity) {
        float x = rand_uniform(-terrain_length / 2 + 1, terrain_length / 2 - 1);
        float y = rand_uniform(-terrain_length / 2 + 1, terrain_length / 2 - 1);
        float z = evaluate_terrain_height(x, y);

        bool valid_position = true;
        if (distance_check) {
            for (const auto& pos : positions) {
                float distance = std::sqrt((pos.x - x) * (pos.x - x) + (pos.y - y) * (pos.y - y));
                if (distance < MIN_DISTANCE || std::fabs(pos.x - x) < MIN_DIFF || std::fabs(pos.y - y) < MIN_DIFF) {
                    valid_position = false;
                    break;
                }
            }
        }

        if (valid_position) {
            if (is_flying) {
                positions.push_back(cgp::vec3(x, y, z + rand_uniform(2.0f, 10.0f)));
            } else {
                positions.push_back(cgp::vec3(x, y, z));
            }
        }
    }

    return positions;
}

std::vector<cgp::vec2> generate_positions_on_terrain_x_y(int quantity, float terrain_length) {
    std::vector<cgp::vec2> positions;
    positions.reserve(quantity); // Reserve space to improve performance
    constexpr float MIN_DISTANCE = 6.0f;

    while (positions.size() < quantity) {
        float x = rand_uniform(-terrain_length / 2 + 1, terrain_length / 2 - 1);
        float y = rand_uniform(-terrain_length / 2 + 1, terrain_length / 2 - 1);

        bool valid_position = true;
        for (const auto& pos : positions) {
            float distance = std::sqrt((pos.x - x) * (pos.x - x) + (pos.y - y) * (pos.y - y));
            if (distance < MIN_DISTANCE) {
                valid_position = false;
                break;
            }
        }

        if (valid_position) {
            positions.push_back(cgp::vec2(x, y));
        }
    }

    return positions;
}
