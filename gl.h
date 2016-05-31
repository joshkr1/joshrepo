//
// Created by Atanda 5/31/2016
//

#include "gl_texture_util.h"

#include <app.h>
#include <Elementary_GL_Helpers.h>

ELEMENTARY_GLVIEW_GLOBAL_DECLARE();

unsigned int create_texture(Evas_Object *parent, const char *filename) {

    unsigned int gltex_object;
    int w, h;
    int surface_w, surface_h;
    evas_object_geometry_get(parent, NULL, NULL, &surface_w, &surface_h);

    Evas_Object* inline_buffer = elm_win_add(parent,"Img Read",ELM_WIN_INLINED_IMAGE);
    evas_object_move(inline_buffer, 0, 0);
    evas_object_resize(inline_buffer, surface_w, surface_h);
    evas_object_show(inline_buffer);

    Evas* canvas = evas_object_evas_get(inline_buffer);
    Evas_Object* image = evas_object_image_add(canvas);

    char path[200];
    sprintf(path, "%s%s", app_get_resource_path(), filename);
    evas_object_image_file_set(image, path, NULL);
    evas_object_image_size_get(image, &w, &h);
    evas_object_image_fill_set(image, 0, 0, w, h);
    evas_object_image_filled_set(image, EINA_TRUE);
    evas_object_resize(image, w, h);
    evas_object_show(image);

    elm_win_render(inline_buffer);

    GLubyte* pixels;
    pixels = (GLubyte*) evas_object_image_data_get(image, EINA_FALSE);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &gltex_object);

    glBindTexture(GL_TEXTURE_2D, gltex_object);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA_EXT, w, h, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pixels);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);

    evas_object_del(inline_buffer);

    return gltex_object;

}
