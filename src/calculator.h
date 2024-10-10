#include "lvgl.h"
#include <stdlib.h>  // for atof
#include <stdio.h>   // for sprintf
#include "ui/screens.h"
#include "hal.h"

static char current_number[32] = "0";
static double previous_number = 0.0;
static char current_operator = '\0';  // Changed from 'operator' to 'current_operator'
static bool is_new_input = true;  // To reset input after an operator
static bool has_decimal = false;  // To track if the input has a decimal point

// Function to update the label text
void update_display() {
    lv_label_set_text(objects.label, current_number);
}

// Function to clear all (AC)
void ac_cb(lv_event_t *e) {
    strcpy(current_number, "0");
    previous_number = 0.0;
    current_operator = '\0';  // Reset operator
    is_new_input = true;
    has_decimal = false;
    update_display();
}

// Function to handle number button presses
void num_cb(lv_event_t *e) {
    
    uint32_t* btn_value = (uint32_t*)lv_event_get_user_data(e);  // Get button's value
    log_v("calculator", "num_cb: %d", btn_value);  
    if (is_new_input) {
        strcpy(current_number, "0");
        is_new_input = false;
    }


    if (strcmp(current_number, "0") == 0 && btn_value == 0) {
        return; // Ignore multiple leading zeros
    }

    char num_str[2];
    sprintf(num_str, "%d", btn_value);
    
    if (strcmp(current_number, "0") == 0) {
        sprintf(current_number, "%d", btn_value); // Replace leading zero
    } else {
        strcat(current_number, num_str); // Append the digit
    }

    update_display();
}

// Function to handle the decimal point
void decimal_cb(lv_event_t *e) {
    log_v("calculator", "decimal point");
    if (!has_decimal) {
        strcat(current_number, ".");
        has_decimal = true;
        update_display();
    }
}

// Function to handle operator button presses (+, -, *, ÷)
void operator_cb(lv_event_t *e) {
    log_v("calculator", "operator");  
    char* op = (char *)lv_event_get_user_data(e);  // Get the operator char
    log_v("calculator", "operator: %s", op);  

    previous_number = atof(current_number);
    current_operator = *op;  // Use 'current_operator' instead of 'operator'
    is_new_input = true;
    has_decimal = false;
}

// Function to calculate the result when '=' is pressed
void equals_cb(lv_event_t *e) {
    double current_value = atof(current_number);
    double result = 0.0;

    if (current_operator == '+') {
        result = previous_number + current_value;
    } else if (current_operator == '-') {
        result = previous_number - current_value;
    } else if (current_operator == '*') {
        result = previous_number * current_value;
    } else if (current_operator == '/') {
        if (current_value != 0) {
            result = previous_number / current_value;
        } else {
            lv_label_set_text(objects.label, "Error");  // Handle division by zero
            return;
        }
    }

    sprintf(current_number, "%.10g", result);  // Format the result to avoid floating point errors
    current_operator = '\0';  // Reset the operator
    is_new_input = true;
    has_decimal = false;
    update_display();
}

// Function to toggle sign (+/-)
void toggle_sign_cb(lv_event_t *e) {
    if (current_number[0] == '-') {
        memmove(current_number, current_number + 1, strlen(current_number));
    } else {
        char temp[32];
        strcpy(temp, current_number);
        sprintf(current_number, "-%s", temp);
    }
    update_display();
}

// Function to handle percentage calculation (%)
void percent_cb(lv_event_t *e) {
    double value = atof(current_number);
    value /= 100.0;
    sprintf(current_number, "%.10g", value);
    update_display();
}

void assign_callbacks() {

    lv_obj_add_event_cb(objects.ac, ac_cb, LV_EVENT_CLICKED, NULL);  // Assign AC callback

    // Assign number button callbacks
    lv_obj_add_event_cb(objects.one, num_cb, LV_EVENT_CLICKED, (void *)1);
    lv_obj_add_event_cb(objects.two, num_cb, LV_EVENT_CLICKED, (void *)2);
    lv_obj_add_event_cb(objects.three, num_cb, LV_EVENT_CLICKED, (void *)3);
    lv_obj_add_event_cb(objects.four, num_cb, LV_EVENT_CLICKED, (void *)4);
    lv_obj_add_event_cb(objects.five, num_cb, LV_EVENT_CLICKED, (void *)5);
    lv_obj_add_event_cb(objects.six, num_cb, LV_EVENT_CLICKED, (void *)6);
    lv_obj_add_event_cb(objects.seven, num_cb, LV_EVENT_CLICKED, (void *)7);
    lv_obj_add_event_cb(objects.eight, num_cb, LV_EVENT_CLICKED, (void *)8);
    lv_obj_add_event_cb(objects.nine, num_cb, LV_EVENT_CLICKED, (void *)9);
    lv_obj_add_event_cb(objects.zero, num_cb, LV_EVENT_CLICKED, (void *)0);


    // Assign decimal callback
    lv_obj_add_event_cb(objects.dot, decimal_cb, LV_EVENT_CLICKED, NULL);

    // Assign operator callbacks
    lv_obj_add_event_cb(objects.add, operator_cb, LV_EVENT_CLICKED, (void *)"+");

    lv_obj_add_event_cb(objects.minus, operator_cb, LV_EVENT_CLICKED, (void *)"-");

    lv_obj_add_event_cb(objects.multiply, operator_cb, LV_EVENT_CLICKED, (void *)"*");

    lv_obj_add_event_cb(objects.divide, operator_cb, LV_EVENT_CLICKED, (void *)"/");

    // Assign equals callback
    lv_obj_add_event_cb(objects.equal, equals_cb, LV_EVENT_CLICKED, NULL);

    // Assign toggle sign callback
    lv_obj_add_event_cb(objects.negate, toggle_sign_cb, LV_EVENT_CLICKED, NULL);

    // Assign percent callback
    lv_obj_add_event_cb(objects.percentage, percent_cb, LV_EVENT_CLICKED, NULL);
}
