#include "../includes/ray_tracer.h"


/*
** Given the head node, obnject *ptr, and its correlating hit function
** will make head, or append to the linked list
*/

t_hit_list          *append_list(t_hit_list *head, void *object, int (*f)())
{
    t_hit_list      *current;
    t_hit_list      *temp;

    current = (t_hit_list*)ft_memalloc(sizeof(t_hit_list));
    current->type = 1;
    current->object = object;
    current->hit = f;
    current->next = NULL;
    if (head == NULL)
        return (current);
    temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = current;
    return (head);
}


/*
    Future, this will read from a file and create each struct in the list
*/

t_hit_list          *new_hit_list(void)
{
    t_hit_list      *head;
    
    head = NULL;
    head = append_list(head, alloc_sphere(new_vec(0,0,-1), 0.5), sphere_hit);
    head = append_list(head, alloc_sphere(new_vec(0,100.5, -1), 100), sphere_hit);
    return (head);
}