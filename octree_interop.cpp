#include <iostream>

#include <pcl/point_cloud.h>
#include <pcl/octree/octree_search.h>

// Globals
pcl::octree::OctreePointCloudSearch<pcl::PointXYZ>::Ptr octree; // Pointer to Octree
const Eigen::Vector3f zero_vector = {0.0f, 0.0f, 0.0f};

// Refs:
// - 2D array interop: https://stackoverflow.com/a/67986571
// - PCL Octree: https://pointclouds.org/documentation/tutorials/octree.html#octree-search

extern "C" void interop_build_octree(float* point_cloud,
                                     int n_points,
                                     float resolution) {
    // Build the point cloud that we'll build the Octree with.
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    cloud->width = n_points;
    cloud->height = 1;
    cloud->points.resize(n_points);
    for (int i_point = 0; i_point < n_points; i_point++) {
        (*cloud)[i_point].x = point_cloud[i_point * 3 + 0];
        (*cloud)[i_point].y = point_cloud[i_point * 3 + 1];
        (*cloud)[i_point].z = point_cloud[i_point * 3 + 2];
    }

    // Build the Octree and set it as a global variable.
    std::cout << "Resolution = " << resolution << std::endl;
    octree.reset(new pcl::octree::OctreePointCloudSearch<pcl::PointXYZ>(resolution));
    octree->setInputCloud(cloud);
    octree->addPointsFromInputCloud();

    // See how many leaves are in the Octree.
    std::cout << "Number of octree leaves = " << octree->getLeafCount() << std::endl;
}

extern "C" void interop_get_intersecting_voxel_elements(float* ray) {
    std::cout << "Number of octree leaves = " << octree->getLeafCount() << std::endl;

    std::vector<int> intersected_voxel_point_indices;
    int n_intersected_voxels = octree->getIntersectedVoxelIndices(
        zero_vector,
        Eigen::Vector3f{ray[0], ray[1], ray[2]},
        intersected_voxel_point_indices
    );
    std::cout << "Number of voxels intersected by ray = " << n_intersected_voxels << std::endl;
    std::cout << "Number of points in voxels intersected by ray = " << intersected_voxel_point_indices.size() << std::endl;
    // std::cout << "Intersected voxel point indices:" << std::endl;
    // for (long unsigned int i_point = 0; i_point < intersected_voxel_point_indices.size(); i_point++) {
    //     std::cout << intersected_voxel_point_indices[i_point] << std::endl;
    // }
}
