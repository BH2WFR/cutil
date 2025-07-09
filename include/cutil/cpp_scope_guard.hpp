/*
 *  Created on: 13/02/2018
 *      Author: ricab
 *      github: https://github.com/ricab/scope_guard
 * See README.md for documentation of this header's public interface.
 *
 * Modified by BH2WFR for cutil project at 7 JUL 2025.
 */

#ifndef CUTIL_CPP_SCOPE_GUARD_HPP__
#define CUTIL_CPP_SCOPE_GUARD_HPP__

#include <cutil/base.h>
#include <cutil/cpp_base.hpp>

/* Example:
	void someFunction() {
		MyDevice* pDevice = Manager::getDevice();
		pDevice->open();
		auto closeDevice = cutil::make_scope_guard([&pDevice] {
			if(pDevice->isOpen()){
				pDevice->close();
			}
		});
		// do something with pDevice
		
		if(...){
			return ; // if something goes wrong, the device will be closed automatically
		}
		// do something else with pDevice
		pDevice->close(); // if everything is ok, close the device manually
	}
	void someFunction2() {
		MyDevice* pDevice = Manager::getDevice();
		pDevice->open();
		auto closeDevice = cutil::make_scope_guard([&pDevice] {
			if(pDevice->isOpen()){
				pDevice->close();
			}
		});
		//...
		closeDevice.dismiss(); // if you want to dismiss the scope guard, call dismiss() before leaving the scope
		// pDevice will not be closed automatically
	}
	void someFunction3() {
		MyDevice* pDevice = Manager::getDevice();
		pDevice->open();
		auto closeDevice = cutil::make_scope_guard([&pDevice] {
			if(pDevice->isOpen()){
				pDevice->close();
			}
		});
		//...
		// if you want to execute the callback and dismiss the scope guard, call execute_and_dismiss() before leaving the scope
		closeDevice.execute_and_dismiss();
		// pDevice will not be closed automatically
	}
*/

#ifndef CUTIL_CPP14_SUPPORTED
	#error ">= C++14 is required"
#endif

#include <type_traits>
#include <utility>

#if defined(CUTIL_CPP17_SUPPORTED)
	#ifdef SG_REQUIRE_NOEXCEPT_IN_CPP17
		#define SG_REQUIRE_NOEXCEPT
	#endif
#endif

_CUTIL_NAMESPACE_BEGIN
	namespace scope_guard_internal
	{
	/* --- Some custom type traits --- */

	// Type trait determining whether a type is callable with no arguments
	template<typename T, typename = void>
	struct is_noarg_callable_t
		: public std::false_type
	{}; // in general, false

	template<typename T>
	struct is_noarg_callable_t<T, decltype(std::declval<T&&>()())>
		: public std::true_type
	{}; // only true when call expression valid

	// Type trait determining whether a no-argument callable returns void
	template<typename T>
	struct returns_void_t
		: public std::is_same<void, decltype(std::declval<T&&>()())>
	{};

	/* Type trait determining whether a no-arg callable is nothrow invocable if
	required. This is where SG_REQUIRE_NOEXCEPT logic is encapsulated. */
	template<typename T>
	struct is_nothrow_invocable_if_required_t
		: public
#ifdef SG_REQUIRE_NOEXCEPT
			std::is_nothrow_invocable<T> /* Note: _r variants not enough to
											confirm void return: any return can be
											discarded so all returns are
											compatible with void */
#else
			std::true_type
#endif
	{};

	// logic AND of two or more type traits
	template<typename A, typename B, typename... C>
	struct and_t : public and_t<A, and_t<B, C...>>
	{}; // for more than two arguments

	template<typename A, typename B>
	struct and_t<A, B> : public std::conditional<A::value, B, A>::type
	{}; // for two arguments

	// Type trait determining whether a type is a proper scope_guard callback.
	template<typename T>
	struct is_proper_sg_callback_t
		: public and_t<is_noarg_callable_t<T>,
					 returns_void_t<T>,
					 is_nothrow_invocable_if_required_t<T>,
					 std::is_nothrow_destructible<T>>
	{};


	/* --- The actual scope_guard template --- */

	template<typename Callback,
			 typename = typename std::enable_if<
				 is_proper_sg_callback_t<Callback>::value>::type>
	class scope_guard;


	/* --- Now the friend maker --- */

	template<typename Callback>
	scope_guard_internal::scope_guard<Callback> make_scope_guard(Callback&& callback)
	noexcept(std::is_nothrow_constructible<Callback, Callback&&>::value); /*
	we need this in the inner namespace due to MSVC bugs preventing
	cutil::scope_guard_internal::scope_guard from befriending a cutil::make_scope_guard
	template instance in the parent namespace (see https://is.gd/xFfFhE). */


	/* --- The template specialization that actually defines the class --- */

	template<typename Callback>
	class _CUTIL_NODISCARD scope_guard<Callback> final
	{
	public:
		typedef Callback callback_type;

		scope_guard(scope_guard&& other)
		noexcept(std::is_nothrow_constructible<Callback, Callback&&>::value);

		~scope_guard() noexcept; // highlight noexcept dtor

		void dismiss() noexcept;
		void execute_and_dismiss() noexcept;

	public:
		scope_guard() = delete;
		scope_guard(const scope_guard&) = delete;
		scope_guard& operator=(const scope_guard&) = delete;
		scope_guard& operator=(scope_guard&&) = delete;

	private:
		explicit scope_guard(Callback&& callback)
		noexcept(std::is_nothrow_constructible<Callback, Callback&&>::value); /*
														meant for friends only */

		friend scope_guard<Callback> make_scope_guard<Callback>(Callback&&)
		noexcept(std::is_nothrow_constructible<Callback, Callback&&>::value); /*
		only make_scope_guard can create scope_guards from scratch (i.e. non-move)
		*/

	private:
		Callback m_callback;
		bool m_active;

	};

	} // namespace scope_guard_internal


	/* --- Now the single public maker function --- */

	using scope_guard_internal::make_scope_guard; // see comment on declaration above

_CUTIL_NAMESPACE_END

////////////////////////////////////////////////////////////////////////////////
template<typename Callback>
cutil::scope_guard_internal::scope_guard<Callback>::scope_guard(Callback&& callback)
noexcept(std::is_nothrow_constructible<Callback, Callback&&>::value)
	: m_callback(std::forward<Callback>(callback)) /* use () instead of {} because
	of DR 1467 (https://is.gd/WHmWuo), which still impacts older compilers
	(e.g. GCC 4.x and clang <=3.6, see https://godbolt.org/g/TE9tPJ and
	https://is.gd/Tsmh8G) */
	, m_active{true}
{}

////////////////////////////////////////////////////////////////////////////////
template<typename Callback>
cutil::scope_guard_internal::scope_guard<Callback>::scope_guard::~scope_guard() noexcept  /*
need the extra injected-class-name here to make different compilers happy */
{
	if(m_active)
	m_callback();
}

////////////////////////////////////////////////////////////////////////////////
template<typename Callback>
cutil::scope_guard_internal::scope_guard<Callback>::scope_guard(scope_guard&& other)
noexcept(std::is_nothrow_constructible<Callback, Callback&&>::value)
	: m_callback(std::forward<Callback>(other.m_callback)) // idem
	, m_active{std::move(other.m_active)}
{
	other.m_active = false;
}


////////////////////////////////////////////////////////////////////////////////
//* Dismisses the scope guard, then it will not executed on destruction.
template<typename Callback>
inline void cutil::scope_guard_internal::scope_guard<Callback>::dismiss() noexcept
{
	m_active = false;
}

////////////////////////////////////////////////////////////////////////////////
//* Execute the scope guard ahead, then dismiss it, it will not executed on destruction.
template<typename Callback>
inline void cutil::scope_guard_internal::scope_guard<Callback>::execute_and_dismiss() noexcept
{
	if(m_active){
		m_callback();
	}
	m_active = false;
}

//*-----------------------------------------------------------------------------
//* Invoke it to make a scope guard object.
//  @param callback - the callable object to be invoked when the scope guard is destructed.
//  note: do not forget to save the returned object, otherwise the callback will not be invoked.
//  if there are multiple scope objects, the callback will be invoked in reverse order. (down to up, LIFO)
//  call `.dismiss()` to dismiss the scope guard, then the callback will not be invoked.
template<typename Callback> _CUTIL_NODISCARD
inline auto cutil::scope_guard_internal::make_scope_guard(Callback&& callback)
noexcept(std::is_nothrow_constructible<Callback, Callback&&>::value)
-> scope_guard_internal::scope_guard<Callback>
{
	return scope_guard_internal::scope_guard<Callback>{std::forward<Callback>(callback)};
}




#endif /* CUTIL_CPP_SCOPE_GUARD_HPP__ */
