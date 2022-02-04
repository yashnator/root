/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            *
 *****************************************************************************/

#ifndef ROOHISTCONSTRAINT
#define ROOHISTCONSTRAINT

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "RooListProxy.h"

class RooParamHistFunc ;

class RooHistConstraint : public RooAbsPdf {
public:
  RooHistConstraint() {} ;
  RooHistConstraint(const char *name, const char *title, const RooArgSet& phfSet, Int_t threshold=1000000);
  RooHistConstraint(const RooHistConstraint& other, const char* name=0) ;
  TObject* clone(const char* newname) const override { return new RooHistConstraint(*this,newname); }
  inline ~RooHistConstraint() override { }

  Double_t getLogVal(const RooArgSet* set=0) const override ;

protected:

  RooListProxy _gamma ;
  RooListProxy _nominal ;
  Bool_t _relParam ;

  Double_t evaluate() const override ;

private:

  ClassDefOverride(RooHistConstraint, 2)
};

#endif
