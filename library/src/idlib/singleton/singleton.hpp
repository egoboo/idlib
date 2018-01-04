// Copyright Michael Heilmann 2016, 2017, 2018.
//
// This file is part of Idlib.
//
// Idlib is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Idlib is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Idlib. If not, see <http://www.gnu.org/licenses/>.

/// @file idlib/singleton/hpp.hpp
/// @brief Singleton implementation.
/// Directly copied from http://en.cppreference.com/w/cpp/algorithm/clamp.
/// @author Michael Heilmann

#pragma once

#include "idlib/utility.hpp"
#include <atomic>
#include <mutex>

namespace id {

/// @brief Functor for creating an object of type @a Type.
/// @a default_create_functor is the default new policy for @a singleton when no new policy is provided.
/// @tparam Type the type of the object to create
/// @tparam ... Arguments the arguments of the constructor
template <typename Type, typename ... Arguments>
struct default_new_functor
{
    Type *operator()(Arguments&& ... arguments) const
	{
        return new Type(std::forward<Arguments>(arguments)...);
    }
};

/// @brief Functor for destroying an object of type @a Type or a derived type.
/// @a default_destroy_functor is the default delete policy for a @a singleton when no delete policy is provided.
/// @tparam Type the type of the object
template <typename Type>
struct default_delete_functor
{
    void operator()(Type *o) const
	{
        delete o;
    }
};

/// @brief If defined to @a 1, the singleton inherits from id::non_copyable.
#define ID_SINGLETON_NONCOPYABLE (1)

/// @brief Double-checked locking singleton with subtyping.
/// Inherit from <tt>singleton&lt;InstanceType&gt;</tt> to create a singleton. 
///
/// Example usage for <tt>singleton&lt;InstanceType&gt;</tt>:
/// @code
/// class a : public singleton<a>
/// {
/// public:
///  a()
///  {}
///  ~a()
///  {}
/// };
/// @endcode
/// The singleton is initialized by
/// @code
/// a::initialize();
/// @endcode
/// and uninitialize by
/// @code
/// a::uninitialize();
/// @endcode
///
/// It is recommended to make the constructors and destructors of @a a protected as no one else shall invoke these constructors except for the singleton.
/// @code
/// class a : public singleton<a>
/// {
/// protected:
///  a()
///  {}
///  ~a()
///  {}
/// };
/// @endcode
/// However, the @a singleton<T> will then not be able to invoke these constructors/destructors as well.
/// The solution is to provide new and delete functors and make them friends of @a a.
/// @code
/// class a;
///
/// struct a_new_functor
/// { a *operator()() const; };
///
/// struct a_new_functor
/// { void operator()(a *p) const; };
///
/// class a : public singleton<a, a_new_functor, a_delete_functor>
/// {
/// protected:
///  friend struct a_new_functor;
///  friend struct a_delete_functor;
///  ...
/// };
/// @endcode
/// Maybe @a a has non-default constructors. To allow singleton creation using non-default constructors simply use perfect forwarding.
/// @code
/// struct a_new_functor
/// { 
///   template <typename ... Arguments> 
///   a *operator()(Arguments ... arguments) const { return new a(std::forward<Arguments>(arguments ...); }
/// };
/// @endcode
///
///
/// If you want to create an object that is a subtype of @a a. Simply adjust the new functor accordingly.
/// @code
/// struct a_new_functor
/// { 
///   template <typename ... Arguments> 
///   a *operator()(Arguments ... arguments) const { return new b(std::forward<Arguments>(arguments ...); }
/// };
/// @endcode
/// where @a b is a subclass of @a a.
///
/// This implementation performs double-checked locking i.e. @a a::initialize and @a a::uninitialize are thread-safe.
/// (a problem described in "Myers, Alexadrescu; "C++ and the Perils of Double-Checked Locking"; 2014).
template <typename Type, typename Create = default_new_functor<Type>, typename Destroy = default_delete_functor<Type>>
class singleton
#if defined(ID_SINGLETON_NONCOPYABLE) && 1 == ID_SINGLETON_NONCOPYABLE
    : private non_copyable
#endif
{
	using type = Type;
    using create_type = Create;
    using destroy_type = Destroy;

protected:
    /// @brief Constructor.
    /// @remark Intentionally protected.
    singleton() {}

    /// @brief Destructor.
    /// @remark Intentionally protected.
    virtual ~singleton() {}

    /// @brief Mutex protecting non-atomic operations.
    /// @remark Intentionally private.
    static std::mutex mutex;

    /// @brief Singleton instance.
    /// @remark Intentionally private.
    static std::atomic<type *> instance;

public:
	/// @brief Get if the singleton is initialized.
	/// @return @a true if the singleton is initialized, @a false otherwise
    /// @warning
    /// The test is just informative, its information is not imperative - by the time the caller acquires the information, facts might already have changed.
    static bool is_initialized() 
	{
        type *o = instance.load();
        return nullptr != o;
    }

    /// @brief Get the instance.
    /// @return the instance
    /// @pre The singleton must be initialized.
	/// @throw std::logic_error the singleton might not be initialized.
	/// @warning Uninitializing the singleton will invalidate any references returned by calls to this method prior to uninitialization.
    static type& get() {
        type *o = instance.load();
        if (!o) {
            throw std::logic_error("singleton not initialized");
        }
        return *o;
    }

    /// @brief Uninitialize the singleton.
    /// @remark If the singleton is not initialized, a call to this method is a no-op.
    static void uninitialize() {
        type *o = instance.load();
        if (o) { // 1st check.
            std::lock_guard<std::mutex> lock(mutex);
            o = instance.load();
            if (o) { // 2nd check.
                instance.store(nullptr);
                destroy_type()(o);
            }
        }
    }

    /// @brief Initialize the singleton.
    /// @post The singleton was initialized if no exception was raised by this call.
    /// @remark If the singleton is initialized, a call to this method is a no-op.
    template<typename ... Arguments>
    static void initialize(Arguments&& ... arguments) {
        type *o = instance.load();
        if (!o) { // 1st check.
            std::lock_guard<std::mutex> lock(mutex);
            o = instance.load();
            if (!o) { // 2nd check.
                o = create_type()(std::forward<Arguments>(arguments) ...);
                instance.store(o);
            }
        }
    }
}; // class singleton

template <typename Type, typename Create, typename Destroy>
std::mutex singleton<Type, Create, Destroy>::mutex;

template <typename Type, typename Create, typename Destroy>
std::atomic<Type *> singleton<Type, Create, Destroy>::instance(nullptr);

} // namespace id
