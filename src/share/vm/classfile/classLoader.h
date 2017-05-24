//
// Created by GentlyGuitar on 5/23/2017.
//

#ifndef MINISPOT_CLASSLOADER_H
#define MINISPOT_CLASSLOADER_H

#include <string>
#include <vector>
#include "utilities/exceptions.h"
#include "runtime/handles.h"
#include "runtime/symbol.h"

/* the bootstrap classloader */
class ClassLoader {
private:
    std::vector<std::string> _boot_search_path;
    std::vector<std::string> _app_search_path;
public:
    static ClassLoader* boot_loader;
    static void init();
    static void destroy();

    ClassLoader();


    //instanceKlassHandle load_classfile(Symbol* h_name, TRAPS);
    instanceKlassHandle load_classfile(std::string name, TRAPS);
    instanceKlassHandle load_app_class(std::string name, TRAPS);
};

#endif //MINISPOT_CLASSLOADER_H
