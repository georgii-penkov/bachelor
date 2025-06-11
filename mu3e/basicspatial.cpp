#include "getxyz.c"
#include <iostream>
#include <vector>
#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TGraph.h"
#include "TMath.h"
#include "Math/Point3D.h"
#include "Math/Vector3D.h"
#include "TAxis.h"
#include "TCanvas.h"
#include <TApplication.h> //to show the gui and not exit immediately
#include "TH1F.h"
#include <algorithm>

double R_TILES = 60.6638;
double R_PIX_IN = 72.8849;
double R_PIX_OUT = 85.7547;