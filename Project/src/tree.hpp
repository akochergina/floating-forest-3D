#pragma once

#include "cgp/cgp.hpp"
#include "pine_tree.hpp"
#include "birch_tree.hpp"

// Forward declaration of scene_structure to avoid circular dependencies
struct scene_structure;

// Explicitly using cgp namespace to avoid conflicts and improve clarity
using cgp::vec3;
using std::vector;

// Structure representing the management of trees in the scene
struct tree_manager {
    // Positions of individual trees
    vector<vec3> tree_position;

    // Instances of different tree types
    pine_tree pine_tree;
    birch_tree birch_tree;

    // Number of trees to manage
    static constexpr int N_TREE = 500;

    // Initializes the tree elements in the given scene with the specified terrain length
    void initialize(scene_structure& scene, float terrain_length);

    // Displays the trees in the given scene
    void display(scene_structure& scene);
};
