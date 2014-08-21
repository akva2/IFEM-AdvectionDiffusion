// $Id$
//==============================================================================
//!
//! \file AdvectionDiffusionBDF.h
//!
//! \date Jun 12 2012
//!
//! \author Arne Morten Kvarving / SINTEF
//!
//! \brief Integrand implementations for time-dependent Advection-Diffusion.
//!
//==============================================================================

#ifndef _ADVECTION_DIFFUSION_BDF_H
#define _ADVECTION_DIFFUSION_BDF_H

#include "AdvectionDiffusion.h"
#include "BDF.h"


/*!
  \brief Class representing the integrand of a time-dependent
         Advection-Diffusion problem.

  \details Time stepping is done using BDF1/BDF2
*/

class AdvectionDiffusionBDF : public AdvectionDiffusion
{
public:
  //! \brief The default constructor initializes all pointers to zero.
  //! \param[in] n Number of spatial dimensions
  //! \param[in] order Temporal order (1,2)
  //! \param[in] itg_type The integrand type to use
  //! \param[in] stab Integrand formulation
  AdvectionDiffusionBDF(unsigned short int n = 3, int order = 1,
                        int itg_type = STANDARD, int form = 0);

  //! \brief Empty destructor.
  virtual ~AdvectionDiffusionBDF() {}

  //! \brief Initializes current element for numerical integration.
  //! \param[in] MNPC Matrix of nodal point correspondance for current element
  virtual bool initElement(const std::vector<int>& MNPC, LocalIntegral& A);

  using AdvectionDiffusion::finalizeElement;
  //! \brief Finalizes the element quantities after the numerical integration.
  //! \details This method is invoked once for each element, after the numerical
  //! integration loop over interior points is finished and before the resulting
  //! element quantities are assembled into their system level equivalents.
  //! It is used here to add stabilization terms to the element matrices.
  virtual bool finalizeElement(LocalIntegral&);

  using AdvectionDiffusion::evalInt;
  //! \brief Evaluates the integrand at an interior point.
  //! \param elmInt The local integral object to receive the contributions
  //! \param[in] fe Finite element data of current integration point
  //! \param[in] X Cartesian coordinates of current integration point
  virtual bool evalInt(LocalIntegral& elmInt, const FiniteElement& fe,
		       const TimeDomain& time, const Vec3& X) const;

  //! \brief Returns the integrand type.
  virtual int getIntegrandType() const
  {
    return stab == NONE ? STANDARD : SECOND_DERIVATIVES | G_MATRIX;
  }

  //! \brief Advance the time stepping scheme
  virtual void advanceStep() { bdf.advanceStep(); }

protected:
  int formulation;           //!< Formulation (STANDARD, RANS, ALE)
  TimeIntegration::BDF bdf;  //!< BDF helper class

  Vectors velocity; //!< The advecting velocity field
  Vector  nut;      //!< The turbulent viscosity field
  Vector  ux;       //!< Grid velocity (ALE)
};

#endif
