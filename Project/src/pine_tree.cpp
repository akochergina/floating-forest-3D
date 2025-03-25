#pragma once

#include "pine_tree.hpp"
#include "mesh_primitive.hpp"
#include "scene.hpp"

struct pine_tree;
using namespace cgp;

void pine_tree::initialize(scene_structure& scene) {
    // Pine tree foliage consists of three combined cones of the same texture, but with
    // overlapping different colours. Therefore, the mesh of all three cones is built in this function.
    // The trunk of the pine tree is also built separately, as it is overlaid with a different texture.

    // Define paths to textures
    const std::string TRUNK_TEXTURE_PATH = project::path + "assets/trunk_pine.jpg";
    const std::string FOLIAGE_TEXTURE_PATH = project::path + "assets/sapin.jpg";

    // Colors for the foliage
    const vec3 FOLIAGE_1_COLOR = {47 / 256.0, 79 / 256.0, 79 / 256.0};
    const vec3 FOLIAGE_2_COLOR = {48 / 256.0, 186 / 256.0, 143 / 256.0};
    const vec3 FOLIAGE_3_COLOR = {1, 1, 1};

    // Radius and height for the trunk
    constexpr float TRUNK_RADIUS = 0.3f;
    constexpr float TRUNK_HEIGHT = 1.6f;

    // Radii and heights for the foliage
    constexpr float FOLIAGE_1_RADIUS = 2;
    constexpr float FOLIAGE_2_RADIUS = 1.5;
    constexpr float FOLIAGE_3_RADIUS = 1;

    constexpr float FOLIAGE_1_HEIGHT = 3;
    constexpr float FOLIAGE_2_HEIGHT = 3;
    constexpr float FOLIAGE_3_HEIGHT = 3;

    const float FOLIAGE_TRANSLATION = TRUNK_HEIGHT / 2.0;

    // Initialize trunk
    mesh trunk_mesh = create_cylinder_mesh(TRUNK_RADIUS, TRUNK_HEIGHT);
    scene.initialize_mesh_with_texture(trunk, trunk_mesh, TRUNK_TEXTURE_PATH);

    // Initialize foliage layers
    initialize_foliage(foliage_1, FOLIAGE_1_RADIUS, FOLIAGE_1_HEIGHT, 0.0f, FOLIAGE_TRANSLATION, FOLIAGE_1_COLOR,
                       FOLIAGE_TEXTURE_PATH, scene);
    initialize_foliage(foliage_2, FOLIAGE_2_RADIUS, FOLIAGE_2_HEIGHT, FOLIAGE_3_RADIUS, FOLIAGE_TRANSLATION,
                       FOLIAGE_2_COLOR, FOLIAGE_TEXTURE_PATH, scene);
    initialize_foliage(foliage_3, FOLIAGE_3_RADIUS, FOLIAGE_3_HEIGHT, FOLIAGE_1_RADIUS, FOLIAGE_TRANSLATION,
                       FOLIAGE_3_COLOR, FOLIAGE_TEXTURE_PATH, scene);

    // Add to hierarchy
    hierarchy.add(trunk, "trunk");
    hierarchy.add(foliage_1, "foliage_1", "trunk");
    hierarchy.add(foliage_2, "foliage_2", "trunk");
    hierarchy.add(foliage_3, "foliage_3", "trunk");
}

void pine_tree::display(scene_structure& scene, int tree_index, vec3 position) {
    // Set the position of the tree
    hierarchy["trunk"].transform_local.translation = position;

    // Define scaling values for different tree sizes
    constexpr std::array<float, 3> TREE_SCALING = {0.6f, 1.3f, 1.7f};
    hierarchy["trunk"].transform_local.scaling = TREE_SCALING[tree_index % 3];

    // Define rotation angles for different tree orientations
    constexpr float PI = 3.14159265359f;
    vec3 rotation_axis = {0, 0, 1};
    float rotation_angle = 0.0f;

    switch (tree_index % 4) {
        case 0:
            rotation_angle = position[2] * PI / 100;
            break;
        case 1:
            rotation_angle = 40 * position[1] + position[0];
            break;
        case 2:
            rotation_angle = position[2] + 3 * position[0];
            break;
        case 3:
            rotation_angle = position[2] - 2 * position[1] + position[0];
            break;
    }

    hierarchy["trunk"].transform_local.rotation =
            rotation_transform::from_axis_angle(rotation_axis, rotation_angle);

    // Update the hierarchy and draw the tree
    hierarchy.update_local_to_global_coordinates();
    draw(hierarchy, scene.environment);
}

void pine_tree::initialize_foliage(mesh_drawable& foliage, float base_radius, float height, float translation_z,
                                   float position_z, vec3 color, const std::string& texture_path, scene_structure& scene) {
    // Create foliage mesh
    mesh foliage_mesh = create_cone_mesh(base_radius, height, translation_z);
    foliage_mesh.translate({0, 0, position_z});
    scene.initialize_mesh_with_texture_and_color(foliage, foliage_mesh, texture_path, color);

    // Assign shader to foliage
    foliage.shader = scene.shader_snake_y; // Reuse shader for foliage
}