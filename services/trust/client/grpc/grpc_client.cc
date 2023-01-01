#include <memory>

#include "base/check.h"
#include "brave/services/trust/client/grpc/grpc_client.h"
#include "brave/services/trust/client/proto/dnssec_cert_verifier.pb.h"

namespace beacon
{
  namespace core
  {

    template <>
    std::string
    GetGrpcMethodName<::dnssec_cert_verifier::CertVerifyRequest>()
    {
      return "/dnssec_cert_verifier.CertVerifier/VerifyCert";
    }

    GrpcClient::GrpcClient(
        std::shared_ptr<grpc::Channel> channel)
        : channel_(std::move(channel)), client_thread_("BeaconGrpcClient")
    {
      DCHECK(channel_);
    }

    GrpcClient::~GrpcClient() = default;

  } // namespace core
} // namespace beacon