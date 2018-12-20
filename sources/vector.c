#include "../includes/ray_tracer.h"

float   x(t_vec3 *A)
{
    return (A->e[0]);
}

float   y(t_vec3 *A)
{
    return (A->e[1]);    
}

float   z(t_vec3 *A)
{
    return (A->e[2]);  
}

float   r(t_vec3 *A)
{
    return (A->e[0]);  
}

float   g(t_vec3 *A)
{
    return (A->e[1]);  
}

float   b(t_vec3 *A)
{
    return (A->e[2]);  
}

void  set_vec(t_vec3 *vec, float A, float B, float C)
{
    vec->e[0] = A;
    vec->e[1] = B;
    vec->e[2] = C;
}