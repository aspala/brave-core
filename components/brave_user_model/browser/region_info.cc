/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_user_model/browser/region_info.h"

namespace brave_user_model {

RegionInfo::RegionInfo() = default;

RegionInfo::RegionInfo(
    const std::string& component_id,
    const std::string& component_base64_public_key)
    : component_id(component_id),
      component_base64_public_key(component_base64_public_key) {}

RegionInfo::~RegionInfo() = default;

}  // namespace brave_user_model
