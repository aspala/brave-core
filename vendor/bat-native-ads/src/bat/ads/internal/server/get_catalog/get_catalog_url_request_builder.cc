/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/server/get_catalog/get_catalog_url_request_builder.h"

#include "base/strings/stringprintf.h"
#include "bat/ads/internal/server/ads_server_util.h"
#include "bat/ads/mojom.h"

namespace ads {

GetCatalogUrlRequestBuilder::GetCatalogUrlRequestBuilder() = default;

GetCatalogUrlRequestBuilder::~GetCatalogUrlRequestBuilder() = default;

// GET /v2/catalog

UrlRequest GetCatalogUrlRequestBuilder::Build() {
  UrlRequest request;
  request.url = BuildUrl();
  request.method = UrlRequestMethod::GET;

  return request;
}

//////////////////////////////////////////////////////////////////////////////

std::string GetCatalogUrlRequestBuilder::BuildUrl() const {
  return base::StringPrintf("%s/v2/catalog", server::GetDomain().c_str());
}

}  // namespace ads
