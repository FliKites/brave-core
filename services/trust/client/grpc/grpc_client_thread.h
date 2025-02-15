// Copyright 2021 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
// source: chromeos/services/libassistant/grpc/grpc_client_thread.h

#ifndef BEACON_SERVICES_TRUST_CLIENT_GRPC_GRPC_CLIENT_THREAD_H_
#define BEACON_SERVICES_TRUST_CLIENT_GRPC_GRPC_CLIENT_THREAD_H_

#include <memory>
#include <string>

#include "base/synchronization/lock.h"
#include "base/threading/platform_thread.h"
#include "base/threading/thread.h"
#include <grpcpp/completion_queue.h>

namespace beacon
{
  namespace core
  {

    // This thread could be shared by multiple grpc clients. It needs to be
    // destroyed after the clients.
    class GrpcClientThread
    {
    public:
      explicit GrpcClientThread(
          const std::string &thread_name,
          base::ThreadType thread_type = base::ThreadType::kDefault);
      GrpcClientThread(const GrpcClientThread &) = delete;
      GrpcClientThread &operator=(const GrpcClientThread &) = delete;
      ~GrpcClientThread();

      grpc::CompletionQueue *completion_queue() { return &completion_queue_; }

    private:
      // Start polling the completion queue.
      void StartCQ();
      // Shutdown the CQ, stop CQ thread, then drain CQ
      void StopCQ();

      void ScanCQInternal();

      grpc::CompletionQueue completion_queue_;
      // Thread to poll the completion queue. Unlike the CQ thread initiated in
      // |ServicesInitializerBase| and used by assistant gRPC server, this thread
      // will *not* be responsible for cleaning up tags returned by calling
      // completion_queue_->Next(). Each tag object will need to delete itself
      // once finished.
      base::Thread thread_;

      base::Lock cq_shutdown_lock_;
      bool is_cq_shutdown_ = false;
    };

  } // namespace core
} // namespace beacon

#endif // BEACON_SERVICES_TRUST_CLIENT_GRPC_GRPC_CLIENT_THREAD_H_
