#pragma once

namespace id { namespace c {

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

} } // namespace id::c
