project('shading',
        ['fortran', 'cpp'],
        default_options: ['buildtype=plain',
                          'warning_level=3',
                          'optimization=2',
                          'cpp_std=c++20'])

arch_flag = '-march=native'

cmake = import('cmake')
octree = cmake.subproject('Octree').dependency('OrthoTree')
octree_include_dir = include_directories('./subprojects/Octree/include/orthotree')

octree_interop_lib = static_library('octree_interop',
                                    sources: ['octree_interop.cpp'],
                                    cpp_args: arch_flag,
                                    dependencies: [octree],
                                    include_directories: octree_include_dir,
                                    )

executable('main',
           sources: ['main.f90'],
           fortran_args: arch_flag,
           link_args: arch_flag,
           link_with: [octree_interop_lib],
           )