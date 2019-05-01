//
//  Org.cpp
//  naturalSelectionSim
//
//  Created by John Landy on 4/30/19.
//  Copyright © 2019 John Landy. All rights reserved.
//

#include "Orgs.hpp"

// Function for Grid to reset the food particles between iterations
void Orgs::Grid::setFood() {
    foodCount = 0;
    // Set food in ~15% of random Tiles on the Grid
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            int random = rand() % 100; // 0 - 99
            if (random < 15) {
                grid[i][j].isFood = true;
                ++foodCount;
            } else {
                grid[i][j].isFood = false;
            }
            // Set location of each tile
            grid[i][j].x = i;
            grid[i][j].y = j;
            // No organisms start on the grid
            grid[i][j].isOrg = false;
        }
    }
}

// Grid Constructor
Orgs::Grid::Grid(int dimensions_in) {
    // Set dimensions
    dimensions = dimensions_in;
    // Set dimensions of grid data structure
    grid.resize(dimensions);
    for (int i = 0; i < grid.size(); ++i) {
        grid[i].resize(dimensions);
    }
}

// Grid function to retrieve dimensions
int Orgs::Grid::getDimensions() {
    return dimensions;
}

// Constructor for Org
Orgs::Org::Org() {
    speed = rand() % 3 + 1; // 1 - 3
    energy = 100; // every Org starts with 100 energy
    food = 0; // every Org starts with 0 food
    size = rand() % 2 + 1; // 1 - 2
    senseDist = size; // 1 - 2 based on size
    energyCost = (speed * speed * size * size); // 1 - 36
}

// Set location of Org as random Tile within the Grid
void Orgs::Org::setLoc(int dimensions) {
    xLoc = rand() % dimensions;
    yLoc = rand() % dimensions;
}

// Energy getter
int Orgs::Org::getEnergy() {
    return energy;
}
// Food getter
int Orgs::Org::getFood() {
    return food;
}

// Size getter
int Orgs::Org::getSize() {
    return size;
}
// Speed getter
int Orgs::Org::getSpeed() {
    return speed;
}

// Energy cost getter
int Orgs::Org::getEnergyCost() {
    return energyCost;
}

// Food setter
void Orgs::Org::setFood(int val) {
    food = val;
}

// Energy setter
void Orgs::Org::setEnergy(int val) {
    energy = val;
}

// Constructor for Orgs
// Build as many organisms as requested
Orgs::Orgs(int numOrgs, int dimensions) : g(Grid(dimensions)) {
    // Reserve vector
    orgs.reserve(numOrgs);
    for (int i = 0; i < numOrgs; ++i) {
        Org temp;
        temp.setLoc(dimensions);
        orgs.push_back(temp);
    }
}

// Function that determines where each organism will move.
// There is no limit to the number of organisms per grid tile, but if a tile
// has food, only the first organism there can eat it
void Orgs::Org::move(Grid g) {
    // Organism can move (speed) times per iteration
    for (int i = 0; i < speed; ++i) {
        // Initially, check if there is food where the organism is
        if (g.grid[xLoc][yLoc].isFood) {
            // Add food to org
            food++;
            // Remove food from grid
            g.grid[xLoc][yLoc].isFood = false;
        }
        if (senseDist == 1) {
            // Check if there is food within senseDist in any direction (1 space)
            if (xLoc + senseDist < g.grid.size() && g.grid[xLoc + senseDist][yLoc].isFood) {
                // Move to spot
                xLoc = xLoc + senseDist;
                // Remove food from grid
                g.grid[xLoc][yLoc].isFood = false;
                // Add food to org
                food++;
            } else if (xLoc - senseDist >= 0 && g.grid[xLoc - senseDist][yLoc].isFood) {
                // Move to spot
                xLoc = xLoc - senseDist;
                // Remove food from grid
                g.grid[xLoc][yLoc].isFood = false;
                // Add food to org
                food++;
            } else if (yLoc + senseDist < g.grid.size() && g.grid[xLoc][yLoc + senseDist].isFood) {
                // Move to spot
                yLoc = yLoc + senseDist;
                // Remove food from grid
                g.grid[xLoc][yLoc].isFood = false;
                // Add food to org
                food++;
            } else if (yLoc - senseDist >= 0 && g.grid[xLoc][yLoc - senseDist].isFood) {
                // Move to spot
                yLoc = yLoc - senseDist;
                // Remove food from grid
                g.grid[xLoc][yLoc].isFood = false;
                // Add food to org
                food++;
            } else {
                // Otherwise, move to a random space in by the grid (easier)
                setLoc(g.getDimensions());
            }
        } else {
            // Check if there is food within senseDist in any direction
            // Since the senseDist for these organisms is 2, we can check within
            // 2 spots from the organsim; check near spots before farther spots
            if (xLoc + 1 < g.grid.size() && g.grid[xLoc + 1][yLoc].isFood) {
                // Move to spot
                xLoc = xLoc + 1;
                // Remove food from grid
                g.grid[xLoc][yLoc].isFood = false;
                // Add food to org
                food++;
            } else if (xLoc - 1 >= 0 && g.grid[xLoc - 1][yLoc].isFood) {
                // Move to spot
                xLoc = xLoc - 1;
                // Remove food from grid
                g.grid[xLoc][yLoc].isFood = false;
                // Add food to org
                food++;
            } else if (yLoc + 1 < g.grid.size() && g.grid[xLoc][yLoc + 1].isFood) {
                // Move to spot
                yLoc = yLoc + 1;
                // Remove food from grid
                g.grid[xLoc][yLoc].isFood = false;
                // Add food to org
                food++;
            } else if (yLoc - 1 >= 0 && g.grid[xLoc][yLoc - 1].isFood) {
                // Move to spot
                yLoc = yLoc - 1;
                // Remove food from grid
                g.grid[xLoc][yLoc].isFood = false;
                // Add food to org
                food++;
            } else if (xLoc + senseDist < g.grid.size() && g.grid[xLoc + senseDist][yLoc].isFood) {
                // Move to spot
                xLoc = xLoc + senseDist;
                // Remove food from grid
                g.grid[xLoc][yLoc].isFood = false;
                // Add food to org
                food++;
            } else if (xLoc - senseDist >= 0 && g.grid[xLoc - senseDist][yLoc].isFood) {
                // Move to spot
                xLoc = xLoc - senseDist;
                // Remove food from grid
                g.grid[xLoc][yLoc].isFood = false;
                // Add food to org
                food++;
            } else if (yLoc + senseDist < g.grid.size() && g.grid[xLoc][yLoc + senseDist].isFood) {
                // Move to spot
                yLoc = yLoc + senseDist;
                // Remove food from grid
                g.grid[xLoc][yLoc].isFood = false;
                // Add food to org
                food++;
            } else if (yLoc - senseDist >= 0 && g.grid[xLoc][yLoc - senseDist].isFood) {
                // Move to spot
                yLoc = yLoc - senseDist;
                // Remove food from grid
                g.grid[xLoc][yLoc].isFood = false;
                // Add food to org
                food++;
            } else {
                // Otherwise, move to a random space in by the grid (easier)
                setLoc(g.getDimensions());
            }
        }
    }
    // Remove energy from the organism
    energy -= energyCost;
}

// Function used every once in a while to print stats about the number of organisms
// that are alive, what the average size, speed are and the mins and maxes.
void Orgs::printStats(int it, bool simple) {
    double avgSize = 0, avgSpeed = 0, avgFood = 0;
    int minSize = INT_MAX, maxSize = INT_MIN, minSpeed = INT_MAX, maxSpeed = INT_MIN,
                  minFood = INT_MAX, maxFood = INT_MIN;
    for (int i = 0; i < orgs.size(); ++i) {
        avgSize += orgs[i].getSize();
        avgSpeed += orgs[i].getSpeed();
        avgFood += orgs[i].getFood();
        if (orgs[i].getSize() > maxSize)
            maxSize = orgs[i].getSize();
        if (orgs[i].getSize() < minSize)
            minSize = orgs[i].getSize();
        if (orgs[i].getSpeed() > maxSpeed)
            maxSpeed = orgs[i].getSpeed();
        if (orgs[i].getSpeed() < minSpeed)
            minSpeed = orgs[i].getSpeed();
        if (orgs[i].getFood() > maxFood)
            maxFood = orgs[i].getFood();
        if (orgs[i].getFood() < minFood)
            minFood = orgs[i].getFood();
    }
    avgSize = avgSize / orgs.size();
    avgSpeed = avgSpeed / orgs.size();
    avgFood = avgFood / orgs.size();
    // Now that we've calculated all of our values, we can print
    if (simple) {
        std::cout << it / 10 << "," << orgs.size() << "," << avgSpeed << "," << avgSize << std::endl;
    } else {
        std::cout << "Data for Iteration " << it << std::endl;
        std::cout << "Number of Organisms: " << orgs.size() << std::endl;
        std::cout << "Total Food: " << g.foodCount << std::endl;
        std::cout << "Average Food: " << avgFood << ", Min: " << minFood
        << ", Max: " << maxFood << std::endl;
        std::cout << "Average Speed: " << avgSpeed << ", Min: " << minSpeed
        << ",  Max: " << maxSpeed << std::endl;
        std::cout << "Average Size: " << avgSize << ", Min: " << minSize
        << ",  Max: " << maxSize << std::endl;
    }
}

// Function allowing organisms to move around the grid at random and get food
void Orgs::interact(int iterationNum, bool simple) {
    // Run this loop the number of grid size squared / numOrgs
    // In each iteration, each organism will have the opportunity to move to
    // pick up food; if there is food within their sensing distance, they can
    // move to pick it up. If they don't see any food, they will move in a random
    // direction (constrained by the edges of the Grid). The number of spaces an
    // org can move per iteration is it's speed.
    // First, set food at the beginning of each iteration
    g.setFood();
    // Re-initialize all organisms food values to 0
    for (int i = 0; i < orgs.size(); ++i) {
        orgs[i].setFood(0);
        orgs[i].setEnergy(100);
        orgs[i].setLoc(g.getDimensions());
    }
    // Go through each organism and allow them to move to find food
    // Have 0.1 * (SIZE^2 / NUM_ORGS) rounds per iteration
    int rounds = (int)(0.1 * g.getDimensions() * g.getDimensions() / orgs.size());
    for (int i = 0; i < rounds; ++i)
        for (int j = 0; j < orgs.size(); ++j)
            if (orgs[j].getEnergy() > orgs[j].getEnergyCost())
                orgs[j].move(g);
    // Based on the iteration number, we will print stats of the state of the
    // organisms and the environment; we will choose multiples of 10 here
    if (iterationNum % 10 == 0)
        printStats(iterationNum, simple);
    // We also need to allow organisms the chance to replicate or die
    std::vector<int> kills;
    std::vector<int> inserts;
    for (int i = 0; i < orgs.size(); ++i) {
        // Check the Org's food, if it is 0, kill the org, if it is greater
        // than 2, allow the org to replicate
        if (orgs[i].getFood() == 0) {
            kills.push_back(i);
        } else if (orgs[i].getFood() >= 10) {
            inserts.push_back(i);
        }
    }
    // Now that we've determined which Orgs are dying and replicating, we can
    // actually remove and append the vector
    int counter = 0;
    for (int i = 0; i < kills.size(); ++i) {
        orgs.erase(orgs.begin() + kills[i] - counter);
        ++counter;
    }
    // For each element in inserts, replicate the org and push it to the back
    for (int i = 0; i < inserts.size(); ++i) {
        Org temp = orgs[inserts[i] - counter];
        orgs.push_back(temp);
    }
}
