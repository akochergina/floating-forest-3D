#pragma once

#include "cgp/cgp.hpp"

// Forward declaration of scene_structure to avoid circular dependencies
struct scene_structure;

// Explicitly using cgp namespace to avoid conflicts and improve clarity
using cgp::vec3;
using cgp::hierarchy_mesh_drawable;
using cgp::mesh_drawable;
using std::vector;

// Structure representing a mosquito in the scene
struct mosquito {
    // Define the number of mosquitoes
    static constexpr int N_MOSQUITO = 300;

    // Positions of individual mosquitoes
    vector<vec3> mosquito_position;

    // Hierarchical drawable for mosquito components
    hierarchy_mesh_drawable hierarchy;

    // Drawable elements
    mesh_drawable body;
    mesh_drawable wing_1;
    mesh_drawable wing_2;

    // Initializes the mosquito structure in the given scene with the specified terrain length
    void initialize(scene_structure& scene, float terrain_length);

    // Displays the mosquitoes in the given scene
    void display(scene_structure& scene);

    // Displays the mosquito wings
    void display_mosquito_wing(scene_structure& scene);

    // Varies the behavior of mosquitoes based on the given index and position
    void vary_mosquito_behavior(scene_structure& scene, int mosquito_index, const vec3& position);
};
