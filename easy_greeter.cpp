#include <iostream>
#include <memory>

#include "grpc++/grpc++.h"

#include "helloworld.pb.h"
#include "helloworld.grpc.pb.h"

using helloworld::Greeter;
using helloworld::HelloRequest;
using helloworld::HelloReply;

int main(int argc, char** argv) {
  auto channel_creds = grpc::GoogleDefaultCredentials();
  auto channel = grpc::CreateChannel("greeter.googleapis.com:443", channel_creds);
  std::unique_ptr<Greeter::Stub> stub(Greeter::NewStub(channel));

  {
    grpc::ClientContext ctx;
    HelloRequest req;
    req.set_name("christian");
    HelloReply resp;
    grpc::Status s = stub->SayHello(&ctx, req, &resp);
    if (!s.ok()) {
      std::cerr << "GRPC error: " << s.error_message()  << std::endl;
      return 1;
    }

    std::cout << "GRPC ok: " << resp.ShortDebugString() << std::endl;
  }

  return 0;
}

