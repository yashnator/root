// @(#)root/tmva/tmva/cnn:$Id$
// Author: Vladimir Ilievski

/**********************************************************************************
 * Project: TMVA - a Root-integrated toolkit for multivariate data analysis       *
 * Package: TMVA                                                                  *
 * Class  :                                                                       *
 * Web    : http://tmva.sourceforge.net                                           *
 *                                                                                *
 * Description:                                                                   *
 *      Testing Im2Col method on a CPU architecture                               *
 *                                                                                *
 * Authors (alphabetical):                                                        *
 *      Vladimir Ilievski      <ilievski.vladimir@live.com>  - CERN, Switzerland  *
 *                                                                                *
 * Copyright (c) 2005-2015:                                                       *
 *      CERN, Switzerland                                                         *
 *      U. of Victoria, Canada                                                    *
 *      MPI-K Heidelberg, Germany                                                 *
 *      U. of Bonn, Germany                                                       *
 *                                                                                *
 * Redistribution and use in source and binary forms, with or without             *
 * modification, are permitted according to the terms listed in LICENSE           *
 * (http://tmva.sourceforge.net/LICENSE)                                          *
 **********************************************************************************/

////////////////////////////////////////////////////////////////////
// Testing the method Im2col                                      //
////////////////////////////////////////////////////////////////////

#include <iostream>

#include "TMVA/DNN/Architectures/Cpu.h"
#include "TestIm2Col.h"

using namespace TMVA::DNN;
using namespace TMVA::DNN::CNN;


int main()
{
   using Scalar_t = Double_t;
   std::cout << "Testing Im2Col function:" << std::endl;

   std::cout << "Test 1: " << std::endl;
   test1<TCpu<Scalar_t >>();

   std::cout << "Test 2: " << std::endl;
   test2<TCpu<Scalar_t >>();

   std::cout << "Test 3: " << std::endl;
   test3<TCpu<Scalar_t >>();
}
