/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_INTERNAL_AD_EVENTS_AD_EVENT_DISMISSED_H_
#define BAT_ADS_INTERNAL_AD_EVENTS_AD_EVENT_DISMISSED_H_

#include "bat/ads/internal/ad_events/ad_event.h"

namespace ads {

class AdsImpl;
struct AdNotificationInfo;

class AdNotificationEventDismissed : public AdEvent<AdNotificationInfo> {
 public:
  AdNotificationEventDismissed(
      AdsImpl* ads);

  ~AdNotificationEventDismissed() override;

  void Trigger(
      const AdNotificationInfo& info) override;

 private:
  AdsImpl* ads_;  // NOT OWNED
};

}  // namespace ads

#endif  // BAT_ADS_INTERNAL_AD_EVENTS_AD_EVENT_DISMISSED_H_