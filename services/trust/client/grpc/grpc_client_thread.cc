// Copyright 2021 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
// source: chromeos/services/libassistant/grpc/grpc_client_thread.cc

#include <memory>

#include "base/bind.h"
#include "base/location.h"
#include "base/logging.h"
#include "base/memory/scoped_refptr.h"
#include "base/task/single_thread_task_runner.h"
#include "brave/services/trust/client/grpc/grpc_client_cq_tag.h"
#include "brave/services/trust/client/grpc/grpc_client_thread.h"

namespace beacon
{
  namespace core
  {

    GrpcClientThread::GrpcClientThread(const std::string &thread_name,
                                       base::ThreadType thread_type)
        : thread_(thread_name)
    {
      base::Thread::Options thread_options = {/*type=*/base::MessagePumpType::IO,
                                              /*size=*/0};
      thread_options.thread_type = thread_type;
      thread_.StartWithOptions(std::move(thread_options));
      StartCQ();
    }

    GrpcClientThread::~GrpcClientThread()
    {
      StopCQ();
    }

    void GrpcClientThread::StartCQ()
    {
      LOG(WARNING) << "Starting GrpcClientThread CQ";

      is_cq_shutdown_ = false;
      thread_.task_runner()->PostTask(
          FROM_HERE, base::BindOnce(&GrpcClientThread::ScanCQInternal,
                                    base::Unretained(this)));
    }

    void GrpcClientThread::StopCQ()
    {
      {
        LOG(WARNING) << "Stopping GrpcClientThread CQ";

        // The lock prevents the following scenario (events listed in time order)
        // 1. CQ thread takes a tag out from completion queue
        // 2. CQ shutdowns
        // 3. CQ thread schedules a gRPC call retry because the call failed
        // Step 3 is problematic because CQ should not be used after shutdown
        base::AutoLock lock(cq_shutdown_lock_);
        completion_queue_.Shutdown();
        is_cq_shutdown_ = true;
      }

      thread_.Stop();
    }

    void GrpcClientThread::ScanCQInternal()
    {
      LOG(WARNING) << "Scanning GrpcClientThread CQ";

      void *tag;
      bool ok;
      while (true)
      {
        // Block waiting for the completion of the next operation in the completion
        // queue. The completing operation is uniquely identified by its tag, which
        // in this case is a pointer to |GrpcClientCQTag| implementing the next step
        // of RPC execution. Next() is thread-safe, and will return true if an event
        // is available, false if the queue is fully drained and shut down.
        if (!completion_queue_.Next(&tag, &ok))
        {
          LOG(WARNING) << "Completion queue shutdown.";
          break;
        }

        LOG(WARNING) << "Read a completion queue event. Invoking its callback.";
        GrpcClientCQTag *callback_tag = static_cast<GrpcClientCQTag *>(tag);
        {
          base::AutoLock lock(cq_shutdown_lock_);
          if (is_cq_shutdown_)
          {
            callback_tag->OnCompleted(GrpcClientCQTag::State::kShutdown);
          }
          else
          {
            callback_tag->OnCompleted(ok ? GrpcClientCQTag::State::kOk
                                         : GrpcClientCQTag::State::kFailed);
          }
        }
      }
    }

  } // namespace core
} // namespace beacon
