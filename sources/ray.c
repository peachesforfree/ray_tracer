#include "../includes/ray_tracer.h"

t_vec3      v_mult_v(t_vec3 A, t_vec3 B)
{
    t_vec3 result;

    result.e[0] = A.e[0] * B.e[0];
    result.e[1] = A.e[1] * B.e[1];
    result.e[2] = A.e[2] * B.e[2];
    return (result);
}

t_vec3      v_plus_v(t_vec3 A, t_vec3 B)
{
    t_vec3 result;

    result.e[0] = A.e[0] + B.e[0];
    result.e[1] = A.e[1] + B.e[1];
    result.e[2] = A.e[2] + B.e[2];
    return (result);
}

t_vec3      v_div_v(t_vec3 A, t_vec3 B)
{
    t_vec3  result;

    result.e[0] = A.e[0] / B.e[0];
    result.e[1] = A.e[1] / B.e[1];
    result.e[2] = A.e[2] / B.e[2];
    return (result);
}

t_vec3      v_minus_v(t_vec3 A, t_vec3 B)
{
    t_vec3  result;

    result.e[0] = A.e[0] - B.e[0];
    result.e[1] = A.e[1] - B.e[1];
    result.e[2] = A.e[2] - B.e[2];
    return (result);
}

t_vec3      v_mult_f(float t, t_vec3 B)
{
    t_vec3  result;

    result.e[0] = B.e[0] * t;
    result.e[1] = B.e[1] * t;
    result.e[2] = B.e[2] * t;
    return (result);
}

t_vec3      v_div_f(float t, t_vec3 B)
{
    t_vec3  result;

    result.e[0] = B.e[0] / t;
    result.e[1] = B.e[1] / t;
    result.e[2] = B.e[2] / t;
    return (result);
}

void        copy_vector(t_vec3 *a, t_vec3 *b)
{
    a->e[0] = b->e[0];
    a->e[1] = b->e[1];
    a->e[2] = b->e[2];
}

float       dot(t_vec3 A, t_vec3 B)
{
    float result;

    result = A.e[0] * B.e[0];
    result += A.e[1] * B.e[1];
    result += A.e[2]  * B.e[2];
    return (result);
}

t_vec3      cross(t_vec3 A, t_vec3 B)
{
    t_vec3  result;

    result.e[0] = A.e[1] * B.e[2] - A.e[2] * B.e[1];
    result.e[1] = -(A.e[0] * B.e[2] - A.e[2] * B.e[0]);
    result.e[2] = A.e[0] * B.e[1] - A.e[1] * B.e[0];
    return (result);
}

t_vec3      point_at_parameter(t_ray ray, float t)
{
    t_vec3 dest;

    dest = v_mult_f(t, ray.B);
    dest = v_plus_v(ray.A, dest);
    return(dest);
}

t_vec3      direction(const t_ray ray)
{
    return (ray.B);
}

t_vec3      origin(t_ray ray)
{
    return (ray.A);
}

t_ray       new_ray(t_vec3 A, t_vec3 B)
{
    t_ray   ray;

    copy_vector(&ray.A, &A);
    copy_vector(&ray.B, &B);
    return (ray);
}

float   length(t_vec3 A)
{
    float result;

    result = A.e[0] * A.e[0];
    result += A.e[1] * A.e[1];
    result += A.e[2] * A.e[2];
    result = sqrtf(result);
    return (result);
}

float   squared_length(t_vec3 A)
{
    float result;
    result = A.e[0] * A.e[0];
    result += A.e[1] * A.e[1];
    result  += A.e[2] * A.e[2];
    return (result);
}

void    make_unit_vector(t_vec3 *A)
{
    float result;

    result = 1.0 / sqrtf(squared_length(*A));
    A->e[0] = result;
    A->e[1] = result;
    A->e[2] = result;
}

t_vec3      unit_vector(t_vec3 A)
{
    return (v_div_f(length(A), A));
}