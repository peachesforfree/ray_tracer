#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "libs/libft/libft.h"

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

t_vec3      vec_new(float a, float b, float c)
{
    t_vec3  result;
    
    result.e[0] = a;
    result.e[1] = b;
    result.e[2] = c;
    return (result);
}

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
    object->top_left = vec_new(-(unit / 2) * scale.e[0], (unit / 2) * scale.e[1], 0);
    object->top_right = vec_new((unit / 2) * scale.e[0], (unit / 2) * scale.e[1], 0);
    object->bottom_left = vec_new(-(unit / 2) * scale.e[0], -(unit / 2) * scale.e[1], 0);
    object->bottom_right = vec_new((unit / 2) * scale.e[0], -(unit / 2) * scale.e[1], 0);
}

/*
**Post transformation the corner points are reset incase of extreme rotations
*/

void        transform_points(t_rectangle *object)
{
    t_vec3  points[5];
    t_vec3  temp;
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
    points[4] = vec_new(0, 0, 0);
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


int main(int argc, char **argv)
{
    t_rectangle     *rectangle;
                                    //translation     rotation             color                 scale
    rectangle = alloc_new_rectangle(vec_new(5, 6, -2), vec_new(10, 10, 0), vec_new(178, 78, 213), vec_new(20, 20, 20));

    //1:    Scale points
    scale_points(rectangle);
    //2:    transform
    if ((rectangle->normal).e[0] != 0 || (rectangle->normal).e[1] != 0 || (rectangle->normal).e[2] != 0)
        transform_points(rectangle);
    printf("\nBEFORE TRANSLATION:\nTop left: %f %f %f\t\ttop_right: %f %f %f\nbottom_left: %f %f %f\t\tbottom_right: %f %f %f\n",
            rectangle->top_left.e[0], rectangle->top_left.e[1], rectangle->top_left.e[2],
            rectangle->top_right.e[0], rectangle->top_right.e[1], rectangle->top_right.e[2],
            rectangle->bottom_left.e[0], rectangle->bottom_left.e[1], rectangle->bottom_left.e[2],
            rectangle->bottom_right.e[0], rectangle->bottom_right.e[1], rectangle->bottom_right.e[2]);
    
    
    //3:    translate
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
    printf("\nPOST TRANSLATION:\nTop left: %f %f %f\t\ttop_right: %f %f %f\nbottom_left: %f %f %f\t\tbottom_right: %f %f %f\n",
            rectangle->top_left.e[0], rectangle->top_left.e[1], rectangle->top_left.e[2],
            rectangle->top_right.e[0], rectangle->top_right.e[1], rectangle->top_right.e[2],
            rectangle->bottom_left.e[0], rectangle->bottom_left.e[1], rectangle->bottom_left.e[2],
            rectangle->bottom_right.e[0], rectangle->bottom_right.e[1], rectangle->bottom_right.e[2]);
    return (0);
}