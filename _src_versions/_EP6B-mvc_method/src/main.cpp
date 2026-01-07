/**
 * @date: 29-12-2024
 * 
 *  Episode 6: "openGL with C++ 6: Design Patterns"
 *  This _EP6B demonstrates the second structure, the use of Model View Controller system
 *  
 */

#include "config.h"
#include "controller/app.h"

int main()
{
    App* app = new App();

    app -> run();

    delete app;
    return 0;
}