program shading
    use iso_fortran_env, only: input_unit, output_unit
    use iso_c_binding, only: c_float, c_int
    implicit none

    interface
        subroutine interop_build_octree(point_cloud, &
                                        n_points, &
                                        resolution) &
        bind(C, name='interop_build_octree')
            import :: c_float, c_int
            integer(kind=c_int), value, intent(in) :: n_points
            real(kind=c_float), dimension(3, n_points), intent(in) :: point_cloud
            real(kind=c_float), value, intent(in) :: resolution
        end subroutine
        subroutine get_intersecting_voxel_elements(ray) &
        bind(C, name='interop_get_intersecting_voxel_elements')
            import :: c_float
            real(kind=c_float), dimension(3), intent(in) :: ray
        end subroutine
        subroutine destroy_octree() &
        bind(C, name='interop_destroy_octree')
        end subroutine
    end interface
  
    real(kind=c_float), dimension(:, :), allocatable :: pt_cloud
    integer, parameter :: n_points = 10000000
    real(kind=c_float), parameter :: resolution = 0.01
    real(kind=c_float), dimension(3) :: ray_to_check

    allocate(pt_cloud(3, n_points))
    call random_init(repeatable=.true., image_distinct=.false.)
    call random_number(pt_cloud)

    call build_octree(pt_cloud, resolution)

    ray_to_check = [1.0, 2.0, 3.0]
    call get_intersecting_voxel_elements(ray_to_check)

    call destroy_octree()
    deallocate(pt_cloud)

    contains
        subroutine build_octree(point_cloud, resolution)
            real(kind=c_float), dimension(:, :), allocatable, intent(in) :: point_cloud
            real(kind=c_float), intent(in) :: resolution

            call interop_build_octree(point_cloud, &
                                      size(point_cloud, 2), &
                                      resolution)
        end subroutine
end program