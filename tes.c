#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct      s_vec3
{
    float           e[3];
}                   t_vec3;

typedef struct      s_rectangle
{
    t_vec3          translate;
    t_vec3          normal;
    t_vec3          color;
    t_vec3          scale;
    t_vec3          top_left;
    t_vec3          top_right;
    t_vec3          bottom_left;
    t_vec3          bottom_right;
}                   t_rectangle;

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

t_rectangle         *alloc_new_rectangle(t_vec3 trans, t_vec3 normal, t_vec3 color, t_vec3 scale)
{
    t_rectangle     *object;

    object = (t_rectangle*)malloc(sizeof(t_rectangle));
    object->translate = trans;
    object->normal = degree_to_radian(normal);
    object->color = color;
    object->scale = scale;
    return (object);
}

t_vec3      rotate(t_vec3 normal, t_vec3 point)
{
    t_vec3  result;

    //figure out here how to perform a transformation of a point given the normal (begin the transformation) and the point the once to be moved
    //result will be the resulting transformation
}

t_vec3      vec_new(float a, float b, float c)
{
    t_vec3  result;
    
    result.e[0] = a;
    result.e[1] = b;
    result.e[2] = c;
    return (result);
}

int main(int argc, char **argv)
{
    t_rectangle     *rectangle;
                                    //translation     rotation             color                 scale
    rectangle = alloc_new_rectangle(vec_new(1, 1, 1), vec_new(10, 10, 10), vec_new(178, 78, 213), vec_new(1, 1, 1));

    return (0);
}