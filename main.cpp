//
//  main.cpp
//  naturalSelectionSim
//
//  Created by John Landy on 4/30/19.
//  Copyright © 2019 John Landy. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Orgs.hpp"

// Driver function
// Parameters: <grid dimension> <numOrgs> <numIterations>
int main(int argc, char* argv[]) {
    int numIterations = atoi(argv[1]);
    // Set constants
    const int NUM_ORGS = 50;
    const int SIZE = 50;
    // Build the organisms object
    Orgs orgs(NUM_ORGS, SIZE);
    // Allow the organisms to interact in the environment
    for (int i = 0; i < numIterations; ++i) {
        orgs.interact(i, true);
    }
    return 0;
}
