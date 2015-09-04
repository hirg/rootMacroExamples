// This macro analyzes a TH1 to find bin ranges with equal numbers of entries.
// The heavy lifting is done by the findParitions() function, which takes a pointer
// to the TH1 and (optionally) a parameter 'delta' which specifies what fraction
// of entries to put in each group. (That is, delta = 0.01 will divide the 
// histogram into equal pieces, each containing 1% of the entries.
// 
// findParitions() is broken into it's own function so that you could load this macro
// with gSystem->Load("partitionHistogram.C") and call it directly.

void findParitions(TH1* hist, Float_t delta = 0.01);

void partitionHistogram(const Float_t delta = 0.01)
{

    // ----------- Create a function and use it to fill some histograms --------------- //
    TF1 f1("f1","gaus(0)",-3,3);
    f1.SetParameters(1,0,1);
    TH1F h1("h1", "Gaussian distribution", 1000, -3, 3);
    h1.FillRandom("f1",10000);

    findParitions(&h1,delta);

}


void findParitions(TH1* hist, Float_t delta)
{

    Int_t nBins = hist->GetNbinsX();
    Float_t temp = 0, sum = 0, perc = 0, lastPerc = 0, target = delta, total = (Float_t)hist->GetEntries();

    for(Int_t i = 1; i <= nBins; i++)
    {
        temp = 0;
        Double_t binContent = hist->GetBinContent(i);
        sum += binContent;
        temp = binContent / total;
        perc = sum / total;
        
        if(perc > target)
        {
            // Did we overshoot? If so: 1) Show perc from last
            // iteration, and 2) do this iteration again
            if( (perc - target) > (target - lastPerc))
            {

            sum -= binContent; // 2)
            i--; // 2)
            cout << 
            "\nBin Center: "    << hist->GetBinCenter(i) << 
            "\tPerc: "          << lastPerc /* 1) */ << 
            "\tTarget: "          << target;

            } else { // ... If we didn't overshoot, continue as normal

            cout << 
            "\nBin Center: "    << hist->GetBinCenter(i) << 
            "\tPerc: "          << perc << 
            "\tTarget: "          << target;

            } 

            target += delta;
        }

        lastPerc = perc;

        if((perc) == 1) { break; }

    }

    cout << endl;

}

/* This is for refmult
21,19,17,15,14,12,11,9 
21+:11
19+:19
17+:29
15+:42
14+:49
12+:63
11+:69
9+:80
*/

/*
This is for number of tracks that pass cuts
75+:0-25
56+:0-50
41+:0-75
*/


