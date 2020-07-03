/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_USER_MODEL_BROWSER_REGION_INFO_H_
#define BRAVE_COMPONENTS_BRAVE_USER_MODEL_BROWSER_REGION_INFO_H_

#include <string>

namespace brave_user_model {

struct RegionInfo {
  RegionInfo();
  RegionInfo(
      const std::string& component_id,
      const std::string& component_base64_public_key);
  ~RegionInfo();

  std::string component_id;
  std::string component_base64_public_key;
};

}  // namespace brave_user_model

#endif  // BRAVE_COMPONENTS_BRAVE_USER_MODEL_BROWSER_REGION_INFO_H_
