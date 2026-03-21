#include <iostream>

#include <pcl/point_cloud.h>
#include <pcl/octree/octree_search.h>

float resolution = 128.0f;
pcl::octree::OctreePointCloudSearch<pcl::PointXYZ> tree_search (resolution);
pcl::octree::OctreePointCloud<pcl::PointXYZ> tree (resolution);

// Refs:
// - 2D array interop: https://stackoverflow.com/a/67986571
// - PCL Octree: https://pointclouds.org/documentation/tutorials/octree.html#octree-search

extern "C" void interop_build_octree(float* point_cloud,
                                     int n_points) {
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
    tree_search.setInputCloud(cloud);
    tree_search.addPointsFromInputCloud();

    pcl::PointXYZ searchPoint;
    searchPoint.x = (*cloud)[0].x;
    searchPoint.y = (*cloud)[0].y;
    searchPoint.z = (*cloud)[0].z;

    std::cout << searchPoint.x << std::endl;
    std::cout << searchPoint.y << std::endl;
    std::cout << searchPoint.z << std::endl;

    // Neighbors within voxel search
    std::vector<int> pointIdxVec;
    if (tree_search.voxelSearch(searchPoint, pointIdxVec)) {
        std::cout << "Neighbors within voxel search at (" << searchPoint.x 
                                                   << " " << searchPoint.y 
                                                   << " " << searchPoint.z << ")" 
                                                   << std::endl;
        
        for (std::size_t i = 0; i < pointIdxVec.size(); ++i) {
            std::cout << "    " << (*cloud)[pointIdxVec[i]].x 
                        << " " << (*cloud)[pointIdxVec[i]].y 
                        << " " << (*cloud)[pointIdxVec[i]].z << std::endl;
        }
    }

    tree.setInputCloud(cloud);
    tree.addPointsFromInputCloud();
    std::cout << tree.getLeafCount() << std::endl;
    // Eigen::Vector3f min_pt;
    // Eigen::Vector3f max_pt;
    // tree.getVoxelBounds(min_pt, max_pt);
}

extern "C" void interop_check_ray(float* ray) {
    std::cout << ray[0] << std::endl;
    std::cout << ray[1] << std::endl;
    std::cout << ray[2] << std::endl;

    // auto const ray_array = std::to_array({ray[0], ray[1], ray[2]});
    // auto const intersected_regions = octree.RayIntersectedAll(
    //     zero_point,
    //     ray_array
    // );

    // std::cout << intersected_regions.size() << std::endl;
    // for(long unsigned int i; i < intersected_regions.size(); i++) {
    //     std::cout << intersected_regions[i] << std::endl;
    // }
}
