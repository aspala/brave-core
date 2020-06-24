/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <stdint.h>
#include <string>
#include <vector>

#include "bat/ads/internal/purchase_intent/purchase_intent_signal_info.h"

namespace ads {

PurchaseIntentSignalInfo::PurchaseIntentSignalInfo() = default;

PurchaseIntentSignalInfo::PurchaseIntentSignalInfo(
    const PurchaseIntentSignalInfo& info) = default;

PurchaseIntentSignalInfo::~PurchaseIntentSignalInfo() = default;

}  // namespace ads