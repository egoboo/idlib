    /// @{
    /// @brief Get the value of the alpha component.
    /// @return the value of the alpha component
    const component_a& get_alpha() const noexcept
    { return a; }
#if defined(ID_COLOR_SHORT_GETTERS) && 1 == ID_COLOR_SHORT_GETTERS
    const component_a& get_a() const noexcept
    { return a; }
#endif
    /// @}
