/******************************************************************************/
/*        Grammatik Raytracer-Beschreibungsfile                               */
/******************************************************************************/

%union
{
    int intval;
    double floatval;
    char *stringval;
}

%{
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
	double dirx, diry, dirz;
	double posx, posy, posz;
	double colr, colg, colb;
	double radius;
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
extern void add_circle_area_light(char* n, double posx, double posy, double posz, double dirx, double diry, double dirz, double radius, double colr, double colg, double colb);

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
%}



%type <intval> index
%type <floatval> colorVal realVal angleVal zeroToOneVal

%token <intval> INTEGER
%token <floatval> FLOAT
%token <stringval> STRING
%token RESOLUTION EYEPOINT LOOKAT UP FOVX FOVY ASPECT
%token OBJECT QUADRIC POLY SPHERE WAVEFRONT
%token VERTEX TEX
%token PROPERTY AMBIENT DIFFUSE SPECULAR MIRROR TEXTURE REFRACTION GLOSSY OPACITY
%token AMBIENCE BACKGROUND
%token DIRLIGHT PTRLIGHT CIRCLEAREALIGHT POSITION DIRECTION RADIUS COLOR
%token FOCAL_DISTANCE DOF_SAMPLES APERTURE_RADIUS

%%

scene 
    : picture_parameters  some_viewing_parameters dof_parameter global_lighting  geometry
    ;

some_viewing_parameters
    :
      {
	fprintf(stderr,"processing viewing parameters...\n");
      }
    viewing_parameters
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
      }
    ;


/* the following allows you to specify the viewing parameters in any order */

viewing_parameters 
    : viewing_parameters viewing_parameter
    | /* empty */
    ;

picture_parameters
    : picture_parameters picture_parameter
    | picture_parameter 
    ;

picture_parameter
    : resolution
    | background
    ;

viewing_parameter
    : eyepoint
    | lookat
    | fov
    | aspect
    | up
    ;

dof_parameter
	: aperture_radius focal_distance dof_samples
	| /* epsillon */
	;

resolution
    : RESOLUTION index index
      { 
		printf("resolution %d %d\n", $2, $3 ); resolution_seen++; set_output_resolution($2, $3);
	  }
    ;

background
    : BACKGROUND colorVal colorVal colorVal
      { 
		printf("background %f %f %f\n", $2, $3, $4); 
		set_scene_background($2, $3, $4)
	  }
    ;


eyepoint
    : EYEPOINT realVal realVal realVal
      { printf("eyepoint %f %f %f\n", $2, $3, $4 ); eyepoint_seen++;  set_eyepoint($2, $3, $4); }
    ;

lookat
    : LOOKAT realVal realVal realVal
      { printf("lookat %f %f %f\n", $2, $3, $4 ); lookat_seen++; set_lookat($2, $3, $4); }
    ;

up
    : UP realVal realVal realVal
      { printf("up %f %f %f\n", $2, $3, $4); up_seen++; set_up($2, $3, $4); }
    ;

fov
	: fovx 
	| fovy
	;

fovx
    : FOVX realVal
      { printf("fovx %f\n", $2); set_fovx($2); }
    ;

fovy
    : FOVY realVal
      { printf("fovy %f\n", $2); set_fovy($2); }
    ;

aspect
    : ASPECT realVal
      { printf("aspect %f\n", $2 ); aspect_seen++; set_aspect($2); }
    ;

global_lighting
    : AMBIENCE colorVal colorVal colorVal
      { printf("ambience %f %f %f\n", $2, $3, $4);  set_global_ambience($2, $3, $4); }
    ;

focal_distance
	: FOCAL_DISTANCE realVal { set_focalDistance($2); }
	;
	
aperture_radius
	: APERTURE_RADIUS realVal { set_apertureRadius($2);	}
	;
	
dof_samples
	: DOF_SAMPLES index	{ set_dofSamples($2); }
	;
	

geometry 
    : 
      {
	fprintf(stderr, "processing surfaces...\n");
      }
    surface_section 
      {
	fprintf(stderr, "processing properties...\n");
      }
    property_section 
      {
	fprintf(stderr, "processing lighting...\n");
      }
    lighting_section
      {
	fprintf(stderr, "processing objects...\n");
      }
    object_section 
    ;

surface_section
    : surfaces
    ;

surfaces 
    : surfaces one_surface
    | one_surface
    ;

one_surface
    : quadric_surface
	| sphere_surface
    | polygon_surface
	| wavefront_surface
    ;

quadric_surface
    : OBJECT STRING QUADRIC realVal realVal realVal realVal realVal 
      realVal realVal realVal realVal realVal
      {
		  add_quadric($2, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13);
		  free($2);
      }
    ;

sphere_surface
	: OBJECT STRING SPHERE realVal realVal realVal realVal
	{
		add_sphere($2, $4, $5, $6, $7);
		free($2);
	}
	;

wavefront_surface
	: OBJECT STRING WAVEFRONT STRING
	{
		add_wavefront($4);

		free($2);
		free($4);
	}

polygon_surface
    : OBJECT STRING POLY 
      {	printf("object poly\n"); begin_poly_object($2); free($2); }
      vertex_section texture_map_section
	   polygon_section
	  { end_poly_object(); }
    ;

vertex_section
    : vertices
    ;

vertices
    : vertices one_vertex
    | one_vertex
    ;

one_vertex
    : VERTEX realVal realVal realVal
      { printf("vertex %f %f %f\n", $2, $3, $4); add_poly_vertex($2, $3, $4); }
    ;

polygon_section
    : polygons
    ;

polygons 
    : polygons one_polygon
    | one_polygon
    ;

one_polygon
    : POLY  
      { printf("polygon"); }
      indices
      { printf("\n"); }
    ;

indices
	: triangle_indices
	| rectangle_indices

triangle_indices
	: index index index
	  { add_poly_triangle($1, $2, $3);  }
	;

rectangle_indices
	: index index index index
	  { add_poly_rectangle($1, $2, $3, $4); }
	;

/*
indices
    : indices one_index
    | one_index
    ;

one_index
	: index
	{ printf("polygon idx %d\n", $1); add_poly_index($1); }
	;
*/

texture_map_section
    : texture_maps
    ;

texture_maps
    : texture_maps one_texture_map
    | one_texture_map
	| /*epsilon*/
    ;

one_texture_map
    : TEX index realVal realVal
      { printf("texture %d %f %f\n", $2, $3, $4); add_poly_texmap($2, $3, $4); }
    ;

property_section
    : properties
    ;

properties
    : properties one_property
    | one_property
    ;

one_property
    : PROPERTY STRING ambient diffuse specular mirror texture refraction glossy opacity
	{
		add_property($2, prop.ar, prop.ag, prop.ab, prop.r, prop.g, prop.b, prop.specular, prop.specShininess, prop.mirror, prop.texture, prop.refraction, prop.refractionIndex, prop.glossy, prop.glossySamples, prop.opacity); 
		free($2);
		free(prop.texture);
	}
    ;

ambient
    : AMBIENT zeroToOneVal zeroToOneVal zeroToOneVal
      { 
		prop.ar = $2;
		prop.ag = $3;
		prop.ab = $4;
      }
    ;

diffuse
    : DIFFUSE zeroToOneVal zeroToOneVal zeroToOneVal
      { 
		prop.r = $2;
		prop.g = $3;
		prop.b = $4;
      }
    ;

specular
    : SPECULAR  zeroToOneVal  realVal 
      { 
		prop.specular = $2;
		prop.specShininess = $3;
      }
    ;

mirror
    : MIRROR zeroToOneVal
      { 
		prop.mirror = $2;
      }
    ;

texture
	: TEXTURE STRING
		{
			prop.texture = $2;
		}
	;

refraction
	: REFRACTION realVal realVal
	  {
		prop.refraction = $2;
		prop.refractionIndex = $3;
	  }
	;

glossy
	: GLOSSY realVal index
	  {
		prop.glossy = $2;
		prop.glossySamples = $3;
	  }
	;

opacity
	: OPACITY realVal
	  {
		prop.opacity = $2;
	  }

object_section
    : objects
    ;

objects 
    : objects one_object
    | one_object
    ;

one_object
    : OBJECT STRING STRING
      {
		add_objekt($2, $3);
		free($2);
		free($3);
      }
    ;

lighting_section
    : lights
    ;

lights 
    : lights one_light
    | one_light
    ;

one_light
	: dir_light
	| ptr_light
	| circle_area_light
	;

dir_light : DIRLIGHT STRING direction color
    {
		add_dirlight($2, light.dirx, light.diry, light.dirz, light.colr, light.colg, light.colb);
		free($2);
    }
    ;

ptr_light : PTRLIGHT STRING position color
	{
		add_ptrlight($2, light.posx, light.posy, light.posz, light.colr, light.colg, light.colb);
		free($2);
	}
	;

circle_area_light :	CIRCLEAREALIGHT STRING position direction circle_area_light_radius color
	{
		add_circle_area_light($2, 
							 light.posx, light.posy, light.posz,
							 light.dirx, light.diry, light.dirz,
							 light.radius,
							 light.colr, light.colg, light.colb);
		free($2);
	}
	;

direction : DIRECTION realVal realVal realVal
    {
		light.dirx = $2;
		light.diry = $3;
		light.dirz = $4;
    }
    ;
	
position : POSITION realVal realVal realVal
	{
		light.posx = $2;
		light.posy = $3;
		light.posz = $4;	
	}
	;

circle_area_light_radius : RADIUS realVal
	{
		light.radius = $2;
	}
	;
color : COLOR colorVal colorVal colorVal
    {
		light.colr = $2;
		light.colg = $3;
		light.colb = $4;
    }
    ;

// some minor type conversions and range checks...

colorVal : zeroToOneVal ;

zeroToOneVal : realVal
    {
	if ( $1 < 0.0 || $1 > 1.0 ) {
	    yyerror("value out of range (only 0 to 1 allowed)");
	} /* if */

	/* pass that value up the tree */
	$$ = $1;
    }
    ;

angleVal : realVal
    {
	if ( $1 < 0.0 || $1 > 180.0 ) {
	    yyerror("value out of range (only 0 to 180 degrees allowed)");
	} /* if */

	/* pass that value up the tree */
	$$ = $1;
    }
    ;

realVal 
    : FLOAT
      { $$ = $1; }
    | INTEGER
      { $$ = (float) $1; /* conversion from integers */ }
    ;

index : INTEGER
      {
    	if ( $1 < 1 ) {
	    yyerror("index out of range (only 1 or more allowed)");
	} /* if */

	/* pass that value up the tree */
	$$ = $1;
      }
    ;
    
%%

#include "lex.yy.c"


