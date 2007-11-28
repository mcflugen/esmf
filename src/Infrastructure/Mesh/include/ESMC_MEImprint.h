// $Id: ESMC_MEImprint.h,v 1.3 2007/11/28 16:23:21 dneckels Exp $
//
// Earth System Modeling Framework
// Copyright 2002-2007, University Corporation for Atmospheric Research, 
// Massachusetts Institute of Technology, Geophysical Fluid Dynamics 
// Laboratory, University of Michigan, National Centers for Environmental 
// Prediction, Los Alamos National Laboratory, Argonne National Laboratory, 
// NASA Goddard Space Flight Center.
// Licensed under the University of Illinois-NCSA License.

//
//-----------------------------------------------------------------------------
#ifndef ESMC_MEImprint_h
#define ESMC_MEImprint_h

#include <mesh/ESMC_MeshObj.h>

#include <string>
#include <vector>

namespace ESMC {

class MasterElementBase;

void MEImprintValSets(const std::string &imname, MeshObj &obj,
               const MasterElementBase &me, std::vector<UInt> &nvalSet, std::vector<UInt> &valSetObj);
// Imprint a mesh object with the necessary contexts to define a field
// A common name should be used when imprinting a family of objects, e.g.
// linear lagrange
// Returns number of distinct contexts found
void MEImprint(const std::string &imname, MeshObj &obj,
               const MasterElementBase &me);

} // namespace

#endif
