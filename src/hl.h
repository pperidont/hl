/*
 * Copyright (C)2005-2016 Haxe Foundation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifndef HL_H
#define HL_H

#define HL_VERSION	010

#ifdef _WIN32
#	define HL_WIN
#endif

#if defined(__APPLE__) || defined(__MACH__) || defined(macintosh)
#	define HL_MAC
#endif

#if defined(linux) || defined(__linux__)
#	define HL_LINUX
#	define _GNU_SOURCE
#endif

#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
#	define HL_BSD
#endif

#if defined(_64BITS) || defined(__x86_64__) || defined(_M_X64)
#	define HL_64
#endif

#if defined(__GNUC__)
#	define HL_GCC
#endif

#if defined(__MINGW32__)
#	define HL_MINGW
#endif

#if defined(__CYGWIN__)
#	define HL_CYGWIN
#endif

#if defined(__llvm__)
#	define HL_LLVM
#endif

#if defined(_MSC_VER) && !defined(HL_LLVM)
#	define HL_VCC
#	pragma warning(disable:4996) // remove deprecated C API usage warnings
#	pragma warning(disable:4055) // void* - to - function cast
#	pragma warning(disable:4152) // void* - to - function cast
#	pragma warning(disable:4201) // anonymous struct
#	pragma warning(disable:4127) // while( true )
#	pragma warning(disable:4710) // inline disabled
#	pragma warning(disable:4711) // inline activated
#	pragma warning(disable:4255) // windows include
#	pragma warning(disable:4820) // windows include
#	pragma warning(disable:4668) // windows include
#endif

#if defined(HL_VCC) || defined(HL_MINGW) || defined(HL_CYGWIN)
#	define HL_WIN_CALL
#endif

#ifdef _DEBUG
#	define HL_DEBUG
#endif

#include <stddef.h>
#ifndef HL_VCC
#	include <stdint.h>
#endif

#if defined(HL_VCC) || defined(HL_MINGW)
#	define EXPORT __declspec( dllexport )
#	define IMPORT __declspec( dllimport )
#else
#	define EXPORT
#	define IMPORT
#endif

#ifdef HL_64
#	define HL_WSIZE 8
#	define IS_64	1
#	ifdef HL_VCC
#		define _PTR_FMT	L"%IX"
#	else
#		define _PTR_FMT	u"%lX"
#	endif
#else
#	define HL_WSIZE 4
#	define IS_64	0
#	ifdef HL_VCC
#		define _PTR_FMT	L"%IX"
#	else
#		define _PTR_FMT	u"%X"
#	endif
#endif

#ifdef __cplusplus
#	define C_FUNCTION_BEGIN extern "C" {
#	define C_FUNCTION_END	};
#else
#	define C_FUNCTION_BEGIN
#	define C_FUNCTION_END
#	ifndef true
#		define true 1
#		define false 0
		typedef unsigned char bool;
#	endif
#endif

typedef intptr_t int_val;
typedef long long int64;

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#ifdef HLDLL_EXPORTS
#define HL_API extern EXPORT
#else
#define	HL_API IMPORT
#endif

// -------------- UNICODE -----------------------------------

#if defined(HL_WIN) && !defined(HL_LLVM)
#	include <windows.h>
#	include <wchar.h>
typedef wchar_t	uchar;
#	define USTR(str)	L##str
#	define HL_NATIVE_WCHAR_FUN
#	define usprintf		swprintf
#	define uprintf		wprintf
#	define ustrlen		wcslen
#	define ustrdup		_wcsdup
#	define uvsprintf	wvsprintf
#	define utod(s,end)	wcstod(s,end)
#	define utoi(s,end)	wcstol(s,end,10)
#	define ucmp(a,b)	wcscmp(a,b)
#	define utostr(out,size,str) wcstombs(out,str,size)	
#else
#	include <stdarg.h>
typedef unsigned short uchar;
#	undef USTR
#	define USTR(str)	u##str
HL_API int ustrlen( const uchar *str );
HL_API uchar *ustrdup( const uchar *str );
HL_API double utod( const uchar *str, uchar **end );
HL_API int utoi( const uchar *str, uchar **end );
HL_API int ucmp( const uchar *a, const uchar *b );
HL_API int utostr( char *out, int out_size, const uchar *str );
HL_API int usprintf( uchar *out, int out_size, const uchar *fmt, ... );
HL_API int uvsprintf( uchar *out, const uchar *fmt, va_list arglist );
HL_API void uprintf( const uchar *fmt, const uchar *str );
#endif

#ifdef HL_VCC
#	define hl_debug_break()	if( IsDebuggerPresent() ) __debugbreak()
#else
#	define hl_debug_break() hl_fatal("debugbreak")
#endif

#define DADDR(v)	((int)((int_val)(v))&0xFFFF)

// ---- TYPES -------------------------------------------

typedef enum {
	HVOID	= 0,
	HUI8	= 1,
	HUI16	= 2,
	HI32	= 3,
	HF32	= 4,
	HF64	= 5,
	HBOOL	= 6,
	HBYTES	= 7,
	HDYN	= 8,
	HFUN	= 9,
	HOBJ	= 10,
	HARRAY	= 11,
	HTYPE	= 12,
	HREF	= 13,
	HVIRTUAL= 14,
	HDYNOBJ = 15,
	HABSTRACT=16,
	HENUM	= 17,
	HNULL	= 18,
	// ---------
	HLAST	= 19,
	_H_FORCE_INT = 0x7FFFFFFF
} hl_type_kind;

typedef struct hl_type hl_type;
typedef struct hl_runtime_obj hl_runtime_obj;
typedef struct hl_alloc_block hl_alloc_block;
typedef struct { hl_alloc_block *cur; } hl_alloc;
typedef struct _hl_field_lookup hl_field_lookup;

typedef struct {
	hl_alloc alloc;
	void **functions_ptrs;
	hl_type **functions_types;
} hl_module_context;

typedef struct {
	hl_type **args;
	hl_type *ret;
	int nargs;
	// storage for closure
	hl_type *parent;
	struct {
		hl_type_kind kind;
		void *p;
	} closure_type;
	struct {
		hl_type **args;
		hl_type *ret;
		int nargs;
		hl_type *parent;
	} closure;
} hl_type_fun;

typedef struct {
	const uchar *name;
	hl_type *t;
	int hashed_name;
} hl_obj_field;

typedef struct {
	const uchar *name;
	int findex;
	int pindex;
	int hashed_name;
} hl_obj_proto;

typedef struct {
	int nfields;
	int nproto;
	const uchar *name;
	hl_type *super;
	hl_obj_field *fields;
	hl_obj_proto *proto;
	void **global_value;
	hl_module_context *m;
	hl_runtime_obj *rt;
} hl_type_obj;

typedef struct {
	hl_obj_field *fields;
	int nfields;
	// runtime
	int dataSize;
	int *indexes;
	hl_field_lookup *lookup;
} hl_type_virtual;

typedef struct {
	const uchar *name;
	int nparams;
	hl_type **params;
	int size;
	bool hasptr;
	int *offsets;
} hl_enum_construct;

typedef struct {
	const uchar *name;
	int nconstructs;
	hl_enum_construct *constructs;
	void **global_value;
} hl_type_enum;

struct hl_type {
	hl_type_kind kind;
	union {
		hl_type_fun *fun;
		hl_type_obj *obj;
		hl_type_enum *tenum;
		hl_type_virtual *virt;
		hl_type	*tparam;
		const uchar *abs_name;
	};
	void **vobj_proto;
};

HL_API int hl_type_size( hl_type *t );
HL_API int hl_pad_size( int size, hl_type *t );
HL_API int hl_stack_size( hl_type *t );

HL_API hl_runtime_obj *hl_get_obj_rt( hl_type *ot );
HL_API hl_runtime_obj *hl_get_obj_proto( hl_type *ot );

/* -------------------- VALUES ------------------------------ */

typedef unsigned char vbyte;

typedef struct {
	hl_type *t;
#	ifndef HL_64
	int __pad; // force align on 16 bytes for double
#	endif
	union {
		bool b;
		unsigned char ui8;
		unsigned short ui16;
		int i;
		float f;
		double d;
		vbyte *bytes;
		void *ptr;
	} v;
} vdynamic;

typedef struct {
	hl_type *t;
	/* fields data */
} vobj;

typedef struct _vvirtual vvirtual;
struct _vvirtual {
	hl_type *t;
	vdynamic *value;
	vvirtual *next;
};

#define hl_vfields(v) ((void**)(((vvirtual*)(v))+1))

typedef struct {
	hl_type *t;
	hl_type *at;
	int size;
	int __pad; // force align on 16 bytes for double
} varray;

typedef struct _vclosure {
	hl_type *t;
	void *fun;
	int hasValue;
	void *value;
} vclosure;

typedef struct {
	vclosure cl;
	vclosure *wrappedFun;
} vclosure_wrapper;

struct _hl_field_lookup {
	hl_type *t;
	int hashed_name;
	int field_index; // negative or zero : index in methods
};

struct hl_runtime_obj {
	hl_type *t;
	// absolute
	int nfields;
	int nproto;
	int size;
	int nmethods;
	void **methods;
	int *fields_indexes;
	hl_runtime_obj *parent;
	const uchar *(*toStringFun)( vdynamic *obj );
	int (*compareFun)( vdynamic *a, vdynamic *b );
	vdynamic *(*castFun)( vdynamic *obj, hl_type *t );
	vdynamic *(*getFieldFun)( vdynamic *obj, int hfield );
	// relative
	int nlookup;
	hl_field_lookup *lookup;
};

typedef struct {
	hl_type t;
	hl_field_lookup fields;
} vdynobj_proto;

typedef struct {
	vdynobj_proto *dproto;
	char *fields_data;
	int nfields;
	int dataSize;
	vvirtual *virtuals;
} vdynobj;

typedef struct _venum {
	int index;
} venum;

HL_API hl_type hlt_void;
HL_API hl_type hlt_i32;
HL_API hl_type hlt_f64;
HL_API hl_type hlt_f32;
HL_API hl_type hlt_dyn;
HL_API hl_type hlt_array;
HL_API hl_type hlt_bytes;
HL_API hl_type hlt_dynobj;

HL_API double hl_nan();
HL_API bool hl_is_dynamic( hl_type *t );
#define hl_is_ptr(t)	((t)->kind >= HBYTES)
HL_API bool hl_same_type( hl_type *a, hl_type *b );
HL_API bool hl_safe_cast( hl_type *t, hl_type *to );

#define hl_aptr(a,t)	((t*)(((varray*)(a))+1))

HL_API varray *hl_alloc_array( hl_type *t, int size );
HL_API vdynamic *hl_alloc_dynamic( hl_type *t );
HL_API vdynamic *hl_alloc_obj( hl_type *t );
HL_API vvirtual *hl_alloc_virtual( hl_type *t );
HL_API vdynobj *hl_alloc_dynobj();
HL_API vbyte *hl_alloc_bytes( int size );
HL_API vbyte *hl_copy_bytes( const vbyte *byte, int size );
HL_API int hl_utf8_length( const vbyte *s, int pos );
HL_API int hl_from_utf8( uchar *out, int outLen, const char *str );
HL_API char *hl_to_utf8( const uchar *bytes );
HL_API vdynamic *hl_virtual_make_value( vvirtual *v );

HL_API int hl_hash( vbyte *name );
HL_API int hl_hash_utf8( const char *str ); // no cache
HL_API int hl_hash_gen( const uchar *name, bool cache_name );
HL_API const uchar *hl_field_name( int hash );

#define hl_error(msg)	hl_error_msg(USTR(msg))
HL_API void hl_error_msg( const uchar *msg, ... );
HL_API void hl_throw( vdynamic *v );
HL_API void hl_rethrow( vdynamic *v );
HL_API void hl_setup_exception( void *resolve_symbol, void *capture_stack );
HL_API varray *hl_exception_stack();

HL_API vvirtual *hl_to_virtual( hl_type *vt, vdynamic *obj );
HL_API void hl_init_virtual( hl_type *vt, hl_module_context *ctx );
HL_API hl_field_lookup *hl_lookup_find( hl_field_lookup *l, int size, int hash );
HL_API hl_field_lookup *hl_lookup_insert( hl_field_lookup *l, int size, int hash, hl_type *t, int index );

HL_API int hl_dyn_geti( vdynamic *d, int hfield, hl_type *t );
HL_API void *hl_dyn_getp( vdynamic *d, int hfield, hl_type *t );
HL_API float hl_dyn_getf( vdynamic *d, int hfield );
HL_API double hl_dyn_getd( vdynamic *d, int hfield );

HL_API int hl_dyn_casti( void *data, hl_type *t, hl_type *to );
HL_API void *hl_dyn_castp( void *data, hl_type *t, hl_type *to );
HL_API float hl_dyn_castf( void *data, hl_type *t );
HL_API double hl_dyn_castd( void *data, hl_type *t );

#define hl_invalid_comparison 0xAABBCCDD
HL_API int hl_dyn_compare( vdynamic *a, vdynamic *b );
HL_API vdynamic *hl_make_dyn( void *data, hl_type *t );
HL_API void hl_write_dyn( void *data, hl_type *t, vdynamic *v );

HL_API void hl_dyn_seti( vdynamic *d, int hfield, hl_type *t, int value );
HL_API void hl_dyn_setp( vdynamic *d, int hfield, hl_type *t, void *ptr );
HL_API void hl_dyn_setf( vdynamic *d, int hfield, float f );
HL_API void hl_dyn_setd( vdynamic *d, int hfield, double v );

HL_API vclosure *hl_alloc_closure_void( hl_type *t, void *fvalue );
HL_API vclosure *hl_alloc_closure_ptr( hl_type *fullt, void *fvalue, void *ptr );
HL_API vclosure *hl_make_fun_wrapper( vclosure *c, hl_type *to );
HL_API void *hl_wrapper_call( void *value, void **args, vdynamic *ret );
HL_API void *hl_dyn_call_obj( vdynamic *obj, hl_type *ft, int hfield, void **args, vdynamic *ret );
HL_API vdynamic *hl_dyn_call( vclosure *c, vdynamic **args, int nargs );

// ----------------------- ALLOC --------------------------------------------------

#define MEM_HAS_PTR(kind)	(!((kind)&2))
#define MEM_KIND_DYNAMIC	0
#define MEM_KIND_RAW		1
#define MEM_KIND_NOPTR		2
#define MEM_KIND_FINALIZER	3
#define MEM_ALIGN_DOUBLE	128
#define MEM_ZERO			256

HL_API void *hl_gc_alloc_gen( int size, int flags );
HL_API void hl_add_root( void **ptr );
HL_API void hl_remove_root( void **ptr );
HL_API void hl_gc_major();
HL_API bool hl_is_gc_ptr( void *ptr );
HL_API void hl_gc_dump();

#define hl_gc_alloc_noptr(size)		hl_gc_alloc_gen(size,MEM_KIND_NOPTR)
#define hl_gc_alloc(size)			hl_gc_alloc_gen(size,MEM_KIND_DYNAMIC)
#define hl_gc_alloc_raw(size)		hl_gc_alloc_gen(size,MEM_KIND_RAW)
#define hl_gc_alloc_finalizer(size) hl_gc_alloc_gen(size,MEM_KIND_FINALIZER)

HL_API void hl_alloc_init( hl_alloc *a );
HL_API void *hl_malloc( hl_alloc *a, int size );
HL_API void *hl_zalloc( hl_alloc *a, int size );
HL_API void hl_free( hl_alloc *a );

HL_API void hl_global_init( void *stack_top );
HL_API void hl_global_free();

// ----------------------- BUFFER --------------------------------------------------

typedef struct hl_buffer hl_buffer;

HL_API hl_buffer *hl_alloc_buffer();
HL_API void hl_buffer_val( hl_buffer *b, vdynamic *v );
HL_API void hl_buffer_char( hl_buffer *b, uchar c );
HL_API void hl_buffer_str( hl_buffer *b, const uchar *str );
HL_API void hl_buffer_cstr( hl_buffer *b, const char *str );
HL_API void hl_buffer_str_sub( hl_buffer *b, const uchar *str, int len );
HL_API int hl_buffer_length( hl_buffer *b );
HL_API uchar *hl_buffer_content( hl_buffer *b, int *len );
HL_API uchar *hl_to_string( vdynamic *v );
HL_API const uchar *hl_type_str( hl_type *t );

// ----------------------- FFI ------------------------------------------------------

// match GNU C++ mangling
#define TYPE_STR	"vcsifdbBDPOATR??X?N"

#undef  _VOID
#define _NO_ARG
#define _VOID						"v"
#define	_I8							"c"
#define _I16						"s"
#define _I32						"i"
#define _F32						"f"
#define _F64						"d"
#define _BOOL						"b"
#define _BYTES						"B"
#define _DYN						"D"
#define _FUN(t, args)				"P" args "_" t
#define _OBJ(fields)				"O" fields "_"
#define _ARR						"A"
#define _TYPE						"T"
#define _REF(t)						"R" t
#define _ABSTRACT(name)				"X" #name "_"
#undef _NULL
#define _NULL(t)					"N" t

#define _STRING						_OBJ(_BYTES _I32)

typedef struct {
	hl_type *t;
	uchar *bytes;
	int length;
} vstring;

#define DEFINE_PRIM(t,name,args)						DEFINE_PRIM_WITH_NAME(t,name,args,name)
#define _DEFINE_PRIM_WITH_NAME(t,name,args,realName)	C_FUNCTION_BEGIN EXPORT void *hlp_##realName( const char **sign ) { *sign = _FUN(t,args); return (void*)(&HL_NAME(name)); } C_FUNCTION_END

#ifndef HL_NAME
#	define HL_NAME(p)					p
#	ifdef HLDLL_EXPORTS
#		define HL_PRIM				EXPORT
#		undef DEFINE_PRIM
#		define DEFINE_PRIM(t,name,args)						_DEFINE_PRIM_WITH_NAME(t,hl_##name,args,name)
#		define DEFINE_PRIM_WITH_NAME						_DEFINE_PRIM_WITH_NAME
#	else
#		define HL_PRIM
#		define DEFINE_PRIM_WITH_NAME(t,name,args,realName)
#	endif
#else
#define	HL_PRIM						EXPORT
#define DEFINE_PRIM_WITH_NAME		_DEFINE_PRIM_WITH_NAME
#endif

// -------------- EXTRA ------------------------------------

#define hl_fatal(msg)			hl_fatal_error(msg,__FILE__,__LINE__)
#define hl_fatal1(msg,p0)		hl_fatal_fmt(__FILE__,__LINE__,msg,p0)
#define hl_fatal2(msg,p0,p1)	hl_fatal_fmt(__FILE__,__LINE__,msg,p0,p1)
#define hl_fatal3(msg,p0,p1,p2)	hl_fatal_fmt(__FILE__,__LINE__,msg,p0,p1,p2)
#define hl_fatal4(msg,p0,p1,p2,p3)	hl_fatal_fmt(__FILE__,__LINE__,msg,p0,p1,p2,p3)
HL_API void *hl_fatal_error( const char *msg, const char *file, int line );
HL_API void hl_fatal_fmt( const char *file, int line, const char *fmt, ...);
HL_API void hl_sys_init(void **args, int nargs);
HL_API void hl_setup_callbacks(void *sc, void *gw);

#include <setjmp.h>
typedef struct _hl_trap_ctx hl_trap_ctx;
struct _hl_trap_ctx {
	jmp_buf buf;
	hl_trap_ctx *prev;
};
HL_API hl_trap_ctx *hl_current_trap;
HL_API vdynamic *hl_current_exc;
#define hl_trap(ctx,r,label) { ctx.prev = hl_current_trap; hl_current_trap = &ctx; if( setjmp(ctx.buf) ) { r = hl_current_exc; goto label; } }
#define hl_endtrap(ctx)	hl_current_trap = ctx.prev

#endif