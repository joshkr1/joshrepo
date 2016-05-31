//
// Created by Atanda 5/31/2016.
//

#ifndef __GLVIEW_H__
#define __GLVIEW_H__

#include <Elementary.h>
#include "basicgles.h"

/**
 * Add elm_glview component to the parent
 *
 * @param[in] parent parent evas object
 * @param[in] ad app data structure
 * @return created elm_glview object
 */
Evas_Object* add_glview(Evas_Object* parent, appdata_s *ad);

#endif /* __GLVIEW_H__ */
