import FWCore.ParameterSet.Config as cms

flashggDiProtonDiPhoton = cms.EDProducer('FlashggDiProtonDiPhotonProducer',
                                  DiProtonTag              = cms.InputTag('flashggDiProtons'),
                                  DiPhotonTag              = cms.InputTag('flashggDiPhotons'),
                                  )
