/*
 * void myMultiNestRings(double tol):
 * Sven Kreiss, Kyle Cranmer, Feb 2011
 * 
 *
 * MultiNest: Feroz, Hobson, Bridges, http://arxiv.org/abs/0809.3437
 * This example is explained on page 9 and 10.
 *
 */

#include "RooWorkspace.h"
#include "RooStats/MultiNestCalculator.h"
#include "RooStats/MCMCIntervalPlot.h"
#include "RooStats/ModelConfig.h"

#include "RooArgList.h"
#include "RooFormulaVar.h"
#include "RooRealVar.h"

#include "TStopwatch.h"
#include "TPluginManager.h"
#include "RooClassFactory.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TCanvas.h"

#ifdef _MPI             // this should be defined at compile time if the parallel one is needed -D_MPI
#include <mpi.h>
#endif

using namespace RooFit;
using namespace RooStats;

void myMultiNestRings(double tol);

int main()
{

#ifdef _MPI
  MPI::Init();
  int rank = MPI::COMM_WORLD.Get_rank();        // current process id 
  int procnum = MPI::COMM_WORLD.Get_size();     // number of processes 
  MPI::Status status;
#else
  int rank = 0;
  int procnum = 1;
#endif

  std::cout << "Hello ... from process " << rank+1 << " of " << procnum << std::endl; 

  if(rank == 0) myMultiNestRings(0.001);

#ifdef _MPI
  MPI::Finalize();
#endif

  return 0;
}

void myMultiNestRings(double tol) {

   #ifdef __CINT__
     cout << "DO NOT RUN WITH CINT: this tutorial must be compiled with ACLIC" << endl;
     return;
   #endif
   
   //////////////////////////////////////////////////////
   // Building the "rings" example

   RooWorkspace w("rings");
   w.factory("x[0,-10,10]");
   w.factory("y[0,-10,10]");

   RooArgList axes(*w.var("x"), *w.var("y"));

   w.factory("expr::v1('sqrt((@0-@1)*(@0-@1)+(@2-@3)*(@2-@3))', x, c11[-3.5], y, c12[0])");
   w.factory("RooGaussian::g1(v1,r1[2],w1[.1])");
   w.factory("expr::v2('sqrt((@0-@1)*(@0-@1)+(@2-@3)*(@2-@3))', x, c21[3.5], y, c22[0])");
   w.factory("RooGaussian::g2(v2,r2[2],w2[.1])");
   w.factory("ASUM::model(10*g1,10*g2)");

   TCanvas* c0 = new TCanvas( "c0","Model",800,600 );
   w.pdf("model")->createHistogram( "modelHist", *w.var("x"),  YVar(*w.var("y")) )->Draw("SURF1");
   //   c0->Print("outPut.pdf(");
   c0->Print("outPut.pdf");

   ModelConfig mc("ringsModel", &w);
   mc.SetPdf( *w.pdf("model") );
   mc.SetParametersOfInterest( axes );

   // This is a weird example, because the expression for the Likelihood is given explicitely
   // without adding any data. However some dummy data is technically necessary.
   w.factory( "obsA[-10,10]" );
   w.defineSet( "obs", "obsA" );
   RooDataSet data( "data", "data", *w.set("obs") );
   data.add( *w.set("obs") );


   
   // model building done
   
   //////////////////////////////////////////////////////
   // Running MultiNest on the built model

   MultiNestCalculator m;
   m.SetModel( mc );
   m.SetData( data );
   m.Tol(tol);
   //m.Nlive(400);
   //   m.NClsPar(0);
   //   m.UpdInt(10);
   //   m.MaxModes(10);

   // get interval and store result
   MultiNestInterval* interval = m.GetInterval();
   std::cout << std::endl;
   std::cout << "DONE" << std::endl;
   // Request that
   // ~/wip/RooStat/dev/rootdev/roofit/roostats/inc/RooStats/MCMCIntervalPlot.h
   // be used in v6 so that I can use the methods below

   // TCanvas* c1 = new TCanvas( "c1","Posterior",800,600 );
   // MultiNestIntervalPlot* plot = new MultiNestIntervalPlot( *interval );
   // plot->GetHist2D( *w.var("x"), *w.var("y") )->Draw("SURF1");
   // c1->Print("outPut.pdf");
   
   // TCanvas* c2 = new TCanvas( "c2","Max Likelihood Hist",800,600 );
   // plot->GetMaxLikelihoodHist2D( *w.var("x"), *w.var("y") )->Draw("SURF1");
   // c2->Print("outPut.pdf)");

   return;
}


