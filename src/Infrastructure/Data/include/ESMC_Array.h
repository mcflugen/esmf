// $Id: ESMC_Array.h,v 1.13 2003/02/06 22:36:52 nscollins Exp $
//
// Earth System Modeling Framework
// Copyright 2002-2003, University Corporation for Atmospheric Research, 
// Massachusetts Institute of Technology, Geophysical Fluid Dynamics 
// Laboratory, University of Michigan, National Centers for Environmental 
// Prediction, Los Alamos National Laboratory, Argonne National Laboratory, 
// NASA Goddard Space Flight Center.
// Licensed under the GPL.

// ESMF Array C++ declaration include file
//
//-----------------------------------------------------------------------------
//

 #ifndef ESMC_Array_H
 #define ESMC_Array_H

//-----------------------------------------------------------------------------

#include "ESMC_Alloc.h"
#include <string.h>

//-----------------------------------------------------------------------------
//BOP
// !CLASS:  ESMC_Array - uniform access to arrays from F90 and C++
//
// !DESCRIPTION:
//
// The code in this file defines the C++ Array members and declares method 
// signatures (prototypes).  The companion file ESMC\_Array.C contains
// the definitions (full code bodies) for the Array methods.
//
// < insert a paragraph or two explaining what you'll find in this file >
//
//-----------------------------------------------------------------------------
// 
// !USES:
#include <ESMC_Base.h>  // all classes inherit from the ESMC Base class.
 //#include <ESMC_XXX.h>   // other dependent classes (subclasses, aggregates,
                        // composites, associates, friends)

// !PUBLIC TYPES:
 class ESMC_ArrayConfig;
 class ESMC_Array;

 // dummy structure which is the right size for an F90 pointer on
 //  each architcture.  ESMF_F90_PTR_SIZE is defined in conf.h in
 //  the build directories for each architecture
 //  TODO: check that this is a fixed size and does not vary per rank
 //  TODO: check if we can simply save the wrapper and save that and not
 //        have to save the full pointer/dopev
struct c_F90ptr {
   unsigned char pad[ESMF_F90_PTR_SIZE];   
};


// !PRIVATE TYPES:

enum ESMC_ArrayOrigin { ESMC_FROM_FORTRAN = 1, 
                        ESMC_FROM_CPLUSPLUS, 
                        ESMC_UNKNOWN};

// class configuration type
class ESMC_ArrayConfig {
   private:
//   < insert resource items here >
};

// private static data - address of fortran callback funcs
extern "C" {
 static void (*allocfuncaddr)(struct c_F90ptr *, int *, int *, int *) = 0;
 static void (*deallocfuncaddr)(struct c_F90ptr *, int *, int *, int *) = 0;
}


// class declaration type
class ESMC_Array : public ESMC_Base {    // inherits from ESMC_Base class

   private:
    int rank;                      // dimensionality
    enum ESMC_DataType type;       // int, real, etc.
    enum ESMC_DataKind kind;       // short, long
    void *base_addr;               // real start of memory
    int offset[ESMF_MAXDIM];       // byte offset from base to 1st element/dim
    int length[ESMF_MAXDIM];       // number of elements/dim
    int stride[ESMF_MAXDIM];       // byte spacing between elements/dim
    enum ESMC_Logical iscontig;    // optimization possible if all contig
    struct c_F90ptr f90dopev;      // opaque object which is real f90 ptr
                                   // potentially these could be needed... 
    enum ESMC_ArrayOrigin origin;  // was the create called from F90 or C++
    int needs_dealloc;             // is array responsible for deallocation?
 // int lbounds[ESMF_MAXDIM];      // real lower indicies
 // int ubounds[ESMF_MAXDIM];      // real upper indicies
 // void *first_element;           // memory address of the first element
    struct ESMC_AxisIndex ai[ESMF_MAXDIM];   // global-local mapping help
    
// !PUBLIC MEMBER FUNCTIONS:
//
// pick one or the other of the init/create sections depending on
//  whether this is a deep class (the class/derived type has pointers to
//  other memory which must be allocated/deallocated) or a shallow class
//  (the class/derived type is self-contained) and needs no destroy methods
//  other than deleting the memory for the object/derived type itself.

  public:
    void ESMC_ArrayConstruct(ESMC_Array *a, int rank,
                          enum ESMC_DataType dt, enum ESMC_DataKind dk,
                          void *base, int *offsets, int *lengths, int *strides, 
                          void *f90ptr, int *rc);
    //void ESMC_ArrayConstruct(void);
    int ESMC_ArrayDestruct(void);

 // optional configuration methods
    int ESMC_ArrayGetConfig(ESMC_ArrayConfig *config) const;
    int ESMC_ArraySetConfig(const ESMC_ArrayConfig *config);

 // optional index values for subsetting and handling arrays standalone
    int ESMC_ArrayGetAxisIndex(struct ESMC_AxisIndex *index) const;
    int ESMC_ArraySetAxisIndex(struct ESMC_AxisIndex *index);
    
 // accessor methods for class members
    //int ESMC_ArrayGet<Value>(<value type> *value) const;
    //int ESMC_ArraySet<Value>(<value type>  value);
    
 // required methods inherited and overridden from the ESMC_Base class
    int ESMC_ArrayValidate(const char *options) const;
    int ESMC_ArrayPrint(const char *options) const;

 // native C++ constructors/destructors
	ESMC_Array(void);
	~ESMC_Array(void);
  
 // get/set methods for internal data
    void ESMC_ArraySetRank(int rank) { this->rank = rank; }
    int ESMC_ArrayGetRank() { return this->rank; }

    void ESMC_ArraySetType(enum ESMC_DataType type) { this->type = type; }
    enum ESMC_DataType ESMC_ArrayGetType() { return this->type; }

    void ESMC_ArraySetKind(enum ESMC_DataKind kind) { this->kind = kind; }
    enum ESMC_DataKind ESMC_ArrayGetKind() { return this->kind; }

    void ESMC_ArraySetLengths(int n, int *l) { for (int i = 0; i < n; i++)
                                                   this->length[i] = l[i]; }
    void ESMC_ArraySetLengths(int ni) { this->length[0] = ni; }
    void ESMC_ArraySetLengths(int ni, int nj) { 
           this->length[0] = ni; this->length[1] = nj; }
    void ESMC_ArraySetLengths(int ni, int nj, int nk) { 
           this->length[0] = ni; this->length[1] = nj; this->length[2] = nk; }
    void ESMC_ArraySetLengths(int ni, int nj, int nk, int nl) { 
           this->length[0] = ni; this->length[1] = nj; 
           this->length[2] = nk; this->length[3] = nl; }

    void ESMC_ArraySetBaseAddr(void *base_addr) { this->base_addr = base_addr; }
    void ESMC_ArrayGetBaseAddr(void *base_addr) { base_addr = this->base_addr; }

    void ESMC_ArraySetOrigin(enum ESMC_ArrayOrigin o) { this->origin = o; }
    void ESMC_ArrayGetOrigin(enum ESMC_ArrayOrigin *o) { *o = this->origin; }

    // copy the contents of an f90 ptr
    void ESMC_ArraySetF90Ptr(struct c_F90ptr *p) {
        memcpy((void *)(&this->f90dopev), (void *)p, sizeof(struct c_F90ptr)); }
    void ESMC_ArrayGetF90Ptr(struct c_F90ptr *p) {
       memcpy((void *)p, (void *)(&this->f90dopev), sizeof(struct c_F90ptr)); }

    // set/get the dealloc flag
    void ESMC_ArraySetNoDealloc(void) { this->needs_dealloc = 0; }
    void ESMC_ArraySetDealloc(void)   { this->needs_dealloc = 1; }
    int ESMC_ArrayNeedsDealloc(void)  { return this->needs_dealloc; }

    //int offset[ESMF_MAXDIM];       // byte offset from base to 1st element/dim
    //int stride[ESMF_MAXDIM];       // byte spacing between elements/dim
    //enum ESMC_Logical iscontig;    // optimization possible if all contig
    // int lbounds[ESMF_MAXDIM];      // real lower indicies
    // int ubounds[ESMF_MAXDIM];      // real upper indicies
    
 // < declare the rest of the public interface methods here >
  
// !PRIVATE MEMBER FUNCTIONS:
//
  private: 
//
 // < declare private interface methods here >
//
//EOP
//-----------------------------------------------------------------------------

 };   // end class ESMC_Array


// these are functions, but not class methods.
ESMC_Array *ESMC_ArrayCreate(int rank, enum ESMC_DataType dt,
                             enum ESMC_DataKind dk, void *base,
                             int *offsets, int *lengths, int *strides, int *rc);
int ESMC_ArrayDestroy(ESMC_Array *array);
ESMC_Array *ESMC_ArrayCreate_F(int rank, enum ESMC_DataType dt,
                               enum ESMC_DataKind dk, void *base,
                               int *offsets, int *lengths, int *strides,
                               struct c_F90ptr *f90ptr, int *rc);

// internal methods for setting the call back addrs
extern "C" {
    int ESMC_AllocFuncStore(void (*func)(struct c_F90ptr *, int *, int *, int *));
    int ESMC_DeallocFuncStore(void (*func)(struct c_F90ptr *, int *, int *, int *));
}

 #endif  // ESMC_Array_H
