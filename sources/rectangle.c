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

void    scale_planes(t_rectangle *obj)
{
    float scale;

    scale = obj->scale / 2;
    obj->x1 = new_vec( scale, 0, 0);
    obj->x2 = new_vec(-scale, 0, 0);
    obj->y1 = new_vec( 0, scale, 0);
    obj->y2 = new_vec( 0, -scale, 0);
    obj->z1 = new_vec( 0, 0, scale);
    obj->z2 = new_vec( 0, 0, -scale);

    // in radians
    float angle;

    obj->nx1 = degree_to_radian(new_vec(0, 90, 90));
    obj->nx2 = degree_to_radian(new_vec(0, -90, -90));
    obj->ny1 = degree_to_radian(new_vec(90, 0, 90));
    obj->ny2 = degree_to_radian(new_vec(-90, 0, -90));
    obj->nz1 = degree_to_radian(new_vec(90, 90, 0));
    obj->nz2 = degree_to_radian(new_vec(-90, -90, 0));
}

t_vec3        plane_ray_intercept(t_ray *r, t_vec3 p, t_vec3 n)
{
    t_vec3 point;
    float t;
    float d;

    d = length(v_minus_v(p, r->A));

    point = v_mult_v(n, r->A);
    point = v_mult_f(-1, point);
    point = v_plus_v(new_vec(d, d, d), point);
    point = v_div_v(point, v_mult_v(n, r->B));

    return (point);
}

int     ft_rectangle_hit(const t_ray *r, float t_min, float t_max, t_hit_record *rec, void *ptr)
{
    t_rectangle     *object;
    float t;
    t_vec3 point;
 
    //S = r->A  V = r->B
    //D is total distance from origin ?
    //N = plane normal
    point = plane_ray_intercept(r, object->x1, object->nx1);
    t = length(v_minus_v(point, r->A));
    
    if (t >= t_min && t <= t_max && dot(object->x1, point))
    {//x1 is intercepted
        //bounders are y1, y2, z1, z2
    }
    
    point = plane_ray_intercept(r, object->x2, object->nx2);
    t = length(v_minus_v(point, r->A));
    if (t >= t_min && t <= t_max && dot(object->x2, point))
    {//x2 is intercepted
            //bounders are y1, y2, z1, z2
    }

    point = plane_ray_intercept(r, object->y1, object->ny1);
    t = length(v_minus_v(point, r->A));
    if (t >= t_min && t <= t_max && dot(object->y1, point))
    {//y1 is intercepted
        //bounders are x1, x2, z1, z2
    }
    
    point = plane_ray_intercept(r, object->y2, object->ny2);
    t = length(v_minus_v(point, r->A));
    if (t >= t_min && t <= t_max && dot(object->y2, point))
    {//y2 is intercepted
        //bounders are x1, x2, z1, z2
    }
    
    point = plane_ray_intercept(r, object->z1, object->nz1);
    t = length(v_minus_v(point, r->A));
    if (t >= t_min && t <= t_max && dot(object->z1, point))
    {//z1 is intercepted
        //bounders are x1, x2, y1, y2
    }

    point = plane_ray_intercept(r, object->z2, object->nz2);
    t = length(v_minus_v(point, r->A));
    if (t >= t_min && t <= t_max && dot(object->z2, point))
    {//z2 is intercepted
        //bounders are x1, x2, y1, y2
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

void                translate_planes(t_rectangle *obj)
{
    obj->x1 = v_plus_v(obj->x1, obj->translate);
    obj->x2 = v_plus_v(obj->x2, obj->translate);
    obj->y1 = v_plus_v(obj->y1, obj->translate);
    obj->y2 = v_plus_v(obj->y2, obj->translate);
    obj->z1 = v_plus_v(obj->z1, obj->translate);
    obj->z2 = v_plus_v(obj->z2, obj->translate);
}
                                        //location      rotations     color         scaling
t_rectangle         *alloc_rectangle(t_vec3 trans, t_vec3 normal, float scale)
{
    t_rectangle     *object;

    object = (t_rectangle*)malloc(sizeof(t_rectangle));
    object->translate = trans;
    object->normal = degree_to_radian(normal);
    object->scale = scale;
    //1:    Scale points
    scale_planes(object);
    //2:    transform
    //if ((object->normal).e[0] != 0 || (object->normal).e[1] != 0 || (object->normal).e[2] != 0)
    //    transform_points(object);
    //translate
    //translate_rectangle(object);
    translate_planes(object);
    return (object);
}