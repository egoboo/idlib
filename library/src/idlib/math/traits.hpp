/// @details The libraries grounds itself on four concepts: scalars, vectors, points, and geometry.
#pragma once

namespace id {

/// @ingroup math
/// @brief The traits of a scalar type.
/// @details Specialization of this class provide the member type @a scalar_type denoting the type of the scalar.
/// @tparam S the type of the scalar
template <typename S>
struct scalar_traits;

/// @ingroup math
/// @brief The traits of a vector type.
/// @details Specialization of this class provide the member type @a scalar_type denoting the scalar type.
/// Specializations shall provide a static constant expression function @a dimensionality returning a @a size_t value denoting the positive dimensionality of the vectors.
/// @tparam V the type of the vector
template <typename V>
struct vector_traits;

/// @ingroup math
/// @brief The traits of a point type.
/// @details Specialization of this class provide the following member types:
/// - @a scalar_type the type of the scalars
/// - @a vector_type the type of the vectors
/// Specializations shall provide a static constant expression function @a dimensionality returning a @a size_t value denoting the positive dimensionality of the points.
/// @tparam T the type of the point
template <typename P>
struct point_traits;

/// @ingroup math
/// @brief The traits of a geometry type.
/// @details
/// Specialization of this class provide the following member types
/// - @a vector_type the vector type
/// - @a scalar_type the scalar type
/// Specializations of this class provide a static constant expression member function @a dimensionality returning a @a size_t value denoting the dimensionality of the geometries.
/// @tparam T the type of the geometry
template <typename X>
struct geometry_traits;

} // namespace id