project('shading',
        ['fortran', 'cpp'],
        default_options: ['buildtype=plain',
                          'warning_level=3',
                          'optimization=2',
                          'cpp_std=c++17'])

arch_flag = '-march=native'

cmake = import('cmake')
octree = cmake.subproject('pcl').dependency('pcl_octree')
octree_include_dir_1 = include_directories('./subprojects/pcl/octree/include')
octree_include_dir_2 = include_directories('./subprojects/pcl/common/include')

octree_interop_lib = static_library('octree_interop',
                                    sources: ['octree_interop.cpp'],
                                    cpp_args: arch_flag,
                                    dependencies: [octree],
                                    include_directories: [octree_include_dir_1, octree_include_dir_2],
                                    )

executable('main',
           sources: ['main.f90'],
           fortran_args: arch_flag,
           link_args: arch_flag,
           link_with: [octree_interop_lib],
           )