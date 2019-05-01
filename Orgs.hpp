//
//  Org.hpp
//  naturalSelectionSim
//
//  Created by John Landy on 4/30/19.
//  Copyright © 2019 John Landy. All rights reserved.
//

#ifndef Orgs_hpp
#define Orgs_hpp

#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <iostream>

// Class containing the group of organisms and their interactions
class Orgs {
public:
    // Constructor
    Orgs(int numOrgs, int dimensions);
    // Base function for organisms to interact
    void interact(int iterationNum, bool simple);
    // Function to print the stats/metadata for the organisms and their environment
    void printStats(int it, bool simple);
private:
    // Class for the Grid the organisms interact on
    class Grid {
    public:
        // Constructor
        Grid(int dimensions_in);
        // Function to retrieve dimensions
        int getDimensions();
        // Function for Grid to reset the food particles between iterations
        void setFood();
        // Public member var to store food count per round
        int foodCount;
    private:
        int dimensions;
        // Tile struct
        struct Tile {
            int x;
            int y;
            bool isFood;
            bool isOrg;
        };
    public:
        // Actual Grid data structure
        std::vector<std::vector<Tile> > grid;
    };

    // Class for each individual organism
    class Org {
    public:
        // Constructor
        Org();
        // Function to randomly set initial location of an organism each day
        void setLoc(int dimensions);
        // Function that determines where each organism will move.
        // There is no limit to the number of organisms per grid tile, but if a tile
        // has food, only the first organism there can eat it
        void move(Grid g);
        // Energy getter
        int getEnergy();
        // Food getter
        int getFood();
        // Size getter
        int getSize();
        // Speed getter
        int getSpeed();
        // Energy cost getter
        int getEnergyCost();
        // Food setter
        void setFood(int val);
        // Energy setter
        void setEnergy(int val);
    private:
        // Location
        int xLoc;
        int yLoc;
        // Org Traits
        int speed;
        int energy;
        int food;
        int size;
        int senseDist;
        int energyCost;
    };
    // Vector of eaten Orgs in each round
    std::vector<int> eaten;
    // Data structure to hold all of the Orgs
    std::vector<Org> orgs;
    // Grid object
    Grid g;
};

#endif /* Org_hpp */
