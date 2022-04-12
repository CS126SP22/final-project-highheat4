#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

using glm::vec2;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
  class GasContainer {
  public:

    /**
     * Constructs the gas container.
     */
    GasContainer();

    GasContainer(std::vector<Particle> & particles, vec2 top_left_corner, vec2 bottom_right_corner);

    /**
     * Displays the container walls and the current positions of the particles.
     */
    void Display() const;

    /**
     * Updates the positions and velocities of all particles (based on the rules
     * described in the assignment documentation).
     */
    void AdvanceOneFrame();

    /**
     * @returns particles_ vector
     */
    std::vector<Particle> GetParticles();

  private:
    /**
     * Default top-left corner coordinates of the rectangular gas container.
     */
    const int kDefaultXCoord = 100;
    const int kDefaultYCoord = 40;

    /**
     * The default width and height of the gas container.
     */
    const size_t kDefaultWidth = 1200;
    const size_t kDefaultHeight = 500;

    /**
     * The default number of each particle type.
     */
    const size_t kDefaultCount = 10;

    /**
     * The actual width, height, and top left corner coordinates of the gas container.
     */
    size_t width_; // Width of container.
    size_t height_; // Height of container.
    int x_coor_;
    int y_coor_;

    /**
     * A vector storing all the particles within the gas container.
     */
    std::vector<Particle> particles_;

    /**
     * Sorts all the particles by mass.
     */
    void SortByMass();
  };

}