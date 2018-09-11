#include "../includes/rtv1.h"

double  **set_matrix_identity()
{
   double **ret_matrix;
   int x;
   int y;
   int shift_idetity;

   x = -1;
   y = -1;
   shift_idetity = 0;
   ret_matrix = (double**)malloc(sizeof(double) * 4);
   while (++x < 4)
       ret_matrix[x] = (double*)malloc(sizeof(double) * 4);
   while (++y < 4)
   {
       x = -1;
       while (++x < 4)
       {
           if (x == shift_idetity)
              ret_matrix[y][x] = 1;
           else
               ret_matrix[y][x] = 0;
       }
       shift_idetity++;
   }
   return (ret_matrix);
}

double  **matrix_multiply(double **m1, double **m2)
{
    double    **ret_matrix;
    int        x;
    int        y;

    y = -1;
    ret_matrix = set_matrix_identity();
    while (++y < 4)
    {
        x = -1;
        while (++x < 4)
            ret_matrix[y][x] = m1[0][x] * m2[y][0] + m1[1][x] * m2[y][1] + m1[2][x] * m2[y][2] + m1[3][x] * m2[y][3];
    }
    return (ret_matrix);
}
float invert_function(int i, int j, double **m)
{
    int        o;
    float    inv;
    
    o = 2 + (j - i);
    i += 4 + o;
    j += 4 - o;
    #define e(a,b) m[((j + b) % 4)] [((i + a) % 4)]
    inv =
    + e(1, -1) * e(0, 0) * e(-1, 1)
    + e(1, 1) * e(0, -1) * e(-1, 0)
    + e(-1, -1) * e(1, 0) * e(0, 1)
    - e(-1, -1) * e(0, 0) * e(1, 1)
    - e(-1, 1) * e(0, -1) * e(1, 0)
    - e(1, -1) * e(-1, 0) * e(0, 1);
    #undef e
    return (o % 2) ? inv : -inv;
}

int matrix_inverse(double **m, double **out)
{
   double    inv[4][4];
   int        i;
    int        j;
    double    deternminant;

    i = -1;
    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
            inv[j][i] = invert_function(i, j, m);
    }
   deternminant = 0;
   i = -1;
    while (++i < 4)
        deternminant += m[0][i] * inv[i][0];
   if (deternminant == 0)
       return 0;
   deternminant = 1.0 / deternminant;
   i = -1;
    while (++i < 16)
        out[i / 4][i % 4] = inv[i / 4][i % 4] * deternminant;
   return 1;

}