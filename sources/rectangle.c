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
    object->point_scale.e[0] = ((unit) * scale.e[0]) + object->point.e[0];
    object->point_scale.e[1] = ((unit) * scale.e[1]) + object->point.e[1];
    object->point_scale.e[2] = ((unit) * scale.e[2]) + object->point.e[2];

    object->top_left = new_vec(-(unit / 2) * scale.e[0], (unit / 2) * scale.e[1], 0);
    object->top_right = new_vec((unit / 2) * scale.e[0], (unit / 2) * scale.e[1], 0);
    object->bottom_left = new_vec(-(unit / 2) * scale.e[0], -(unit / 2) * scale.e[1], 0);
    object->bottom_right = new_vec((unit / 2) * scale.e[0], -(unit / 2) * scale.e[1], 0);
}

int     ft_rectangle_hit(const t_ray *r, float t_min, float t_max, t_hit_record *rec, void *ptr)
{
    t_rectangle     *object;

    float x = 0, y = 0, z = 0, rx = 1, ry = 1, rz = 1;
    t_vec3 planes;
    int i = 0;
    

    //if Vx = 0
    if (r->B.e[0] == 0)
    {
        //can not intersect either x plane or rx plane ... ray is parallel to these planes
        //leaving NOT x or rx plane
        x = x;
    }
    else if (r->B.e[1] > 0)
    {
        //will not intersect rx plane ... back side of box from plane perspective
        //leaving x plane
        planes.e[i++] = x;
    }
    else if (r->B.e[2] < 0)
    {
        //do not need to test plane x
        //leaving xr plane
        planes.e[i++] = rx;
    }

    if (r->B.e[1] == 0)
    {
        //can not intersect either Y or ry plane
        //leaving NOT y or ry
        y = y;
    }
    else if (r->B.e[1] > 0)
    {
        //leaving y plane
        planes.e[i++] = y;
    }
    else if (r->B.e[1] < 0)
    {
        //leaving ry plane
        planes.e[i++] = ry;
    }

    if (r->B.e[2] == 0)
    {
        //leaving NOT z or rz plane
        z = z;
    }
    else if (r->B.e[2] > 0)
    {
        //leaving z plane
        planes.e[i++] = z;
    }
    else if (r->B.e[2] < 0)
    {
        //leaving rz plane
        planes.e[i++] = rz;
    }
    //once I have a collection of planes to test against ... MUST HAVE AT LEAST 3 PLANES

    /* first plane is within tmin and tmax
        OR second plane is within tmin amd tmax
        OR third plane is within tmin and tmax*/
    float t;

    //t = v_div_v(v_minus_v(planes, r->A), r->B);  
    //left off here ... need to find a way to dinamically store the plane values by which ones are potentially intersected
    // might just beak it up into 6 seperate functions for each face of the cube.
    // that way t=rx-−Sx/Vx can be run for each possible plane and the other planes 
    //      0≤[P(t)]y ≤ry   0≤[P(t)]z ≤rz.  can be run speciffically for each opposing plane
    if (i == 4)
    {
            //to lie within the corresponding face of the box the Y and Z coordinates of point p(t) must satisfy
            //0 <=[P(t)]y <= Ry
            //0 <=[P(t)]z <= Rz
        if (0 <= t.e[0])   
    }


















    // //guessing A is origin and B is direction
    // t_vec3 t;

    // object = ptr;
    // //checking for intersection on X axis
    // t = v_div_v(v_minus_v(object->point, r->A), r->B);
    // if ((t.e[0] >= t_min && t_max >= t.e[0]))
    // {
    //     if (0 <= object->point_scale.e[1] && 0 >= object->point.e[1])
    //         //&& t.e[2] <= object->point_scale.e[2] && t.e[2] >= object->point.e[2])
    //     { 
    //         rec->t = t.e[0];
    //         rec->p = point_at_parameter(*r, rec->t);
    //         rec->normal = object->normal;
    //         return (1);
    //     }
    // }
    // else if (t.e[1] >= t_min && t_max >= t.e[1]) 
    // {
    //     if (0 <= object->point_scale.e[1] && 0 >= object->point.e[1])
    //         //&& t.e[2] <= object->point_scale.e[2] && t.e[2] >= object->point.e[2])
    //     { 
    //         rec->t = t.e[0];
    //         rec->p = point_at_parameter(*r, rec->t);
    //         rec->normal = object->normal;
    //         return (1);
    //     }
    // }
    // else if (t.e[2] >= t_min && t_max >= t.e[2]) 
    // {
    //     if (0 <= object->point_scale.e[1] && 0 >= object->point.e[1])
    //         //&& t.e[2] <= object->point_scale.e[2] && t.e[2] >= object->point.e[2])
    //     { 
    //         rec->t = t.e[0];
    //         rec->p = point_at_parameter(*r, rec->t);
    //         rec->normal = object->normal;
    //         return (1);
    //     }
    // }
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
t_rectangle         *alloc_rectangle(t_vec3 trans, t_vec3 normal, float scale)
{
    t_rectangle     *object;

    object = (t_rectangle*)malloc(sizeof(t_rectangle));
    object->translate = trans;
    object->normal = degree_to_radian(normal);
    object->scale = new_vec(scale, scale, scale);
    object->point = trans;
    //1:    Scale points
    scale_points(object);
    //2:    transform
    //if ((object->normal).e[0] != 0 || (object->normal).e[1] != 0 || (object->normal).e[2] != 0)
    //    transform_points(object);
    //translate
    //translate_rectangle(object);
    return (object);
}