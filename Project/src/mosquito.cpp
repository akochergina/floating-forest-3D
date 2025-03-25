#include "mosquito.hpp"
#include "cgp/cgp.hpp"
#include "scene.hpp"
#include "terrain.hpp"
#include "mesh_object.hpp"

// Avoid using namespace in implementation files to prevent potential name conflicts
using cgp::vec3;
using cgp::hierarchy_mesh_drawable;
using cgp::mesh_drawable;
using std::vector;

// Initialize the mosquito elements in the scene
void mosquito::initialize(scene_structure &scene, float terrain_length) {
    // Generate positions for mosquitoes on the terrain
    mosquito_position = generate_positions_on_terrain(N_MOSQUITO, terrain_length * 0.9f, true, true);

    // Define colors for the mosquito body and wings
    const vec3 BODY_COLOR = {117 / 256.0f, 92 / 256.0f, 72 / 256.0f};
    const vec3 WING_COLOR = {250 / 256.0f, 238 / 256.0f, 221 / 256.0f};

    // Create and initialize the mosquito body
    scene.initialize_mesh_with_color(body, create_mosquito(), BODY_COLOR);

    // Create and initialize the mosquito wings
    scene.initialize_mesh_with_color(wing_1, create_mosquito_wing(true), WING_COLOR);
    scene.initialize_mesh_with_color(wing_2, create_mosquito_wing(false), WING_COLOR);

    // Add body and wings to the hierarchy
    hierarchy.add(body, "mosquito");
    hierarchy.add(wing_1, "wing_1", "mosquito");
    hierarchy.add(wing_2, "wing_2", "mosquito");
}

// Display the mosquitoes in the scene
void mosquito::display(scene_structure &scene) {
    // Use mosquito_index to vary moving type and size of mosquito
    int mosquito_index = 0;

    // Define scaling values for different mosquito sizes
    constexpr std::array<float, 4> MOSQUITO_SCALING = {1.6f, 0.9f, 1.1f, 1.2f};

    // Iterate over each mosquito position
    for (const vec3 &position: mosquito_position) {
        // Set the base position of the mosquito
        hierarchy["mosquito"].transform_local.translation = position;

        // Set the mosquito scale based on the index
        hierarchy["mosquito"].transform_local.scaling = MOSQUITO_SCALING[mosquito_index % 4];

        // Display mosquito wings
        display_mosquito_wing(scene);

        // Rotate the mosquito around itself at a different speed
        const float ROTATION_ANGLE = scene.timer.t + position[2] + position[1] + position[0];
        hierarchy["mosquito"].transform_local.rotation =
                rotation_transform::from_axis_angle({0, 0, 1}, ROTATION_ANGLE);

        // Vary the size and movement of the mosquito
        vary_mosquito_behavior(scene, mosquito_index, position);

        // Update the hierarchy and draw the mosquito
        hierarchy.update_local_to_global_coordinates();
        draw(hierarchy, scene.environment);

        ++mosquito_index;
    }
}

// Display the mosquito wings with rotation
void mosquito::display_mosquito_wing(scene_structure &scene) {
    // Rotate the wings randomly around the z-axis
    const float RANDOM_ANGLE = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    hierarchy["wing_1"].transform_local.rotation =
            rotation_transform::from_axis_angle({0, 0, 1}, RANDOM_ANGLE);
    hierarchy["wing_2"].transform_local.rotation =
            rotation_transform::from_axis_angle({0, 0, 1}, -RANDOM_ANGLE);
}

// Vary the mosquito behavior based on index and position
void mosquito::vary_mosquito_behavior(scene_structure &scene, int mosquito_index, const vec3 &position) {
    // Define useful constants for behavior variation
    const float TIME = scene.timer.t;
    const float VARIATION = 0.5f * sin(2 * TIME + position[0] + position[1] + position[2]);
    const float RAND_UNIFORM_0_1 = rand_uniform(0.0f, 1.0f);
    const float RAND_UNIFORM_0_2 = rand_uniform(0.0f, 2.0f);
    const float COS_TIME = cos(TIME);
    const float SIN_TIME = sin(TIME);

    vec3 new_translation;

    switch (mosquito_index % 4) {
        case 0:
            // Mosquito 0 flies along the z-axis with slight variations in x and y
            new_translation = {
                    COS_TIME + position[0],
                    SIN_TIME + position[1],
                    position[2] + VARIATION
            };
            break;

        case 1:
            // Mosquito 1 flies along a complex trajectory with randomization
            new_translation = {
                    (position[0] + position[1]) * COS_TIME + position[0] + RAND_UNIFORM_0_1,
                    (position[0] + position[1]) * sin(TIME + position[0]) * cos(position[0] + position[1]) +
                    position[1] + RAND_UNIFORM_0_1,
                    position[2] + VARIATION
            };
            break;

        case 2:
            // Mosquito 2 flies along another complex trajectory with randomization
            new_translation = {
                    (position[0] + position[1]) * cos(position[0] + position[1]) + position[0] + RAND_UNIFORM_0_2,
                    (position[0] + position[1]) * COS_TIME + position[1] + RAND_UNIFORM_0_2,
                    position[2] + VARIATION
            };
            break;

        case 3:
            // Mosquito 3 flies along the z-axis
            new_translation = {
                    position[0],
                    position[1],
                    position[2] + VARIATION
            };
            break;
    }

    // Update the mosquito translation in the hierarchy
    hierarchy["mosquito"].transform_local.translation = new_translation;
}
