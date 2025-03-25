#pragma once

#include "terrain.hpp"
#include "scene.hpp"
#include "mushroom.hpp"

void mushroom_manager::initialize(scene_structure &scene, const float TERRAIN_LENGTH) {
    // Generate positions for mushrooms on the terrain
    mushroom_position = generate_positions_on_terrain(MUSHROOM_QUANTITY, TERRAIN_LENGTH, false, true);

    // Initialize different types of mushrooms
    amanite_mushroom.initialize(scene);
    porcini_mushroom.initialize(scene);
}

void mushroom_manager::display(scene_structure &scene) {
    // using mushroom_index to vary mushroom type
    int mushroom_index = 0;

    // A single variable mushroom_position is used for the positions of all mushroom types to avoid the problem of
    // rendering two different mushrooms in approximately the same place.
    for (vec3 position: mushroom_position) {
        if (mushroom_index < MUSHROOM_QUANTITY / 2) {
            amanite_mushroom.display(scene, position);
        } else {
            porcini_mushroom.display(scene, position);
        }
        mushroom_index++;
    }
}