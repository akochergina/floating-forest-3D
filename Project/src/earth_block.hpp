#pragma once

#include "cgp/cgp.hpp"

// Forward declaration of scene_structure to avoid circular dependencies
struct scene_structure;

// Explicitly using cgp namespace to avoid conflicts and improve clarity
using cgp::hierarchy_mesh_drawable;
using cgp::mesh_drawable;
using cgp::vec3;
using std::string;

// Structure representing an earth block
struct earth_block {
    // Hierarchical drawable for the earth block components
    hierarchy_mesh_drawable hierarchy;

    // Drawable elements
    mesh_drawable base;
    mesh_drawable terrain;

    // Initializes the earth block structure with the given scene and terrain length
    void initialize(scene_structure &scene, const int terrain_length);

    // Initializes the terrain of the earth block
    void initialize_terrain(scene_structure &scene, const int terrain_length, const int samples_quantity,
                            const string &texture_path, const vec3 &color);

    // Initializes the base of the earth block
    void initialize_base(scene_structure &scene, const int terrain_length, const string &texture_path);

    // Displays the earth block in the given scene
    void display(scene_structure &scene);
};
