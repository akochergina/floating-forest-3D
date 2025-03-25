#ifndef CGP_MODELING_MESH_PRIMITIVE_HPP
#define CGP_MODELING_MESH_PRIMITIVE_HPP

#include "cgp/cgp.hpp"


// Creates a mesh object representing a vertically arranged cylinder.
cgp::mesh create_cylinder_mesh(float radius, float height);

// Creates a mesh object representing a vertically arranged cone.
cgp::mesh create_cone_mesh(float radius, float height, float z_offset);

// Creates a mesh object representing the sphere.
cgp::mesh create_sphere_mesh(float radius, const cgp::vec3 &translation);

// Creates a mesh object representing the ellipse.
cgp::mesh create_ellipse_mesh(float semi_major_axis, float semi_minor_axis);

// Creates a mesh object representing a quadrilateral pyramid without a base with the apex pointing downward.
cgp::mesh create_quadrilateral_pyramid(float base, float height);


#endif // CGP_MODELING_MESH_PRIMITIVE_HPP
