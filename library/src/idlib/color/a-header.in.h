public:
/// @brief The type of the alpha component.
using component_a = typename color_space_type::a::syntax::underlying_type;

private:
/// @brief The alpha component value.
/// @invariant Within the bounds of color_space::min() (inclusive) and color_space::max() (inclusive).
component_a a;
