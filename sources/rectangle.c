#include "../includes/ray_tracer.h"


/*
**Post transformation the corner points are reset incase of extreme rotations
*/

void        transform_points(t_rectangle *object)
{
    t_vec3  points[5];
   // t_vec3  temp;
    int i;

    i = -1;
    //transforming all points
    object->top_left = rotate_point(object->normal, object->top_left);
    object->top_right = rotate_point(object->normal, object->top_right);
    object->bottom_left = rotate_point(object->normal, object->bottom_left);
    object->bottom_right = rotate_point(object->normal, object->bottom_right);
    points[0] = object->top_left;
    points[1] = object->top_right;
    points[2] = object->bottom_left;
    points[3] = object->bottom_right;
    points[4] = new_vec(0, 0, 0);
    while (++i < 4)
    {
        if ((points[i]).e[0] < 0 && (points[i]).e[1] > 0)
            object->top_left = points[i];
        else if ((points[i]).e[0] > 0 && (points[i]).e[1] > 0)
            object->top_right = points[i];
        else if ((points[i]).e[0] <= 0 && (points[i]).e[1] <= 0)
            object->bottom_left = points[i];
        else if ((points[i]).e[0] >= 0 && (points[i]).e[1] <= 0)
            object->bottom_right = points[i];
    }
}

/*
**This set and scales the points
*/

void        scale_points(t_rectangle *object)
{
//     t_vec3          scale;   x, y, z
//     t_vec3          top_left;
//     t_vec3          top_right;
//     t_vec3          bottom_left;
//     t_vec3          bottom_right;
    float   unit;
    t_vec3  scale;

    scale = object->scale;
    unit = 1.0;
    object->top_left = new_vec(-(unit / 2) * scale.e[0], (unit / 2) * scale.e[1], 0);
    object->top_right = new_vec((unit / 2) * scale.e[0], (unit / 2) * scale.e[1], 0);
    object->bottom_left = new_vec(-(unit / 2) * scale.e[0], -(unit / 2) * scale.e[1], 0);
    object->bottom_right = new_vec((unit / 2) * scale.e[0], -(unit / 2) * scale.e[1], 0);
}

int     ft_rectangle_hit(const t_ray *r, float t_min, float t_max, t_hit_record *rec, void *ptr)
{
    t_rectangle     *object;

    //guessing A is origin and B is direction
    float t;

    object = ptr;
    //checking for intersection on X axis
    t = (object->scale.e[0] - r->A.e[0])/(r->B.e[0]);
    if (t >= t_min && t_max >= t)
    {
        rec->t = t;
        rec->p = point_at_parameter(*r, rec->t);
        rec->normal = object->normal;
        return (1);
    }        
    return (0);
}

void                translate_rectangle(t_rectangle *rectangle)
{
    rectangle->top_left.e[0] += (rectangle->translate).e[0];
    rectangle->top_left.e[1] += (rectangle->translate).e[1];
    rectangle->top_left.e[2] += (rectangle->translate).e[2];
    rectangle->top_right.e[0] += (rectangle->translate).e[0];
    rectangle->top_right.e[1] += (rectangle->translate).e[1];
    rectangle->top_right.e[2] += (rectangle->translate).e[2];
    rectangle->bottom_left.e[0] += (rectangle->translate).e[0];
    rectangle->bottom_left.e[1] += (rectangle->translate).e[1];
    rectangle->bottom_left.e[2] += (rectangle->translate).e[2];
    rectangle->bottom_right.e[0] += (rectangle->translate).e[0];
    rectangle->bottom_right.e[1] += (rectangle->translate).e[1];
    rectangle->bottom_right.e[2] += (rectangle->translate).e[2];
}
                                        //location      rotations     color         scaling
t_rectangle         *alloc_rectangle(t_vec3 trans, t_vec3 normal, int scale)
{
    t_rectangle     *object;

    object = (t_rectangle*)malloc(sizeof(t_rectangle));
    object->translate = trans;
    object->normal = degree_to_radian(normal);
    object->scale = new_vec(scale, scale, scale);
    //1:    Scale points
    scale_points(object);
    //2:    transform
    //if ((object->normal).e[0] != 0 || (object->normal).e[1] != 0 || (object->normal).e[2] != 0)
    //    transform_points(object);
    //translate
    //translate_rectangle(object);
    return (object);
}