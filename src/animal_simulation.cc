#include "animal_simulation.h"

namespace animal_simulator {

AnimalSimulationApp::AnimalSimulationApp() {
  ci::app::setWindowSize(kWindowSizeX, kWindowSizeY);
}

void AnimalSimulationApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  container_.Display();
}

void AnimalSimulationApp::update() {
  container_.AdvanceOneFrame();
}

}  // namespace animal_simulator
