%{ 
   
int yywrap()
{
return 1; // EOF
} 
   
%} 

ziffern  ([0-9]+)
vorz     ([+-]?)
ganzz    ({vorz}{ziffern})
kommaz   ({vorz}{ziffern}*[.]{ziffern})
expo	 ([eE]{vorz}{ziffern})
zahl	 (({kommaz}{expo}?)|({ganzz}{expo}))
string   ([a-zA-Z0-9+-_]+)

%%

#.* { /*printf("COMMENT: '%s'\n", yytext);*/ }
resolution { return(RESOLUTION); }
eyepoint { return(EYEPOINT); }
lookat { return(LOOKAT); }
fovx { return(FOVX); }
fovy { return(FOVY); }
aspect { return(ASPECT); }
apertureRadius { return(APERTURE_RADIUS); }
focalDistance { return(FOCAL_DISTANCE); }
dofSamples { return(DOF_SAMPLES); }
object { return(OBJECT); }
poly { return(POLY); }
polygon { return(POLY); } /* equivalent spelling */
tex { return(TEX); }
vertex { return(VERTEX); }
quadric { return(QUADRIC); }
sphere { return(SPHERE); }
wavefront { return(WAVEFRONT); }
property { return(PROPERTY); }
ambient { return(AMBIENT); }
diffuse { return(DIFFUSE); }
specular { return(SPECULAR); }
mirror { return(MIRROR); }
glossy { return(GLOSSY); }
opacity { return(OPACITY); }
texture { return(TEXTURE); }
refraction { return(REFRACTION); }
ambience { return(AMBIENCE); }
background { return(BACKGROUND); }
dir_light { return(DIRLIGHT); }
point_light { return(PTRLIGHT); }
circlearea_light { return(CIRCLEAREALIGHT); }
radius { return(RADIUS); }
direction { return(DIRECTION); }
position { return(POSITION); }
color { return(COLOR); } /* equivalent spelling */
up { return(UP); } /* equivalent spelling */
{ganzz}	        {  yylval.intval=atoi(yytext); return(INTEGER); }
{zahl}		{  yylval.floatval=atof(yytext); return(FLOAT);  }
{string}	{ yylval.stringval=(char *)strdup(yytext); return(STRING); }
\n              { linenum++; }
.    ;
