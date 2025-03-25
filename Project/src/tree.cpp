#pragma once

#include "tree.hpp"
#include "terrain.hpp"
#include "scene.hpp"

void tree_manager::initialize(scene_structure &scene, const float TERRAIN_LENGTH) {
    // Generate positions for trees
    tree_position = generate_positions_on_terrain(N_TREE, TERRAIN_LENGTH, false, true);

    // Initialize different types of trees
    pine_tree.initialize(scene);
    birch_tree.initialize(scene);
}

void tree_manager::display(scene_structure &scene) {
    // using tree_index to vary tree type, tree size and tree angle
    int tree_index = 0;

    // A single variable tree_position is used for the positions of all tree types to avoid the problem of rendering
    // two different trees in approximately the same place.
    for (const vec3 &position: tree_position) {
        if (tree_index < N_TREE / 2) {
            pine_tree.display(scene, tree_index, position);
        } else {
            birch_tree.display(scene, tree_index, position);
        }
        tree_index++;
    }
}

