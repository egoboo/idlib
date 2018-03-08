#pragma once

#include "gtest/gtest.h"
#include "idlib/math_geometry.hpp"

namespace idlib::tests {

using vector_3s = idlib::vector<single, 3>;
using point_3s = idlib::point<vector_3s>;
using sphere_3s = idlib::sphere<point_3s>;
using axis_aligned_box_3s = idlib::axis_aligned_box<point_3s>;
using axis_aligned_cube_3s = idlib::axis_aligned_cube<point_3s>;

template <typename Scalar, size_t Dimensionality>
idlib::vector<Scalar, Dimensionality> normalize(const idlib::vector<Scalar, Dimensionality>& v) {
    auto l = idlib::euclidean_norm(v);
    if (l < idlib::zero<Scalar>()) {
        throw idlib::runtime_error(__FILE__, __LINE__, "negative length");
    } else {
        return v * (1.0f / l);
    }
}

struct Utilities {
    /// \f$\delta^+(x)\f$ is a value greater than \f$x\f$
    /// such that \f$|x-\delta(x)|\f$ is sufficient that
    /// \f$f(x) \neq f(\delta(x))\f$ if \f$f\f$ is
    /// a function.
    static float pdelta(float x) {
        return x + 0.001f;
    }
    /// \f$\delta^+(x)\f$ is a value smaller than \f$x\f$
    /// such that \f$|x-\delta(x)|\f$ is sufficient that
    /// \f$f(x) \neq f(\delta(x))\f$ if \f$f\f$ is
    /// a function.
    static float ndelta(float x) {
        return x - 0.001f;
    }

    // The unit vector.
    static vector_3s unit() {
        static const auto v = normalize(vector_3s(1.0f, 1.0f, 1.0f));
        return v;
    }

public:
    /**
     * Get a point which does not overlap with the specified point.
     *
     * Let \f$a\f$ be the specified point.
     * The point
     * \f$b = a + \delta^+(1) \vec{1}\f$
     * does not overlap with \f$a\f$.
     */
    static point_3s get_non_overlapping_point_3s(const point_3s& a)
    { return a + unit() * pdelta(1.0f); }
    
    /**
     * Get a point which overlaps with the specified point.
     *
     * Let \f$a\f$ be the specified point.
     * The point
     * \f$b = a\f$
     * overlaps with \f$a\f$.
     */
    static point_3s get_overlapping_point_3s(const point_3s& a)
    { return a; }
    
    /**
     * Get a point which is not contained in the specified point.
     *
     * Let \f$a\f$ be the specified point.
     * The point
     * \f$b = a + \epsilon\vec{1}\f$
     * is not contained in \$a\f$.
     */
    static point_3s get_non_contained_point_3s(const point_3s& a)
    { return a + unit() * pdelta(0.0f); }
    
    // Get a point which is contained in the specified point.
    //
    // Let \f$a\f$ be the specified point.
    // The point
    // \f$b = a\f$
    // is contained in \f$a\f$.
    static point_3s get_contained_point_3s(const point_3s& a)
    { return a; }

public:
    // Get a sphere which does not intersect with the specified sphere.
    //
    // Let \f$a\f$ be the specified sphere with center \f$c\f$ and radius \f$r\f$.
    // The sphere \f$b\f$ with
    // center \f$\mathbf{c}' = \mathbf{c} + \delta^+(2r)\vec{1}\f$ and radius \f$r'=r\f$
    // does not intersect with \f$a\f$.
    static sphere_3s get_non_overlapping_sphere_3s(const sphere_3s& a) {
        auto c = a.get_center() + unit() * pdelta(2.0f * a.get_radius());
        auto r = a.get_radius();
        return sphere_3s(c, r);
    }

    // Get a point which does not intersect with the specified sphere.
    //
    // Let \f$a\f$ be the specified sphere with center \f$c\f$ and radius \f$r\f$.
    // The point
    // \f$b = c + \delta^+(r) \vec{1}\f$
    // does not intersect \f$a\f$.
    static point_3s get_non_overlapping_point_3s(const sphere_3s& a) {
        return a.get_center() + unit() * pdelta(a.get_radius());
    }

    // Get a sphere which intersects with the specified sphere.
    //
    // Let \f$a\f$ be the specified sphere with center \f$c\f$ and radius \f$r\f$.
    // The sphere \f$b\f$ with center
    // center \f$c' = c + r \vec{1}\f$ and radius \f$r\f$
    // intersects with \f$a\f$.
    static sphere_3s get_overlapping_sphere_3s(const sphere_3s& a) {
        return sphere_3s(a.get_center() + unit() * a.get_radius(), a.get_radius());
    }
    // Get a point which intersects with the specified sphere.
    //
    // Let \f$a\f$ be the specified sphere with center \f$c\f$ and radius \f$r\f$.
    // The point
    // \f$b = c + ndelta(r) \vec{1}\f$
    // intersects with \f$a\f$.
    static point_3s get_overlapping_point_3s(const sphere_3s& a) {
        return a.get_center() + unit() * ndelta(a.get_radius());
    }

    // Get a point which is not contained in the specified sphere.
    //
    // Let \f$a\f$ be the specified sphere with center \f$c\f$ and radius \f$r\f$.
    // The point
    // \f$b = c + \delta^+(r) \vec{1}\f$
    // does not intersect with \f$a\f$.
    static point_3s get_non_contained_point_3s(const sphere_3s& a) {
        return a.get_center() + unit() * pdelta(a.get_radius());
    }
    // Get a sphere which is not contained in the specified sphere.
    //
    // Let \f$a\f$ be the specified sphere with center \f$c\f$ and radius \f$r\f$.
    // The sphere \f$b\f$ with
    // center \f$c' = c + \delta^+(r) \vec{1}\f$ and radius \f$r' = r\f$
    // is not contained in \f$a\f$.
    static sphere_3s get_non_contained_sphere_3s(const sphere_3s& a) {
        return sphere_3s(a.get_center() + unit() * pdelta(a.get_radius()), a.get_radius());
    }

    // Get a point which is contained in the specified sphere.
    //
    // Let \f$a\f$ be the specified sphere with center \f$c\f$ and radius \f$r\f$.
    // The point
    // \f$b = c + \delta^-(r) \vec{1}\f$
    // intersects with \f$a\f$.
    static point_3s get_contained_point_3s(const sphere_3s& a) {
        return a.get_center() + unit() * ndelta(a.get_radius());
    }
    // Get a sphere which is contained in the specified sphere.
    //
    // Let \f$a\f$ be the specified sphere with center \f$c\f$ and radius \f$r\f$.
    // The sphere \f$b\f$ with
    // center \f$c' = c + \frac{1}{2}r\vec{1}\f$ and radius \f$r' = \frac{1}{2}r\f$
    // is contained in \f$a\f$.
    static sphere_3s get_contained_sphere_3s(const sphere_3s& a) {
        return sphere_3s(a.get_center() + unit() * (0.5 * a.get_radius()), 0.5 * a.get_radius());
    }

public:
    // Get an AABB which does not overlap with the specified AABB.
    //
    // Let \f$a\f$ be the specified axis-aligned bounding box with
    // minimum point \f$\mathbf{m}\f$ and edge lengths \f$\vec{l}\f$.
    // The axis-aligned bounding box \f$b\f$ with minimum point
    // \f$\mathbf{m}' = \mathbf{m} + \delta^+(0)\vec{1} + \vec{l}\f$
    // and edge lengths \f$\vec{l}' = \vec{l}\f$ does not overlap with \f$a\f$.
    static axis_aligned_box_3s get_non_overlapping_axis_aligned_box_3s(const axis_aligned_box_3s& x) {
        auto t = pdelta(0.0f);
        auto d = unit() * t + x.get_size();
        return axis_aligned_box_3s(x.get_min() + d, x.get_max() + d);
    }

    // Get an axis-aligned bounding box which intersects with the specified axis-aligned bounding box.
    //
    // Let \f$a\f$ be the specified axis-aligned bounding box with minimum point \f$m\f$
    // and edge lengths \f$\vec{l}\f$. The axis-aligned bounding box \f$b\f$ with
    // minimum point \f$m' = m + \frac{1}{4}\vec{l}\f$ and edge lengths \f$\vec{l}\f$ intersects with \f$a\f$.
    static axis_aligned_box_3s get_overlapping_axis_aligned_box_3s(const axis_aligned_box_3s& a) {
        auto d = a.get_size() * 0.25f;
        return axis_aligned_box_3s(a.get_min() + d, a.get_max() + d);
    }

    // Get a point which overlaps with the specified AABB.
    static point_3s get_overlapping_point_3s(const axis_aligned_box_3s& x) {
        return x.get_center();
    }

    // Get a point which does not overlap with the specified axis-aligned bounding box.
    //
    // Let \f$a\f$ be the specified axis-aligned bounding box with minimum point \f$m\f$
    // and edge lengths \f$\vec{l}\f$. The point \f$b = min + l + \delta^+(0) \vec{1}\f$
    // does not intersect \f$a\f$.
    static point_3s get_non_overlapping_point_3s(const axis_aligned_box_3s& a) {
        return a.get_min() + a.get_size() + unit() * pdelta(0.0f);
    }

    // Get an axis-aligned bounding box which is not contained in the specified axis-aligned bounding box.
    //
    // Let \f$a\f$ be the specified axis-aligned bounding box with minimum point \f$m\f$
    // and edge lengths \f$\vec{l}\f$. The axis-aligned bounding box \f$b\f$ with
    // minimum point \f$m' = m + \frac{1}{4}\vec{l}\f$ and edge lengths \f$\vec{l}\f$ is not contained in \f$a\f$.
    static axis_aligned_box_3s get_non_contained_axis_aligned_box_3s(const axis_aligned_box_3s& a) {
        auto d = a.get_size() * 0.25f;
        return axis_aligned_box_3s(a.get_min() + d, a.get_max() + d);
    }

    // Get a point which is not contained in the specified axis-aligned bounding box.
    //
    // Let \f$a\f$ be the specified axis-aligned bounding box.
    // The point
    // \f$b = a_{max} + \delta^+(0)\vec{1}\f$
    // is not contained in \f$a\f$.
    static point_3s get_non_contained_point_3s(const axis_aligned_box_3s& a) {
        return a.get_max() + unit() * pdelta(0.0f);
    }

    // Get an AABB which is contained in the specified AABB.
    // Let \f$a\f$ be the specified axis-aligned bounding box
    // with minimum \f$min\f$ and maximum \f$max\f$.
    // The axis-aligned bounding box \f$b\f$ with
    // minimum \f$min' = (min - c) \delta^-(1) + c\f$
    // and
    // maximum \f$max' = (max - c) \delta^-(1) + c\f$
    // is contained in \f$a\f$.
    static axis_aligned_box_3s get_contained_axis_aligned_box_3s(const axis_aligned_box_3s& a) {
        auto s = ndelta(1.0f);
        auto min = a.get_center() + (a.get_min() - a.get_center())*s;
        auto max = a.get_center() + (a.get_max() - a.get_center())*s;
        return axis_aligned_box_3s(min, max);
    }

    // Get a point which is contained in the specified axis-aligned bounding box.
    // Let \f$a\f$ be the specified axis-aligned bounding box with center \f$c\f$.
    // The point \f$b = c\f$ is contained in \f$a\f$.
    static point_3s get_contained_point_3s(const axis_aligned_box_3s& a) {
        return a.get_center();
    }

public:
    // Get a cube which does not overlap with the specified cube.
    // 
    // Let \f$a\f$ be the specified cube with
    // minimum point \f$\mathbf{m}\f$ and edge length \f$l\f$.
    // The cube \f$b\f$ with minimum point
    // \f$\mathbf{m}' = \mathbf{m} + \delta^+(l)\vec{1}\f$
    // and edge length \f$l' = l\f$ does not overlap with \f$a\f$.
    static axis_aligned_cube_3s get_non_overlapping_axis_aligned_cube_3s(const axis_aligned_cube_3s& a) {
        auto d = vector_3s(1.0f, 1.0f, 1.0f) * pdelta(a.get_size());
        return axis_aligned_cube_3s(a.get_center() + d, a.get_size());
    }

    // Get an axis-aligned cube which intersects with the specified axis-aligned cube.
    //
    // Let \f$a\f$ be the specified axis-aligned cube with minimum point \f$m\f$
    // and edge length \f$l\f$. The axis-aligned bounding cube \f$b\f$ with
    // minimum point \f$m' = m + \frac{1}{4}l\vec{1}\f$ and edge length \f$l' = l\f$
    // intersects with \f$a\f$.
    static axis_aligned_cube_3s get_overlapping_axis_aligned_cube_3s(const axis_aligned_cube_3s& a) {
        auto d = unit() * (a.get_size() * 0.25f);
        return axis_aligned_cube_3s(a.get_min() + d, a.get_size());
    }

    // Get a point which overlaps with the specified axis-aligned cube.
    static point_3s get_overlapping_point_3s(const axis_aligned_cube_3s& a) {
        return a.get_center();
    }

    // Get a point which does not overlap with the specified axis-aligned cube.
    //
    // Let \f$a\f$ be the specified axis-aligned cube with minimum point \f$m\f$
    // and edge length \f$l\f$. The point \f$b = min + \delta^+(l) \vec{1}\f$
    // does not intersect \f$a\f$.
    static point_3s get_non_overlapping_point_3s(const axis_aligned_cube_3s& a) {
        return a.get_min() + unit() * a.get_size() + unit() * pdelta(a.get_size());
    }

    // Get a point which is not contained in the specified axis-aligned cube.
    //
    // Let \f$a\f$ be the specified axis-aligned cube.
    // The point
    // \f$b = a_{max} + \delta^+(0.0f)\vec{1}\f$
    // is not contained in \f$a\f$.
    static point_3s get_non_contained_point_3s(const axis_aligned_cube_3s& a) {
        return a.get_max() + unit() * pdelta(0.0f);
    }

	// Add basis vectors (1,0,0), (0,1,0), (0,0,1).
	static std::vector<vector_3s> basis(std::vector<vector_3s> l) {
		std::vector<vector_3s> l1{ l };
		l1.emplace_back(1.0f, 0.0f, 0.0f);
		l1.emplace_back(0.0f, 1.0f, 0.0f);
		l1.emplace_back(0.0f, 0.0f, 1.0f);
		return l1;
	}

	// Add the zero vector to a list.
	static std::vector<vector_3s> zero(std::vector<vector_3s> l) {
		std::vector<vector_3s> l1{ l };
		l1.emplace_back(0.0f, 0.0f, 0.0f);
		return l1;
	}

	// Add negation of all list elements to a list.
	template <typename T>
	static std::vector<T> negation(std::vector<T> l) {
		std::vector<T> l1{ l };
		for (auto e : l) {
			auto e1 = -e;
			l1.emplace_back(-e1);
		}
		return l1;
	}

	// Cartesian product list of two list.
	template <typename T>
	static std::vector<std::pair<T, T>> cartesian(const std::vector<T>& a, const std::vector<T>& b) {
		std::vector<std::pair<T, T>> c;
		for (auto x : a) {
			for (auto y : b) {
				c.emplace_back(x, y);
			}
		}
		return c;
	}

};

} // namespace idlib::tests
