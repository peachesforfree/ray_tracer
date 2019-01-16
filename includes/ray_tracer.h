#ifndef RAYTRACERH
#define RAYTRACERH

#include "../libs/libft/libft.h"
#include "../libs/minilibx/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/keys.h"
#include <math.h>

//3200 x 1800 mac standard resolution?

//Screen dimensions
#define WIN_X 800
#define WIN_Y 400
#define SAMPLE_COUNT 1000
#define MARCH_DEPTH 50

//material types
#define MATERIAL_TYPES 3
#define LAMBERTIAN  0
#define METAL       1
#define DIELECTRIC  2

#define SPHERE      1
#define RECTANGLE   2
#define CYLINDER    3
#define CONE        4
#define TRIANGLE    5

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*img_ptr;
	int			bpp;
	int			size_line;
	int			endian;
	void		*tmp_map;
}				t_mlx;

typedef struct      s_vec3
{
    float   e[3];
}                   t_vec3;

typedef struct      s_ray
{
    t_vec3      A;
    t_vec3      B;
}                   t_ray;

typedef struct      s_hit_list
{
    int             type;
    void            *object;
//    int             (*hit)();
    int             material_id;
    void            *material;
    struct s_hit_list      *next;
}                   t_hit_list;

typedef struct      s_hit_record
{
    float           t;
    t_vec3          p;
    t_vec3          normal;
    t_hit_list      *current_object;
}                   t_hit_record;

typedef struct      s_hit_data
{
    t_ray           r;
    float           tmin;
    float           tmax;
}                   t_hit_data;

typedef struct      s_sphere_hit_data
{
    t_vec3          oc;
    float           a;
    float           b;
    float           c;
    float           discriminant;
}                   t_sphere_hit_data;

typedef struct      s_sphere
{
    t_vec3              center;
    float               radius;
}                   t_sphere;

typedef struct      s_camera
{
    t_vec3  origin;
    t_vec3  lower_left_corner;
    t_vec3  horizontal;
    t_vec3  vertical;
}                   t_camera;

typedef struct      s_metal
{
    t_vec3          albedo;
    float           fuzz;
}                   t_metal;

typedef struct      s_lambertian
{
    t_vec3      albedo;
}                   t_lambertian;

typedef struct      s_dielectric
{
    float           ref_idx;
    float           fuzz;
}                   t_dielectric;

typedef struct      s_matrix
{
    float           o[4][4];
}                   t_matrix;


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

//hit list functions
t_hit_list *new_hit_list(void);


//Ray and vector functions
t_ray       new_ray(t_vec3 A, t_vec3 B);
t_vec3      origin(t_ray ray);
t_vec3      direction(const t_ray ray);
t_vec3      point_at_parameter(t_ray ray, float t);//\\\\\\\//
t_vec3      cross(t_vec3 A, t_vec3 B);
float       dot(t_vec3 A, t_vec3 B);//
void        copy_vector(t_vec3 *a, t_vec3 *b);
t_vec3      v_div_f(float t, t_vec3 B);//
t_vec3      v_minus_f(float t, t_vec3 B);
t_vec3      v_mult_f(float t, t_vec3 B);//
t_vec3      v_minus_v(t_vec3 A, t_vec3 B);//
t_vec3      v_div_v(t_vec3 A, t_vec3 B);//
t_vec3      v_plus_v(t_vec3 A, t_vec3 B);//
t_vec3      v_mult_v(t_vec3 A, t_vec3 B);//
float       length(t_vec3 A);
float       squared_length(t_vec3 A);
void        make_unit_vector(t_vec3 *A);
t_vec3      unit_vector(t_vec3 A);


//Vector func
float   x(t_vec3 *A);
float   y(t_vec3 *A);
float   z(t_vec3 *A);
float   r(t_vec3 *A);
float   g(t_vec3 *A);
float   b(t_vec3 *A);
void    set_vec(t_vec3 *vec, float A, float B, float C);
t_vec3      new_vec(float a, float b, float c);



//MLX functions
void		mlx_start(t_mlx *env);

//Color Functions
int    ft_rgb(unsigned char r, unsigned char g, unsigned char b);
int    ft_hsltorgb(double h, float s, float l);
float    ft_huetorgb(float v1, float v2, float h);

//sphere
int         ft_sphere_hit(const t_ray *r, float t_min, float t_max, t_hit_record *rec, void *ptr);
t_sphere    *alloc_sphere(t_vec3 center, float radius);
t_vec3      random_in_sphere();

//rectangle
t_rectangle         *alloc_new_rectangle(t_vec3 trans, t_vec3 normal, t_vec3 color, t_vec3 scale);



//material functions
int     metal_scatter(t_ray *ray,  t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered, void *ptr);
int     lambertian_scatter(t_ray *ray, t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered, void *ptr);
int     dielectric_scatter(t_ray *ray, t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered, void *ptr);

//fun math stuff
t_vec3      degree_to_radian(t_vec3 degree);
t_vec3      rotate_point(t_vec3 normal, t_vec3 point);




//camera
t_camera    init_camera(t_vec3 look_from, t_vec3 look_at, t_vec3 vert_up,  float vfov, float aspect);
t_ray    get_ray(t_camera *cam, float u, float v);

#endif