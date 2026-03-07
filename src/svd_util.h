// SPDX-FileCopyrightText: 2007-2020 pancake <pancake@nopcode.org>
// SPDX-License-Identifier: LGPL-3.0-only

// Internal utility header for rz-svd standalone compilation.
// Provides macros and types derived from Rizin's rz_types.h and rz_util.

#ifndef SVD_UTIL_H
#define SVD_UTIL_H

#include "rz_svd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#if defined(_MSC_VER)
#define strcasecmp  _stricmp
#define strncasecmp _strnicmp
#endif

#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

// Basic type aliases (from rz_types_base.h)
typedef uint8_t ut8;
typedef uint16_t ut16;
typedef uint32_t ut32;
typedef uint64_t ut64;

// Allocation macros (from rz_types.h)
#define RZ_NEW0(x) (x *)calloc(1, sizeof(x))
#define RZ_FREE(x) \
	{ \
		free((void *)x); \
		x = NULL; \
	}

// Path separator (from rz_types.h)
#ifdef _WIN32
#define RZ_SYS_DIR "\\"
#else
#define RZ_SYS_DIR "/"
#endif

#define RZ_JOIN_2_PATHS(p1, p2) p1 RZ_SYS_DIR p2

// Logging (no-op in standalone mode)
#define RZ_LOG_DEBUG(fmtstr, ...) /* no-op */

// The SvdList types and svd_list_foreach macro are defined in rz_svd.h
// Include additional list utility declarations here.

SvdList *svd_list_newf(SvdListFree fn);
void svd_list_free(SvdList *list);
bool svd_list_append(SvdList *list, void *data);

// File utilities (replaces rz_file_*)
char *svd_file_slurp(const char *path, size_t *size_out);
bool svd_file_exists(const char *path);

// String utilities (replaces rz_str_*)
char *svd_str_newf(const char *fmt, ...);

#endif // SVD_UTIL_H
