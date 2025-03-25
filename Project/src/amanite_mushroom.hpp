#pragma once

#include "cgp/cgp.hpp"

// Forward declaration of scene_structure
struct scene_structure;

// Using namespace cgp explicitly to avoid prefixing
using namespace cgp;

// Structure representing an amanite mushroom
struct amanite_mushroom {
    // Hierarchical drawable for the mushroom
    cgp::hierarchy_mesh_drawable hierarchy;

    // Drawable components
    mesh_drawable stem;
    mesh_drawable cap;

    // Function to initialize the mushroom in the scene
    void initialize(scene_structure &scene);

    // Function to display the mushroom at a specific position
    void display(scene_structure &scene, const vec3 &position);
};
