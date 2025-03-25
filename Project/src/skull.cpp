#pragma once

#include "skull.hpp"
#include "cgp/cgp.hpp"
#include "scene.hpp"
#include "terrain.hpp"


using namespace cgp;

void skull::initialize(scene_structure& scene, const float terrain_length) {
    // Generate positions for skulls on the terrain
    skull_position = generate_positions_on_terrain(N_SKULL, terrain_length * 0.9, false, true);

    // Define paths to textures
    const std::string SKULL_TEXTURE_PATH = project::path + "assets/skull/skull.jpg";
    const std::string SKULL_MESH_PATH = project::path + "assets/skull/skull.obj";

    constexpr float ROTATION_ANGLE_X = -3.14 / 7;

    // Initialize skull
    mesh skull_mesh = mesh_load_file_obj(SKULL_MESH_PATH);
    scene.initialize_mesh_with_texture(skull, skull_mesh, SKULL_TEXTURE_PATH);

    // Set skull scaling and rotation
    skull.model.scaling = 0.1;
    skull.model.rotation = rotation_transform::from_axis_angle({1, 0, 0}, ROTATION_ANGLE_X);
}

void skull::display(scene_structure& scene){
    // Display all skulls
    for (vec3 position :skull_position){
        skull.model.translation = position;
        draw(skull, scene.environment);
    }
}