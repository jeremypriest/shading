#include <iostream>
#include "octree.h"

OrthoTree::OrthoTreeManaged<OrthoTree::OctreePoint> octree;

// Refs:
// - 2D array interop: https://stackoverflow.com/a/67986571
// - OrthoTree examples: https://github.com/attcs/Octree/blob/master/README.md#basic-examples

extern "C" void interop_build_octree(float* point_cloud,
                                     int n_points,
                                     int depth) {
    // Build the vector of points to pass to the Octree.
    std::vector<OrthoTree::Point3D> points;
    for(int i_point = 0; i_point < n_points; i_point++) {
        points.push_back(OrthoTree::Point3D{point_cloud[i_point * 3 + 0],
                                            point_cloud[i_point * 3 + 1],
                                            point_cloud[i_point * 3 + 2]});
    }

    // Build the Octree and set it as a global variable.
    octree = OrthoTree::OctreePointM(points, depth);
}

extern "C" void interop_check_ray(float* ray) {
    std::cout << ray[0] << std::endl;
    std::cout << ray[1] << std::endl;
    std::cout << ray[2] << std::endl;

    // const auto std::vector = octree.RayIntersectedFirst();
    // const auto std::vector = octree.RayIntersectedAll();
}
