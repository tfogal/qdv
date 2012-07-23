#include <iostream>
#include <stdexcept>
#include <H5Cpp.h>
#include "particles.h"
#include "nonstd.h"

struct part_impl {
  const char* file;
  bool open;
};

RawParticles::RawParticles(const char* fn) : ParticleDS(fn), pimpl(nullptr)
{
}

std::vector<particle> RawParticles::particles(uint16_t component, uint64_t i,
                                              uint64_t count)
{
  return std::vector<particle>();
}
