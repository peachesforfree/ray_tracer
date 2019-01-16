#include "../includes/ray_tracer.h"


/*
**translate: set as object location (x,y,z)
**normal: orientation post rotations in radians(x,y,z)
**color: color of object         (r,g,b)
**scale: how far to scale object (x,y,z)
*/

t_vec3              degree_to_radian(t_vec3 degree)
{
    t_vec3          radian;

    if (degree.e[0] > 360)
        degree.e[0] = fmod(degree.e[0], 360);
    if (degree.e[1] > 360)
        degree.e[1] = fmod(degree.e[1], 360);
    if (degree.e[2] > 360)
        degree.e[2] = fmod(degree.e[2], 360);
    radian.e[0] = degree.e[0] * (M_PI / 180);
    radian.e[1] = degree.e[1] * (M_PI / 180);
    radian.e[2] = degree.e[2] * (M_PI / 180);
    return (radian);
}

t_vec3      rotate_point(t_vec3 normal, t_vec3 point)
{
    t_vec3  result;
    float   x;
    float   y;
    float   z;

    x = normal.e[0];
    y = normal.e[1];
    z = normal.e[2];
    //x axis roation:       normal.e[0] == theta of x
    if (x != 0)
    {
        result.e[0] = point.e[0];
        result.e[1] = (point.e[1] * cos(x)) + (point.e[2] * sin(x));
        result.e[2] = (point.e[1] * -sin(x)) + (point.e[2] * cos(x));
    }
    //y axis roation
    if (y != 0)
    {
        result.e[0] = (point.e[0] * cos(y)) + (point.e[2] * -sin(y));
        result.e[1] = point.e[1];
        result.e[2] = (point.e[0] * sin(y)) + (point.e[2] * cos(y));
    }
    //z axis rotation
    if (z != 0)
    {
        result.e[0] = (point.e[0] * cos(z)) + (point.e[1] * sin(z));
        result.e[1] = (point.e[0] * -sin(z)) + (point.e[1] * cos(z));
        result.e[2] = point.e[2];
    }
    return (result);
}

