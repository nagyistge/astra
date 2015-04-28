#ifndef HANDSTREAM_H
#define HANDSTREAM_H

#include <SenseKit/Plugins/SingleBinStream.h>
#include <SenseKitUL/streams/hand_types.h>
#include <SenseKitUL/skul_ctypes.h>
#include <SenseKitUL/Plugins/stream_types.h>

namespace sensekit { namespace plugins { namespace hand {

    class HandStream : public SingleBinStream<sensekit_handframe_wrapper_t,
                                              sensekit_handpoint_t>

    {
    public:
        HandStream(PluginServiceProxy& pluginService,
                   Sensor& streamSet,
                   size_t maxHandCount)
            : SingleBinStream(pluginService,
                              streamSet,
                              StreamDescription(SENSEKIT_STREAM_HAND,
                                                DEFAULT_SUBTYPE),
                              sizeof(sensekit_handpoint_t) * maxHandCount)
        { }

        bool include_candidate_points() const { return m_includeCandidatePoints; }
        void set_include_candidate_points(bool includeCandidatePoints)
        {
            m_includeCandidatePoints = includeCandidatePoints;
        }
    protected:
        virtual void set_parameter(sensekit_streamconnection_t connection,
                                   sensekit_parameter_id id,
                                   size_t inByteLength,
                                   sensekit_parameter_data_t inData) override;

        virtual void get_parameter(sensekit_streamconnection_t connection,
                                   sensekit_parameter_id id,
                                   sensekit_parameter_bin_t& parameterBin) override;
    private:
        void get_include_candidates(sensekit_parameter_bin_t& parameterBin);
        void set_include_candidates(size_t inByteLength, sensekit_parameter_data_t& inData);

        bool m_includeCandidatePoints{ false };
    };

}}}

#endif /* HANDSTREAM_H */