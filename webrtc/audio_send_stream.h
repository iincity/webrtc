/*
 *  Copyright (c) 2015 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_AUDIO_SEND_STREAM_H_
#define WEBRTC_AUDIO_SEND_STREAM_H_

#include <string>
#include <vector>

#include "webrtc/base/scoped_ptr.h"
#include "webrtc/config.h"
#include "webrtc/modules/audio_coding/codecs/audio_encoder.h"
#include "webrtc/stream.h"
#include "webrtc/transport.h"
#include "webrtc/typedefs.h"

namespace webrtc {

class AudioSendStream : public SendStream {
 public:
  struct Stats {};

  struct Config {
    Config() = delete;
    explicit Config(Transport* send_transport)
        : send_transport(send_transport) {}

    std::string ToString() const;

    // Receive-stream specific RTP settings.
    struct Rtp {
      std::string ToString() const;

      // Sender SSRC.
      uint32_t ssrc = 0;

      // RTP header extensions used for the received stream.
      std::vector<RtpExtension> extensions;
    } rtp;

    // Transport for outgoing packets. The transport is expected to exist for
    // the entire life of the AudioSendStream and is owned by the API client.
    Transport* send_transport = nullptr;

    // Underlying VoiceEngine handle, used to map AudioSendStream to lower-level
    // components.
    // TODO(solenberg): Remove when VoiceEngine channels are created outside
    // of Call.
    int voe_channel_id = -1;

    // Ownership of the encoder object is transferred to Call when the config is
    // passed to Call::CreateAudioSendStream().
    // TODO(solenberg): Implement, once we configure codecs through the new API.
    // rtc::scoped_ptr<AudioEncoder> encoder;
    int cng_payload_type = -1;  // pt, or -1 to disable Comfort Noise Generator.
    int red_payload_type = -1;  // pt, or -1 to disable REDundant coding.
  };

  virtual Stats GetStats() const = 0;
};
}  // namespace webrtc

#endif  // WEBRTC_AUDIO_SEND_STREAM_H_
