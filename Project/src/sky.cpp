#pragma once

#include "sky.hpp"
#include "scene.hpp"

void sky_structure::initialize(scene_structure& scene){
    // Define constants for the sky dimensions and position
    const vec3 SKY_TRANSLATION = {0.0f, 0.0f, 20.0f};
    const std::vector<float> SKY_SCALE = {900.0f, 500.0f};

    mesh_drawable sky;

    // Initialize the farest sky cube
    initialize_sky_cube(scene, sky, SKY_SCALE[0], SKY_TRANSLATION);
    hierarchy.add(sky, "layer_1");

    // Initialize the closest sky cube
    initialize_sky_cube(scene, sky, SKY_SCALE[1], SKY_TRANSLATION);
    hierarchy.add(sky, "layer_2", "layer_1");
}

void sky_structure::initialize_sky_cube(scene_structure& scene, mesh_drawable& sky_part, const float SKY_SCALE, const vec3& SKY_TRANSLATION){
    // Define path to the sky texture
    const std::string TEXTURE_PATH = project::path + "assets/sky.png";

    // Create and configure sky mesh
    mesh sky_mesh = mesh_primitive_cube();
    sky_mesh.scale(SKY_SCALE);
    sky_mesh.translate(SKY_TRANSLATION);
    scene.initialize_mesh_with_texture(sky_part, sky_mesh, TEXTURE_PATH);
}

void sky_structure::display(scene_structure &scene) {
    // Define rotation angle
    const std::vector<float> ROTATION_ANGLE = {scene.timer.t / 10, scene.timer.t / 15};

    // Rotation around its axis
    hierarchy["layer_1"].transform_local.rotation =
            rotation_transform::from_axis_angle({0, 0, 1}, ROTATION_ANGLE[0]);
    hierarchy["layer_2"].transform_local.rotation =
            rotation_transform::from_axis_angle({0, 0, 1}, ROTATION_ANGLE[1]);

    // Update the hierarchy and draw the amanite
    hierarchy.update_local_to_global_coordinates();

    // Display the sky
    draw(hierarchy, scene.environment);
}