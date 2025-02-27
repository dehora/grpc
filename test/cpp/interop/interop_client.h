/*
 *
 * Copyright 2015, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef GRPC_TEST_CPP_INTEROP_INTEROP_CLIENT_H
#define GRPC_TEST_CPP_INTEROP_INTEROP_CLIENT_H

#include <memory>

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include "test/proto/messages.grpc.pb.h"

namespace grpc {
namespace testing {

class InteropClient {
 public:
  explicit InteropClient(std::shared_ptr<Channel> channel);
  ~InteropClient() {}

  void Reset(std::shared_ptr<Channel> channel) { channel_ = channel; }

  void DoEmpty();
  void DoLargeUnary();
  void DoLargeCompressedUnary();
  void DoPingPong();
  void DoHalfDuplex();
  void DoRequestStreaming();
  void DoResponseStreaming();
  void DoResponseCompressedStreaming();
  void DoResponseStreamingWithSlowConsumer();
  void DoCancelAfterBegin();
  void DoCancelAfterFirstResponse();
  void DoTimeoutOnSleepingServer();
  void DoStatusWithMessage();
  // Auth tests.
  // username is a string containing the user email
  void DoJwtTokenCreds(const grpc::string& username);
  void DoComputeEngineCreds(const grpc::string& default_service_account,
                            const grpc::string& oauth_scope);
  // username the GCE default service account email
  void DoOauth2AuthToken(const grpc::string& username,
                         const grpc::string& oauth_scope);
  // username is a string containing the user email
  void DoPerRpcCreds(const grpc::string& json_key);

 private:
  void PerformLargeUnary(SimpleRequest* request, SimpleResponse* response);
  void AssertOkOrPrintErrorStatus(const Status& s);

  std::shared_ptr<Channel> channel_;
};

}  // namespace testing
}  // namespace grpc

#endif  // GRPC_TEST_CPP_INTEROP_INTEROP_CLIENT_H
