#pragma once

#include "cgp/cgp.hpp"

// Forward declaration of scene_structure to avoid circular dependencies
struct scene_structure;

// Explicitly using cgp namespace to avoid conflicts and improve clarity
using cgp::hierarchy_mesh_drawable;
using cgp::mesh_drawable;
using cgp::vec3;
using std::vector;

// Structure representing a collection of skulls in the scene
struct skull {
    // Define the number of skulls
    static constexpr int N_SKULL = 10;

    // Hierarchical drawable for skull components
    hierarchy_mesh_drawable hierarchy;

    // Drawable for a single skull
    mesh_drawable skull;

    // Positions of individual skulls
    vector<vec3> skull_position;

    // Initializes the skull elements in the given scene with the specified terrain length
    void initialize(scene_structure& scene, float terrain_length);

    // Displays the skulls in the given scene
    void display(scene_structure& scene);
};
