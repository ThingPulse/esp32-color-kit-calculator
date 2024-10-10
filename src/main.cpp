
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
    delay(5000);
	hal_setup();

    ui_init();  
    assign_callbacks();

}

void loop() {
	hal_loop();
}

