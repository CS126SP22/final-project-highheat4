#include "gas_container.h"
#include "particle.h"

namespace idealgas {

  using glm::vec2;

  GasContainer::GasContainer() {
    width_ = kDefaultWidth;
    height_ = kDefaultHeight;
    x_coor_ = kDefaultXCoord;
    y_coor_ = kDefaultYCoord;

    particles_ = Particle::SpawnParticles(kDefaultCount);
  }

  GasContainer::GasContainer(std::vector<Particle> & particles, vec2 top_left_corner, vec2 bottom_right_corner) {
    x_coor_ = top_left_corner.x;
    y_coor_ = top_left_corner.y;
    width_ = bottom_right_corner.x - x_coor_;
    height_ = bottom_right_corner.y - y_coor_;

    particles_ = particles;
  }

  std::vector<Particle> GasContainer::GetParticles() {
    return particles_;
  }

  void GasContainer::Display() const {
    for (size_t i = 0; i < particles_.size(); i++) {
      ci::gl::color(particles_.at(i).GetColor());
      ci::gl::drawSolidCircle(particles_.at(i).GetPosition(), particles_.at(i).GetRadius());
    }

    ci::gl::drawStrokedRect(ci::Rectf(vec2(x_coor_, y_coor_),
                      vec2(x_coor_ + width_, y_coor_ + height_)));

  }

  void GasContainer::AdvanceOneFrame() {
    for (size_t i = 0; i < particles_.size(); i++) {
      //Checks and updates upon wall collision

      particles_.at(i).CheckContainerCollision(x_coor_, x_coor_ + width_, y_coor_, y_coor_ + height_);

      //Checks and updates upon particle collision
      for (size_t j = i + 1; j < particles_.size(); j++) {
        if (particles_.at(i).ApproachesOtherParticle(particles_.at(j))) {
          if (particles_.at(i).IsTouchingParticles(particles_.at(j))) {
            //Update velocities
            std::vector<vec2> new_velocities =
                particles_.at(i).CalculateCollisionResults(particles_.at(j));

            particles_.at(i).SetVelocity(new_velocities.at(0));
            particles_.at(j).SetVelocity(new_velocities.at(1));
          }
        }
      }

      particles_.at(i).Move();
    }
  }


}  // namespace idealgas
