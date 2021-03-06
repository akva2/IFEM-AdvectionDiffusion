// $Id$
//==============================================================================
//!
//! \file AdvectionDiffusionExplicit.h
//!
//! \date Oct 29 2012
//!
//! \author Arne Morten Kvarving / SINTEF
//!
//! \brief Integrand implementations for time-dependent Advection-Diffusion.
//!
//==============================================================================

#ifndef _ADVECTION_DIFFUSION_EXPLICIT_H
#define _ADVECTION_DIFFUSION_EXPLICIT_H

#include "AdvectionDiffusion.h"


/*!
  \brief Class representing the integrand of a time-dependent
         Advection-Diffusion problem.
  \details Time stepping is done using an explicit (RK type) method.
*/

class AdvectionDiffusionExplicit : public AdvectionDiffusion
{
public:
  //! \brief The default constructor initializes all pointers to zero.
  //! \param[in] n Number of spatial dimensions
  //! \param[in] itg_type The integrand type to use
  //! \param[in] form Integrand formulation
  AdvectionDiffusionExplicit(unsigned short int n = 3,
                             int itg_type = STANDARD, int form = 0);

  //! \brief Empty destructor.
  virtual ~AdvectionDiffusionExplicit() {}

  using AdvectionDiffusion::finalizeElement;
  //! \brief Finalizes the element quantities after the numerical integration.
  //! \details This method is invoked once for each element, after the numerical
  //! integration loop over interior points is finished and before the resulting
  //! element quantities are assembled into their system level equivalents.
  virtual bool finalizeElement(LocalIntegral&);

  using AdvectionDiffusion::evalInt;
  //! \brief Evaluates the integrand at an interior point.
  //! \param elmInt The local integral object to receive the contributions
  //! \param[in] fe Finite element data of current integration point
  //! \param[in] X Cartesian coordinates of current integration point
  virtual bool evalInt(LocalIntegral& elmInt, const FiniteElement& fe,
		       const TimeDomain& time, const Vec3& X) const;

  //! \brief Returns a local integral container for the given element.
  //! \param[in] nen Number of nodes on element
  //! \param[in] neumann Whether or not we are assembling Neumann BC's
  virtual LocalIntegral* getLocalIntegral(size_t nen, size_t,
                                          bool neumann) const;

  //! \brief Returns the integrand type.
  virtual int getIntegrandType() const
  {
    return stab == NONE ? STANDARD : SECOND_DERIVATIVES | G_MATRIX;
  }
};

#endif
