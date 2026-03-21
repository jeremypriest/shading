program shading
    use iso_fortran_env, only: input_unit, output_unit
    use iso_c_binding, only: c_float, c_int
    implicit none

    interface
        subroutine build_octree(point_cloud, &
                                n_points) &
                                bind(C, name='interop_build_octree')
            import :: c_float, c_int
            integer(kind=c_int), value :: n_points
            real(kind=c_float), dimension(3, n_points) :: point_cloud
        end subroutine
        subroutine check_ray(ray) &
                             bind(C, name='interop_check_ray')
            import :: c_float
            real(kind=c_float), dimension(3) :: ray
        end subroutine
    end interface
  
    real(kind=c_float), dimension(:, :), allocatable :: pt_cloud
    real(kind=c_float), dimension(3) :: ray_to_check

    allocate(pt_cloud(3, 100))

    call random_init(repeatable=.true., image_distinct=.false.)
    call random_number(pt_cloud)

    call build_octree(pt_cloud, size(pt_cloud, 2))

    ray_to_check = [1.0, 2.0, 3.0]
    call check_ray(ray_to_check)

    deallocate(pt_cloud)
end program