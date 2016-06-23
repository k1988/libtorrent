/*

Copyright (c) 2007-2016, Arvid Norberg
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the distribution.
    * Neither the name of the author nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef TORRENT_ASSERT

#include "libtorrent/config.hpp"

#if (defined TORRENT_DEBUG && TORRENT_USE_ASSERTS) \
	|| defined TORRENT_ASIO_DEBUGGING \
	|| defined TORRENT_PROFILE_CALLS \
	|| defined TORRENT_RELEASE_ASSERTS \
	|| defined TORRENT_DEBUG_BUFFERS

#include <string>
std::string demangle(char const* name);
TORRENT_EXPORT void print_backtrace(char* out, int len, int max_depth = 0);
#endif

// this is to disable the warning of conditional expressions
// being constant in msvc
#ifdef _MSC_VER
#define TORRENT_WHILE_0  \
	__pragma( warning(push) ) \
	__pragma( warning(disable:4127) ) \
	while (0) \
	__pragma( warning(pop) )
#else
#define TORRENT_WHILE_0 while (0)
#endif


// declarations of the two functions

// internal
TORRENT_EXPORT void assert_print(char const* fmt, ...) TORRENT_FORMAT(1,2);

// internal
TORRENT_EXPORT void assert_fail(const char* expr, int line
	, char const* file, char const* function, char const* val, int kind = 0);



#if TORRENT_USE_ASSERTS

#ifdef TORRENT_PRODUCTION_ASSERTS
extern char const* libtorrent_assert_log;
#endif

#if TORRENT_USE_IOSTREAM
#include <sstream>
#endif

#ifndef TORRENT_USE_SYSTEM_ASSERTS

#define TORRENT_ASSERT_PRECOND(x) \
	do { if (x) {} else assert_fail(#x, __LINE__, __FILE__, TORRENT_FUNCTION, 0, 1); } TORRENT_WHILE_0

#define TORRENT_ASSERT(x) \
	do { if (x) {} else assert_fail(#x, __LINE__, __FILE__, TORRENT_FUNCTION, 0, 0); } TORRENT_WHILE_0

#if TORRENT_USE_IOSTREAM
#define TORRENT_ASSERT_VAL(x, y) \
	do { if (x) {} else { std::stringstream __s__; __s__ << #y ": " << y; \
	assert_fail(#x, __LINE__, __FILE__, TORRENT_FUNCTION, __s__.str().c_str(), 0); } } TORRENT_WHILE_0
#else
#define TORRENT_ASSERT_VAL(x, y) TORRENT_ASSERT(x)
#endif

#else
#include <cassert>
#define TORRENT_ASSERT_PRECOND(x) assert(x)
#define TORRENT_ASSERT(x) assert(x)
#define TORRENT_ASSERT_VAL(x, y) assert(x)
#endif

#else // TORRENT_USE_ASSERTS

#pragma warning(disable:4267)
#pragma warning(disable:4244)
#pragma warning(disable:4800)
#pragma warning(disable:4099)
#pragma warning(disable:4018)
#pragma warning(disable:4355)
#pragma warning(disable:4101)

#define TORRENT_ASSERT_PRECOND(a) do {} TORRENT_WHILE_0
#define TORRENT_ASSERT(a) do {} TORRENT_WHILE_0
#define TORRENT_ASSERT_VAL(a, b) do {} TORRENT_WHILE_0

#endif // TORRENT_USE_ASSERTS

#endif

