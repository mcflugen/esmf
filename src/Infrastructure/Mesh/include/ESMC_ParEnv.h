// $Id: ESMC_ParEnv.h,v 1.2 2007/11/28 16:23:22 dneckels Exp $
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
#ifndef ESMC_ParEnv_h
#define ESMC_ParEnv_h

#include <mesh/ESMC_MeshTypes.h>

#include <iostream>
#include <fstream>
#include <map>

#include <mpi.h>

namespace ESMC {

class ParLog {
public:
// If called (first time) with a fstem, it opens a file
// fstem.rank, otherwise this arg is ignored.
static ParLog *instance(const std::string &fstem="PARALOG", UInt rank = 0);
static std::ofstream &stream() { return ParLog::instance()->of; }
static void flush() { ParLog::instance()->of.flush(); }
private:
static ParLog *classInstance;
ParLog(const std::string &fname);
std::ofstream of;
ParLog(const ParLog&);
ParLog &operator=(const ParLog&);

};




/// *********** Wrap MPI junk *************
class Par {
public:
static void Init(int &argc, char **&argv, const std::string &logfile= "PARLOG", bool _serial=false);
static void Abort();
static void End();
static MPI_Comm Comm() { return MPI_COMM_WORLD;}

static UInt Rank() { return rank; }
static UInt Size() { return psize; }
static bool Serial() { return serial; }

static std::ofstream &Out() { return log->stream(); }
static ParLog *Log() { return log;}

private:
static bool serial;
static int rank;
static int psize;
static ParLog *log;
};

} // namespace

#endif
