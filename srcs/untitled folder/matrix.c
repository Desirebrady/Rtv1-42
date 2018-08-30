#include "ray_tracer.h"

// transformation of position vector
t_vec multiply_m_v(t_matrix m, t_vec v)
{
  static t_vec ret;

  ret.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3];
  ret.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3];
  ret.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3];

  return ret;
}

// transformation of direction vector (i.e., no translation)
void multiply_m_v_dir(t_matrix m, t_vec vdir)
{
  static t_vec ret;

  ret.x = m.m[0][0] * vdir.x + m.m[0][1] * vdir.y + m.m[0][2] * vdir.z;
  ret.y = m.m[1][0] * vdir.x + m.m[1][1] * vdir.y + m.m[1][2] * vdir.z;
  ret.z = m.m[2][0] * vdir.x + m.m[2][1] * vdir.y + m.m[2][2] * vdir.z;

  return ret;
}