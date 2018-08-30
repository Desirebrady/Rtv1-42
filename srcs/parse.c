/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshumba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 11:11:33 by dshumba           #+#    #+#             */
/*   Updated: 2018/08/28 11:11:34 by dshumba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int ft_rm_char(char *dest, char c)
{
   int removed = 0;
   char *tmp;

   while (*dest)
   {
       tmp = strchr(dest,c);
       if (NULL==tmp)
           break;
       size_t len = strlen(tmp+1);
       memmove(tmp,tmp+1,len);
       tmp[len] = 0;
       ++removed;
       dest=tmp;
   }
   return (removed);
}

t_list          *ignore_comments(t_list *lst)
{
    int     lst_pos;

    lst_pos = -1;
    ft_rm_char(lst->content, '\n');
    if (ft_strequ(lst->content, "/*") == 1)
    {
        while (lst)
        {
            ft_rm_char(lst->content, '\n');
            if (ft_strequ(lst->content, "*/") == 1)
            {
                ft_rm_char(lst->content, '\n');
                if (lst->next != NULL)
                    lst = lst->next;
                break ;
            }
            if (lst->next == NULL)
                break ;
            lst = lst->next;
        }
    }
    return (lst);
}

t_objecttype    get_objecttype(t_list *lst)
{
    t_objecttype    object_type;

    object_type = -1;
    if (ft_strstr(lst->content, "T_CAMERA"))
        object_type = T_CAMERA;
    else if (ft_strstr(lst->content, "T_PLANE"))
        object_type = T_PLANE;
    else if (ft_strstr(lst->content, "T_CUBE"))
        object_type = T_CUBE;
    else if (ft_strstr(lst->content, "T_SPHERE"))
        object_type = T_SPHERE;
    else if (ft_strstr(lst->content, "T_CONE"))
        object_type = T_CONE;
    else if (ft_strstr(lst->content, "T_CYLINDER"))
        object_type = T_CYLINDER;
    else if (ft_strstr(lst->content, "T_PYRAMID"))
        object_type = T_PYRAMID;
    return (object_type);
}

t_vector3       get_vector3(char *str)
{
    t_vector3   vector;
    char        **vector_arr;

    ft_rm_char(str, '\n');
    str = ft_strrchr(str++, '(');
    vector_arr = ft_strsplit(str, ' ');
    vector.x = ft_atoi(vector_arr[0]);
    vector.y = ft_atoi(vector_arr[1]);
    vector.z = ft_atoi(vector_arr[2]);
    return (vector);
}

double          get_value(char *str)
{
    double   value;

    ft_rm_char(str, '\n');
    str = ft_strrchr(str, '=');
    value = ft_atoi(str);
    return (value);
}

unsigned int HexStringToUInt(char const* hexstring)
{
    unsigned int    result;
    char const      *str;
    unsigned int    add;
    char            c;

    result = 0;
    str = hexstring;
    while(*str)
    {
        c = *str;
        result <<= 4;
        if (c >= '0' &&  c <= '9')
            add = c - '0';
        else if (c >= 'A' && c <= 'F')
            add = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f')
            add = c - 'a' + 10;
        else
            return (0x000000);
        result += add;
        ++str;
    }
    return (result);  
}

unsigned int        get_colour(char *str)
{
    unsigned int   colour_hex;

    ft_rm_char(str, '\n');
    str = ft_strrchr(str, 'x');
    ft_rm_char(str, 'x');
    ft_rm_char(str, ';');
    colour_hex = HexStringToUInt(str);
    return (colour_hex);
}

t_object          get_objectinfo(t_list *lst)
{
    t_object    gameobject;

    ft_rm_char(lst->content, ' ');
    gameobject.object_type = get_objecttype(lst);
    while (lst)
    {
        ft_rm_char(lst->content, ' ');
        if (ft_strstr(lst->content, "{"))
        {
            lst = lst->next;
            while (lst)
            {
                if (ft_strstr(lst->content, "position = "))
                    gameobject.transform.position = get_vector3(lst->content);
                else if (ft_strstr(lst->content, "rotation = "))
                    gameobject.transform.rotation = get_vector3(lst->content);
                else if (ft_strstr(lst->content, "colour = "))
                    gameobject.colour = get_colour(lst->content);
                else if (ft_strstr(lst->content, "width = "))
                    gameobject.shape.width = get_value(lst->content);
                else if (ft_strstr(lst->content, "height = "))
                    gameobject.shape.height = get_value(lst->content);
                else if (ft_strstr(lst->content, "depth = "))
                    gameobject.shape.depth = get_value(lst->content);
                else if (ft_strstr(lst->content, "radius = "))
                    gameobject.shape.radius = get_value(lst->content);
                else if (ft_strstr(lst->content, "}"))
                {
                    lst = lst->next;
                    return (gameobject);
                }
                lst = lst->next;
            }
        }
        lst = lst->next;
    }
    return (gameobject);
}

void    parse_list(t_list *lst, t_app *app)
{
    t_list          *tmp_lst;
    int             object_counter;

    lst = ignore_comments(lst);
    tmp_lst = lst;
    ft_rm_char(lst->content, '\n');
    ft_rm_char(lst->content, ' ');
    object_counter = 0;
    while (tmp_lst)
    {
        if (ft_strstr(tmp_lst->content, "OBJECT:"))
            object_counter++;
        tmp_lst = tmp_lst->next;
    }
    app->objectcount = object_counter;
    app->objects = (t_object*)malloc(sizeof(t_object) * (object_counter));
    object_counter = 0;
    while (lst)
    {
        if (ft_strstr(lst->content, "OBJECT:"))
            app->objects[object_counter++] = get_objectinfo(lst);
        lst = lst->next;
    }
}
