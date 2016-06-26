#ifndef FLASHgg_Proton_h
#define FLASHgg_Proton_h

#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
#include "flashgg/DataFormats/interface/WeightedObject.h"
#include "FastSimulation/PPSFastObjects/interface/PPSRecoTracks.h"
#include "FastSimulation/PPSFastObjects/interface/PPSBaseTrack.h"


#include <map>
#include <string>
#include <set>

namespace flashgg {

    // class Proton : public WeightedObject
    class Proton : public reco::RecoCandidate , public WeightedObject
    {

    public:
        Proton();
        Proton( const PPSRecoTrack &);
        ~Proton();
        void Variables(const PPSRecoTrack &);
        void Hits(const PPSRecoTrack &);
        void SetDirection(int dir) { direction_ = dir;};
        int GetDirection() const { return direction_;};

    // private:
        int         direction_; //1 = ArmForward, -1 = ArmBackward
        float        X0_;
        float        Y0_;
        float        thetaX_;   // in urad
        float        thetaY_;   // in urad
        float        phi_;
        float        xTrackChiSquare_;
        float        yTrackChiSquare_;
        float        timeOfFlight_;
        bool         Tracker1_;
        bool         Tracker2_;
        bool         Tof_;

    private:
        virtual bool overlap( const Candidate & ) const;

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
