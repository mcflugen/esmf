// $Id: ESMC_MeshVTK.h,v 1.3 2007/11/28 16:23:22 dneckels Exp $
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
#ifndef ESMC_MeshVTK_h
#define ESMC_MeshVTK_h

#include <mesh/ESMC_MeshTypes.h>

#include <string>

namespace ESMC {

class Mesh;

void WriteVTKMesh(const Mesh &mesh, const std::string &filename);

void ReadVTKMesh(Mesh &mesh, const std::string &filename);

} // namespace

#endif
