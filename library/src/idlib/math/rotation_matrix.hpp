#pragma once

#pragma push_macro("IDLIB_PRIVATE")

#if !defined(IDLIB_PRIVATE)
#define IDLIB_PRIVATE (1)
#endif

#include "idlib/math/angle-degrees-radians-turns.hpp"
#include "idlib/math/vector.hpp"
#include "idlib/math/matrix.hpp"

#pragma pop_macro("IDLIB_PRIVATE")

namespace idlib {

/**@{*/

/**
 * @brief Get a matrix representing an anticlockwise rotation around the x-axis.
 * @param a the angle of rotation
 * @return the matrix
 * @remark
 *  \f[
 *  \left[\begin{matrix}
 *  1 & 0 &  0 & 0 \\
 *  0 & c & -s & 0 \\
 *  0 & s &  c & 0 \\
 *  0 & 0 &  0 & 1 \\
 *  \end{matrix}\right]
 *  \f]
 *  where \f$c=\cos(a)\f$ and \f$s=\sin(a)\f$.
 */
matrix<single, 4, 4> rotation_matrix_x(const angle<single, degrees>& a);

matrix<single, 4, 4> rotation_matrix_x(const angle<single, turns>& a);

matrix<single, 4, 4> rotation_matrix_x(const angle<single, radians>& a);

/**@}*/

/**@{*/

/**
 * @brief Get a matrix representing a anticlockwise rotation around the y-axis.
 * @param a the angle of rotation
 * @return the matrix
 * @remark
 *  \f[
 *  \left[\begin{matrix}
 *   c & 0 & s & 0 \\
 *   0 & 1 & 0 & 0 \\
 *  -s & 0 & c & 0 \\
 *   0 & 0 & 0 & 1 \\
 *  \end{matrix}\right]
 *  \f]
 *  where \f$c=\cos(a)\f$ and \f$s=\sin(a)\f$.
 */
matrix<single, 4, 4> rotation_matrix_y(const angle<single, degrees>& a);

matrix<single, 4, 4> rotation_matrix_y(const angle<single, turns>& a);

matrix<single, 4, 4> rotation_matrix_y(const angle<single, radians>& a);

/**@}*/

/**@{*/

/**
 * @brief Get a matrix representing an anticlockwise rotation about the z-axis.
 * @param a the angle of rotation
 * @return the matrix
 * @remark
 *  \f[
 *  \left[\begin{matrix}
 *  c & -s & 0 & 0 \\
 *  s &  c & 0 & 0 \\
 *  0 &  0 & 1 & 0 \\
 *  0 &  0 & 0 & 1 \\
 *  \end{matrix}\right]
 *  \f]
 *  where \f$c=\cos(a)\f$ and \f$s=\sin(a)\f$.
 */
matrix<single, 4, 4> rotation_matrix_z(const angle<single, degrees>& a);

matrix<single, 4, 4> rotation_matrix_z(const angle<single, turns>& a);

matrix<single, 4, 4> rotation_matrix_z(const angle<single, radians>& a);

/**@}*/


/**@{*/

/**
 * @brief Get a rotation matrix representing a counter-clockwise rotation around an axis.
 * @param axis the rotation axis
 * @param angle the rotation angle
 * @return the rotation matrix
 * @throw std::invalid_argument the rotation axis is the zero vector
 * @remark
 *  Given an axis of rotation represented by the unit vector \f$\hat{r}=(k_x,k_y,k_z,1)\f$ and an angle
 *  \f$\theta\f$, we shall obtain a \f$4 \times 4\f$ matrix \f$\mathcal{T}\f$ called the Rodrigues rotation
 *  matrix \f$R\f$ for the axis of rotation \f$\hat{k}\f$ and the angle \f$\theta\f$. This matrix has
 *  represents the transformation of rotating counter-clockwise by \f$\theta\f$ about the axis
 *  \f$\hat{k}\f$ i.e. for any point \f$\vec{v}=(v_x,v_y,v_z,1)\f$
 *  \f[
 *  \vec{v}' = \mathbf{L} \vec{v}
 *  \f]
 *  is the counter-clockwise rotation of \f$\vec{v}\f$ by \f$\theta\f$ about the axis \f$\hat{\vec{r}}\f$.
 *  </br>
 *  The derivation of that matrix is provided here for reference, the geometric reasoning is omitted.
 *  </br>
 *  To compute the rotated point \f$\vec{v}'\f$, we begin by splutting \f$\vec{v}\f$ into a part \f$\vec{v}_{\parallel}\f$
 *  parallel to \f$\hat{\vec{r}}\f$ and into a part \f$\vec{v}_{\perp}\f$ perpendicular to \f$\hat{\vec{r}}\f$ which lies
 *  on the plane of rotation. Recall from vector<single, 3>::decompose(const vector<single, 3>&,const vector<single, 3>&,vector<single, 3>&,vector<single, 3>&) that the
 *  parallel part is the projection of \f$\vec{v}\f$ on \f$\hat{\vec{r}}\f$, the perpendicular part is the rejection
 *  \f$\vec{v}_{\perp}\f$ of \f$\vec{v}\f$ from \f$\hat{\vec{r}}\f$:
 *  \f{align*}{
 *  \vec{v}_{\parallel} = \left(\vec{v} \cdot \hat{\vec{r}}\right) \hat{\vec{r}}\\
 *  \vec{v}_{\perp} = \vec{v} - \vec{v}_{\parallel}
 *  \f}
 *  To compute the effect of the rotation, a two-dimensional basis on the plane of rotation is required.
 *  \f$\vec{v}_{\perp}\f$ is used as the first basis vector. As second basis vector perpendicular to
 *  \f$\vec{v}_{\perp}\f$ is required. One can use the vector
 *  \f{align*}{
 *  \vec{w} = \hat{\vec{r}} \times \vec{v}_{\perp} = \hat{\vec{r}} \times \vec{v}
 *  \f}
 *  which is perpendicular to and has the same length as \f$\vec{v}_{\perp}\f$ as
 *  shown in vector<single, 3>::decompose(const vector<single, 3>&,const vector<single, 3>&,vector<single, 3>&,vector<single, 3>&).
 *  </br>
 *  If in \f$\mathbb{R}^2\f$ one rotates the vector \f$\vec{i}=(1,0)\f$ by \f$\theta\f$
 *  in the plane of rotation spanned by the standard basis \f$\vec{i}=(1,0)\f$,
 *  \f$\vec{j}=(0,1)\f$ for \f$\mathbb{R}^2\f$, the result is the vector
 *  \f{align*}{
 *  \vec{i}' = \cos(\theta)\vec{i} + \sin(\theta) \vec{j}
 *  \f}
 *  If \f$\vec{v}_{\perp}\f$ and \f$\vec{w}\f$ are used as the standard basis and
 *  \f$\vec{v}_{\perp}\f$ is rotated in the plane of rotation spanned by the basis
 *  \f$\vec{v}_{\perp}\f$ and \f$\vec{w}\f$, the result of the rotation is given in
 *  a similar manner:
 *  \f{align*}{
 *  \vec{v}'_{\perp} = \cos(\theta)\vec{v}_{\perp} + \sin(\theta)\vec{w}
 *  \f}
 *  </br>
 *  As \f$\vec{v}_{\parallel}\f$ is completely unaffected by the rotation about \f$\hat{\vec{r}}\f$
 *  the final result of the anti-clockwise rotation of \f$\vec{v}\f$ by \f$\theta\f$ degree around
 *  \f$\hat{\vec{r}}\f$ is given by
 *  \f[
 *  \vec{v}' = \vec{v}_{\parallel} + \vec{v}'_{\perp}
 *  \f]
 *  </br>
 *  As
 *  \f{align*}{
 *  \vec{v}_{\parallel} =& \left(\vec{v} \cdot \hat{\vec{r}}\right) \hat{\vec{r}}\\
 *  \vec{v}_{\perp}     =& \vec{v} - \vec{v}_{\parallel} = \vec{v}_{\parallel}\\
 *                    =& \vec{v} - \left(\vec{v} \cdot \hat{\vec{r}}\right) \hat{\vec{r}}\\
 *  \vec{w}             =& \hat{\vec{r}} \times \vec{v}\\
 *  \vec{v}'_{\perp}    =& \cos(\theta)\vec{v}_{\perp} + \sin(\theta)\vec{w}\\
 *                    =& \cos(\theta)\left(\vec{v} - \left(\vec{v} \cdot \hat{\vec{r}}\right) \hat{\vec{r}}\right) + \sin(\theta)\left(\hat{\vec{r}} \times \vec{v}\right)
 *  \f}
 *  the above expression can be rewritten and simplified
 *  \f{align*}{
 *  \vec{v}' =& \left(\vec{v} \cdot \hat{\vec{r}}\right) \hat{\vec{r}} + \cos(\theta)\left(\vec{v} - \left(\vec{v} \cdot \hat{\vec{r}}\right) \hat{\vec{r}}\right) + \sin(\theta)\left(\hat{\vec{r}} \times \vec{v}\right)\\
 *         =& \left(\vec{v} \cdot \hat{\vec{r}}\right) \hat{\vec{r}} + \cos(\theta)\vec{v} - \cos(\theta)\left(\vec{v} \cdot \hat{\vec{r}}\right) \hat{\vec{r}} + \sin(\theta)\left(\hat{\vec{r}} \times \vec{v}\right)\\
 *         =& \cos(\theta)\vec{v} + \left[\left(\vec{v} \cdot \hat{\vec{r}}\right) \hat{\vec{r}} - \cos(\theta)\left(\vec{v} \cdot \hat{\vec{r}}\right) \hat{\vec{r}}\right] + \sin(\theta)\left(\hat{\vec{r}} \times \vec{v}\right)\\
 *         =& \cos(\theta)\vec{v} + (1- \cos(\theta))\left(\vec{v} \cdot \hat{\vec{r}}\right) \hat{\vec{r}} + \sin(\theta)\left(\hat{\vec{r}} \times \vec{v}\right)
 *  \f}
 *  which is known as the Rodrigues rotation formula.
 * @remark
 *  To obtain the Rodrigues rotation formula in a matrix form, the projection \f$\left(\vec{v} \cdot \hat{\vec{r}}
 *  \right)\vec{r}\f$ can be replaced by the tensor product \f$(\hat{\vec{r}} \otimes \hat{\vec{r}})\vec{v}\f$
 *  and the cross product \f$\hat{\vec{r}} \times \vec{v}\f$ can be replaced by a multiplication with a cross product
 *   matrix \f$\mathbf{R} \vec{v}\f$ which gives
 *  \f{align*}{
 *  \vec{v}' =& \cos(\theta)\vec{v} + (1- \cos(\theta))\left(\hat{\vec{r}} \otimes \hat{\vec{r}}\right)\vec{v} + \sin(\theta)\left(\mathbf{R}\vec{v}\right)\\
 *         =& \left[\cos(\theta)\mathbf{I} + (1 - \cos(\theta))\left(\hat{\vec{r}} \otimes \hat{\vec{r}}\right) + \sin(\theta)\mathbf{R}\right]\vec{v}
 *  \f}
 *  with
 *  \f[
 *  \mathbf{R} =
 *  \left[\begin{matrix}
 *   0                  & -\hat{\vec{r}}_3 &  \hat{\vec{r}}_2 \\
 *   \hat{\vec{r}}_3    & 0                & -\hat{\vec{r}}_1 \\
 *  -\hat{\vec{r}}_2    & \hat{\vec{r}}_1  & 0
 *  \end{matrix}\right]
 *  \f]
 *  and
 *  \f[
 *  \hat{\vec{r}} \otimes \hat{\vec{r}}
 *  =
 *  \left[\begin{matrix}
 *   \hat{\vec{r}}_1 \\
 *   \hat{\vec{r}}_2 \\
 *   \hat{\vec{r}}_3
 *  \end{matrix}\right]
 *  \otimes
 *  \left[\begin{matrix}
 *   \hat{\vec{r}}_1 & \hat{\vec{r}}_2 & \hat{\vec{r}}_3
 *  \end{matrix}\right]
 *  =
 *  \left[\begin{matrix}
 *  \hat{\vec{r}}^2_1               & \hat{\vec{r}}_1 \hat{\vec{r}}_2 & \hat{\vec{r}}_1 \hat{\vec{r}}_3 \\
 *  \hat{\vec{r}}_1 \hat{\vec{r}}_2 & \hat{\vec{r}}^2_2               & \hat{\vec{r}}_2 \hat{\vec{r}}_3 \\
 *  \hat{\vec{r}}_1 \hat{\vec{r}}_3 & \hat{\vec{r}}_2 \hat{\vec{r}}_3 & \hat{\vec{r}}^3_3
 *  \end{matrix}\right]
 *  \f]
 *  The matrix
 *  \f[
 *  \mathcal{T} = \cos(\theta)\mathbf{I} + (1 - \cos(\theta))\left(\hat{\vec{r}} \otimes \hat{\vec{r}}\right) + \sin(\theta)\mathbf{R}
 *  \f]
 *  is known as the Rodrigues rotation matrix.
 * @remark
 *  To compute the matrix \f$\mathbf{T}\f$ efficiently, its formula
 *  \f[
 *  \mathcal{T} = \cos(\theta)\mathbf{I} + (1 - \cos(\theta))\left(\hat{\vec{r}} \otimes \hat{\vec{r}}\right) + \sin(\theta)\mathbf{R}
 *  \f]
 *  is expanded. Let \f$s=\sin(\theta)\f$, \f$c = \cos(\theta)\f$ and \f$t = 1 - \cos(\theta)\f$
 *  \f{align*}{
 *  \mathcal{T}
 * =& c \mathbf{I} + t \left(\hat{\vec{r}} \otimes \hat{\vec{r}}\right) + s \mathbf{R}\\
 * =&
 *  c
 *  \left[\begin{matrix}
 *   1 & 0 & 0 \\
 *   0 & 1 & 0 \\
 *   0 & 0 & 1
 *   \end{matrix}\right]
 *   +
 *   t
 *   \left[\begin{matrix}
 *   \hat{\vec{r}}^2_1               & \hat{\vec{r}}_1 \hat{\vec{r}}_2 & \hat{\vec{r}}_1 \hat{\vec{r}}_3 \\
 *   \hat{\vec{r}}_1 \hat{\vec{r}}_2 & \hat{\vec{r}}^2_2               & \hat{\vec{r}}_2 \hat{\vec{r}}_3 \\
 *   \hat{\vec{r}}_1 \hat{\vec{r}}_3 & \hat{\vec{r}}_2 \hat{\vec{r}}_3 & \hat{\vec{r}}^3_3
 *   \end{matrix}\right]
 *   +
 *   s
 *   \left[\begin{matrix}
 *   0                  & -\hat{\vec{r}}_3 &  \hat{\vec{r}}_2 \\
 *   \hat{\vec{r}}_3    & 0                & -\hat{\vec{r}}_1 \\
 *   -\hat{\vec{r}}_2    & \hat{\vec{r}}_1  & 0
 *   \end{matrix}\right]\\
 * =&
 *  \left[\begin{matrix}
 *   c & 0 & 0 \\
 *   0 & c & 0 \\
 *   0 & 0 & c
 *   \end{matrix}\right]
 *   +
 *   \left[\begin{matrix}
 *   t\hat{\vec{r}}^2_1               & t\hat{\vec{r}}_1 \hat{\vec{r}}_2 & t\hat{\vec{r}}_1 \hat{\vec{r}}_3 \\
 *   t\hat{\vec{r}}_1 \hat{\vec{r}}_2 & t\hat{\vec{r}}^2_2               & t\hat{\vec{r}}_2 \hat{\vec{r}}_3 \\
 *   t\hat{\vec{r}}_1 \hat{\vec{r}}_3 & t\hat{\vec{r}}_2 \hat{\vec{r}}_3 & t\hat{\vec{r}}^3_3
 *   \end{matrix}\right]
 *   +
 *   \left[\begin{matrix}
 *   0                 & -s\hat{\vec{r}}_3 &  s\hat{\vec{r}}_2 \\
 *   s\hat{\vec{r}}_3  & 0                 & -s\hat{\vec{r}}_1 \\
 *   -s\hat{\vec{r}}_2 & s\hat{\vec{r}}_1  & 0
 *   \end{matrix}\right]\\
 * =&
 *   \left[\begin{matrix}
 *   t\hat{\vec{r}}^2_1 + c                              & t\hat{\vec{r}}_1 \hat{\vec{r}}_2 - s\hat{\vec{r}}_3 & t\hat{\vec{r}}_1 \hat{\vec{r}}_3 + s\hat{\vec{r}}_2\\
 *   t\hat{\vec{r}}_1 \hat{\vec{r}}_2 + s\hat{\vec{r}}_3 & t\hat{\vec{r}}^2_2 + c                              & t\hat{\vec{r}}_2 \hat{\vec{r}}_3 - s\hat{\vec{r}}_1  \\
 *   t\hat{\vec{r}}_1 \hat{\vec{r}}_3 - s\hat{\vec{r}}_2 & t\hat{\vec{r}}_2 \hat{\vec{r}}_3 + s\hat{\vec{r}}_1 & t\hat{\vec{r}}^3_3 + c
 *   \end{matrix}\right]
 *  \f}
 * @note
 *  In the matrix
 *  \f[
 *  \mathcal{T} =
 *  \left[\begin{matrix}
 *  t\hat{\vec{r}}^2_1 + c                              & t\hat{\vec{r}}_1 \hat{\vec{r}}_2 - s\hat{\vec{r}}_3 & t\hat{\vec{r}}_1 \hat{\vec{r}}_3 + s\hat{\vec{r}}_2\\
 *  t\hat{\vec{r}}_1 \hat{\vec{r}}_2 + s\hat{\vec{r}}_3 & t\hat{\vec{r}}^2_2 + c                              & t\hat{\vec{r}}_2 \hat{\vec{r}}_3 - s\hat{\vec{r}}_1  \\
 *  t\hat{\vec{r}}_1 \hat{\vec{r}}_3 - s\hat{\vec{r}}_2 & t\hat{\vec{r}}_2 \hat{\vec{r}}_3 + s\hat{\vec{r}}_1 & t\hat{\vec{r}}^3_3 + c
 *  \end{matrix}\right]\\
 *  s=\sin(\theta), c = \cos(\theta), t = 1 - \cos(\theta)
 *  \f]
 *  common subexpressions exist which can be eliminated by precomputation:
 *  \f{align*}{
 *  \mathcal{T} =
 *  \left[\begin{matrix}
 *  t_1 \hat{\vec{r}}_1 + c & t_12 - s_3              & t_13 + s_2 \\
 *  t_12 + s_3              & t_2 \hat{\vec{r}}_2 + c & t_23 - s_1 \\
 *  t_13 - s_2              & t_23 + s_1              & t_3 \hat{\vec{r}}_3 + c
 *  \end{matrix}\right]\\
 *  s=\sin(\theta), c = \cos(\theta), t = 1 - \cos(\theta),\\
 *  t_1 = t\hat{\vec{r}}_1, t_2 = t\hat{\vec{r}}_2, t_3 = t\hat{\vec{r}}_3,\\
 *  t_12 = t_1 \hat{\vec{r}}_2, t_13 = t_1 \hat{\vec{r}}_3, t_23 = t_2 \hat{\vec{r}}_3\\
 *  s_1 = s\hat{\vec{r}}_1, s_2 = s\hat{\vec{r}}_2, s_3 = s\hat{\vec{r}}_3
 *  \f}
 *  This implementation performs this form of elimination of common subexpressions.
 */
matrix<single, 4, 4> rotation_matrix(const vector<single, 3>& axis, const angle<single, degrees>& angle);

matrix<single, 4, 4> rotation_matrix(const vector<single, 3>& axis, const angle<single, turns>& angle);

matrix<single, 4, 4> rotation_matrix(const vector<single, 3>& axis, const angle<single, radians>& angle);

/**@}*/

} // namespace idlib
