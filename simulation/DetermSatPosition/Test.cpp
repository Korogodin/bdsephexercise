#include "UnitTest++.h"
#include "Kepler.h"

namespace
{

TEST(OurFirstTest)
{

  double Result = kepler(7.20643904060125351e-04,0.628525);
  // printf("%16.16f",Result);
   //0.6289489513181900
  CHECK_EQUAL(0.6289489513181900, Result);
}
}
