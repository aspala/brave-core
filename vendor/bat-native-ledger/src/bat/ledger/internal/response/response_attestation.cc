/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ledger/internal/response/response_attestation.h"

#include "base/base64.h"
#include "base/json/json_reader.h"
#include "base/strings/stringprintf.h"
#include "bat/ledger/internal/logging.h"
#include "net/http/http_status_code.h"

namespace braveledger_response_util {

// Request Url:
// POST /v1/attestations/safetynet (Android)
// POST /v1/devicecheck/attestations (ios)
//
// Response Format:
// {Empty body}

ledger::Result ParseStartAttestationResponse(
    const ledger::UrlResponse& response) {
  if (response.status_code != net::HTTP_OK) {
    return ledger::Result::LEDGER_ERROR;
  }

  return ledger::Result::LEDGER_OK;
}

// Request Url:
// POST /v1/captchas (Desktop)
//
// Response Format:
// {
//   "hint": "circle",
//   "captchaId": "d155d2d2-2627-425b-9be8-44ae9f541762"
// }

ledger::Result ParseCaptchaResponse(
    const ledger::UrlResponse& response,
    base::Value* result) {
  DCHECK(result);

  if (response.status_code != net::HTTP_OK) {
    return ledger::Result::LEDGER_ERROR;
  }

  base::Optional<base::Value> value = base::JSONReader::Read(response.body);
  if (!value || !value->is_dict()) {
    BLOG(0, "Invalid JSON");
    return ledger::Result::LEDGER_ERROR;
  }

  base::DictionaryValue* dictionary = nullptr;
  if (!value->GetAsDictionary(&dictionary)) {
    BLOG(0, "Invalid JSON");
    return ledger::Result::LEDGER_ERROR;
  }

  const auto* captcha_id = dictionary->FindStringKey("captchaId");
  if (!captcha_id) {
    BLOG(0, "Captcha id is wrong");
    return ledger::Result::LEDGER_ERROR;
  }

  const auto* hint = dictionary->FindStringKey("hint");
  if (!hint) {
    BLOG(0, "Hint is wrong");
    return ledger::Result::LEDGER_ERROR;
  }

  result->SetStringKey("hint", *hint);
  result->SetStringKey("captchaId", *captcha_id);

  return ledger::Result::LEDGER_OK;
}

// Request Url:
// GET /v1/captchas/{captcha_id}.png
//
// Response Format:
// {PNG data}

ledger::Result ParseCaptchaImageResponse(
    const ledger::UrlResponse& response,
    std::string* encoded_image) {
  DCHECK(encoded_image);

  base::Base64Encode(response.body, encoded_image);
  *encoded_image =
      base::StringPrintf("data:image/jpeg;base64,%s", encoded_image->c_str());

  return ledger::Result::LEDGER_OK;
}

// Request Url:
// PUT /v1/captchas/{captcha_id} (Desktop)
// POST /v2/attestations/safetynet/{nonce} (Android)
// POST /v1/devicecheck/attestations/{nonce} (ios)
//
// Response Format (success):
// {Empty body}
//
// Response Format (error):
// {
//   "message": "Error solving captcha",
//   "code": 401
// }

ledger::Result ParseConfirmAttestationResponse(
    const ledger::UrlResponse& response) {
  if (response.status_code == net::HTTP_UNAUTHORIZED ||
      response.status_code == net::HTTP_BAD_REQUEST ) {
    return ledger::Result::CAPTCHA_FAILED;
  }

  if (response.status_code != net::HTTP_OK) {
    return ledger::Result::LEDGER_ERROR;
  }

  return ledger::Result::LEDGER_OK;
}

}  // namespace braveledger_response_util
