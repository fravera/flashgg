#ifndef FLASHgg_DiProtonDiPhoton_h
#define FLASHgg_DiProtonDiPhoton_h

#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"
#include "flashgg/DataFormats/interface/DiProtonCandidate.h"

namespace flashgg {

    class DiProtonDiPhoton : public DiProtonCandidate, public DiPhotonCandidate
    {
    public:
        DiProtonDiPhoton();
        DiProtonDiPhoton( edm::Ptr<flashgg::DiPhotonCandidate>, edm::Ptr<flashgg::DiProtonCandidate> );
        void ComputeObject ();
        double DeltaMass_;
        double DeltaEta_;
        ~DiProtonDiPhoton();
    private:
      edm::Ptr<flashgg::DiProtonCandidate> DiProton_ ;
      edm::Ptr<flashgg::DiPhotonCandidate> DiPhoton_;

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
