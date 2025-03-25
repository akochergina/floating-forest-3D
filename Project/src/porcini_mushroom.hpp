#pragma once

#include "cgp/cgp.hpp"

// Forward declaration of scene_structure to avoid circular dependencies
struct scene_structure;

// Explicitly using cgp namespace to avoid conflicts and improve clarity
using cgp::vec3;
using cgp::hierarchy_mesh_drawable;
using cgp::mesh_drawable;
using std::string;

// Structure representing a porcini mushroom
struct porcini_mushroom {
    // Hierarchical drawable for mushroom components
    hierarchy_mesh_drawable hierarchy;

    // Drawable elements for the mushroom
    mesh_drawable stem;
    mesh_drawable cap;

    // Initializes the porcini mushroom in the given scene
    void initialize(scene_structure& scene);

    // Displays the porcini mushroom at the specified position
    void display(scene_structure& scene, const vec3& position);
};
