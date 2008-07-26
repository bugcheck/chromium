// Copyright 2008, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//    * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef NET_HTTP_HTTP_PROXY_RESOLVER_WINHTTP_H__
#define NET_HTTP_HTTP_PROXY_RESOLVER_WINHTTP_H__

#include "net/http/http_proxy_service.h"

typedef LPVOID HINTERNET;  // From winhttp.h

namespace net {

// An implementation of HttpProxyResolver that uses WinHTTP and the system
// proxy settings.
class HttpProxyResolverWinHttp : public HttpProxyResolver {
 public:
  HttpProxyResolverWinHttp();
  ~HttpProxyResolverWinHttp();

  // HttpProxyResolver implementation:
  virtual int GetProxyConfig(HttpProxyConfig* config);
  virtual int GetProxyForURL(const std::wstring& query_url,
                             const std::wstring& pac_url,
                             HttpProxyInfo* results);

 private:
   bool OpenWinHttpSession();
   void CloseWinHttpSession();

  // Proxy configuration is cached on the session handle.
  HINTERNET session_handle_;

  DISALLOW_EVIL_CONSTRUCTORS(HttpProxyResolverWinHttp);
};

}  // namespace net

#endif  // NET_HTTP_HTTP_PROXY_RESOLVER_WINHTTP_H__
