#include "../../../lvgl.h"
#if LV_USE_TABLE && LV_BUILD_EXAMPLES

static void event_cb(lv_obj_t * obj, lv_event_t e)
{
    if(e == LV_EVENT_DRAW_PART_BEGIN) {
        lv_obj_draw_hook_dsc_t * hook_dsc = lv_event_get_param();
        /*If the cells are drawn...*/
        if(hook_dsc->part == LV_PART_ITEMS) {
            uint32_t row = hook_dsc->id /  lv_table_get_col_cnt(obj);
            uint32_t col = hook_dsc->id - row * lv_table_get_col_cnt(obj);

            /*Make the texts in the first cell center aligned*/
            if(row == 0) {
                hook_dsc->label_dsc->align = LV_TEXT_ALIGN_CENTER;
                hook_dsc->rect_dsc->bg_color = lv_color_mix(LV_COLOR_BLUE, hook_dsc->rect_dsc->bg_color, LV_OPA_20);
                hook_dsc->rect_dsc->bg_opa = LV_OPA_COVER;
            }
            /*In the first column align the texts to the right*/
            else if(col == 0) {
                hook_dsc->label_dsc->flag = LV_TEXT_ALIGN_RIGHT;
            }

            /*MAke every 2nd row grayish*/
            if((row != 0 && row % 2) == 0) {
                hook_dsc->rect_dsc->bg_color = lv_color_mix(LV_COLOR_GRAY, hook_dsc->rect_dsc->bg_color, LV_OPA_10);
                hook_dsc->rect_dsc->bg_opa = LV_OPA_COVER;
            }
        }
    }
}


void lv_example_table_1(void)
{
    lv_obj_t * table = lv_table_create(lv_scr_act(), NULL);

    /*Fill the first column*/
    lv_table_set_cell_value(table, 0, 0, "Name");
    lv_table_set_cell_value(table, 1, 0, "Apple");
    lv_table_set_cell_value(table, 2, 0, "Banana");
    lv_table_set_cell_value(table, 3, 0, "Lemon");
    lv_table_set_cell_value(table, 4, 0, "Grape");
    lv_table_set_cell_value(table, 5, 0, "Melon");
    lv_table_set_cell_value(table, 6, 0, "Peach");
    lv_table_set_cell_value(table, 7, 0, "Nuts");

    /*Fill the second column*/
    lv_table_set_cell_value(table, 0, 1, "Price");
    lv_table_set_cell_value(table, 1, 1, "$7");
    lv_table_set_cell_value(table, 2, 1, "$4");
    lv_table_set_cell_value(table, 3, 1, "$6");
    lv_table_set_cell_value(table, 4, 1, "$2");
    lv_table_set_cell_value(table, 5, 1, "$5");
    lv_table_set_cell_value(table, 6, 1, "$1");
    lv_table_set_cell_value(table, 7, 1, "$9");

    /*Set a smaller height to the table. It'll make it scrollable*/
    lv_obj_set_height(table, 200);
    lv_obj_align(table, NULL, LV_ALIGN_CENTER, 0, 0);

    /*Add an event callback to to apply some custom drawing*/
    lv_obj_add_event_cb(table, event_cb, NULL);
}

#endif