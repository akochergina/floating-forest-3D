#include "mesh_object.hpp"

// Avoid using namespace in implementation files to prevent potential name conflicts
using cgp::vec3;
using cgp::mesh;
using cgp::mat4;


mesh create_foliage_birch() {
    // Define the foliage constants
    constexpr float FOLIAGE_RADIUS_1 = 1.2f;
    constexpr float FOLIAGE_RADIUS_2 = FOLIAGE_RADIUS_1 * 0.7f;
    constexpr float FOLIAGE_RADIUS_3 = FOLIAGE_RADIUS_2 * 0.3f;

    // Define translation vectors for foliage positioning
    const vec3 TRANSLATION_1 = {0, 0, FOLIAGE_RADIUS_1 / 1.2f};
    const vec3 TRANSLATION_2 = {0, 0, FOLIAGE_RADIUS_1 / 1.2f + FOLIAGE_RADIUS_1};
    const vec3 TRANSLATION_3 = {FOLIAGE_RADIUS_2 / 1.5f, FOLIAGE_RADIUS_2 / 1.2f, FOLIAGE_RADIUS_1 / 1.2f + FOLIAGE_RADIUS_1};
    const vec3 TRANSLATION_4 = {-FOLIAGE_RADIUS_1 / 2.0f, -FOLIAGE_RADIUS_1 / 1.2f, FOLIAGE_RADIUS_1 / 1.2f + FOLIAGE_RADIUS_2 / 1.2f};
    const vec3 TRANSLATION_5 = {FOLIAGE_RADIUS_2 / 1.5f - FOLIAGE_RADIUS_3 / 1.5f, FOLIAGE_RADIUS_2 / 1.2f - FOLIAGE_RADIUS_3 / 1.3f, FOLIAGE_RADIUS_1 / 1.2f + FOLIAGE_RADIUS_1 + FOLIAGE_RADIUS_2};
    const vec3 TRANSLATION_6 = {FOLIAGE_RADIUS_1 * 0.6f, FOLIAGE_RADIUS_1 * 0.6f, FOLIAGE_RADIUS_1 * 0.3f};

    // Create foliage mesh and add individual spheres
    mesh foliage_mesh = create_sphere_mesh(FOLIAGE_RADIUS_1, TRANSLATION_1);
    foliage_mesh.push_back(create_sphere_mesh(FOLIAGE_RADIUS_1, TRANSLATION_2));
    foliage_mesh.push_back(create_sphere_mesh(FOLIAGE_RADIUS_2, TRANSLATION_3));
    foliage_mesh.push_back(create_sphere_mesh(FOLIAGE_RADIUS_2, TRANSLATION_4));
    foliage_mesh.push_back(create_sphere_mesh(FOLIAGE_RADIUS_3, TRANSLATION_5));
    foliage_mesh.push_back(create_sphere_mesh(FOLIAGE_RADIUS_3, TRANSLATION_6));

    return foliage_mesh;
}


mesh create_stem_amanite(float height_stem) {
    // Define constants for the stem
    constexpr float STEM_RADIUS = 0.07f;
    constexpr float SKIRT_HEIGHT = 0.3f;
    constexpr float SKIRT_RADIUS = 0.25f;

    // Create stem mesh and add the skirt
    mesh stem_amanite_mesh = create_cylinder_mesh(STEM_RADIUS, height_stem);
    stem_amanite_mesh.push_back(create_cone_mesh(SKIRT_RADIUS, SKIRT_HEIGHT, height_stem / 2));

    return stem_amanite_mesh;
}


mesh create_mosquito() {
    // Define mosquito constants
    constexpr float BREAST_RADIUS = 0.2f;
    constexpr float HEAD_RADIUS = BREAST_RADIUS * 0.5f;
    constexpr float NOSE_RADIUS = HEAD_RADIUS / 3.0f;
    constexpr float NOSE_LENGTH = HEAD_RADIUS * 4.0f;
    constexpr float EYE_RADIUS = HEAD_RADIUS * 0.7f;
    constexpr float BODY_RADIUS = BREAST_RADIUS * 0.7f;
    constexpr float BODY_LENGTH = BREAST_RADIUS * 2.5f;

    // Define translation vectors for parts of the mosquito
    const vec3 TRANSLATION_0 = {0, 0, 0.0f};
    const vec3 TRANSLATION_EYE_1 = {HEAD_RADIUS * 0.5f, -HEAD_RADIUS * 0.4f, 0};
    const vec3 TRANSLATION_EYE_2 = {-HEAD_RADIUS * 0.5f, -HEAD_RADIUS * 0.4f, 0};
    const vec3 TRANSLATION_HEAD = {0, -(BREAST_RADIUS + HEAD_RADIUS) * 0.9f, 0};
    const vec3 TRANSLATION_BODY = {0, (BREAST_RADIUS + BODY_LENGTH) * 0.9f, 0};
    const vec3 TRANSLATION_TAIL = {0, (BREAST_RADIUS + BODY_LENGTH) * 0.9f, 0};

    // Create mosquito body parts and add to the main mosquito mesh
    mesh mosquito = create_sphere_mesh(BREAST_RADIUS, TRANSLATION_0);

    // Create head with nose and eyes
    mesh mosquito_head = create_sphere_mesh(HEAD_RADIUS, TRANSLATION_0);
    mesh nose = create_cone_mesh(NOSE_RADIUS, NOSE_LENGTH, 0);
    nose.apply_transform(mat4(1.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, -1.0f, 0.0f,
                              0.0f, 1.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f));
    mosquito_head.push_back(nose);

    // Adding eyes to the mosquito head
    mosquito_head.push_back(create_sphere_mesh(EYE_RADIUS, TRANSLATION_EYE_1));
    mosquito_head.push_back(create_sphere_mesh(EYE_RADIUS, TRANSLATION_EYE_2));

    // Transform the mosquito head
    mosquito_head.translate(TRANSLATION_HEAD);
    mosquito_head.apply_transform(mat4(1.0f, 0.0f, 0.0f, 0.0f,
                                       0.0f, 0.7f, -0.7f, 0.0f,
                                       0.0f, 0.7f, 0.7f, 0.0f,
                                       0.0f, 0.0f, 0.0f, 1.0f));
    mosquito.push_back(mosquito_head);

    // Create and transform the mosquito body
    mesh mosquito_body = create_cylinder_mesh(BODY_RADIUS, BODY_LENGTH);
    mosquito_body.apply_transform(mat4(1.0f, 0.0f, 0.0f, 0.0f,
                                       0.0f, 0.0f, -1.0f, 0.0f,
                                       0.0f, 1.0f, 0.0f, 0.0f,
                                       0.0f, 0.0f, 0.0f, 1.0f));
    mosquito_body.translate(TRANSLATION_BODY);
    mosquito.push_back(mosquito_body);

    // Add the end part of the mosquito body
    mosquito.push_back(create_sphere_mesh(BODY_RADIUS, TRANSLATION_TAIL));

    return mosquito;
}


cgp::mesh create_mosquito_wing(bool is_left_wing) {
    // Define wing constants
    constexpr float WING_LENGTH = 0.154f;
    constexpr float WING_WIDTH = 0.25f;

    // Create the wing mesh
    mesh wing = create_ellipse_mesh(WING_LENGTH, WING_WIDTH);

    // Apply transformations based on the wing side
    if (is_left_wing) {
        wing.apply_transform(mat4(0.0f, 1.0f, 0.0f, 0.0f,
                                  -1.0f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 1.0f, 1.0f, 0.0f,
                                  0.0f, 0.0f, 0.0f, 1.0f));
        wing.translate({WING_WIDTH, 0.0f, WING_LENGTH});
    } else {
        wing.apply_transform(mat4(0.0f, -1.0f, 0.0f, 0.0f,
                                  1.0f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 1.0f, 1.0f, 0.0f,
                                  0.0f, 0.0f, 0.0f, 1.0f));
        wing.translate({-WING_WIDTH, 0.0f, WING_LENGTH});
    }

    return wing;
}


cgp::mesh create_snake_body() {
    // Define snake body constants
    constexpr float BODY_RADIUS = 0.1f;
    constexpr float BODY_LENGTH = BODY_RADIUS * 6;
    constexpr float TAIL_RADIUS = BODY_RADIUS;
    constexpr float TAIL_LENGTH = BODY_LENGTH;

    // Define translation vectors for body segments
    const vec3 TRANSLATION_0 = {0, 0, 0};
    const vec3 TAIL_TRANSLATION = {0, 4 * BODY_LENGTH, 0};

    // Helper function to create and transform a cylinder
    auto create_and_transform_cylinder = [](float radius, float length, const vec3 &translation) {
        mesh cylinder = create_cylinder_mesh(radius, length);
        cylinder.apply_transform(mat4(1.0f, 0.0f, 0.0f, 0.0f,
                                      0.0f, 0.0f, 1.0f, 0.0f,
                                      0.0f, -1.0f, 0.0f, 0.0f,
                                      0.0f, 0.0f, 0.0f, 1.0f));
        cylinder.translate(translation);
        return cylinder;
    };

    // Helper function to create and transform a cone
    auto create_and_transform_cone = [](float radius, float length, const vec3 &translation) {
        mesh cone = create_cone_mesh(radius, length, 0);
        cone.apply_transform(mat4(1.0f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 0.0f, 1.0f, 0.0f,
                                  0.0f, -1.0f, 0.0f, 0.0f,
                                  0.0f, 0.0f, 0.0f, 1.0f));
        cone.translate(translation);
        return cone;
    };

    // Create snake body segments and add to the main snake mesh
    mesh snake = create_and_transform_cylinder(BODY_RADIUS, BODY_LENGTH, TRANSLATION_0);

    for (int i = 1; i <= 3; ++i) {
        const vec3 TRANSLATION = {0, i * BODY_LENGTH, 0};
        snake.push_back(create_and_transform_cylinder(BODY_RADIUS, BODY_LENGTH, TRANSLATION));
    }

    // Add the tail to the snake mesh
    snake.push_back(create_and_transform_cone(TAIL_RADIUS, TAIL_LENGTH, TAIL_TRANSLATION));

    return snake;
}
