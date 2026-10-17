#ifndef SYSTEM_SETUP_H
#define SYSTEM_SETUP_H

#include "models/Graph.h"
#include "managers/DockManager.h"
#include "managers/BikeManager.h"

using namespace std;

void setupSystem(Graph& campus,DockManager& dockManager,BikeManager& bikeManager);

#endif