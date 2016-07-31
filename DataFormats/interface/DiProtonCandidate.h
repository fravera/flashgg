#ifndef FLASHgg_DiProtonCandidate_h
#define FLASHgg_DiProtonCandidate_h

#include "DataFormats/Candidate/interface/CompositeCandidate.h"
// #include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
// #include "DataFormats/Candidate/interface/ShallowCloneCandidate.h"
#include "DataFormats/Candidate/interface/LeafCandidate.h"
#include "flashgg/DataFormats/interface/Proton.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "flashgg/DataFormats/interface/WeightedObject.h"

namespace flashgg {

    class DiProtonCandidate :  public reco::LeafCandidate  , public WeightedObject
    {
    public:
        DiProtonCandidate();
        DiProtonCandidate( edm::Ptr<flashgg::Proton>, edm::Ptr<flashgg::Proton>, double, edm::Ptr<reco::Vertex> );
        void SetProtonForward (edm::Ptr<flashgg::Proton> proton);// { protonForward_  = proton;};
        void SetProtonBackward(edm::Ptr<flashgg::Proton> proton);// { protonBackward_ = proton;};
        void SetComEnergy(double energy) {comEnergy_ = energy;};
        void SetVertex( edm::Ptr<reco::Vertex> vertex);// { CTPPSVertex_ = vertex;};
        // void SetMissingMass(double missingMass) { missingMass_ = missingMass; }; 
        bool ComputeDiProtonObject();
        edm::Ptr<flashgg::Proton> GetProtonForward() const {return protonForward_;}
        edm::Ptr<flashgg::Proton> GetProtonBackward() const {return protonBackward_;}
        edm::Ptr<reco::Vertex> GetProtonVertex() const {return CTPPSVertex_;}
        double GetRapidity() const {return rapidity_;}
        double GetMissingMass() const {return missingMass_;}
        bool IsDoubleTrackingHitArmForward() const {return doubleTrackingHitArmForward_;}
        bool IsDoubleTrackingHitArmBackward() const {return doubleTrackingHitArmBackward_;}
        ~DiProtonCandidate();

    private:
    	bool doubleTrackingHitArmForward_;
    	bool doubleTrackingHitArmBackward_;
        bool vertexFound_;

        edm::Ptr<flashgg::Proton> protonForward_ ;
        edm::Ptr<flashgg::Proton> protonBackward_;
        edm::Ptr<reco::Vertex> CTPPSVertex_;

        double missingMass_;
        double rapidity_   ;
        double comEnergy_  ;
        virtual bool overlap( const Candidate & ) const;

	};
}

#endif
