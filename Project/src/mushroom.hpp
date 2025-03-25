#pragma once

#include "cgp/cgp.hpp"
#include "amanite_mushroom.hpp"
#include "porcini_mushroom.hpp"

// Explicitly using cgp namespace to avoid conflicts and improve clarity
using cgp::vec3;
using std::vector;

// Structure managing mushroom elements in the scene
struct mushroom_manager {
    // Define the number of mushrooms
    static constexpr int MUSHROOM_QUANTITY = 600;

    // Positions of individual mushrooms
    vector<vec3> mushroom_position;

    // Different mushroom instances
    amanite_mushroom amanite_mushroom;
    porcini_mushroom porcini_mushroom;

    // Initializes the mushroom elements in the given scene with the specified terrain length
    void initialize(scene_structure& scene, float terrain_length);

    // Displays the mushrooms in the given scene
    void display(scene_structure& scene);
};
