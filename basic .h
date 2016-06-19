#ifndef __BASICGLES_H__
#define __BASICGLES_H__

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>
#include <Elementary_GL_Helpers.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "basicgles"

#if !defined(PACKAGE)
#define PACKAGE "org.example.basicgles"
#endif

ELEMENTARY_GLVIEW_GLOBAL_DECLARE();

typedef struct appdata {
	const char *name;

	// All graphical objects here are pointers to the value of the type Evas_Object
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *naviframe;
	Evas_Object *glview;

	Ecore_Animator *ani;

	int glview_w, glview_h;

	/* GL related data here... */
	unsigned int program;
	unsigned int vtx_shader;
	unsigned int fgmt_shader;
	unsigned int texture;

	unsigned int vbo_vertex;
	unsigned int vbo_color;
	unsigned int vbo_texture;
	unsigned int vbo_index;

	float xangle;
	float yangle;
	float tic_xangle;
	float tic_yangle;

	// Locations for vertex attribute
	unsigned int idx_a_position;
	unsigned int idx_a_color;
	unsigned int idx_a_tex;

	// Locations for shdaer uniforms
	int idx_wvp;
	int idx_tex;

	float wvp[16];

	Eina_Bool mouse_down : 1;
	Eina_Bool initialized : 1;
	Eina_Bool reset_anim : 1;
} appdata_s;

#endif /* __BASICGLES_H__ */
