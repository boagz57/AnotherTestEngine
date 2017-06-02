/* Support code for BOOST_OUTCOME_ENABLE_ADVANCED
(C) 2015-2017 Niall Douglas <http://www.nedproductions.biz/> (5 commits)
File Created: Jan 2017


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

#ifndef BOOST_OUTCOME_ADVANCED_SUPPORT_H
#define BOOST_OUTCOME_ADVANCED_SUPPORT_H

#include "config.hpp"

#ifndef BOOST_OUTCOME_ENABLE_ADVANCED
#error This file should not be included without BOOST_OUTCOME_ENABLE_ADVANCED being defined
#endif

BOOST_OUTCOME_V1_NAMESPACE_EXPORT_BEGIN

namespace traits
{
  namespace detail
  {
    // Gets the return type of F(A), returning a not_well_formed type if not well formed
    template <class F, class A> struct get_return_type
    {
      struct not_well_formed
      {
      };
      template <class _F, class _A> static not_well_formed test(...);
      template <class _F, class _A, class = decltype(std::declval<_F>()(std::declval<_A>()))> static auto test(_F &&f) noexcept(noexcept(f(std::declval<_A>()))) -> decltype(f(std::declval<_A>()));
      using type = decltype(test<F, A>(std::declval<F>()));
      static constexpr bool is_noexcept = noexcept(test<F, A>(std::declval<F>()));
    };

    // Without Expression SFINAE (VS2015), I actually don't know of a better way :(
    template <class T, class Arg> class has_call_operator2
    {
      struct Fallback
      {
        int operator()(Arg);
      };
      struct Derived : T, Fallback
      {
      };

      template <typename U, U> struct Check;

      typedef char ArrayOfOne[1], ArrayOfTwo[2];

      template <typename U> static ArrayOfOne &func(Check<int Fallback::*, &U::operator()> *);
      template <typename U> static ArrayOfTwo &func(...);

    public:
      static constexpr bool value = sizeof(func<Derived>(0)) == 2;
    };
    template <bool enable, typename F, typename Arg> struct has_call_operator : public std::false_type
    {
    };
    template <typename F, typename Arg> struct has_call_operator<true, F, Arg> : public has_call_operator2<F, typename get_return_type<F, Arg>::type(Arg)>
    {
    };

    template <bool _is_const, bool _is_move, bool _is_lvalue, bool _is_auto, typename T = void> struct arg_form
    {
      static constexpr bool is_const = _is_const;
      static constexpr bool is_rvalue = _is_move;
      static constexpr bool is_lvalue = _is_lvalue;
      static constexpr bool is_auto = _is_auto;
      using non_auto_type = T;
    };

    template <int R> struct rank;
#ifndef DOXYGEN_IS_IN_THE_HOUSE
    template <int R> struct rank : rank<R - 1>
    {
      static_assert(R > 0, "");
    };
    template <> struct rank<0>
    {
    };
#endif

    template <bool is_class, bool is_const_well_formed, class F, class A> struct call_operator_argument_form
    {
    };
    template <class F, class A> struct call_operator_argument_form<true, true, F, A>
    {
      using return_type = typename get_return_type<F, A>::type;
      using arg_type = typename std::decay<A>::type;

      static arg_form<true, false, true, true> test(return_type (F::*)(const arg_type &), rank<1>);
      static arg_form<false, false, true, true> test(return_type (F::*)(arg_type &), rank<2>);
      static arg_form<false, true, false, true> test(return_type (F::*)(arg_type &&), rank<3>);
      static arg_form<false, false, false, true> test(return_type (F::*)(arg_type), rank<4>);
      static arg_form<true, false, true, true> test(return_type (F::*)(const arg_type &) const, rank<5>);
      static arg_form<false, false, true, true> test(return_type (F::*)(arg_type &) const, rank<6>);
      static arg_form<false, true, false, true> test(return_type (F::*)(arg_type &&) const, rank<7>);
      static arg_form<false, false, false, true> test(return_type (F::*)(arg_type) const, rank<8>);

      template <class T> static arg_form<false, false, false, false, T> test(return_type (F::*)(T), rank<9>);
      template <class T> static arg_form<false, false, true, false, T> test(return_type (F::*)(T &), rank<10>);
      template <class T> static arg_form<false, true, false, false, T> test(return_type (F::*)(T &&), rank<11>);
      template <class T> static arg_form<false, false, false, false, T> test(return_type (F::*)(T) const, rank<12>);
      template <class T> static arg_form<false, false, true, false, T> test(return_type (F::*)(T &) const, rank<13>);
      template <class T> static arg_form<false, true, false, false, T> test(return_type (F::*)(T &&) const, rank<14>);

      using result = decltype(test(&F::operator(), rank<15>()));

      static constexpr bool is_rvalue = result::is_rvalue;
      static constexpr bool is_lvalue = result::is_lvalue;
      static constexpr bool is_auto = result::is_auto;
      using type = typename result::non_auto_type;
      static constexpr bool is_const = result::is_auto ? result::is_const : std::is_const<type>::value;
    };
    template <class F, class A> struct call_operator_argument_form<true, false, F, A>
    {
      using return_type = typename get_return_type<F, A>::type;
      using arg_type = typename std::decay<A>::type;

      // static arg_form<true , false, true , true> test(return_type(F::*)(const arg_type&)      , rank<1>);
      static arg_form<false, false, true, true> test(return_type (F::*)(arg_type &), rank<2>);
      static arg_form<false, true, false, true> test(return_type (F::*)(arg_type &&), rank<3>);
      static arg_form<false, false, false, true> test(return_type (F::*)(arg_type), rank<4>);
      // static arg_form<true , false, true , true> test(return_type(F::*)(const arg_type&) const, rank<5>);
      static arg_form<false, false, true, true> test(return_type (F::*)(arg_type &) const, rank<6>);
      static arg_form<false, true, false, true> test(return_type (F::*)(arg_type &&) const, rank<7>);
      static arg_form<false, false, false, true> test(return_type (F::*)(arg_type) const, rank<8>);

      template <class T> static arg_form<false, false, false, false, T> test(return_type (F::*)(T), rank<9>);
      template <class T> static arg_form<false, false, true, false, T> test(return_type (F::*)(T &), rank<10>);
      template <class T> static arg_form<false, true, false, false, T> test(return_type (F::*)(T &&), rank<11>);
      template <class T> static arg_form<false, false, false, false, T> test(return_type (F::*)(T) const, rank<12>);
      template <class T> static arg_form<false, false, true, false, T> test(return_type (F::*)(T &) const, rank<13>);
      template <class T> static arg_form<false, true, false, false, T> test(return_type (F::*)(T &&) const, rank<14>);

      using result = decltype(test(&F::operator(), rank<15>()));

      static constexpr bool is_rvalue = result::is_rvalue;
      static constexpr bool is_lvalue = result::is_lvalue;
      static constexpr bool is_auto = result::is_auto;
      using type = typename result::non_auto_type;
      static constexpr bool is_const = result::is_auto ? result::is_const : std::is_const<type>::value;
    };

    template <bool is_function, bool is_const_well_formed, class F, class A> struct function_argument_form
    {
    };
    template <class F, class A> struct function_argument_form<true, true, F, A>
    {
      using return_type = typename get_return_type<F, A>::type;
      using arg_type = typename std::decay<A>::type;

      static arg_form<true, false, true, true> test(return_type (*)(const arg_type &), rank<1>);
      static arg_form<false, false, true, true> test(return_type (*)(arg_type &), rank<2>);
      static arg_form<false, true, false, true> test(return_type (*)(arg_type &&), rank<3>);
      static arg_form<false, false, false, true> test(return_type (*)(arg_type), rank<4>);

      template <class T> static arg_form<false, false, false, false, T> test(return_type (*)(T), rank<5>);
      template <class T> static arg_form<false, false, true, false, T> test(return_type (*)(T &), rank<6>);
      template <class T> static arg_form<false, true, false, false, T> test(return_type (*)(T &&), rank<7>);

      using result = decltype(test(F(), rank<10>()));

      static constexpr bool is_rvalue = result::is_rvalue;
      static constexpr bool is_lvalue = result::is_lvalue;
      static constexpr bool is_auto = result::is_auto;
      using type = typename result::non_auto_type;
      static constexpr bool is_const = result::is_auto ? result::is_const : std::is_const<type>::value;
    };
    template <class F, class A> struct function_argument_form<true, false, F, A>
    {
      using return_type = typename get_return_type<F, A>::type;
      using arg_type = typename std::decay<A>::type;

      // static arg_form<true , false, true , true> test(return_type(*)(const arg_type&)      , rank<1>);
      static arg_form<false, false, true, true> test(return_type (*)(arg_type &), rank<2>);
      static arg_form<false, true, false, true> test(return_type (*)(arg_type &&), rank<3>);
      static arg_form<false, false, false, true> test(return_type (*)(arg_type), rank<4>);

      template <class T> static arg_form<false, false, false, false, T> test(return_type (*)(T), rank<5>);
      template <class T> static arg_form<false, false, true, false, T> test(return_type (*)(T &), rank<6>);
      template <class T> static arg_form<false, true, false, false, T> test(return_type (*)(T &&), rank<7>);

      using result = decltype(test(F(), rank<10>()));

      static constexpr bool is_rvalue = result::is_rvalue;
      static constexpr bool is_lvalue = result::is_lvalue;
      static constexpr bool is_auto = result::is_auto;
      using type = typename result::non_auto_type;
      static constexpr bool is_const = result::is_auto ? result::is_const : std::is_const<type>::value;
    };
  }

  //! \brief Is the callable F called with Arg well formed?
  template <class F, class A> struct is_callable_is_well_formed
  {
    using return_type = detail::get_return_type<F, A>;
    //! \brief The type returned by the callable F when called with Arg
    using type = typename return_type::type;
    //! \brief Whether the call with Arg is well formed
    static constexpr bool value = !std::is_same<type, typename return_type::not_well_formed>::value;
    //! \brief Whether the call with Arg is noexcept
    static constexpr bool is_noexcept = return_type::is_noexcept;
  };

  //! \brief Is F a class type and does it have a call operator callable with Arg?
  template <typename F, typename Arg> struct has_call_operator : public detail::has_call_operator<std::is_class<F>::value, F, Arg>
  {
  };

  namespace detail
  {
    template <bool enable, class F, class A> struct callable_argument_traits
    {
      //! \brief Is the callable F called with Arg well formed?
      static constexpr bool valid = false;
      //! \brief Is the arg const?
      static constexpr bool is_const = false;
      //! \brief Is the arg a rvalue ref?
      static constexpr bool is_rvalue = false;
      //! \brief Is the arg a lvalue ref?
      static constexpr bool is_lvalue = false;
      //! \brief Is the arg a templated arg?
      static constexpr bool is_auto = false;
      //! \brief If the arg is not a templated arg, it is this type
      using type = void;
    };
    template <class F, class A>
    struct callable_argument_traits<true, F, A>
    : public std::conditional<!std::is_function<F>::value && has_call_operator<std::is_class<F>::value, F, A>::value, detail::call_operator_argument_form<true, is_callable_is_well_formed<F, const A>::value, F, A>, detail::function_argument_form<true, is_callable_is_well_formed<F, const A>::value, F, A>>::type
    {
      static constexpr bool valid = true;
    };
  }

  /*! \brief If callable F were to be called with A, tell me about the call.
  */
  template <class F, class A> struct callable_argument_traits : public detail::callable_argument_traits<is_callable_is_well_formed<F, A>::value, F, A>
  {
    //! The type returned by the callable when called with A
    using return_type = typename is_callable_is_well_formed<F, A>::type;
  };
}

namespace detail
{
  // Does the monad contain a monad?
  template <class> struct is_monad_monad;
  template <class Policy> struct is_monad_monad<basic_monad<Policy>>
  {
    static constexpr bool value = is_monad<typename basic_monad<Policy>::value_type>::value;
  };

  // Convert any input type into a lvalue ref
  template <class T> struct to_lvalue_ref : public std::add_lvalue_reference<typename std::decay<T>::type>
  {
  };
  // Call C with A either by rvalue or lvalue ref
  template <bool with_rvalue> struct do_invoke
  {
    template <class C, class A> BOOST_OUTCOME_CONSTEXPR auto operator()(C &&c, A &&a) -> decltype(c(static_cast<typename to_lvalue_ref<A>::type>(a))) { return c(static_cast<typename to_lvalue_ref<A>::type>(a)); }
  };
  template <> struct do_invoke<true>
  {
    template <class C, class A> BOOST_OUTCOME_CONSTEXPR auto operator()(C &&c, A &&a) -> decltype(c(std::move(a))) { return c(std::move(a)); }
  };
  /* Invokes the callable passed to next() folding any monad return type
  R is the type returned by the callable
  C is the callable
  Monad is the monad
  Policy is the implementation policy

  Call operator is always invoked with basic_monad.
  */
  // For when R is not a monad and not void
  template <class R, class C, template <class> class Monad, class Policy> struct do_simple_continuation
  {
    typedef typename std::decay<C>::type callable_type;
    // If the return type is an error_type or exception_type or void, reuse monad else rebind monad to R
    typedef typename std::conditional<std::is_same<R, typename Monad<Policy>::error_type>::value || std::is_same<R, typename Monad<Policy>::exception_type>::value || std::is_void<R>::value, Monad<Policy>, typename Monad<Policy>::template rebind<R>>::type output_type;
    typedef Monad<Policy> input_type;
    callable_type _c;
    template <class U>
    constexpr do_simple_continuation(U &&c)
        : _c(std::forward<U>(c))
    {
    }
    BOOST_OUTCOME_CONSTEXPR output_type operator()(input_type &&v)
    {
      using c_traits = traits::callable_argument_traits<callable_type, input_type>;
      return output_type(do_invoke<c_traits::is_rvalue>()(_c, std::move(v)));
    }
  };
  // For when R is void
  template <class C, template <class> class Monad, class Policy> struct do_simple_continuation<void, C, Monad, Policy>
  {
    typedef typename std::decay<C>::type callable_type;
    // If the return type is an error_type or exception_type or void, reuse monad else rebind monad to R
    typedef typename Monad<Policy>::template rebind<void> output_type;
    typedef Monad<Policy> input_type;
    callable_type _c;
    template <class U>
    constexpr do_simple_continuation(U &&c)
        : _c(std::forward<U>(c))
    {
    }
    BOOST_OUTCOME_CONSTEXPR output_type operator()(input_type &&v)
    {
      using c_traits = traits::callable_argument_traits<callable_type, input_type>;
      return do_invoke<c_traits::is_rvalue>()(_c, std::move(v)), output_type();
    }
  };
  // For when R is a monad
  template <class Policy1, class C, template <class> class Monad, class Policy2> struct do_simple_continuation<Monad<Policy1>, C, Monad, Policy2>
  {
    typedef typename std::decay<C>::type callable_type;
    typedef Monad<Policy1> output_type;
    typedef Monad<Policy2> input_type;
    callable_type _c;
    template <class U>
    constexpr do_simple_continuation(U &&c)
        : _c(std::forward<U>(c))
    {
    }
    BOOST_OUTCOME_CONSTEXPR output_type operator()(input_type &&v)
    {
      using c_traits = traits::callable_argument_traits<callable_type, input_type>;
      return output_type(do_invoke<c_traits::is_rvalue>()(_c, std::move(v)));
    }
  };
  template <class R, class C, class Policy> using do_next = do_simple_continuation<R, C, basic_monad, Policy>;

  template <bool is_monad_monad, class M> struct do_unwrap2;
  template <class M> using do_unwrap = do_unwrap2<is_monad_monad<M>::value, M>;
  template <bool is_monad_monad, class M> struct do_unwrap2
  {
    typedef M input_type;
    typedef input_type output_type;
    BOOST_OUTCOME_CONSTEXPR output_type operator()(const input_type &v) const { return v; }
    BOOST_OUTCOME_CONSTEXPR output_type operator()(input_type &&v) const { return std::move(v); }
  };
  template <class M> struct do_unwrap2<true, M>
  {
    typedef M input_type;
    typedef typename input_type::value_type unwrapped_type;
    typedef typename do_unwrap<unwrapped_type>::output_type output_type;
    BOOST_OUTCOME_CONSTEXPR output_type operator()(const input_type &v) const
    {
      if(v.has_error())
        return do_unwrap<unwrapped_type>()(v.get_error());
      else if(v.has_exception())
        return do_unwrap<unwrapped_type>()(v.get_exception());
      else if(v.has_value())
        return do_unwrap<unwrapped_type>()(v.get());
      else
        return do_unwrap<unwrapped_type>()(unwrapped_type());
    }
    BOOST_OUTCOME_CONSTEXPR output_type operator()(input_type &&v) const
    {
      if(v.has_error())
        return do_unwrap<unwrapped_type>()(std::move(v).get_error());
      else if(v.has_exception())
        return do_unwrap<unwrapped_type>()(std::move(v).get_exception());
      else if(v.has_value())
        return do_unwrap<unwrapped_type>()(std::move(v).get());
      else
        return do_unwrap<unwrapped_type>()(unwrapped_type());
    }
  };

  // Is the monad M's contents directly constructible from an R, not allowing a monad<monad<int>> being constructible from an int
  template <class M, class R, bool is_monad_monad = is_monad_monad<M>::value> struct is_monad_constructible : public std::is_constructible<typename M::value_type, R>
  {
  };
  template <class M, bool is_monad_monad> struct is_monad_constructible<M, typename M::error_type, is_monad_monad> : public std::true_type
  {
  };
  template <class M, bool is_monad_monad> struct is_monad_constructible<M, typename M::exception_type, is_monad_monad> : public std::true_type
  {
  };
  template <class M, bool is_monad_monad> struct is_monad_constructible<M, typename M::empty_type, is_monad_monad> : public std::true_type
  {
  };
  template <class M> struct is_monad_constructible<M, typename M::value_type::value_type, true> : public std::false_type
  {
  };
  template <class _F, class M> struct bind_map_parameter_validation
  {
    typedef typename std::decay<_F>::type F;
    // Figure out what the callable takes
    typedef traits::callable_argument_traits<F, typename M::value_type> f_value_traits;
    typedef traits::callable_argument_traits<F, typename M::error_type> f_error_traits;
    typedef traits::callable_argument_traits<F, typename M::exception_type> f_exception_traits;
    typedef traits::callable_argument_traits<F, typename M::empty_type> f_empty_traits;
    static constexpr bool callable_takes_anything = f_value_traits::is_auto;
    static constexpr bool callable_is_uncallable = !callable_takes_anything && !is_monad<typename M::value_type>::value && (f_value_traits::valid + f_error_traits::valid + f_exception_traits::valid + f_empty_traits::valid) == 0;
    static constexpr bool callable_is_ambiguous = !callable_takes_anything && !is_monad<typename M::value_type>::value && (f_value_traits::valid + f_error_traits::valid + f_exception_traits::valid + f_empty_traits::valid) > 1;

    // Error out common mistakes in the callable parameter
    static_assert(!callable_is_uncallable, "Callable does not have an auto nor templated parameter and is not well formed for none of a value_type, an error_type, an exception_type nor an empty_type. You probably need to adjust the parameter being taken by your callable");
    static_assert(!callable_is_ambiguous, "Callable does not have an auto nor templated parameter, yet is well formed for more than one of value_type, error_type, exception_type and empty_type. As cannot disambiguate meaning, stopping");
    static_assert(!f_value_traits::valid || (callable_takes_anything || std::is_convertible<typename f_value_traits::type, typename M::value_type>::value), "A value_type consuming callable must have a parameter type which can be implicitly converted to from a value_type, or be an auto or templated parameter");
    static_assert(!f_error_traits::valid || callable_takes_anything || is_monad<typename M::value_type>::value || (!f_error_traits::is_rvalue && std::is_same<typename f_error_traits::type, typename M::error_type>::value), "An error_type consuming callable must take an error_type by value");
    static_assert(!f_exception_traits::valid || callable_takes_anything || is_monad<typename M::value_type>::value || (!f_exception_traits::is_rvalue && std::is_same<typename f_exception_traits::type, typename M::exception_type>::value), "An exception_type consuming callable must take an exception_type by value");
    static_assert(!f_empty_traits::valid || callable_takes_anything || is_monad<typename M::value_type>::value || (!f_empty_traits::is_rvalue && std::is_same<typename f_empty_traits::type, typename M::empty_type>::value), "An empty_type consuming callable must take an empty_type by value");

    // Figure out what the callable returns
    using return_type = typename std::conditional<
    f_value_traits::valid, typename f_value_traits::return_type,
    typename std::conditional<f_error_traits::valid, typename f_error_traits::return_type, typename std::conditional<f_exception_traits::valid, typename f_exception_traits::return_type, typename std::conditional<f_empty_traits::valid, typename f_empty_traits::return_type, void>::type>::type>::type>::type;

    // Error out common mistakes in the return type
    static_assert(!f_error_traits::valid || callable_takes_anything || std::is_same<void, return_type>::value || is_monad_constructible<M, return_type>::value, "An error_type consuming callable must return a type convertible to the monad type");
    static_assert(!f_exception_traits::valid || callable_takes_anything || std::is_same<void, return_type>::value || is_monad_constructible<M, return_type>::value, "An exception_type consuming callable must return a type convertible to the monad type");
    static_assert(!f_empty_traits::valid || callable_takes_anything || std::is_same<void, return_type>::value || is_monad_constructible<M, return_type>::value, "An empty_type consuming callable must return a type convertible to the monad type");
  };

  // Enable calling callable if is well formed and is either not auto or we're doing value_type
  template <class C, class U, class value_type, bool additional = true, class value_type2 = void>
  struct enable_if_callable_valid : std::enable_if<additional && traits::callable_argument_traits<C, U>::valid && (!traits::callable_argument_traits<C, U>::is_auto || std::is_same<U, value_type>::value || std::is_same<U, value_type2>::value)>
  {
  };
  template <class C, class U, class value_type, bool additional> struct enable_if_callable_valid<C, U, value_type, additional, void> : std::enable_if<additional && traits::callable_argument_traits<C, U>::valid && (!traits::callable_argument_traits<C, U>::is_auto || std::is_same<U, value_type>::value)>
  {
  };
  /* Invokes the callable passed to next() and bind() and map() optionally folding any monad return type
  R is the type returned by the callable
  C is the callable
  M is the monad

  Call operator is invoked with any of value, error, exception or empty. If not well
  formed, passes through input.
  */
  template <bool fold_monadic_return, class R, class C, class M> struct do_continuation;
  // For when R is not a monad or map()
  template <bool fold_monadic_return, class R, class C, class Policy> struct do_continuation<fold_monadic_return, R, C, basic_monad<Policy>>
  {
    typedef typename std::decay<C>::type callable_type;
    // If the return type is an error_type or exception_type or void, reuse monad else rebind monad to R
    typedef typename std::conditional<std::is_same<R, typename basic_monad<Policy>::error_type>::value || std::is_same<R, typename basic_monad<Policy>::exception_type>::value || std::is_void<R>::value, basic_monad<Policy>, typename basic_monad<Policy>::template rebind<R>>::type output_type;
    callable_type _c;
    constexpr do_continuation(const callable_type &c)
        : _c(c)
    {
    }
    constexpr do_continuation(callable_type &c)
        : _c(c)
    {
    }
    constexpr do_continuation(callable_type &&c)
        : _c(std::move(c))
    {
    }
    template <class U, typename = typename enable_if_callable_valid<callable_type, U, typename basic_monad<Policy>::value_type, !std::is_void<R>::value>::type> constexpr output_type operator()(U &&v, traits::detail::rank<4>) const
    {
      return output_type(do_invoke<traits::callable_argument_traits<callable_type, U>::is_rvalue>()(_c, std::move(v)));
    }
    template <class U, typename = typename enable_if_callable_valid<callable_type, U, typename basic_monad<Policy>::value_type, std::is_void<R>::value>::type> constexpr output_type operator()(U &&v, traits::detail::rank<3>) const
    {
      return do_invoke<traits::callable_argument_traits<callable_type, U>::is_rvalue>()(_c, std::move(v)), output_type();
    }
    template <class U, typename = typename std::enable_if<std::is_constructible<output_type, U>::value>::type> constexpr output_type operator()(U &&v, traits::detail::rank<2>) const { return output_type(std::forward<U>(v)); }
    template <class U> constexpr output_type operator()(U &&, traits::detail::rank<1>) const { return output_type(); }
  };
  // For when R is a monad
  template <class Policy1, class C, class Policy2> struct do_continuation<true, basic_monad<Policy1>, C, basic_monad<Policy2>>
  {
    typedef typename std::decay<C>::type callable_type;
    typedef basic_monad<Policy1> output_type;
    typedef basic_monad<Policy2> input_type;
    callable_type _c;
    constexpr do_continuation(const callable_type &c)
        : _c(c)
    {
    }
    constexpr do_continuation(callable_type &c)
        : _c(c)
    {
    }
    constexpr do_continuation(callable_type &&c)
        : _c(std::move(c))
    {
    }
    template <class U, typename = typename enable_if_callable_valid<callable_type, U, input_type, !std::is_void<typename output_type::value_type>::value, typename input_type::value_type>::type> constexpr output_type operator()(U &&v, traits::detail::rank<4>) const
    {
      return output_type(do_invoke<traits::callable_argument_traits<callable_type, U>::is_rvalue>()(_c, std::move(v)));
    }
    template <class U, typename = typename enable_if_callable_valid<callable_type, U, input_type, std::is_void<typename output_type::value_type>::value, typename input_type::value_type>::type> constexpr output_type operator()(U &&v, traits::detail::rank<3>) const
    {
      return do_invoke<traits::callable_argument_traits<callable_type, U>::is_rvalue>()(_c, std::move(v)), output_type();
    }
    template <class U, typename = typename std::enable_if<std::is_constructible<output_type, U>::value>::type> constexpr output_type operator()(U &&v, traits::detail::rank<2>) const { return output_type(std::forward<U>(v)); }
    template <class U> constexpr output_type operator()(U &&, traits::detail::rank<1>) const { return output_type(); }
  };

  template <class R, class C, class M> using do_bind = do_continuation<true, R, C, M>;
  template <class R, class C, class M> using do_map = do_continuation<false, R, C, M>;
}

BOOST_OUTCOME_V1_NAMESPACE_END

#endif
