#include "animal_container.h"
#include "herbivore.h"

namespace animal_simulator {

  using glm::vec2;

  AnimalContainer::AnimalContainer() {
    width_ = kDefaultWidth;
    height_ = kDefaultHeight;
    x_coor_ = kDefaultXCoord;
    y_coor_ = kDefaultYCoord;

    animals_ = Herbivore::SpawnAnimals(kDefaultCount);
  }

  AnimalContainer::AnimalContainer(std::vector<Herbivore> & animals, vec2 top_left_corner, vec2 bottom_right_corner) {
    x_coor_ = top_left_corner.x;
    y_coor_ = top_left_corner.y;
    width_ = bottom_right_corner.x - x_coor_;
    height_ = bottom_right_corner.y - y_coor_;

    animals_ = animals;
  }

  std::vector<Herbivore> AnimalContainer::GetParticles() {
    return animals_;
  }

  void AnimalContainer::Display() const {
    for (size_t i = 0; i < animals_.size(); i++) {
      ci::gl::color(animals_.at(i).GetColor());
      ci::gl::drawSolidCircle(animals_.at(i).GetPosition(), animals_.at(i).GetRadius());
    }

    ci::gl::drawStrokedRect(ci::Rectf(vec2(x_coor_, y_coor_),
                      vec2(x_coor_ + width_, y_coor_ + height_)));

  }

  void AnimalContainer::AdvanceOneFrame() {
    for (size_t i = 0; i < animals_.size(); i++) {
      //Checks and updates upon wall collision

      animals_.at(i).CheckContainerCollision(x_coor_, x_coor_ + width_, y_coor_, y_coor_ + height_);

      //Checks and updates upon animal collision
      for (size_t j = i + 1; j < animals_.size(); j++) {
        if (animals_.at(i).ApproachesOtherAnimal(animals_.at(j))) {
          if (animals_.at(i).IsTouchingAnimal(animals_.at(j))) {
            //Update velocities
            std::vector<vec2> new_velocities =
                animals_.at(i).CalculateCollisionResults(animals_.at(j));

            animals_.at(i).SetVelocity(new_velocities.at(0));
            animals_.at(j).SetVelocity(new_velocities.at(1));
          }
        }
      }

      animals_.at(i).Move();
    }
  }


}  // namespace animal_simulator
