// This macro plots several histograms on the same Canvas, each with a different color scheme
//
// The heavy lifter in this macro is the colorScheme() function, which comes equipped with 4
// hard coded color schemes, indexed 0-3.

void colorScheme(const Int_t index);

void drawMultipleColorSchemes()
{


    // ----------- Create a function and use it to fill some histograms --------------- //
    TF2 f1("f1","exp(-0.5*((x-[0])/[1])**2)*exp(-0.5*((y-[2])/[3])**2)",-3,3,-3,3);

    TH2F* h1 = new TH2F("h1","Gaussian Distribution",100,-3,3,100,-3,3);
    f1.SetParameters(2,.3,2,.5);
    h1->FillRandom("f1",10000);

    TH2F* h2 = new TH2F("h2","Gaussian Distribution",100,-3,3,100,-3,3);
    f1.SetParameters(1.5,.2,-1.8,1);
    h2->FillRandom("f1",10000);

    TH2F* h3 = new TH2F("h3","Gaussian Distribution",100,-3,3,100,-3,3);
    f1.SetParameters(-.6,.9,-2.5,.5);
    h3->FillRandom("f1",10000);

    TH2F* h4 = new TH2F("h4","Gaussian Distribution",100,-3,3,100,-3,3);
    f1.SetParameters(-2,.9,2.1,.1);
    h4->FillRandom("f1",10000);

    // ----------- Draw the histograms, using a TExec for each --------------- //
    h1->Draw();
    TExec* ex1 = new TExec("ex1","colorScheme(0);");
    ex1->Draw();
    h1->Draw("colsame");

    TExec* ex2 = new TExec("ex2","colorScheme(1);");
    ex2->Draw();
    h2->Draw("colsame");

    TExec* ex3 = new TExec("ex3","colorScheme(2);");
    ex3->Draw();
    h3->Draw("colsame");

    TExec* ex4 = new TExec("ex4","colorScheme(3);");
    ex4->Draw();
    h4->Draw("colsame");

}

void colorScheme(const Int_t index)
{
    const  Int_t nCols = 2, nSteps = 50;
    static Int_t  colors[nSteps];

    // Blue - 0
    Double_t r0[nCols] = {0.00,1.00};
    Double_t g0[nCols] = {0.00,1.00};
    Double_t b0[nCols] = {1.00,1.00};
    Double_t L0[nCols] = {0.00,1.00};

    // Red - 1
    Double_t r1[nCols] = {0.70,1.00};
    Double_t g1[nCols] = {0.00,1.00};
    Double_t b1[nCols] = {0.00,1.00};
    Double_t L1[nCols] = {0.00,1.00};

    // Yellow - 2
    Double_t r2[nCols] = {1.00,1.00};
    Double_t g2[nCols] = {0.80,1.00};
    Double_t b2[nCols] = {0.30,1.00};
    Double_t L2[nCols] = {0.00,1.00};
    
    // Avocado - 3
    Double_t r3[nCols] = {0.33,1.00};
    Double_t g3[nCols] = {0.50,1.00};
    Double_t b3[nCols] = {0.00,1.00};
    Double_t L3[nCols] = {0.00,1.00};


    switch(index) {
        case 0: 
            Int_t grad = TColor::CreateGradientColorTable(nCols,L0,r0,g0,b0,nSteps);
            break;

        case 1: 
            Int_t grad = TColor::CreateGradientColorTable(nCols,L1,r1,g1,b1,nSteps);
            break;

        case 2: 
            Int_t grad = TColor::CreateGradientColorTable(nCols,L2,r2,g2,b2,nSteps);
            break;

        case 3: 
            Int_t grad = TColor::CreateGradientColorTable(nCols,L3,r3,g3,b3,nSteps);
            break;

        default:
            cout << "Bad index passed to colorScheme()!\n";
    }

    for (int i=0; i<nSteps; i++) colors[i] = grad+i;

    gStyle->SetPalette(nSteps,colors);
}
