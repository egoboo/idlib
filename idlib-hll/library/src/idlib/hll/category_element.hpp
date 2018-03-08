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

#pragma once

namespace idlib::hll {

/// @tparam Category the category type
/// @tparam DefaultCategory the default category
template <typename Category, Category DefaultCategory>
struct category_element
{
public:
    /// @brief The category type.
    using category_type = Category;
private:
    /// @brief The category.
    category_type m_category;
public:
    /// @brief Construct this category element with the default category.
    category_element() :
        m_category(DefaultCategory)
    {}

    /// @brief Construct this category element with the specified category.
    /// @param category the category
    category_element(const category_type& category) :
        m_category(category)
    {}

    /// @brief Get the category of this category element.
    /// @return the category of this category element
    constexpr const category_type& category() const noexcept
    { return m_category; }

    /// @brief Set the category of this category element.
    /// @param category the category of this category element
    void category(const category_type& category) noexcept
    { m_category = category; }

public:
    /// @brief Get if this category element is in the specified category.
    /// @param category the category
    /// @return @a true if this category is in the specified category @a category, @a false otherwise
    constexpr bool is_one_of(const category_type& category) const noexcept
    { return category == this->category(); }

    /// @brief Get if this category element is in the specified categories.
    /// @param category1, category2 the categories
    /// @return @a true if this category is in the specified categories @a category1 or @a category2, @a false otherwise
    constexpr bool is_one_of(const category_type& category1, const category_type& category2) const noexcept
    { return is_one_of(category1) || is_one_of(category2); }

    /// @brief Get if this category element is in the specified categories.
    /// @param category1, category2, categories the categories
    /// @return @a true if this category element is in the specified categories @a category1, @a category2, or @a categories, @a false otherwise
    template <typename ... Categories>
    constexpr bool is_one_of(const category_type& category1, const category_type& category2, Categories ... categories) const noexcept
    { return is_one_of(category1) || is_one_of(category2, categories ...); }

}; // class category_element

} // namespace idlib::hll
