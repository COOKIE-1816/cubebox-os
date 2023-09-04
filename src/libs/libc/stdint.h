#ifndef _STDINT_H_
#define _STDINT_h_

typedef unsigned int			uint_t;

typedef signed char				int8_t;
typedef short int				int16_t;
typedef int						int32_t;
typedef long long int			int64_t;

typedef unsigned char			uint8_t;
typedef unsigned short int		uint16_t;
typedef unsigned int			uint32_t;
typedef unsigned long long		uint64_t;

typedef signed char				int_least8_t;
typedef short int				int_least16_t;
typedef int						int_least32_t;
typedef unsigned long long int	uint_least64_t;

typedef signed char				int_fast8_t;
typedef int						int_fast16_t;
typedef int						int_fast32_t;
typedef long long int			int_fast64_t;

typedef unsigned char			uint_fast8_t;
typedef unsigned int			uint_fast16_t;
typedef unsigned int			uint_fast32_t;
typedef unsigned long long int	uint_fast64_t;

typedef int				intptr_t;
typedef unsigned int	uintptr_t;

typedef long long int			intmax_t;
typedef unsigned long long int	uintmax_t;


#if !defined __cplusplus || defined __STDC_LIMIT_MACROS

#define __INT64_C(c)	c ## LL		// As a ISO C99 standard specifies, implementations of these macros in C++ should only
#define __UINT64_C(c)	c ## ULL	// be defined if explicitly requested.

#define INT8_MIN			(-128)								// ---+
#define INT16_MIN			(-32767-1)							//    +-- Signed integral types minimum
#define INT32_MIN			(-2147483647-1)						//    |
#define INT64_MIN			(-__INT64_C(9223372036854775807)-1) // ---+

#define INT8_MAX			(127)								// ---+
#define INT16_MAX			(32767)								//    +-- Signed integral types maximum
#define INT32_MAX			(2147483647)						//    |
#define INT64_MAX			(__INT64_C(9223372036854775807))	// ---+

#define UINT8_MAX			(255)								// ---+
#define UINT16_MAX			(65535)								//    +-- Unsigned integral types maximum
#define UINT32_MAX			(4294967295U)						//    |
#define UINT64_MAX			(__UINT64_C(18446744073709551615))	// ---+

#define INT_LEAST8_MIN		(-128)								// ---+
#define INT_LEAST16_MIN		(-32767-1)							//    +-- Signed integral types with minimum minumum
#define INT_LEAST32_MIN		(-2147483647-1)						//    |
#define INT_LEAST64_MIN		(-__INT64_C(9223372036854775807)-1)	// ---+

#define INT_LEAST8_MAX		(127)								// ---+
#define INT_LEAST16_MAX		(32767)								//    +-- Signed integral types with maximum maximum
#define INT_LEAST32_MAX		(2147483647)						//    |
#define INT_LEAST64_MAX		(__INT64_C(9223372036854775807))	// ---+

#define UINT_LEAST8_MAX		(255)								// ---+
#define UINT_LEAST16_MAX	(65535)								//    +-- Unsigned integral types with maximum maximum
#define UINT_LEAST32_MAX	(4294967295U)						//    |
#define UINT_LEAST64_MAX	(__UINT64_C(18446744073709551615))	// ---+

#define INT_FAST8_MIN		(-128)								// ---+
#define INT_FAST16_MIN      (-2147483647-1)						//    +-- Fast signed integral types with minimum minimum
#define INT_FAST32_MIN		(-2147483647-1)						//    |
#define INT_FAST64_MIN      (-__INT64_C(9223372036854775807)-1)	// ---+

#define INT_FAST8_MAX		(127)								// ---+
#define INT_FAST16_MAX		(2147483647)						//    +-- Fast signed integral types with maximum maximum
#define INT_FAST32_MAX		(2147483647)						//    |
#define INT_FAST64_MAX		(__INT64_C(9223372036854775807))	// ---+

#define UINT_FAST8_MAX		(255)								// ---+
#define UINT_FAST16_MAX		(4294967295U)						//    +-- Fast unsigned integral types with maximum maximum
#define UINT_FAST32_MAX		(4294967295U)						//    |
#define UINT_FAST64_MAX		(__UINT64_C(18446744073709551615))	// ---+



#define INTPTR_MIN			(- 2147483647 - 1	)
#define INTPTR_MAX			(  2147483647		)
#define UINTPTR_MAX			(  4294967295U		)

# define INTMAX_MIN			(-	__INT64_C(9223372036854775807) - 1	)
# define INTMAX_MAX			(	__INT64_C(9223372036854775807)		)
# define UINTMAX_MAX		(	__UINT64_C(18446744073709551615)	)

#define PTRDIFF_MIN			(- 2147483647 - 1	)
#define PTRDIFF_MAX			(  2147483647		)

#define SIG_ATOMIC_MIN		(- 2147483647 - 1	)
#define SIG_ATOMIC_MAX		(  2147483647		)

#define SIZE_MAX			(4294967295U)

#define WCHAR_MIN			__WCHAR_MIN
#define WCHAR_MAX			__WCHAR_MAX

#define WINT_MIN			(0u			)
#define WINT_MAX			(4294967295u)

#endif // C99


#if !defined __cplusplus || defined __STDC_CONSTANT_MACROS

#define INT8_C		(c)	c
#define INT16_C		(c)	c
#define INT32_C		(c)	c
#define INT64_C		(c)	c ## LL

#define UINT8_C		(c) c
#define UINT16_C	(c) c
#define UINT32_C	(c) c ## U
#define UINT64_C	(c) c ## ULL

#define INTMAX_C	(c)	c ## LL
#define UINTMAX_C	(c)	c ## ULL

#endif

#define i8		int8_t
#define i16		int16_t
#define i32		int32_t
#define i64		int64_t
#define u8		uint8_t
#define u16		uint16_t
#define u32		uint32_t
#define u64		uint64_t
#define f8		int_fast8_t
#define f16		int_fast16_t
#define f32		int_fast32_t
#define f64		int_fast64_t
#define fu8		uint_fast8_t
#define fu16	uint_fast16_t
#define fu32	uint_fast32_t
#define fu64	uint_fast64_t

#endif