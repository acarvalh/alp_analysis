
#pragma once

#include <algorithm>

#include "TH1.h"
#include "TH2.h"

#include "BaseOperator.h"

template <class EventClass> class JetPlotterOperator : public BaseOperator<EventClass> {

  public:
 
    std::string disc_;
    std::vector<std::string> weights_;
    bool root_;
    std::string dir_;
    std::vector<std::size_t> j_sortInd_;

    TH1D h_jets_ht {"h_jets_ht", "", 300, 0., 900.};

    TH1D h_jet0_pt {"h_jet0_pt", "", 300, 0., 900.};
    TH1D h_jet0_eta {"h_jet0_eta", "", 100, -4.0, 4.0};
    TH1D h_jet0_csv {"h_jet0_csv", "", 300,  -12., 1.};
    TH1D h_jet1_pt {"h_jet1_pt", "", 300, 0., 900.};
    TH1D h_jet1_eta {"h_jet1_eta", "", 100, -4.0, 4.0};
    TH1D h_jet1_csv {"h_jet1_csv", "", 300, -12., 1.};
    TH1D h_jet2_pt {"h_jet2_pt", "", 300, 0., 900.};
    TH1D h_jet2_pt_unc_sq {"h_jet2_pt_unc_sq", "", 300, 0., 900.};
    TH1D h_jet2_eta {"h_jet2_eta", "", 100, -4.0, 4.0};
    TH1D h_jet2_eta_unc_sq {"h_jet2_eta_unc_sq", "", 100, -4.0, 4.0};
    TH1D h_jet2_csv {"h_jet2_csv", "", 300,  -12., 1.};
    TH1D h_jet2_csv_unc_sq {"h_jet2_csv_unc_sq", "", 300,  -12., 1.};
    TH1D h_jet3_pt {"h_jet3_pt", "", 300, 0., 900.};
    TH1D h_jet3_pt_unc_sq {"h_jet3_pt_unc_sq", "", 300, 0., 900.};
    TH1D h_jet3_eta {"h_jet3_eta", "", 100, -4.0, 4.0};
    TH1D h_jet3_eta_unc_sq {"h_jet3_eta_unc_sq", "", 100, -4.0, 4.0};
    TH1D h_jet3_csv {"h_jet3_csv", "", 300,  -12., 1.};
    TH1D h_jet3_csv_unc_sq {"h_jet3_csv_unc_sq", "", 300,  -12., 1.};


     JetPlotterOperator(std::string disc, const std::vector<std::string> & weights = {}, bool root = false, std::string dir = ""  ) :
      disc_(disc),
      weights_(weights),
      root_(root),
      dir_(dir) {}
    virtual ~JetPlotterOperator() {}

    virtual void init(TDirectory * tdir) {
      if (root_) {
        tdir = tdir->GetFile();
        auto ndir = tdir->mkdir(dir_.c_str());
        if (ndir == 0) {
          tdir = tdir->GetDirectory(dir_.c_str());
        } else {
          tdir = ndir;
        }
      }
      h_jets_ht.SetDirectory(tdir);
      h_jet0_pt.SetDirectory(tdir);
      h_jet0_eta.SetDirectory(tdir);
      h_jet0_csv.SetDirectory(tdir);
      h_jet1_pt.SetDirectory(tdir);
      h_jet1_eta.SetDirectory(tdir);
      h_jet1_csv.SetDirectory(tdir);
      h_jet2_pt.SetDirectory(tdir);
      h_jet2_eta.SetDirectory(tdir);
      h_jet2_csv.SetDirectory(tdir);
      h_jet2_pt_unc_sq.SetDirectory(tdir);
      h_jet2_eta_unc_sq.SetDirectory(tdir);
      h_jet2_csv_unc_sq.SetDirectory(tdir);
      h_jet3_pt.SetDirectory(tdir);
      h_jet3_eta.SetDirectory(tdir);
      h_jet3_csv.SetDirectory(tdir);
      h_jet3_pt_unc_sq.SetDirectory(tdir);
      h_jet3_eta_unc_sq.SetDirectory(tdir);
      h_jet3_csv_unc_sq.SetDirectory(tdir);

      h_jets_ht.Sumw2();

      h_jet0_pt.Sumw2();
      h_jet0_eta.Sumw2();
      h_jet0_csv.Sumw2();
      h_jet1_pt.Sumw2();
      h_jet1_eta.Sumw2();
      h_jet1_csv.Sumw2();
      h_jet2_pt.Sumw2();
      h_jet2_eta.Sumw2();
      h_jet2_csv.Sumw2();
      h_jet3_pt.Sumw2();
      h_jet3_eta.Sumw2();
      h_jet3_csv.Sumw2();
      h_jet2_pt_unc_sq.Sumw2();
      h_jet2_eta_unc_sq.Sumw2();
      h_jet2_csv_unc_sq.Sumw2();
      h_jet3_pt_unc_sq.Sumw2();
      h_jet3_eta_unc_sq.Sumw2();
      h_jet3_csv_unc_sq.Sumw2();
   }


    virtual bool process( EventClass & ev ) {

      float w = 1.0;
      float w_unc_sq = 1.0;      

      // get index of ordering by discriminator
      get_sortIndex_jets(j_sortInd_, ev.jets_, disc_);

      auto ht = get_jets_ht(ev.jets_);

      h_jets_ht.Fill(ht, w);
      h_jet0_pt.Fill(ev.jets_.at(j_sortInd_[0]).pt(), w);
      h_jet0_eta.Fill(ev.jets_.at(j_sortInd_[0]).eta(), w);
      h_jet0_csv.Fill(ev.jets_.at(j_sortInd_[0]).CSV(), w);
      h_jet1_pt.Fill(ev.jets_.at(j_sortInd_[1]).pt(), w);
      h_jet1_eta.Fill(ev.jets_.at(j_sortInd_[1]).eta(), w);
      h_jet1_csv.Fill(ev.jets_.at(j_sortInd_[1]).CSV(), w);
      h_jet2_pt.Fill(ev.jets_.at(j_sortInd_[2]).pt(), w);
      h_jet2_eta.Fill(ev.jets_.at(j_sortInd_[2]).eta(), w);
      h_jet2_csv.Fill(ev.jets_.at(j_sortInd_[2]).CSV(), w);
      h_jet3_pt.Fill(ev.jets_.at(j_sortInd_[3]).pt(), w);
      h_jet3_eta.Fill(ev.jets_.at(j_sortInd_[3]).eta(), w);
      h_jet3_csv.Fill(ev.jets_.at(j_sortInd_[3]).CSV(), w);
      h_jet2_pt_unc_sq.Fill(ev.jets_.at(j_sortInd_[2]).pt(), w_unc_sq);
      h_jet2_eta_unc_sq.Fill(ev.jets_.at(j_sortInd_[2]).eta(), w_unc_sq);
      h_jet2_csv_unc_sq.Fill(ev.jets_.at(j_sortInd_[2]).CSV(), w_unc_sq);
      h_jet3_pt_unc_sq.Fill(ev.jets_.at(j_sortInd_[3]).pt(), w_unc_sq);
      h_jet3_eta_unc_sq.Fill(ev.jets_.at(j_sortInd_[3]).eta(), w_unc_sq);
      h_jet3_csv_unc_sq.Fill(ev.jets_.at(j_sortInd_[3]).CSV(), w_unc_sq);

      return true;
    }

    virtual bool output( TFile * tfile) {

      return true;

    }

};