#include <iostream>
void treelooper()
{
    TFile *file = TFile::Open("./test.sim.root");
    file->cd("alignment;1");
    TTree *tiles_tree = file->Get<TTree>("mu3e");
    float x;
    tiles_tree->SetBranchAddress("Ntilehit", &x);
    for (int i = 0; i < tiles_tree->GetEntries(); ++i)
    {
        tiles_tree->GetEntry(i);
        std::cout << x << std::endl;
    };
};
