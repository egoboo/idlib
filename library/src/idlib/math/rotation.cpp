#include "idlib/math/rotation.hpp"

namespace idlib {

matrix<single, 4, 4> rotation_x(const angle<single, degrees>& a)
{ return rotation_x(semantic_cast<angle<single, radians>>(a)); }

matrix<single, 4, 4> rotation_x(const angle<single, turns>& a)
{ return rotation_x(semantic_cast<angle<single, radians>>(a)); }

matrix<single, 4, 4> rotation_x(const angle<single, radians>& a)
{
	single c = std::cos(a), s = std::sin(a);
	return
		matrix<single, 4, 4>
		(
			1,  0,  0, 0,
			0, +c, -s, 0,
			0, +s,  c, 0,
			0,  0,  0, 1
		);
}

matrix<single, 4, 4> rotation_y(const angle<single, degrees>& a)
{ return rotation_y(semantic_cast<angle<single, radians>>(a)); }

matrix<single, 4, 4> rotation_y(const angle<single, turns>& a)
{ return rotation_y(semantic_cast<angle<single, radians>>(a)); }

matrix<single, 4, 4> rotation_y(const angle<single, radians>& a)
{
    single c = std::cos(a), s = std::sin(a);
    return
        matrix<single, 4, 4>
        (
            +c, 0, +s, 0,
             0, 1,  0, 0,
            -s, 0, +c, 0,
             0, 0,  0, 1
        );
}

 matrix<single, 4, 4> rotation_z(const angle<single, degrees>& a)
{ return rotation_z(semantic_cast<angle<single, radians>>(a)); }

matrix<single, 4, 4> rotation_z(const angle<single, turns>& a)
{ return rotation_z(semantic_cast<angle<single, radians>>(a)); }

matrix<single, 4, 4> rotation_z(const angle<single, radians>& a)
{
    single c = std::cos(a), s = std::sin(a);
    return
        matrix<single, 4, 4>
        (
            +c, -s, 0, 0,
            +s, +c, 0, 0,
             0,  0, 1, 0,
             0,  0, 0, 1
        );
}

matrix<single, 4, 4> rotation(const vector<single, 3>& axis, const angle<single, degrees>& angle)
{ return rotation(axis, semantic_cast<idlib::angle<single, radians>>(angle)); }

matrix<single, 4, 4> rotation(const vector<single, 3>& axis, const angle<single, turns>& angle)
{ return rotation(axis, semantic_cast<idlib::angle<single, radians>>(angle)); }

matrix<single, 4, 4> rotation(const vector<single, 3>& axis, const angle<single, radians>& angle)
{
    single c = std::cos(angle), s = std::sin(angle);
    single t = 1.0f - c;
    single x = axis[0], y = axis[1], z = axis[2];
    single xx = x*x, yy = y*y, zz = z*z;
    single l = std::sqrt(xx+yy+zz);
    if (l == 0.0f)
    {
        throw std::invalid_argument("axis vector is zero vector");
    }
    x /= l; y /= l; z /= l;
    single sx = s * x, sy = s * y, sz = s * z,
            tx = t * x, ty = t * y, tz = t * z;
    single txy = tx * y, txz = tx * z, tyz = ty * z;

    return matrix<single, 4, 4>
        (
            tx * x + c, txy - sz,   txz + sy,   0,
            txy + sz,   ty * y + c, tyz - sx,   0,
            txz - sy,   tyz + sx,   tz * z + c, 0,
            0,          0,          0,          1
        );
}

} // namespace idlib
