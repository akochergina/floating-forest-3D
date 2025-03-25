#pragma once

#include "snake.hpp"
#include "cgp/cgp.hpp"
#include "scene.hpp"
#include "mesh_object.hpp"
#include "terrain.hpp"


using namespace cgp;

void snake_structure::initialize_snake(scene_structure& scene, mesh_drawable& head, mesh_drawable& body, hierarchy_mesh_drawable& hierarchy,
                                       const std::string& texture_path, opengl_shader_structure& shader,
                                       const vec3& rotation_axis, float rotation_angle, const vec3& body_translation) {
    // Its head is an ellipsoid (deformed ball) and its body is an elongated cylinder with a cone at the end (tail).
    // Snakes moving along the x and y axes are built separately to avoid rotation problems during animation.

    // Define the translation vectors
    const vec3 TRANSLATION_0 = {0, 0, 0.0};

    // Initialize snake head
    mesh head_mesh = create_sphere_mesh(HEAD_RADIUS, TRANSLATION_0);
    head_mesh.scale(1.0, 2.0, 1.0);
    head_mesh.rotate(rotation_axis, rotation_angle);
    scene.initialize_mesh_with_texture(head, head_mesh, texture_path);

    // Initialize snake body. The body mesh is built separately, since a different shader is used for the body.
    // This is necessary to simulate the wriggling of the snake's body.
    mesh body_mesh = create_snake_body();
    body_mesh.rotate(rotation_axis, rotation_angle);
    scene.initialize_mesh_with_texture(body, body_mesh, texture_path);

    // Add to hierarchy
    body.shader = shader;

    // Add head and body to the hierarchy
    hierarchy.add(head, "head");
    hierarchy.add(body, "body", "head", body_translation);
}

void snake_structure::initialize_snake_x(scene_structure& scene) {
    const vec3 BODY_TRANSLATION = {-HEAD_RADIUS, 0.0, 0.0};
    const float ROTATION_ANGLE = 1.57;

    // Define paths to textures
    const std::string SNAKE_TEXTURE_PATH = project::path + "assets/snake_2.jpg";

    // Initialize snake head and body
    initialize_snake(scene, head_x, body_x, hierarchy_x, SNAKE_TEXTURE_PATH,
                     scene.shader_snake_x, {0, 0, 1}, ROTATION_ANGLE, BODY_TRANSLATION);
}

void snake_structure::initialize_snake_y(scene_structure& scene) {
    const vec3 BODY_TRANSLATION = {0.0, HEAD_RADIUS, 0.0};
    const float ROTATION_ANGLE = 0.0;

    // Define paths to textures
    const std::string SNAKE_TEXTURE_PATH = project::path + "assets/snake.jpeg";

    // Initialize snake head and body
    initialize_snake(scene, head_y, body_y, hierarchy_y, SNAKE_TEXTURE_PATH,
                     scene.shader_snake_y, {0, 0, 1}, ROTATION_ANGLE, BODY_TRANSLATION);
}

void snake_structure::initialize(scene_structure& scene, const float TERRAIN_LENGTH) {
    // Generate positions for snakes on the terrain
    snake_position_y = generate_positions_on_terrain(N_SNAKE, TERRAIN_LENGTH * 0.9, false, true);
    snake_position_x = generate_positions_on_terrain(N_SNAKE, TERRAIN_LENGTH * 0.9, false, true);

    // Initialize previous positions and angles
    for (int i = 0; i < N_SNAKE; ++i) {
        snake_position_previous_y.push_back(snake_position_y[i]);
        if (snake_angle_x.size() < N_SNAKE)
            snake_angle_x.push_back(0.0f);
        snake_position_previous_x.push_back(snake_position_x[i]);
        if (snake_angle_y.size() < N_SNAKE)
            snake_angle_y.push_back(0.0f);
    }

    // Initialize the snake along the x and y axes
    initialize_snake_x(scene);
    initialize_snake_y(scene);
}


void snake_structure::display(scene_structure& scene, const float TERRAIN_LENGTH){
    display_snake_x(scene, TERRAIN_LENGTH);
    display_snake_y(scene, TERRAIN_LENGTH);
}

void snake_structure::display_snake_x(scene_structure& scene, const float TERRAIN_LENGTH) {
    // Index used to vary moving type and size of snake
    int snake_index = 0;

    constexpr float MIN_Z_DIFF = 0.07f;
    constexpr float MIN_X_DIFF = 0.001f;
    const float TIME = scene.timer.t;

    for (const vec3& position : snake_position_x) {
        float x, y, z; // New x, y, z coordinates of the snake head
        hierarchy_x["head"].transform_local.translation = position;

        // Varying the size and moving type of the snake
        switch (snake_index % 2) {
            case 0: {
                // Snake_0 moves in a straight line along the x-axis.
                hierarchy_x["head"].transform_local.rotation =
                        rotation_transform::from_axis_angle({0, 1, 0}, snake_angle_x[snake_index]);

                const float TERRAIN_HALF_LENGTH = TERRAIN_LENGTH / 2 * 0.9f;
                x = -TERRAIN_HALF_LENGTH - (int(TIME / TERRAIN_LENGTH + fabs(position[0])) - TIME / TERRAIN_LENGTH - fabs(position[0])) * TERRAIN_LENGTH;
                y = position[1];

                // Move the snake to the beginning of the terrain if it reaches the edge
                if (fabs(x) > TERRAIN_HALF_LENGTH || fabs(y) > TERRAIN_HALF_LENGTH) {
                    x = -TERRAIN_HALF_LENGTH;
                    y = position[1];
                    snake_angle_x[snake_index] = 0;
                }

                z = evaluate_terrain_height(x, y) + HEAD_RADIUS;

                // Change the snake's body inclination if the difference between the previous and new z coordinates is large enough
                if (fabs(z - snake_position_previous_x[snake_index].z) > MIN_Z_DIFF) {
                    if (fabs(snake_position_previous_x[snake_index].x - x) > MIN_X_DIFF) {
                        float angle = atan((z - snake_position_previous_x[snake_index].z) / (snake_position_previous_x[snake_index].x - x)) - snake_angle_x[snake_index];
                        hierarchy_x["head"].transform_local.rotation =
                                rotation_transform::from_axis_angle({0, 1, 0}, angle);

                        // Save the new angle and the new position into an array for use in the next drawing
                        snake_angle_x[snake_index] = angle;
                        snake_position_previous_x[snake_index] = {x, y, z};
                    }
                }

                hierarchy_x["head"].transform_local.translation = {x, y, z};
                hierarchy_x["head"].transform_local.scaling = 1.6f;
                break;
            }
            case 1: {
                // Snake_1 remains in its position with a pseudo-random body rotation angle
                x = position[0];
                y = position[1];
                z = evaluate_terrain_height(x, y) + HEAD_RADIUS;

                hierarchy_x["head"].transform_local.rotation =
                        rotation_transform::from_axis_angle({0, 0, 1}, 2 * position[0] - 6 * position[1] + position[2]);

                hierarchy_x["head"].transform_local.translation = {x, y, z};
                hierarchy_x["head"].transform_local.scaling = 1.1f;
                break;
            }
        }

        snake_index++;

        hierarchy_x.update_local_to_global_coordinates();
        draw(hierarchy_x, scene.environment);
    }
}

void snake_structure::display_snake_y(scene_structure& scene, const float TERRAIN_LENGTH) {
    // Index used to vary moving type and size of snake
    int snake_index = 0;

    constexpr float HEAD_SCALING_0 = 1.6f;
    constexpr float HEAD_SCALING_1 = 1.1f;
    constexpr float HEAD_RADIUS_HALF = HEAD_RADIUS / 2.0f;
    const float TERRAIN_HALF_LENGTH = TERRAIN_LENGTH / 2.0f;
    const float TERRAIN_OFFSET = TERRAIN_HALF_LENGTH * 0.9f;
    constexpr float MIN_Z_DIFF = 0.07f;
    constexpr float MIN_Y_DIFF = 0.001f;
    const float TIME = scene.timer.t;

    for (const vec3& position : snake_position_y) {
        float x, y, z; // New x, y, z coordinates of the snake head
        hierarchy_y["head"].transform_local.translation = position;

        // Varying the size and moving type of the snake
        switch (snake_index % 2) {
            case 0: {
                // Snake_0 moves in a straight line along the y-axis.
                hierarchy_y["head"].transform_local.rotation =
                        rotation_transform::from_axis_angle({1, 0, 0}, snake_angle_y[snake_index]);

                x = position[0];
                y = TERRAIN_OFFSET + (int(TIME / TERRAIN_LENGTH + fabs(position[1])) -
                        TIME / TERRAIN_LENGTH - fabs(position[1])) * TERRAIN_LENGTH;

                // Move the snake to the beginning of the terrain if it reaches the edge
                if (fabs(x) > TERRAIN_HALF_LENGTH || fabs(y) > TERRAIN_HALF_LENGTH) {
                    x = position[0];
                    y = TERRAIN_OFFSET;
                    snake_angle_y[snake_index] = 0;
                }

                z = evaluate_terrain_height(x, y) + HEAD_RADIUS_HALF;

                // Change the snake's body inclination if the difference between the previous and new z coordinates is large enough
                if (fabs(z - snake_position_previous_y[snake_index].z) > MIN_Z_DIFF) {
                    if (fabs(y - snake_position_previous_y[snake_index].y) > MIN_Y_DIFF) {
                        float angle = atan((z - snake_position_previous_y[snake_index].z) / (y - snake_position_previous_y[snake_index].y)) - snake_angle_y[snake_index];
                        hierarchy_y["head"].transform_local.rotation =
                                rotation_transform::from_axis_angle({1, 0, 0}, angle);

                        // Save the new angle and the new position into an array for use in the next drawing
                        snake_angle_y[snake_index] = angle;
                        snake_position_previous_y[snake_index] = {x, y, z};
                    }
                }

                hierarchy_y["head"].transform_local.translation = {x, y, z};
                hierarchy_y["head"].transform_local.scaling = HEAD_SCALING_0;
                break;
            }
            case 1: {
                // Snake_1 remains in its position with a pseudo-random body rotation angle
                x = position[0];
                y = position[1];
                z = evaluate_terrain_height(x, y) + HEAD_RADIUS_HALF;

                hierarchy_y["head"].transform_local.rotation =
                        rotation_transform::from_axis_angle({0, 0, 1}, 2 * position[0] - 6 * position[1] + position[2]);
                hierarchy_y["head"].transform_local.translation = {x, y, z};
                hierarchy_y["head"].transform_local.scaling = HEAD_SCALING_1;
                break;
            }
        }

        snake_index++;

        hierarchy_y.update_local_to_global_coordinates();
        draw(hierarchy_y, scene.environment);
    }
}