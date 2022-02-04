// @(#)root/roostats:$Id$
// Authors: Kevin Belasco        7/22/2009
// Authors: Kyle Cranmer         7/22/2009
/*************************************************************************
 * Copyright (C) 1995-2008, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef RooStats_ProposalHelper
#define RooStats_ProposalHelper

#include "Rtypes.h"
#include "RooStats/ProposalFunction.h"
#include "RooStats/UniformProposal.h"
#include "RooStats/PdfProposal.h"
#include "RooArgSet.h"
#include "RooMsgService.h"
#include "RooRealVar.h"
#include "TMatrixDSym.h"
#include "TObject.h"



namespace RooStats {

   class ProposalHelper : public TObject {

   public:
      ProposalHelper();

      /// Set the PDF to be the proposal density function
      virtual void SetPdf(RooAbsPdf& pdf) { fPdf = &pdf; }
      /// Set the bank of clues to add to the current proposal density function
      virtual void SetClues(RooDataSet& clues) { fClues = &clues; }

      /// Get the ProposalFunction that we've been designing
      virtual ProposalFunction* GetProposalFunction();

      virtual void SetCacheSize(Int_t size)
      {
         if (size > 0)
            fCacheSize = size;
         else
            coutE(Eval) << "Warning: Requested non-positive cache size: " <<
                           size << ". Cache size unchanged." << std::endl;
      }

      virtual void SetUpdateProposalParameters(Bool_t updateParams)
      { fUseUpdates = updateParams; }

      virtual void SetVariables(RooArgList& vars)
      { fVars = &vars; }

      virtual void SetVariables(const RooArgList& vars)
      { fVars = new RooArgList(vars); fOwnsVars = kTRUE; }

      /// set what fraction of the proposal density function should come from
      /// a uniform proposal distribution
      virtual void SetUniformFraction(Double_t uniFrac) { fUniFrac = uniFrac; }

      /// set what fraction of the proposal density function should come from
      /// the bank of clues
      virtual void SetCluesFraction(Double_t cluesFrac) { fCluesFrac = cluesFrac; }

      /// set the covariance matrix to use for a multi-variate Gaussian proposal
      virtual void SetCovMatrix(const TMatrixDSym& covMatrix)
      { fCovMatrix = new TMatrixDSym(covMatrix); }

      /// set what divisor we will use when dividing the range of a variable to
      /// determine the width of the proposal function for each dimension
      /// e.g. divisor = 6 for sigma = 1/6th
      virtual void SetWidthRangeDivisor(Double_t divisor)
      { if (divisor > 0.) fSigmaRangeDivisor = divisor; }

      /// set the option string to pass to the RooNDKeysPdf constructor
      /// if the bank of clues pdf is being automatically generated by this
      /// ProposalHelper
      virtual void SetCluesOptions(const Option_t* options)
      { if (options != NULL) fCluesOptions = options; }

      virtual void SetVariables(RooArgSet& vars)
      {
         RooArgList* argList = new RooArgList(vars);
         SetVariables(*argList);
         fOwnsVars = kTRUE;
      }

      ~ProposalHelper() override
      {
         if (fOwnsPdfProp)      delete fPdfProp;
         if (fOwnsPdf)          delete fPdf;
         if (fOwnsCluesPdf)     delete fCluesPdf;
         if (fOwnsVars)         delete fVars;
         delete fCovMatrix;
         delete fUniformPdf;
      }

   protected:
      RooAbsPdf* fPdf;               ///< the main proposal density function
      RooAbsPdf* fCluesPdf;          ///< proposal dens. func. with clues for certain points
      RooAbsPdf* fUniformPdf;        ///< uniform proposal dens. func.
      RooDataSet* fClues;            ///< data set of clues
      TMatrixDSym* fCovMatrix;       ///< covariance matrix for multi var gaussian pdf
      PdfProposal* fPdfProp;         ///< the PdfProposal we are (probably) going to return
      RooArgList* fVars;             ///< the RooRealVars to generate proposals for
      Int_t fCacheSize;              ///< for generating proposals from PDFs
      Double_t fSigmaRangeDivisor;   ///< range divisor to get sigma for each variable
      Double_t fUniFrac;             ///< what fraction of the PDF integral is uniform
      Double_t fCluesFrac;           ///< what fraction of the PDF integral comes from clues
      Bool_t fOwnsPdfProp;           ///< whether we own the PdfProposal; equivalent to:
                                     ///< !(whether we have returned it in GetProposalFunction)
      Bool_t fOwnsPdf;               ///< whether we created (and own) the main pdf
      Bool_t fOwnsCluesPdf;          ///< whether we created (and own) the clues pdf
      Bool_t fOwnsVars;              ///< whether we own fVars
      Bool_t fUseUpdates;            ///< whether to set updates for proposal params in PdfProposal
      const Option_t* fCluesOptions; ///< option string for clues RooNDKeysPdf

      void CreatePdf();
      void CreateCluesPdf();
      void CreateUniformPdf();
      void CreateCovMatrix(RooArgList& xVec);

      ClassDefOverride(ProposalHelper,1)
   };
}
#endif
