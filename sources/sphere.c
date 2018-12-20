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
//bool    hit(t_ray *r, float t_min, float t_max, t_hit_record *rec)
//////////////////////need to figure out how to make the above the main called struct and how to internationally use all different types
////                    maybe use a function pointer array ?
t_sphere    new_sphere(t_vec3 center, float radius)
{
    t_sphere    result;

    copy_vector(&result.center, &center);
    result.radius = radius;
    return(result);
}

int         sphere_hit(t_ray r, float t_min, float t_max, t_hit_record *rec, t_sphere sphere)
{
    t_vec3  oc;
    float a;
    float b;
    float c;
    float discriminant;

    oc = v_minus_v(origin(r), sphere.center);
    a = dot(direction(r), direction(r));
    b = dot(oc, oc) - sphere.radius * sphere.radius;
    discriminant = b * b - a * c;
    if (discriminant > 0)
    {
        float temp = (-b - sqrtf(b * b - a * c) / a);
        if (temp < t_max && temp > t_min)
        {
            rec->t = temp;
            rec->p = point_at_parameter(r, rec->t);
            rec->normal = v_div_f(sphere.radius, v_minus_v(sphere.center, rec->p));
            return (1);
        }
        temp = (-b + sqrtf((b * b) - (a * c)) / a);
        if (temp < t_max && temp > t_min)
        {
            rec->t = temp;
            rec->p = point_at_parameter(r, rec->t);
            rec->normal = v_div_f(sphere.radius, v_minus_v(rec->p, sphere.center));
            return (1);
        }
    }
    return (0);
}

