
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     FLOAT = 259,
     STRING = 260,
     RESOLUTION = 261,
     EYEPOINT = 262,
     LOOKAT = 263,
     UP = 264,
     FOVX = 265,
     FOVY = 266,
     ASPECT = 267,
     OBJECT = 268,
     QUADRIC = 269,
     POLY = 270,
     SPHERE = 271,
     VERTEX = 272,
     TEX = 273,
     PROPERTY = 274,
     AMBIENT = 275,
     DIFFUSE = 276,
     SPECULAR = 277,
     MIRROR = 278,
     TEXTURE = 279,
     REFRACTION = 280,
     AMBIENCE = 281,
     BACKGROUND = 282,
     LIGHT = 283,
     DIRECTION = 284,
     COLOR = 285,
     FOCAL_DISTANCE = 286,
     DOF_SAMPLES = 287,
     APERTURE_RADIUS = 288
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{


    int intval;
    double floatval;
    char *stringval;



} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Fix compatibility warnings
#pragma warning(disable: 4996)

// Fix linker warning
extern __declspec(dllimport) void *malloc(size_t);
extern __declspec(dllimport) void free(void*);
#define YYMALLOC
#define YYFREE

// so that we can keep track if a particular parameter appeared in our input or not
static int resolution_seen = 0;
static int aspect_seen = 0;
static int up_seen = 0;
static int eyepoint_seen = 0;
static int lookat_seen = 0;

static int linenum = 1;
static int yywarn(char *s)
{
    fprintf(stderr,"warning: line %d: %s\n", linenum, s);
    return 0;
}

static int yyerror(char *s)
{
    fprintf(stderr,"error: line %d: %s\n", linenum, s);
	return 1;
    //exit(1);
}

struct {
	double ar,ag,ab, r, g, b, specular, specShininess, mirror, refraction, refractionIndex;
	char* texture;
	} prop;

struct {
	double dirx, diry, dirz, colr, colg, colb;
	} light;

int yylex();
extern void add_quadric(char *n, double a, double b, double c, double d, double e, double f, double g, double h, double j, double k);
extern void add_sphere(char *n, double xm, double ym, double zm, double r);
extern void add_property(char *n, double ar, double ag, double ab, double r, double g, double b, double s, double shininess, double m, char* textureFilename, double refraction, double refractionIndex);
extern void add_objekt(char *ns, char *np);
extern void add_light(char *n, double dirx, double diry, double dirz, double colr, double colg, double colb);

extern void begin_poly_object(char *n);
extern void add_poly_vertex(double x, double y, double z);
extern void add_poly_triangle(int i0, int i1, int i2);
extern void add_poly_rectangle(int i0, int i1, int i2, int i3);
extern void add_poly_texmap(int index, double u, double v);
extern void end_poly_object();

extern void set_output_resolution(int x, int y);
extern void set_scene_background(double r, double g, double b);
extern void set_eyepoint(double x, double y, double z);
extern void set_lookat(double x, double y, double z);
extern void set_up(double x, double y, double z);
extern void set_fovx(double fovxInDeg);
extern void set_fovy(double fovyInDeg);
extern void set_aspect(double a);
extern void set_global_ambience(double r, double g, double b);

extern void set_apertureRadius(double r);
extern void set_focalDistance(double d);
extern void set_dofSamples(int s);



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   171

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  68
/* YYNRULES -- Number of rules.  */
#define YYNRULES  89
/* YYNRULES -- Number of states.  */
#define YYNSTATES  178

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     9,    10,    13,    16,    17,    20,    22,
      24,    26,    28,    30,    32,    34,    36,    40,    41,    45,
      50,    55,    60,    65,    67,    69,    72,    75,    78,    83,
      86,    89,    92,    93,    94,    95,    96,   105,   107,   110,
     112,   114,   116,   118,   132,   140,   141,   149,   151,   154,
     156,   161,   163,   166,   168,   169,   173,   175,   177,   181,
     186,   188,   191,   193,   194,   199,   201,   204,   206,   215,
     220,   225,   229,   232,   235,   239,   241,   244,   246,   250,
     252,   255,   257,   262,   267,   272,   274,   276,   278,   280
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      35,     0,    -1,    39,    36,    42,    52,    56,    -1,    -1,
      37,    38,    -1,    38,    41,    -1,    -1,    39,    40,    -1,
      40,    -1,    43,    -1,    44,    -1,    45,    -1,    46,    -1,
      48,    -1,    51,    -1,    47,    -1,    54,    53,    55,    -1,
      -1,     6,   101,   101,    -1,    27,    98,    98,    98,    -1,
       7,   100,   100,   100,    -1,     8,   100,   100,   100,    -1,
       9,   100,   100,   100,    -1,    49,    -1,    50,    -1,    10,
     100,    -1,    11,   100,    -1,    12,   100,    -1,    26,    98,
      98,    98,    -1,    31,   100,    -1,    33,   100,    -1,    32,
     101,    -1,    -1,    -1,    -1,    -1,    57,    61,    58,    81,
      59,    93,    60,    90,    -1,    62,    -1,    62,    63,    -1,
      63,    -1,    64,    -1,    65,    -1,    66,    -1,    13,     5,
      14,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,    -1,    13,     5,    16,   100,   100,   100,   100,    -1,
      -1,    13,     5,    15,    67,    68,    78,    71,    -1,    69,
      -1,    69,    70,    -1,    70,    -1,    17,   100,   100,   100,
      -1,    72,    -1,    72,    73,    -1,    73,    -1,    -1,    15,
      74,    75,    -1,    76,    -1,    77,    -1,   101,   101,   101,
      -1,   101,   101,   101,   101,    -1,    79,    -1,    79,    80,
      -1,    80,    -1,    -1,    18,   101,   100,   100,    -1,    82,
      -1,    82,    83,    -1,    83,    -1,    19,     5,    84,    85,
      86,    87,    88,    89,    -1,    20,    99,    99,    99,    -1,
      21,    99,    99,    99,    -1,    22,    99,   100,    -1,    23,
      99,    -1,    24,     5,    -1,    25,   100,   100,    -1,    91,
      -1,    91,    92,    -1,    92,    -1,    13,     5,     5,    -1,
      94,    -1,    94,    95,    -1,    95,    -1,    28,     5,    96,
      97,    -1,    29,   100,   100,   100,    -1,    30,    98,    98,
      98,    -1,    99,    -1,   100,    -1,     4,    -1,     3,    -1,
       3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   103,   103,   108,   108,   130,   131,   135,   136,   140,
     141,   145,   146,   147,   148,   149,   153,   154,   158,   165,
     174,   179,   184,   189,   190,   194,   199,   204,   209,   214,
     218,   222,   228,   232,   236,   240,   228,   247,   251,   252,
     256,   257,   258,   262,   271,   280,   279,   287,   291,   292,
     296,   301,   305,   306,   311,   310,   317,   318,   321,   326,
     343,   347,   348,   349,   353,   358,   362,   363,   367,   376,
     385,   394,   402,   409,   416,   424,   428,   429,   433,   442,
     446,   447,   450,   457,   465,   475,   477,   500,   502,   506
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "FLOAT", "STRING",
  "RESOLUTION", "EYEPOINT", "LOOKAT", "UP", "FOVX", "FOVY", "ASPECT",
  "OBJECT", "QUADRIC", "POLY", "SPHERE", "VERTEX", "TEX", "PROPERTY",
  "AMBIENT", "DIFFUSE", "SPECULAR", "MIRROR", "TEXTURE", "REFRACTION",
  "AMBIENCE", "BACKGROUND", "LIGHT", "DIRECTION", "COLOR",
  "FOCAL_DISTANCE", "DOF_SAMPLES", "APERTURE_RADIUS", "$accept", "scene",
  "some_viewing_parameters", "$@1", "viewing_parameters",
  "picture_parameters", "picture_parameter", "viewing_parameter",
  "dof_parameter", "resolution", "background", "eyepoint", "lookat", "up",
  "fov", "fovx", "fovy", "aspect", "global_lighting", "focal_distance",
  "aperture_radius", "dof_samples", "geometry", "$@2", "$@3", "$@4", "$@5",
  "surface_section", "surfaces", "one_surface", "quadric_surface",
  "sphere_surface", "polygon_surface", "$@6", "vertex_section", "vertices",
  "one_vertex", "polygon_section", "polygons", "one_polygon", "$@7",
  "indices", "triangle_indices", "rectangle_indices",
  "texture_map_section", "texture_maps", "one_texture_map",
  "property_section", "properties", "one_property", "ambient", "diffuse",
  "specular", "mirror", "texture", "refraction", "object_section",
  "objects", "one_object", "lighting_section", "lights", "one_light",
  "direction", "color", "colorVal", "zeroToOneVal", "realVal", "index", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    34,    35,    37,    36,    38,    38,    39,    39,    40,
      40,    41,    41,    41,    41,    41,    42,    42,    43,    44,
      45,    46,    47,    48,    48,    49,    50,    51,    52,    53,
      54,    55,    57,    58,    59,    60,    56,    61,    62,    62,
      63,    63,    63,    64,    65,    67,    66,    68,    69,    69,
      70,    71,    72,    72,    74,    73,    75,    75,    76,    77,
      78,    79,    79,    79,    80,    81,    82,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    91,    92,    93,
      94,    94,    95,    96,    97,    98,    99,   100,   100,   101
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     0,     2,     2,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     3,     4,
       4,     4,     4,     1,     1,     2,     2,     2,     4,     2,
       2,     2,     0,     0,     0,     0,     8,     1,     2,     1,
       1,     1,     1,    13,     7,     0,     7,     1,     2,     1,
       4,     1,     2,     1,     0,     3,     1,     1,     3,     4,
       1,     2,     1,     0,     4,     1,     2,     1,     8,     4,
       4,     3,     2,     2,     3,     1,     2,     1,     3,     1,
       2,     1,     4,     4,     4,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     3,     8,     9,    10,    89,     0,
      88,    87,     0,    85,    86,     1,    17,     6,     7,    18,
       0,     0,     0,     0,     4,    19,    30,     0,    32,     0,
       0,     0,     0,     0,     0,     0,     0,     5,    11,    12,
      15,    13,    23,    24,    14,     0,     2,     0,    29,     0,
      16,     0,     0,     0,    25,    26,    27,     0,     0,    33,
      37,    39,    40,    41,    42,    31,     0,     0,     0,    28,
       0,     0,    38,    20,    21,    22,     0,    45,     0,     0,
      34,    65,    67,     0,     0,     0,     0,     0,    66,     0,
       0,    63,    47,    49,     0,     0,     0,     0,    35,    79,
      81,     0,     0,     0,     0,    60,    62,    48,     0,     0,
       0,     0,     0,     0,    80,     0,     0,     0,    54,    46,
      51,    53,    61,    44,     0,     0,     0,     0,     0,     0,
       0,    36,    75,    77,     0,    50,     0,     0,    52,    69,
       0,     0,     0,     0,     0,     0,    82,     0,    76,     0,
      64,    55,    56,    57,     0,    70,    71,    72,     0,     0,
       0,     0,    78,     0,     0,    73,     0,    68,    83,     0,
       0,    58,     0,    84,     0,    59,    74,    43
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,    16,    17,    24,     4,     5,    37,    22,     6,
       7,    38,    39,    40,    41,    42,    43,    44,    28,    30,
      23,    50,    46,    47,    71,    87,   113,    59,    60,    61,
      62,    63,    64,    84,    91,    92,    93,   119,   120,   121,
     137,   151,   152,   153,   104,   105,   106,    80,    81,    82,
      96,   111,   127,   143,   159,   167,   131,   132,   133,    98,
      99,   100,   129,   146,    12,    13,    14,     9
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -90
static const yytype_int8 yypact[] =
{
      -4,     2,     0,     7,    -4,   -90,   -90,   -90,   -90,     2,
     -90,   -90,     0,   -90,   -90,   -90,   -25,   -90,   -90,   -90,
       0,     0,    -7,   -14,     3,   -90,   -90,     0,   -90,     0,
     -10,     0,     0,     0,     0,     0,     0,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,     0,   -90,    11,   -90,     2,
     -90,     0,     0,     0,   -90,   -90,   -90,     0,    20,   -90,
      11,   -90,   -90,   -90,   -90,   -90,     0,     0,     0,   -90,
      27,     8,   -90,   -90,   -90,   -90,     0,   -90,     0,    33,
     -90,     8,   -90,     0,    22,     0,    24,    17,   -90,     0,
       0,    29,    22,   -90,     0,     0,    31,    49,   -90,    17,
     -90,     0,     0,     2,    40,    29,   -90,   -90,     0,     0,
       0,    34,    28,    45,   -90,     0,     0,     0,   -90,   -90,
      40,   -90,   -90,   -90,     0,     0,     0,    36,     0,    30,
      56,   -90,    45,   -90,     0,   -90,     0,     2,   -90,   -90,
       0,     0,     0,    38,     0,     0,   -90,    61,   -90,     0,
     -90,   -90,   -90,   -90,     2,   -90,   -90,   -90,    62,    43,
       0,     0,   -90,     0,     2,   -90,     0,   -90,   -90,     0,
       0,     2,     0,   -90,     0,   -90,   -90,   -90
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -90,   -90,   -90,   -90,   -90,   -90,    65,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,    10,
     -90,   -90,   -90,   -90,   -90,   -90,   -21,   -90,   -90,   -48,
     -90,   -90,   -90,   -90,   -90,   -90,   -31,   -90,   -90,    -5,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -55,   -90,
     -90,   -20,   -90,   -90,   -11,   -89,    -3,    -9
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      19,    20,     1,    10,    11,     8,   109,    15,    21,    25,
      31,    32,    33,    34,    35,    36,    45,    29,    26,    27,
     124,   125,    49,     2,    58,    70,    48,    79,    51,    52,
      53,    54,    55,    56,    57,   139,   140,   141,    86,    90,
      65,    76,    77,    78,    95,    97,    69,   103,    66,    67,
      68,   155,   110,   157,   112,   118,   126,   128,   130,   142,
     145,   147,   158,    73,    74,    75,   162,   165,   166,    18,
      72,   107,   138,    83,   122,    85,    88,   148,     0,   114,
      89,     0,    94,     0,     0,     0,   101,   102,     0,     0,
       0,   108,     0,     0,   117,     0,     0,     0,   115,   116,
       0,     0,     0,     0,     0,   123,     0,     0,     0,     0,
       0,     0,   134,   135,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   144,     0,     0,   154,     0,
       0,   149,     0,   150,   161,     0,     0,     0,   156,     0,
       0,   160,     0,     0,     0,   164,   163,     0,     0,     0,
     169,     0,     0,     0,     0,   171,     0,   168,   173,     0,
     170,     0,   175,   172,     0,     0,     0,   174,     0,   176,
       0,   177
};

static const yytype_int16 yycheck[] =
{
       9,    12,     6,     3,     4,     3,    95,     0,    33,    20,
       7,     8,     9,    10,    11,    12,    27,    31,    21,    26,
     109,   110,    32,    27,    13,     5,    29,    19,    31,    32,
      33,    34,    35,    36,    45,   124,   125,   126,     5,    17,
      49,    14,    15,    16,    20,    28,    57,    18,    51,    52,
      53,   140,    21,   142,     5,    15,    22,    29,    13,    23,
      30,     5,    24,    66,    67,    68,     5,     5,    25,     4,
      60,    92,   120,    76,   105,    78,    81,   132,    -1,    99,
      83,    -1,    85,    -1,    -1,    -1,    89,    90,    -1,    -1,
      -1,    94,    -1,    -1,   103,    -1,    -1,    -1,   101,   102,
      -1,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,
      -1,    -1,   115,   116,   117,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   128,    -1,    -1,   137,    -1,
      -1,   134,    -1,   136,   145,    -1,    -1,    -1,   141,    -1,
      -1,   144,    -1,    -1,    -1,   154,   149,    -1,    -1,    -1,
     161,    -1,    -1,    -1,    -1,   164,    -1,   160,   169,    -1,
     163,    -1,   171,   166,    -1,    -1,    -1,   170,    -1,   172,
      -1,   174
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    27,    35,    39,    40,    43,    44,     3,   101,
       3,     4,    98,    99,   100,     0,    36,    37,    40,   101,
      98,    33,    42,    54,    38,    98,   100,    26,    52,    31,
      53,     7,     8,     9,    10,    11,    12,    41,    45,    46,
      47,    48,    49,    50,    51,    98,    56,    57,   100,    32,
      55,   100,   100,   100,   100,   100,   100,    98,    13,    61,
      62,    63,    64,    65,    66,   101,   100,   100,   100,    98,
       5,    58,    63,   100,   100,   100,    14,    15,    16,    19,
      81,    82,    83,   100,    67,   100,     5,    59,    83,   100,
      17,    68,    69,    70,   100,    20,    84,    28,    93,    94,
      95,   100,   100,    18,    78,    79,    80,    70,   100,    99,
      21,    85,     5,    60,    95,   100,   100,   101,    15,    71,
      72,    73,    80,   100,    99,    99,    22,    86,    29,    96,
      13,    90,    91,    92,   100,   100,   100,    74,    73,    99,
      99,    99,    23,    87,   100,    30,    97,     5,    92,   100,
     100,    75,    76,    77,   101,    99,   100,    99,    24,    88,
     100,    98,     5,   100,   101,     5,    25,    89,   100,    98,
     100,   101,   100,    98,   100,   101,   100,   100
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:

    {
	fprintf(stderr,"processing viewing parameters...\n");
      ;}
    break;

  case 4:

    {
	if (!lookat_seen)
	  yywarn("LOOKAT missing from viewing parameters");
	if (!up_seen)
	  yywarn("UP missing from viewing parameters");
	if (!aspect_seen)
	  yywarn("ASPECT missing from viewing parameters");
	if (!eyepoint_seen)
	  yywarn("EYEPOINT missing from viewing parameters");
	if (!resolution_seen)
	  yywarn("RESOLUTION missing from viewing parameters");
      ;}
    break;

  case 18:

    { 
		printf("resolution %d %d\n", (yyvsp[(2) - (3)].intval), (yyvsp[(3) - (3)].intval) ); resolution_seen++; set_output_resolution((yyvsp[(2) - (3)].intval), (yyvsp[(3) - (3)].intval));
	  ;}
    break;

  case 19:

    { 
		printf("background %f %f %f\n", (yyvsp[(2) - (4)].floatval), (yyvsp[(3) - (4)].floatval), (yyvsp[(4) - (4)].floatval)); 
		set_scene_background((yyvsp[(2) - (4)].floatval), (yyvsp[(3) - (4)].floatval), (yyvsp[(4) - (4)].floatval))
	  ;}
    break;

  case 20:

    { printf("eyepoint %f %f %f\n", (yyvsp[(2) - (4)].floatval), (yyvsp[(3) - (4)].floatval), (yyvsp[(4) - (4)].floatval) ); eyepoint_seen++;  set_eyepoint((yyvsp[(2) - (4)].floatval), (yyvsp[(3) - (4)].floatval), (yyvsp[(4) - (4)].floatval)); ;}
    break;

  case 21:

    { printf("lookat %f %f %f\n", (yyvsp[(2) - (4)].floatval), (yyvsp[(3) - (4)].floatval), (yyvsp[(4) - (4)].floatval) ); lookat_seen++; set_lookat((yyvsp[(2) - (4)].floatval), (yyvsp[(3) - (4)].floatval), (yyvsp[(4) - (4)].floatval)); ;}
    break;

  case 22:

    { printf("up %f %f %f\n", (yyvsp[(2) - (4)].floatval), (yyvsp[(3) - (4)].floatval), (yyvsp[(4) - (4)].floatval)); up_seen++; set_up((yyvsp[(2) - (4)].floatval), (yyvsp[(3) - (4)].floatval), (yyvsp[(4) - (4)].floatval)); ;}
    break;

  case 25:

    { printf("fovx %f\n", (yyvsp[(2) - (2)].floatval)); set_fovx((yyvsp[(2) - (2)].floatval)); ;}
    break;

  case 26:

    { printf("fovy %f\n", (yyvsp[(2) - (2)].floatval)); set_fovy((yyvsp[(2) - (2)].floatval)); ;}
    break;

  case 27:

    { printf("aspect %f\n", (yyvsp[(2) - (2)].floatval) ); aspect_seen++; set_aspect((yyvsp[(2) - (2)].floatval)); ;}
    break;

  case 28:

    { printf("ambience %f %f %f\n", (yyvsp[(2) - (4)].floatval), (yyvsp[(3) - (4)].floatval), (yyvsp[(4) - (4)].floatval));  set_global_ambience((yyvsp[(2) - (4)].floatval), (yyvsp[(3) - (4)].floatval), (yyvsp[(4) - (4)].floatval)); ;}
    break;

  case 29:

    { set_focalDistance((yyvsp[(2) - (2)].floatval)); ;}
    break;

  case 30:

    { set_apertureRadius((yyvsp[(2) - (2)].floatval));	;}
    break;

  case 31:

    { set_dofSamples((yyvsp[(2) - (2)].intval)); ;}
    break;

  case 32:

    {
	fprintf(stderr, "processing surfaces...\n");
      ;}
    break;

  case 33:

    {
	fprintf(stderr, "processing properties...\n");
      ;}
    break;

  case 34:

    {
	fprintf(stderr, "processing lighting...\n");
      ;}
    break;

  case 35:

    {
	fprintf(stderr, "processing objects...\n");
      ;}
    break;

  case 43:

    {
		  add_quadric((yyvsp[(2) - (13)].stringval), (yyvsp[(4) - (13)].floatval), (yyvsp[(5) - (13)].floatval), (yyvsp[(6) - (13)].floatval), (yyvsp[(7) - (13)].floatval), (yyvsp[(8) - (13)].floatval), (yyvsp[(9) - (13)].floatval), (yyvsp[(10) - (13)].floatval), (yyvsp[(11) - (13)].floatval), (yyvsp[(12) - (13)].floatval), (yyvsp[(13) - (13)].floatval));
		  free((yyvsp[(2) - (13)].stringval));
      ;}
    break;

  case 44:

    {
		add_sphere((yyvsp[(2) - (7)].stringval), (yyvsp[(4) - (7)].floatval), (yyvsp[(5) - (7)].floatval), (yyvsp[(6) - (7)].floatval), (yyvsp[(7) - (7)].floatval));
		free((yyvsp[(2) - (7)].stringval));
	;}
    break;

  case 45:

    {	printf("object poly\n"); begin_poly_object((yyvsp[(2) - (3)].stringval)); free((yyvsp[(2) - (3)].stringval)); ;}
    break;

  case 46:

    { end_poly_object(); ;}
    break;

  case 50:

    { printf("vertex %f %f %f\n", (yyvsp[(2) - (4)].floatval), (yyvsp[(3) - (4)].floatval), (yyvsp[(4) - (4)].floatval)); add_poly_vertex((yyvsp[(2) - (4)].floatval), (yyvsp[(3) - (4)].floatval), (yyvsp[(4) - (4)].floatval)); ;}
    break;

  case 54:

    { printf("polygon"); ;}
    break;

  case 55:

    { printf("\n"); ;}
    break;

  case 58:

    { add_poly_triangle((yyvsp[(1) - (3)].intval), (yyvsp[(2) - (3)].intval), (yyvsp[(3) - (3)].intval));  ;}
    break;

  case 59:

    { add_poly_rectangle((yyvsp[(1) - (4)].intval), (yyvsp[(2) - (4)].intval), (yyvsp[(3) - (4)].intval), (yyvsp[(4) - (4)].intval)); ;}
    break;

  case 64:

    { printf("texture %d %f %f\n", (yyvsp[(2) - (4)].intval), (yyvsp[(3) - (4)].floatval), (yyvsp[(4) - (4)].floatval)); add_poly_texmap((yyvsp[(2) - (4)].intval), (yyvsp[(3) - (4)].floatval), (yyvsp[(4) - (4)].floatval)); ;}
    break;

  case 68:

    {
		add_property((yyvsp[(2) - (8)].stringval), prop.ar, prop.ag, prop.ab, prop.r, prop.g, prop.b, prop.specular, prop.specShininess, prop.mirror, prop.texture, prop.refraction, prop.refractionIndex); 
		free((yyvsp[(2) - (8)].stringval));
		free(prop.texture);
	;}
    break;

  case 69:

    { 
		prop.ar = (yyvsp[(2) - (4)].floatval);
		prop.ag = (yyvsp[(3) - (4)].floatval);
		prop.ab = (yyvsp[(4) - (4)].floatval);
      ;}
    break;

  case 70:

    { 
		prop.r = (yyvsp[(2) - (4)].floatval);
		prop.g = (yyvsp[(3) - (4)].floatval);
		prop.b = (yyvsp[(4) - (4)].floatval);
      ;}
    break;

  case 71:

    { 
		prop.specular = (yyvsp[(2) - (3)].floatval);
		prop.specShininess = (yyvsp[(3) - (3)].floatval);
      ;}
    break;

  case 72:

    { 
		prop.mirror = (yyvsp[(2) - (2)].floatval);
      ;}
    break;

  case 73:

    {
			prop.texture = (yyvsp[(2) - (2)].stringval);
		;}
    break;

  case 74:

    {
		prop.refraction = (yyvsp[(2) - (3)].floatval);
		prop.refractionIndex = (yyvsp[(3) - (3)].floatval);
	  ;}
    break;

  case 78:

    {
		add_objekt((yyvsp[(2) - (3)].stringval), (yyvsp[(3) - (3)].stringval));
		free((yyvsp[(2) - (3)].stringval));
		free((yyvsp[(3) - (3)].stringval));
      ;}
    break;

  case 82:

    {
		add_light((yyvsp[(2) - (4)].stringval), light.dirx, light.diry, light.dirz, light.colr, light.colg, light.colb);
		free((yyvsp[(2) - (4)].stringval));  
    ;}
    break;

  case 83:

    {
		light.dirx = (yyvsp[(2) - (4)].floatval);
		light.diry = (yyvsp[(3) - (4)].floatval);
		light.dirz = (yyvsp[(4) - (4)].floatval);
    ;}
    break;

  case 84:

    {
		light.colr = (yyvsp[(2) - (4)].floatval);
		light.colg = (yyvsp[(3) - (4)].floatval);
		light.colb = (yyvsp[(4) - (4)].floatval);
    ;}
    break;

  case 86:

    {
	if ( (yyvsp[(1) - (1)].floatval) < 0.0 || (yyvsp[(1) - (1)].floatval) > 1.0 ) {
	    yyerror("value out of range (only 0 to 1 allowed)");
	} /* if */

	/* pass that value up the tree */
	(yyval.floatval) = (yyvsp[(1) - (1)].floatval);
    ;}
    break;

  case 87:

    { (yyval.floatval) = (yyvsp[(1) - (1)].floatval); ;}
    break;

  case 88:

    { (yyval.floatval) = (float) (yyvsp[(1) - (1)].intval); /* conversion from integers */ ;}
    break;

  case 89:

    {
    	if ( (yyvsp[(1) - (1)].intval) < 1 ) {
	    yyerror("index out of range (only 1 or more allowed)");
	} /* if */

	/* pass that value up the tree */
	(yyval.intval) = (yyvsp[(1) - (1)].intval);
      ;}
    break;



      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}





#include "lex.yy.c"



