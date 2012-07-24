#ifndef QDV_PARTICLES_H
#define QDV_PARTICLES_H

#include <memory>
#include <string>
#include <vector>

struct particle {
  float x,y,z;
  float field[4];
};

class ParticleDS {
  public:
    ParticleDS(const char*) { }
    virtual ~ParticleDS() {}

    virtual std::vector<particle> particles(uint16_t component, uint64_t i,
                                            uint64_t count) = 0;
};

struct part_impl;

class RawParticles : public ParticleDS {
  public:
    RawParticles(const char*);
    virtual ~RawParticles() { }

    virtual std::vector<particle> particles(uint16_t, uint64_t, uint64_t);

  private:
    std::unique_ptr<part_impl> pimpl;
};

#endif /* QDV_PARTICLES_H */
