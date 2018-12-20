#include <stdio.h>

typedef struct      s_vec3
{
    float   e[3];
}                   t_vec3;

t_vec3        copy_vector(t_vec3 *a, t_vec3 *b)
{
    t_vec3 dest;

    dest.e[0] = b->e[0];
    dest.e[1] = b->e[1];
    dest.e[2] = b->e[2];
    return (dest);
}

t_vec3      v_mult_v(t_vec3 *A, t_vec3 *B)
{
    t_vec3 result;

    result.e[0] = A->e[0] * B->e[0];
    result.e[1] = A->e[1] * B->e[1];
    result.e[2] = A->e[2] * B->e[2];
    return (result);
}

int main(void)
{
    t_vec3 temp;
    t_vec3 test;

    temp.e[0] = 10.5;
    temp.e[1] = 5.5;
    temp.e[2] = 20.20;

    test.e[0] = .5;
    test.e[1] = .5;
    test.e[2] = .5;



    printf("start:%f\t%f\t%f\n", temp.e[0], temp.e[1], temp.e[2]);
    printf("end:  %f\t%f\t%f\n\n", test.e[0], test.e[1], test.e[2]);

    t_vec3 destination = v_mult_v(&temp, &test);

    //printf("start:%f\t%f\t%f\n", temp.e[0], temp.e[1], temp.e[2]);
    printf("end:  %f\t%f\t%f\n", destination.e[0], destination.e[1], destination.e[2]);
}