#pragma once

#include "cgp/cgp.hpp"

// Forward declaration of scene_structure to avoid circular dependencies
struct scene_structure;

// Explicitly using cgp namespace to avoid conflicts and improve clarity
using cgp::mesh_drawable;
using cgp::vec3;
using std::vector;

// Structure representing a collection of grass elements
struct grass {
    // Define constant for the quantity of grass elements
    static constexpr int GRASS_QUANTITY = 1000;

    // Drawable for the grass element
    mesh_drawable grass;

    // Positions of individual grass elements
    vector<vec3> grass_position;

    // Function to get the scaling factor for a grass element based on its index
    float get_grass_scaling(int index) const;

    // Initializes the grass elements in the given scene with specified terrain length
    void initialize(scene_structure &scene, int terrain_length);

    // Displays the grass elements in the given scene
    void display(scene_structure &scene);
};
