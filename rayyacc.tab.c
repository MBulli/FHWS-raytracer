
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
     WAVEFRONT = 272,
     VERTEX = 273,
     TEX = 274,
     PROPERTY = 275,
     AMBIENT = 276,
     DIFFUSE = 277,
     SPECULAR = 278,
     MIRROR = 279,
     TEXTURE = 280,
     REFRACTION = 281,
     GLOSSY = 282,
     OPACITY = 283,
     AMBIENCE = 284,
     BACKGROUND = 285,
     DIRLIGHT = 286,
     PTRLIGHT = 287,
     POSITION = 288,
     DIRECTION = 289,
     COLOR = 290,
     FOCAL_DISTANCE = 291,
     DOF_SAMPLES = 292,
     APERTURE_RADIUS = 293
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
	double glossy; int glossySamples;
	double opacity;
	char* texture;
	} prop;

struct {
	double dirx, diry, dirz, colr, colg, colb;
	} light;

int yylex();
extern void add_property(char* n,
						 double ar, double ag, double ab, 
						 double r, double g, double b,
						 double s, double shininess,
						 double m,
						 char* textureFilename,
						 double refraction, double refractionIndex,
						 double glossy, int glossySamples,
						 double opacity);

extern void add_quadric(char* n, double a, double b, double c, double d, double e, double f, double g, double h, double j, double k);
extern void add_sphere(char* n, double xm, double ym, double zm, double r);
extern void add_objekt(char* ns, char *np);
extern void add_wavefront(char *filename);

extern void add_dirlight(char* n, double dirx, double diry, double dirz, double colr, double colg, double colb);
extern void add_ptrlight(char* n, double posx, double posy, double posz, double colr, double colg, double colb);

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
#define YYLAST   183

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNRULES -- Number of states.  */
#define YYNSTATES  198

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
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
     112,   114,   116,   118,   120,   134,   142,   147,   148,   156,
     158,   161,   163,   168,   170,   173,   175,   176,   180,   182,
     184,   188,   193,   195,   198,   200,   201,   206,   208,   211,
     213,   224,   229,   234,   238,   241,   244,   248,   252,   255,
     257,   260,   262,   266,   268,   271,   273,   275,   277,   282,
     287,   292,   297,   302,   304,   306,   308,   310
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      40,     0,    -1,    44,    41,    47,    57,    61,    -1,    -1,
      42,    43,    -1,    43,    46,    -1,    -1,    44,    45,    -1,
      45,    -1,    48,    -1,    49,    -1,    50,    -1,    51,    -1,
      53,    -1,    56,    -1,    52,    -1,    59,    58,    60,    -1,
      -1,     6,   112,   112,    -1,    30,   109,   109,   109,    -1,
       7,   111,   111,   111,    -1,     8,   111,   111,   111,    -1,
       9,   111,   111,   111,    -1,    54,    -1,    55,    -1,    10,
     111,    -1,    11,   111,    -1,    12,   111,    -1,    29,   109,
     109,   109,    -1,    36,   111,    -1,    38,   111,    -1,    37,
     112,    -1,    -1,    -1,    -1,    -1,    62,    66,    63,    87,
      64,   101,    65,    98,    -1,    67,    -1,    67,    68,    -1,
      68,    -1,    69,    -1,    70,    -1,    72,    -1,    71,    -1,
      13,     5,    14,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,    -1,    13,     5,    16,   111,   111,   111,
     111,    -1,    13,     5,    17,     5,    -1,    -1,    13,     5,
      15,    73,    74,    84,    77,    -1,    75,    -1,    75,    76,
      -1,    76,    -1,    18,   111,   111,   111,    -1,    78,    -1,
      78,    79,    -1,    79,    -1,    -1,    15,    80,    81,    -1,
      82,    -1,    83,    -1,   112,   112,   112,    -1,   112,   112,
     112,   112,    -1,    85,    -1,    85,    86,    -1,    86,    -1,
      -1,    19,   112,   111,   111,    -1,    88,    -1,    88,    89,
      -1,    89,    -1,    20,     5,    90,    91,    92,    93,    94,
      95,    96,    97,    -1,    21,   110,   110,   110,    -1,    22,
     110,   110,   110,    -1,    23,   110,   111,    -1,    24,   110,
      -1,    25,     5,    -1,    26,   111,   111,    -1,    27,   111,
     112,    -1,    28,   111,    -1,    99,    -1,    99,   100,    -1,
     100,    -1,    13,     5,     5,    -1,   102,    -1,   102,   103,
      -1,   103,    -1,   104,    -1,   105,    -1,    31,     5,   106,
     108,    -1,    32,     5,   107,   108,    -1,    34,   111,   111,
     111,    -1,    33,   111,   111,   111,    -1,    35,   109,   109,
     109,    -1,   110,    -1,   111,    -1,     4,    -1,     3,    -1,
       3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   117,   117,   122,   122,   144,   145,   149,   150,   154,
     155,   159,   160,   161,   162,   163,   167,   168,   172,   179,
     188,   193,   198,   203,   204,   208,   213,   218,   223,   228,
     232,   236,   242,   246,   250,   254,   242,   261,   265,   266,
     270,   271,   272,   273,   277,   286,   294,   304,   303,   311,
     315,   316,   320,   325,   329,   330,   335,   334,   341,   342,
     345,   350,   367,   371,   372,   373,   377,   382,   386,   387,
     391,   400,   409,   418,   426,   433,   440,   448,   456,   462,
     466,   467,   471,   480,   484,   485,   489,   490,   493,   500,
     507,   515,   523,   533,   535,   558,   560,   564
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "FLOAT", "STRING",
  "RESOLUTION", "EYEPOINT", "LOOKAT", "UP", "FOVX", "FOVY", "ASPECT",
  "OBJECT", "QUADRIC", "POLY", "SPHERE", "WAVEFRONT", "VERTEX", "TEX",
  "PROPERTY", "AMBIENT", "DIFFUSE", "SPECULAR", "MIRROR", "TEXTURE",
  "REFRACTION", "GLOSSY", "OPACITY", "AMBIENCE", "BACKGROUND", "DIRLIGHT",
  "PTRLIGHT", "POSITION", "DIRECTION", "COLOR", "FOCAL_DISTANCE",
  "DOF_SAMPLES", "APERTURE_RADIUS", "$accept", "scene",
  "some_viewing_parameters", "$@1", "viewing_parameters",
  "picture_parameters", "picture_parameter", "viewing_parameter",
  "dof_parameter", "resolution", "background", "eyepoint", "lookat", "up",
  "fov", "fovx", "fovy", "aspect", "global_lighting", "focal_distance",
  "aperture_radius", "dof_samples", "geometry", "$@2", "$@3", "$@4", "$@5",
  "surface_section", "surfaces", "one_surface", "quadric_surface",
  "sphere_surface", "wavefront_surface", "polygon_surface", "$@6",
  "vertex_section", "vertices", "one_vertex", "polygon_section",
  "polygons", "one_polygon", "$@7", "indices", "triangle_indices",
  "rectangle_indices", "texture_map_section", "texture_maps",
  "one_texture_map", "property_section", "properties", "one_property",
  "ambient", "diffuse", "specular", "mirror", "texture", "refraction",
  "glossy", "opacity", "object_section", "objects", "one_object",
  "lighting_section", "lights", "one_light", "dir_light", "ptr_light",
  "direction", "position", "color", "colorVal", "zeroToOneVal", "realVal",
  "index", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    42,    41,    43,    43,    44,    44,    45,
      45,    46,    46,    46,    46,    46,    47,    47,    48,    49,
      50,    51,    52,    53,    53,    54,    55,    56,    57,    58,
      59,    60,    62,    63,    64,    65,    61,    66,    67,    67,
      68,    68,    68,    68,    69,    70,    71,    73,    72,    74,
      75,    75,    76,    77,    78,    78,    80,    79,    81,    81,
      82,    83,    84,    85,    85,    85,    86,    87,    88,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,    99,   100,   101,   102,   102,   103,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   111,   112
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     0,     2,     2,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     3,     4,
       4,     4,     4,     1,     1,     2,     2,     2,     4,     2,
       2,     2,     0,     0,     0,     0,     8,     1,     2,     1,
       1,     1,     1,     1,    13,     7,     4,     0,     7,     1,
       2,     1,     4,     1,     2,     1,     0,     3,     1,     1,
       3,     4,     1,     2,     1,     0,     4,     1,     2,     1,
      10,     4,     4,     3,     2,     2,     3,     3,     2,     1,
       2,     1,     3,     1,     2,     1,     1,     1,     4,     4,
       4,     4,     4,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     3,     8,     9,    10,    97,     0,
      96,    95,     0,    93,    94,     1,    17,     6,     7,    18,
       0,     0,     0,     0,     4,    19,    30,     0,    32,     0,
       0,     0,     0,     0,     0,     0,     0,     5,    11,    12,
      15,    13,    23,    24,    14,     0,     2,     0,    29,     0,
      16,     0,     0,     0,    25,    26,    27,     0,     0,    33,
      37,    39,    40,    41,    43,    42,    31,     0,     0,     0,
      28,     0,     0,    38,    20,    21,    22,     0,    47,     0,
       0,     0,    34,    67,    69,     0,     0,     0,    46,     0,
       0,    68,     0,     0,    65,    49,    51,     0,     0,     0,
       0,     0,    35,    83,    85,    86,    87,     0,     0,     0,
       0,    62,    64,    50,     0,     0,     0,     0,     0,     0,
       0,    84,     0,     0,     0,    56,    48,    53,    55,    63,
      45,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36,    79,    81,     0,    52,     0,     0,    54,    71,     0,
       0,     0,     0,     0,     0,    88,     0,    89,     0,    80,
       0,    66,    57,    58,    59,     0,    72,    73,    74,     0,
       0,     0,     0,     0,    82,     0,     0,    75,     0,     0,
      90,     0,    91,     0,    60,     0,     0,     0,    92,     0,
      61,    76,     0,     0,    70,    44,    77,    78
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,    16,    17,    24,     4,     5,    37,    22,     6,
       7,    38,    39,    40,    41,    42,    43,    44,    28,    30,
      23,    50,    46,    47,    72,    90,   120,    59,    60,    61,
      62,    63,    64,    65,    86,    94,    95,    96,   126,   127,
     128,   146,   162,   163,   164,   110,   111,   112,    82,    83,
      84,    99,   117,   134,   152,   170,   179,   187,   194,   140,
     141,   142,   102,   103,   104,   105,   106,   136,   138,   155,
      12,    13,    14,     9
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -96
static const yytype_int8 yypact[] =
{
      -4,     5,    19,    17,    -4,   -96,   -96,   -96,   -96,     5,
     -96,   -96,    19,   -96,   -96,   -96,   -19,   -96,   -96,   -96,
      19,    19,    -5,    -6,    71,   -96,   -96,    19,   -96,    19,
       2,    19,    19,    19,    19,    19,    19,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,   -96,    19,   -96,    14,   -96,     5,
     -96,    19,    19,    19,   -96,   -96,   -96,    19,    29,   -96,
      14,   -96,   -96,   -96,   -96,   -96,   -96,    19,    19,    19,
     -96,   -10,    15,   -96,   -96,   -96,   -96,    19,   -96,    19,
      36,    37,   -96,    15,   -96,    19,    26,    19,   -96,    24,
      -3,   -96,    19,    19,    27,    26,   -96,    19,    19,    28,
      46,    47,   -96,    -3,   -96,   -96,   -96,    19,    19,     5,
      38,    27,   -96,   -96,    19,    19,    19,    35,    30,    33,
      48,   -96,    19,    19,    19,   -96,   -96,    38,   -96,   -96,
     -96,    19,    19,    19,    39,    19,    25,    19,    25,    57,
     -96,    48,   -96,    19,   -96,    19,     5,   -96,   -96,    19,
      19,    19,    43,    19,    19,   -96,    19,   -96,    64,   -96,
      19,   -96,   -96,   -96,   -96,     5,   -96,   -96,   -96,    65,
      45,    19,    19,    19,   -96,    19,     5,   -96,    19,    49,
     -96,    19,   -96,    19,     5,    19,    19,    56,   -96,    19,
     -96,   -96,     5,    19,   -96,   -96,   -96,   -96
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -96,   -96,   -96,   -96,   -96,   -96,    70,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,    31,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,     0,   -96,   -96,
     -52,   -96,   -96,   -96,   -96,   -96,   -96,   -26,   -96,   -96,
       3,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   -51,   -96,   -96,   -14,   -96,   -96,   -96,   -96,   -46,
      -2,   -95,   -20,    -9
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      19,    26,     1,   115,    77,    78,    79,    80,     8,    48,
      20,    51,    52,    53,    54,    55,    56,    15,    25,    21,
     131,   132,    10,    11,    27,    45,     2,    58,   100,   101,
      29,    67,    68,    69,    71,    81,   148,   149,   150,    49,
      66,    88,    89,    57,    93,    98,   109,    74,    75,    76,
     116,   118,   119,   125,   166,    70,   168,    85,   133,    87,
     154,   139,   158,   151,   135,    92,   137,    97,   169,   174,
     177,   178,   107,   108,    18,   147,   186,   114,    31,    32,
      33,    34,    35,    36,   193,   129,    91,   122,   123,   121,
     159,    73,   157,     0,   130,   113,     0,     0,     0,     0,
     124,     0,   143,   144,   145,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   153,     0,   156,     0,     0,
       0,     0,     0,   160,     0,   161,     0,     0,     0,     0,
     167,     0,     0,   171,     0,     0,   173,   165,     0,     0,
     175,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   180,   172,   182,     0,   183,   176,     0,   185,     0,
       0,     0,     0,   189,     0,   191,   192,   184,     0,   195,
     181,     0,     0,   197,     0,   190,     0,     0,     0,   188,
       0,     0,     0,   196
};

static const yytype_int16 yycheck[] =
{
       9,    21,     6,    98,    14,    15,    16,    17,     3,    29,
      12,    31,    32,    33,    34,    35,    36,     0,    20,    38,
     115,   116,     3,     4,    29,    27,    30,    13,    31,    32,
      36,    51,    52,    53,     5,    20,   131,   132,   133,    37,
      49,     5,     5,    45,    18,    21,    19,    67,    68,    69,
      22,     5,     5,    15,   149,    57,   151,    77,    23,    79,
      35,    13,     5,    24,    34,    85,    33,    87,    25,     5,
       5,    26,    92,    93,     4,   127,    27,    97,     7,     8,
       9,    10,    11,    12,    28,   111,    83,   107,   108,   103,
     141,    60,   138,    -1,   114,    95,    -1,    -1,    -1,    -1,
     109,    -1,   122,   123,   124,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   135,    -1,   137,    -1,    -1,
      -1,    -1,    -1,   143,    -1,   145,    -1,    -1,    -1,    -1,
     150,    -1,    -1,   153,    -1,    -1,   156,   146,    -1,    -1,
     160,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   171,   154,   173,    -1,   175,   165,    -1,   178,    -1,
      -1,    -1,    -1,   183,    -1,   185,   186,   176,    -1,   189,
     172,    -1,    -1,   193,    -1,   184,    -1,    -1,    -1,   181,
      -1,    -1,    -1,   192
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    30,    40,    44,    45,    48,    49,     3,   112,
       3,     4,   109,   110,   111,     0,    41,    42,    45,   112,
     109,    38,    47,    59,    43,   109,   111,    29,    57,    36,
      58,     7,     8,     9,    10,    11,    12,    46,    50,    51,
      52,    53,    54,    55,    56,   109,    61,    62,   111,    37,
      60,   111,   111,   111,   111,   111,   111,   109,    13,    66,
      67,    68,    69,    70,    71,    72,   112,   111,   111,   111,
     109,     5,    63,    68,   111,   111,   111,    14,    15,    16,
      17,    20,    87,    88,    89,   111,    73,   111,     5,     5,
      64,    89,   111,    18,    74,    75,    76,   111,    21,    90,
      31,    32,   101,   102,   103,   104,   105,   111,   111,    19,
      84,    85,    86,    76,   111,   110,    22,    91,     5,     5,
      65,   103,   111,   111,   112,    15,    77,    78,    79,    86,
     111,   110,   110,    23,    92,    34,   106,    33,   107,    13,
      98,    99,   100,   111,   111,   111,    80,    79,   110,   110,
     110,    24,    93,   111,    35,   108,   111,   108,     5,   100,
     111,   111,    81,    82,    83,   112,   110,   111,   110,    25,
      94,   111,   109,   111,     5,   111,   112,     5,    26,    95,
     111,   109,   111,   111,   112,   111,    27,    96,   109,   111,
     112,   111,   111,    28,    97,   111,   112,   111
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

  case 44:

    {
		  add_quadric((yyvsp[(2) - (13)].stringval), (yyvsp[(4) - (13)].floatval), (yyvsp[(5) - (13)].floatval), (yyvsp[(6) - (13)].floatval), (yyvsp[(7) - (13)].floatval), (yyvsp[(8) - (13)].floatval), (yyvsp[(9) - (13)].floatval), (yyvsp[(10) - (13)].floatval), (yyvsp[(11) - (13)].floatval), (yyvsp[(12) - (13)].floatval), (yyvsp[(13) - (13)].floatval));
		  free((yyvsp[(2) - (13)].stringval));
      ;}
    break;

  case 45:

    {
		add_sphere((yyvsp[(2) - (7)].stringval), (yyvsp[(4) - (7)].floatval), (yyvsp[(5) - (7)].floatval), (yyvsp[(6) - (7)].floatval), (yyvsp[(7) - (7)].floatval));
		free((yyvsp[(2) - (7)].stringval));
	;}
    break;

  case 46:

    {
		add_wavefront((yyvsp[(4) - (4)].stringval));

		free((yyvsp[(2) - (4)].stringval));
		free((yyvsp[(4) - (4)].stringval));
	;}
    break;

  case 47:

    {	printf("object poly\n"); begin_poly_object((yyvsp[(2) - (3)].stringval)); free((yyvsp[(2) - (3)].stringval)); ;}
    break;

  case 48:

    { end_poly_object(); ;}
    break;

  case 52:

    { printf("vertex %f %f %f\n", (yyvsp[(2) - (4)].floatval), (yyvsp[(3) - (4)].floatval), (yyvsp[(4) - (4)].floatval)); add_poly_vertex((yyvsp[(2) - (4)].floatval), (yyvsp[(3) - (4)].floatval), (yyvsp[(4) - (4)].floatval)); ;}
    break;

  case 56:

    { printf("polygon"); ;}
    break;

  case 57:

    { printf("\n"); ;}
    break;

  case 60:

    { add_poly_triangle((yyvsp[(1) - (3)].intval), (yyvsp[(2) - (3)].intval), (yyvsp[(3) - (3)].intval));  ;}
    break;

  case 61:

    { add_poly_rectangle((yyvsp[(1) - (4)].intval), (yyvsp[(2) - (4)].intval), (yyvsp[(3) - (4)].intval), (yyvsp[(4) - (4)].intval)); ;}
    break;

  case 66:

    { printf("texture %d %f %f\n", (yyvsp[(2) - (4)].intval), (yyvsp[(3) - (4)].floatval), (yyvsp[(4) - (4)].floatval)); add_poly_texmap((yyvsp[(2) - (4)].intval), (yyvsp[(3) - (4)].floatval), (yyvsp[(4) - (4)].floatval)); ;}
    break;

  case 70:

    {
		add_property((yyvsp[(2) - (10)].stringval), prop.ar, prop.ag, prop.ab, prop.r, prop.g, prop.b, prop.specular, prop.specShininess, prop.mirror, prop.texture, prop.refraction, prop.refractionIndex, prop.glossy, prop.glossySamples, prop.opacity); 
		free((yyvsp[(2) - (10)].stringval));
		free(prop.texture);
	;}
    break;

  case 71:

    { 
		prop.ar = (yyvsp[(2) - (4)].floatval);
		prop.ag = (yyvsp[(3) - (4)].floatval);
		prop.ab = (yyvsp[(4) - (4)].floatval);
      ;}
    break;

  case 72:

    { 
		prop.r = (yyvsp[(2) - (4)].floatval);
		prop.g = (yyvsp[(3) - (4)].floatval);
		prop.b = (yyvsp[(4) - (4)].floatval);
      ;}
    break;

  case 73:

    { 
		prop.specular = (yyvsp[(2) - (3)].floatval);
		prop.specShininess = (yyvsp[(3) - (3)].floatval);
      ;}
    break;

  case 74:

    { 
		prop.mirror = (yyvsp[(2) - (2)].floatval);
      ;}
    break;

  case 75:

    {
			prop.texture = (yyvsp[(2) - (2)].stringval);
		;}
    break;

  case 76:

    {
		prop.refraction = (yyvsp[(2) - (3)].floatval);
		prop.refractionIndex = (yyvsp[(3) - (3)].floatval);
	  ;}
    break;

  case 77:

    {
		prop.glossy = (yyvsp[(2) - (3)].floatval);
		prop.glossySamples = (yyvsp[(3) - (3)].intval);
	  ;}
    break;

  case 78:

    {
		prop.opacity = (yyvsp[(2) - (2)].floatval);
	  ;}
    break;

  case 82:

    {
		add_objekt((yyvsp[(2) - (3)].stringval), (yyvsp[(3) - (3)].stringval));
		free((yyvsp[(2) - (3)].stringval));
		free((yyvsp[(3) - (3)].stringval));
      ;}
    break;

  case 88:

    {
		add_dirlight((yyvsp[(2) - (4)].stringval), light.dirx, light.diry, light.dirz, light.colr, light.colg, light.colb);
		free((yyvsp[(2) - (4)].stringval));
    ;}
    break;

  case 89:

    {
		add_ptrlight((yyvsp[(2) - (4)].stringval), light.dirx, light.diry, light.dirz, light.colr, light.colg, light.colb);
		free((yyvsp[(2) - (4)].stringval));
	;}
    break;

  case 90:

    {
		light.dirx = (yyvsp[(2) - (4)].floatval);
		light.diry = (yyvsp[(3) - (4)].floatval);
		light.dirz = (yyvsp[(4) - (4)].floatval);
    ;}
    break;

  case 91:

    {
		light.dirx = (yyvsp[(2) - (4)].floatval);
		light.diry = (yyvsp[(3) - (4)].floatval);
		light.dirz = (yyvsp[(4) - (4)].floatval);	
	;}
    break;

  case 92:

    {
		light.colr = (yyvsp[(2) - (4)].floatval);
		light.colg = (yyvsp[(3) - (4)].floatval);
		light.colb = (yyvsp[(4) - (4)].floatval);
    ;}
    break;

  case 94:

    {
	if ( (yyvsp[(1) - (1)].floatval) < 0.0 || (yyvsp[(1) - (1)].floatval) > 1.0 ) {
	    yyerror("value out of range (only 0 to 1 allowed)");
	} /* if */

	/* pass that value up the tree */
	(yyval.floatval) = (yyvsp[(1) - (1)].floatval);
    ;}
    break;

  case 95:

    { (yyval.floatval) = (yyvsp[(1) - (1)].floatval); ;}
    break;

  case 96:

    { (yyval.floatval) = (float) (yyvsp[(1) - (1)].intval); /* conversion from integers */ ;}
    break;

  case 97:

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



