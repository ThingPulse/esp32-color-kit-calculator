
#include "lvgl.h"
#include "hal.h"


//#include "demos/lv_demos.h"
#include "ui/ui.h"
#include "calculator.h"


#if defined( NATIVE )
    /**
     * for non arduino
     */                 
    void setup( void );
    void loop( void );

    int main( void ) {
        setup();
        while( 1 ) { 
            loop(); 
        };
        return( 0 );
    }
#endif // NATIVE



void setup() {
	hal_setup();
    log_i("main", "hal_setup done");

    ui_init();  
    log_i("main", "ui init done");
    assign_callbacks();
    log_i("main", "assign callbacks done");

}

void loop() {
	hal_loop();
}

