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


    
    printf("\nBEFORE TRANSLATION:\nTop left: %f %f %f\t\ttop_right: %f %f %f\nbottom_left: %f %f %f\t\tbottom_right: %f %f %f\n",
            rectangle->top_left.e[0], rectangle->top_left.e[1], rectangle->top_left.e[2],
            rectangle->top_right.e[0], rectangle->top_right.e[1], rectangle->top_right.e[2],
            rectangle->bottom_left.e[0], rectangle->bottom_left.e[1], rectangle->bottom_left.e[2],
            rectangle->bottom_right.e[0], rectangle->bottom_right.e[1], rectangle->bottom_right.e[2]);
    
    
    //3:    translate
    
    printf("\nPOST TRANSLATION:\nTop left: %f %f %f\t\ttop_right: %f %f %f\nbottom_left: %f %f %f\t\tbottom_right: %f %f %f\n",
            rectangle->top_left.e[0], rectangle->top_left.e[1], rectangle->top_left.e[2],
            rectangle->top_right.e[0], rectangle->top_right.e[1], rectangle->top_right.e[2],
            rectangle->bottom_left.e[0], rectangle->bottom_left.e[1], rectangle->bottom_left.e[2],
            rectangle->bottom_right.e[0], rectangle->bottom_right.e[1], rectangle->bottom_right.e[2]);
    return (0);
}