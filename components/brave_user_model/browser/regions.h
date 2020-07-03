/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_USER_MODEL_BROWSER_REGIONS_H_
#define BRAVE_COMPONENTS_BRAVE_USER_MODEL_BROWSER_REGIONS_H_

#include <map>
#include <string>

#include "brave/components/brave_user_model/browser/region_info.h"

namespace brave_user_model {

const std::map<std::string, RegionInfo> regions = {
  {
    "US", RegionInfo(
      "cchgndhfgmkkfmhjhmdenpgdbcdjfmgh",
      "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA22Pjefa2d1B1"
      "Ms3n3554kpGQK9hgnoGgkKnGOODNB9+pwnXIbUBQ0UPNzfxUnqU16++y"
      "3JAbmDpLKswlioRrCY8ZX0uhnotU1ZfqtNd48MEPg/DqJGU37XDxa2lx"
      "SoUQq3ppGUm6j384Ma90WEAW05ZIwfe9fu1AUpO5RRoad79LG5C+Ol2H"
      "bIQQga5YJjpFuAM5KHqbXkrYZfoDOOEAoDiV4YkmZpmsrntB45LoX0eF"
      "aQAMkd7wSujzJ261jSRmc5fBpWni3DCWjeVMqYhv40tNAjtPqwwqXEG2"
      "p3QO3wlT5LLW6mIw/SXSgecW/fzcA7gKwMsoEIumN13j21WH8wIDAQAB"
    )
  },
  {
    "GB", RegionInfo(
      "oldkbaailkiinmopalbhaidpjdndifpa",
      "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA22Pjefa2d1B1"
      "Ms3n3554kpGQK9hgnoGgkKnGOODNB9+pwnXIbUBQ0UPNzfxUnqU16++y"
      "3JAbmDpLKswlioRrCY8ZX0uhnotU1ZfqtNd48MEPg/DqJGU37XDxa2lx"
      "SoUQq3ppGUm6j384Ma90WEAW05ZIwfe9fu1AUpO5RRoad79LG5C+Ol2H"
      "bIQQga5YJjpFuAM5KHqbXkrYZfoDOOEAoDiV4YkmZpmsrntB45LoX0eF"
      "aQAMkd7wSujzJ261jSRmc5fBpWni3DCWjeVMqYhv40tNAjtPqwwqXEG2"
      "p3QO3wlT5LLW6mIw/SXSgecW/fzcA7gKwMsoEIumN13j21WH8wIDAQAB"
    )
  }
};

}  // namespace brave_user_model

#endif  // BRAVE_COMPONENTS_BRAVE_USER_MODEL_BROWSER_REGIONS_H_
