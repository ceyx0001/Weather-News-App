/* Jun Shao
* 251258566
* November 7 2022
* Assistant contains the logic for starting the WT app and the main function
*/

#include "Assistant.h"

using namespace Wt;
using namespace std;

// createApplication(env) creates the WT application
// @param env points to the environment platform
// @return app points to the WT application
unique_ptr<WApplication> createApplication(const WEnvironment &env) {
    auto theme = make_shared<WBootstrap5Theme>();
    auto app = make_unique<WApplication>(env);
    app->setTitle("Boogle Home");
    app->setTheme(theme);
    app->messageResourceBundle().use(app->appRoot() + "templates");
    app->useStyleSheet("style.css");

    // start auth process
    Authenticate a;
    a.startAuth();

    return app;
}

// main function to run program
int main(int argc, char** argv) {
    try {
        int status = WRun(argc, argv, createApplication);
        return status;
    } catch(exception e) {
        cerr << e.what() << endl;
    }
}