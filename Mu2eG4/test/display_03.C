//
// Crude event display running from the output of
// g4test_03.py
//
//
//
// Original author Rob Kutschke
//
// Double click in the TCanvas( the graphics window )
// to advance to the the next page.
//
// Top of first page shows an xy and rz plot for all hits.
// Bottom of first page shows the same for event 0 only.
//  - The red point is the initial xy direction of the
//    track.
// The second page repeats the bottom two plots for
// events 1 and 2.
// The third page makes a 3d scatter plot of event 1.
//

{

  // With this you can reinvoke the script without exiting root.
  gROOT->Reset();

  // Get rid of grey background on print out.
  gROOT->SetStyle("Plain");

  // Open the input file that contains Mu2e event data.
  TFile* file = new TFile("data_03.root");

  // Fill a pointer to the event tree.
  TTree* event; file->GetObject("Events",event);

  // Define some aliases for convenience.
  // Be careful about defining short aliases in long scripts!

  // There is a way to do this using the native objects, not using aliases.
  // I am still debugging that.


  // Aliases for hit points.
  event->SetAlias("hx",   "mu2eStepPointMCs_g4run__G4Test03.obj._position.dx");
  event->SetAlias("hy",   "mu2eStepPointMCs_g4run__G4Test03.obj._position.dy");
  event->SetAlias("hz",   "mu2eStepPointMCs_g4run__G4Test03.obj._position.dz");
  event->SetAlias("edep", "mu2eStepPointMCs_g4run__G4Test03.obj._edep");
  event->SetAlias("time", "mu2eStepPointMCs_g4run__G4Test03.obj._time");

  // Aliases for initial momentum of the particle.
  event->SetAlias("genid", "mu2eToyGenParticles_generate__G4Test03.obj._generatorId._id");
  event->SetAlias("px", "mu2eToyGenParticles_generate__G4Test03.obj._momentum.pp.dx");
  event->SetAlias("py", "mu2eToyGenParticles_generate__G4Test03.obj._momentum.pp.dy");
  event->SetAlias("pz", "mu2eToyGenParticles_generate__G4Test03.obj._momentum.pp.dz");
  event->SetAlias("ptinv", "1./sqrt(px*px+py*py)");

  // Open window on the screen.
  TCanvas*c = new TCanvas("c", "Test", 0, 0, 900, 900 );

  // Open a postscript file (may be multi-page).
  c->Print("data03.ps[");

  // Split the window into 4 regions.
  c->Divide(2,2);

  // Make a y vs x scatter plot for all events.
  c->cd(1);
  event->Draw( "hy:hx","","");

  // Make an r vs z scatter plot.
  c->cd(2);
  event->Draw( "sqrt(hx*hx+hy*hy):hz","","");

  // Redefine marker from a point to a blue triangle.
  event->SetMarkerStyle(kOpenTriangleUp);
  event->SetMarkerSize(0.5);
  event->SetMarkerColor(kBlue);

  // Plot limits in xy and z.
  double xysize =  750.;
  double zsize  = 1500.;

  // Make a y vs x scatter plot for just the first event.
  // Define the axes ourselves.
  // Arguments to TTree::Draw are:
  // 1 - expression to plot
  // 2 - string to be interpretted as cuts
  // 3 - plot options.  "pSAME" says to overplot on an existing frame.
  // 4 - number of events to loop over.
  // 5 - index of the first event in the loop.

  c->cd(3);
  TH1F* frame;
  frame = c_3->DrawFrame( -xysize, -xysize, xysize, xysize );
  frame->SetTitle("Y vs X for event 0");
  event->Draw( "hy:hx","","PSAME",1,0);

  // Overlay the initial pt.
  event->SetMarkerColor(kRed);
  event->Draw( "py*ptinv*300.:px*ptinv*300.","genid==2","PSAME",1,0);
  event->SetMarkerColor(kBlue);

  // Make an r vs z scatter plot for just the first event.
  c->cd(4);
  frame = c_4->DrawFrame( -xysize, -zsize, xysize, zsize );
  frame->SetTitle("R vs Z for event 0");
  event->Draw( "sqrt(hx*hx+hy*hy):hz","","pSAME",1,0);


  // Flush page to and issue continuation prompt.
  c->Update();
  cerr << "Double click in the Canvas to continue:" ;

  // Print this page to the postscript file.
  c->Print("data03.ps");

  // Wait for response before continuing.
  gPad->WaitPrimitive();

  // Get ready for page 2.
  c->cd(0);
  c->Clear();

  c->Divide(2,2);

  // Y vs X for event 1.
  c->cd(1);
  frame = c_1->DrawFrame( -xysize, -xysize, xysize, xysize );
  frame->SetTitle("Y vs X for event 1");
  event->SetMarkerColor(kBlue);
  event->Draw( "hy:hx","","PSAME",1,1);

  // Overlay the initial pt.
  event->SetMarkerColor(kRed);
  event->Draw( "py*ptinv*300.:px*ptinv*300.","genid==2","PSAME",1,1);
  event->SetMarkerColor(kBlue);

  // R vs Z for event 1.
  c->cd(2);
  frame = c_2->DrawFrame( -xysize, -zsize, xysize, zsize );
  frame->SetTitle("R vs Z for event 1");
  event->SetMarkerColor(kBlue);
  event->Draw( "sqrt(hx*hx+hy*hy):hz","","pSAME",1,1);

  // Y vs X for event 2.
  c->cd(3);
  frame = c_3->DrawFrame( -xysize, -xysize, xysize, xysize );
  frame->SetTitle("Y vs X for event 2");
  event->SetMarkerColor(kBlue);
  event->Draw( "hy:hx","","PSAME",1,2);

  // Overlay the initial pt.
  event->SetMarkerColor(kRed);
  event->Draw( "py*ptinv*300.:px*ptinv*300.","genid==2","PSAME",1,2);
  event->SetMarkerColor(kBlue);


  // R vs Z for event 2.
  c->cd(4);
  frame = c_4->DrawFrame( -xysize, -zsize, xysize, zsize );
  frame->SetTitle("R vs Z for events 2");
  event->SetMarkerColor(kBlue);
  event->Draw( "sqrt(hx*hx+hy*hy):hz","","pSAME",1,2);

  // Flush page to and issue continuation prompt.
  c->Update();
  cerr << "Double click in Canvas to continue:" ;

  // Add this page to the printed output.
  c->Print("data03.ps");

  // Wait for response before continuing.
  gPad->WaitPrimitive();

  // Close the output file.
  c->Print("data03.ps]");

  // Make a 3d view that you can manipulate.
  c->cd(0);
  c->Clear();
  event->Draw( "hy:hx:hz","","",1,0);

 }
