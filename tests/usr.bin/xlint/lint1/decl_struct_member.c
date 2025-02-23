/*	$NetBSD: decl_struct_member.c,v 1.9 2021/07/15 21:00:05 rillig Exp $	*/
# 3 "decl_struct_member.c"

struct multi_attributes {
	__attribute__((deprecated))
	__attribute__((deprecated))
	__attribute__((deprecated))
	int deprecated;
};

struct cover_begin_type_noclass_declspecs {
	int m1;
	__attribute__((deprecated)) int m2;
	const int m3;
	int const m4;
	int const long m5;
	int __attribute__((deprecated)) m6;
};

typedef int number;

struct cover_begin_type_typespec {
	int m1;
	number m2;
};

struct cover_begin_type_noclass_declmods {
	const m1;
	const volatile m2;
};

/* cover struct_or_union_specifier: struct_or_union error */
/* expect+1: error: syntax error 'goto' [249] */
struct goto {
	/* expect+1: error: illegal type combination [4] */
	int member;
	/* expect+1: error: syntax error '}' [249] */
};
/* expect-1: warning: empty declaration [0] */

/*
 * Before cgram.y 1.228 from 2021-06-19, lint ran into an assertion failure:
 *
 * "is_struct_or_union(dcs->d_type->t_tspec)" at cgram.y:846
 */
struct {
	char;			/* expect: syntax error 'unnamed member' */
};

struct cover_notype_struct_declarators {
	const a, b;
};

struct cover_notype_struct_declarator_bit_field {
	const a: 3, : 0, b: 4;
	const : 0;
};

/*
 * Before decl.c 1.188 from 2021-06-20, lint ran into a segmentation fault.
 */
struct {
	char a(_)0		/* expect: syntax error '0' */
}
/*
 * FIXME: adding a semicolon here triggers another assertion:
 *
 * assertion "t == NOTSPEC" failed in end_type at decl.c:774
 */
/* expect+1: cannot recover from previous errors */
