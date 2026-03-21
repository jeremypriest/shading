project('shading',
        ['fortran', 'cpp'],
        default_options: ['buildtype=plain',
                          'warning_level=3',
                          'optimization=2',
                          'cpp_std=c++17'])

arch_flag = '-march=native'

cmake = import('cmake')
cmake_opts = cmake.subproject_options()
cmake_opts.add_cmake_defines({
        'PCL_SHARED_LIBS': 'OFF',
        'BUILD_common': 'ON',
        'BUILD_octree': 'ON',
        'BUILD_features': 'OFF',
        'BUILD_filters': 'OFF',
        'BUILD_global_tests': 'OFF',
        'BUILD_io': 'OFF',
        'BUILD_kdtree': 'OFF',
        'BUILD_keypoints': 'OFF',
        'BUILD_ml': 'OFF',
        'BUILD_range_image': 'OFF',
        'BUILD_registration': 'OFF',
        'BUILD_sample_consensus': 'OFF',
        'BUILD_segmentation': 'OFF',
        'BUILD_surface': 'OFF',
        'BUILD_visualization': 'OFF',
        })
cmake_pcl = cmake.subproject('pcl', options: cmake_opts)
octree = cmake_pcl.dependency('pcl_octree')
octree_include_dirs = include_directories('./subprojects/pcl/octree/include',
                                          './subprojects/pcl/common/include')

octree_interop_lib = static_library('octree_interop',
                                    sources: ['octree_interop.cpp'],
                                    cpp_args: arch_flag,
                                    dependencies: [octree],
                                    include_directories: octree_include_dirs,
                                    )

executable('main',
           sources: ['main.f90'],
           fortran_args: arch_flag,
           link_args: arch_flag,
           link_with: [octree_interop_lib],
           )