#include "../includes/ray_tracer.h"

float    ft_huetorgb(float v1, float v2, float h)
{
    if (h < 0)
        h += 1;
    if (h > 1)
        h -= 1;
    if ((6 * h) < 1)
        return (v1 + (v2 - v1) * 6 * h);
    if ((2 * h ) < 1)
        return (v2);
    if ((3 * h) < 2)
        return (v1 + (v2 - v1) * ((2.0f / 3) - h) * 6);
    return (v1);
}

int    ft_rgb(unsigned char r, unsigned char g, unsigned char b)
{
    unsigned int rgb;

    rgb = 0;
    rgb |= (r << 16);
    rgb |= (g << 8);
    rgb |= (b);
    return (rgb);
}

int    ft_hsltorgb(double h, float s, float l)
{
    unsigned char    r;
    unsigned char    g;
    unsigned char    b;
    float            v1;
    float            v2;

    if (s == 0)
    {
        r = (unsigned char)(l * 255);
        g = (unsigned char)(l * 255);
        b = (unsigned char)(l * 255);
    }
    else
    {
        v2 = (l < 0.5) ? (l * (1 + s)) : ((l + s) - (l * s));
        v1 = 2 * l - v2;
        r = (unsigned char)(255 * ft_huetorgb(v1, v2, h + (1.0f / 3)));
        g = (unsigned char)(255 * ft_huetorgb(v1, v2, h));
        b = (unsigned char)(255 * ft_huetorgb(v1, v2, h - (1.0f / 3)));
    }
    return (ft_rgb(r, g, b));
}