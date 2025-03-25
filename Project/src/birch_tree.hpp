#pragma once

#include "cgp/cgp.hpp"

// Forward declaration of scene_structure to avoid circular dependencies
struct scene_structure;

// Using the cgp namespace explicitly
using namespace cgp;

// Structure representing a birch tree
struct birch_tree {
    // Hierarchical drawable for the tree components
    cgp::hierarchy_mesh_drawable hierarchy;

    // Drawable elements
    mesh_drawable trunk;
    mesh_drawable foliage;

    // Initializes the birch tree structure with the given scene
    void initialize(scene_structure &scene);

    // Initializes the trunk of the birch tree with specified parameters
    void initialize_trunk(scene_structure &scene, mesh_drawable &trunk, float radius, float height,
                          const std::string &texture_path);

    // Initializes the foliage of the birch tree with the specified trunk height and texture
    void initialize_foliage(scene_structure &scene, mesh_drawable &foliage, float trunk_height,
                            const std::string &texture_path);

    // Displays the birch tree at a specified position, using the given tree index for variations
    void display(scene_structure &scene, int tree_index, vec3 position);
};
