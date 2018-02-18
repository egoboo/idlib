///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Idlib: A C++ utility library
// Copyright (C) 2017-2018 Michael Heilmann
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

/// @file idlib/math/matrix.hpp
/// @brief \f$n \times m\f$-dimensional matrices
/// @author Michael Heilmann

#pragma once

#include "idlib/crtp.hpp"
#include "idlib/debug.hpp"
#include "idlib/math/arithmetic_array_2d.hpp"
#include "idlib/math/one_zero.hpp"
#include "idlib/math/trace.hpp"
#include "idlib/math/transpose.hpp"
#include "idlib/math/identity.hpp"

namespace idlib {

/// @brief A row-major matrix.
/// @tparam Element the element type
/// @tparam Number_Of_Rows the number of rows. Can be @a 0.
/// @tparam Number_Of_Columns the number of columns. Can be @a 0.
/// @tparam Enabled for SFINAE
template <typename Element,
          size_t Number_Of_Rows,
          size_t Number_Of_Columns,
          typename Enabled = void>
struct matrix;

template <typename Element,
          size_t Number_Of_Rows,
          size_t Number_Of_Columns>
struct matrix<Element,
              Number_Of_Rows,
              Number_Of_Columns,
              std::enable_if_t<(Number_Of_Rows > 0) && (Number_Of_Columns > 0)>>
: public equal_to_expr<matrix<Element, Number_Of_Rows, Number_Of_Columns>>
{
    /// @brief Get if this matrix type is square matrix type.
    /// @return @a true if this matrix type is a square matrix type,  @a false otherwise
    constexpr static bool is_square()
    { return number_of_rows() == number_of_columns(); }

    /// @brief Get the the number of rows of this matrix type.
    /// @return the number of rows of this matrix type
    constexpr static size_t number_of_rows()
    { return Number_Of_Rows; }

    /// @brief Get the number of columns of this matrix type.
    /// @return the number of columns of this matrix type
    constexpr static size_t number_of_columns()
    { return Number_Of_Columns; }

    /// @brief Get the number of elements of this matrix type.
    /// @return the number of elements of this matrix type
    /// @remark The number of elements of a matrix is the product of its number of rows and its number of columns.
    constexpr static size_t number_of_elements()
    { return number_of_rows() * number_of_columns(); }
    
    /// @brief Get the order of this matrix type.
    /// @return the order of this matrix type
    constexpr static std::enable_if_t<matrix::is_square(), size_t> order()
    { return number_of_rows(); }

    /// @brief The element type of this matrix type.
    using element_type = Element;

    /// @brief @a MyType is the type of this template/template specialization.
    using MyType = matrix<element_type, Number_Of_Rows, Number_Of_Columns>;

    using implementation = arithmetic_array_2d<Element,
                                               Number_Of_Rows,
                                               Number_Of_Columns,
                                               zero_functor<Element>>;

    union {
        /**@{*/
        element_type _v[number_of_elements()];
        /**
         * @brief
         *  The union of a two-dimensional array and a one-dimensional array.
         * @remark
         *  C++ has a native row-major order:
         *  A two dimensional array \f$a_{n,m}\f$ is layed out in memory
         *  \f{align*}{
         *  a_{0,0}   a_{0,1}   a_{0,2}   a_{0,3}   \ldots a_{0,m-2}   a_{0,m-1}
         *  a_{1,0}   a_{1,1}   a_{1,2}   a_{1,3}   \ldots a_{1,m-2}   a_{1,m-1}  \
         *  \vdots
         *  a_{n-2,0} a_{n-2,1} a_{n-2,2} a_{n-2,3} \ldots a_{n-2,m-2} a_{n-2,m-1}
         *  a_{n-1,0} a_{n-1,1} a_{n-1,2} a_{n-1,3} \ldots a_{n-1,m-2} a_{n-1,m-1}
         *  \}
         *  and an one dimensional array \f$a_{n \cdot m}\f$ is layed out in memory as
         *  \f{align*}{
         *  a_{0} a_{1} a_{2} a_{3} \ldots a_{n \cdot m - 2} a_{n \cdot m - 1}
         *  \f}
         *  The element \f$a_{i,j}\f$ of the two dimensional array maps
         *  to the element \f$a_{i * m + j}\f$ of the one-dimensional array.
         *
         *  The two dimensional array index \f$(i,j)\f$ maps to the one dimensional array index \f$(i \cdot m + j)\f$.
         *  The one dimensional array index \f$(k)\f$ maps to the two dimensional array index \f$(\lfloor k / m \rfloor, k \mod m)\f$.
         */
        element_type _v2[number_of_rows()][number_of_columns()];
        /**@}*/
    };

    template<typename ... Args,
             typename = std::enable_if_t<(sizeof...(Args) == MyType::number_of_elements()) 
                                         &&
                                         (idlib::all_true<std::is_convertible<Args, element_type>::value ...>::value)>>
    matrix(Args&& ... args)
        : _v { static_cast<element_type>(args) ... }
    {
        static_assert(number_of_elements() == sizeof ... (args), "wrong number of arguments");
    }

    /**
     * @brief
     *  Construct this matrix with default element values.
     */
    matrix() {
        for (size_t i = 0; i < number_of_elements(); ++i) {
            _v[i] = idlib::zero<element_type>();
        }
    }

    /**
     * @brief
     *  Construct this matrix with the element values of another matrix.
     * @param other
     *  the other matrix
     */
    matrix(const matrix& other) {
        for (size_t i = 0; i < number_of_elements(); ++i) {
            _v[i] = other._v[i];
        }
    }


protected:

    /**
     * @brief
     *  Assign this matrix with the values of another matrix.
     * @param other
     *  the other matrix
     * @post
     *  This matrix was assigned the values of another matrix.
     */
    void assign(const matrix& other) {
        for (size_t i = 0; i < number_of_elements(); ++i) {
            _v[i] = other._v[i];
        }
    }

    /**
     * @brief
     *  Get the matrix element at the specified index.
     * @param i
     *  the index
     * @return
     *  the matrix element
     */
    element_type& at(const size_t i) {
        IDLIB_DEBUG_ASSERT(i < number_of_elements());
        return _v[i];
    }

    /**
     * @brief
     *  Get the matrix element at the specified index.
     * @param i
     *  the index
     * @return
     *  the matrix element
     */
    const element_type& at(const size_t i) const {
        IDLIB_DEBUG_ASSERT(i < number_of_elements());
        return _v[i];
    }

    /**
     * @brief
     *  Get the matrix element at the specified index.
     * @param i
     *  the row index
     * @param j
     *  the column index
     * @return
     *  the matrix element
     */
    element_type& at(const size_t i, const size_t j) {
        IDLIB_DEBUG_ASSERT(i < number_of_rows());
        IDLIB_DEBUG_ASSERT(j < number_of_columns());
        return _v2[i][j];
    }

    /**
     * @brief
     *  Get the matrix element at the specified index.
     * @param i
     *  the row index
     * @param j
     *  the column index
     * @return
     *  the matrix element
     */
    const element_type& at(const size_t i, const size_t j) const {
        IDLIB_DEBUG_ASSERT(i < number_of_rows());
        IDLIB_DEBUG_ASSERT(j < number_of_columns());
        return _v2[i][j];
    }

public:
    // CRTP
    bool equal_to(const matrix& other) const {
        for (size_t i = 0; i < number_of_elements(); ++i) {
            if (at(i) != other.at(i)) {
                return false;
            }
        }
        return true;
    }

public:

    const element_type& operator()(const size_t i) const
    { return at(i); }

    element_type& operator()(const size_t i)
    { return at(i); }

    const element_type& operator()(const size_t i, const size_t j) const
    { return at(i, j); }

    element_type& operator()(const size_t i, const size_t j)
    { return at(i, j); }

public:

    /**
     * @brief
     *  Assign this matrix the values of another matrix.
     * @param other
     *  the other matrix
     * @return
     *  this matrix
     * @post
     *  This matrix was assigned the values of another matrix.
     */
    matrix& operator=(const matrix& other) {
        assign(other);
        return *this;
    }

public:
    matrix& operator+=(const matrix& other)
    {
        *this = *this + other;
        return *this;
    }

    matrix& operator-=(const matrix& other)
    {
        *this = *this - other;
        return *this;
    }

    matrix& operator*=(const element_type& other)
    {
        *this = *this * other;
        return *this;
    }

    matrix& operator/=(const element_type& other)
    {
        *this = *this / other;
        return *this;
    }

    /**
     * Overloaded assignment multiplication operator.
     */
    /// @todo Does not work for non-square matrices.
    matrix& operator*=(const matrix& other) {
        *this = *this * other;
        return *this;
    }
    
    template <size_t N = Number_Of_Rows, size_t M = Number_Of_Columns>
    std::enable_if_t<(N == 1 && M == 1), element_type>
    det() const
    {
        static_assert(matrix::is_square(), "determinant on non-square matrix");
        return _v2[0][0];
    }

    template <size_t N = Number_Of_Rows, size_t M = Number_Of_Columns>
    std::enable_if_t<N == 2 && M == 2, element_type>
    det() const
    {
        static_assert(matrix::is_square(), "determinant on non-square matrix");
        return _v2[0][0] * _v2[1][1] - _v2[0][1] * _v2[1][0];
    }

    template <size_t N = Number_Of_Rows, size_t M = Number_Of_Columns>
    std::enable_if_t<N == 3 && M == 3, element_type>
    det() const
    {
        static_assert(matrix::is_square(), "determinant on non-square matrix");
        return _v2[0][0] * (_v2[1][1] * _v2[2][2] - _v2[2][1] * _v2[1][2]) -
               _v2[0][1] * (_v2[1][0] * _v2[2][2] - _v2[1][2] * _v2[2][0]) +
               _v2[0][2] * (_v2[1][0] * _v2[2][1] - _v2[1][1] * _v2[2][0]);
    }

    template <size_t N = Number_Of_Rows, size_t M = Number_Of_Columns>
    std::enable_if_t<N == 4 && M == 4, element_type>
    det() const
    {
        static_assert(matrix::is_square(), "determinant on non-square matrix");
        return
            _v2[0][3] * _v2[1][2] * _v2[2][1] * _v2[3][0] - _v2[0][2] * _v2[1][3] * _v2[2][1] * _v2[3][0] -
            _v2[0][3] * _v2[1][1] * _v2[2][2] * _v2[3][0] + _v2[0][1] * _v2[1][3] * _v2[2][2] * _v2[3][0] +
            _v2[0][2] * _v2[1][1] * _v2[2][3] * _v2[3][0] - _v2[0][1] * _v2[1][2] * _v2[2][3] * _v2[3][0] -
            _v2[0][3] * _v2[1][2] * _v2[2][0] * _v2[3][1] + _v2[0][2] * _v2[1][3] * _v2[2][0] * _v2[3][1] +
            _v2[0][3] * _v2[1][0] * _v2[2][2] * _v2[3][1] - _v2[0][0] * _v2[1][3] * _v2[2][2] * _v2[3][1] -
            _v2[0][2] * _v2[1][0] * _v2[2][3] * _v2[3][1] + _v2[0][0] * _v2[1][2] * _v2[2][3] * _v2[3][1] +
            _v2[0][3] * _v2[1][1] * _v2[2][0] * _v2[3][2] - _v2[0][1] * _v2[1][3] * _v2[2][0] * _v2[3][2] -
            _v2[0][3] * _v2[1][0] * _v2[2][1] * _v2[3][2] + _v2[0][0] * _v2[1][3] * _v2[2][1] * _v2[3][2] +
            _v2[0][1] * _v2[1][0] * _v2[2][3] * _v2[3][2] - _v2[0][0] * _v2[1][1] * _v2[2][3] * _v2[3][2] -
            _v2[0][2] * _v2[1][1] * _v2[2][0] * _v2[3][3] + _v2[0][1] * _v2[1][2] * _v2[2][0] * _v2[3][3] +
            _v2[0][2] * _v2[1][0] * _v2[2][1] * _v2[3][3] - _v2[0][0] * _v2[1][2] * _v2[2][1] * _v2[3][3] -
            _v2[0][1] * _v2[1][0] * _v2[2][2] * _v2[3][3] + _v2[0][0] * _v2[1][1] * _v2[2][2] * _v2[3][3];
    }

    template <size_t N = Number_Of_Rows, size_t M = Number_Of_Columns>
    std::enable_if_t<N == M && N == 2, matrix<element_type, N, M>> inverse() const
    {
        const element_type determinant = det();
        matrix result;
        result._v2[0][0] =  _v2[1][1] / determinant;
        result._v2[0][1] = -_v2[0][1] / determinant;
        result._v2[1][0] = -_v2[1][0] / determinant;
        result._v2[1][1] =  _v2[0][0] / determinant;
        return result;
    }

    template <size_t N = Number_Of_Rows, size_t M = Number_Of_Columns>
    std::enable_if_t<N == M && N == 3, matrix> inverse() const
    {
        const element_type determinant = det();
        matrix result;
        result._v2[0][0] = (_v2[1][1] * _v2[2][2] - _v2[2][1] * _v2[1][2]) / determinant;
        result._v2[0][1] = (_v2[0][2] * _v2[2][1] - _v2[0][1] * _v2[2][2]) / determinant;
        result._v2[0][2] = (_v2[0][1] * _v2[1][2] - _v2[0][2] * _v2[1][1]) / determinant;
        result._v2[1][0] = (_v2[1][2] * _v2[2][0] - _v2[1][0] * _v2[2][2]) / determinant;
        result._v2[1][1] = (_v2[0][0] * _v2[2][2] - _v2[0][2] * _v2[2][0]) / determinant;
        result._v2[1][2] = (_v2[1][0] * _v2[0][2] - _v2[0][0] * _v2[1][2]) / determinant;
        result._v2[2][0] = (_v2[1][0] * _v2[2][1] - _v2[2][0] * _v2[1][1]) / determinant;
        result._v2[2][1] = (_v2[2][0] * _v2[0][1] - _v2[0][0] * _v2[2][1]) / determinant;
        result._v2[2][2] = (_v2[0][0] * _v2[1][1] - _v2[1][0] * _v2[0][1]) / determinant;
        return result;
    }

    template <size_t N = Number_Of_Rows, size_t M = Number_Of_Columns>
    std::enable_if_t<N == M && N == 4, matrix> inverse() const
    {
        matrix result;

        result._v[0] = _v[5]  * _v[10] * _v[15] -
                       _v[5]  * _v[11] * _v[14] -
                       _v[9]  * _v[6]  * _v[15] +
                       _v[9]  * _v[7]  * _v[14] +
                       _v[13] * _v[6]  * _v[11] -
                       _v[13] * _v[7]  * _v[10];

        result._v[4] = -_v[4]  * _v[10] * _v[15] +
                        _v[4]  * _v[11] * _v[14] +
                        _v[8]  * _v[6]  * _v[15] -
                        _v[8]  * _v[7]  * _v[14] -
                        _v[12] * _v[6]  * _v[11] +
                        _v[12] * _v[7]  * _v[10];

        result._v[8] = _v[4]  * _v[9]  * _v[15] -
                       _v[4]  * _v[11] * _v[13] -
                       _v[8]  * _v[5]  * _v[15] +
                       _v[8]  * _v[7]  * _v[13] +
                       _v[12] * _v[5]  * _v[11] -
                       _v[12] * _v[7]  * _v[9];

        result._v[12] = -_v[4]  * _v[9]  * _v[14] +
                         _v[4]  * _v[10] * _v[13] +
                         _v[8]  * _v[5]  * _v[14] -
                         _v[8]  * _v[6]  * _v[13] -
                         _v[12] * _v[5]  * _v[10] +
                         _v[12] * _v[6]  * _v[9];

        result._v[1] = -_v[1]  * _v[10] * _v[15] +
                        _v[1]  * _v[11] * _v[14] +
                        _v[9]  * _v[2]  * _v[15] -
                        _v[9]  * _v[3]  * _v[14] -
                        _v[13] * _v[2]  * _v[11] +
                        _v[13] * _v[3]  * _v[10];

        result._v[5] = _v[0]  * _v[10] * _v[15] -
                       _v[0]  * _v[11] * _v[14] -
                       _v[8]  * _v[2]  * _v[15] +
                       _v[8]  * _v[3]  * _v[14] +
                       _v[12] * _v[2]  * _v[11] -
                       _v[12] * _v[3]  * _v[10];

        result._v[9] = -_v[0]  * _v[9]  * _v[15] +
                        _v[0]  * _v[11] * _v[13] +
                        _v[8]  * _v[1]  * _v[15] -
                        _v[8]  * _v[3]  * _v[13] -
                        _v[12] * _v[1]  * _v[11] +
                        _v[12] * _v[3]  * _v[9];

        result._v[13] = _v[0]  * _v[9]  * _v[14] -
                        _v[0]  * _v[10] * _v[13] -
                        _v[8]  * _v[1]  * _v[14] +
                        _v[8]  * _v[2]  * _v[13] +
                        _v[12] * _v[1]  * _v[10] -
                        _v[12] * _v[2]  * _v[9];

        result._v[2] = _v[1]  * _v[6] * _v[15] -
                       _v[1]  * _v[7] * _v[14] -
                       _v[5]  * _v[2] * _v[15] +
                       _v[5]  * _v[3] * _v[14] +
                       _v[13] * _v[2] * _v[7]  -
                       _v[13] * _v[3] * _v[6];

        result._v[6] = -_v[0]  * _v[6] * _v[15] +
                        _v[0]  * _v[7] * _v[14] +
                        _v[4]  * _v[2] * _v[15] -
                        _v[4]  * _v[3] * _v[14] -
                        _v[12] * _v[2] * _v[7]  +
                        _v[12] * _v[3] * _v[6];

        result._v[10] = _v[0]  * _v[5] * _v[15] -
                        _v[0]  * _v[7] * _v[13] -
                        _v[4]  * _v[1] * _v[15] +
                        _v[4]  * _v[3] * _v[13] +
                        _v[12] * _v[1] * _v[7]  -
                        _v[12] * _v[3] * _v[5];

        result._v[14] = -_v[0]  * _v[5] * _v[14] +
                         _v[0]  * _v[6] * _v[13] +
                         _v[4]  * _v[1] * _v[14] -
                         _v[4]  * _v[2] * _v[13] -
                         _v[12] * _v[1] * _v[6]  +
                         _v[12] * _v[2] * _v[5];

        result._v[3] = -_v[1] * _v[6] * _v[11] +
                        _v[1] * _v[7] * _v[10] +
                        _v[5] * _v[2] * _v[11] -
                        _v[5] * _v[3] * _v[10] -
                        _v[9] * _v[2] * _v[7]  +
                        _v[9] * _v[3] * _v[6];

        result._v[7] = _v[0] * _v[6] * _v[11] -
                       _v[0] * _v[7] * _v[10] -
                       _v[4] * _v[2] * _v[11] +
                       _v[4] * _v[3] * _v[10] +
                       _v[8] * _v[2] * _v[7]  -
                       _v[8] * _v[3] * _v[6];

        result._v[11] = -_v[0] * _v[5] * _v[11] +
                         _v[0] * _v[7] * _v[9]  +
                         _v[4] * _v[1] * _v[11] -
                         _v[4] * _v[3] * _v[9]  -
                         _v[8] * _v[1] * _v[7]  +
                         _v[8] * _v[3] * _v[5];

        result._v[15] = _v[0] * _v[5] * _v[10] -
                        _v[0] * _v[6] * _v[9]  -
                        _v[4] * _v[1] * _v[10] +
                        _v[4] * _v[2] * _v[9]  +
                        _v[8] * _v[1] * _v[6]  -
                        _v[8] * _v[2] * _v[5];

        // Efficient determinant calculation
        element_type det = _v[0] * result._v[0] + _v[1] * result._v[4] + _v[2] * result._v[8] + _v[3] * result._v[12];
        if (det == zero<element_type>())
        {
            throw std::domain_error("Cannot inverse matrix with 0 determinant");
        }

        // Finally multiply by the inverse determinant
        det = one<element_type>() / det;
        for (size_t i = 0; i < 16; i++)
        {
            result(i) = result._v[i] * det;
        }

        return result;
    }
};

template <typename E, size_t N, size_t M>
struct arithmetic_binary_plus_functor<matrix<E, N, M>,
                                      matrix<E, N, M>>
{
    using T = matrix<E, N, M>;
    T operator()(const T& a, const T& b) const
    { return impl(a, b, std::make_index_sequence<N * M>{}); }

private:
    template <size_t ... Is>
    T impl(const T& a, const T& b, std::index_sequence<Is ...>) const
    { return T((a(Is) + b(Is)) ...); }
};

template <typename E, size_t N, size_t M>
struct arithmetic_binary_minus_functor<matrix<E, N, M>,
                                       matrix<E, N, M>>
{
    using T = matrix<E, N, M>;
    T operator()(const T& a, const T& b) const
    { return impl(a, b, std::make_index_sequence<N * M>{}); }

private:
    template <size_t ... Is>
    T impl(const T& a, const T& b, std::index_sequence<Is ...>) const
    { return T((a(Is) - b(Is)) ...); }
};

template <typename E, size_t N, size_t M>
struct arithmetic_unary_plus_functor<matrix<E, N, M>>
{
    using T = matrix<E, N, M>;

    auto operator()(const T& a) const
    { return impl(a, std::make_index_sequence<N * M>{}); }

private:
    template <size_t ... Is>
    auto impl(const T& a, std::index_sequence<Is...>) const
    { return T((+(a(Is)))...); }
};

template <typename E, size_t N, size_t M>
struct arithmetic_unary_minus_functor<matrix<E, N, M>>
{
    using T = matrix<E, N, M>;

    auto operator()(const T& a) const
    { return impl(a, std::make_index_sequence<N * M>{}); }

private:
    template <size_t ... Is>
    auto impl(const T& a, std::index_sequence<Is...>) const
    { return T((-(a(Is)))...); }
};

template <typename E, size_t N, size_t M>
struct arithmetic_binary_star_functor<matrix<E, N, M>,
                                      E>
{
    using B = E;
    using A = matrix<E, N, M>;
    A operator()(const A& a, const B& b) const
    { return impl(a, b, std::make_index_sequence<N * M>{}); }

private:
    template <size_t ... Is>
    A impl(const A& a, const B& b, std::index_sequence<Is ...>) const
    { return A((a(Is) * b) ...); }
};

template <typename E, size_t N, size_t M>
struct arithmetic_binary_slash_functor<matrix<E, N, M>,
                                       E>
{
    using B = E;
    using A = matrix<E, N, M>;
    A operator()(const A& a, const B& b) const
    { return impl(a, b, std::make_index_sequence<N * M>{}); }

private:
    template <size_t ... Is>
    A impl(const A& a, const B& b, std::index_sequence<Is ...>) const
    { return A((a(Is) / b) ...); }
};

/// @brief Specialization of idlib::arithmetic_binary_star_functor computing
/// the \f$L \times N\f$ product matrix \f$C\f$ of an \f$L \times M\f$ matrix
/// \f$A\f$ and an \f$M \times N\f$ matrix \f$B\f$. The element \f$C_{i,j}\f$
/// of matrix \f$C\f$ is computed by
/// \f[
/// C_{i,j} = \sum_{i=0}^k A_{i,k} \cdot B_{k,j}
/// \f]
template <typename E, size_t L, size_t M, size_t N>
struct arithmetic_binary_star_functor<matrix<E, L, M>,
                                      matrix<E, M, N>>
{
    using B = matrix<E, M, N>;
    using A = matrix<E, L, M>;
    using C = matrix<E, L, N>;
    C operator()(const A& a, const B& b) const
    { return impl(a, b); }

private:
    C impl(const A& a, const B& b) const
    { 
        C c;
        for (size_t i = 0; i < L; ++i)
        {
            for (size_t j = 0; j < N; ++j)
            {
                for (size_t k = 0; k < M; ++k)
                {
                    c(i, j) += a(i, k) * b(k, j);
                }
            }
        }
        return c;
    }
};

/// @brief Specialization of idlib::trace_functor computing the trace of a non-empty square matrix.
/// @tparam E the element type of the matrix type
/// @tparam N the number of rows of the matrix type
/// @tparam M the number of columns of the matrix type
/// The trace of a square matrix \f$M\f$ of order \f$n\f$ is defined as
/// \f[
/// \sum_{i=0}^{n-1} M_{i,i}
/// \f]
template <typename E, size_t N, size_t M>
struct trace_functor<matrix<E, N, M>, std::enable_if_t<N == M>>
{
    using A = matrix<E, N, M>;
    using R = E;

    R operator()(const A& a) const
    {
        R t = zero<R>();
        for (size_t i = 0; i < N; ++i)
        {
            t += a(i, i);
        }
        return t;
    }
}; // struct trace_functor

/// @brief Specialization of idlib::transpose_functor computing the transpose of a non-empty matrix.
/// @tparam E the element type of the matrix type
/// @tparam N the number of rows of the matrix type
/// @tparam M the number of columns of the matrix type
/// The trace of a square matrix \f$M\f$ of order \f$n\f$ is defined as
/// \f[
/// \sum_{i=0}^{n-1} M_{i,i}
/// \f]
template <typename E, size_t N, size_t M>
struct transpose_functor<matrix<E, N, M>, void>
{
    using A = matrix<E, N, M>;
    using R = matrix<E, M, N>;

    R operator()(const A& a) const
    {
        R r;
        for (size_t i = 0; i < N; ++i)
        {
            for (size_t j = 0; j < M; ++j)
            {
                r(j, i) = a(i, j);
            }
        }
        return r;
    }
}; // struct transpose_functor

/// @brief Specialization of idlib::zero returning the null matrix.
template <typename E, size_t N, size_t M>
struct zero_functor<matrix<E, N, M>,
                    std::enable_if_t<(N > 0)>>
{
    using R = matrix<E, N, M>;
    R operator()() const
    { return R(); }
}; // struct zero_functor

/// @brief Specialization of idlib::identity_functor returning the identity (aka multiplicative neutral) matrix.
/// @remark The identity matrix is defined as
/// \f[
/// I_n = \begin{pmatrix} 1 & 0 & \cdots & 0 \\ 0 & 1 & \ddots & \vdots \\ \vdots & \ddots & \ddots & 0 \\ 0 & \cdots  & 0 & 1 \end{pmatrix}
/// \f]
template <typename E, size_t N, size_t M>
struct identity_functor<matrix<E, N, M>,
                        std::enable_if_t<(N > 0) && (N == M)>>
{
    using R = matrix<E, N, M>;
    R operator()() const
    {
        R r = zero<R>();
        for (size_t i = 0; i < N; ++i)
        {
            r(i, i) = one<E>();
        }
        return r;    
    }
}; // struct identity_functor

} // namespace idlib
