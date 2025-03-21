// Ed Callaghan
// A fixed-length sinusoid
// February 2025

#ifndef TrackerMC_TruncatedSinusoid_hh
#define TrackerMC_TruncatedSinusoid_hh

// stl
#include <cmath>

// clhep
#include "CLHEP/Units/GlobalPhysicalConstants.h"

// mu2e
#include "Offline/GeneralUtilities/inc/UnaryFunction.hh"

namespace mu2e{
  class TruncatedSinusoid: public UnaryFunction{
    public:
      TruncatedSinusoid(double, double, double, double, double);
     ~TruncatedSinusoid() = default;

      double Evaluate(double) override;

    protected:
      double _amplitude;    // baseline-to-peak amplitude
      double _frequency;
      double _phase;
      double _time_lo;      // lower bound of non-zero signal
      double _time_hi;      // upper bound of non-zero signal

    private:
      /**/
  };
} // namespace mu2e

#endif
