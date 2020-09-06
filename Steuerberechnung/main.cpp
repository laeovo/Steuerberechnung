//
//  main.cpp
//  Steuerberechnung
//
//  Created by Leo Vornberger on 30.08.20.
//  Copyright © 2020 Leo Vornberger. All rights reserved.
//

#include <iostream>

#include "Steuerberechnung.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    
    Steuerberechnung sb;
    sb.setzeParameter();
    sb.run();
    
    return 0;
}
