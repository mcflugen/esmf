#  $Id: build_rules.mk,v 1.7 2004/03/16 18:00:53 nscollins Exp $
#
#  Linux.nag.default.mk
#


#
#  Make sure that ESMF_PREC is set to 32
#
ESMF_PREC = 32

#
# Default MPI setting.
#
ifndef ESMF_COMM
export ESMF_COMM := mpiuni
endif
ifeq ($(ESMF_COMM),default)
export ESMF_COMM := mpiuni
endif

# if using PBS system, export this for run time
ifdef PBS_NODEFILE
export ESMF_NODES := -machinefile $(PBS_NODEFILE)
endif


############################################################
#
#  The following naming convention is used:
#     XXX_LIB - location of library XXX
#     XXX_INCLUDE - directory for include files needed for library XXX
#

# Location of MPI (Message Passing Interface) software

# comment in one or the other, depending on whether you have
# installed the mpich or lam library. 

ifeq ($(ESMF_COMM),lam)
# with lam-mpi installed:
MPI_LIB        = -lmpi -llam 
MPI_INCLUDE    = 
MPIRUN         =  mpirun
endif

ifeq ($(ESMF_COMM),mpich)
MPI_LIB        = -lmpich
MPI_INCLUDE    = -DESMF_MPICH=1
MPIRUN         =  mpirun
endif

ifeq ($(ESMF_COMM),mpiuni)
# without mpich installed:
MPI_HOME       = ${ESMF_DIR}/src/Infrastructure/mpiuni
MPI_LIB        = -lmpiuni
MPI_INCLUDE    = -I${MPI_HOME}
MPIRUN         =  ${MPI_HOME}/mpirun
endif

# MP_LIB is for openMP
#MP_LIB          = 
#MP_INCLUDE      = 
# For pthreads (or omp)
THREAD_LIB      = 


############################################################
#
AR		   = ar
AR_FLAGS	   = cr
RM		   = rm -f
OMAKE		   = ${MAKE}
RANLIB		   = ranlib
SHELL		   = /bin/sh
SED		   = /bin/sed
SH_LD		   = cc
# ######################### All compilers ########################
ifeq ($(ESMF_COMM),mpich)
C_CC		   = mpicc
C_FC		   = mpif90
C_CLINKER	   = ${C_CC}
C_FLINKER	   = ${C_FC}
CXX_CC		   = mpiCC -fPIC
CXX_FC		   = ${C_FC}
CXX_CLINKER	   = mpiCC
CXX_FLINKER	   = mpiCC
C_F90CXXLD         = ${C_FC}
C_CXXF90LD         = mpiCC
else
C_CC		   = cc
C_FC		   = f90
C_CLINKER	   = ${C_CC}
C_FLINKER	   = ${C_FC}
CXX_CC		   = CC -fPIC
CXX_FC		   = ${C_FC}
CXX_CLINKER	   = CC
CXX_FLINKER	   = CC
C_F90CXXLD         = g++
C_CXXF90LD         = g++
endif
# ######################### C and Fortran compiler options ################
C_FC_MOD           = -I
C_CLINKER_SLFLAG   = -Wl,-rpath,
C_FLINKER_SLFLAG   = -Wl,-rpath,
C_CCV		   = ${C_CC} -v
C_FCV              = ${C_FC} -V
C_SYS_LIB	   = ${MPI_LIB} -ldl -lc -lg2c -lm
# ---------------------------- BOPT - g options ----------------------------
G_COPTFLAGS	   = -g 
G_FOPTFLAGS	   = -g 
# ----------------------------- BOPT - O options -----------------------------
O_COPTFLAGS	   = -O 
O_FOPTFLAGS	   = -O
# ########################## Fortran compiler ##############################
#FFLAGS          = -w=x77 -kind=byte -dusty -mismatch_all-gline
FFLAGS          = -kind=byte -dusty
F_FREECPP       = -free -fpp
F_FIXCPP        = -fixed -fpp
F_FREENOCPP     = -free
F_FIXNOCPP      = -fixed
# ########################## C++ compiler ##################################
#
CXX_CLINKER_SLFLAG = -Wl,-rpath,
CXX_FLINKER_SLFLAG = -Wl,-rpath,
CXX_CCV		   = ${CXX_CC} -V
CXX_SYS_LIB	   = ${MPI_LIB} -ldl -lc -lg2c -lm
CXXLIBBASE         = /soft/com/packages/intel-7/compiler70/ia32/lib
C_F90CXXLIBS       = ${MPI_LIB} -L${F90LIBBASE} -lf96 -lnag \
                     -L${CXXLIBBASE} -lcxa -lunwind -lcprts
F90LIBBASE         = /soft/com/packages/nag-f95-4.2/lib
C_CXXF90LIBS       = ${MPI_LIB} -L${F90LIBBASE} -lf96 -lnag ${F90LIBBASE}/gc.o
# ------------------------- BOPT - g_c++ options ------------------------------
GCXX_COPTFLAGS	   = -g 
GCXX_FOPTFLAGS	   = -g
# ------------------------- BOPT - O_c++ options ------------------------------
OCXX_COPTFLAGS	   = -O 
OCXX_FOPTFLAGS	   = -O
# -------------------------- BOPT - g_complex options ------------------------
GCOMP_COPTFLAGS	   = -g
GCOMP_FOPTFLAGS	   = -g
# --------------------------- BOPT - O_complex options -------------------------
OCOMP_COPTFLAGS	   = -O
OCOMP_FOPTFLAGS	   = -O
##################################################################################

PARCH		   = linux

SL_SUFFIX   = 
SL_LIBOPTS  = 
SL_LINKOPTS = 
SL_F_LINKER = $(F90CXXLD)
SL_C_LINKER = $(CXXF90LD)
SL_LIB_LINKER = $(CXXF90LD)
SL_LIBS_TO_MAKE = libesmf 


#############
#
# Set shared dependent on build_shared to build .so lib.
#
shared: 

