# joshrepo
~~this is a read me file for our term project
atanda oluwasegun oluwashina~~
2014210113
PROJECT PROPOSAL FOR COMPUTER GRAPHICS- (TIZEN)
MEMBERS(3)
DUBHAN CONRY(2012210117) , ATANDA OLUWASEGUN OLUWASHINA(2014210113), PRINCE GIDIGLO(2014210115)

THESIS STATEMENT
We are creating a multicolored 3D rotating cube using the OpenGL ES 2.0 API provided by the GLView library. Several concepts are used, such as the cube geometry, the initialization phase of the model, the adjustment of the model frame by frame, and the way to design the OpenGL ES rendering loop.
METHODOLOGY
o	win: Application window
o	conform: Conformant object for the indicator
o	glview: GLView object
o	main_box: Box object which contains glview and inner_box
o	inner_box: Box object for the toolbox

OBJECTIVES
•	creating a cube,
•	Drawing the cube with GLview,
•	Rendering the cube,
•	Animating the cube,
•	Implementing UI component interaction and implementing effects.

5/27/2016. Atada O.

the project is too basic and the TA wants us to add more features to the cube;
therefore, I decided to make the cube look like the teapot in project three,
giving it a new texture and making it like a game where the cube will explode if it is not alligned with a reference, i.e 
for the cube to be alligned it has to be touched an d made to balance with a reference plane due to the calibration of the phone
@joshkr1

TIZEN_BASIC GLES



#include "basicgles.h"
#include "glview.h"

static void
del_anim(void *data, Evas *evas, Evas_Object *obj, void *event_info) {
    appdata_s *ad = (appdata_s *)data;

    if(ad && ad->ani) {
        ecore_animator_del(ad->ani);
        ad->ani = NULL;
    }
}

static Eina_Bool
anim_cb(void *data) {
    appdata_s *ad = (appdata_s *) data;

    ad->xangle -= ad->tic_xangle;
    ad->yangle -= ad->tic_yangle;

    if (fabs(ad->xangle - 45.0f) < 0.05f) {
        ad->xangle = 45.0f;
        ad->yangle = 45.0f;
        ecore_animator_del(ad->ani);
        ad->reset_anim = EINA_FALSE;
    }

    // notify the object need to be updated
    elm_glview_changed_set(ad->glview);

    return EINA_TRUE;
}

static void
clicked_cb(void *user_data, Evas_Object *obj, void *event_info) {
    appdata_s *ad = (appdata_s *) user_data;
    if (!ad->reset_anim) {
        ad->reset_anim = EINA_TRUE;

        // Setting animation angle for 0.75 seconds
        ad->tic_xangle = (ad->xangle - 45.0f) / 45.0f;
        ad->tic_yangle = (ad->yangle - 45.0f) / 45.0f;

        // Add animator which calls elm_glview_changed_set() per frame
        // This will rotate object tic_x(y)angle along x(y)-axis
        // until object reaches the initial angle
        ad->ani = ecore_animator_add(anim_cb, ad);
        evas_object_event_callback_add(ad->glview, EVAS_CALLBACK_DEL, del_anim, ad);
    }
}

static void
win_delete_request_cb(void *data, Evas_Object *obj, void *event_info) {
    ui_app_exit();
}

static void
win_back_cb(void *data, Evas_Object *obj, void *event_info) {
    appdata_s *ad = (appdata_s *)data;
    /* Let window go to hide state. */
    elm_win_lower(ad->win);
}

static void
create_indicator(appdata_s *ad) {
    elm_win_conformant_set(ad->win, EINA_TRUE);

    elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
    elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_OPAQUE);

    ad->conform = elm_conformant_add(ad->win);
    evas_object_size_hint_weight_set(ad->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_win_resize_object_add(ad->win, ad->conform);
    evas_object_show(ad->conform);
}

static Evas_Object *
add_win(const char *name) {
    Evas_Object *win;
    win = elm_win_util_standard_add(name, "OpenGL example");

    if (!win)
        return NULL;

    if (elm_win_wm_rotation_supported_get(win)) {
        int rots[4] = {0, 90, 180, 270};
        elm_win_wm_rotation_available_rotations_set(win, rots, 4);
    }

    evas_object_show(win);

    return win;
}

static bool
create_base_gui(appdata_s *ad) {

    // set elm configuration to use GPU acceleration for opengles
    elm_config_accel_preference_set("opengl");

    // create & initialize window
    ad->win = add_win(ad->name);

    if (!ad->win)
        return false;

    create_indicator(ad);
    evas_object_smart_callback_add(ad->win, "delete,request", win_delete_request_cb, NULL);
    eext_object_event_callback_add(ad->win, EEXT_CALLBACK_BACK, win_back_cb, ad);

    // Create the naviframe
    ad->naviframe = elm_naviframe_add(ad->conform);
    elm_object_content_set(ad->conform, ad->naviframe);

    // Show the naviframe
    evas_object_show(ad->naviframe);

    // Create the box
    Evas_Object *box = elm_box_add(ad->naviframe);

    // Set the box vertical
    elm_box_horizontal_set(box, EINA_FALSE);
    // The box expands when its contents need more space
    evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    // The box fills the available space
    evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);

    ad->glview = add_glview(box, ad);
    elm_box_pack_end(box, ad->glview);

    Evas_Object *button = elm_button_add(box);
    evas_object_size_hint_weight_set(button, EVAS_HINT_EXPAND, EVAS_HINT_FILL);
    evas_object_size_hint_align_set(button, EVAS_HINT_FILL, 1);
    elm_object_text_set(button, "Reset Animation");
    evas_object_smart_callback_add(button, "clicked", clicked_cb, ad);
    evas_object_show(button);
    elm_box_pack_end(box, button);

    // Show the box
    evas_object_show(box);

    // Add the box in the naviframe container
    elm_naviframe_item_push(ad->naviframe, "Basic GLES App", NULL, NULL, box, NULL);

    // Show window after base gui is set up
    evas_object_show(ad->win);

    return true;
}

static bool
app_create(void *data) {
    /* Hook to take necessary actions before main event loop starts
        Initialize UI resources and application's data
        If this function returns true, the main loop of application starts
        If this function returns false, the application is terminated */
    appdata_s *ad = data;

    return create_base_gui(ad);
}

static void
app_control(app_control_h app_control, void *data) {
    /* Handle the launch request. */
}

static void
app_pause(void *data) {
    /* Take necessary actions when application becomes invisible. */
}

static void
app_resume(void *data) {
    /* Take necessary actions when application becomes visible. */
}

static void
app_terminate(void *data) {
    /* Release all resources. */
}

static void
ui_app_lang_changed(app_event_info_h event_info, void *user_data) {
    /*APP_EVENT_LANGUAGE_CHANGED*/
    char *locale = NULL;
    system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
    elm_language_set(locale);
    free(locale);
    return;
}

static void
ui_app_orient_changed(app_event_info_h event_info, void *user_data) {
    /*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
    return;
}

static void
ui_app_region_changed(app_event_info_h event_info, void *user_data) {
    /*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void
ui_app_low_battery(app_event_info_h event_info, void *user_data) {
    /*APP_EVENT_LOW_BATTERY*/
}

static void
ui_app_low_memory(app_event_info_h event_info, void *user_data) {
    /*APP_EVENT_LOW_MEMORY*/
}

int
main(int argc, char *argv[]) {
    appdata_s ad = {0,};
    int ret = 0;

    ui_app_lifecycle_callback_s event_callback = {0,};
    app_event_handler_h handlers[5] = {NULL,};

    ad.name = "basicGLES";

    event_callback.create = app_create;
    event_callback.terminate = app_terminate;
    event_callback.pause = app_pause;
    event_callback.resume = app_resume;
    event_callback.app_control = app_control;

    ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, &ad);
    ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, &ad);
    ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED,
                             ui_app_orient_changed, &ad);
    ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed,
                             &ad);
    ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED,
                             ui_app_region_changed, &ad);

    ret = ui_app_main(argc, argv, &event_callback, &ad);
    if (ret != APP_ERROR_NONE) {
        dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);
    }

    return ret;
}
