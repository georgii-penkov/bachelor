gROOT->ProcessLine(".L generatevariables.cpp");
gROOT->ProcessLine(".x generatedata.cpp(&lowerrange, &upperrange, &steps)");
gROOT->ProcessLine(".x analysis.cpp");