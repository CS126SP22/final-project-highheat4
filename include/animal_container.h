#pragma once

#include "cinder/gl/gl.h"
#include "herbivore.h"
#include "vegetation.h"

using glm::vec2;

namespace animal_simulator {

/**
 * The container in which all of the gas animals are contained. This class
 * stores all of the animals and updates them on each frame of the simulation.
 */
  class AnimalContainer {
  public:

    /**
     * Constructs the gas container.
     */
    AnimalContainer();

    AnimalContainer(std::vector<Herbivore> & animals, vec2 top_left_corner, vec2 bottom_right_corner);

    /**
     * Displays the container walls and the current positions of the animals.
     */
    void Display() const;

    /**
     * Updates the positions and velocities of all animals (based on the rules
     * described in the assignment documentation).
     */
    void AdvanceOneFrame();

    /**
     * @returns animals_ vector
     */
    std::vector<Herbivore> GetAnimals();

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
     * The actual width, height, and top left corner coordinates of the gas container.
     */
    size_t width_; // Width of container.
    size_t height_; // Height of container.
    int x_coor_;
    int y_coor_;

    /**
     * A vector storing all the animals within the animal container.
     */
    std::vector<Herbivore> herbivores_;

    /**
     * A vector storing all the vegetation within the animal container.
     */
    std::vector<Vegetation> vegetation_;

    /**
     * Keeps track of how many frames have passed so as to update spawner.
     */
    int spawn_timer_ = 0;
  };

}