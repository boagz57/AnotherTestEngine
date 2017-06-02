/* The world's most simple C++ monad
(C) 2015-2017 Niall Douglas <http://www.nedproductions.biz/> (59 commits)
File Created: June 2015


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

#ifndef BOOST_OUTCOME_MONAD_HPP
#define BOOST_OUTCOME_MONAD_HPP

#ifndef BOOST_OUTCOME_HEADERS_PATH
#error Please do not include monad.hpp directly, include master outcome.hpp file instead
#endif

#if defined(__cpp_modules) || defined(DOXYGEN_SHOULD_SKIP_THIS)
#if defined(_MSC_VER) && !defined(__clang__)
//! \brief The Outcome C++ module name
#define BOOST_OUTCOME_MODULE_NAME BOOST_OUTCOME_VERSION_GLUE(outcome_v, BOOST_OUTCOME_NAMESPACE_VERSION, )
#elif !__PCPP_ALWAYS_FALSE__
//! \brief The Outcome C++ module name
#define BOOST_OUTCOME_MODULE_NAME BOOST_OUTCOME_VERSION_GLUE(outcome_v, BOOST_OUTCOME_NAMESPACE_VERSION, )
#endif
#endif

// If C++ Modules are on and we are not compiling the library,
// we are either generating the interface or importing
#if defined(__cpp_modules)
#if defined(GENERATING_OUTCOME_MODULE_INTERFACE)
// We are generating this module's interface
#define BOOSTLITE_HEADERS_ONLY 0
#define BOOST_OUTCOME_HEADERS_ONLY 0
#define BOOST_OUTCOME_INCLUDE_ALL
#elif defined(BOOST_OUTCOME_SOURCE)
// We are implementing this module
#define BOOST_OUTCOME_INCLUDE_ALL
#else
// We are importing this module
import BOOST_OUTCOME_MODULE_NAME;
#undef BOOST_OUTCOME_INCLUDE_ALL
#endif
#else
// C++ Modules not on, therefore include as usual
#define BOOST_OUTCOME_INCLUDE_ALL
#endif

#ifdef BOOST_OUTCOME_INCLUDE_ALL

#include "config.hpp"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4714)  // failure to __forceinline
#pragma warning(disable : 4996)  // use of strncpy
#endif

#include "error_code_extended.hpp"
#include "monad_error.hpp"
#include "value_storage.hpp"

#include "../boost-lite/include/tribool.hpp"

/*! \defgroup macro_helpers Useful preprocessor macros which expand into commonly written boilerplate
\ingroup monad
*/

BOOST_OUTCOME_V1_NAMESPACE_EXPORT_BEGIN

template <class implementation_policy> class basic_monad;

namespace detail
{
  template <class M> struct is_monad : std::false_type
  {
  };
  template <class Impl> struct is_monad<basic_monad<Impl>> : std::true_type
  {
  };
  // Internal type sugar to indicate that a monad is guaranteed to be valueless
  template <class M> struct tagged_valueless
  {
    M value;
  };
  template <class M> tagged_valueless<M> tag_valueless(M &&m) { return tagged_valueless<M>{std::forward<M>(m)}; }
}

#ifdef BOOST_OUTCOME_ENABLE_ADVANCED
BOOST_OUTCOME_V1_NAMESPACE_END
#include "advanced_support.hpp"
BOOST_OUTCOME_V1_NAMESPACE_EXPORT_BEGIN
#endif

//! \brief Tag type for in_place construction
struct in_place_t
{
  constexpr in_place_t() {}
};
//! \brief Constexpr instance of in_place construction tag type
constexpr in_place_t in_place;

//! \brief True if the type passed is a monad or a reference to a monad
template <class M> static constexpr bool is_monad = detail::is_monad<typename std::decay<M>::type>::value;

//! \brief Specialise to whitelist a type with throwing move constructors for use with basic monad
template <class T>
static constexpr bool enable_move_throwing_type = (std::is_move_constructible<T>::value && std::is_nothrow_move_constructible<T>::value) || (std::is_copy_constructible<T>::value && std::is_nothrow_copy_constructible<T>::value) || (!std::is_move_constructible<T>::value && !std::is_copy_constructible<T>::value);

/*! \class basic_monad
\brief Implements a configurable lightweight simple monadic value transport with the same semantics and API as a future
\tparam implementation_policy An implementation policy type
\ingroup monad

*/
#ifdef DOXYGEN_IS_IN_THE_HOUSE
template <class implementation_policy> class BOOSTLITE_NODISCARD basic_monad : public implementation_policy
#else
template <class implementation_policy> class BOOSTLITE_NODISCARD basic_monad : public implementation_policy::base
#endif
{
  // Allow my policy unfettered acces
  friend implementation_policy;
  // Allow my policy specialised with void unfettered access
  friend typename implementation_policy::template rebind_policy<void>;
  // Allow other implementations of myself unfettered access
  template <class U> friend class basic_monad;
#ifndef BOOST_OUTCOME_DISABLE_IOSTREAMS
  // Allow serialisation
  friend inline std::istream &operator>>(std::istream &s, basic_monad &v) { return s >> v._storage; }
  friend inline std::ostream &operator<<(std::ostream &s, const basic_monad &v) { return s << v._storage; }
#endif

protected:
  struct from_value_storage_type_t
  {
  };
  typedef value_storage<typename implementation_policy::value_type, typename implementation_policy::error_type, typename implementation_policy::exception_type> value_storage_type;
  constexpr explicit basic_monad(from_value_storage_type_t, value_storage_type &&s)
      : implementation_policy::base(std::move(s))
  {
  }

public:
  //! \brief This monad has a value_type
  static constexpr bool has_value_type = value_storage_type::has_value_type;
  //! \brief This monad has an error_type
  static constexpr bool has_error_type = value_storage_type::has_error_type;
  //! \brief This monad has an exception_type
  static constexpr bool has_exception_type = value_storage_type::has_exception_type;
  //! \brief The final implementation type
  typedef typename implementation_policy::implementation_type implementation_type;
  //! \brief The type potentially held by the monad
  typedef typename value_storage_type::value_type value_type;
  //! \brief The raw type potentially held by the monad
  typedef typename implementation_policy::value_type raw_value_type;
  //! \brief The error code potentially held by the monad
  typedef typename value_storage_type::error_type error_type;
  //! \brief The raw error code potentially held by the monad
  typedef typename implementation_policy::error_type raw_error_type;
  //! \brief The exception ptr potentially held by the monad
  typedef typename value_storage_type::exception_type exception_type;
  //! \brief The raw exception ptr potentially held by the monad
  typedef typename implementation_policy::exception_type raw_exception_type;
  //! \brief Tag type for an empty monad
  struct empty_type
  {
    typedef implementation_type parent_type;
  };
  //! \brief Rebind this monad type into a different value_type
  template <typename U> using rebind = typename implementation_policy::template rebind<U>;

  // If types are move constructible, make sure they are nothrow move constructible
  static_assert(enable_move_throwing_type<value_type>,
                "WARNING: value_type used in basic_monad is not nothrow move constructible which means you must write code to handle valueless by exception every time a move happens. Either make your type never throw during moves, or specialise enable_move_throwing_type<T> to disable this check.");
  static_assert(enable_move_throwing_type<error_type>,
                "WARNING: error_type used in basic_monad is not nothrow move constructible which means you must write code to handle valueless by exception every time a move happens. Either make your type never throw during moves, or specialise enable_move_throwing_type<T> to disable this check.");
  static_assert(enable_move_throwing_type<exception_type>,
                "WARNING: exception_type used in basic_monad is not nothrow move constructible which means you must write code to handle valueless by exception every time a move happens. Either make your type never throw during moves, or specialise enable_move_throwing_type<T> to disable this check.");

private:
  struct implicit_conversion_from_void_disabled
  {
  };
  using void_rebound = typename std::conditional<has_value_type, rebind<void>, implicit_conversion_from_void_disabled>::type;

public:
  //! \brief This monad can be default constructed
  static constexpr bool is_default_constructible = implementation_policy::is_default_constructible;
  //! \brief This monad will never throw exceptions during default construction
  static constexpr bool is_nothrow_default_constructible = implementation_policy::is_nothrow_default_constructible;
  //! \brief This monad can be copy constructed
  static constexpr bool is_copy_constructible = value_storage_type::is_copy_constructible;
  //! \brief This monad will never throw exceptions during copy construction
  static constexpr bool is_nothrow_copy_constructible = value_storage_type::is_nothrow_copy_constructible;
  //! \brief This monad can be move constructed
  static constexpr bool is_move_constructible = value_storage_type::is_move_constructible;
  //! \brief This monad will never throw exceptions during move construction
  static constexpr bool is_nothrow_move_constructible = value_storage_type::is_nothrow_move_constructible;
  //! \brief This monad can be copy assigned
  static constexpr bool is_copy_assignable = value_storage_type::is_copy_assignable;
  //! \brief This monad will never throw exceptions during copy assignment
  static constexpr bool is_nothrow_copy_assignable = value_storage_type::is_nothrow_copy_assignable;
  //! \brief This monad can be move assigned
  static constexpr bool is_move_assignable = value_storage_type::is_move_assignable;
  //! \brief This monad will never throw exceptions during move assignment
  static constexpr bool is_nothrow_move_assignable = value_storage_type::is_nothrow_move_assignable;
  //! \brief This monad will never throw exceptions during destruction
  static constexpr bool is_nothrow_destructible = value_storage_type::is_nothrow_destructible;
  //! \brief This monad does not implement a destructor
  static constexpr bool is_trivially_destructible = value_storage_type::is_trivially_destructible;
#if defined(DOXYGEN_IS_IN_THE_HOUSE) || defined(__c2__) || (!defined(_MSC_VER) || _MSC_FULL_VER > 191025017 /* VS2017 RTM */)
  //! \brief This monad is constructible from the monad specified
  template <class OtherMonad> static constexpr bool is_constructible = value_storage_type::template is_constructible_from<typename OtherMonad::raw_value_type, typename OtherMonad::raw_error_type, typename OtherMonad::raw_exception_type>;
  //! \brief This monad is comparable to the monad specified. Note this is as if ThisMonad::operator==(OtherMonad), so without associativity i.e. is this monad comparable to the other monad which != the other monad is comparable to this monad.
  template <class OtherMonad> static constexpr bool is_comparable = value_storage_type::template is_comparable_to<typename OtherMonad::raw_value_type, typename OtherMonad::raw_error_type, typename OtherMonad::raw_exception_type>;
#endif

  // MSVC can't cope with the above, so for compatibility:
  template <class OtherMonad> using _is_constructible = typename value_storage_type::template _is_constructible_from<typename OtherMonad::raw_value_type, typename OtherMonad::raw_error_type, typename OtherMonad::raw_exception_type>;
  template <class OtherMonad> using _is_comparable = typename value_storage_type::template _is_comparable_to<typename OtherMonad::raw_value_type, typename OtherMonad::raw_error_type, typename OtherMonad::raw_exception_type>;

// Define all my constructors, this is reused below later
#define BOOST_OUTCOME_BASIC_MONAD_NAME basic_monad
#include "detail/basic_monad.ipp"

  // Deliberately don't document this constructor
  template <class OtherMonad>
  constexpr basic_monad(detail::tagged_valueless<OtherMonad> &&v) noexcept(std::is_nothrow_move_constructible<error_type>::value)
      : implementation_policy::base(typename implementation_policy::base::passthru_t(), std::move(v))
  {
  }

  //! \brief Same as `true_(tribool(*this))`
  constexpr explicit operator bool() const noexcept { return has_value(); }
  //! \brief True if monad contains a value_type, unknown if monad is empty, else false if monad is errored/excepted.
  constexpr explicit operator boost_lite::tribool::tribool() const noexcept { return has_value() ? boost_lite::tribool::tribool::true_ : empty() ? boost_lite::tribool::tribool::unknown : boost_lite::tribool::tribool::false_; }
  //! \brief True if monad is not empty
  constexpr bool is_ready() const noexcept { return implementation_policy::base::_storage.type != value_storage_type::storage_type::empty; }
  //! \brief True if monad is empty
  constexpr bool empty() const noexcept { return implementation_policy::base::_storage.type == value_storage_type::storage_type::empty; }
  //! \brief True if monad contains a value_type
  constexpr bool has_value() const noexcept { return implementation_policy::base::_storage.type == value_storage_type::storage_type::value; }
  //! \brief True if monad contains an error_type
  constexpr bool has_error() const noexcept { return implementation_policy::base::_storage.type == value_storage_type::storage_type::error; }
  /*! \brief True if monad contains an exception_type or error_type (any error_type is returned as an exception_ptr by get_exception()).
  This needs to be true for both for compatibility with Boost.Thread's future. If you really want to test only for has exception only,
  pass true as the argument.
  */
  constexpr bool has_exception(bool only_exception = false) const noexcept { return implementation_policy::base::_storage.type == value_storage_type::storage_type::exception || (!only_exception && implementation_policy::base::_storage.type == value_storage_type::storage_type::error); }

  //! \brief If contains a value_type, return that value type, else return the supplied value_type
  BOOST_OUTCOME_CONSTEXPR value_type &get_or(value_type &v) & noexcept { return has_value() ? implementation_policy::base::_storage.value : v; }
  //! \brief If contains a value_type, return that value type, else return the supplied value_type
  BOOST_OUTCOME_CONSTEXPR value_type &value_or(value_type &v) & noexcept { return has_value() ? implementation_policy::base::_storage.value : v; }
  //! \brief If contains a value_type, return that value type, else return the supplied value_type
  constexpr const value_type &get_or(const value_type &v) const &noexcept { return has_value() ? implementation_policy::base::_storage.value : v; }
  //! \brief If contains a value_type, return that value type, else return the supplied value_type
  constexpr const value_type &value_or(const value_type &v) const &noexcept { return has_value() ? implementation_policy::base::_storage.value : v; }
  //! \brief If contains a value_type, return that value type, else return the supplied value_type
  BOOST_OUTCOME_CONSTEXPR value_type &&get_or(value_type &&v) && noexcept { return has_value() ? std::move(implementation_policy::base::_storage.value) : std::move(v); }
  //! \brief If contains a value_type, return that value type, else return the supplied value_type
  BOOST_OUTCOME_CONSTEXPR value_type &&value_or(value_type &&v) && noexcept { return has_value() ? std::move(implementation_policy::base::_storage.value) : std::move(v); }
  //! \brief If contains a value_type, return that value type, else return the supplied value_type
  BOOST_OUTCOME_CONSTEXPR const value_type &&get_or(const value_type &&v) const &&noexcept { return has_value() ? std::move(implementation_policy::base::_storage.value) : std::move(v); }
  //! \brief If contains a value_type, return that value type, else return the supplied value_type
  BOOST_OUTCOME_CONSTEXPR const value_type &&value_or(const value_type &&v) const &&noexcept { return has_value() ? std::move(implementation_policy::base::_storage.value) : std::move(v); }
  //! \brief Disposes of any existing state, setting the monad to the value storage
  BOOST_OUTCOME_CONSTEXPR void set_state(value_storage_type &&v) { implementation_policy::base::_storage.set_state(std::move(v)); }
  //! \brief Disposes of any existing state, setting the monad to a copy of the value_type
  BOOST_OUTCOME_CONSTEXPR void set_value(const value_type &v) { implementation_policy::base::_storage.emplace_value(v); }
  //! \brief Disposes of any existing state, setting the monad to a move of the value_type
  BOOST_OUTCOME_CONSTEXPR void set_value(value_type &&v) { implementation_policy::base::_storage.emplace_value(std::move(v)); }
  //! \brief Disposes of any existing state, setting the monad to a default value
  BOOST_OUTCOME_CONSTEXPR void set_value() { implementation_policy::base::_storage.emplace_value(value_type()); }
  //! \brief Disposes of any existing state, setting the monad to an emplaced construction
  template <class... Args> BOOST_OUTCOME_CONSTEXPR void emplace(Args &&... args) { implementation_policy::base::_storage.emplace_value(std::forward<Args>(args)...); }

  //! \brief Disposes of any existing state, setting the monad to the error_type
  BOOST_OUTCOME_CONSTEXPR void set_error(error_type v) { implementation_policy::base::_storage.emplace_error(std::move(v)); }

  //! \brief Disposes of any existing state, setting the monad to the exception_type
  BOOST_OUTCOME_CONSTEXPR void set_exception(exception_type v) { implementation_policy::base::_storage.emplace_exception(std::move(v)); }
  //! \brief Disposes of any existing state, setting the monad to make_exception_type(forward<E>(e))
  template <typename E, typename = typename std::enable_if<std::is_same<E, E>::value && has_exception_type>::type> BOOST_OUTCOME_CONSTEXPR void set_exception(E &&e) { set_exception(make_exception_type(std::forward<E>(e))); }

  //! \brief Swaps one monad for another
  BOOST_OUTCOME_CONSTEXPR void swap(basic_monad &o) noexcept(is_nothrow_move_constructible) { implementation_policy::base::_storage.swap(o._storage); }
  //! \brief Destructs any state stored, resetting to empty
  BOOST_OUTCOME_CONSTEXPR void clear() noexcept(is_nothrow_destructible) { implementation_policy::base::_storage.clear(); }

  // Accessor for underlying storage. Used by the comparison functions
  const value_storage_type &__storage() const noexcept { return this->_storage; }

#ifdef DOXYGEN_IS_IN_THE_HOUSE
//! \brief If contains a value_type, returns a lvalue reference to it, else throws an exception of monad_error(no_state), system_error or the exception_type.
//! \brief If contains a value_type, returns a const lvalue reference to it, else throws an exception of monad_error(no_state), system_error or the exception_type.
//! \brief If contains a value_type, returns a rvalue reference to it, else throws an exception of monad_error(no_state), system_error or the exception_type.
//! \brief If contains an error_type, returns that error_type. If contains an error, returns an error code of `monad_errc::exception_present`. Otherwise returns a null error_type. Can only throw the exception monad_error(no_state) if empty.
//! \brief If contains an exception_type, returns that exception_type. If contains an error_type, returns system_error(error_type). If contains a value_type, returns a null exception_type. Can only throw the exception monad_error(no_state) if empty.
#endif

#ifdef BOOST_OUTCOME_ENABLE_ADVANCED
/*! \name Functional programming extensions (optional)
\ingroup monad

\note All code in this section can be enabled by defining BOOST_OUTCOME_ENABLE_ADVANCED.
By default only next() is available. This prevents you writing code which impacts build times.

Classic monadic programming consists of a sequence of nested functional operations:
<dl>
  <dt>JOIN (single): outcome<outcome<T>>.get() -> outcome<T></dt>
  <dt>JOIN (maximum): outcome<outcome<outcome<outcome<T>>>>.unwrap() -> outcome<T></dt>
    <dd>Whatever is the first monad containing a non-monad is returned.</dd>
  <dt>MAP: outcome<T>.map(R(T)) -> outcome<R></dt>
    <dd>If callable maps T to R, map() maps a outcome<T> to a outcome<R> if outcome<T>
    contains a T. If it contains an error or is empty, that is passed through.</dd>
  <dt>BIND: outcome<T>.bind(outcome<R>(T)) -> outcome<R></dt>
  <dt>BIND: outcome<T>.bind(R(T)) -> outcome<R></dt>
    <dd>If callable maps T to outcome<R> and if outcome<T> contains a T, then bind() maps
    a outcome<T> to a outcome<R> else if callable maps T to R and if outcome<T> contains a T,
    bind() maps a outcome<T> to a outcome<R>. In other words, returning a monad from the
    callable does not wrap it in another monad. If the originating monad did not
    contain a T, that is passed through.</dd>
</dl>
We also support outcome<T>.next(R(outcome<T>)) for semantic equivalence to futures where the
callable is called with the originating monad. This
acts like bind(), so if the callable returns a monad it is not wrapped in another
monad. Unlike map() or bind(), next() always calls the callable no matter what the
monad contains, so it is up to you to interrogate the monad. Note that the originating
monad is passed by const lvalue ref unless the callable takes a rvalue ref to the monad.

A quick use example:
\snippet monad_example.cpp monad_bind_example
\snippet unittests.cpp monad_match_example
\snippet unittests.cpp monad_operators_example

You will note in the code example that the type of the callable for bind() and map()
determines what operation happens. Here are the rules:
- If the monad contains a T and the callable takes a T or an `auto`, then:
  - If the callable takes a T or any reference to a T which isn't an rvalue reference,
  the T is passed by const lvalue reference (i.e. copy semantics).
  - If the callable takes a T by non-const rvalue reference, the T is passed by rvalue ref.
  This lets you move from the value held by the originating monad if so desired.
  - If the callable takes the originating monad or any reference to such which isn't a
  rvalue reference, then the originating monad is passed by const lvalue reference.
  - If the callable takes the originating monad by non-const rvalue reference, the
  originating monad is passed by rvalue reference.
The ability to take the originating monad makes bind() identical to next() though much
harder on build times. Note that these options let you rebind the type of the monad,
so if your callable returns a different type from the originating monad then the resulting
monad is based on that different return type.
\warning The current implementation requires you to specify a non-dependent return
type for all generic lambdas, else you'll get compile errors where the compiler tried
to insert `error_type`, `exception_type` etc when it was trying to figure out if the
return type is correct. A future implementation (once VS2015 has Expression SFINAE) may
remove this restriction, until then just hard specify your return types if your lambdas
take an `auto`, or use lambdas not taking `auto`.

- If the monad contains an `error_type` and the callable takes an `error_type`, then
call the callable, else pass through the monad. For this reason, any callable taking
an `error_type` must always return the same monad type as the originating monad.
- If the monad contains an `error_type` or an `exception_type` and the callable takes
an `exception_type`, then call the callable, else pass through the monad. For this reason,
any callable taking an `exception_type` must always return the same monad type as the
originating monad.
- If the monad is empty and the callable takes an `empty_type`, then call the callable,
else pass through the monad. For this reason, any callable with an `empty_type` parameter must
always return the same monad type as the originating monad.

Note that for nested monads e.g. outcome<outcome<int>>, either or both of the inner or outer
monads can be with value or with error or empty. You should have your binds and maps
work appropriately.

For maximum build performance, try to avoid bind() and map() as these use some hefty
metaprogramming to deduce what kind of bind and map you're doing based on the callables
passed. unwrap() is implemented using a recursively expanded structure which is probably
okay for low unwrap depths. next() is probably the least weighty of the monadic operators
as it's relatively dumb and the only metaprogramming is to determine whether to wrap
the return type with a monad or not.

### Acknowledgements ###
To T.C. on Stack Overflow for answering my question at https://stackoverflow.com/questions/30802404/how-to-detect-whether-some-callable-takes-a-rvalue-reference
and without whose excellent answer the intelligent map() and bind() above could not work.
*/
///@{
/*! \brief Return basic_monad(F(*this)) or F(*this) if the latter returns a monad.

The callable F needs to consume a monad obviously enough, however if your callable takes a monad &&, you can move
from the monad. Equally, you can avoid copies if your
callable takes a reference argument. The callable F can be a generic lambda if desired.

If your callable does not return a monad, a monad will be constructed to hold the type it does return
inheriting the same error_code, exception_type etc of the originating monad. If your callable returns
a monad, that monad can be of any template parameter configuration and it will be returned from next(). This
allows a very easy way of converting between different configurations of monad cost free.
*/
#ifdef DOXYGEN_IS_IN_THE_HOUSE
  template <class F> basic_monad<...> next(F &&f);
#else
  template <class _F> BOOST_OUTCOME_CONSTEXPR typename detail::do_next<typename traits::is_callable_is_well_formed<typename std::decay<_F>::type, basic_monad>::type, typename std::decay<_F>::type, implementation_policy>::output_type next(_F &&f)
  {
    typedef typename std::decay<_F>::type F;
    typedef traits::callable_argument_traits<F, basic_monad> f_traits;
    static_assert(f_traits::valid, "The callable passed to next() must take this monad type or a reference to it.");
    return detail::do_next<typename f_traits::return_type, F, implementation_policy>(std::forward<F>(f))(std::move(*this));
  }
#endif

//! \brief If I am a basic_monad<basic_monad<...>>, return copy of most nested basic_monad<...>, else return copy of *this
#ifdef DOXYGEN_IS_IN_THE_HOUSE
  basic_monad<...> unwrap() const &;
#else
  BOOST_OUTCOME_CONSTEXPR typename detail::do_unwrap<basic_monad>::output_type unwrap() const & { return detail::do_unwrap<basic_monad>()(*this); }
#endif
//! \brief If I am a basic_monad<basic_monad<...>>, return move of most nested basic_monad<...>, else return move of *this
#ifdef DOXYGEN_IS_IN_THE_HOUSE
  basic_monad<...> unwrap() &&;
#else
  BOOST_OUTCOME_CONSTEXPR typename detail::do_unwrap<basic_monad>::output_type unwrap() && { return detail::do_unwrap<basic_monad>()(std::move(*this)); }
#endif

//! \brief If bool(*this), return basic_monad(F(get())).unwrap, else return basic_monad<result_of<F(get())>>(error)
#ifdef DOXYGEN_IS_IN_THE_HOUSE
  template <class F> basic_monad<...> bind(F &&f);
#else
  template <class _F> BOOST_OUTCOME_CONSTEXPR typename detail::do_bind<typename detail::bind_map_parameter_validation<typename std::decay<_F>::type, basic_monad>::return_type, typename std::decay<_F>::type, basic_monad>::output_type bind(_F &&f)
  {
    typedef typename std::decay<_F>::type F;
    typedef detail::do_bind<typename detail::bind_map_parameter_validation<F, basic_monad>::return_type, F, basic_monad> impl;
    if(has_value())
      return impl(std::forward<F>(f))(std::move(implementation_policy::base::_storage.value), traits::detail::rank<5>());
    else if(has_error())
      return impl(std::forward<F>(f))(std::move(implementation_policy::base::_storage.error), traits::detail::rank<5>());
    else if(has_exception())
      return impl(std::forward<F>(f))(std::move(implementation_policy::base::_storage.exception), traits::detail::rank<5>());
    else
      return impl(std::forward<F>(f))(empty_type(), traits::detail::rank<5>());
  }
#endif
//! \brief If bool(*this), return basic_monad(F(get())).unwrap, else return basic_monad<result_of<F(get())>>(error)
#ifdef DOXYGEN_IS_IN_THE_HOUSE
  template <class F> basic_monad<...> operator>>(F &&f);
#else
  template <class _F> BOOST_OUTCOME_CONSTEXPR typename detail::do_bind<typename detail::bind_map_parameter_validation<typename std::decay<_F>::type, basic_monad>::return_type, typename std::decay<_F>::type, basic_monad>::output_type operator>>(_F &&f) { return bind(std::forward<_F>(f)); }
#endif

//! \brief If bool(*this), return basic_monad(F(get())), else return basic_monad<result_of<F(get())>>(error)
#ifdef DOXYGEN_IS_IN_THE_HOUSE
  template <class F> basic_monad<...> map(F &&f);
#else
  template <class _F> BOOST_OUTCOME_CONSTEXPR typename detail::do_map<typename detail::bind_map_parameter_validation<typename std::decay<_F>::type, basic_monad>::return_type, typename std::decay<_F>::type, basic_monad>::output_type map(_F &&f)
  {
    typedef typename std::decay<_F>::type F;
    typedef detail::do_map<typename detail::bind_map_parameter_validation<F, basic_monad>::return_type, F, basic_monad> impl;
    if(has_value())
      return impl(std::forward<F>(f))(std::move(implementation_policy::base::_storage.value), traits::detail::rank<5>());
    else if(has_error())
      return impl(std::forward<F>(f))(std::move(implementation_policy::base::_storage.error), traits::detail::rank<5>());
    else if(has_exception())
      return impl(std::forward<F>(f))(std::move(implementation_policy::base::_storage.exception), traits::detail::rank<5>());
    else
      return impl(std::forward<F>(f))(empty_type(), traits::detail::rank<5>());
  }
#endif

//! \brief Call callable F with the current contents of the monad. Whatever the callable returns for when it is called with value_type is the type of the resulting monad.
#ifdef DOXYGEN_IS_IN_THE_HOUSE
  template <class F> basic_monad(F(contents)).unwrap() match(F &&f);
#else
  template <class _F>
  BOOST_OUTCOME_CONSTEXPR typename detail::do_next<typename traits::is_callable_is_well_formed<typename std::decay<_F>::type, value_type>::type, typename traits::is_callable_is_well_formed<typename std::decay<_F>::type, value_type>::type(basic_monad &&), implementation_policy>::output_type match(_F &&f)
  {
    typedef typename std::decay<_F>::type F;
    typedef traits::callable_argument_traits<F, value_type> f_traits_value;
    static_assert(f_traits_value::valid, "Callable is not well formed when called with value_type");
    auto invoke_f = [
#ifdef __cpp_init_captures
    f = std::forward<F>(f)
#else
        f
#endif
    ](basic_monad &&m)
    {
      return f_traits_value::is_rvalue ? (m.has_value() ? f(std::move(m).get()) : m.has_error() ? f(std::move(m).get_error()) : m.has_exception() ? f(std::move(m).get_exception()) : f(empty_type())) :
                                         (m.has_value() ? f(m.get()) : m.has_error() ? f(m.get_error()) : m.has_exception() ? f(m.get_exception()) : f(empty_type()));
    };
    return next(std::move(invoke_f));
  }

  //! \brief If contains a value_type, invoke the call operator on that type. Return type must be default constructible.
  template <class... Args, typename = typename std::result_of<value_type(Args...)>::type> BOOST_OUTCOME_CONSTEXPR auto operator()(Args &&... args) -> decltype(this->get()(std::forward<Args>(args)...))
  {
    typedef decltype(this->get()(std::forward<Args>(args)...)) rettype;
    return has_value() ? this->get()(std::forward<Args>(args)...) : rettype();
  }

  //! \brief If contains a value_type, return that value type, else return the supplied type
  template <class U, typename = typename std::enable_if<std::is_constructible<basic_monad, U>::value>::type> BOOST_OUTCOME_CONSTEXPR basic_monad operator|(U &&v) & { return has_value() ? *this : basic_monad(std::forward<U>(v)); }
  //! \brief If contains a value_type, return that value type, else return the supplied type
  template <class U, typename = typename std::enable_if<std::is_constructible<basic_monad, U>::value>::type> BOOST_OUTCOME_CONSTEXPR basic_monad operator|(U &&v) const & { return has_value() ? *this : basic_monad(std::forward<U>(v)); }
  //! \brief If contains a value_type, return that value type, else return the supplied type
  template <class U, typename = typename std::enable_if<std::is_constructible<basic_monad, U>::value>::type> BOOST_OUTCOME_CONSTEXPR basic_monad operator|(U &&v) && { return has_value() ? std::move(*this) : basic_monad(std::forward<U>(v)); }
  //! \brief If contains a value_type, return the supplied type else the value_type
  template <class U, typename = typename std::enable_if<std::is_constructible<basic_monad, U>::value>::type> BOOST_OUTCOME_CONSTEXPR basic_monad operator&(U &&v) & { return has_value() ? basic_monad(std::forward<U>(v)) : *this; }
  //! \brief If contains a value_type, return the supplied type else the value_type
  template <class U, typename = typename std::enable_if<std::is_constructible<basic_monad, U>::value>::type> BOOST_OUTCOME_CONSTEXPR basic_monad operator&(U &&v) const & { return has_value() ? basic_monad(std::forward<U>(v)) : *this; }
  //! \brief If contains a value_type, return the supplied type else the value_type
  template <class U, typename = typename std::enable_if<std::is_constructible<basic_monad, U>::value>::type> BOOST_OUTCOME_CONSTEXPR basic_monad operator&(U &&v) && { return has_value() ? basic_monad(std::forward<U>(v)) : std::move(*this); }


#endif
///@}
#endif
};
//! \brief True if this monad exactly equals the other monad
template <class Policy1, class Policy2> constexpr inline typename std::enable_if<basic_monad<Policy1>::template _is_comparable<basic_monad<Policy2>>::value, bool>::type operator==(const basic_monad<Policy1> &a, const basic_monad<Policy2> &b)
{
  return a.__storage() == b.__storage();
}
//! \brief True if this monad exactly equals the other monad (associative)
template <class Policy1, class Policy2> constexpr inline typename std::enable_if<!basic_monad<Policy1>::template _is_comparable<basic_monad<Policy2>>::value && basic_monad<Policy2>::template _is_comparable<basic_monad<Policy1>>::value, bool>::type operator==(const basic_monad<Policy1> &a, const basic_monad<Policy2> &b)
{
  return b.__storage() == a.__storage();
}
//! \brief True if this monad does not exactly equal the other monad
template <class Policy1, class Policy2> constexpr inline typename std::enable_if<basic_monad<Policy1>::template _is_comparable<basic_monad<Policy2>>::value, bool>::type operator!=(const basic_monad<Policy1> &a, const basic_monad<Policy2> &b)
{
  return a.__storage() != b.__storage();
}
//! \brief True if this monad does not exactly equal the other monad (associative)
template <class Policy1, class Policy2> constexpr inline typename std::enable_if<!basic_monad<Policy1>::template _is_comparable<basic_monad<Policy2>>::value && basic_monad<Policy2>::template _is_comparable<basic_monad<Policy1>>::value, bool>::type operator!=(const basic_monad<Policy1> &a, const basic_monad<Policy2> &b)
{
  return b.__storage() != a.__storage();
}

namespace policy
{
  /*! \struct basic_monad_storage
  \brief A basic_monad storage policy which defines how the basic_monad is represented in memory.

  The struct is at the base of the inheritance hierarchy, and simply keeps some storage for the monad.
  */
  template <class _implementation_policy> struct basic_monad_storage
  {
    template <class P> friend struct basic_monad_storage;

  protected:
    typedef _implementation_policy implementation_policy;
    typedef value_storage<typename implementation_policy::value_type, typename implementation_policy::error_type, typename implementation_policy::exception_type> value_storage_type;
    value_storage_type _storage;

  public:
    //! \brief The final implementation type
    typedef typename implementation_policy::implementation_type implementation_type;
    //! \brief The type potentially held by the monad
    typedef typename value_storage_type::value_type value_type;
    //! \brief The error code potentially held by the monad
    typedef typename value_storage_type::error_type error_type;
    //! \brief The exception ptr potentially held by the monad
    typedef typename value_storage_type::exception_type exception_type;

    constexpr basic_monad_storage() = default;
    constexpr basic_monad_storage(const basic_monad_storage &) = default;
    constexpr basic_monad_storage(basic_monad_storage &&) = default;
    BOOST_OUTCOME_CONSTEXPR basic_monad_storage &operator=(const basic_monad_storage &) = default;
    BOOST_OUTCOME_CONSTEXPR basic_monad_storage &operator=(basic_monad_storage &&) = default;
    template <class Policy>
    constexpr basic_monad_storage(detail::tagged_valueless<basic_monad<Policy>> &&o)
        : _storage(typename value_storage_type::valueless_t(), std::move(o.value._storage))
    {
    }
    template <class Policy>
    constexpr basic_monad_storage(basic_monad_storage<Policy> &&o)
        : _storage(std::move(o._storage))
    {
    }
    template <class Policy>
    constexpr basic_monad_storage(const basic_monad_storage<Policy> &o)
        : _storage(o._storage)
    {
    }
    constexpr explicit basic_monad_storage(value_storage_type &&v)
        : _storage(std::move(v))
    {
    }
    constexpr basic_monad_storage(empty_t _)
        : _storage(_)
    {
    }
    constexpr basic_monad_storage(value_t _)
        : _storage(_)
    {
    }
    constexpr basic_monad_storage(error_t _)
        : _storage(_)
    {
    }
    constexpr basic_monad_storage(exception_t _)
        : _storage(_)
    {
    }
    constexpr basic_monad_storage(const value_type &v)
        : _storage(v)
    {
    }
    constexpr basic_monad_storage(value_type &&v)
        : _storage(std::move(v))
    {
    }
    constexpr basic_monad_storage(const error_type &v)
        : _storage(v)
    {
    }
    constexpr basic_monad_storage(error_type &&v)
        : _storage(std::move(v))
    {
    }
    constexpr basic_monad_storage(const exception_type &v)
        : _storage(v)
    {
    }
    constexpr basic_monad_storage(exception_type &&v)
        : _storage(std::move(v))
    {
    }
    template <class... Args>
    constexpr basic_monad_storage(typename value_storage_type::emplace_t _, Args &&... args)
        : _storage(_, std::forward<Args>(args)...)
    {
    }

    constexpr bool is_ready() const noexcept { return _storage.type != value_storage_type::storage_type::empty; }
    constexpr bool empty() const noexcept { return _storage.type == value_storage_type::storage_type::empty; }
    constexpr bool has_value() const noexcept { return _storage.type == value_storage_type::storage_type::value; }
    constexpr bool has_error() const noexcept { return _storage.type == value_storage_type::storage_type::error; }
    constexpr bool has_exception(bool only_exception = false) const noexcept { return _storage.type == value_storage_type::storage_type::exception || (!only_exception && _storage.type == value_storage_type::storage_type::error); }
  };
  template <bool enable, class T> struct move_if
  {
    template <class U> constexpr typename std::remove_reference<U>::type &&operator()(U &&v) const { return static_cast<typename std::remove_reference<U>::type &&>(v); }
  };
  template <class T> struct move_if<false, T>
  {
    constexpr T operator()(T v) const { return v; }
  };
}
//! \brief Contains the basic_monad policy definitions
namespace policy
{
}

#define BOOST_OUTCOME_MONAD_NAME monad
#define BOOST_OUTCOME_MONAD_POLICY_ERROR_TYPE error_code_extended
#define BOOST_OUTCOME_MONAD_POLICY_EXCEPTION_TYPE std::exception_ptr
#include "detail/monad_policy.ipp"
#define BOOST_OUTCOME_MONAD_NAME result
#define BOOST_OUTCOME_MONAD_POLICY_ERROR_TYPE error_code_extended
#include "detail/monad_policy.ipp"
#define BOOST_OUTCOME_MONAD_NAME option
#include "detail/monad_policy.ipp"

/*! \brief `outcome<R>` can hold a fixed variant list of empty, a type `R`, a lightweight `std::error_code` or a
heavier `std::exception_ptr` at a space cost of `max(24, sizeof(R)+8)`. This corresponds to `tribool::unknown`,
`tribool::true_`, `tribool::false_` and `tribool::false_` respectively. \ingroup monad
*/
#ifdef DOXYGEN_IS_IN_THE_HOUSE
template <typename R> class outcome : public basic_monad<policy::monad_policy_base<policy::basic_monad_storage<policy::monad_policy<R>>, R, error_code_extended, std::exception_ptr>>
{
#define BOOST_OUTCOME_BASIC_MONAD_NAME outcome
#include "detail/basic_monad.ipp"
};
#else
template <typename R> using outcome = basic_monad<policy::monad_policy<R>>;
#endif
//! \brief Makes an outcome from the type passed \ingroup monad
template <class T> constexpr inline outcome<T> make_outcome(T &&v)
{
  return outcome<T>(std::move(v));
}
//! \brief Makes an outcome from the type passed \ingroup monad
template <class T> constexpr inline outcome<T> make_outcome(const T &v)
{
  return outcome<T>(v);
}
//! \brief Makes an errored outcome of type T \ingroup monad
template <class T = void> inline outcome<T> make_outcome(error_code_extended v)
{
  return outcome<T>(std::move(v));
}
//! \brief Makes an errored outcome of type T \ingroup monad
template <class T = void> inline outcome<T> make_outcome(std::error_code v)
{
  return outcome<T>(error_code_extended(std::move(v)));
}
//! \brief Makes an excepted outcome of type T \ingroup monad
template <class T = void> inline outcome<T> make_outcome(std::exception_ptr v)
{
  return outcome<T>(std::move(v));
}
//! \brief Makes an empty outcome of type T \ingroup monad
template <class T = void> constexpr inline outcome<T> make_outcome()
{
  return outcome<T>();
}
//! \brief Makes an empty outcome of type T \ingroup monad
template <class T = void> constexpr inline outcome<T> make_empty_outcome()
{
  return outcome<T>();
}
//! \brief Make an outcome from the type passed \ingroup monad
template <class T> constexpr inline outcome<T> make_valued_outcome(T &&v)
{
  return outcome<T>(std::move(v));
}
//! \brief Make an outcome from the type passed \ingroup monad
template <class T> constexpr inline outcome<T> make_valued_outcome(const T &v)
{
  return outcome<T>(v);
}
//! \brief Make an outcome from the type passed \ingroup monad
template <class T = void> constexpr inline outcome<T> make_valued_outcome()
{
  static_assert(!std::is_same<T, T>::value, "Empty make_valued_outcome<T> not specialised");
  return outcome<T>();
}
template <> inline outcome<void> make_valued_outcome<void>()
{
  return outcome<void>(value);
}
//! \brief Make an errored outcome from the type passed \ingroup monad
template <class T = void> inline outcome<T> make_errored_outcome(error_code_extended v)
{
  return outcome<T>(std::move(v));
}
//! \brief Make an errored outcome from the type passed \ingroup monad
template <class T = void> inline outcome<T> make_errored_outcome(std::error_code v)
{
  return outcome<T>(error_code_extended(std::move(v)));
}
/*! \brief Make an errored outcome from the type passed \ingroup monad
\note This makes an error code in generic category matching the error condition.
It does NOT preserve the "semantic equivalence" of error conditions during comparisons,
if you want that then test `.error()` against the `default_error_condition()` of the
error code. This overload is purely to save you typing `make_error_code()` around every
time you use `errc::something`.
*/
template <class T = void, class ErrorCondEnum, typename = typename std::enable_if<stl11::is_error_condition_enum<ErrorCondEnum>::value>::type> inline outcome<T> make_errored_outcome(ErrorCondEnum v)
{
  return outcome<T>(error_code_extended(make_error_code(v)));
}
//! \brief Make a generic errored outcome from the errno passed \ingroup monad
template <class T = void> inline outcome<T> make_errored_outcome(int e, const char *extended = nullptr)
{
  return outcome<T>(error_code_extended(e, deatomiced_categories::generic_category(), extended));
}
#if defined(_WIN32) || defined(DOXYGEN_IS_IN_THE_HOUSE)
//! \brief Make a system errored outcome from the code passed \ingroup monad
template <class T = void> constexpr inline outcome<T> make_errored_outcome(unsigned long e, const char *extended = nullptr)
{
  return outcome<T>(error_code_extended(e, deatomiced_categories::system_category(), extended));
}
#endif
//! \brief Make an excepted outcome from the type passed \ingroup monad
template <class T = void> inline outcome<T> make_exceptional_outcome(std::exception_ptr v = std::current_exception())
{
  return outcome<T>(std::move(v));
}

/*! \brief `result<R>` can hold a fixed variant list of empty, a type `R` or a lightweight `std::error_code` at a
space cost of `max(24, sizeof(R)+8)`. This corresponds to `tribool::unknown`, `tribool::true_` and
`tribool::false_` respectively. This specialisation looks deliberately like Rust's `Result<T>`. \ingroup monad
*/
#ifdef DOXYGEN_IS_IN_THE_HOUSE
template <typename R> class result : public basic_monad<policy::result_policy_base<policy::basic_monad_storage<policy::result_policy<R>>, R, error_code_extended>>
{
#define BOOST_OUTCOME_BASIC_MONAD_NAME result
#include "detail/basic_monad.ipp"
};
#else
template <typename R> using result = basic_monad<policy::result_policy<R>>;
#endif
//! \brief Makes a result from the type passed \ingroup monad
template <class T> constexpr inline result<T> make_result(T &&v)
{
  return result<T>(std::move(v));
}
//! \brief Makes a result from the type passed \ingroup monad
template <class T> constexpr inline result<T> make_result(const T &v)
{
  return result<T>(v);
}
//! \brief Makes an errored result of type T \ingroup monad
template <class T = void> inline result<T> make_result(error_code_extended v)
{
  return result<T>(std::move(v));
}
//! \brief Makes an errored result of type T \ingroup monad
template <class T = void> inline result<T> make_result(std::error_code v)
{
  return result<T>(error_code_extended(std::move(v)));
}
//! \brief Makes an empty result of type T \ingroup monad
template <class T = void> constexpr inline result<T> make_result()
{
  return result<T>();
}
//! \brief Makes an empty result of type T \ingroup monad
template <class T = void> constexpr inline result<T> make_empty_result()
{
  return result<T>();
}
//! \brief Makes a result from the type passed \ingroup monad
template <class T> constexpr inline result<T> make_valued_result(T &&v)
{
  return result<T>(std::move(v));
}
//! \brief Makes a result from the type passed \ingroup monad
template <class T> constexpr inline result<T> make_valued_result(const T &v)
{
  return result<T>(v);
}
//! \brief Makes a result from the type passed \ingroup monad
template <class T = void> constexpr inline result<T> make_valued_result()
{
  static_assert(!std::is_same<T, T>::value, "Empty make_valued_result<T> not specialised");
  return result<T>();
}
template <> inline result<void> make_valued_result<void>()
{
  return result<void>(value);
}
//! \brief Make an errored result from the type passed \ingroup monad
template <class T = void> inline result<T> make_errored_result(error_code_extended v)
{
  return result<T>(std::move(v));
}
//! \brief Make an errored result from the type passed \ingroup monad
template <class T = void> inline result<T> make_errored_result(std::error_code v)
{
  return result<T>(error_code_extended(std::move(v)));
}
/*! \brief Make an errored result from the type passed \ingroup monad
\note This makes an error code in generic category matching the error condition.
It does NOT preserve the "semantic equivalence" of error conditions during comparisons,
if you want that then test `.error()` against the `default_error_condition()` of the
error code. This overload is purely to save you typing `make_error_code()` around every
time you use `errc::something`.
*/
template <class T = void, class ErrorCondEnum, typename = typename std::enable_if<stl11::is_error_condition_enum<ErrorCondEnum>::value>::type> inline result<T> make_errored_result(ErrorCondEnum v)
{
  return result<T>(error_code_extended(make_error_code(v)));
}
//! \brief Make a generic errored outcome from the errno passed \ingroup monad
template <class T = void> constexpr inline result<T> make_errored_result(int e, const char *extended = nullptr)
{
  return result<T>(error_code_extended(e, deatomiced_categories::generic_category(), extended));
}
#if defined(_WIN32) || defined(DOXYGEN_IS_IN_THE_HOUSE)
//! \brief Make a system errored outcome from the code passed \ingroup monad
template <class T = void> constexpr inline result<T> make_errored_result(unsigned long e, const char *extended = nullptr)
{
  return result<T>(error_code_extended(e, deatomiced_categories::system_category(), extended));
}
#endif

/*! \brief `option<R>` can hold a fixed variant list of empty or a type `R` at a space cost of `sizeof(value_storage<R>)`
which is usually `sizeof(R)+8`, but may be smaller if `value_storage<R>` is specialised. This
corresponds to `tribool::unknown` and `tribool::true_` respectively. This specialisation looks deliberately
like Rust's `Option<T>`. \ingroup monad
*/
#ifdef DOXYGEN_IS_IN_THE_HOUSE
template <typename R> class option : public basic_monad<policy::option_policy_base<policy::basic_monad_storage<policy::option_policy<R>>, R>>
{
#define BOOST_OUTCOME_BASIC_MONAD_NAME option
#include "detail/basic_monad.ipp"
};
#else
template <typename R> using option = basic_monad<policy::option_policy<R>>;
#endif
//! \brief Makes a option from the type passed \ingroup monad
template <class T> constexpr inline option<T> make_option(T &&v)
{
  return option<T>(std::move(v));
}
//! \brief Makes a option from the type passed \ingroup monad
template <class T> constexpr inline option<T> make_option(const T &v)
{
  return option<T>(v);
}
//! \brief Makes an empty option of type T \ingroup monad
template <class T = void> constexpr inline option<T> make_option()
{
  return option<T>();
}
//! \brief Makes an empty option of type T \ingroup monad
template <class T = void> constexpr inline option<T> make_empty_option()
{
  return option<T>();
}
//! \brief Makes a option from the type passed \ingroup monad
template <class T> constexpr inline option<T> make_valued_option(T &&v)
{
  return option<T>(std::move(v));
}
//! \brief Makes a option from the type passed \ingroup monad
template <class T> constexpr inline option<T> make_valued_option(const T &v)
{
  return option<T>(v);
}
//! \brief Makes a option from the type passed \ingroup monad
template <class T = void> constexpr inline option<T> make_valued_option()
{
  static_assert(!std::is_same<T, T>::value, "Empty make_valued_option<T> not specialised");
  return option<T>();
}
template <> constexpr inline option<void> make_valued_option<void>()
{
  return option<void>(value);
}


//! \brief Makes an outcome from a result \ingroup monad
template <class T> constexpr inline outcome<T> as_outcome(result<T> &&v)
{
  return outcome<T>(std::move(v));
}
//! \brief Makes an outcome from a result \ingroup monad
template <class T> constexpr inline outcome<T> as_outcome(const result<T> &v)
{
  return outcome<T>(v);
}
//! \brief Makes an outcome from an option \ingroup monad
template <class T> constexpr inline outcome<T> as_outcome(option<T> &&v)
{
  return outcome<T>(std::move(v));
}
//! \brief Makes an outcome from an option \ingroup monad
template <class T> constexpr inline outcome<T> as_outcome(const option<T> &v)
{
  return outcome<T>(v);
}
//! \brief Makes a result from an option \ingroup monad
template <class T> constexpr inline result<T> as_result(option<T> &&v)
{
  return result<T>(std::move(v));
}
//! \brief Makes a result from an option \ingroup monad
template <class T> constexpr inline result<T> as_result(const option<T> &v)
{
  return result<T>(v);
}

//! \brief Makes a void outcome from an input outcome, forwarding any emptiness, error or exception \ingroup monad
template <class T> inline outcome<void> as_void(const outcome<T> &v)
{
  if(v.has_exception())
    return v.get_exception();
  if(v.has_error())
    return v.get_error();
  if(v.has_value())
    return make_valued_outcome<void>();
  return make_empty_outcome<void>();
}
//! \brief Makes a void result from an input result, forwarding any emptiness or error \ingroup monad
template <class T> inline result<void> as_void(const result<T> &v)
{
  if(v.has_error())
    return v.get_error();
  if(v.has_value())
    return make_valued_result<void>();
  return make_empty_result<void>();
}
//! \brief Makes a void option from an input option, forwarding any emptiness \ingroup monad
template <class T> BOOSTLITE_CONSTEXPR inline option<void> as_void(const option<T> &v)
{
  if(v.has_value())
    return make_valued_option<void>();
  return make_empty_option<void>();
}


#ifndef BOOST_OUTCOME_LEAN_AND_MEAN
/********************************************************** LEWG Expected implementation  ***********************************************************/

/*! \defgroup expected Implementation of LEWG proposed expected<T, E>

For your convenience, Outcome implements the LEWG Expected proposal as per
http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0323r1.pdf.

See https://ned14.github.io/boost.outcome/md_doc_md_08-expectedsynopsis.html for detail.
*/

#ifndef BOOST_OUTCOME_EXPECTED_DEFAULT_ERROR_TYPE
//! \brief Predefine to change the default error type for expected to something else. Defaults to `std::error_code`.
#define BOOST_OUTCOME_EXPECTED_DEFAULT_ERROR_TYPE std::error_code
#endif

/*! \class bad_expected_access_base
\ingroup expected
\brief The base exception type thrown when you try to access an errored expected
*/
class bad_expected_access_base : public std::logic_error
{
public:
  //! \brief The type of error
  using error_type = void;
  //! \brief Constructs an instance
  bad_expected_access_base(const char *what)
      : std::logic_error(what)
  {
  }
};

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4814)
#endif
/*! \class bad_expected_access
\ingroup expected
\brief The exception type thrown when you try to access an errored expected
*/
template <class E = BOOST_OUTCOME_EXPECTED_DEFAULT_ERROR_TYPE> class bad_expected_access : public bad_expected_access_base
{
  E _error;

public:
  //! \brief The type of error
  using error_type = E;
  //! \brief Constructs an instance taking a copy
  explicit bad_expected_access(const error_type &e) noexcept : bad_expected_access_base("Bad expected access of value when error was present"), _error(e) {}
  //! \brief Returns the error
  const error_type &error() const &noexcept { return _error; }
  //! \brief Returns the error
  error_type &error() & noexcept { return _error; }
  //! \brief Returns the error
  const error_type &&error() const &&noexcept { return _error; }
  //! \brief Returns the error
  error_type &&error() && noexcept { return _error; }
};
//! \brief Type thrown due to valueless by exception state
template <> class bad_expected_access<void> : public bad_expected_access_base
{
public:
  //! \brief The type of error
  using error_type = void;
  //! \brief Constructs an instance
  explicit bad_expected_access() noexcept : bad_expected_access_base("Bad expected access of value when valueless due to exception") {}
};
template <class E> inline bad_expected_access<E> make_bad_expected_access(const E &v) noexcept
{
  return bad_expected_access<E>(v);
}
inline bad_expected_access<void> make_bad_expected_access() noexcept
{
  return bad_expected_access<void>();
}
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include "detail/expected_policy.ipp"

/*! \brief `expected<R>` can hold a fixed variant list of empty, a type `R` or a lightweight `std::error_code` at a
space cost of `max(24, sizeof(R)+8)`. This corresponds to `tribool::unknown`, `tribool::true_` and
`tribool::false_` respectively. This specialisation matches the proposed Expected implementation before standards. \ingroup expected
*/
#ifdef DOXYGEN_IS_IN_THE_HOUSE
template <typename R, typename E = BOOST_OUTCOME_EXPECTED_DEFAULT_ERROR_TYPE> class expected : public basic_monad<policy::expected_policy_base<policy::basic_monad_storage<policy::expected_policy<R, E>>, R, E>>
{
#define BOOST_OUTCOME_BASIC_MONAD_NAME expected
#include "detail/basic_monad.ipp"
};
#else
template <typename R, typename E = BOOST_OUTCOME_EXPECTED_DEFAULT_ERROR_TYPE> using expected = basic_monad<policy::expected_policy<R, E>>;
#endif
//! \brief Type sugar to indicate type E is an unexpected value \ingroup expected
template <typename E> using unexpected_type = basic_monad<policy::expected_policy<void, E>>;
//! \brief Tag type for unexpected \ingroup expected
using unexpect_t = error_t;
//! \brief Tag value for unexpected \ingroup expected
constexpr unexpect_t unexpect = unexpect_t();


//! \brief Makes an expected<void> \ingroup expected
inline expected<void> make_expected()
{
  return expected<void>();
}
//! \brief Makes an expected from the type passed \ingroup expected
template <class T, typename E = BOOST_OUTCOME_EXPECTED_DEFAULT_ERROR_TYPE> constexpr inline expected<T, E> make_expected(T &&v)
{
  return expected<T, E>(std::move(v));
}
//! \brief Makes an expected from the type passed \ingroup expected
template <class T, typename E = BOOST_OUTCOME_EXPECTED_DEFAULT_ERROR_TYPE> constexpr inline expected<T, E> make_expected(const T &v)
{
  return expected<T, E>(v);
}
//! \brief Makes an unexpected from the type passed \ingroup expected
template <class E> constexpr inline unexpected_type<typename std::decay<E>::type> make_unexpected(E &&v)
{
  return unexpected_type<typename std::decay<E>::type>(std::move(v));
}
//! \brief Makes an unexpected from the type passed \ingroup expected
template <class E> constexpr inline unexpected_type<E> make_unexpected(const E &v)
{
  return unexpected_type<E>(v);
}
//! \brief Make an errored expected from the type passed \ingroup expected
template <class T, class E> constexpr inline expected<T, E> make_expected_from_error(E &&v)
{
  return expected<T, E>(std::move(v));
}
//! \brief Make an errored expected from the type passed \ingroup expected
template <class T, class E> constexpr inline expected<T, E> make_expected_from_error(const E &v)
{
  return expected<T, E>(v);
}
//! \brief Make an errored expected from the type passed \ingroup expected
template <class T, class E, class U, typename = typename std::enable_if<!std::is_same<E, U>::value && std::is_constructible<E, U>::value>::type> constexpr inline expected<T, E> make_expected_from_error(U &&v)
{
  return expected<T, E>(std::forward<U>(v));
}
// Not implementing this as I think it redundant and highly likely to disappear from the next P-paper
// template <class F> constexpr expected<typename result_type<F>::type> make_expected_from_call(F f);


//! \brief Makes a void expected from an input expected, forwarding any emptiness or error \ingroup expected
template <class T, class E> inline expected<void, E> as_void(const expected<T, E> &v)
{
  if(v.has_error())
    return expected<void, E>(v.get_error());
  if(v.has_value())
    return expected<void, E>();
  return expected<void, E>(empty);
}

/********************************************************** LEWG Expected implementation  ***********************************************************/
#endif  // BOOST_OUTCOME_LEAN_AND_MEAN

BOOST_OUTCOME_V1_NAMESPACE_END

namespace std
{
  //! \brief Specialise swap for basic_monad \ingroup monad
  template <class Impl> inline void swap(BOOST_OUTCOME_V1_NAMESPACE::basic_monad<Impl> &a, BOOST_OUTCOME_V1_NAMESPACE::basic_monad<Impl> &b) { a.swap(b); }
}

#define BOOST_OUTCOME__GLUE2(x, y) x##y
#define BOOST_OUTCOME__GLUE(x, y) BOOST_OUTCOME__GLUE2(x, y)
#define BOOST_OUTCOME_UNIQUE_NAME BOOST_OUTCOME__GLUE(__t, __COUNTER__)
//#define BOOST_OUTCOME_UNIQUE_NAME __t

#define BOOST_OUTCOME_TRYV2(unique, m)                                                                                                                                                                                                                                                                                         \
  auto &&unique = (m);                                                                                                                                                                                                                                                                                                         \
  if(!unique.has_value())                                                                                                                                                                                                                                                                                                      \
    return BOOST_OUTCOME_V1_NAMESPACE::detail::tag_valueless(BOOST_OUTCOME_V1_NAMESPACE::as_void(unique));
#define BOOST_OUTCOME_TRY2(unique, v, m)                                                                                                                                                                                                                                                                                       \
  BOOST_OUTCOME_TRYV2(unique, m);                                                                                                                                                                                                                                                                                              \
  auto v(std::move(std::move(unique).get()))

/*! \brief If the monad returned by expression \em m is empty, erroneous or excepted, propagate that by immediately returning a void immediately
\ingroup macro_helpers
*/
#ifdef DOXYGEN_IS_IN_THE_HOUSE
#define BOOST_OUTCOME_TRYV(m) ...
#else
#define BOOST_OUTCOME_TRYV(m) BOOST_OUTCOME_TRYV2(BOOST_OUTCOME_UNIQUE_NAME, m)
#endif

#if defined(DOXYGEN_IS_IN_THE_HOUSE) || defined(__GNUC__) || defined(__clang__)

/*! \brief If the monad returned by expression \em m is empty, erroneous or excepted, propagate that by immediately returning a void immediately, else become the unwrapped value as an expression. This makes `BOOST_OUTCOME_TRYX(expr)` an expression which can be used exactly like the `try` operator in other languages.

\note This macro makes use of a proprietary extension in GCC and clang and is not portable. The macro is not made available on unsupported compilers,
so you can test for its presence using `#ifdef BOOST_OUTCOME_TRYX`.
\ingroup macro_helpers
*/
#ifdef DOXYGEN_IS_IN_THE_HOUSE
#define BOOST_OUTCOME_TRYX(m) ...
#else
#define BOOST_OUTCOME_TRYX(m)                                                                                                                                                                                                                                                                                                  \
  ({                                                                                                                                                                                                                                                                                                                           \
                                                                                                                                                                                                                                                                                                                               \
    auto &&res = (m);                                                                                                                                                                                                                                                                                                          \
    if(!res.has_value())                                                                                                                                                                                                                                                                                                       \
      return BOOST_OUTCOME_V1_NAMESPACE::detail::tag_valueless(BOOST_OUTCOME_V1_NAMESPACE::as_void(res));                                                                                                                                                                                                                      \
    std::move(res.value());                                                                                                                                                                                                                                                                                                    \
  \
})
#endif
#endif

/*! \brief If the monad returned by expression \em m is empty, erroneous or excepted, propagate that by immediately returning a void immediately, else return the unwrapped value
\ingroup macro_helpers
*/
#ifdef DOXYGEN_IS_IN_THE_HOUSE
#define BOOST_OUTCOME_TRY(v, m) ...
#else
#define BOOST_OUTCOME_TRY(v, m) BOOST_OUTCOME_TRY2(BOOST_OUTCOME_UNIQUE_NAME, v, m)
#endif

/*! \brief A boilerplate sequence of `catch(exceptions...)` returning those exceptions as their equivalent `result<void>`
\ingroup macro_helpers
*/
#ifdef DOXYGEN_IS_IN_THE_HOUSE
#define BOOST_OUTCOME_CATCH_EXCEPTION_TO_RESULT ...
#else
#define BOOST_OUTCOME_CATCH_EXCEPTION_TO_RESULT                                                                                                                                                                                                                                                                                \
  \
catch(const std::invalid_argument &e)                                                                                                                                                                                                                                                                                          \
  {                                                                                                                                                                                                                                                                                                                            \
    return BOOST_OUTCOME_V1_NAMESPACE::detail::tag_valueless(BOOST_OUTCOME_V1_NAMESPACE::make_errored_result<void>(EINVAL, e.what()));                                                                                                                                                                                         \
  }                                                                                                                                                                                                                                                                                                                            \
  \
catch(const std::domain_error &e)                                                                                                                                                                                                                                                                                              \
  {                                                                                                                                                                                                                                                                                                                            \
    return BOOST_OUTCOME_V1_NAMESPACE::detail::tag_valueless(BOOST_OUTCOME_V1_NAMESPACE::make_errored_result<void>(EDOM, e.what()));                                                                                                                                                                                           \
  }                                                                                                                                                                                                                                                                                                                            \
  \
catch(const std::length_error &e)                                                                                                                                                                                                                                                                                              \
  {                                                                                                                                                                                                                                                                                                                            \
    return BOOST_OUTCOME_V1_NAMESPACE::detail::tag_valueless(BOOST_OUTCOME_V1_NAMESPACE::make_errored_result<void>(E2BIG, e.what()));                                                                                                                                                                                          \
  }                                                                                                                                                                                                                                                                                                                            \
  \
catch(const std::out_of_range &e)                                                                                                                                                                                                                                                                                              \
  {                                                                                                                                                                                                                                                                                                                            \
    return BOOST_OUTCOME_V1_NAMESPACE::detail::tag_valueless(BOOST_OUTCOME_V1_NAMESPACE::make_errored_result<void>(ERANGE, e.what()));                                                                                                                                                                                         \
  }                                                                                                                                                                                                                                                                                                                            \
  \
catch(const std::logic_error &e) /* base class for this group */                                                                                                                                                                                                                                                               \
  {                                                                                                                                                                                                                                                                                                                            \
    return BOOST_OUTCOME_V1_NAMESPACE::detail::tag_valueless(BOOST_OUTCOME_V1_NAMESPACE::make_errored_result<void>(EINVAL, e.what()));                                                                                                                                                                                         \
  }                                                                                                                                                                                                                                                                                                                            \
  \
\
catch(const std::system_error &e) /* also catches ios::failure */                                                                                                                                                                                                                                                              \
  {                                                                                                                                                                                                                                                                                                                            \
    return BOOST_OUTCOME_V1_NAMESPACE::detail::tag_valueless(BOOST_OUTCOME_V1_NAMESPACE::make_errored_result<void>(BOOST_OUTCOME_V1_NAMESPACE::error_code_extended(e.code(), e.what())));                                                                                                                                      \
  }                                                                                                                                                                                                                                                                                                                            \
  \
catch(const std::overflow_error &e)                                                                                                                                                                                                                                                                                            \
  {                                                                                                                                                                                                                                                                                                                            \
    return BOOST_OUTCOME_V1_NAMESPACE::detail::tag_valueless(BOOST_OUTCOME_V1_NAMESPACE::make_errored_result<void>(EOVERFLOW, e.what()));                                                                                                                                                                                      \
  }                                                                                                                                                                                                                                                                                                                            \
  \
catch(const std::range_error &e)                                                                                                                                                                                                                                                                                               \
  {                                                                                                                                                                                                                                                                                                                            \
    return BOOST_OUTCOME_V1_NAMESPACE::detail::tag_valueless(BOOST_OUTCOME_V1_NAMESPACE::make_errored_result<void>(ERANGE, e.what()));                                                                                                                                                                                         \
  }                                                                                                                                                                                                                                                                                                                            \
  \
catch(const std::runtime_error &e) /* base class for this group */                                                                                                                                                                                                                                                             \
  {                                                                                                                                                                                                                                                                                                                            \
    return BOOST_OUTCOME_V1_NAMESPACE::detail::tag_valueless(BOOST_OUTCOME_V1_NAMESPACE::make_errored_result<void>(EAGAIN, e.what()));                                                                                                                                                                                         \
  }                                                                                                                                                                                                                                                                                                                            \
  \
\
catch(const std::bad_alloc &e)                                                                                                                                                                                                                                                                                                 \
  {                                                                                                                                                                                                                                                                                                                            \
    return BOOST_OUTCOME_V1_NAMESPACE::detail::tag_valueless(BOOST_OUTCOME_V1_NAMESPACE::make_errored_result<void>(ENOMEM, e.what()));                                                                                                                                                                                         \
  }                                                                                                                                                                                                                                                                                                                            \
  \
catch(const std::exception &e)                                                                                                                                                                                                                                                                                                 \
  {                                                                                                                                                                                                                                                                                                                            \
    return BOOST_OUTCOME_V1_NAMESPACE::detail::tag_valueless(BOOST_OUTCOME_V1_NAMESPACE::make_errored_result<void>(EINVAL, e.what()));                                                                                                                                                                                         \
  }
#endif
/*! \brief A boilerplate sequence of `catch(exceptions...)` plus a catch all returning those exceptions as their equivalent `result<void>`
\ingroup macro_helpers
*/
#ifdef DOXYGEN_IS_IN_THE_HOUSE
#define BOOST_OUTCOME_CATCH_ALL_EXCEPTION_TO_RESULT ...
#else
#define BOOST_OUTCOME_CATCH_ALL_EXCEPTION_TO_RESULT                                                                                                                                                                                                                                                                            \
  BOOST_OUTCOME_CATCH_EXCEPTION_TO_RESULT                                                                                                                                                                                                                                                                                      \
  \
catch(...)                                                                                                                                                                                                                                                                                                                     \
  {                                                                                                                                                                                                                                                                                                                            \
    return BOOST_OUTCOME_V1_NAMESPACE::detail::tag_valueless(BOOST_OUTCOME_V1_NAMESPACE::make_errored_result<void>(EAGAIN, "unknown exception"));                                                                                                                                                                              \
  }
#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
#endif
