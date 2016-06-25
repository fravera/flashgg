#include "flashgg/DataFormats/interface/DiProtonCandidate.h"
#include "flashgg/DataFormats/interface/Proton.h"

using namespace flashgg;

DiProtonCandidate::~DiProtonCandidate() {}

DiProtonCandidate::DiProtonCandidate()
{
	doubleTrackingHitArmForward_  = kFALSE;
    doubleTrackingHitArmBackward_ = kFALSE;
    vertexFound_ = kFALSE;
    missingMass_ = -1.  ;
    rapidity_    = -100.;
}

DiProtonCandidate::DiProtonCandidate( flashgg::Proton *protonForward, flashgg::Proton *protonBackward, double energy, edm::Ptr<reco::Vertex> vertex )
{
    //    std::cout << " DiProtonCandidate::DiProtonCandidate " << std::endl;
    protonForward_  = protonForward ;
    doubleTrackingHitArmForward_  = kFALSE;
    if(protonForward_->Tracker1_  && protonForward_->Tracker2_ ) doubleTrackingHitArmForward_  = kTRUE;
    protonBackward_ = protonBackward;
    doubleTrackingHitArmBackward_ = kFALSE;
    if(protonBackward_->Tracker1_ && protonBackward_->Tracker2_) doubleTrackingHitArmBackward_ = kTRUE;
    CTPPSVertex_ = vertex;
    vertexFound_ = kTRUE;
    missingMass_ = -1.;
    comEnergy_ = energy;
    ComputeDiProtonObject();
    
}

void DiProtonCandidate::SetProtonForward(flashgg::Proton *protonForward)
{
	
	protonForward_  = protonForward ;
    if(protonForward_->Tracker1_  && protonForward_->Tracker2_ ) doubleTrackingHitArmForward_  = kTRUE;
    
}

void DiProtonCandidate::SetProtonBackward(flashgg::Proton *protonBackward)
{
	
	protonBackward_  = protonBackward ;
    if(protonBackward_->Tracker1_  && protonBackward_->Tracker2_ ) doubleTrackingHitArmBackward_  = kTRUE;
    
}

void DiProtonCandidate::SetVertex(edm::Ptr<reco::Vertex> vertex)
{
	CTPPSVertex_ = vertex;
    vertexFound_ = kTRUE;
}

bool DiProtonCandidate::ComputeDiProtonObject()
{

	if( protonBackward_ == NULL || protonForward_ == NULL ) return kFALSE;
	if( (protonBackward_->GetDirection() * protonForward_->GetDirection()) >= 0 ) return kFALSE;
	// missingMass_ = comEnergy_*TMath::Sqrt(protonForward_.xi)

	return kTRUE;
}



