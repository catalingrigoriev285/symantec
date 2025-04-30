#include "main.h"

int main(){
    app::models::logs::Logs log("Test Title", "This is a test description.", app::models::logs::INFO);
    log.display();
    return 0;
}