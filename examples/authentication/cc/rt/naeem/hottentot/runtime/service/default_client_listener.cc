#include "default_client_listener.h"


void
DefaultClientListener::OnNewClient(::naeem::hottentot::runtime::service::ClientSession *clientSession) {
  // TODO(kamran) Handle new client.
}

void
DefaultClientListener::OnNewRequest(::naeem::hottentot::runtime::service::ClientSession *clientSession,
                                    unsigned char *requestData,
                                    uint32_t requestDataLength) {
  // TODO(kamran) Handle new message.
}

void
DefaultClientListener::OnClientGone(::naeem::hottentot::runtime::service::ClientSession *clientSession) {
  // TODO(kamran) Handle gone client.
}