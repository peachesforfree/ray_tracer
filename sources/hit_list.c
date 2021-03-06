#include "../includes/ray_tracer.h"

//dispatch table stuff
//http://vandervoord.net/blog/2015/6/2/making-function-pointers-usable-in-c

void    *alloc_new_lambertian(t_vec3 values)
{
    t_lambertian    *object;

    object = ft_memalloc(sizeof(t_lambertian));
    object->albedo = values;
    return (object);
}

void    *alloc_new_metal(t_vec3 values, float f)
{
    t_metal     *object;

    object = ft_memalloc(sizeof(t_metal));
    object->albedo =  values;
    //copy_vector(&object->albedo, &values);
    if (f < 0 || f > 1)
        object->fuzz = 1;
    else
        object->fuzz = f;
    return (object);
}

void    *alloc_new_dielectric(float refrac_index, float fuzz)
{
    t_dielectric    *object;

    object = ft_memalloc(sizeof(t_dielectric));
    object->ref_idx = refrac_index;
    object->fuzz = fuzz;
    return (object);
}

/*
** Given the head node, obnject *ptr, and its correlating hit function
** will make head, or append to the linked list
*/

t_hit_list          *append_list(t_hit_list *head, void *object, int id_type, int id_material, void *material_ptr)
{
    t_hit_list      *current;
    t_hit_list      *temp;

    current = (t_hit_list*)ft_memalloc(sizeof(t_hit_list));
    current->object = object;
    current->type = id_type;
    current->material_id = id_material;
    current->material = material_ptr;
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
    head = append_list(head, alloc_sphere(new_vec(0,1,-1), 0.5), SPHERE, LAMBERTIAN, alloc_new_lambertian(new_vec(0.1, 0.2, 0.5)));
    head = append_list(head, alloc_sphere(new_vec(0,-100.5, -1), 100), SPHERE, LAMBERTIAN, alloc_new_lambertian(new_vec(0.8, 0.8, 0.0)));
    head = append_list(head, alloc_sphere(new_vec( 1, 0, -1), 0.5), SPHERE, METAL, alloc_new_metal(new_vec( 0.8, 0.6, 0.2), 0.0));
    //head = append_list(head, alloc_sphere(new_vec( -1, 0, -1), 0.5), SPHERE, METAL, alloc_new_metal(new_vec( 0.8, 0.8, 0.8), 1.0));
    //head = append_list(head, alloc_sphere(new_vec( -1, 0, -1), 0.5), SPHERE, DIELECTRIC, alloc_new_dielectric(1.5, 0.0));
    head = append_list(head, alloc_rectangle(new_vec(0, 0, 0), new_vec(0, 0, 0)/* <- input as degree*/, 0.5), RECTANGLE, LAMBERTIAN, alloc_new_lambertian(new_vec(0.83, 0.0, 0.0)));
    //head = append_list(head, alloc_sphere(new_vec( -1, 0, -1), -0.45), SPHERE, DIELECTRIC, alloc_new_dielectric(1.5, 0.0));
    
    //head = append_list(head, alloc_sphere(new_vec(0,0,-1), 0.5), SPHERE);

    return (head);
}


//there is a compile error because of how the function pointer is declared.
//  follow http://vandervoord.net/blog/2015/6/2/making-function-pointers-usable-in-c to figure out how to use a dispatch table to do it
// ...maybe use a dispatch table that is attatched to the linked list that is referenced by an 'ID' variable in the list.