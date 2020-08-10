/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_R_R_PARSER_H_INCLUDED
# define YY_R_R_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef R_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define R_DEBUG 1
#  else
#   define R_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define R_DEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined R_DEBUG */
#if R_DEBUG
extern int r_debug;
#endif

/* Token type.  */
#ifndef R_TOKENTYPE
# define R_TOKENTYPE
  enum r_tokentype
  {
    IP = 258,
    ADDRESS_LITERARY = 259,
    ADD = 260,
    DEL = 261,
    DEV = 262,
    STRING = 263,
    NUMBER = 264
  };
#endif

/* Value type.  */
#if ! defined R_STYPE && ! defined R_STYPE_IS_DECLARED
union R_STYPE
{
#line 43 "r_parser.y"

    char* str;
    int number;

#line 80 "r_parser.h"

};
typedef union R_STYPE R_STYPE;
# define R_STYPE_IS_TRIVIAL 1
# define R_STYPE_IS_DECLARED 1
#endif



int r_parse (struct r_ctx* ctx, void * scanner);

#endif /* !YY_R_R_PARSER_H_INCLUDED  */
