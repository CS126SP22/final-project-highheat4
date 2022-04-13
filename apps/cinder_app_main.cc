#include "animal_simulation.h"

using animal_simulator::AnimalSimulationApp;

void prepareSettings(AnimalSimulationApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(AnimalSimulationApp, ci::app::RendererGl, prepareSettings);
