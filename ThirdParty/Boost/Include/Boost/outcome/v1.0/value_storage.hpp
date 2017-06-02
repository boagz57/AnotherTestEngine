/* Storage for the world's most simple C++ monad
(C) 2015-2017 Niall Douglas <http://www.nedproductions.biz/> (27 commits)
File Created: July 2015


Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License in the accompanying file
Licence.txt or at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


Distributed under the Boost Software License, Version 1.0.
    (See accompanying file Licence.txt or copy at
          http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_OUTCOME_VALUE_STORAGE_H
#define BOOST_OUTCOME_VALUE_STORAGE_H

#include "config.hpp"

BOOST_OUTCOME_V1_NAMESPACE_EXPORT_BEGIN

//! \brief Type tag for an empty monad \ingroup monad
struct empty_t
{
  constexpr empty_t() {}
};

//! \brief Variable of type empty_t \ingroup monad
constexpr empty_t empty = empty_t();

//! \brief Type tag for a valued monad \ingroup monad
struct value_t
{
  constexpr value_t() {}
};

//! \brief Variable of type value_t \ingroup monad
constexpr value_t value = value_t();

//! \brief Type tag for an errored monad \ingroup monad
struct error_t
{
  constexpr error_t() {}
};

//! \brief Variable of type error_t \ingroup monad
constexpr error_t error = error_t();

//! \brief Type tag for an excepted monad \ingroup monad
struct exception_t
{
  constexpr exception_t() {}
};

//! \brief Variable of type exception_t \ingroup monad
constexpr exception_t exception = exception_t();

//! \brief Specialise to indicate that this type should use the single byte storage layout. You get six bits of storage.
template <class _value_type> static constexpr bool enable_single_byte_value_storage = false;
//! \def BOOST_OUTCOME_DISABLE_DEFAULT_SINGLE_BYTE_VALUE_STORAGE
//! \brief Define to disable coercing option<void> and option<bool> into a single byte of storage
#ifdef DOXYGEN_IS_IN_THE_HOUSE
#define BOOST_OUTCOME_DISABLE_DEFAULT_SINGLE_BYTE_VALUE_STORAGE
#undef BOOST_OUTCOME_DISABLE_DEFAULT_SINGLE_BYTE_VALUE_STORAGE
#endif
// Temporarily disable single byte storage until GCC fixes itself
#if defined(__GNUC__) && !defined(__clang__) && __GNUC__ < 7
#define BOOST_OUTCOME_DISABLE_DEFAULT_SINGLE_BYTE_VALUE_STORAGE
#endif
#ifndef BOOST_OUTCOME_DISABLE_DEFAULT_SINGLE_BYTE_VALUE_STORAGE
template <> constexpr bool enable_single_byte_value_storage<void> = true;
template <> constexpr bool enable_single_byte_value_storage<bool> = true;
#endif

namespace detail
{
  // Older clangs have a bug where you can't use a templated variable to default template args, so indirect
  template <class _value_type> struct _enable_single_byte_value_storage
  {
    static constexpr bool value = enable_single_byte_value_storage<_value_type>;
  };
#define BOOST_OUTCOME_VALUE_STORAGE_IMPL value_storage_impl_trivial
#define BOOST_OUTCOME_VALUE_STORAGE_NON_TRIVIAL_DESTRUCTOR 0
#include "detail/value_storage.ipp"
#undef BOOST_OUTCOME_VALUE_STORAGE_IMPL
#undef BOOST_OUTCOME_VALUE_STORAGE_NON_TRIVIAL_DESTRUCTOR

#define BOOST_OUTCOME_VALUE_STORAGE_IMPL value_storage_impl_nontrivial
#define BOOST_OUTCOME_VALUE_STORAGE_NON_TRIVIAL_DESTRUCTOR 1
#include "detail/value_storage.ipp"
#undef BOOST_OUTCOME_VALUE_STORAGE_IMPL
#undef BOOST_OUTCOME_VALUE_STORAGE_NON_TRIVIAL_DESTRUCTOR

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 6287)  // the left and right sub expressions are identical
#endif
  template <class _value_type, class _error_type, class _exception_type>
  static constexpr bool can_have_trivial_destructor = (std::is_literal_type<_value_type>::value || std::is_trivially_destructible<_value_type>::value) && (std::is_literal_type<_error_type>::value || std::is_trivially_destructible<_error_type>::value) &&
                                                      (std::is_literal_type<_exception_type>::value || std::is_trivially_destructible<_exception_type>::value);
#ifdef _MSC_VER
#pragma warning(pop)
#endif
  template <bool enable> struct emplace_value_if
  {
    template <class U, class V> BOOST_OUTCOME_CONSTEXPR emplace_value_if(U *v, V &&o) { v->emplace_value(std::forward<V>(o)); }
  };
  template <> struct emplace_value_if<false>
  {
    template <class U, class V> BOOST_OUTCOME_CONSTEXPR emplace_value_if(U *v, V &&) { v->emplace_value(); }
  };
  template <bool enable> struct emplace_error_if
  {
    template <class U, class V> BOOST_OUTCOME_CONSTEXPR emplace_error_if(U *v, V &&o) { v->emplace_error(std::forward<V>(o)); }
  };
  template <> struct emplace_error_if<false>
  {
    template <class U, class V> BOOST_OUTCOME_CONSTEXPR emplace_error_if(U *v, V &&) { v->emplace_error(); }
  };
  template <bool enable> struct emplace_exception_if
  {
    template <class U, class V> BOOST_OUTCOME_CONSTEXPR emplace_exception_if(U *v, V &&o) { v->emplace_exception(std::forward<V>(o)); }
  };
  template <> struct emplace_exception_if<false>
  {
    template <class U, class V> BOOST_OUTCOME_CONSTEXPR emplace_exception_if(U *v, V &&) { v->emplace_exception(); }
  };

  template <bool enable, class U, class V> struct compare_if_impl
  {
    bool operator()(const U &v, const V &o) const { return v == o; }
  };
  template <class U, class V> struct compare_if_impl<false, U, V>
  {
    bool operator()(const U &, const V &) const { return false; }
  };
  template <bool enable, class U, class V> inline bool compare_if(const U &v, const V &o) { return compare_if_impl<enable, U, V>()(v, o); }
}

/*! \class value_storage
\tparam _value_type The value type to use
\tparam _error_type The error type to use. Can be void to disable.
\tparam _exception_type The exception type to use. Can be void to disable.
\brief A fixed lightweight variant store for monad.
\ingroup monad

This fixed variant list of empty, a type `value_type`, a lightweight `error_type` or a
heavier `exception_type` typically has a space cost of `max(24, sizeof(R)+8)`. If however
you specialise `enable_single_byte_value_storage<T>` with `true`, and both `error_type`
and `exception_type` are disabled (void), a special single byte storage implementation is
enabled. Both `bool` and `void` are already specialised.
*/
template <class _value_type, class _error_type, class _exception_type>
class value_storage : public std::conditional<detail::can_have_trivial_destructor<_value_type, _error_type, _exception_type>, detail::value_storage_impl_trivial<_value_type, _error_type, _exception_type>, detail::value_storage_impl_nontrivial<_value_type, _error_type, _exception_type>>::type
{
  using base = typename std::conditional<detail::can_have_trivial_destructor<_value_type, _error_type, _exception_type>, detail::value_storage_impl_trivial<_value_type, _error_type, _exception_type>, detail::value_storage_impl_nontrivial<_value_type, _error_type, _exception_type>>::type;

public:
  static constexpr bool has_value_type = base::has_value_type;
  static constexpr bool has_error_type = base::has_error_type;
  static constexpr bool has_exception_type = base::has_exception_type;
  using value_type = typename base::value_type;
  using error_type = typename base::error_type;
  using exception_type = typename base::exception_type;
  using storage_type = typename base::storage_type;
  using base::clear;
  static_assert(!std::is_same<value_type, error_type>::value, "value_type and error_type cannot be the same type");
  static_assert(!std::is_same<value_type, exception_type>::value, "value_type and exception_type cannot be the same type");
  static_assert(!std::is_same<error_type, exception_type>::value, "error_type and exception_type cannot be the same type");
  // static_assert(!std::is_constructible<value_type, error_type>::value, "value_type cannot be constructible from error_type");
  // static_assert(!std::is_constructible<value_type, exception_type>::value, "value_type cannot be constructible from exception_type");
  // static_assert(!std::is_constructible<error_type, exception_type>::value, "error_type cannot be constructible from exception_type");

  // Is this storage copy and move constructible?
  static constexpr bool is_nothrow_move_constructible = base::is_nothrow_move_constructible;
  static constexpr bool is_nothrow_copy_constructible = base::is_nothrow_copy_constructible;
  static constexpr bool is_nothrow_move_assignable = base::is_nothrow_move_assignable;
  static constexpr bool is_nothrow_copy_assignable = base::is_nothrow_copy_assignable;
  static constexpr bool is_nothrow_destructible = base::is_nothrow_destructible;

#if(defined(_MSC_VER) && _MSC_FULL_VER > 191025017 /* VS2017 RTM */) || __clang_major__ >= 4 || (__clang_major__ == 3 && __clang_minor__ >= 8)
  template <class _value_type2> static constexpr bool value_type_is_constructible_from = std::is_same<_value_type, _value_type2>::value || std::is_void<_value_type2>::value || std::is_constructible<_value_type, _value_type2>::value;
  template <class _error_type2> static constexpr bool error_type_is_constructible_from = std::is_void<_error_type2>::value || std::is_same<_error_type, _error_type2>::value || std::is_constructible<_error_type, _error_type2>::value;
  template <class _exception_type2> static constexpr bool exception_type_is_constructible_from = std::is_void<_exception_type2>::value || std::is_same<_exception_type, _exception_type2>::value || std::is_constructible<_exception_type, _exception_type2>::value;
  // True if this storage can be constructed from the specified storage
  template <class _value_type2, class _error_type2, class _exception_type2> static constexpr bool is_constructible_from = value_type_is_constructible_from<_value_type2> &&error_type_is_constructible_from<_error_type2> &&exception_type_is_constructible_from<_exception_type2>;

  template <class _value_type2> static constexpr bool value_type_is_comparable_to = std::is_void<_value_type2>::value || value_type_is_constructible_from<_value_type2>;
  template <class _error_type2> static constexpr bool error_type_is_comparable_to = error_type_is_constructible_from<_error_type2>;
  template <class _exception_type2> static constexpr bool exception_type_is_comparable_to = exception_type_is_constructible_from<_exception_type2>;
  // True if this storage can be compared to the specified storage
  template <class _value_type2, class _error_type2, class _exception_type2> static constexpr bool is_comparable_to = value_type_is_comparable_to<_value_type2> &&error_type_is_comparable_to<_error_type2> &&exception_type_is_comparable_to<_exception_type2>;

  template <class _value_type2, class _error_type2, class _exception_type2> using _is_constructible_from = typename std::conditional<is_constructible_from<_value_type2, _error_type2, _exception_type2>, std::true_type, std::false_type>::type;
  template <class _value_type2, class _error_type2, class _exception_type2> using _is_comparable_to = typename std::conditional<is_comparable_to<_value_type2, _error_type2, _exception_type2>, std::true_type, std::false_type>::type;
#else
  template <class _value_type2, class _error_type2, class _exception_type2>
  using _is_constructible_from = typename std::conditional<(std::is_same<_value_type, _value_type2>::value || std::is_void<_value_type2>::value || std::is_constructible<_value_type, _value_type2>::value) &&
                                                           (std::is_void<_error_type2>::value || std::is_same<_error_type, _error_type2>::value || std::is_constructible<_error_type, _error_type2>::value) &&
                                                           (std::is_void<_exception_type2>::value || std::is_same<_exception_type, _exception_type2>::value || std::is_constructible<_exception_type, _exception_type2>::value),
                                                           std::true_type, std::false_type>::type;
  template <class _value_type2, class _error_type2, class _exception_type2> using _is_comparable_to = typename std::conditional<std::is_void<_value_type2>::value || _is_constructible_from<_value_type2, _error_type2, _exception_type2>::value, std::true_type, std::false_type>::type;
#endif

  constexpr value_storage() = default;
  constexpr value_storage(const value_storage &) = default;
  constexpr value_storage(value_storage &&) = default;
  BOOST_OUTCOME_CONSTEXPR value_storage &operator=(const value_storage &) = default;
  BOOST_OUTCOME_CONSTEXPR value_storage &operator=(value_storage &&) = default;
  constexpr value_storage(empty_t _) noexcept : base(_) {}
  constexpr value_storage(value_t _) noexcept(std::is_nothrow_default_constructible<value_type>::value)
      : base(_)
  {
  }
  constexpr value_storage(error_t _) noexcept(std::is_nothrow_default_constructible<error_type>::value)
      : base(_)
  {
  }
  constexpr value_storage(exception_t _) noexcept(std::is_nothrow_default_constructible<exception_type>::value)
      : base(_)
  {
  }
  constexpr value_storage(const value_type &v) noexcept(std::is_nothrow_copy_constructible<value_type>::value)
      : base(v)
  {
  }
  constexpr value_storage(const error_type &v) noexcept(std::is_nothrow_copy_constructible<error_type>::value)
      : base(v)
  {
  }
  constexpr value_storage(const exception_type &v) noexcept(std::is_nothrow_copy_constructible<exception_type>::value)
      : base(v)
  {
  }
  constexpr value_storage(value_type &&v) noexcept(std::is_nothrow_move_constructible<value_type>::value)
      : base(std::move(v))
  {
  }
  constexpr value_storage(error_type &&v) noexcept(std::is_nothrow_move_constructible<error_type>::value)
      : base(std::move(v))
  {
  }
  constexpr value_storage(exception_type &&v) noexcept(std::is_nothrow_move_constructible<exception_type>::value)
      : base(std::move(v))
  {
  }
  using emplace_t = typename base::emplace_t;
  template <class... Args>
  constexpr explicit value_storage(emplace_t _, Args &&... args)
#if !defined(_MSC_VER) || _MSC_VER > 190022816
  noexcept(std::is_nothrow_constructible<value_type, Args...>::value)
#endif
      : base(_, std::forward<Args>(args)...)
  {
  }
  template <class _value_type2, class _error_type2, class _exception_type2, typename = typename std::enable_if<_is_constructible_from<_value_type2, _error_type2, _exception_type2>::value>::type>
  BOOST_OUTCOME_CONSTEXPR explicit value_storage(const value_storage<_value_type2, _error_type2, _exception_type2> &o)
      : base()
  {
    switch(o.type)
    {
    case storage_type::empty:
      break;
    case storage_type::value:
      detail::emplace_value_if<has_value_type && value_storage<_value_type2, _error_type2, _exception_type2>::has_value_type>(this, o.value);
      break;
    case storage_type::error:
      detail::emplace_error_if<has_error_type && value_storage<_value_type2, _error_type2, _exception_type2>::has_error_type>(this, o.error);
      break;
    case storage_type::exception:
      detail::emplace_exception_if<has_exception_type && value_storage<_value_type2, _error_type2, _exception_type2>::has_exception_type>(this, o.exception);
      break;
    }
  }
  template <class _value_type2, class _error_type2, class _exception_type2, typename = typename std::enable_if<base::is_referenceable && _is_constructible_from<_value_type2, _error_type2, _exception_type2>::value>::type>
  BOOST_OUTCOME_CONSTEXPR explicit value_storage(value_storage<_value_type2, _error_type2, _exception_type2> &&o)
      : base()
  {
    switch(o.type)
    {
    case storage_type::empty:
      break;
    case storage_type::value:
      detail::emplace_value_if<has_value_type && value_storage<_value_type2, _error_type2, _exception_type2>::has_value_type>(this, std::move(o.value));
      break;
    case storage_type::error:
      detail::emplace_error_if<has_error_type && value_storage<_value_type2, _error_type2, _exception_type2>::has_error_type>(this, std::move(o.error));
      break;
    case storage_type::exception:
      detail::emplace_exception_if<has_exception_type && value_storage<_value_type2, _error_type2, _exception_type2>::has_exception_type>(this, std::move(o.exception));
      break;
    }
  }
  struct valueless_t
  {
  };  // used to tag when incoming storage cannot have a value
  template <class _value_type2, class _error_type2, class _exception_type2, typename = typename std::enable_if<base::is_referenceable && _is_constructible_from<_value_type2, _error_type2, _exception_type2>::value>::type>
  BOOST_OUTCOME_CONSTEXPR explicit value_storage(valueless_t, value_storage<_value_type2, _error_type2, _exception_type2> &&o)
      : base()
  {
    switch(o.type)
    {
    case storage_type::empty:
      break;
    case storage_type::value:
      break;
    case storage_type::error:
      detail::emplace_error_if<has_error_type && value_storage<_value_type2, _error_type2, _exception_type2>::has_error_type>(this, std::move(o.error));
      break;
    case storage_type::exception:
      detail::emplace_exception_if<has_exception_type && value_storage<_value_type2, _error_type2, _exception_type2>::has_exception_type>(this, std::move(o.exception));
      break;
    }
  }
  BOOST_OUTCOME_CONSTEXPR void set_state(value_storage &&o) noexcept(is_nothrow_destructible &&is_nothrow_move_constructible)
  {
    clear();
    new(this) value_storage(std::move(o));
  }

  void swap(value_storage &o) noexcept(is_nothrow_move_constructible)
  {
    if(this->type == o.type)
    {
      switch(this->type)
      {
      case storage_type::empty:
        break;
      case storage_type::value:
        std::swap(this->value, o.value);
        break;
      case storage_type::error:
        std::swap(this->error, o.error);
        break;
      case storage_type::exception:
        std::swap(this->exception, o.exception);
        break;
      }
    }
    else
    {
      value_storage temp(std::move(o));
#if defined(__cpp_exceptions)
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4297)  // use of throw within a noexcept function
#endif
#if defined(__GNUC__) && !defined(__clang__) && __GNUC__ >= 6
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wterminate"
#endif
      try
      {
        try
        {
          o = std::move(*this);
          try
          {
            *this = std::move(temp);
          }
          catch(...)
          {
            *this = std::move(o);
            throw;
          }
        }
        catch(...)
        {
          o = std::move(temp);
          throw;
        }
      }
      catch(...)
      {
        // Silence static analysers
        if(is_nothrow_move_constructible)
          std::terminate();
        else
          throw;
      }
#if defined(__GNUC__) && !defined(__clang__) && __GNUC__ >= 6
#pragma GCC diagnostic pop
#endif
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#else
      o = std::move(*this);
      *this = std::move(temp);
#endif
    }
  }
  template <class _value_type2, class _error_type2, class _exception_type2, typename = typename std::enable_if<_is_comparable_to<_value_type2, _error_type2, _exception_type2>::value>::type> BOOST_OUTCOME_CONSTEXPR bool operator==(const value_storage<_value_type2, _error_type2, _exception_type2> &o) const
  {
    if(this->type != o.type)
      return false;
    switch(this->type)
    {
    case storage_type::empty:
      return true;
    case storage_type::value:
      return (!has_value_type && !value_storage<_value_type2, _error_type2, _exception_type2>::has_value_type) || detail::compare_if < has_value_type && value_storage<_value_type2, _error_type2, _exception_type2>::has_value_type > (this->value, o.value);
    case storage_type::error:
      return detail::compare_if < has_error_type && value_storage<_value_type2, _error_type2, _exception_type2>::has_error_type > (this->error, o.error);
    case storage_type::exception:
      return detail::compare_if < has_exception_type && value_storage<_value_type2, _error_type2, _exception_type2>::has_exception_type > (this->exception, o.exception);
    }
    return false;
  }
  template <class _value_type2, class _error_type2, class _exception_type2, typename = typename std::enable_if<_is_comparable_to<_value_type2, _error_type2, _exception_type2>::value>::type> BOOST_OUTCOME_CONSTEXPR bool operator!=(const value_storage<_value_type2, _error_type2, _exception_type2> &o) const
  {
    return !(*this == o);
  }
};

BOOST_OUTCOME_V1_NAMESPACE_END

#ifndef BOOST_OUTCOME_DISABLE_IOSTREAMS
namespace std
{
  //! \brief Deserialise a value_storage value_type (only value_type) \ingroup monad
  template <class _value_type, class _error_type, class _exception_type> inline istream &operator>>(istream &s, BOOST_OUTCOME_V1_NAMESPACE::value_storage<_value_type, _error_type, _exception_type> &v)
  {
    using namespace BOOST_OUTCOME_V1_NAMESPACE;
    switch(v.type)
    {
    case value_storage<_value_type, _error_type, _exception_type>::storage_type::value:
      return s >> v.value;
    default:
      BOOST_OUTCOME_THROW_DESERIALISATION_FAILURE(v, ios_base::failure("Set the type of lightweight_futures::value_storage to a value_type before deserialising into it"));
    }
  }
  //! \brief Serialise a value_storage. Mostly useful for debug printing. \ingroup monad
  template <class _value_type> inline ostream &operator<<(ostream &s, const BOOST_OUTCOME_V1_NAMESPACE::value_storage<_value_type, void, void> &v)
  {
    using namespace BOOST_OUTCOME_V1_NAMESPACE;
    using _error_type = void;
    using _exception_type = void;
    switch(v.type)
    {
    case value_storage<_value_type, _error_type, _exception_type>::storage_type::empty:
      return s << "(empty)";
    case value_storage<_value_type, _error_type, _exception_type>::storage_type::value:
      return s << v.value;
    default:
      return s << "(unknown)";
    }
  }
  template <class _value_type, class _error_type> inline ostream &operator<<(ostream &s, const BOOST_OUTCOME_V1_NAMESPACE::value_storage<_value_type, _error_type, void> &v)
  {
    using namespace BOOST_OUTCOME_V1_NAMESPACE;
    using _exception_type = void;
    switch(v.type)
    {
    case value_storage<_value_type, _error_type, _exception_type>::storage_type::empty:
      return s << "(empty)";
    case value_storage<_value_type, _error_type, _exception_type>::storage_type::value:
      return s << v.value;
    case value_storage<_value_type, _error_type, _exception_type>::storage_type::error:
      return s << v.error;
    default:
      return s << "(unknown)";
    }
  }
  template <class _value_type, class _error_type, class _exception_type> inline ostream &operator<<(ostream &s, const BOOST_OUTCOME_V1_NAMESPACE::value_storage<_value_type, _error_type, _exception_type> &v)
  {
    using namespace BOOST_OUTCOME_V1_NAMESPACE;
    switch(v.type)
    {
    case value_storage<_value_type, _error_type, _exception_type>::storage_type::empty:
      return s << "(empty)";
    case value_storage<_value_type, _error_type, _exception_type>::storage_type::value:
      return s << v.value;
    case value_storage<_value_type, _error_type, _exception_type>::storage_type::error:
      return s << v.error;
    case value_storage<_value_type, _error_type, _exception_type>::storage_type::exception:
#ifdef __cpp_exceptions
      try
      {
        rethrow_exception(v.exception);
      }
      catch(const system_error &e)
      {
        return s << "std::system_error code " << e.code() << ": " << e.what();
      }
      /*catch(const future_error &e)
      {
      return s << "(std::future_error code " << e.code() << ": " << e.what() << ")";
      }*/
      catch(const exception &e)
      {
        return s << "std::exception: " << e.what();
      }
      catch(...)
#endif
      {
        return s << "unknown exception";
      }
    default:
      return s << "(unknown)";
    }
  }
}
#endif

#endif
