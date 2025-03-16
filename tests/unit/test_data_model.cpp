#include "core/data_model.h"
#include <cassert>
#include <iostream>

using namespace my_desktop_app;

void testAddItem() {
    DataModel model;
    model.addItem("test", "value");
    assert(model.getItemValue("test") == "value");
    std::cout << "testAddItem: PASSED" << std::endl;
}

void testRemoveItem() {
    DataModel model;
    model.addItem("test", "value");
    model.removeItem("test");
    assert(model.getItemValue("test") == "");
    std::cout << "testRemoveItem: PASSED" << std::endl;
}

void testDataChangeCallback() {
    DataModel model;
    bool callbackCalled = false;
    std::string changedItem;
    
    model.registerDataChangeCallback([&callbackCalled, &changedItem](const std::string& item) {
        callbackCalled = true;
        changedItem = item;
    });
    
    model.addItem("test", "value");
    assert(callbackCalled);
    assert(changedItem == "test");
    std::cout << "testDataChangeCallback: PASSED" << std::endl;
}

int main() {
    testAddItem();
    testRemoveItem();
    testDataChangeCallback();
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
