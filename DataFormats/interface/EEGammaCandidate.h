#ifndef FLASHgg_EEGammaCandidate_h
#define FLASHgg_EEGammaCandidate_h

#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "flashgg/DataFormats/interface/DiElectronCandidate.h"
#include "flashgg/DataFormats/interface/Photon.h"

// L. Forthomme (KU)
// (modified from the MuMuGammaCandidate container)

namespace flashgg {
    class EEGammaCandidate : public reco::CompositeCandidate
    {
    public:
        EEGammaCandidate();
        EEGammaCandidate( edm::Ptr<flashgg::DiElectronCandidate>, edm::Ptr<flashgg::Photon>, edm::Ptr<reco::Vertex> );
        EEGammaCandidate( edm::Ptr<flashgg::DiElectronCandidate>, const flashgg::Photon &, edm::Ptr<reco::Vertex> ); //mixed
        ~EEGammaCandidate();

        const flashgg::DiElectronCandidate *EEG_DiEle() const;
        const flashgg::Photon *EEG_Photon() const;

        edm::Ptr<flashgg::DiElectronCandidate> DiElePtr() const { return dieleptr_; }
        void setDiElePtr( edm::Ptr<flashgg::DiElectronCandidate> val ) { dieleptr_ = val; }

        edm::Ptr<reco::Vertex> Vertex() const { return vertex_; }
        void setVertex( edm::Ptr<reco::Vertex> val ) { vertex_ = val; }

    private:

        edm::Ptr<flashgg::DiElectronCandidate> dieleptr_;
        edm::Ptr<reco::Vertex> vertex_;

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
