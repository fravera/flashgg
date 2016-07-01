#include "flashgg/DataFormats/interface/DiProtonDiPhoton.h"
#include "flashgg/DataFormats/interface/Photon.h"
#include "flashgg/DataFormats/interface/Proton.h"
#include "CommonTools/CandUtils/interface/AddFourMomenta.h"
#include "TMath.h"


using namespace flashgg;

DiProtonDiPhoton::~DiProtonDiPhoton() {}

DiProtonDiPhoton::DiProtonDiPhoton()
{
  DeltaMass_ = 0.;
  DeltaEta_ = 0.;
}

DiProtonDiPhoton::DiProtonDiPhoton( edm::Ptr<flashgg::DiPhotonCandidate> DiPhoton, edm::Ptr<flashgg::DiProtonCandidate> DiProton)
{
  DiPhoton_ = DiPhoton ;
  DiProton_ = DiProton ;
  ComputeObject();
}

void DiProtonDiPhoton::ComputeObject()
{
  DeltaMass_= DiProton_->mass() - DiPhoton_->mass();
  DeltaEta_= DiProton_->eta() - DiPhoton_->eta();
}



// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
