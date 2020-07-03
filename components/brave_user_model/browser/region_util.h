/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_USER_MODEL_BROWSER_REGION_UTIL_H_
#define BRAVE_COMPONENTS_BRAVE_USER_MODEL_BROWSER_REGION_UTIL_H_

#include <string>

#include "base/optional.h"
#include "brave/components/brave_user_model/browser/region_info.h"

namespace brave_user_model {

base::Optional<RegionInfo> GetRegionInfo(
    const std::string& country_code);

}  // namespace brave_user_model

#endif  // BRAVE_COMPONENTS_BRAVE_USER_MODEL_BROWSER_REGION_UTIL_H_
