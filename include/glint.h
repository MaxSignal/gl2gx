#include "GL/gl.h"

//TODO: rewrite to support dynamic arrays
#define MAX_ARRAY 1000

#define LARGE_NUMBER 1048576
#define BIG_NUMBER		(1024*1024)
//1048576
//1.0e-18F
//9.9999998e+017

typedef struct 
{
	float x;
	float y;
	float z;
	float w;
} VertexElement;

//32bit element, with different types
union TypeElement32{
    float f32;
    s16 s16;
    s8 s8;
};

typedef struct 
{
	union TypeElement32 x;
	union TypeElement32 y;
	union TypeElement32 z;
    //type of variables defined
    u8 types;
} xyzElement;

typedef struct 
{
	union TypeElement32 s;
	union TypeElement32 t;
    //type of variables defined
    u8 types;
} TexCoordElement;

//Types of variables defined for xyz and tex
#define TypeElementf32 1
#define TypeElements16 2
#define TypeElements8 3

typedef struct 
{
	float r;
	float g;
	float b;
	float a;
} GXColorf;

xyzElement _tempnormalelement;
TexCoordElement _temptexcoordelement;
GXColor _tempcolorelement;

//TODO: integrate in normal, vertex, texcoord and color in struct and place that in dynamic arrray
xyzElement _normalelements[MAX_ARRAY]; //TODO: dynamic
xyzElement _vertexelements[MAX_ARRAY]; //TODO: dynamic
TexCoordElement _texcoordelements[MAX_ARRAY]; //TODO: dynamic
GXColor _colorelements[MAX_ARRAY]; //TODO: dynamic

int _numelements;
int _type;

/* Depth Buffer */

u8 depthtestenabled;
GLenum depthfunction;
float _cleardepth;

/* Matrixes */

Mtx _mtxelements[32]; //max stack depth is 32 in opengl
int _mtxcurrentelement;
//TODO: clean up unneeded and naming
Mtx view,perspective; // view and perspective matrices
Mtx model, modelview, inversemodel, normalmodel;

/* light */
GXLightObj gxlight[8]; //max 8 lights in opengl
VertexElement gxlightpos[8]; //light position for each light
VertexElement gxlightdir[8]; //light direction for each light
bool gxlightenabled[8]; //is specific light enabled
int gxcurlight; //test for light position

//light specs
GXColorf gxlightambientcolor[8];
GXColorf gxlightdiffusecolor[8];
GXColorf gxlightspecularcolor[8];

//spot light specs
VertexElement gxspotdirection[8];
float gxspotexponent[8];
float gxspotcutoff[8];

float gxconstantattanuation[8];
float gxlinearattanuation[8];
float gxquadraticattanuation[8];

//lightmodel specs
GXColorf gxglobalambientlightcolor;

//material specs
GXColorf gxcurrentmaterialemissivecolor;
GXColorf gxcurrentmaterialambientcolor;
GXColorf gxcurrentmaterialdiffusecolor;
GXColorf gxcurrentmaterialspecularcolor;
float gxcurrentmaterialshininess;

/* culling */
bool gxcullfaceanabled;
GLenum gxwinding;

/* textures */
bool tex2denabled;
GLint curtexture;
GLenum curtexturetarget;
GXTexObj gxtextures[MAX_ARRAY]; //TODO: dynamic

/* end */
