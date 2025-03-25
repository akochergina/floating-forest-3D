
#include "cgp/cgp.hpp"
using namespace cgp;
#include "mesh_primitive.hpp"

mesh create_cylinder_mesh(float radius, float height) {
    mesh cylinder;

    // Number of samples
    constexpr int N = 20;
    constexpr float TWO_PI = 2 * 3.14f;

    // Geometry
    for (int k = 0; k < N; ++k) {
        float u = k / float(N - 1);
        float theta = TWO_PI * u;

        vec3 base = {radius * std::cos(theta), radius * std::sin(theta), 0.0f};
        vec3 top = base + vec3(0, 0, height);

        cylinder.position.push_back(base);
        cylinder.position.push_back(top);

        cylinder.uv.push_back({4 * u, 0});
        cylinder.uv.push_back({4 * u, 4});
    }

    // Connectivity
    for (int k = 0; k < N - 1; ++k) {
        int u00 = 2 * k;
        int u01 = 2 * k + 1;
        int u10 = 2 * (k + 1);
        int u11 = 2 * (k + 1) + 1;

        cylinder.connectivity.push_back({u00, u10, u11});
        cylinder.connectivity.push_back({u00, u11, u01});
    }

    // Close the cylinder
    int last = 2 * (N - 1);
    cylinder.connectivity.push_back({last, 0, 1});
    cylinder.connectivity.push_back({last, 1, last + 1});

    cylinder.fill_empty_field();

    return cylinder;
}

mesh create_cone_mesh(float radius, float height, float z_offset) {
    mesh cone;

    // Constants
    constexpr int N = 20;
    constexpr float TWO_PI = 2 * 3.14f;

    // Geometry: base of the cone
    for (int k = 0; k < N; ++k) {
        float u = k / float(N - 1);
        float theta = TWO_PI * u;
        vec3 p = {radius * std::cos(theta), radius * std::sin(theta), z_offset};
        cone.position.push_back(p);
        cone.uv.push_back({u, 0});
    }

    // Apex of the cone
    cone.position.push_back({0, 0, height + z_offset});
    cone.uv.push_back({0.5f, 1.0f});

    // Connectivity: sides of the cone
    for (int k = 0; k < N; ++k) {
        int next = (k + 1) % N;
        cone.connectivity.push_back({k, next, N});
    }

    // Close the bottom of the cone
    // Geometry
    for (int k = 0; k < N; ++k) {
        float u = k / float(N - 1);
        float theta = TWO_PI * u;
        vec3 p = {radius * std::cos(theta), radius * std::sin(theta), z_offset};
        cone.position.push_back(p);
        cone.uv.push_back({std::cos(theta), std::sin(theta)});
    }

    // Central position
    cone.position.push_back({0, 0, z_offset});
    cone.uv.push_back({0, 0});

    // Connectivity: bottom of the cone
    int base_center_index = 2 * N + 1;
    for (int k = 0; k < N; ++k) {
        int next = (k + 1) % N;
        cone.connectivity.push_back({N + k, N + next, base_center_index});
    }

    cone.fill_empty_field();
    return cone;
}


mesh create_sphere_mesh(float radius, const vec3& translation) {
    mesh sphere;
    int N = 10;
    sphere.position.resize((N + 1) * (N + 1));
    sphere.uv.resize((N + 1) * (N + 1));

    // Fill sphere geometry
    for (int stack = 0; stack <= N; ++stack) {
        float phi = stack * Pi / N; // angle from top
        float y = radius * std::cos(phi);

        for (int slice = 0; slice <= N; ++slice) {
            float theta = slice * 2 * Pi / N; // angle around
            float x = radius * std::sin(phi) * std::cos(theta);
            float z = radius * std::sin(phi) * std::sin(theta);

            float u = stack / float(N);
            float v = slice / float(N);

            vec3 p = {x + translation.x, y + translation.y, z + translation.z};
            vec2 uv = {5 * (1.0f - u), 5 * (1.0f - v)};

            sphere.position[slice + (N + 1) * stack] = p;
            sphere.uv[slice + (N + 1) * stack] = uv;
        }
    }

    // Generate triangle organization
    for (int stack = 0; stack < N; ++stack) {
        for (int slice = 0; slice < N; ++slice) {
            int idx = slice + (N + 1) * stack;

            uint3 triangle_1 = {idx, idx + 1, idx + N + 1};
            uint3 triangle_2 = {idx + 1, idx + N + 2, idx + N + 1};

            sphere.connectivity.push_back(triangle_1);
            sphere.connectivity.push_back(triangle_2);
        }
    }

    sphere.fill_empty_field();
    return sphere;
}

mesh create_ellipse_mesh(float a, float b) {
    // Constants
    constexpr int SEGMENTS = 36;
    constexpr int CENTER_INDEX = 0;

    mesh ellipse;

    // Center of the ellipse
    ellipse.position.push_back({0.0f, 0.0f, 0.0f});
    ellipse.uv.push_back({0.5f, 0.5f});

    // Vertices around the ellipse
    for (int i = 0; i <= SEGMENTS; ++i) {
        float theta = 2.0f * M_PI * float(i) / float(SEGMENTS);
        float x = a * cos(theta);
        float y = b * sin(theta);
        ellipse.position.push_back({x, y, 0.0f});

        // Texture coordinates (optional, if you need texturing)
        float u = 0.5f + 0.5f * cos(theta);
        float v = 0.5f + 0.5f * sin(theta);
        ellipse.uv.push_back({u, v});
    }

    // Connectivity (creating triangles)
    for (int i = 1; i <= SEGMENTS; ++i) {
        int nextIndex = (i % SEGMENTS) + 1;
        ellipse.connectivity.push_back({CENTER_INDEX, i, nextIndex});
    }

    ellipse.fill_empty_field();
    return ellipse;
}

cgp::mesh create_quadrilateral_pyramid(float base, float height) {
    cgp::mesh pyramid;

    // Constants
    const float HALF_BASE = base / 2.0f;

    // Define the vertices of the pyramid
    pyramid.position = {
            { -HALF_BASE, -HALF_BASE, 0.0f },  // Vertex 0: bottom left corner
            { HALF_BASE, -HALF_BASE, 0.0f },   // Vertex 1: bottom right corner
            { HALF_BASE, HALF_BASE, 0.0f },    // Vertex 2: top right corner
            { -HALF_BASE, HALF_BASE, 0.0f },   // Vertex 3: top left corner
            { 0.0f, 0.0f, -height }            // Vertex 4: apex (top point)
    };

    // Define the UV coordinates for texturing
    pyramid.uv = {
            {0.0f, 0.0f},  // For vertex 0
            {1.0f, 0.0f},  // For vertex 1
            {1.0f, 1.0f},  // For vertex 2
            {0.0f, 1.0f},  // For vertex 3
            {0.5f, 0.5f}   // For vertex 4 (apex), using central texture coordinate
    };

    // Define the connectivity (creating triangles for the faces)
    pyramid.connectivity = {
            {0, 1, 4},  // Side face 1
            {1, 2, 4},  // Side face 2
            {2, 3, 4},  // Side face 3
            {3, 0, 4},  // Side face 4
    };

    // Fill in any missing fields
    pyramid.fill_empty_field();

    return pyramid;
}
