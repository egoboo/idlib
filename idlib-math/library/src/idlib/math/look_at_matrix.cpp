#include "idlib/math/look_at_matrix.hpp"

#include "idlib/numeric.hpp"
#include "idlib/math/translation_matrix.hpp"

namespace idlib {

matrix<single, 4, 4> look_at_matrix(const vector<single, 3>& eye, const vector<single, 3>& center, const vector<single, 3>& up)
{
    auto f = center - eye;
    auto u = up;

    f = normalize(f, euclidean_norm_functor<vector<single, 3>>()).get_vector();
    u = normalize(u, euclidean_norm_functor<vector<single, 3>>()).get_vector();

    auto s = cross_product(f, u);
    s = normalize(s, euclidean_norm_functor<vector<single, 3>>()).get_vector();

    u = cross_product(s, f);

    return matrix<single, 4, 4>( s[0],  s[1],  s[2], 0.0f,
                                 u[0],  u[1],  u[2], 0.0f,
                                -f[0], -f[1], -f[2], 0.0f,
                                 0.0f,   0.0f,   0.0f,  1.0f)
         * translation_matrix(-eye);
}

} // namespace idlib
