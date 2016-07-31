#ifndef FLASHgg_DiProtonDiPhoton_h
#define FLASHgg_DiProtonDiPhoton_h

#include "DataFormats/Candidate/interface/LeafCandidate.h"
#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"
#include "flashgg/DataFormats/interface/DiProtonCandidate.h"

namespace flashgg {

    class DiProtonDiPhoton : public reco::LeafCandidate  , public WeightedObject
    {
    public:
        DiProtonDiPhoton();
        DiProtonDiPhoton( edm::Ptr<flashgg::DiPhotonCandidate>, edm::Ptr<flashgg::DiProtonCandidate> );
        void ComputeObject ();
        ~DiProtonDiPhoton();
        void SetDiProtonCandidate(edm::Ptr<flashgg::DiProtonCandidate> DiProton) { DiProton = DiProton_; } 
        void SetDiPhotonCandidate(edm::Ptr<flashgg::DiPhotonCandidate> DiPhoton) { DiPhoton = DiPhoton_; } 
        edm::Ptr<flashgg::DiProtonCandidate> GetDiProtonCandidate() const {return DiProton_;}
        edm::Ptr<flashgg::DiPhotonCandidate> GetDiPhotonCandidate() const {return DiPhoton_;}
        double GetDeltaMass() const {return DeltaMass_;}
        double GetDeltaEta() const {return DeltaEta_;}
    
    private:
        edm::Ptr<flashgg::DiProtonCandidate> DiProton_ ;
        edm::Ptr<flashgg::DiPhotonCandidate> DiPhoton_;
        double DeltaMass_;
        double DeltaEta_;

    };

}


#endif
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
