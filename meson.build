project('shading',
        ['fortran', 'cpp'],
        default_options: ['buildtype=plain',
                          'warning_level=3',
                          'optimization=2',
                          'cpp_std=c++17'])

arch_flag = '-axCOMMON-AVX512,CORE-AVX512,CORE-AVX2'
add_project_arguments(arch_flag,
                      '-traceback',
                      language: ['fortran', 'cpp'])
add_project_link_arguments(arch_flag,
                           language: ['fortran', 'cpp'])

octree = dependency('pcl_octree')
octree_include_dirs = include_directories('./pcl/x64-linux/include')
octree_interop_lib = static_library('octree_interop',
                                    sources: ['octree_interop.cpp'],
                                    dependencies: [octree],
                                    include_directories: octree_include_dirs,
                                    )

executable('main',
           sources: ['main.f90'],
           link_with: [octree_interop_lib],
           link_language: 'fortran',
           link_args: ['-cxxlib'],
           )