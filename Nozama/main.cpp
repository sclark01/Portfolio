/*main.cpp
*Name: Shea C-T
*Tests Nozama
 */

#include "manager.h"
#include "fetch.h"
#include "packer.h"
#include "queue.h"
#include "pack_manager.h"
#include <iostream>

using namespace std;

int main () {

    Manager nozama;

    nozama.get_orders();
    nozama.run();

    return 0;
}
