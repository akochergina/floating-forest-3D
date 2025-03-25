#pragma once

#include "cgp/cgp.hpp"

// Forward declaration of scene_structure to avoid circular dependencies
struct scene_structure;

// Explicitly using cgp namespace to avoid conflicts and improve clarity
using cgp::vec3;
using cgp::hierarchy_mesh_drawable;
using cgp::mesh_drawable;
using std::string;

// Structure representing a pine tree in the scene
struct pine_tree {
    // Hierarchical drawable for pine tree components
    hierarchy_mesh_drawable hierarchy;

    // Drawable for the tree trunk
    mesh_drawable trunk;

    // Drawables for different layers of foliage
    mesh_drawable foliage_1;
    mesh_drawable foliage_2;
    mesh_drawable foliage_3;

    // Initializes the pine tree in the given scene
    void initialize(scene_structure& scene);

    // Displays the pine tree at the specified position and tree index
    void display(scene_structure& scene, int tree_index, vec3 position);

    // Initializes the foliage with specified parameters
    void initialize_foliage(mesh_drawable& foliage, float base_radius, float height, float translation_z,
                            float position_z, vec3 color, const string& texture_path, scene_structure& scene);
};
