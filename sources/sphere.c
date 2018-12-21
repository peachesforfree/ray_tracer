#include "../includes/ray_tracer.h"

/*
typedef struct      s_sphere
{
    t_vec3      center;
    float       radius;
}                   t_sphere;

typedef struct      s_hit_record
{
    float   t;
    t_vec3  p;
    t_vec3  normal;
}                   t_hit_record;

*/

t_sphere    *new_sphere(t_vec3 center, float radius)
{
    t_sphere    *result;

    result = (t_sphere*)malloc(sizeof(t_sphere));
    copy_vector(&result->center, &center);
    result->radius = radius;
    result->hit = sphere_hit;
    return(result);
}